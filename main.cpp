/**
 ----------------------------------------
| Auteur : CLEMENT Pierre (INFO 25)      |
|                                        |
| Date : 28/02/2023                      |
|                                        |
| Utilité :                              |
| Le Programme permet de lire, filtrer   |
| et modifier des fichiers .csv          |
 ----------------------------------------
**/

#include <iostream>
#include <stdio.h>
#include <conio.h> //kbhit()
#include <string.h>
#include <cstring>
#include <stdlib.h>
#include <locale>
#include <codecvt>
#include <windows.h>

using namespace std;

#define LIGNE 500
#define COLONNE 6
#define LONG_LIGNE 100
#define VRAI 1
#define FAUX 0

int col_Num = 3, col_Nom = 20, col_CB = 19, col_Date = 10, col_Tel = 14, col_Ville = 25;

char Nom_fichier[] = "C:\\Users\\pierr\\Documents\\CodeBlocks\\CSV_Reader\\Data.csv"; // le chemin absolu vers mon fichier .csv


// Cette fonction permet de charger un fichier CSV puis le stocker dans un tableau à deux dimensions
int chargement_fichier(string arr[][COLONNE], int rows, int cols)
{

    FILE *fp = fopen(Nom_fichier, "r");
    char line[LONG_LIGNE];
    char *token;
    string mot;
    int i = 0, j = 0;

    if (fp == NULL)
    {
        printf("Impossible d'ouvrir le fichier %s\n", Nom_fichier);
        return 1;
    }
    cout << "chargement du fichier " << endl;
    fgets(line, LONG_LIGNE, fp);

    while (fgets(line, LONG_LIGNE, fp) != NULL) // lecture d'une ligne
    {
        token = strtok(line, ";"); // repĂŠrage du premier mot de la ligne avec le sÄĹ parateur ";"
        while (token != NULL)
        {
            mot.assign(token); // compatibilitĂŠ string (C++) avec C (tableau de caractĂ¨re)
            arr[i][j++] = mot;
            token = strtok(NULL, ";");
        }
        i++;
        j = 0;
    }
    fclose(fp);
}


// Permet de fix la derniere colonne
void modifier_la_derniere_colonne(string arr[][COLONNE], int rows)
{
    int i;
    string str;
    str = arr[rows][5];
    char tab[str.size() + 1]; // +1 pour le caractère nul '\0'
    strcpy(tab, str.c_str()); // conversion de la chaîne en tableau
    tab[str.size() - 1] = '\0';

    int taille = sizeof(tab) / sizeof(tab[0]); // détermine la taille du tableau
    string n_str(tab, tab + taille);           // conversion du tableau en chaîne de caractères

    arr[rows][5] = n_str;
}

/** Pas utilisé
void charge_tableau(string arr[][COLONNE], int rows, int cols)
{
    int i, j;
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            cout << "Saisir la valeur :";
            cin >> arr[i][j];
        }
    }
}
**/

// Retourne la place de la colonne pour l'affichage
int verif_place_colonne(int longueur, int long_col)
{
    return (long_col - longueur);
}

