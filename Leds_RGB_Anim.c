
#include "main.h"

uint8_t state_RGB = 44;
uint8_t RGB_En = 1;
uint32_t timer_RGB = 0;

// les buffers sont crees dans le fichier Leds_RGB
// mais on va jouer avec ici
extern uint32_t Right_Strip_GRB_Pix[RGB_STRIP_LENGTH];
extern uint32_t Left_Strip_GRB_Pix[RGB_STRIP_LENGTH];

extern uint32_t Matrix_RGB_Pix[RGB_MATRIX_H][RGB_MATRIX_L];
// matrice :   (TBC)
//  - ligne 0 en haut, 7 en bas
//  - colonne 0 a gauche, 31 a droite


uint32_t RGB_Gen_Timer = 0;
int State_Led = 1;
int cpt = 0;
uint32_t Matrix_Arrow[RGB_MATRIX_H][9] = { {0} };
uint32_t Matrix_Copy[RGB_MATRIX_H][RGB_MATRIX_L] = { {0} };




// TODO : faire des anims sympa

uint32_t Couleur32(uint8_t green,uint8_t red, uint8_t blue) 
{
    uint32_t couleur_finale = 0x0;
    couleur_finale = couleur_finale + green;
    couleur_finale =  couleur_finale << 8 ;
    couleur_finale = couleur_finale + red;
    couleur_finale =  couleur_finale << 8 ;
    couleur_finale = couleur_finale + blue;
    return couleur_finale; 
}

