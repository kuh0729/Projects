/*
Cette fonction vérifie si la tension de la batterie est en dessous du niveau critique 
si c'est le cas, on allume le buzzer afin d'en informer l'utilisateur
*/

void verifierTensionBatterie()
{

  if (analogRead(nivBat) < 830) { // on vérifie si la tension de la batterie est inférieure au seuil fixé
    digitalWrite(buzzer, LOW); //on allume le buzzer c'est le cas (le buzzer fonctionne à l'état bas)

  }
  else {
    digitalWrite(buzzer, HIGH);
  }
}
