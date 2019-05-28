/*
La fonction tourner() permet de réaliser une maneuvre d'évitement d'un obstacle
en réalisant un pas les 2 pieds au sol, 2 pas simple puis de nouveau un pas les
2 pieds au sol pour se remettre dans la direction initiale



*/



void tourner() {
  onTourne = true;
  for (int i = 0; i < debattement_avance; i++) {
    ServoAvance.write(90 - gauche_droite * (i - (debattement_avance / 2)));
    delay(20);
  }

  avance(+gauche_droite, avant_arriere);
  avance(-gauche_droite, avant_arriere);
  for (int i = 0; i < debattement_avance; i++) {
    ServoAvance.write(90 - gauche_droite * (i - (debattement_avance / 2)));
    delay(20);
  }
  Serial.println("radar degele");
  geleradar = false;
  Serial.println("on tourne pas");
  onTourne = false;

}