void Afficher_Chiffres(uint8_t chiffre,  uint32_t couleur, uint16_t colonne) // colonne = extremité gauche du chiffre
{
    if (chiffre == 0) {
        for (int i = 0; i < RGB_MATRIX_H ;i++)
        {
        Matrix_RGB_Pix[i][colonne] = couleur;
        Matrix_RGB_Pix[i][colonne+1] = Couleur32(0,0,0);
         Matrix_RGB_Pix[i][colonne+2] = Couleur32(0,0,0);
        Matrix_RGB_Pix[i][colonne + 3] = Couleur32(0,0,0);
        Matrix_RGB_Pix[i][colonne + 4] = couleur;

        }
        Matrix_RGB_Pix[0][colonne] = Couleur32(0,0,0);
        Matrix_RGB_Pix[7][colonne] = Couleur32(0,0,0);
        Matrix_RGB_Pix[0][colonne + 1] = couleur;
        Matrix_RGB_Pix[7][colonne + 1] = couleur;
        Matrix_RGB_Pix[0][colonne + 2] = couleur;
        Matrix_RGB_Pix[7][colonne + 2] = couleur;
        Matrix_RGB_Pix[0][colonne + 3] = couleur;
        Matrix_RGB_Pix[7][colonne + 3] = couleur;
        Matrix_RGB_Pix[0][colonne + 4] = Couleur32(0,0,0);
        Matrix_RGB_Pix[7][colonne + 4] = Couleur32(0,0,0);

    }
    if (chiffre == 1) { 
        for (int i = 0; i < RGB_MATRIX_H ;i++) 
        {
        Matrix_RGB_Pix[i][colonne+3] = couleur;
        Matrix_RGB_Pix[i][colonne+2] = Couleur32(0,0,0);
        Matrix_RGB_Pix[i][colonne+1] = Couleur32(0,0,0);
        Matrix_RGB_Pix[i][colonne] = Couleur32(0,0,0);
        }
        Matrix_RGB_Pix[3][colonne] = couleur;
        Matrix_RGB_Pix[2][colonne + 1] = couleur;
        Matrix_RGB_Pix[1][colonne + 2] = couleur;
        
    }
    if (chiffre == 2) {
        for (int i =0; i < RGB_MATRIX_H ;i++){
        Matrix_RGB_Pix[i][colonne] = couleur;
        Matrix_RGB_Pix[i][colonne+1] = Couleur32(0,0,0);
        Matrix_RGB_Pix[i][colonne + 2] = Couleur32(0,0,0);
        Matrix_RGB_Pix[i][colonne + 3] = Couleur32(0,0,0);
        Matrix_RGB_Pix[i][colonne + 4] = Couleur32(0,0,0);
        }
        Matrix_RGB_Pix[1][colonne] = Couleur32(0,0,0);
        Matrix_RGB_Pix[2][colonne] = Couleur32(0,0,0);
        Matrix_RGB_Pix[7][colonne] = Couleur32(0,0,0);
        Matrix_RGB_Pix[0][colonne+1] = couleur;
        Matrix_RGB_Pix[3][colonne+1] = couleur;
        Matrix_RGB_Pix[7][colonne+1] = couleur;
        Matrix_RGB_Pix[0][colonne+2] = couleur;
        Matrix_RGB_Pix[3][colonne+2] = couleur;
        Matrix_RGB_Pix[7][colonne+2] = couleur;
        Matrix_RGB_Pix[0][colonne+3] = couleur;
        Matrix_RGB_Pix[3][colonne+3] = couleur;
        Matrix_RGB_Pix[7][colonne+3] = couleur;
        Matrix_RGB_Pix[2][colonne+4] = couleur;
        Matrix_RGB_Pix[1][colonne+4] = couleur;
        Matrix_RGB_Pix[3][colonne+4] = couleur;
        Matrix_RGB_Pix[7][colonne+4] = couleur;

    }
    if (chiffre == 3) {
        for (int i =0; i < RGB_MATRIX_H ;i++){
        Matrix_RGB_Pix[i][colonne] = Couleur32(0,0,0);
        Matrix_RGB_Pix[i][colonne+1] = Couleur32(0,0,0);
        Matrix_RGB_Pix[i][colonne + 2] = Couleur32(0,0,0);
        Matrix_RGB_Pix[i][colonne + 3] = Couleur32(0,0,0);
        Matrix_RGB_Pix[i][colonne + 4] = couleur;
        }
        Matrix_RGB_Pix[0][colonne] = couleur;
        Matrix_RGB_Pix[3][colonne] = couleur;
        Matrix_RGB_Pix[7][colonne] = couleur;

        Matrix_RGB_Pix[0][colonne + 1] = couleur;
        Matrix_RGB_Pix[3][colonne + 1] = couleur;
        Matrix_RGB_Pix[7][colonne + 1] = couleur;


        Matrix_RGB_Pix[0][colonne + 2] = couleur;
        Matrix_RGB_Pix[3][colonne + 2] = couleur;
        Matrix_RGB_Pix[7][colonne + 2] = couleur;

        Matrix_RGB_Pix[0][colonne + 3] = couleur;
        Matrix_RGB_Pix[3][colonne + 3] = couleur;
        Matrix_RGB_Pix[7][colonne + 3] = couleur;

        Matrix_RGB_Pix[0][colonne + 4] =  Couleur32(0,0,0);
        Matrix_RGB_Pix[3][colonne + 4] =  Couleur32(0,0,0);
        Matrix_RGB_Pix[7][colonne + 4] =  Couleur32(0,0,0);
    }
    if (chiffre == 4) {
         for (int i =0; i < RGB_MATRIX_H ;i++){
        Matrix_RGB_Pix[i][colonne] = couleur;
        Matrix_RGB_Pix[i][colonne+1] = Couleur32(0,0,0);
        Matrix_RGB_Pix[i][colonne + 2] = Couleur32(0,0,0);
        Matrix_RGB_Pix[i][colonne + 3] = Couleur32(0,0,0);
        Matrix_RGB_Pix[i][colonne + 4] = couleur;
        }
        Matrix_RGB_Pix[6][colonne] = Couleur32(0,0,0);
        Matrix_RGB_Pix[5][colonne] = Couleur32(0,0,0);
        Matrix_RGB_Pix[7][colonne] = Couleur32(0,0,0);
        Matrix_RGB_Pix[4][colonne] = Couleur32(0,0,0);

        Matrix_RGB_Pix[3][colonne+1] = couleur;
        Matrix_RGB_Pix[3][colonne+2] = couleur;
        Matrix_RGB_Pix[3][colonne+3] = couleur;


    }
    if (chiffre == 5) {
         for (int i =0; i < RGB_MATRIX_H ;i++){
        Matrix_RGB_Pix[i][colonne + 4] = couleur;
        Matrix_RGB_Pix[i][colonne+1] = Couleur32(0,0,0);
        Matrix_RGB_Pix[i][colonne + 2] = Couleur32(0,0,0);
        Matrix_RGB_Pix[i][colonne + 3] = Couleur32(0,0,0);
        Matrix_RGB_Pix[i][colonne] = Couleur32(0,0,0);
        }
        Matrix_RGB_Pix[1][colonne] = couleur;
        Matrix_RGB_Pix[2][colonne] = couleur;
        Matrix_RGB_Pix[3][colonne] = couleur;
        Matrix_RGB_Pix[7][colonne] = couleur;

        Matrix_RGB_Pix[0][colonne+1] = couleur;
        Matrix_RGB_Pix[3][colonne+1] = couleur;
        Matrix_RGB_Pix[7][colonne+1] = couleur;

        Matrix_RGB_Pix[0][colonne+2] = couleur;
        Matrix_RGB_Pix[3][colonne+2] = couleur;
        Matrix_RGB_Pix[7][colonne+2] = couleur;

        Matrix_RGB_Pix[0][colonne+3] = couleur;
        Matrix_RGB_Pix[3][colonne+3] = couleur;
        Matrix_RGB_Pix[7][colonne+3] = couleur;

        Matrix_RGB_Pix[2][colonne+4] = Couleur32(0,0,0);
        Matrix_RGB_Pix[1][colonne+4] = Couleur32(0,0,0);
        Matrix_RGB_Pix[7][colonne+4] = Couleur32(0,0,0);
    }
    if (chiffre == 6) {
        for (int i =0; i < RGB_MATRIX_H ;i++){
        Matrix_RGB_Pix[i][colonne] = couleur;
        Matrix_RGB_Pix[i][colonne+1] = couleur;
        Matrix_RGB_Pix[i][colonne + 2] = couleur;
        Matrix_RGB_Pix[i][colonne + 3] = couleur;
        }
        Matrix_RGB_Pix[0][colonne] = Couleur32(0,0,0);
        Matrix_RGB_Pix[7][colonne] = Couleur32(0,0,0);

        Matrix_RGB_Pix[1][colonne+1] = Couleur32(0,0,0);
        Matrix_RGB_Pix[2][colonne+1] = Couleur32(0,0,0);
        Matrix_RGB_Pix[4][colonne+1] = Couleur32(0,0,0);
        Matrix_RGB_Pix[5][colonne+1] = Couleur32(0,0,0);
        Matrix_RGB_Pix[6][colonne+1] = Couleur32(0,0,0);

        Matrix_RGB_Pix[1][colonne+2] = Couleur32(0,0,0);
        Matrix_RGB_Pix[2][colonne+2] = Couleur32(0,0,0);
        Matrix_RGB_Pix[4][colonne+2] = Couleur32(0,0,0);
        Matrix_RGB_Pix[5][colonne+2] = Couleur32(0,0,0);
        Matrix_RGB_Pix[6][colonne+2] = Couleur32(0,0,0);

       

        Matrix_RGB_Pix[1][colonne+3] = Couleur32(0,0,0);
        Matrix_RGB_Pix[2][colonne+3] = Couleur32(0,0,0);
        Matrix_RGB_Pix[3][colonne+3] = Couleur32(0,0,0);
        Matrix_RGB_Pix[7][colonne+3] = Couleur32(0,0,0);

    

    }
    if (chiffre == 7) {
        for (int i =0; i < RGB_MATRIX_H ;i++){
        Matrix_RGB_Pix[i][colonne] = Couleur32(0,0,0);
        Matrix_RGB_Pix[i][colonne+1] = Couleur32(0,0,0);
        Matrix_RGB_Pix[i][colonne + 2] = Couleur32(0,0,0);
        Matrix_RGB_Pix[i][colonne + 3] = Couleur32(0,0,0);
        Matrix_RGB_Pix[i][colonne + 4] = couleur;
        }
        Matrix_RGB_Pix[0][colonne] = couleur;
        Matrix_RGB_Pix[0][colonne + 1] = couleur;
        Matrix_RGB_Pix[4][colonne + 1] = couleur;
        Matrix_RGB_Pix[0][colonne + 2] = couleur;
        Matrix_RGB_Pix[4][colonne + 2] = couleur;
        Matrix_RGB_Pix[0][colonne + 3] =  couleur;
        Matrix_RGB_Pix[4][colonne + 3] =  couleur;
    }
    if (chiffre == 8) {
         for (int i = 0; i < RGB_MATRIX_H ;i++)
        {
        Matrix_RGB_Pix[i][colonne] = couleur;
        Matrix_RGB_Pix[i][colonne+1] = Couleur32(0,0,0);
        Matrix_RGB_Pix[i][colonne+2] = Couleur32(0,0,0);
        Matrix_RGB_Pix[i][colonne + 3] = Couleur32(0,0,0);
        Matrix_RGB_Pix[i][colonne + 4] = couleur;

        }
        Matrix_RGB_Pix[0][colonne] = Couleur32(0,0,0);
        Matrix_RGB_Pix[3][colonne] = Couleur32(0,0,0);
        Matrix_RGB_Pix[7][colonne] = Couleur32(0,0,0);

        Matrix_RGB_Pix[0][colonne + 1] = couleur;
        Matrix_RGB_Pix[3][colonne + 1] = couleur;
        Matrix_RGB_Pix[7][colonne + 1] = couleur;

        Matrix_RGB_Pix[0][colonne + 2] = couleur;
        Matrix_RGB_Pix[3][colonne + 2] = couleur;
        Matrix_RGB_Pix[7][colonne + 2] = couleur;

        Matrix_RGB_Pix[0][colonne + 3] = couleur;
        Matrix_RGB_Pix[3][colonne + 3] = couleur;
        Matrix_RGB_Pix[7][colonne + 3] = couleur;

        Matrix_RGB_Pix[0][colonne + 4] = Couleur32(0,0,0);
        Matrix_RGB_Pix[3][colonne + 4] = Couleur32(0,0,0);
        Matrix_RGB_Pix[7][colonne + 4] = Couleur32(0,0,0);
    }
    if (chiffre == 9) {
        for (int i =0; i < RGB_MATRIX_H ;i++){
        Matrix_RGB_Pix[i][colonne] = Couleur32(0,0,0);
        Matrix_RGB_Pix[i][colonne+1] = Couleur32(0,0,0);
        Matrix_RGB_Pix[i][colonne + 2] = Couleur32(0,0,0);
        Matrix_RGB_Pix[i][colonne + 3] = Couleur32(0,0,0);
        Matrix_RGB_Pix[i][colonne + 4] = couleur;
        }

        Matrix_RGB_Pix[1][colonne] = couleur;
        Matrix_RGB_Pix[2][colonne] = couleur;
        Matrix_RGB_Pix[3][colonne] = couleur;
        Matrix_RGB_Pix[7][colonne] = couleur;

        Matrix_RGB_Pix[0][colonne + 1] = couleur;
        Matrix_RGB_Pix[4][colonne + 1] = couleur;
        Matrix_RGB_Pix[7][colonne + 1] = couleur;

        Matrix_RGB_Pix[0][colonne + 2] = couleur;
        Matrix_RGB_Pix[4][colonne + 2] = couleur;
        Matrix_RGB_Pix[7][colonne + 2] = couleur;

        Matrix_RGB_Pix[0][colonne + 3] = couleur;
        Matrix_RGB_Pix[4][colonne + 3] = couleur;
        Matrix_RGB_Pix[7][colonne + 3] = couleur;

        Matrix_RGB_Pix[7][colonne + 4] = Couleur32(0,0,0);
        Matrix_RGB_Pix[0][colonne + 4] = Couleur32(0,0,0);

        
    }
    
}

