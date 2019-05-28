

void val_setup(){
  
  b1=90; l1=135; f1=135;
  b4=85; l4=45; f4=50;
  b5=90; l5=135; f5=135;
  b2=90; l2=45; f2=45;
  b3=95; l3=135; f3=130;
  b6=90; l6=45; f6=45;

  b51=0; b52=0; b53=0; b54=0; b55=0; b56=0;
  b61=0; b62=0; b63=0; b64=0; b65=0; b66=0;

  action_speed = 240;
}
void val_setup_left_advance(){
  
  b1=90+(pid*2); l1=135; f1=135;
  b3=95+pid; l3=135; f3=130;
  b5=90+pid; l5=135; f5=135;

  b2=90+(pid*3); l2=45; f2=45;
  b4=85+pid; l4=45; f4=50;
  b6=90;     l6=45; f6=45;

 // b51=-10; b52=-15; b53=-20; b54=0; b55=0; b56=-5;
 // b61=0; b62=0; b63=0; b64=0; b65=0; b66=0;

    action_speed = 190;

 Serial.print("GO LEFT!");
 Serial.print("\n");
  }
void val_setup_right_advance(){
  
  b1=90+(pid*3); l1=135; f1=135;
  b3=95+pid; l3=135; f3=130;
  b5=90; l5=135; f5=135;

  b2=90+(pid*2); l2=45; f2=45;
  b4=85+pid; l4=45; f4=50;
  b6=90+pid; l6=45; f6=45;

//  b51=0; b52=0; b53=0; b54=0; b55=0; b56=0;
//  b61=0; b62=0; b63=-5; b64=-10; b65=-15; b66=-20;

      action_speed = 190;
  Serial.print("GO RIGHT!");
 Serial.print("\n");
}

