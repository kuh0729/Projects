/*
Cette fonction permet de faire un pas à gauche ou à droite, en avant ou en arrière, 
en fonction des 2 variables entrées (dont la valeur est {1,-1})

Le pas générique est décomposé à l'aide d'une boucle for en cent itérations représentées
en pourcent

Si i (la variable incrémentée) est compris dans l'intervalle correspondant à la phase 
durant laquelle un des servomoteur doit fonctionner, celui-ci sera incrémenté.
Il y a donc 3 tests (if) correspondant aux 3 phases de fonctionnement d'un pas : 
- mise en équilibre sur un pied (Servo bascule)
- avance du pied (Servo avance)
– remise à l'état neutre du Servo bascule

Nous avons choisi d'utiliser une boucle ainsi que des tests correspondant aux 3 phases, 
car nous souhaitons que ces 3 phases puissent être réalisées en partie en parallèle pour
gagner en rapidité et en fluidité dans le mouvement

A chaque pour cent du pas, on vérifie qu'il ne faut pas arrêter le robot,et on fait appel
à la fonction radar qui incrémente le radar et vérifie s'il y a un obstacle

*/



void avance(int  a, int  b) {
  gauche_droite = a;
  avant_arriere = b;

  debattement_avance = debattement_avance_init + gauche_droite * rectification;
  increment_angle_avance = debattement_avance / pourcent_avance; //angle par %

  pasTermine = false;

  ServoAvance.write(90 + avant_arriere * ( - gauche_droite * debattement_avance / 2));

  for (int i = 1; i <= 100; i++) {

    //On remet les Servo avance en position lorsque le Servo bascule est en position neutre.
    //C'est donc ici que se fait la correction de trajectoire

    if (i <= pourcent_bascule / 2) {
      ServoBascule.write(90 + gauche_droite * increment_angle_bascule * i);
    }

    if (i >= pourcent_bascule / 2 - recoupement && i <= 100 - pourcent_bascule / 2 + recoupement) {
      int j = i - pourcent_bascule / 2 - recoupement;
      ServoAvance.write(90 + avant_arriere * gauche_droite * (increment_angle_avance * j - debattement_avance / 2));
    }

    if (i >= 100 - pourcent_bascule / 2) {
      int k = 100 - i;
      ServoBascule.write(90 + gauche_droite * increment_angle_bascule * k);
    }
    testStop();
    delay(duree_delay);
    if (i == 100) {
      pasTermine = true;
    }
    if (!onTourne) {
      radar();
    }
  }
}


//cette fonction vérifie si les conditions d'arret sont réalisées
//ces conditions sont un appui sur le bouton poussoir, une donnée arrivant du Bluetooth, ou la présence d'un obstacle à moins de 10 cm
void testStop()
{
  if (digitalRead(bouton_poussoire) || Serial.available() > 0 || distance < 10 && distance > 0) //  On teste si les conditions d'arret sont vraies
  {
    Stop = true;
    Serial.println("On arrete le robot");
  }
}