void Afficher_super_7(uint32_t couleur, uint16_t colonne)
{
    Matrix_RGB_Pix[1][colonne] = couleur;

    Matrix_RGB_Pix[1][colonne+1] = couleur;
    Matrix_RGB_Pix[5][colonne+1] = couleur;
    Matrix_RGB_Pix[6][colonne+1] = couleur;
    Matrix_RGB_Pix[7][colonne+1] = couleur;

    Matrix_RGB_Pix[1][colonne+2] = couleur;
    Matrix_RGB_Pix[4][colonne+2] = couleur;

    Matrix_RGB_Pix[1][colonne+3] = couleur;
    Matrix_RGB_Pix[2][colonne+3] = couleur;
    Matrix_RGB_Pix[3][colonne+3] = couleur;


    
}

void Afficher_Lettres(char lettre, uint32_t couleur, uint16_t colonne)

{
    if ( lettre == 'R'){
            for (int i = 1 ; i< RGB_MATRIX_H ; i ++) {
                Matrix_RGB_Pix[i][colonne] = couleur;
            }
            Matrix_RGB_Pix[1][colonne+1] = couleur;
            Matrix_RGB_Pix[4][colonne+1] = couleur;
            Matrix_RGB_Pix[5][colonne+1] = couleur;

            Matrix_RGB_Pix[1][colonne+2] = couleur;
            Matrix_RGB_Pix[4][colonne+2] = couleur;
            Matrix_RGB_Pix[6][colonne+2] = couleur;

            Matrix_RGB_Pix[2][colonne+3] = couleur;
            Matrix_RGB_Pix[3][colonne+3] = couleur;
            Matrix_RGB_Pix[7][colonne+3] = couleur;

           
           
         }
    
    else if ( lettre == 'O'){ // le O est placé dans 4 colonnes au lieu de 3 !
            for (int i = 2 ; i< 7 ; i ++) {
                Matrix_RGB_Pix[i][colonne] = couleur;
                Matrix_RGB_Pix[i][colonne + 4] = couleur;
            }
            
            Matrix_RGB_Pix[1][colonne+1] = couleur;
            Matrix_RGB_Pix[7][colonne+1] = couleur;

            Matrix_RGB_Pix[1][colonne+2] = couleur;
            Matrix_RGB_Pix[7][colonne+2] = couleur;

            Matrix_RGB_Pix[1][colonne+3] = couleur;
            Matrix_RGB_Pix[7][colonne+3] = couleur;

        }
    else if ( lettre == 'G'){ 
            for (int i = 2 ; i< 7 ; i ++) {
                Matrix_RGB_Pix[i][colonne] = couleur;
            }
            
            Matrix_RGB_Pix[1][colonne+1] = couleur;
            Matrix_RGB_Pix[7][colonne+1] = couleur;

            Matrix_RGB_Pix[1][colonne+2] = couleur;
            Matrix_RGB_Pix[4][colonne+2] = couleur;
            Matrix_RGB_Pix[7][colonne+2] = couleur;

            Matrix_RGB_Pix[1][colonne+3] = couleur;
            Matrix_RGB_Pix[4][colonne+3] = couleur;
            Matrix_RGB_Pix[7][colonne+3] = couleur;

            Matrix_RGB_Pix[1][colonne+4] = couleur;
            Matrix_RGB_Pix[4][colonne+4] = couleur;
            Matrix_RGB_Pix[5][colonne+4] = couleur;
            Matrix_RGB_Pix[6][colonne+4] = couleur;


        }
    else if ( lettre == 'T'){ 
            for (int i = 1 ; i< 8 ; i ++) {
                Matrix_RGB_Pix[i][colonne] = couleur;
            }
            Matrix_RGB_Pix[1][colonne - 1] = couleur;
            Matrix_RGB_Pix[1][colonne+1] = couleur;
        }
    
    else if ( lettre == 'B'){ 
            for (int i = 1 ; i< 8 ; i ++) {
                Matrix_RGB_Pix[i][colonne] = couleur;
            }

            Matrix_RGB_Pix[1][colonne + 1] = couleur;
            Matrix_RGB_Pix[4][colonne+1] = couleur;
            Matrix_RGB_Pix[7][colonne+1] = couleur;

            Matrix_RGB_Pix[1][colonne + 2] = couleur;
            Matrix_RGB_Pix[4][colonne+2] = couleur;
            Matrix_RGB_Pix[7][colonne+2] = couleur;

            Matrix_RGB_Pix[3][colonne+3] = couleur;
            Matrix_RGB_Pix[2][colonne+3] = couleur;
            Matrix_RGB_Pix[5][colonne+3] = couleur;
            Matrix_RGB_Pix[6][colonne+3] = couleur;

        }
}

