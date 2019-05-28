/*
Cette fonction permet de modifier les variables principales du programme, 
à l'aide du Bluetooth, lorsque le robot est arrêté.

Cette fonction ne sera utile que lors de la phase de test, pour modifier 
les différents paramètres et ainsi voir leur influence, de manière à choisir 
la combinaison idéale

On réalise tout d'abord un premier affichage des différents choix, puis une 
fois que l'utilisateur a choisie la variable qu'il veut modifier on lit la 
nouvelle valeur entrée puis on l'enregistre dans l'EEPROM, afin qu'on puisse 
y accéder à nouveau lors des prochains démarrages



*/




void choix_variables() {
  char input = '0';
  Serial.println();
  Serial.println("-- Liste des Reglages --");
  Serial.print("1 : Kp = ");
  Serial.println(Kp);
  Serial.print("2 : Ki = ");
  Serial.println(Ki);
  Serial.print("3 : recoupement = ");
  Serial.println(recoupement);
  Serial.print("4 : debattement avance = ");
  Serial.println(debattement_avance_init);
  Serial.print("5 : debattement bascule = ");
  Serial.println(debattement_bascule);
  Serial.print("6 : duree avance = ");
  Serial.println(duree_avance);
  Serial.print("7 : duree bascule = ");
  Serial.println(duree_bascule);
  Serial.println("0 : pour valider ");

  while (!termine) // Tant que l'utilisateur ne veut pas ne veut pas quitter le menu de modification des variables.
  {
    if (Serial.available() > 0) //  On vérifie si des données viennent du module bluetooth
    {
      input = Serial.read();  //  On lit ce qui vient du bluetooth puis on analyse l'information afin de savoir ce qu'il faut faire.
      switch (input)
      {
        case '1':
          Serial.println("choisir une valeur de Kp : ");
          Kp = lecture(); 
          EEPROM.write(adresseKp, entier_lu);
          break;
        case '2':
          Serial.println("choisir une valeur de Ki (x0.1) : ");
          Ki = 0.1 * lecture();
          EEPROM.write(adresseKi, entier_lu);
          break;
        case '3':
          Serial.println("choisir une valeur de recoupement : ");
          recoupement = lecture();
          EEPROM.write(adresseRecoupement, entier_lu);
        case '4':
          Serial.println("choisir une valeur de debattement avance : ");
          debattement_avance_init = lecture();
          EEPROM.write(adresseDebAvance, entier_lu);
          break;
        case '5':
          Serial.println("choisir une valeur de debattement bascule  : ");
          debattement_bascule = lecture();
          EEPROM.write(adresseDebBascule, entier_lu);
          break;
        case '6':
          Serial.println("choisir une valeur de duree avance (x0.1) : ");
          duree_avance = 0.1 * lecture();
          EEPROM.write(adresseDureeAvance, entier_lu);
          break;
        case '7':
          Serial.println("choisir une valeur de duree bascule (x0.1) : ");
          duree_bascule = 0.1 * lecture();
          EEPROM.write(adresseDureeBascule, entier_lu);
          break;
        case '0':
          termine = true;
          break;
      }
    }
  }

  //On recalcule alors la valeur des variables utilisées par le programme en fonction des valeurs entrées
  duree_pas = 50 * (duree_avance + duree_bascule) / (50 + recoupement); //en secondes DA+DB-2DR=DP ; (RE/100)*DP=DR ; DP=(DA+DB*50/(50+Re)
  duree_delay = duree_pas * 10; //en ms par % DD=1000/100DP
  pourcent_avance = duree_avance / duree_pas * 100;
  pourcent_bascule = duree_bascule / duree_pas * 100;
  increment_angle_bascule = debattement_bascule / pourcent_bascule;
}



//Cette fonction permet la lecture d'un entier envoyé depuis le port série UART
byte lecture() {
  while (Serial.available() == 0); //  On s'arrête dans cette boucle tant qu'il n'y a pas de données arrivant du Bluetooth
  entier_lu = Serial.parseInt(); //On lit alors L'entier reçu Que l'on renvoie ensuite
  Serial.print("valeur entree : ");
  Serial.println(entier_lu);
  return entier_lu;
}







