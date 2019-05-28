#ifndef BASE_HPP 
#define BASE_HPP

#include <Arduino.h>

// Constantes mapping
// Patte droite
#define RFF_PIN PD0  //18
#define RFU_PIN PD1  //19
#define RMF_PIN PB0  //8 
#define RMU_PIN PB2  //10
#define RBF_PIN PC6  //31
#define RBU_PIN PD7  //27

// Patte gauche
#define LFF_PIN PE6  //1   
#define LFU_PIN PB4  //28
#define LMF_PIN PB3  //11
#define LMU_PIN PB1  //9 
#define LBF_PIN PF4  //39 
#define LBU_PIN PB5  //29 

// Declaration manuelle des outputs
#define Init DDRB=DDRB|0b00111111;\
             DDRC=DDRC|0b01000000;\
             DDRD=DDRD|0b10000011;\
             DDRE=DDRE|0b01000000;\
             DDRF=DDRF|0b00010000;

typedef unsigned long FullState ;

// Etat actuel du stiquito
class Stiquito{
  public:
  Stiquito():FullState_((unsigned long)(0)),numero_etat_(0){};
  Stiquito(FullState state): FullState_(state),numero_etat_(0){};  
  //Constructeur de Stiquito

  void setState(FullState newState);
  //fonction de affectation des pin de Stiquito par modele de marche
  
  void execute(FullState Mode[],unsigned short temps);
  //fonction execution de programme en limitant de temps(pas tester)
  
  void showState(){Serial.println(FullState_);};
  //fonction de Serial.print pour afficher le current FullState_
  
  protected:
    FullState FullState_;
    //Il s'agit Etat Complete de Stiquito (4 Octet)
    //Compris 1 Octet de State RIGHT,1 Octet de State LEFT, 2 Octets pour holdTime 

    int numero_etat_;
    //Indication de numero etat en ce moment  
};

#endif // BASE_HPP