// Affiche le tableau dans la console
void affichage_tableau(string arr[][COLONNE], int rows, int cols)
{
    int i, j, len, place, Debut = 0, Fin = 20, Continuer = VRAI;
    char Choix;

    while (Continuer)
    {
        system("cls"); // Effacement de l'ecran
        cout << "+---+--------------------+-------------------+----------+--------------+-------------------------+" << endl;
        cout << "|Num|    Nom-Prenom      |       CB          |   Date   |     Tel      |           Ville         |" << endl;
        cout << "+---+--------------------+-------------------+----------+--------------+-------------------------+" << endl;
        for (i = Debut; i < Fin; i++)
        { // affichage de 20 lignes
            cout << "|";
            //-----------------numero d'ordre -----------------
            len = arr[i][0].length();
            place = verif_place_colonne(len, col_Num);
            for (j = 1; j <= place; j++)
                cout << " "; // affichage des espaces avant l'affichage
            cout << arr[i][0];
            cout << "|";
            //-----------------affichage nom prenom-----------------
            len = arr[i][1].length();
            place = verif_place_colonne(len, col_Nom);
            for (j = 1; j <= place; j++)
                cout << " ";
            cout << arr[i][1];
            cout << "|";
            //-----------------affichage CB-----------------
            len = arr[i][2].length();
            place = verif_place_colonne(len, col_CB);
            for (j = 1; j <= place; j++)
                cout << " ";
            cout << arr[i][2];
            cout << "|";
            //-----------------affichage Date-----------------
            len = arr[i][3].length();
            place = verif_place_colonne(len, col_Date);
            for (j = 1; j <= place; j++)
                cout << " ";
            cout << arr[i][3];
            cout << "|"; //-----------------affichage tel-----------------
            len = arr[i][4].length();
            place = verif_place_colonne(len, col_Tel);
            for (j = 1; j <= place; j++)
                cout << " ";
            cout << arr[i][4];
            cout << "|";
            //-----------------affichage Ville-----------------
            len = arr[i][5].length();
            place = verif_place_colonne(len, col_Ville);
            //       cout <<endl<<"longueur du mot = "<<len<<endl;
            //       cout <<"place mot = "<<place<<endl;
            //       break;
            for (j = 1; j <= place; j++)
                cout << " ";
            cout << arr[i][5];
            cout << "  |" << endl;

            cout << "+---+--------------------+-------------------+----------+--------------+-------------------------+" << endl;
        }
        cout << "A -> Page suivante  --- Z->Page precedente ---- Q -> Quitter    [Votre choix ] :";
        cin >> Choix;
        if (Choix == 'A' or Choix == 'a')
        {
            if ((Debut + 20) <= LIGNE - 20)
            {
                Debut += 20;
                Fin += 20;
            }
            if ((Fin + 20) > LIGNE)
            {
                Fin = LIGNE;
                Debut = LIGNE - 20;
            }
        }
        if (Choix == 'Z' or Choix == 'z')
        {
            if ((Debut - 20) < 0)
            {
                Debut = 0;
                Fin = 20;
            }
            else
            {
                Debut -= 20;
                Fin -= 20;
            }
        }
        if (Choix == 'Q' or Choix == 'q')
            Continuer = FAUX;
    }
}

// Permet de centrer l'affichage
void decale(int val)
{
    for (int i = 0; i < val; i++)
        cout << " ";
}

// Permet de sauter des lignes sur l'affichage
void passe_des_lignes(int val)
{
    for (int i = 0; i < val; i++)
        cout << "\n";
}

// Affiche le menu principal de l'utilitaire
void affiche_le_menu_principal()
{
    int x = 30;
    int y = 5;
    passe_des_lignes(y);
    decale(x);
    cout << "+-----------------------------------------------+\n";
    decale(x);
    cout << "|                                               |\n";
    decale(x);
    cout << "|   Gestion de Tableau : ITII 2023              |\n";
    decale(x);
    cout << "|                                               |\n";
    decale(x);
    cout << "+-----------------------------------------------+\n";
    decale(x);
    cout << "|                                               |\n";
    decale(x);
    cout << "|  1 - Charger le fichier                       |\n";
    decale(x);
    cout << "|                                               |\n";
    decale(x);
    cout << "|  2 - Afficher le contenu du fichier par Ecran |\n";
    decale(x);
    cout << "|                                               |\n";
    decale(x);
    cout << "|  3 - Rechercher une information               |\n";
    decale(x);
    cout << "|                                               |\n";
    decale(x);
    cout << "|  4 - Modifier une information                 |\n";
    decale(x);
    cout << "|                                               |\n";
    decale(x);
    cout << "|  5 - Trier le tableau                         |\n";
    decale(x);
    cout << "|                                               |\n";
    decale(x);
    cout << "|  6 - Quitter                                  |\n";
    decale(x);
    cout << "|                                               |\n";
    decale(x);
    cout << "+-----------------------------------------------+\n";
    decale(x);
    cout << "|                                               |\n";
    decale(x);
    cout << "|   Votre choix :                               |\n";
    decale(x);
    cout << "|                                               |\n";
    decale(x);
    cout << "+-----------------------------------------------+\n";
}