void Motif_Fleche_Gauche(uint8_t colonne, uint32_t couleur)
{

        Matrix_Arrow[3][colonne] = couleur;
        Matrix_Arrow[2][colonne+1] = couleur;
        Matrix_Arrow[1][colonne + 2] = couleur;
        Matrix_Arrow[0][colonne + 3] = couleur;

        Matrix_Arrow[3][colonne+1] = couleur;
        Matrix_Arrow[2][colonne+2] = couleur;
        Matrix_Arrow[1][colonne + 3] = couleur;
        Matrix_Arrow[0][colonne + 4] = couleur;


        Matrix_Arrow[4][colonne] = couleur;
        Matrix_Arrow[5][colonne +1] = couleur;
        Matrix_Arrow[6][colonne +2] = couleur;
        Matrix_Arrow[7][colonne +3] = couleur;

        Matrix_Arrow[4][colonne +1] = couleur;
        Matrix_Arrow[5][colonne +2] = couleur;
        Matrix_Arrow[6][colonne +3] = couleur;
        Matrix_Arrow[7][colonne +4] = couleur;
       
}

void Pluie_Modif(int intensite) // L'intensité est un entier

{
    for (int col = 0 ; col < RGB_MATRIX_L; col++)
    {  
        for (int line = RGB_MATRIX_H-1; line > 0; line --){
            Matrix_RGB_Pix[line][col] = Matrix_RGB_Pix[line-1][col];
        }
    }

    for (int col = 0 ;  col < RGB_MATRIX_L; col++)
    {  
            Matrix_RGB_Pix[0][col] = Couleur32(0,0,0);
    }

    for (int i = 0; i< intensite ; i++){
        Matrix_RGB_Pix[0][rand() % RGB_MATRIX_L] = Couleur32(rand()%50,rand()%20,rand()%10);
        Matrix_RGB_Pix[0][rand() % RGB_MATRIX_L] = Couleur32(rand()%20,rand()%50,rand()%10);
        Matrix_RGB_Pix[0][rand() % RGB_MATRIX_L] = Couleur32(rand()%10,rand()%50,rand()%20);
    }

}

void Pluie(int intensite, int sol) // L'intensité est un entier

