
#include "WalkingModels.h"

/***************************************************/
/*       Section de declaration de variable        */
/***************************************************/
Stiquito Papion;
//Objet de Stiquito
int indice;
//current state
FullState etat0;
//etat initial
FullState etat1;
//etat initial

/***************************************************/
/*            Section de Initialisation            */
/***************************************************/
void setup() {
  Serial.begin(9600);
  indice = 0;
  etat0 = STATE(0,0,0,0,0,0,0,0,0,0,0,0,1000);
  etat1 = STATE(1,1,1,1,1,1,1,1,1,1,1,1,1000);
  Init;
}

inline uint8_t fsTabSize(FullState * fs) { 
  return sizeof(fs) / sizeof(fs[0]);
}

/***************************************************/
/*              Section de Execution               */
/***************************************************/
void loop() {

  Papion.setState(WalkingTab[indice]);
  indice++;
  if ( indice >= WalkingTabSize ) indice = 0;

}


