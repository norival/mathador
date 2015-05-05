/***********************************************************************************************************************
*                                                    'TUX MATHADOR'
*
*       Auteur      : Xavier Laviron <xavier.laviron@gmx.fr>
*       Description : Ce programme simule et résoud le jeu 'MATHADOR'
*                     de Éric Trouillot (http://www.mathador.fr/apropos.html)
*                     Il y a trois modes de jeu :
*                         Affichage des soluotions à partir de dés tirés par l'ordinateur
*                         Affichage des soluotions à partir de dés rentrés par l'utilisateur
*                         Simulation de n tirages de dés
*       Projet      : Inititation à la programmation en Licence 3 Biologie des Organismes (Dijon)
*       Date        : 13 mai 2015
*
*		Remarques	: Le programme est capable d'éliminer une partie des doublons mais pas tous
*
*
*		Tux Mathador is free software: you can redistribute it and/or modify
*		it under the terms of the GNU General Public License as published by
*		the Free Software Foundation, either version 3 of the License, or
*		(at your option) any later version.
*
*		Tux Mathador is distributed in the hope that it will be useful,
*		but WITHOUT ANY WARRANTY; without even the implied warranty of
*		MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*		GNU General Public License for more details.
*
*		You should have received a copy of the GNU General Public License
*		along with Tux Mathador.  If not, see <http://www.gnu.org/licenses/>.
*
************************************************************************************************************************/

/// Chargement des bibliothèques nécessaires ///

#include <iostream>    //Utilisation des Entrées/Sorties
#include <stdlib.h>    //Bibliothèque standard : pour utiliser rand()
#include <string>      //Permet d'utiliser les chaînes de caractères
#include <algorithm>   //Permet d'utiliser les fonctions next_permutation() et sort()
#include <iomanip>     //Pour convertir les nombres en caractères
#include <sstream>     //idem
#include <vector>      //Pour utiliser les vecteurs
#include <iomanip>
#include <ctime>
#include <math.h>
#include <float.h>
	#define EPSILON 1E-6
//madfssdfksd
using namespace std;


/// Déclaration des variables globales ///

int i, j, k, n;							//Compteurs
int reponse;							//Réponse de l'utilisateur pour le mode de jeu

float	desCible[2],            		//Tableau stockant les résultats des dés cibles
		cible,                  		//Résultat de la cible
		desNombre[5],           		//Tableau stockant les résultats des dés nombres
		A, B, C, D, E;             		//Variables intermédiaires stockant les opérations entre plusieurs dés

long double	nMathador = 0;				//Nombre de solutions Mathador pour un tirage
long double	nSimulationsMathador = 0;	//Nombre de simulations avec au moins une solution Mathador (Mode simulation seulement)
long double	nSolutions = 0,     		//Nombre de solutions
			nSimulations = 0,  			//Nombre de simulations (Mode simulation seulement)
			nPositives = 0;      		//Nombre de simulations positives (Mode simulation seulement)
long double	temps_initial,				//Calcul du temps d'exécution du programme
			temps_final,				//
			temps_cpu;					//

char operateurs[256][5];   			    //tableau[lignes][colonnes] de toutes les permutations des opérateurs

string solutionTmp;

vector<string> solutions(0);   			//Tableau dynamique stockant toutes les solutions
vector<int> nPoints(0);        			//Tableau dynamique stockant les points de chaque solution


/// Définitions des fonctions ///

float operation(char operateur, float X, float Y)
{
	float Z;
	switch (operateur)
	{
		case '+':
			Z = X+Y;
			break;
		case '*':
			Z = X*Y;
			break;
		case '-':
			Z = X-Y;
			break;
		case '/':
			Z = X/Y;
			break;
		default:
			break;
	}
	return Z;
}