{
    for (int col = 0 ; col < RGB_MATRIX_L; col++)
    {   Matrix_RGB_Pix[sol][col] = Couleur32(0,0,0);
        for (int line = sol; line>0; line --){
            Matrix_RGB_Pix[line ][col] = Matrix_RGB_Pix[line-1][col];
        }
    }
    for (int col = 0 ;  col < RGB_MATRIX_L; col++)
    {  
            Matrix_RGB_Pix[0][col] = Couleur32(0,0,0);
    }

    for (int i = 0; i< intensite ; i++){
        Matrix_RGB_Pix[0][rand() % RGB_MATRIX_L] = Couleur32(5,5,30);
        Matrix_RGB_Pix[0][rand() % RGB_MATRIX_L] = Couleur32(5,5,30);
    }
    

}


void Cadran_1(uint32_t couleur1, uint32_t couleur2)
{
    //Couleur_Bords(couleur>>16,couleur>>8,couleur);
    Motif_Fleche_Gauche(0, couleur1);
    Motif_Fleche_Gauche(4, couleur2);
}

void Clear_Matrix_Number_Area(void)
{
    for (int line = 0 ; line < RGB_MATRIX_H ; line++){
        for (int col = 9 ; col < (RGB_MATRIX_L-9) ; col++) { 
                Matrix_RGB_Pix[line][col] =  0;
            }              
    }    
}

void Draw_Number(uint8_t Nombre, uint32_t Couleur) {
    Clear_Matrix_Number_Area();
    if (Nombre < 10) {
        Afficher_Chiffres(Nombre,Couleur,14);
    } else if (Nombre < 100) {
        Afficher_Chiffres(Nombre/10,Couleur,11);
        Afficher_Chiffres(Nombre%10,Couleur,17);
    } else {
        Afficher_Chiffres(1,Couleur,9);
        Afficher_Chiffres(0,Couleur,13);
        Afficher_Chiffres(0,Couleur,18);
    }
}




void SROBOT(void)
{
    static uint8_t nb_calls = 0;
    nb_calls ++;
    if (nb_calls == 5) {
        nb_calls = 0;
        for(int i = 0; i < RGB_MATRIX_H ; i++){
            for(int j = 0; j < RGB_MATRIX_L ; j++){
                Matrix_RGB_Pix[i][j] = Couleur32(6,5,25);
            }
        }

        if (State_Led == 0){
            Afficher_super_7(Couleur32(5,25,0), 1);
            Afficher_Lettres('R',Couleur32(5,25,0),6);
            Afficher_Lettres('O',Couleur32(5,25,0),11);
            Afficher_Lettres('B',Couleur32(5,25,0),17);
            Afficher_Lettres('O',Couleur32(5,25,0),22);
            Afficher_Lettres('T',Couleur32(5,25,0),29);
            State_Led = 1;
        } else {
            Afficher_super_7(Couleur32(0,0,0), 1);
            Afficher_Lettres('R',Couleur32(0,0,0),6);
            Afficher_Lettres('O',Couleur32(0,0,0),11);
            Afficher_Lettres('B',Couleur32(0,0,0),17);
            Afficher_Lettres('O',Couleur32(0,0,0),22);
            Afficher_Lettres('T',Couleur32(0,0,0),29);
            State_Led = 0;
        }
    }
}

void Dessiner_Fleche(bool Decal) // Il faut initialiser la matrice avant
{
    static uint8_t decal_arrow = 0;
    if (!Decal) {
        decal_arrow = 0;
    }

    for (int j = 0; j < 9; j ++){
        for (int i = 0 ; i< RGB_MATRIX_H; i++){
            Matrix_RGB_Pix[i][j] = Matrix_Arrow[i][(j+decal_arrow)%9];
        }
    }
    for (int j = 0; j < 9; j ++){
        for (int i = 0 ; i< RGB_MATRIX_H; i++){
            Matrix_RGB_Pix[i][RGB_MATRIX_L-j-1] = Matrix_Arrow[i][(j+decal_arrow)%9];
        }
    }
    decal_arrow ++;
}