// Affiche chacune des colonnes utilisables, cette méthode est utilisé dans les méthodes de filtres, recherches et modifications
void affichage_colonne() {
    int x = 30;
    int y = 5;
    passe_des_lignes(y);
    decale(x);
    cout << "+-----------------------------------------------+\n";
    decale(x);
    cout << "|                                               |\n";
    decale(x);
    cout << "|   Choisissez une colonne :                    |\n";
    decale(x);
    cout << "|                                               |\n";
    decale(x);
    cout << "+-----------------------------------------------+\n";
    decale(x);
    cout << "|                                               |\n";
    decale(x);
    cout << "|  1 - Numero                                   |\n";
    decale(x);
    cout << "|                                               |\n";
    decale(x);
    cout << "|  2 - Nom                                      |\n";
    decale(x);
    cout << "|                                               |\n";
    decale(x);
    cout << "|  3 - CB                                       |\n";
    decale(x);
    cout << "|                                               |\n";
    decale(x);
    cout << "|  4 - Date                                     |\n";
    decale(x);
    cout << "|                                               |\n";
    decale(x);
    cout << "|  5 - Telephone                                |\n";
    decale(x);
    cout << "|                                               |\n";
    decale(x);
    cout << "|  6 - Ville                                    |\n";
    decale(x);
    cout << "|                                               |\n";
    decale(x);
    cout << "|  7 - Quitter                                  |\n";
    decale(x);
    cout << "|                                               |\n";
    decale(x);
    cout << "+-----------------------------------------------+\n";
    decale(x);
    cout << "|                                               |\n";
    decale(x);
    cout << "|   Votre choix :                               |\n";
    decale(x);
    cout << "|                                               |\n";
    decale(x);
    cout << "+-----------------------------------------------+\n";
}

// L'affichage permet de choisir entre les différentes méthodes de tris
void affichage_tri() {
    int x = 30;
    int y = 5;
    passe_des_lignes(y);
    decale(x);
    cout << "+-----------------------------------------------+\n";
    decale(x);
    cout << "|                                               |\n";
    decale(x);
    cout << "|   Choisissez une methode de tri :             |\n";
    decale(x);
    cout << "|                                               |\n";
    decale(x);
    cout << "+-----------------------------------------------+\n";
    decale(x);
    cout << "|                                               |\n";
    decale(x);
    cout << "|  1 - Tri a bulle                              |\n";
    decale(x);
    cout << "|                                               |\n";
    decale(x);
    cout << "|  2 - Tri par insertion (en maintenance)       |\n";
    decale(x);
    cout << "|                                               |\n";
    decale(x);
    cout << "|  3 - Quitter                                  |\n";
    decale(x);
    cout << "+-----------------------------------------------+\n";
    decale(x);
    cout << "|                                               |\n";
    decale(x);
    cout << "|   Votre choix :                               |\n";
    decale(x);
    cout << "|                                               |\n";
    decale(x);
    cout << "+-----------------------------------------------+\n";
}

// Méthode de tri à bulle pour des int (numéro)
void tri_a_bulle_id(string arr[][COLONNE]) {
    int n = LIGNE;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (stoi(arr[j][0]) > stoi(arr[j+1][0])) {
                string temp1 = arr[j][0];
                string temp2 = arr[j][1];
                string temp3 = arr[j][2];
                string temp4 = arr[j][3];
                string temp5 = arr[j][4];
                string temp6 = arr[j][5];

                arr[j][0] = arr[j+1][0];
                arr[j][1] = arr[j+1][1];
                arr[j][2] = arr[j+1][2];
                arr[j][3] = arr[j+1][3];
                arr[j][4] = arr[j+1][4];
                arr[j][5] = arr[j+1][5];

                arr[j+1][0] = temp1;
                arr[j+1][1] = temp2;
                arr[j+1][2] = temp3;
                arr[j+1][3] = temp4;
                arr[j+1][4] = temp5;
                arr[j+1][5] = temp6;
            }
        }
    }
}

