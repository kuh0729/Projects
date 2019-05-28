/*
Cette fonction réalise l'incrémentation du Servo radar (balayage du capteur ultrason), 
ainsi que la mesure de la distance entre le robot et les obstacles présents devant lui
de plus elle fait appel à la fonction tourner qui effectue la manœuvre d'évitement de 
l'obstacle lorsque les conditions sont appropriées (pas terminé et le bon pied en avant)


*/



void radar() {
  //Si l'angle du radar atteint la borne de l'intervalle donné ([60,120]), la variable HB qui représente le sens d'incrémentation du Servo radar change de signe
  if (angle >= 120) { 
    HB = -1;
  }
  if (angle <= 60) {
    HB = 1;
  }
  if (!geleradar) {
    calculDistance(); //on calcule la distance avec l'objet le plus proche. Si geleradar est vrai, il faut garder la valeur de mémoire et donc ne pas la recalculer
    angle = angle + HB;//On incrémente le Servo radar
  }

  ServoRadar.write(angle);



  if (distance < 20 && distance > 0) { //  On vérifie s'il y a un obstacle à moins de 20 cm
    geleradar = true;
    if ((angle < 90 && gauche_droite == 1 || angle >= 90 && gauche_droite == -1) && pasTermine ) { 
      //Ce test Vérifie si Le pas est terminé et si le bon pied est en avant pour éviter l'obstacle
      //Si c'est le cas on fait alors appel à la fonction tourner
      tourner();
    }
  }
}

//fonction permettant de calculer la distance à un obstacle à l'aide du capteur ultrason
void calculDistance() {

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);//une salve est émise pendant 10 µs
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  //pulseIn est une fonction qui renvoie le temps mis depuis son activation par une pin à réaliser un front montant
  duration = pulseIn(echoPin, HIGH, 2000); //ne capte pas les distances supérieurs à 34cm (renvoi 34cm si la distance est supérieur à 34)
  //duration renvoie donc la durée qu'a mis l'onde sonore à faire un aller-retour entre le robot et l'obstacle
  distance = duration * 0.034 / 2; //conversion de cette durée en distance de la vitesse du son dans l'air
}