void Animation_pluie(void)
{
if ((Timer_ms1 - RGB_Gen_Timer) < 5000){
            Pluie(1, RGB_MATRIX_H - 1);
            Matrix_RGB_Pix[0][rand() % RGB_MATRIX_L] = Couleur32(6,5,25);
            Matrix_RGB_Pix[0][rand() % RGB_MATRIX_L] = Couleur32(6,5,25);
            
        }
        else if (5000 < (Timer_ms1 - RGB_Gen_Timer)  && (Timer_ms1 - RGB_Gen_Timer) < 10000)
        {
            Pluie(5, RGB_MATRIX_H - 1);
            Matrix_RGB_Pix[0][rand() % RGB_MATRIX_L] = Couleur32(6,5,25);
            Matrix_RGB_Pix[0][rand() % RGB_MATRIX_L] = Couleur32(6,5,25);
            
        }
        else if (10000 < (Timer_ms1 - RGB_Gen_Timer) && (Timer_ms1 - RGB_Gen_Timer) < 15000)
        {
            Pluie(10, RGB_MATRIX_H - 2);
            Matrix_RGB_Pix[0][rand() % RGB_MATRIX_L] = Couleur32(6,5,25);
            Matrix_RGB_Pix[0][rand() % RGB_MATRIX_L] = Couleur32(6,5,25);
            for (int i = 0 ; i < RGB_MATRIX_L ; i++){
                Matrix_RGB_Pix[RGB_MATRIX_H-1][i] = Couleur32(6,5,25);
            }
            Matrix_RGB_Pix[RGB_MATRIX_H-1][2] = Couleur32(0,0,0);
            Matrix_RGB_Pix[RGB_MATRIX_H-1][6] = Couleur32(0,0,0);
            Matrix_RGB_Pix[RGB_MATRIX_H-1][9] = Couleur32(0,0,0);
            Matrix_RGB_Pix[RGB_MATRIX_H-1][12] = Couleur32(0,0,0);
            Matrix_RGB_Pix[RGB_MATRIX_H-1][13] = Couleur32(0,0,0);
            Matrix_RGB_Pix[RGB_MATRIX_H-1][14] = Couleur32(0,0,0);
            Matrix_RGB_Pix[RGB_MATRIX_H-1][17] = Couleur32(0,0,0);
            Matrix_RGB_Pix[RGB_MATRIX_H-1][18] = Couleur32(0,0,0);
            Matrix_RGB_Pix[RGB_MATRIX_H-1][19] = Couleur32(0,0,0);
            Matrix_RGB_Pix[RGB_MATRIX_H-1][23] = Couleur32(0,0,0);
            Matrix_RGB_Pix[RGB_MATRIX_H-1][24] = Couleur32(0,0,0);
            Matrix_RGB_Pix[RGB_MATRIX_H-1][25] = Couleur32(0,0,0);
            Matrix_RGB_Pix[RGB_MATRIX_H-1][29] = Couleur32(0,0,0);

        }
          else if (15000 < (Timer_ms1 - RGB_Gen_Timer) && (Timer_ms1 - RGB_Gen_Timer) < 20000)
        {
            Pluie(10, RGB_MATRIX_H - 3);
            Matrix_RGB_Pix[0][rand() % RGB_MATRIX_L] = Couleur32(6,5,25);
            Matrix_RGB_Pix[0][rand() % RGB_MATRIX_L] = Couleur32(6,5,25);
            for (int i = 0 ; i < RGB_MATRIX_L ; i++){
                Matrix_RGB_Pix[RGB_MATRIX_H-2][i] = Couleur32(6,5,25);
            }
            Matrix_RGB_Pix[RGB_MATRIX_H-2][2] = Couleur32(0,0,0);
            Matrix_RGB_Pix[RGB_MATRIX_H-2][6] = Couleur32(0,0,0);
            Matrix_RGB_Pix[RGB_MATRIX_H-2][8] = Couleur32(0,0,0);
            Matrix_RGB_Pix[RGB_MATRIX_H-2][11] = Couleur32(0,0,0);
            Matrix_RGB_Pix[RGB_MATRIX_H-2][15] = Couleur32(0,0,0);
            Matrix_RGB_Pix[RGB_MATRIX_H-2][17] = Couleur32(0,0,0);
            Matrix_RGB_Pix[RGB_MATRIX_H-2][20] = Couleur32(0,0,0);
            Matrix_RGB_Pix[RGB_MATRIX_H-2][22] = Couleur32(0,0,0);
            Matrix_RGB_Pix[RGB_MATRIX_H-2][26] = Couleur32(0,0,0);
            Matrix_RGB_Pix[RGB_MATRIX_H-2][29] = Couleur32(0,0,0);

        }

         else if (20000 < (Timer_ms1 - RGB_Gen_Timer)  && (Timer_ms1 - RGB_Gen_Timer) < 25000)
        {
            Pluie(10, RGB_MATRIX_H - 4);
            Matrix_RGB_Pix[0][rand() % RGB_MATRIX_L] = Couleur32(6,5,25);
            Matrix_RGB_Pix[0][rand() % RGB_MATRIX_L] = Couleur32(6,5,25);
            for (int i = 0 ; i < RGB_MATRIX_L ; i++){
                Matrix_RGB_Pix[RGB_MATRIX_H-3][i] = Couleur32(6,5,25);
            }
            Matrix_RGB_Pix[RGB_MATRIX_H-3][2] = Couleur32(0,0,0);
            Matrix_RGB_Pix[RGB_MATRIX_H-3][6] = Couleur32(0,0,0);
            Matrix_RGB_Pix[RGB_MATRIX_H-3][7] = Couleur32(0,0,0);
            Matrix_RGB_Pix[RGB_MATRIX_H-3][11] = Couleur32(0,0,0);
            Matrix_RGB_Pix[RGB_MATRIX_H-3][15] = Couleur32(0,0,0);
            Matrix_RGB_Pix[RGB_MATRIX_H-3][17] = Couleur32(0,0,0);
            Matrix_RGB_Pix[RGB_MATRIX_H-3][20] = Couleur32(0,0,0);
            Matrix_RGB_Pix[RGB_MATRIX_H-3][22] = Couleur32(0,0,0);
            Matrix_RGB_Pix[RGB_MATRIX_H-3][26] = Couleur32(0,0,0);
            Matrix_RGB_Pix[RGB_MATRIX_H-3][29] = Couleur32(0,0,0);

        }
        else if (25000 < (Timer_ms1 - RGB_Gen_Timer)  && (Timer_ms1 - RGB_Gen_Timer) <30000)
        {
            Pluie(10, RGB_MATRIX_H - 5);
            Matrix_RGB_Pix[0][rand() % RGB_MATRIX_L] = Couleur32(6,5,25);
            Matrix_RGB_Pix[0][rand() % RGB_MATRIX_L] = Couleur32(6,5,25);
            for (int i = 0 ; i < RGB_MATRIX_L ; i++){
                Matrix_RGB_Pix[RGB_MATRIX_H-4][i] = Couleur32(6,5,25);
            }
            Matrix_RGB_Pix[RGB_MATRIX_H-4][3] = Couleur32(0,0,0);
            Matrix_RGB_Pix[RGB_MATRIX_H-4][6] = Couleur32(0,0,0);
            Matrix_RGB_Pix[RGB_MATRIX_H-4][7] = Couleur32(0,0,0);
            Matrix_RGB_Pix[RGB_MATRIX_H-4][8] = Couleur32(0,0,0);
            Matrix_RGB_Pix[RGB_MATRIX_H-4][11] = Couleur32(0,0,0);
            Matrix_RGB_Pix[RGB_MATRIX_H-4][15] = Couleur32(0,0,0);
            Matrix_RGB_Pix[RGB_MATRIX_H-4][17] = Couleur32(0,0,0);
            Matrix_RGB_Pix[RGB_MATRIX_H-4][18] = Couleur32(0,0,0);
            Matrix_RGB_Pix[RGB_MATRIX_H-4][19] = Couleur32(0,0,0);
            Matrix_RGB_Pix[RGB_MATRIX_H-4][22] = Couleur32(0,0,0);
            Matrix_RGB_Pix[RGB_MATRIX_H-4][26] = Couleur32(0,0,0);
            Matrix_RGB_Pix[RGB_MATRIX_H-4][29] = Couleur32(0,0,0);

        }
        else if (30000 < (Timer_ms1 - RGB_Gen_Timer)  && (Timer_ms1 - RGB_Gen_Timer) <35000)
        {
            Pluie(10, RGB_MATRIX_H - 6);
            Matrix_RGB_Pix[0][rand() % RGB_MATRIX_L] = Couleur32(6,5,25);
            Matrix_RGB_Pix[0][rand() % RGB_MATRIX_L] = Couleur32(6,5,25);

            for (int i = 0 ; i < RGB_MATRIX_L ; i++){
                Matrix_RGB_Pix[RGB_MATRIX_H-5][i] = Couleur32(6,5,25);
            }
            Matrix_RGB_Pix[RGB_MATRIX_H-5][4] = Couleur32(0,0,0);
            Matrix_RGB_Pix[RGB_MATRIX_H-5][6] = Couleur32(0,0,0);
            Matrix_RGB_Pix[RGB_MATRIX_H-5][9] = Couleur32(0,0,0);
            Matrix_RGB_Pix[RGB_MATRIX_H-5][11] = Couleur32(0,0,0);
            Matrix_RGB_Pix[RGB_MATRIX_H-5][15] = Couleur32(0,0,0);
            Matrix_RGB_Pix[RGB_MATRIX_H-5][17] = Couleur32(0,0,0);
            Matrix_RGB_Pix[RGB_MATRIX_H-5][20] = Couleur32(0,0,0);
            Matrix_RGB_Pix[RGB_MATRIX_H-5][22] = Couleur32(0,0,0);
            Matrix_RGB_Pix[RGB_MATRIX_H-5][26] = Couleur32(0,0,0);
            Matrix_RGB_Pix[RGB_MATRIX_H-5][29] = Couleur32(0,0,0);

        }
        else if (35000 < (Timer_ms1 - RGB_Gen_Timer)  && (Timer_ms1 - RGB_Gen_Timer) <40000)
        {
            Pluie(10, 1);
            Matrix_RGB_Pix[0][rand() % RGB_MATRIX_L] = Couleur32(6,5,25);
            Matrix_RGB_Pix[0][rand() % RGB_MATRIX_L] = Couleur32(6,5,25);
            for (int i = 0 ; i < RGB_MATRIX_L ; i++){
                Matrix_RGB_Pix[2][i] = Couleur32(6,5,25);
            }
            Matrix_RGB_Pix[2][4] = Couleur32(0,0,0);
            Matrix_RGB_Pix[2][6] = Couleur32(0,0,0);
            Matrix_RGB_Pix[2][9] = Couleur32(0,0,0);
            Matrix_RGB_Pix[2][11] = Couleur32(0,0,0);
            Matrix_RGB_Pix[2][15] = Couleur32(0,0,0);
            Matrix_RGB_Pix[2][17] = Couleur32(0,0,0);
            Matrix_RGB_Pix[2][20] = Couleur32(0,0,0);
            Matrix_RGB_Pix[2][22] = Couleur32(0,0,0);
            Matrix_RGB_Pix[2][26] = Couleur32(0,0,0);
            Matrix_RGB_Pix[2][29] = Couleur32(0,0,0);

        }
        else if (40000 < (Timer_ms1 - RGB_Gen_Timer)  && (Timer_ms1 - RGB_Gen_Timer) <43000)
        {
            Matrix_RGB_Pix[0][rand() % RGB_MATRIX_L] = Couleur32(6,5,25);
            Matrix_RGB_Pix[0][rand() % RGB_MATRIX_L] = Couleur32(6,5,25);
            Matrix_RGB_Pix[0][rand() % RGB_MATRIX_L] = Couleur32(6,5,25);
            Matrix_RGB_Pix[0][rand() % RGB_MATRIX_L] = Couleur32(6,5,25);
            Matrix_RGB_Pix[0][rand() % RGB_MATRIX_L] = Couleur32(6,5,25);
            
            for (int i = 0 ; i < RGB_MATRIX_L ; i++){
                Matrix_RGB_Pix[1][i] = Couleur32(6,5,25);
            }
            Matrix_RGB_Pix[1][1] = Couleur32(0,0,0);
            Matrix_RGB_Pix[1][2] = Couleur32(0,0,0);
            Matrix_RGB_Pix[1][3] = Couleur32(0,0,0);
            Matrix_RGB_Pix[1][4] = Couleur32(0,0,0);
            Matrix_RGB_Pix[1][6] = Couleur32(0,0,0);
            Matrix_RGB_Pix[1][7] = Couleur32(0,0,0);
            Matrix_RGB_Pix[1][8] = Couleur32(0,0,0);
            Matrix_RGB_Pix[1][12] = Couleur32(0,0,0);
            Matrix_RGB_Pix[1][13] = Couleur32(0,0,0);
            Matrix_RGB_Pix[1][14] = Couleur32(0,0,0);
            Matrix_RGB_Pix[1][17] = Couleur32(0,0,0);
            Matrix_RGB_Pix[1][18] = Couleur32(0,0,0);
            Matrix_RGB_Pix[1][19] = Couleur32(0,0,0);
            Matrix_RGB_Pix[1][23] = Couleur32(0,0,0);
            Matrix_RGB_Pix[1][24] = Couleur32(0,0,0);
            Matrix_RGB_Pix[1][25] = Couleur32(0,0,0);
            Matrix_RGB_Pix[1][28] = Couleur32(0,0,0);
            Matrix_RGB_Pix[1][29] = Couleur32(0,0,0);
            Matrix_RGB_Pix[1][30] = Couleur32(0,0,0);

        }
        else if(42000 <= (Timer_ms1 - RGB_Gen_Timer) && (Timer_ms1 - RGB_Gen_Timer) <50000){
                SROBOT();
           }

}


