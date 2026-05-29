#include "Console.h"
#include <iostream>
#include <algorithm>
#include <cctype>

#if defined(__EMSCRIPTEN__)
    #include <emscripten/html5.h>
    #include <emscripten/emscripten.h>

    static int g_last_wasm_key = 0;
    static int g_wasm_cx = 0;
    static int g_wasm_cy = 0;

    static EM_BOOL wasm_keydown_callback(int eventType, const EmscriptenKeyboardEvent *e, void *userData) {
        std::string key(e->key);
        
        if (key == "Escape") g_last_wasm_key = 27;
        else if (key == "Enter") g_last_wasm_key = 13;
        else if (key == "Backspace") g_last_wasm_key = 8;
        else if (key == "ArrowUp")    g_last_wasm_key = 72;
        else if (key == "ArrowLeft")  g_last_wasm_key = 75;
        else if (key == "ArrowRight") g_last_wasm_key = 77;
        else if (key == "ArrowDown")  g_last_wasm_key = 80;
        else if (!key.empty() && key.size() == 1) {
            g_last_wasm_key = static_cast<unsigned char>(key[0]);
        }

        if (key == "ArrowUp" || key == "ArrowDown" || key == "ArrowLeft" || key == "ArrowRight" || 
            key == " " || key == "Enter" || key == "Backspace" || key == "Escape") {
            return EM_TRUE; 
        }
        return EM_FALSE;
    }

    static void init_wasm_keyboard() {
        static bool initialized = false;
        if (!initialized) {
            emscripten_set_keydown_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, nullptr, EM_TRUE, wasm_keydown_callback);
            MAIN_THREAD_EM_ASM({
                if (typeof FS !== 'undefined' && FS.stream_ops && FS.stream_ops.tty) {
                    FS.stream_ops.tty.read = function() { return 0; };
                }
            });
            initialized = true;
        }
    }

    static void wasm_inject_char_at_cursor(char c, int cx, int cy) {
        MAIN_THREAD_EM_ASM({
            if (typeof window.term !== 'undefined') {
                var charToWrite = String.fromCharCode($0);
                window.term.write("\x1b[s");
                window.term.write("\x1b[" + ($2 + 1) + ";" + ($1 + 1) + "H");
                
                if (charToWrite === "\b") {
                    window.term.write("\b \b");
                } else {
                    window.term.write(charToWrite);
                }
                window.term.write("\x1b[u");
            }
        }, c, cx, cy);
    }
#elif defined(_WIN32)
    #include <windows.h>
    #include <conio.h>
#else
    #include <unistd.h>
    #include <termios.h>

    static int getch_linux() {
        char buf = 0;
        struct termios old{0};
        if (tcgetattr(0, &old) < 0) return 0;
        old.c_lflag &= ~(ICANON | ECHO);
        old.c_cc[VMIN] = 1;
        old.c_cc[VTIME] = 0;
        if (tcsetattr(0, TCSANOW, &old) < 0) return 0;
        
        int nread = read(0, &buf, 1);
        int result = static_cast<unsigned char>(buf);
        
        if (nread > 0 && result == 27) {
            char seq[2];
            if (read(0, &seq[0], 1) > 0 && read(0, &seq[1], 1) > 0) {
                if (seq[0] == '[') {
                    switch (seq[1]) {
                        case 'A': result = 72; break;
                        case 'B': result = 80; break;
                        case 'C': result = 77; break;
                        case 'D': result = 75; break;
                    }
                }
            }
        } else if (nread <= 0) {
            result = 0;
        }
        
        old.c_lflag |= (ICANON | ECHO);
        tcsetattr(0, TCSADRAIN, &old);
        return result;
    }
#endif

namespace Console {

    void clear() {
#if defined(__EMSCRIPTEN__)
        g_wasm_cx = 0;
        g_wasm_cy = 0;
        MAIN_THREAD_EM_ASM({
            if (typeof Module !== 'undefined' && typeof Module.cleanTTY === 'function') {
                Module.cleanTTY();
            }
        });
#endif
        std::cout << "\033[2J\033[1;1H" << std::flush;
    }

    void setCursor(int x, int y) {
#if defined(_WIN32) && !defined(__EMSCRIPTEN__)
        COORD pos = { (SHORT)x, (SHORT)y };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
#elif defined(__EMSCRIPTEN__)
        init_wasm_keyboard();
        g_wasm_cx = x;
        g_wasm_cy = y;
#else
        std::cout << "\033[" << (y + 1) << ";" << (x + 1) << "H" << std::flush;
#endif
    }

    int getWidth() {
#if defined(_WIN32) && !defined(__EMSCRIPTEN__)
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
            return csbi.srWindow.Right - csbi.srWindow.Left + 1;
        }
#endif
        return 80;
    }

    char readKeyFromList(const std::vector<char>& listeValide) {
#if defined(__EMSCRIPTEN__)
        init_wasm_keyboard();
        while (true) {
            emscripten_sleep(20); 
            if (g_last_wasm_key != 0) {
                char c = static_cast<char>(g_last_wasm_key);
                g_last_wasm_key = 0;
                if (std::find(listeValide.begin(), listeValide.end(), c) != listeValide.end()) {
                    return c;
                }
            }
        }
#else
        while (true) {
#if defined(_WIN32)
            int val = _getch();
            if (val == 0 || val == 224) val = _getch();
#else
            int val = getch_linux();
#endif
            char c = static_cast<char>(val);
            if (std::find(listeValide.begin(), listeValide.end(), c) != listeValide.end()) {
                return c;
            }
        }
#endif
    }

    std::optional<std::string> readLineWithEscape(size_t maxChars, bool numeriqueUniquement) {
        std::string entree;
#if defined(__EMSCRIPTEN__)
        init_wasm_keyboard();
        int startX = g_wasm_cx; 
#endif

        while (true) {
            int input_char = 0;

#if defined(__EMSCRIPTEN__)
            emscripten_sleep(20);
            if (g_last_wasm_key != 0) {
                input_char = g_last_wasm_key;
                g_last_wasm_key = 0;
            } else continue;
#elif defined(_WIN32)
            int val = _getch();
            if (val == 0 || val == 224) { _getch(); continue; }
            input_char = val;
#else
            input_char = getch_linux();
            if (input_char == 72 || input_char == 80 || input_char == 75 || input_char == 77) continue;
#endif

            if (input_char == 27) return std::nullopt;
            
            if (input_char == 13 || input_char == '\n' || input_char == '\r') { 
                if (!entree.empty()) {
#if defined(__EMSCRIPTEN__)
                    g_wasm_cx = 0;
                    g_wasm_cy++;
#else
                    std::cout << '\n' << std::flush;
#endif
                    return entree;
                }
            }
            else if (input_char == 8 || input_char == 127) {
                if (!entree.empty()) {
                    entree.pop_back();
#if defined(__EMSCRIPTEN__)
                    if (g_wasm_cx > startX) g_wasm_cx--;
                    wasm_inject_char_at_cursor('\b', g_wasm_cx, g_wasm_cy);
#else
                    std::cout << "\b \b" << std::flush; 
#endif
                }
            }
            else if (entree.size() < maxChars && input_char >= 32 && input_char < 127) {
                char c = static_cast<char>(input_char);
                if (!numeriqueUniquement || std::isdigit(static_cast<unsigned char>(c))) {
                    entree.push_back(c);
#if defined(__EMSCRIPTEN__)
                    wasm_inject_char_at_cursor(c, g_wasm_cx, g_wasm_cy);
                    g_wasm_cx++;
#else
                    std::cout << c << std::flush;
#endif
                }
            }
        }
    }
}