#ifndef WALKINGMODEL_H
#define WALKINGMODEL_H
#include "Base.hpp"
#define STATE(rff, rfu, rmf, rmu, rbf, rbu, lff, lfu, lmf, lmu, lbf, lbu, holdtime) \
  ( ((unsigned long)(rff) << 29) | ((unsigned long)(rfu) << 28) | ((unsigned long)(rmf) << 27) | \
  ((unsigned long)(rmu) << 26) | ((unsigned long)(rbf) << 25) | ((unsigned long)(rbu) << 24) | \
  ((unsigned long)(lff) << 21) | ((unsigned long)(lfu) << 20) | ((unsigned long)(lmf) << 19) | \
  ((unsigned long)(lmu) << 18) | ((unsigned long)(lbf) << 17) | ((unsigned long)(lbu) << 16) | \
  (unsigned long)(holdtime) )
#define STATE_ZERO(holdtime) STATE(0,0,0,0,0,0,0,0,0,0,0,0,holdtime)
//macro de fonction affectation de FullState
#define WalkingTab bipodjon

#define WalkingTabSize 9
#define DELAY 1000   
#define DELAY_DOWN 200
 //rff, rfu, rmf, rmu, rbf, rbu, lff, lfu, lmf, lmu, lbf, lbu //modified

FullState testVertical[2] = {

                    STATE(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, DELAY), \
                    STATE(0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, DELAY/2),
  
                    };

//DELAY ideal = 500
FullState tripod[6] = {
  
                    STATE(0, 1,  0, 0,  0, 1,   0, 0,  0, 1,  0, 0, (DELAY-DELAY_DOWN)/2), \
                    STATE(1, 1,  0, 0,  1, 1,   0, 0,  1, 1,  0, 0, (DELAY-DELAY_DOWN)/2), \
                    STATE(1, 0,  0, 0,  1, 0,   0, 0,  1, 0,  0, 0, DELAY_DOWN), \

                    STATE(0, 0,  0, 1,  0, 0,   0, 1,  0, 0,  0, 1, (DELAY-DELAY_DOWN)/2), \
                    STATE(0, 0,  1, 1,  0, 0,   1, 1,  0, 0,  1, 1, (DELAY-DELAY_DOWN)/2), \
                    STATE(0, 0,  1, 0,  0, 0,   1, 0,  0, 0,  1, 0, DELAY_DOWN),

                    };
                    
//rff, rfu, rmf, rmu, rbf, rbu, lff, lfu, lmf, lmu, lbf, lbu, holdtime
FullState bipod1[6] =  {
                       STATE(0, 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 0, DELAY/2),\
                       STATE(0, 0, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, DELAY/1.5),\
  
                       
                       STATE(0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, DELAY/2),\
                       STATE(1, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1, DELAY/1.5),\

                       
                       STATE(1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, DELAY/2),\
                       STATE(1, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, DELAY/1.5),\
                     }; 
//Tableau de modele de marche Tripod


FullState bipod[9] = {
                    //Pattes Droite/Milieu et Gauche/Arrière se posent, Droite/Arrière et Gauche/Avant avancent
                    STATE(0, 0,  1, 0,  1, 1,   1, 1,  0, 0,  1, 0, DELAY_DOWN/2), \
                    //Pattes Droite/Avant et Gauche/Milieu se lèvent
                    STATE(0, 1,  1, 0,  1, 1,   1, 1,  0, 1,  1, 0, DELAY_DOWN/2),

                    //Pattes Droite/Avant et Arrière et Gauche/Milieu et Avant avancent
                    STATE(1, 1,  0, 0,  1, 1,   1, 1,  1, 1,  0, 0, DELAY-DELAY_DOWN/2), \

                    //Pattes Droite/Avant et Gauche/Milieu avancent, Droite/Arrière et Gauche/Avant se posent
                    STATE(1, 1,  0, 0,  1, 0,   1, 0,  1, 1,  0, 0,  DELAY_DOWN/2), \
                    ////Pattes Droite/Milieu et Gauche/Arrière se lèvent
                    STATE(1, 1,  0, 1,  1, 0,   1, 0,  1, 1,  0, 1,  DELAY_DOWN/2), \

                    //Pattes Droite/Avant et Milieu et Gauche/Milieu et Arrière avancent
                    STATE(1, 1,  1, 1,  0, 0,   0, 0,  1, 1,  1, 1, DELAY-DELAY_DOWN/2), \

                    //Pattes Droite/Milieu et Gauche/Arrière avancent, Droite/Avant et Gauche/Milieu se posent
                    STATE(1, 0,  1, 1,  0, 0,   0, 0,  1, 0,  1, 1, DELAY_DOWN/2), \
                    //Pattes Droite/Arrière et Gauche/Avant se lèvent
                    STATE(1, 0,  1, 1,  0, 1,   0, 1,  1, 0,  1, 1, DELAY_DOWN/2), \

                    //Pattes Droite/Arrière et Milieu et Gauche/Avant et Arrière avancent
                    STATE(0, 0,  1, 1,  1, 1,   1, 1,  0, 0,  1, 1, DELAY-DELAY_DOWN/2),
                    };