void tirageDes(char mode)
{
	/****************************************************************************
	*						Fonction tirageDes()
	*	Arguments:
	*		char mode: mode de jeu demandé par l'utilisateur
	*			o: Dés tirés par l''o'rdinateur
	*			j: Dés rentrés par le 'j'oueur
	*			s: 's'imulation
	*
	*	Rôles:
	*		Tirage aléatoire des dés si mode et affichage des dés si mode == 'o'
	*		Demande les dés à l'utilisateur si mode == 'j'
	*		Tirage aléatoire des dés sans les afficher si mode == 's'
	****************************************************************************/

	if (mode != 'j')
	{
		srand(time(NULL));
		rand();

		//Tirage des dés cibles
		desCible[0] = rand()%5 + 1;      	//Tirage du dé des dizaines (dé à 6 faces)
		desCible[1] = rand()%10;       		//Tirage du dé des unités (dé à 10 faces)
		cible = desCible[0]*10 + desCible[1];

		//Tirage des dés de jeu
		desNombre[0] = rand()%4 + 1;		//Tirage du dé à 4 faces
		desNombre[1] = rand()%6 + 1;		//Tirage du dé à 6 faces
		desNombre[2] = rand()%8 + 1;		//Tirage du dé à 8 faces
		desNombre[3] = rand()%12 + 1;		//Tirage du dé à 12 faces
		desNombre[4] = rand()%20 + 1;		//Tirage du dé à 20 faces
	}
	if (mode != 's')
	{
		if (mode == 'o')
		{
			cout << "Les dés rouges ont été jetés : " << desCible[0] << " et " << desCible[1] << endl;
			cout << "La cible à atteindre est donc :" << endl;
			cout << cible << endl;
			cout << "Les dés blancs ont été jetés :" << endl;

			for (j = 0; j <= 4; j++)
				cout << desNombre[j] << endl;
		}
		else
		{
			cout << "Rentrer le dé des dizaines" << endl;
			cin >> desCible[0];
			cout << "Rentrer le dé des unités" << endl;
			cin >> desCible[1];

			cible = (desCible[0]*10 + desCible[1])/1.0;

			cout << "La cible est donc : " << cible << endl;
			cout << "Rentrer les dés nombres" << endl;

			for (j = 0; j <= 4; j++)
			{
				cin >> desNombre[j];
				desNombre[j] /= 1.0;
			}
		}
		cout << "Appuyer sur 'Entrée' pour afficher les solutions" << endl;
		//J'ai trouvé cette ligne ici: http://ppfr.it/kfez
		//Elle permet de faire une pause dans la console sous Linux
		cin.ignore().get();
	}
}

void constructionTableau()
{
	/***************************************************************
	*			Fonction constructionTableau()
	*	Rôles:
	*		Construit un tableau de caractères contenant
	*		les 256 permutations possibles des 4 opérateurs
	***************************************************************/

	/// Colonne 4 ///
	//Fin du tableau: permet d'arrêter les calculs quand 'F' est détecté
	for (i = 0; i <= 255; i++)
		operateurs[i][4] = 'F';

	/// Colonne 3 ///
	for (i = 0; i <= 252; i += 4)
	{
		operateurs[i][3] = '+';
		operateurs[i+1][3] = '-';
		operateurs[i+2][3] = '*';
		operateurs[i+3][3] = '/';
	}

	/// Colonne 2 ///
	for (i = 0; i <= 240; i += 16)
	{
		for (j = i; j <= i+3; j++)
			operateurs[j][2] = '+';
		for (j = j; j <= i+7; j++)
			operateurs[j][2] = '-';
		for (j = j; j <= i+11; j++)
			operateurs[j][2] = '*';
		for (j = j; j <= i+15; j++)
			operateurs[j][2] = '/';
	}

	/// Colonne 1 ///
	for (i = 0; i <= 192; i += 64)
	{
		for (j = i; j <= i+15; j++)
			operateurs[j][1] = '+';
		for (j = j; j <= i+31; j++)
			operateurs[j][1] = '-';
		for (j = j; j <= i+47; j++)
			operateurs[j][1] = '*';
		for (j = j; j <= i+63; j++)
			operateurs[j][1] = '/';
	}

	/// Colonne 0 ///
	for (i = 0; i <= 63; i++)
		operateurs[i][0] = '+';
	for (i = 64; i <= 127; i++)
		operateurs[i][0] = '-';
	for (i = 128; i <= 191; i++)
		operateurs[i][0] = '*';
	for (i = 192; i <= 255; i++)
		operateurs[i][0] = '/';
}

