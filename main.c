//
//  main.c
//  TP_Laby
//
//  Created by David Lamoot on 16/12/2022.
//

#include <stdlib.h>
#include "clientAPI.h"
#include <stdio.h>
#include "labyrinthAPI.h"

typedef struct{ //Structure décrivant une tuile
    int tileN;
    int tileE;
    int tileS;
    int tileW;
    int tileItem;
}t_tile;

typedef struct{ //Structure décrivant un joueur
    int pos[2];
    int item[2];
    int num_item;
}t_joueur;

typedef struct{ //Structure contenant les variables locale du projet
    int lab_local;
    t_move p_move;
} t_local;

void init_tile(t_tile* tile, t_move* move){
    tile->tileN = move->tileN;
    tile->tileS = move->tileS;
    tile->tileE = move->tileE;
    tile->tileW = move->tileW;
    tile->tileItem = move->tileItem;
}

//Fonction permettant de récupérer le labyrinthe de manière locale
void recupLaby(int x, int y, int* lab, t_tile* local){
    int i, j, k = 0;
    t_tile tuile;
    for(i = 0; i < x; i++){
        for(j = 0; j < y; j++){
            tuile.tileN = lab[5*k];
            tuile.tileE = lab [5 * k + 1];
            tuile.tileS = lab[5 * k + 2];
            tuile.tileW = lab[5 * k + 3];
            tuile.tileItem = lab[5 * k + 4];
            local[k] = tuile;
            k++;
        }
    }
}

//Fonction définissant la rotation d'une tuile dans le sens trigonométrique
void rotationTuile(t_tile* tile, int val_inter, int rotation){
    if (rotation == 1){ //rotation de 90°
        val_inter = tile->tileN;
        tile->tileN = tile->tileW;
        tile->tileW = tile->tileS;
        tile->tileS = tile->tileE;
        tile->tileE = val_inter;
    }
    else if (rotation == 2){ //rotation de 180°
        val_inter = tile->tileN;
        tile->tileN = tile->tileS;
        tile->tileS = val_inter;
        val_inter = tile->tileE;
        tile->tileE = tile->tileW;
        tile->tileW = val_inter;
    }
    else if (rotation == 3){ //rotation de 270°
        val_inter = tile->tileN;
        tile->tileN = tile->tileE;
        tile->tileE = tile->tileS;
        tile->tileS = tile->tileW;
        tile->tileW = val_inter;
    }
}

//Fonction permettant d'introduire une tuile dans le labyrinthe
void insertionTuile(t_tile* tab_tile, t_tile* tile, t_insertion insert, int nombre, int x, int y){
    //insertion à gauche
    if (insert == 0){
        for(int i = x-2; i >= 0; i--){ //décalage de la ligne vers la droite
            tab_tile[i + nombre * x].tileN = tab_tile[i + 1 + nombre * x].tileN;
            tab_tile[i + nombre * x].tileS = tab_tile[i + 1 + nombre * x].tileS;
            tab_tile[i + nombre * x].tileE = tab_tile[i + 1 + nombre * x].tileE;
            tab_tile[i + nombre * x].tileW = tab_tile[i + 1 + nombre * x].tileW;
        }
        tab_tile[nombre * x].tileN = tile->tileN; //ajout de la tuile à gauche
        tab_tile[nombre * x].tileS = tile->tileS;
        tab_tile[nombre * x].tileE = tile->tileE;
        tab_tile[nombre * x].tileW = tile->tileW;

    }
    //insertion à droite
    else if (insert == 1){
        for(int i = 1; i < x; i++){ //décalage de la ligne vers la gauche
            tab_tile[i + nombre * x].tileN = tab_tile[i - 1 + nombre * x].tileN;
            tab_tile[i + nombre * x].tileS = tab_tile[i - 1 + nombre * x].tileS;
            tab_tile[i + nombre * x].tileE = tab_tile[i - 1 + nombre * x].tileE;
            tab_tile[i + nombre * x].tileW = tab_tile[i - 1 + nombre * x].tileW;
        }
        tab_tile[x - 1 + nombre * x].tileN = tile->tileN; //ajout de la tuile à droite
        tab_tile[x - 1 + nombre * x].tileS = tile->tileS;
        tab_tile[x - 1 + nombre * x].tileE = tile->tileE;
        tab_tile[x - 1 + nombre * x].tileW = tile->tileW;

    }
    //insertion en haut
    else if (insert == 2){
        for(int i = y-2; i >= 0; i--){ //décalage de la colonne vers le bas
            tab_tile[nombre + i * x].tileN = tab_tile[nombre + (i + 1) * x].tileN;
            tab_tile[nombre + i * x].tileS = tab_tile[nombre + (i + 1) * x].tileS;
            tab_tile[nombre + i * x].tileE = tab_tile[nombre + (i + 1) * x].tileE;
            tab_tile[nombre + i * x].tileW = tab_tile[nombre + (i + 1) * x].tileW;
        }
        tab_tile[nombre].tileN = tile->tileN; //ajout de la tuile en haut
        tab_tile[nombre].tileS = tile->tileS;
        tab_tile[nombre].tileE = tile->tileE;
        tab_tile[nombre].tileW = tile->tileW;

    }
    //insertion en bas
    else if (insert == 3){
        for(int i = 1; i < y; i++){ //décalage de la colonne vers le haut
            tab_tile[nombre + i * x].tileN = tab_tile[nombre + (i - 1) * x].tileN;
            tab_tile[nombre + i * x].tileS = tab_tile[nombre + (i - 1) * x].tileS;
            tab_tile[nombre + i * x].tileE = tab_tile[nombre + (i - 1) * x].tileE;
            tab_tile[nombre + i * x].tileW = tab_tile[nombre + (i - 1) * x].tileW;
        }
        tab_tile[nombre + (y - 1)* x].tileN = tile->tileN; //ajout de la tuile en haut
        tab_tile[nombre + (y - 1)* x].tileS = tile->tileS;
        tab_tile[nombre + (y - 1)* x].tileE = tile->tileE;
        tab_tile[nombre + (y - 1)* x].tileW = tile->tileW;
    }
}

