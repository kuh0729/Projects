/*
Cette partie contient les différentes fonctions en lien avec le magnétomètre.

- La fonction correction () utilise la valeur de l’angle mesuré par la boussole afin
de renvoyer une correction proportionnelle intégrale (rectification).

- La fonction boussole () lit la valeur du champ magnétique selon les 3 axes, et
renvoie l’angle correspondant. Cette valeur évolue dans l’intervalle :
[angle_initial – 180 ; angle_initial + 180] où angle_initial est l’angle mesuré au lancement du mode.

- Init_HMC5803L() permet d’envoyer la séquence d’initialisation du magnétomètre.

- La dernière fonction, HMC5803L_Read(byte Axis), renvoie la valeur du champ magnétique selon l’axe entré.
*/




void correction() { //Correction proportionnelle intégrale
  boussole();

  //calcul de l'erreur entre la valeur initiale et la valeur actuelle
  erreur = angle_initial -  boussole();

  //calcul du terme correspondant à la correction intégrale
  correction_integrale = correction_integrale + erreur * Ki;

  //calcul du terme correspond dans la correction proportionnelle
  correction_proportionnelle = erreur * Kp;

  //somme des 2 corrections
  rectification = correction_proportionnelle + correction_integrale;
}

// fonction qui lit les données de la boussole et renvoie un angle utilisable pour la correction
double boussole()
{
  Xmagnetic = HMC5803L_Read(X);  //lecture sur 3 axes et sortie sur le port sériel
  Ymagnetic = HMC5803L_Read(Y);
  Zmagnetic = HMC5803L_Read(Z);
   Serial.print("x = "); Serial.println( Xmagnetic);
   Serial.print("y = "); Serial.println( Ymagnetic);
   Serial.print("y = "); Serial.println( Ymagnetic);

  //Calculer l'angle_boussole de la boussole à partir de X et Y (à plat)
  angle_boussole = atan2(Ymagnetic, Xmagnetic) * (180 / 3.14159265); // angle_boussole en degres
  if (angle_boussole < angle_initial - 180) { //on modifie l'angle calculé par la boussole pour qu'il soit dans un intervalle centré sur l'angle initial
    angle_boussole = angle_boussole + 360;
  }
  if (angle_boussole >= angle_initial + 180) {
    angle_boussole = angle_boussole - 360;
  }
  return angle_boussole; // on renvoie l'angle dans le bon intervalle
}

//fonction qui initialise la transmission I2C
void Init_HMC5803L(void)
{
  // Set the module to 8x averaging and 15Hz measurement rate
  Wire.beginTransmission(HMC5803L_Address);
  Wire.write(0x00);
  Wire.write(0x70);

  Wire.write(0x01);
  Wire.write(0xA0);   //Règle un gain de 5
  Wire.endTransmission();
}

// Fonction qui lit le module boussole
int HMC5803L_Read(byte Axis)
{
  int Result;
  /* Initiate a single measurement */
  Wire.beginTransmission(HMC5803L_Address);
  Wire.write(0x02);
  Wire.write(0x01);
  Wire.endTransmission();
  delay(6);

  /* Move modules the resiger pointer to one of the axis data registers */
  Wire.beginTransmission(HMC5803L_Address);
  Wire.write(Axis);
  Wire.endTransmission();

  /* Read the data from registers (there are two 8 bit registers for each axis) */
  Wire.requestFrom(HMC5803L_Address, 2);
  Result = Wire.read() << 8;
  Result |= Wire.read();

  return Result;
}
