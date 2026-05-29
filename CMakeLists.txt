cmake_minimum_required(VERSION 3.10)

project(Akropolis)


set(CMAKE_CXX_STANDARD 17)

include_directories(inc)
file(GLOB SOURCES "src/*.cpp" "main.cpp")

add_executable(Akropolis ${SOURCES})

if(EMSCRIPTEN)
    set_target_properties(Akropolis PROPERTIES SUFFIX ".html")
    target_link_options(Akropolis PRIVATE
        "--shell-file" "${CMAKE_SOURCE_DIR}/shell_minimal.html"  # Utilise votre modèle avec xterm.js
        "-sASYNCIFY=1"                                          # Requis pour vos boucles/saisies bloquantes getch
        "-sUSE_PTHREADS=0"                                      # Désactive les pthreads si non utilisés
    )
endif()