FullState tetrapod[9] = {
                    //Pattes Droite/Arrière et Gauche/Avant avancent
                    STATE(0, 0,  0, 0,  1, 1,   1, 1,  0, 0,  0, 0, DELAY/2-DELAY_DOWN), \

                    //Pattes Droite/Arrière et Gauche/Avant se posent
                    //Pattes Droite/Avant et Gauche/Arrière se lèvent
                    STATE(0, 0,  0, 0,  1, 0,   1, 0,  0, 0,  0, 0, DELAY_DOWN/2), \
                    STATE(0, 1,  0, 0,  1, 0,   1, 0,  0, 0,  0, 1, DELAY_DOWN/2), 

                    //Pattes Droite/Avant et Gauche/Arrière avancent
                    STATE(1, 1,  0, 0,  0, 0,   0, 0,  0, 0,  1, 1,  DELAY/2-DELAY_DOWN), \

                    //Pattes Droite/Avant et Gauche/Arrière se posent
                    //Pattes Droite/Milieu et Gauche/Milieu se lèvent
                    STATE(1, 0,  0, 0,  0, 0,   0, 0,  0, 0,  1, 0, DELAY_DOWN/2), \
                    STATE(1, 0,  0, 1,  0, 0,   0, 0,  0, 1,  1, 0, DELAY_DOWN/2),

                    //Pattes Droite/Milieu et Gauche/Milieu avancent
                    STATE(0, 0,  1, 1,  0, 0,   0, 0,  1, 1,  0, 0, DELAY/2-DELAY_DOWN), \

                    //Pattes Droite/Milieu et Gauche/Milieu se posent
                    //Pattes Droite/Arrière et Gauche/Avant se lèvent
                    STATE(0, 0,  1, 0,  0, 0,   0, 0,  1, 0,  0, 0, DELAY_DOWN/2),
                    STATE(0, 0,  1, 0,  0, 1,   0, 1,  1, 0,  0, 0, DELAY_DOWN/2),
                    };




                    
//Tableau de modele de marche Quatre_deux

FullState true_single_wave[15] = {
                      // il faudrait voir a quel moment on fait pull
                      // tripode 1
                      STATE(0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, DELAY/4), \
                      STATE(1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, DELAY/2), \
                      STATE(1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, DELAY/4), \
                      STATE(1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, DELAY/2), \
                      STATE(1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, DELAY/4), \
                      STATE(1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, DELAY/2), \
                      STATE(1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, DELAY/4), \
    
                      // tripode 2
                      STATE(1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, DELAY/4), \
                      STATE(1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, DELAY/2), \
                      STATE(1, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, DELAY/4), \
                      STATE(1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0, DELAY/2), \
                      STATE(1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, DELAY/4), \
                      STATE(1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, DELAY/2), \
                      STATE(1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, DELAY/2), \
                      STATE_ZERO(DELAY)
                      };
// Tableau de modele de marche true_single_wave                

FullState optimal_wave[18] = {
                      // tripode 1
                      STATE(1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, DELAY_DO WN/4), \
                      STATE(1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3*(DELAY_DOWN/4)), \
                      STATE(1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, DELAY/100), \
                      
                      STATE(0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, DELAY_DOWN/4), \
                      STATE(0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 3*(DELAY_DOWN/4)), \
                      STATE(0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, DELAY/100), \
                      
                      STATE(0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, DELAY_DOWN/4), \
                      STATE(0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 3*(DELAY_DOWN/4)), \
                      STATE(0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, DELAY/100), \
    
                      // tripode 2
                      STATE(0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, DELAY_DOWN/4), \
                      STATE(0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 3*(DELAY_DOWN/4)), \
                      STATE(0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, DELAY/100), \
                      
                      STATE(0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, DELAY_DOWN/4), \
                      STATE(0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3*(DELAY_DOWN/4)), \
                      STATE(0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, DELAY/100), \
                      
                      STATE(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, DELAY_DOWN/4), \
                      STATE(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 3*(DELAY_DOWN/4)), \
                      STATE(0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, DELAY/100), \
                      };


//old 

FullState ex[3] = {
                    STATE(1, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1, DELAY), //up            etape1
                    STATE(1, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, DELAY), //up            etape1
                    STATE(0, 0, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, DELAY), //up
                    };
                    
FullState single_wave_version_erreur[8] = {
                      STATE_ZERO(DELAY / 2), \
                      STATE(1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, DELAY/2), \
                      STATE(1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, DELAY/2), \
                      STATE(1, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, DELAY/2), \
                      STATE(1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 0, DELAY/2), \
                      STATE(1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0, DELAY/2), \
                      STATE(1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, DELAY/2), \
                      STATE(1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, DELAY/2)
                      };
//Tableau de modele de marche single_wave_version_erreur
FullState quatre_deux_rotation[5] = {
                    STATE(1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, DELAY/2), \
                    STATE(1, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, DELAY/2), \
                    STATE(1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, DELAY/2), \
                    STATE(1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, DELAY/2), \
                    STATE_ZERO(DELAY / 2)
                    };
//Tableau de modele de marche quatre_deux_rotation
FullState fastripod[8] = {STATE_ZERO(DELAY / 4), \
                    STATE(0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, DELAY/4), \
                    STATE(1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, DELAY/4), \
                    STATE(1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, DELAY/4), \
                    STATE_ZERO(DELAY / 4), \
                    STATE(0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, DELAY/4), \
                    STATE(0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, DELAY/4), \
                    STATE(0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, DELAY/4)
                    };
// Tableau de modele de marche fastripod
FullState pilipili[7] = {
                      STATE(1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, DELAY/2), \
                      STATE(1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 0, DELAY/2), \
                      STATE(1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, DELAY/2), \
                      STATE(1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, DELAY/2), \
                      STATE(1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, DELAY/2), \
                      STATE(0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, DELAY/2), \
                      };
FullState TestZero[5] = {
                    STATE_ZERO(DELAY / 2),
                    STATE_ZERO(DELAY / 2),
                    STATE_ZERO(DELAY / 2),
                    STATE_ZERO(DELAY / 2),
                    STATE_ZERO(DELAY / 2),
                    };
#endif