uint8_t Cmd_RGB_OFF(void){
    state_RGB = RGB_OFF;
    RGB_init();
    return 0;
}

uint8_t Cmd_RGB_Compteur(void){
    state_RGB = RGB_COMPTEUR;
    RGB_init();
    return 0;
}

uint8_t Cmd_RGB_Pluie(void){
    state_RGB = RGB_PLUIE;
    return 0;
}

uint8_t Cmd_RGB_Super_Pluie(void){
    state_RGB = RGB_SUPER_PLUIE;
    return 0;
}

uint8_t Cmd_RGB_Decompteur(void){
    state_RGB = RGB_DECOMPTEUR;
    RGB_init();
    return 0;
}

uint8_t Cmd_RGB_Match(void)
{
    if(state_RGB != RGB_MATCH) {
        state_RGB = RGB_MATCH;
        RGB_init();
    }
    return 0;
}

void RGB_init(void) {
    RGB_Gen_Timer = Timer_ms1;
    Cadran_1(Couleur32(5,5,30), Couleur32(3,30,2));
}



// cette fonction est appellee une fois toutes les 10 ms
void RGB_Anim_Loop(void) {
    if ((Timer_ms1 - timer_RGB) > 100) {
        timer_RGB += 100;
        switch (state_RGB) {
            case RGB_OFF:
                RGB_Anim_OFF();
                break;
            case RGB_COMPTEUR:
                RGB_Anim_Compteur();
                break;
            case RGB_DECOMPTEUR : 
                RGB_Anim_Decompteur();
                break;
            case RGB_PLUIE : 
                Pluie_Modif(5);
                break;
            case RGB_SUPER_PLUIE : 
                Animation_pluie();
                break;

            case RGB_MATCH : 
                Match_Mode();
                break;
            default:
                RGB_Anim_OFF();
                break;
        }
    }
}

