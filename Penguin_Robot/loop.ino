void loop()
{
  /*

  Cette fonction est la fonction principale de notre programme ; c’est la fonction appelée une fois l’initialisation
  des variables et le setup effectué. Cette fonction est une boucle que le microcontrôleur fait tourner indéfiniment.

  Nous avons choisi d’utiliser cette boucle en tant que menu principal. Elle sert d’interface avec l’utilisateur en lui
  permettant de choisir parmi les différents modes de fonctionnement du robot.

  Voici comment est constitué cette fonction :
  Une boucle permet le choix du mode à l’aide du Bluetooth, ou bien de façon manuelle par appui du bouton poussoir.
  Celle-ci s’exécute tant que la variable d’initialisation (start) n’est pas vraie.
  Une fois cette variable vraie, on entre dans une seconde partie permettant exécution du mode choisi .

  Lorsque l'on sort d'un mode, la boucle nous ramène à la première partie, pour choisir à nouveau un mode.

  */







  start = false; //  "start" est la variable qui indique si il faut démarrer un code ou non.  On la mets à "false" pour ne lancer aucun mode avant que l'utilisateur l'ai décidé.
  char input = '0';
  menu();
  while (!start) // Tant que l'utilisateur ne veut pas lancer de mode.
  {
    if (Serial.available() > 0) //  On vérifie si des données viennent du module bluetooth
    {
      input = Serial.read();  //  On lit ce qui vient du bluetooth puis on analyse l'information afin de savoir ce qu'il faut faire.
      switch (input)
      {
        case '1':
          mode = 1;  //  "mode"  est la variable qui contient le mode qu'il faut exécuter.
          digitalWrite(led1, HIGH); // On allume la led correspondant au mode 1
          digitalWrite(led2, LOW);
          Serial.println("mode course choisi");
          break;
        case '2':
          mode = 2;
          digitalWrite(led1, LOW);// On allume la led correspondant au mode 2
          digitalWrite(led2, HIGH);
          Serial.println("mode obstacle choisi");
          break;
        case '3':
          start = true;  //Si l'entrée est '3', on considère que l'utilisateur valide le mode choisi.
          break;
        case '0':
          choix_variables();//Si l'entrée est '0',
          menu();
          break;
      }
    }
    else
    {
      if (digitalRead(bouton_poussoire))// Si il y a un appui sur le bouton, on éxecute le mode manuel
      {
        manuel();
      }
    }
    verifierTensionBatterie();  // On vérifie si la batterie n'est pas déchargé.
    delay(50);
  }

  Stop = false;
  switch (mode)
  {
    case 1:
      Serial.println("Execution du mode course");
      clignotement();
      digitalWrite(led1, HIGH); // On mets la led de mode 1 à HIGH et les autres led à LOW
      digitalWrite(led2, LOW);
      mode1();
      break;
    case 2:
      Serial.println("Execution du mode obstacle");
      clignotement();
      digitalWrite(led1, LOW);
      digitalWrite(led2, HIGH);

      mode1();
      break;
  }
}






void manuel()
{
  /*
  cette fonction ne s'active que lorsqu'il y a eu un appui sur le bouton poussoir.
  si cet appui est toujours présent au bout d'une demi seconde, on considère que c'est un appui long, dans le cas contraire ce sera un appui court.
  l'appui court terme est entre le mode 1 et 2
  la pluie long valide le mode choisi en faisant passer le booléen start à l'état vrai
  */
  delay(500);
  if (digitalRead(bouton_poussoire))
  {
    start = true;
  }
  else
  {
    mode++;
    if (mode == 3)
    {
      mode = 1;
    }
  }
  switch (mode) //affichage des leds
  {
    case 1:
      digitalWrite(led1, HIGH);
      digitalWrite(led2, LOW);
      break;
    case 2:
      digitalWrite(led1, LOW);
      digitalWrite(led2, HIGH);
      break;
  }
}
void clignotement()
{
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  delay(100);
  digitalWrite(led1, HIGH);
  digitalWrite(led2, LOW);
  delay(100);
  digitalWrite(led1, LOW);
  digitalWrite(led2, HIGH);
  delay(100);
  digitalWrite(led1, HIGH);
  digitalWrite(led2, LOW);
  delay(100);
  digitalWrite(led1, LOW);
  digitalWrite(led2, HIGH);
  delay(100);
  digitalWrite(led1, HIGH);
  digitalWrite(led2, LOW);
  delay(100);
  digitalWrite(led1, LOW);
  digitalWrite(led2, HIGH);
  delay(100);
}
void menu() {
  Serial.println();
  Serial.println("-- Menu --");
  Serial.println("0 : choix des variables");
  Serial.println("1 : mode course");
  Serial.println("2 : mode obstacle");
  Serial.println("3 : valider le mode");
}
