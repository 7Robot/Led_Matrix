#ifndef __LEDS_RGB_ANIM_H_
#define __LEDS_RGB_ANIM_H_




uint32_t Couleur32(uint8_t green,uint8_t red, uint8_t blue) ;
void Afficher_Chiffres(uint8_t chiffre,  uint32_t couleur, uint16_t colonne);
void Motif_Fleche_Droite(uint8_t colonne, uint32_t couleur);
// void Motif_Fleche_Gauche(uint8_t colonne, uint32_t couleur);
void Cadran_1(uint32_t couleur1, uint32_t couleur2);
void Dessiner_Fleche(bool Decal);
void RGB_Anim_10ms_Loop(void);
void RGB_Anim_Decompteur();
void Pluie_Modif(int intensite);
void Pluie(int intensite, int sol);
void SROBOT(void);


uint8_t RGB_Func(void);
uint8_t RGB_Param_Func(void);

uint32_t BRG_From_RGB(uint32_t RGB_Val);

uint8_t Cmd_RGB_OFF(void);
uint8_t Cmd_RGB_Compteur(void);
uint8_t Cmd_RGB_Decompteur(void);
uint8_t Cmd_RGB_Pluie(void);
uint8_t Cmd_RGB_Super_Pluie(void);


void Match_Mode(void);

void RGB_init(void);
void RGB_Anim_Loop(void);

void RGB_Anim_OFF(void);
void RGB_Anim_Compteur(void);
uint8_t Cmd_RGB_Match(void);

#define RGB_OFF 1
#define RGB_COMPTEUR 10
#define RGB_DECOMPTEUR 11
#define RGB_PLUIE 20
#define RGB_SUPER_PLUIE 21
#define RGB_MATCH 30




#endif // __LEDS_RGB_ANIM_H_