// Méthode générale de tri à bulle
void tri_a_bulle(string arr[][COLONNE], int col) {
    int n = LIGNE;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j][col] > arr[j+1][col]) {
                string temp1 = arr[j][0];
                string temp2 = arr[j][1];
                string temp3 = arr[j][2];
                string temp4 = arr[j][3];
                string temp5 = arr[j][4];
                string temp6 = arr[j][5];

                arr[j][0] = arr[j+1][0];
                arr[j][1] = arr[j+1][1];
                arr[j][2] = arr[j+1][2];
                arr[j][3] = arr[j+1][3];
                arr[j][4] = arr[j+1][4];
                arr[j][5] = arr[j+1][5];

                arr[j+1][0] = temp1;
                arr[j+1][1] = temp2;
                arr[j+1][2] = temp3;
                arr[j+1][3] = temp4;
                arr[j+1][4] = temp5;
                arr[j+1][5] = temp6;
            }
        }
    }
}

// Tri par insertion (infonctionnel)
void tri_par_insertion(string arr[][COLONNE], int col) {
    int n = LIGNE;
    string temp1,temp2,temp3,temp4,temp5,temp6;

    for (int i = 1; i < n; i++) {
        temp1 = arr[i][0];
        temp2 = arr[i][1];
        temp3 = arr[i][2];
        temp4 = arr[i][3];
        temp5 = arr[i][4];
        temp6 = arr[i][5];
        int j = i - 1;
        while (j >= 0 && arr[j][col] > arr[i][col]) {
            arr[j + 1][0] = arr[j][0];
            arr[j + 1][1] = arr[j][1];
            arr[j + 1][2] = arr[j][2];
            arr[j + 1][3] = arr[j][3];
            arr[j + 1][4] = arr[j][4];
            arr[j + 1][5] = arr[j][5];
            j--;
        }
        arr[j + 1][0] = temp1;
        arr[j + 1][1] = temp2;
        arr[j + 1][2] = temp3;
        arr[j + 1][3] = temp4;
        arr[j + 1][4] = temp5;
        arr[j + 1][5] = temp6;
    }
}

// Méthode de filtre de l'application
int filtrer_tableau(string arr[][COLONNE], int rows, int cols)
{
    char Choix_tri, Choix_filtre;
    int tri, filtre;
    bool is_tri = true, is_filtre = true;

    while(is_tri) {
        is_tri = false;
        system("cls");
        affichage_tri();
        cin >> Choix_tri;
        switch (Choix_tri)
        {
            case '1':
                tri = 1;
                break;
            case '2':
                tri = 2;
                break;
            case '3':
                tri = -1;
                is_filtre = false;
                break;
            default:
                is_tri = true;
                cout << "Choix Invalide\n";
        }
    }

    while(is_filtre) {
        is_filtre = false;
        system("cls");
        affichage_colonne();
        cin >> Choix_filtre;
        switch (Choix_filtre)
        {
            case '1':
                filtre = 0;
                break;
            case '2':
                filtre = 1;
                break;
            case '3':
                filtre = 2;
                break;
            case '4':
                filtre = 3;
                break;
            case '5':
                filtre = 4;
                break;
            case '6':
                filtre = 5;
                break;
            case '7':
                filtre = -1;
                break;
            default:
                cout << "Choix Invalide\n";
        }
    }

    if (tri != -1 && filtre != -1) {
        system("cls");
        if (tri == 1 && filtre == 0) {
            tri_a_bulle_id(arr);
        }
        else if (tri == 1) {
            tri_a_bulle(arr, filtre);
        } else if (tri == 2) {
            tri_par_insertion(arr, filtre);
        }
        cout << "Le tableau a bien ete filtre !\n";
        cout << "Affichez le tableau a l'acceuil pour voir les changements !" << endl;
    }

    cout << "Taper sur une touche pour sortir ";
    while (!kbhit());
    return 0;
}