//Fonction permettant d'explorer le labyrinthe
void expansion(int x, int y, t_tile tab[x][y], int depart[2], int arrivee[2]){
    int d = 1;
    int chemin = 0;
    while (tab[arrivee[0]][arrivee[1]].tileItem == 0) {
        for (int i = 0; i < x; i++) {
            for (int j = 0; j < y; j++) {
                if ((i == depart[0] && (j == depart[1]))){
                    continue;
                }
                if ((tab[i-1][j].tileItem == d) && (tab[i][j].tileItem == 0) && (tab[i-1][j].tileS == 0) && (tab[i][j].tileN == 0)){
                    tab[i][j].tileItem = d + 1;
                    chemin++;
                }
                if ((tab[i-1][j].tileItem == d) && (tab[i][j].tileItem == 0) && (tab[i][j-1].tileE == 0) && (tab[i][j].tileW == 0)){
                    tab[i][j].tileItem = d + 1;
                    chemin++;
                }
                if ((tab[i-1][j].tileItem == d) && (tab[i][j].tileItem == 0) && (tab[i][j+1].tileW == 0) && (tab[i][j].tileE == 0)){
                    tab[i][j].tileItem = d + 1;
                    chemin++;
                }
                if ((tab[i-1][j].tileItem == d) && (tab[i][j].tileItem == 0) && (tab[i+1][j].tileN == 0) && (tab[i][j].tileS == 0)){
                    tab[i][j].tileItem = d + 1;
                    chemin++;
                }
            }
        }
        if (chemin != 0){
            d++;
        }
    }
}

//Fonction indiquant les fonctionnalités au joueur
void Commandes(void){
    printf("INSERTION_GAUCHE = 0, INSERTION_DROITE = 1, INSERTION_HAUT = 2, INSERTION_BAS = 3\n");
    printf("Number : numero de ligne ou colonne\n");
    printf("Rotation : compris entre 0 et 3\n");
    printf("x , y : position où aller\n");
}

//Fonction permettant au joueur de jouer localement
void jouer(t_move *p_move){
    int insert;
    int number;
    int rotation;
    int x;
    int y;
    printf("Type d'insertion\n");
    scanf("%d", &insert);
    printf("Numéro de ligne ou de colonne\n");
    scanf("%d",&number);
    printf("Rotation de la piece\n");
    scanf("%d",&rotation);
    printf("Coorodonée en x\n");
    scanf("%d", &x);
    printf("Coordonnée en y\n");
    scanf("%d", &y);
    p_move->insert = insert;
    p_move->number = number;
    p_move->rotation = rotation;
    p_move->x = x;
    p_move->y = y;
}

int main(void) {
    int taille_X, taille_Y;
    char name[50];
    t_tile tile;
    t_move* p_move_j0 = malloc(sizeof(t_move));
    t_move* p_move_j1 = malloc(sizeof(t_move));
    int Partie_en_cours = 1; //Passe à 0 lorsque la partie est fini
    connectToServer("172.105.76.204", 5678, "test");
    waitForLabyrinth("TRAINING BASIC timeout=1000", name, &taille_X, &taille_Y);
    int *lab = malloc(5*taille_X*taille_Y*sizeof(int));
    int num_joueur = getLabyrinth(lab, &tile.tileN, &tile.tileE, &tile.tileS, &tile.tileW, &tile.tileItem);
    while(Partie_en_cours == 1){
        printLabyrinth();
        Commandes();
        jouer(p_move_j0);
        free(p_move_j0);
        free(p_move_j1);
    }
    closeConnection();
    return 0;
}
