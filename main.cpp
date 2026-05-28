#include "Vue.h"
// #include "VueGUI.h"
#include "MenuTerminal.h"
#include "Jeu.h"

// #include <QApplication>
// #include <QMainWindow>
// #include <QPushButton>

void runConsoleMode()
{
	menuPrincipalTerminal();
}

// void runGuiMode(int argc, char* argv[])
// {
// 	QApplication app(argc, argv);


// 	app.setStyleSheet(
// 		// Fenêtre principale
// 		"QMainWindow { background-color: #F1F5F9; } "

// 		// CHANTIER : Correction du contour (On utilise . pour cibler uniquement le widget)
// 		".ChantierWidget { "
// 		"   background-color: #FFFFFF; "
// 		"   border: 3px solid #F39C12; "           // Contour complet
// 		"   border-radius: 20px; "    // Arrondis uniquement en bas
// 		"} "
// 		".ChantierWidget QLabel { "
// 		"   color: #1E293B; "
// 		"   font-weight: 900; "
// 		"   text-transform: uppercase; "
// 		"   letter-spacing: 1px; "
// 		"} "

// 		// TABLEAU DES SCORES : Blanc et Gris avec texte contrasté
// 		".ScoreWidget { "
// 		"   background-color: #FFFFFF; "           // Fond blanc
// 		"   border: 3px solid #F39C12; "           // Bordure grise
// 		"   border-radius: 20px; "
// 		"} "
// 		".ScoreWidget QLabel { "
// 		"   color: #1E293B; "
// 		"   font-family: 'Segoe UI'; "
// 		"   font-size: 14px; "
// 		"   font-weight: bold; "
// 		"} "

// 		"QScrollArea { "
// 		"   border: none; "
// 		"   background-color: transparent; "
// 		"} "

// 		// 2. On change le fond du contenu défilable (votre variable 'container')
// 		// On cible le widget directement à l'intérieur de la zone d'affichage (viewport)
// 		"QScrollArea > QWidget > QWidget { "
// 		"   background-color: #F8FAFC; " // Gris-bleu très clair (ou la couleur de votre choix)
// 		"   border-radius: 10px; "
// 		"} "

// 		// TUILES DANS LE CHANTIER
// 		".TuileWidget { "
// 		"   background-color: #F8FAFC; "
// 		"   border: 2px solid #E2E8F0; "
// 		"   border-radius: 20px; "
// 		"} "
// 		".TuileWidget:hover { "
// 		"   border: 3px solid #F39C12; "           // Bordure orange au survol
// 		"   background-color: #FFF7ED; "
// 		"} "

// 		// BOUTONS (Réinitialiser Vue, etc.)
// 		"QPushButton { "
// 		"   background-color: #F39C12; "
// 		"   color: white; "
// 		"   border-radius: 12px; "
// 		"   padding: 8px 16px; "
// 		"   font-weight: bold; "
// 		"   border: 1px solid #D35400; "
// 		"} "
// 		"QPushButton:hover { "
// 		"   background-color: #E67E22; "
// 		"} "

// 		// ZONE DU PLATEAU
// 		"PlateauWidget { "
// 		"   background-color: #FFFFFF; "
// 		"   border: 4px solid #F39C12; "           // Bordure orange épaisse
// 		"   border-radius: 25px; "
// 		"   margin: 10px; "
// 		"} "
// 	);

// 	// Widget central
// 	//GUIcontroler* centralWidget = new GUIcontroler(grid, dataChantier, scoresTest, &window);
// 	VueGUI vue = VueGUI();
// 	vue.jouer();
// 	app.exec();
// }

int main(int argc, char* argv[]){
	std::cout << __cplusplus << std::endl;

	system("cls");
	MenuRestreint menu = MenuRestreint("CHOIX DE LA VERSION", "AKROPOLIS");
	menu.ajouterOption({ "Version Terminal" });
	menu.ajouterOption({ "Version GUI (Qt)" });

	switch (menu.loop()) {
	case 1: runConsoleMode(); //Mode Terminal
		break;
	case 2:
		system("cls");
		// runGuiMode(argc,argv); //Mode Qt
		break;
	}
	system("cls");
	return 0;
}	