void RGB_Anim_OFF(void) {
    for(int i = 0 ; i < RGB_MATRIX_H ; i ++){
         for(int j = 0 ; j < RGB_MATRIX_L ; j ++){
            Matrix_RGB_Pix[i][j] = 0;
         }
    }
}

void RGB_Anim_Compteur(void)
{
    int Nombre = ((Timer_ms1-RGB_Gen_Timer)/1000);

    if (Nombre <= 105) {

        Draw_Number(Nombre, Couleur32(34,100,0));
        Dessiner_Fleche(Nombre>94);
    } else {
        Cmd_RGB_OFF();
    }
}

void RGB_Anim_Decompteur(void)
{
    int Nombre = 5-((Timer_ms1-RGB_Gen_Timer)/1000);

    if (Nombre > 0) {

         Draw_Number(Nombre, Couleur32(34,100,0)); 
        Afficher_Lettres('G', Couleur32(34,100,0),11);
        Afficher_Lettres('O', Couleur32(34,100,0),17);

        Dessiner_Fleche(true);
    } else {
        Cmd_RGB_OFF();
    }
}
#define DECOMPTE_LEN 3
#define MATCH_LEN 100
void Match_Mode(void)
{
    uint32_t time = (Timer_ms1 - RGB_Gen_Timer)/1000;
    static uint32_t old_time; 
    if (time < DECOMPTE_LEN)
    {
        Draw_Number(DECOMPTE_LEN - time, Couleur32(34,100,0)); 
        Dessiner_Fleche(true);
        if (time != old_time){
            old_time = time;
            printf(" %d \n",DECOMPTE_LEN-time);
        }
          
    }
    else if (time<(DECOMPTE_LEN+1))
    {   
        Clear_Matrix_Number_Area();
        Afficher_Lettres('G', Couleur32(34,100,0),11);
        Afficher_Lettres('O', Couleur32(34,100,0),17);
        Dessiner_Fleche(true);
    }
    else if (time < (DECOMPTE_LEN + MATCH_LEN + 5))
    {
        Draw_Number(time - DECOMPTE_LEN, Couleur32(34,100,0));
        if (time != old_time){
            old_time = time;
            printf(" %d \n",time-DECOMPTE_LEN);
        }
        Dessiner_Fleche(time>(MATCH_LEN + DECOMPTE_LEN - 6));
    } else
    {
        Cmd_RGB_OFF();
    }
    
};



uint8_t RGB_Func(void)
{
	uint32_t val32;

    if (Get_Param_x32(&val32)) return PARAM_ERROR_CODE;
    RGB_En = (val32 != 0);
	
	return 0;
}

uint8_t RGB_Param_Func(void)
{
	uint32_t val32;

    if (Get_Param_u32(&val32)) return PARAM_ERROR_CODE;
    
    // on vient de recup un parametre envoye par l'utilisateur :
    // dans val32, entre 0 et ~ 4 milliard
    // on en fait ce qu'on en veut pour choisir ce que font les leds :)
    
	
	return 0;
}


uint32_t BRG_From_RGB(uint32_t RGB_Val) {
    return ((RGB_Val & 0xFF) << 16) | (RGB_Val  >> 8);
}