// Méthode de recherche de l'application
int recherche_tableau(string arr[][COLONNE], int rows, int cols)
{
    char Choix;
    bool on = true;
    string nom_de_la_recherche;
    int i, compteur = 0, x = 30, len, col;
    size_t found;

    while(on) {
        on = false;
        system("cls");
        affichage_colonne();
        cin >> Choix;
        switch (Choix)
        {
            case '1':
                col = 0;
                break;
            case '2':
                col = 1;
                break;
            case '3':
                col = 2;
                break;
            case '4':
                col = 3;
                break;
            case '5':
                col = 4;
                break;
            case '6':
                col = 5;
                break;
            case '7':
                col = -1;
                break;
            default:
                on = true;
                cout << "Choix Invalide\n";
        }
    }

    if (col != -1) {
        system("cls");
        decale(x);
        cout << "+-----------------------------------------------+\n";
        decale(x);
        cout << "|                                               |\n";
        decale(x);
        cout << "|  Recherche suivante :                         |\n";
        decale(x);
        cout << "|                                               |\n";
        decale(x);
        cout << "+-----------------------------------------------+\n";
        decale(x);
        cout << "|                                               |\n";
        decale(x);
        cout << "|  Entrez le nom : ";
        cin >> nom_de_la_recherche;
        decale(x);
        cout << "|                                               |\n";

        for (i = 0; i < LIGNE; i++)
        {
            found = arr[i][col].find(nom_de_la_recherche);
            if (found != std::string::npos)
                compteur++;
        }

        if (compteur < 10)
            len = 1;
        else
            len = 2;
        if (len == 2)
        {
            decale(x);
            cout << "|  Il y a : " << compteur;
        }
        else
        {
            decale(x);
            cout << "|  Il y a :  " << compteur;
        }
        cout << " solution(s)                      |\n";
        decale(x);
        cout << "|                                               |\n";
        decale(x);
        cout << "+-----------------------------------------------+\n";
        if (compteur > 0)
        {
            cout << "+---+--------------------+-------------------+----------+--------------+-------------------------+" << endl;
            cout << "|Num|    Nom-Prenom      |       CB          |   Date   |     Tel      |           Ville         |" << endl;
            cout << "+---+--------------------+-------------------+----------+--------------+-------------------------+" << endl;
            for (i = 0; i < LIGNE; i++)
            {
                found = arr[i][col].find(nom_de_la_recherche);
                int len, place, j;
                if (found != std::string::npos)
                {
                    cout << "|";
                    //-----------------numero d'ordre -----------------
                    len = arr[i][0].length();
                    place = verif_place_colonne(len, col_Num);
                    for (j = 1; j <= place; j++)
                        cout << " "; // affichage des espaces avant l'affichage
                    cout << arr[i][0];
                    cout << "|";
                    //-----------------affichage nom prenom-----------------
                    len = arr[i][1].length();
                    place = verif_place_colonne(len, col_Nom);
                    for (j = 1; j <= place; j++)
                        cout << " ";
                    cout << arr[i][1];
                    cout << "|";
                    //-----------------affichage CB-----------------
                    len = arr[i][2].length();
                    place = verif_place_colonne(len, col_CB);
                    for (j = 1; j <= place; j++)
                        cout << " ";
                    cout << arr[i][2];
                    cout << "|";
                    //-----------------affichage Date-----------------
                    len = arr[i][3].length();
                    place = verif_place_colonne(len, col_Date);
                    for (j = 1; j <= place; j++)
                        cout << " ";
                    cout << arr[i][3];
                    cout << "|"; //-----------------affichage tel-----------------
                    len = arr[i][4].length();
                    place = verif_place_colonne(len, col_Tel);
                    for (j = 1; j <= place; j++)
                        cout << " ";
                    cout << arr[i][4];
                    cout << "|";
                    //-----------------affichage Ville-----------------
                    len = arr[i][5].length();
                    place = verif_place_colonne(len, col_Ville);

                    for (j = 1; j <= place; j++)
                        cout << " ";
                    cout << arr[i][5];
                    cout << "  |" << endl;

                    cout << "+---+--------------------+-------------------+----------+--------------+-------------------------+" << endl;
                }
            }
        }
    }

    cout << "Taper sur une touche pour sortir ";
    while (!kbhit());
    return 0;
}