void comptagePoints(string result)
{
	/************************************************************************
	*			Fonction comptagePoints()
	*	Arguments:
	*		string result: string temporaire stockant la solution dont il
	*			faut compter les points
	*
	*	Rôles:
	*		Compter les points de la solution stockée dans 'result'
	*		Stocker ces points dans le tableau 'nPoints'
	*		Addition: 		1 point
	*		Soustraction:	2 points
	*		Multiplication:	1 point
	*		Division:		3 points
	************************************************************************/

	//Initialisation des compteurs
	int points = 0;
	bool addition = false;
	bool soustraction = false;
	bool multiplication = false;
	bool division = false;

	for (int l = 0; l < result.size(); l++)
	{
		switch (result[l])
		{
			case '+':
				points += 1;
				addition = true;
				break;
			case '-':
				points += 2;
				soustraction = true;
				break;
			case '*':
				points += 1;
				multiplication = true;
				break;
			case '/':
				points += 3;
				division = true;
				break;
		}
	}

	if (addition == true && soustraction == true && multiplication == true && division == true)
	{
		//Mathador!
		points = 13;
		nMathador++;
	}

	if (addition == false && soustraction == false && multiplication == false && division == false)
	{
		//Solution à 1 dé
		points = 0;
	}

	nPoints.push_back(points);
}

void affichageResultats()
{
	/************************************************************************
	*					Fonction affichageResultat()
	*	Rôles:
	*		Afficher les solutions classées par ordre croissant de points
	************************************************************************/
	bool dejaAffiche1;
	bool dejaAffiche2;

	for (int l = 0; l <= 13; l++)
	{
		dejaAffiche1 = false;
		dejaAffiche2 = false;
		for (int ll = 0; ll < solutions.size(); ll++)
		{
			if (nPoints[ll] == l)
			{
				if (dejaAffiche1 == false)
				{
					dejaAffiche1 = true;
					dejaAffiche2 = true;
					cout << "Solutions à " << l << " points : " << endl;
				}
				cout << solutions[ll] << endl;
			}
		}
		if (dejaAffiche2 == true)
			cout << endl;
	}
}

bool verification33(float X)
{
	if (fabsf(X - cible) <= EPSILON)
		return true;
	else
		return false;
}

void stockageSolution(string solution)
{
	bool existe = false;
	solution += "=";
	solution += static_cast<ostringstream*>( &(ostringstream() << cible) )->str();

	/// Vérification si la solution existe déjà dans le tableau 'solutions' ///
	for (int jj = 0; jj < solutions.size(); jj++)
	{
		if (solution == solutions[jj])
		{
			//La solution existe, on arrête la vérification
			existe = true;
			break;
		}
	}

	/// Stockage de la solution et comptage des points si la solution n'existe pas ///
	if (existe == false)
	{
		nSolutions++;
		solutions.push_back(solution);
		comptagePoints(solution);
	}
}

string constructionGroupement(char chaine)
{
	string groupement = "";

	if (chaine == 'A')
	{
		//Affichage A
		for (int ii = 0; ii <= j; ii++)
			groupement += "(";

		for (int ii = 0; ii <= j+1; ii++)
		{
			groupement += static_cast<ostringstream*>( &(ostringstream() << desNombre[ii]) )->str();
			if (ii > 0)
				groupement += ")";
			if (ii <= j)
				groupement += operateurs[i][ii];
		}
	}

	if (chaine == B)
	{
		//Affichage B
		for (int kk = k-1; kk < 4; kk++)
			groupement += "(";
		for (int kk = 4; kk >= k-1; kk--)
		{
			groupement += static_cast<ostringstream*>( &(ostringstream() << desNombre[kk]) )->str();
			if (kk < 4)
				groupement += ")";
			if (kk > k-1)
				groupement += operateurs[i][kk-1];
		}
	}

	return groupement;
}



