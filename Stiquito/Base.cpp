#include "Base.hpp"

int Mapping[12] = {RFF_PIN, RFU_PIN, RMF_PIN, RMU_PIN, RBF_PIN, RBU_PIN, \
                   LFF_PIN, LFU_PIN, LMF_PIN, LMU_PIN, LBF_PIN, LBU_PIN};
//tableau de pin de Arduino


void Stiquito::setState(FullState newState) {
  this->FullState_ = newState; //Affectation de attribute de Stiquito
  //initialisation de valeurs pour PORT B,C,D,E,F
  //sizeof(int)= 2 octets, qui est le meme taille que les registres de port
  int i_b=0;
  int i_c=0;
  int i_d=0;
  int i_e=0;
  int i_f=0;

  // Set des pattes droites //단순 다리 핀 정의
  if (newState & ((unsigned long)(1) << (29)))i_d=i_d+0b00000001;
  if (newState & ((unsigned long)(1) << (28)))i_d=i_d+0b00000010;
  if (newState & ((unsigned long)(1) << (27)))i_b=i_b+0b00000001;
  if (newState & ((unsigned long)(1) << (26)))i_b=i_b+0b00000100;
  if (newState & ((unsigned long)(1) << (25)))i_c=i_c+0b01000000;
  if (newState & ((unsigned long)(1) << (24)))i_d=i_d+0b10000000;

  // Set des pattes droites
  if (newState & ((unsigned long)(1) << (21)))i_e=i_e+0b01000000;
  if (newState & ((unsigned long)(1) << (20)))i_b=i_b+0b00010000;
  if (newState & ((unsigned long)(1) << (19)))i_b=i_b+0b00001000;
  if (newState & ((unsigned long)(1) << (18)))i_b=i_b+0b00000010;
  if (newState & ((unsigned long)(1) << (17)))i_f=i_f+0b00010000;
  if (newState & ((unsigned long)(1) << (16)))i_b=i_b+0b00100000;

  PORTB = i_b;
  PORTC = i_c;
  PORTD = i_d;
  PORTE = i_e;
  PORTF = i_f;


  // Set des pattes droites  //움직이게 하는코드 24까지
  for (i = 0; i < 6; i++) {
    if (newState & ((unsigned long)(1) << (29 - i)))
      digitalWrite(Mapping[i], HIGH);
    else
      digitalWrite(Mapping[i], LOW);
  }

  // Set des pattes gauches
  for (i = 6; i < 12; i++) {
    if (newState & ((unsigned long)(1) << (27 - i)))
      digitalWrite(Mapping[i], HIGH);
    else
      digitalWrite(Mapping[i], LOW);
  }

  delay(newState & (0xFFFF));
}



void Stiquito::execute(FullState Mode[], unsigned short temps) {
  unsigned short timer_ = 0;
  //Counter pour temps totale execution
  int ind = 0;
  //current state=0;
  while (timer_ < temps) {
    this->setState(Mode[ind]);
    timer_=  timer_ +(unsigned short)(Mode[ind] & (0xFFFF));
    ind++;
    if ( ind >= (sizeof(Mode)/(sizeof(unsigned long))) ) ind = 0;
  }
}




