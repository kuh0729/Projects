/*
La fonction mode1 fait appel aux différentes fonctions nécessaires pour réaliser l'avance correctement

Après avoir attendu 3 secondes, l'angle de la boussole est initialisé pour la correction intégrale proportionnelle,
puis on effectue un pas à gauche puis à droite ainsi que la correction réalisée par la boussole et la vérification 
de la tension de la batterie tant que les conditions d'arret ne sont pas satisfaites

*/



void mode1() {
  delay(2300);
  //mesure initiale de l'orientation du champ magnétique
  angle_initial = 0; //il faut que l'angle soit nul car il est utilisé dans boussole()
  boussole();
  angle_initial = boussole();

  while (!Stop) {

    avance(gauche, avant);
    avance(droite, avant);
    correction();
    verifierTensionBatterie();
  }
}