// Méthode de modification de l'application
int modifier_tableau(string arr[][COLONNE], int rows, int cols)
{
    char Choix;
    bool on = true;
    int numero_ligne, len, place, j, x = 30, col;
    string nouveau_nom;

    while(on) {
        on = false;
        system("cls");
        affichage_colonne();
        cin >> Choix;
        switch (Choix)
        {
            case '1':
                col = 0;
                break;
            case '2':
                col = 1;
                break;
            case '3':
                col = 2;
                break;
            case '4':
                col = 3;
                break;
            case '5':
                col = 4;
                break;
            case '6':
                col = 5;
                break;
            case '7':
                col = -1;
                break;
            default:
                on = true;
                cout << "Choix Invalide\n";
        }
    }

    if (col != -1) {
        system("cls");
        decale(x);
        cout << "+-----------------------------------------------+\n";
        decale(x);
        cout << "|                                               |\n";
        decale(x);
        cout << "|  Saisir la ligne a modifier :                 |\n";
        decale(x);
        cout << "|                                               |\n";
        decale(x);
        cout << "+-----------------------------------------------+\n";
        decale(x);
        cout << "|                                               |\n";
        decale(x);
        cout << "|  Entrez le numero de la ligne : ";

        cin >> numero_ligne;
        numero_ligne -= 1;

        decale(x);
        cout << "|                                               |\n";
        decale(x);
        cout << "|  La valeur est : ";
        cout << arr[numero_ligne][col] << "\n";
        decale(x);
        cout << "+-----------------------------------------------+\n";

        cout << "+---+--------------------+-------------------+----------+--------------+-------------------------+" << endl;
        cout << "|Num|    Nom-Prenom      |       CB          |   Date   |     Tel      |           Ville         |" << endl;
        cout << "+---+--------------------+-------------------+----------+--------------+-------------------------+" << endl;

        cout << "|";
        //-----------------numero d'ordre -----------------
        len = arr[numero_ligne][0].length();
        place = verif_place_colonne(len, col_Num);
        for (j = 1; j <= place; j++)
            cout << " "; // affichage des espaces avant l'affichage
        cout << arr[numero_ligne][0];
        cout << "|";
        //-----------------affichage nom prenom-----------------
        len = arr[numero_ligne][1].length();
        place = verif_place_colonne(len, col_Nom);
        for (j = 1; j <= place; j++)
            cout << " ";
        cout << arr[numero_ligne][1];
        cout << "|";
        //-----------------affichage CB-----------------
        len = arr[numero_ligne][2].length();
        place = verif_place_colonne(len, col_CB);
        for (j = 1; j <= place; j++)
            cout << " ";
        cout << arr[numero_ligne][2];
        cout << "|";
        //-----------------affichage Date-----------------
        len = arr[numero_ligne][3].length();
        place = verif_place_colonne(len, col_Date);
        for (j = 1; j <= place; j++)
            cout << " ";
        cout << arr[numero_ligne][3];
        cout << "|"; //-----------------affichage tel-----------------
        len = arr[numero_ligne][4].length();
        place = verif_place_colonne(len, col_Tel);
        for (j = 1; j <= place; j++)
            cout << " ";
        cout << arr[numero_ligne][4];
        cout << "|";
        //-----------------affichage Ville-----------------
        len = arr[numero_ligne][5].length();
        place = verif_place_colonne(len, col_Ville);
        //       cout <<endl<<"longueur du mot = "<<len<<endl;
        //       cout <<"place mot = "<<place<<endl;
        //       break;
        for (j = 1; j <= place; j++)
            cout << " ";
        cout << arr[numero_ligne][5];
        cout << "  |" << endl;

        cout << "+---+--------------------+-------------------+----------+--------------+-------------------------+" << endl;

        decale(x);
        cout << "+-----------------------------------------------+\n";
        decale(x);
        cout << "|                                               |\n";
        decale(x);
        cout << "|  Saisir le nouveau nom pour " << arr[numero_ligne][col] << " : \n";
        decale(x);
        cout << "|                                               |\n";
        decale(x);
        cout << "+-----------------------------------------------+\n";
        decale(x);
        cout << "|                                               |\n";
        decale(x);
        cout << "|  Entrez le nouveau nom : ";

        cin >> nouveau_nom;
        arr[numero_ligne][col] = nouveau_nom;

        decale(x);
        cout << "|                                               |\n";
        decale(x);
        cout << "|  La nouvelle valeur est : ";
        cout << arr[numero_ligne][col] << "\n";
        decale(x);
        cout << "+-----------------------------------------------+\n";

        cout << "+---+--------------------+-------------------+----------+--------------+-------------------------+" << endl;
        cout << "|Num|    Nom-Prenom      |       CB          |   Date   |     Tel      |           Ville         |" << endl;
        cout << "+---+--------------------+-------------------+----------+--------------+-------------------------+" << endl;

        cout << "|";
        //-----------------numero d'ordre -----------------
        len = arr[numero_ligne][0].length();
        place = verif_place_colonne(len, col_Num);
        for (j = 1; j <= place; j++)
            cout << " "; // affichage des espaces avant l'affichage
        cout << arr[numero_ligne][0];
        cout << "|";
        //-----------------affichage nom prenom-----------------
        len = arr[numero_ligne][1].length();
        place = verif_place_colonne(len, col_Nom);
        for (j = 1; j <= place; j++)
            cout << " ";
        cout << arr[numero_ligne][1];
        cout << "|";
        //-----------------affichage CB-----------------
        len = arr[numero_ligne][2].length();
        place = verif_place_colonne(len, col_CB);
        for (j = 1; j <= place; j++)
            cout << " ";
        cout << arr[numero_ligne][2];
        cout << "|";
        //-----------------affichage Date-----------------
        len = arr[numero_ligne][3].length();
        place = verif_place_colonne(len, col_Date);
        for (j = 1; j <= place; j++)
            cout << " ";
        cout << arr[numero_ligne][3];
        cout << "|"; //-----------------affichage tel-----------------
        len = arr[numero_ligne][4].length();
        place = verif_place_colonne(len, col_Tel);
        for (j = 1; j <= place; j++)
            cout << " ";
        cout << arr[numero_ligne][4];
        cout << "|";
        //-----------------affichage Ville-----------------
        len = arr[numero_ligne][5].length();
        place = verif_place_colonne(len, col_Ville);
        //       cout <<endl<<"longueur du mot = "<<len<<endl;
        //       cout <<"place mot = "<<place<<endl;
        //       break;
        for (j = 1; j <= place; j++)
            cout << " ";
        cout << arr[numero_ligne][5];
        cout << "  |" << endl;

        cout << "+---+--------------------+-------------------+----------+--------------+-------------------------+" << endl;

    }

    cout << "Taper sur une touche pour sortir ";
    while (!kbhit());
    return 0;
}

/*-----------------------------------------------------------------------------
                                 Programme principale
  -----------------------------------------------------------------------------*/
int main()
{
    // setlocale(LC_CTYPE, "fra");
    // setlocale(LC_ALL, "fr_FR.UTF-8");
    string Tableau[LIGNE][COLONNE];
    int continu_le_menu = VRAI, i;
    char Choix;
    while (continu_le_menu)
    {
        system("cls");
        affiche_le_menu_principal();
        cin >> Choix;
        switch (Choix)
        {
        case '1':
            chargement_fichier(Tableau, LIGNE, COLONNE);
            for (i = 0; i < LIGNE; i++)
                modifier_la_derniere_colonne(Tableau, i);
            while (!kbhit())
                ;

            break;
        case '2':
            affichage_tableau(Tableau, LIGNE, COLONNE);
            break;
        case '3':
            recherche_tableau(Tableau, LIGNE, COLONNE);
            break;
        case '4':
            modifier_tableau(Tableau, LIGNE, COLONNE);
            break;
        case '5':
            filtrer_tableau(Tableau, LIGNE, COLONNE);
            break;
        case '6':
            continu_le_menu = FAUX;
            break;
        default:
            cout << "Choix Invalide\n";
        } // switch
    }     // while
}