int main()
{
	/*********************************
	*  Début du jeu proprement dit
	*********************************/

	/// Variables locales ///
	char reponse;


	cout << "                 .88888888:." << endl;
	cout << "                88888888.88888." << endl;
	cout << "              .8888888888888888." << endl;
	cout << "              888888888888888888" << endl;
	cout << "              88' _`88'_  `88888" << endl;
	cout << "              88 88 88 88  88888" << endl;
	cout << "              88_88_::_88_:88888" << endl;
	cout << "              88:::,::,:::::8888" << endl;
	cout << "              88`:::::::::'`8888" << endl;
	cout << "             .88  `::::'    8:88." << endl;
	cout << "            8888            `8:888." << endl;
	cout << "          .8888'             `888888." << endl;
	cout << "         .8888:..  .::.  ...:'8888888:." << endl;
	cout << "        .8888.'     :'     `'::`88:88888" << endl;
	cout << "       .8888        '         `.888:8888." << endl;
	cout << "      888:8         .           888:88888" << endl;
	cout << "    .888:88        .:           888:88888:" << endl;
	cout << "    8888888.       ::           88:888888" << endl;
	cout << "    `.::.888.      ::          .88888888" << endl;
	cout << "   .::::::.888.    ::         :::`8888'.:." << endl;
	cout << "  ::::::::::.888   '         .::::::::::::" << endl;
	cout << "  ::::::::::::.8    '      .:8::::::::::::." << endl;
	cout << " .::::::::::::::.        .:888:::::::::::::" << endl;
	cout << " :::::::::::::::88:.__..:88888:::::::::::'" << endl;
	cout << "  `'.:::::::::::88888888888.88:::::::::'" << endl;
	cout << "     `':::_:' -- '' -'-' `':_::::'`" << endl;

	cout << "********************************************************************************" << endl;
	cout << "      _____             __  __       _   _               _            " << endl;
	cout << "     |_   _|   ___  __ |  \\/  | __ _| |_| |__   __ _  __| | ___  _ __ " << endl;
	cout << "       | || | | \\ \\/ / | |\\/| |/ _` | __| '_ \\ / _` |/ _` |/ _ \\| '__|" << endl;
	cout << "       | || |_| |>  <  | |  | | (_| | |_| | | | (_| | (_| | (_) | |   " << endl;
	cout << "       |_| \\__,_/_/\\_\\ |_|  |_|\\__,_|\\__|_| |_|\\__,_|\\__,_|\\___/|_|   " << endl;
	cout << "********************************************************************************" << endl;

	cout << "Bienvenue dans le jeu 'Tux Mathador' ! Adaptation numérique du célèbre jeu de dé." << endl;
	cout << "Les règles du jeu sont disponibles ici : http://ppfr.it/k0to" << endl;
	cout << "Je vous propose 3 modes de jeu différents" << endl;
	cout << "Lequel choisissez-vous ?" << endl;
	cout << "o: Calcul de solutions à partir de dés tirés par la machine" << endl;
	cout << "j: Calcul de solutions à partir de dés rentrés par l'utilisateur" << endl;
	cout << "s: Mode simulation. Calcul de solutions pour n tirages de dés" << endl;
	do
	{
		cin >> reponse;
	} while (reponse != 'o' && reponse != 'j' && reponse != 's');

	system("clear");

	if (reponse == 'o' || reponse == 'j')
		nSimulations = 1;
	else
	{
		cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
		cout << "%                    Mode simulation                   %" << endl;
		cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
		cout << endl;
		cout << "Ce mode permet de calculer le nombre de simulations ayant au moins une réponse pour n simulations" << endl;
		cout << "Il affiche également la proportion de simulations ayant au moins une solution 'Mathador' (avec tous les opérateurs utilisés)" << endl;
		cout << "Combien de simulations voulez-vous effectuer ?" << endl;
		cin >> nSimulations;
//		cout << "Calcul des simulations en cours..." << endl;
	}

	n = 0;                 //Initialisation du compteur de simulations
	constructionTableau(); //Construction du tableau de permutations d'opérateurs

	temps_initial = clock ();

	do
	{
		/// Cette boucle est répétée tant que le nombre de simulations n'est pas atteint ///

		//On tire les dés
		tirageDes(reponse);

		/// Début des tests ///

		//Solutions à 1 dé
		for (j = 0; j <= 4; j++)
		{
			if (verification33(desNombre[j]) == true)
			{
				solutionTmp = static_cast<ostringstream*>( &(ostringstream() << desNombre[j]) )->str();
			}
		}

		//Autres solutions

		/*****************************************************************************************
		*                                  ALGORITHME
		*	La boucle suivante teste toutes les permutations possibles de dés avec toutes les
		*	permutations possibles d'opérateurs en lisant la succession d'opérateurs dans le
		*	tableau 'operateurs[ligne][colonne]'
		*
		*	Pour j == 0, on teste également les groupements de 2 blocs de 2 dés, puis les
		*	groupements de 2 blocs de 2 dés et 1 dé
		*	Pour j > 0, on teste les groupements en repartant de la fin du tableau de dés
		*
		*	Les permutations possibles des dés sont faites par la fonction next_permutation(),
		*	qui a été trouvée ici : http://ppfr.it/k09v
		*****************************************************************************************/

		sort(desNombre, desNombre+5); //Trie les valeurs des dés pour initialiser les permutations de 'next_permuation'
		do
		{
			for (i = 0; i <= 255; i++)
			{
				A = desNombre[0];
//				solutionTmp = "";
				for (j = 0; j <= 4; j++)
				{
					if (operateurs[i][j] == 'F')
						break;
					A = operation(operateurs[i][j], A, desNombre[j+1]);
					if (verification33(A) == true)
					{
						solutionTmp = "E";
						//Affichage A
						for (int ii = 0; ii <= j; ii++)
							solutionTmp += "(";

						for (int ii = 0; ii <= j+1; ii++)
						{
							solutionTmp += static_cast<ostringstream*>( &(ostringstream() << desNombre[ii]) )->str();
							if (ii > 0)
								solutionTmp += ")";
							if (ii <= j)
								solutionTmp += operateurs[i][ii];
						}
//						solutionTmp = constructionGroupement('A');
						stockageSolution(solutionTmp);
					}

					//Vérification dans l'autre sens, pour les groupements par parenthèses
					B = desNombre[4];
					for (k = 4; k > j+2; k--)
					{
						B = operation(operateurs[i][k-1], B, desNombre[k-1]);
						C = operation(operateurs[i][j+1], A, B);
						if (verification33(C) == true)
						{
							solutionTmp = "";
							//Affichage A
							for (int ii = 0; ii <= j; ii++)
							solutionTmp += "(";

							for (int ii = 0; ii <= j+1; ii++)
							{
								solutionTmp += static_cast<ostringstream*>( &(ostringstream() << desNombre[ii]) )->str();
								if (ii > 0)
									solutionTmp += ")";
								if (ii <= j)
									solutionTmp += operateurs[i][ii];
							}
							///
							solutionTmp += operateurs[i][j+1];
							///
							//Affichage B
							for (int kk = k-1; kk < 4; kk++)
								solutionTmp += "(";
							for (int kk = 4; kk >= k-1; kk--)
							{
								solutionTmp += static_cast<ostringstream*>( &(ostringstream() << desNombre[kk]) )->str();
								if (kk < 4)
									solutionTmp += ")";
								if (kk > k-1)
									solutionTmp += operateurs[i][kk-1];
							}
							stockageSolution(solutionTmp);
						}

						if (k == 4 && j == 0)
						{
							D = operation(operateurs[i][j+1], A, desNombre[2]);
							E = operation(operateurs[i][j+2], D, B);
							if (verification33(E) == true)
							{
								solutionTmp = "(";
								//Affichage A
								for (int ii = 0; ii <= j; ii++)
								solutionTmp += "(";

								for (int ii = 0; ii <= j+1; ii++)
								{
									solutionTmp += static_cast<ostringstream*>( &(ostringstream() << desNombre[ii]) )->str();
									if (ii > 0)
										solutionTmp += ")";
									if (ii <= j)
										solutionTmp += operateurs[i][ii];
								}
								//Affichage Dé2
								solutionTmp += operateurs[i][j+1];
								solutionTmp += static_cast<ostringstream*>( &(ostringstream() << desNombre[2]) )->str();
								solutionTmp += ")";
								solutionTmp += operateurs[i][j+2];
								//Affichage B
								for (int kk = k-1; kk < 4; kk++)
									solutionTmp += "(";
								for (int kk = 4; kk >= k-1; kk--)
								{
									solutionTmp += static_cast<ostringstream*>( &(ostringstream() << desNombre[kk]) )->str();
									if (kk < 4)
										solutionTmp += ")";
									if (kk > k-1)
										solutionTmp += operateurs[i][kk-1];
								}
								stockageSolution(solutionTmp);
							}

							if (operateurs[i][j+2] == '-' || operateurs[i][j+2] == '/')
							{
								E = operation(operateurs[i][j+2], B, D);
								if (verification33(E) == true)
								{
									solutionTmp = "";
									//Affichage B
									for (int kk = k-1; kk < 4; kk++)
										solutionTmp += "(";
									for (int kk = 4; kk >= k-1; kk--)
									{
										solutionTmp += static_cast<ostringstream*>( &(ostringstream() << desNombre[kk]) )->str();
										if (kk < 4)
											solutionTmp += ")";
										if (kk > k-1)
											solutionTmp += operateurs[i][kk-1];
									}
									solutionTmp += operateurs[i][j+2];
									solutionTmp += "(";
									//Affichage A
									for (int ii = 0; ii <= j; ii++)
									solutionTmp += "(";

									for (int ii = 0; ii <= j+1; ii++)
									{
										solutionTmp += static_cast<ostringstream*>( &(ostringstream() << desNombre[ii]) )->str();
										if (ii > 0)
											solutionTmp += ")";
										if (ii <= j)
											solutionTmp += operateurs[i][ii];
									}
									//Affichage Dé2
									solutionTmp += operateurs[i][j+1];
									solutionTmp += static_cast<ostringstream*>( &(ostringstream() << desNombre[2]) )->str();
									solutionTmp += ")";

									stockageSolution(solutionTmp);
								}
							}

							D = operation(operateurs[i][j+1], A, B);
							E = operation(operateurs[i][j+2], D, desNombre[2]);
							if (verification33(E) == true)
							{
								//Affichage
								solutionTmp ="(";
								for (int ii = 0; ii <= j; ii++)
									solutionTmp += "(";

								for (int ii = 0; ii <= j+1; ii++)
								{
									solutionTmp += static_cast<ostringstream*>( &(ostringstream() << desNombre[ii]) )->str();
									if (ii > 0)
										solutionTmp += ")";
									if (ii <= j)
										solutionTmp += operateurs[i][ii];
								}
								///
								solutionTmp += operateurs[i][j+1];
								//Affichage B
								for (int kk = k-1; kk < 4; kk++)
									solutionTmp += "(";
								for (int kk = 4; kk >= k-1; kk--)
								{
									solutionTmp += static_cast<ostringstream*>( &(ostringstream() << desNombre[kk]) )->str();
									if (kk < 4)
										solutionTmp += ")";
									if (kk > k-1)
										solutionTmp += operateurs[i][kk-1];
								}
								solutionTmp += ")";
								//Affichage Dé2
								solutionTmp += operateurs[i][j+2];
								solutionTmp += static_cast<ostringstream*>( &(ostringstream() << desNombre[2]) )->str();
								stockageSolution(solutionTmp);
							}

							if (operateurs[i][j+2] == '-' || operateurs[i][j+2] == '/')
							{
								E = operation(operateurs[i][j+2], desNombre[2], D);
//								verification(E, 1);
								if (verification33(E) == true)
								{
									solutionTmp = "";
									solutionTmp += static_cast<ostringstream*>( &(ostringstream() << desNombre[2]) )->str();
									solutionTmp += operateurs[i][j+2];
									solutionTmp += "(";
									//Affichage A
									for (int ii = 0; ii <= j; ii++)
									solutionTmp += "(";

									for (int ii = 0; ii <= j+1; ii++)
									{
										solutionTmp += static_cast<ostringstream*>( &(ostringstream() << desNombre[ii]) )->str();
										if (ii > 0)
											solutionTmp += ")";
										if (ii <= j)
											solutionTmp += operateurs[i][ii];
									}									///
										solutionTmp += operateurs[i][j+1];
									//Affichage B
									for (int kk = k-1; kk < 4; kk++)
										solutionTmp += "(";
									for (int kk = 4; kk >= k-1; kk--)
									{
										solutionTmp += static_cast<ostringstream*>( &(ostringstream() << desNombre[kk]) )->str();
										if (kk < 4)
											solutionTmp += ")";
										if (kk > k-1)
											solutionTmp += operateurs[i][kk-1];
									}
									solutionTmp += ")";
								}
								stockageSolution(solutionTmp);
							}

							D = operation(operateurs[i][j+1], desNombre[2], A);
							E = operation(operateurs[i][j+2], D, B);
							if (verification33(E) == true)
							{
								solutionTmp = "";
								solutionTmp += "(";
								//Affichage Dé2
								solutionTmp += static_cast<ostringstream*>( &(ostringstream() << desNombre[2]) )->str();
								solutionTmp += operateurs[i][j+1];
								//Affichage A
								for (int ii = 0; ii <= j; ii++)
								solutionTmp += "(";

								for (int ii = 0; ii <= j+1; ii++)
								{
									solutionTmp += static_cast<ostringstream*>( &(ostringstream() << desNombre[ii]) )->str();
									if (ii > 0)
										solutionTmp += ")";
									if (ii <= j)
										solutionTmp += operateurs[i][ii];
								}
								///
								solutionTmp += operateurs[i][j+2];
								//Affichage B
								for (int kk = 4; kk > k; kk--)
								{
									solutionTmp += "(";
								}
								solutionTmp += static_cast<ostringstream*>( &(ostringstream() << desNombre[4]) )->str();
								for (int kk = 4; kk > k; kk--)
								{
									solutionTmp += operateurs[i][kk-1];
									solutionTmp += static_cast<ostringstream*>( &(ostringstream() << desNombre[kk-1]) )->str();
									solutionTmp += ")";
								}
								stockageSolution(solutionTmp);
							}
							if (operateurs[i][j+2] == '-' || operateurs[i][j+2] == '/')
							{
								E = operation(operateurs[i][j+2], B, D);
								if (verification33(E) == true)
								{
									solutionTmp = "";
									solutionTmp += "(";
									//Affichage B
									for (int kk = 4; kk > k; kk--)
									{
										solutionTmp += "(";
									}
									solutionTmp += static_cast<ostringstream*>( &(ostringstream() << desNombre[4]) )->str();
									for (int kk = 4; kk > k; kk--)
									{
										solutionTmp += operateurs[i][kk-1];
										solutionTmp += static_cast<ostringstream*>( &(ostringstream() << desNombre[kk-1]) )->str();
										solutionTmp += ")";
									}
									solutionTmp += operateurs[i][j+2];
									//Affichage Dé2
									solutionTmp += "(";
									solutionTmp += static_cast<ostringstream*>( &(ostringstream() << desNombre[2]) )->str();
									solutionTmp += operateurs[i][j+1];
									//Affichage A
									for (int ii = 0; ii <= j; ii++)
									solutionTmp += "(";

									for (int ii = 0; ii <= j+1; ii++)
									{
										solutionTmp += static_cast<ostringstream*>( &(ostringstream() << desNombre[ii]) )->str();
										if (ii > 0)
											solutionTmp += ")";
										if (ii <= j)
											solutionTmp += operateurs[i][ii];
									}
									stockageSolution(solutionTmp);
								}
							}
						}
					}
				}
			}
		} while (next_permutation(desNombre, desNombre+5));

		if (reponse == 's')
		{
			system("clear");
			cout << setprecision(7) << "Simulation " << n+1 << " sur " << nSimulations << " en cours" << endl;
			if (nSolutions > 0)
			{
				/* S'il y a au moins une solution, en mode simulation, on incrémente le
				compteur de simulations positives et on remet le compteur de solutions
				à zéro pour la simulation d'après */
				nSolutions = 0;
				nPositives++;

				for (int l = solutions.size()-1; l >= 0; l--)
					solutions.pop_back();

				if (nMathador > 0)
				{
					nMathador = 0;
					nSimulationsMathador++;
				}
			}
		}

		n++;	//On incrémente le compteur de simulations

	} while (n < nSimulations);


	temps_final = clock ();
	temps_cpu = (temps_final - temps_initial) / CLOCKS_PER_SEC * 1;

	if (reponse != 's')
	{
		affichageResultats();
		cout << "Il y a " << nSolutions << " solutions" << endl;
		cout << "Dont " << nMathador << " solutions Mathador" << endl;
	}

	if (reponse == 's')
	{
		cout << nSimulations << " simulations effectuées en " << temps_cpu << " secondes ("
		<< nSimulations/temps_cpu << " simulations/seconde)" << endl;
		cout << "Il y a eu " << nPositives << " simulations avec au moins une solution sur " << nSimulations
		<< " simulations (" << nPositives*100/nSimulations << " %)" << endl;

		cout << "Dont " << nSimulationsMathador << " simulations avec au moins une solution Mathador ("
		<< nSimulationsMathador*100/nPositives << " %)" << endl;
	}

	return 0;

}
