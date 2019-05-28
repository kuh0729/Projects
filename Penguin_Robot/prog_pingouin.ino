/*
Le programme commence tout d'abord à exécuter le contenu de cet onglet avant de s'engager 
dans la fonction principale qui est la fonction loop()
Cette partie commence par la déclaration des variables utilisées dans chaque fonction
Vient ensuite la fonction setup () qui a pour but d'initialiser les différentes sorties et
entrées microcontroleur

Les différentes variables utilisées sont écrites dans la mémoire vive du microcontroleur.
on utilise les types de variable suivants:
byte ; entier codé sur 1 octet 
double ; réel signé codé sur 4 octets
bool ; booléen

L'opérateur #define remplace le texte qui le suit par la valeur entrée après ce texte dans 
tout le programme. cela permet d'avoir des constantes qui ne sont pas stockées dans la 
mémoire vive du microcontrôleur

On utilise la mémoire EEPROM pour stocker la valeur de nos variables principales que l'on 
pourra modifier par la suite dans la fonction choix_variables

*/
bool termine=false;




//library EEPROM, memoire morte qui enregistre des données accessibles après un redémarrage
#include <EEPROM.h>
//adresses des variables stockées dans l'EEPROM
#define adresseKp 256 
#define adresseKi 257
#define adresseRecoupement 258
#define adresseDebAvance 259
#define adresseDebBascule 260
#define adresseDureeAvance 261
#define adresseDureeBascule 262
byte entier_lu = 0;


//lecture des variables préalablement enregistrées dans l'EEPROM
byte  recoupement = EEPROM.read(adresseRecoupement);  //en %
byte  debattement_avance_init = EEPROM.read(adresseDebAvance);  //en °
byte  debattement_bascule = EEPROM.read(adresseDebBascule);
double  duree_avance = 0.1 * EEPROM.read(adresseDureeAvance); //en s
double  duree_bascule = 0.1 * EEPROM.read(adresseDureeBascule);


//fonction boussole
double Kp = EEPROM.read(adresseKp);
double Ki = 0.1 * EEPROM.read(adresseKi);

//fonction avance
//calcul des variables utilisées par le programme à partir des variables entrées par l'utilisateur (plus simples et intuitives à utiliser)
double duree_pas = 50 * (duree_avance + duree_bascule) / (50 + recoupement); //en secondes DA+DB-2DR=DP ; (RE/100)*DP=DR ; DP=(DA+DB*50/(50+Re)
double duree_delay = duree_pas * 10; //en ms par % DD=1000/100DP
double pourcent_avance = duree_avance / duree_pas * 100;
double pourcent_bascule = duree_bascule / duree_pas * 100;
double increment_angle_bascule = debattement_bascule / pourcent_bascule;
double increment_angle_avance;
byte debattement_avance;


//library magnétometre
#include <Wire.h>   //Librairie Wire pour la communication I2C
#define HMC5803L_Address 0x1E  //Adresse I2C du module

#define X 3  //Adresses de registres pour les données X Y et Z
#define Y 7
#define Z 5
double Xmagnetic;
double Ymagnetic;
double Zmagnetic;
double angle_boussole;
double angle_initial = 0;
double rectification;
double erreur;
double correction_integrale = 0;
double correction_proportionnelle;


//library servo
#include <Servo.h>
//déclaration des 3 servos
Servo ServoAvance;
Servo ServoBascule;
Servo ServoRadar;


//Pins
#define buzzer 8
#define led1  7
#define led2  5
#define bouton_poussoire 6
#define trigPin 4
#define echoPin 2
#define nivBat A0


//Radar
#define LR 8  //largeur robot
#define s 4  // largeur de sécurité
double duration;
double distance = 34;
byte angle = 90;
byte HB = 1; //definit le sens de rotation du moteur radar


//loop
byte avant_arriere = 1;
byte gauche_droite = 1;
#define avant 1       //valeurs a verifier
#define arriere -1
#define gauche 1
#define droite -1
byte mode = 0;
bool start, Stop;


// tourner
bool pasTermine = false ;
bool geleradar = false;
bool onTourne = false;




void setup() {
  //initialisation du protocole UART pour communication bluetooth
  Serial.begin(9600);

  //initialisation du protocole I2C pour communication Boussole
  Wire.begin();
  Init_HMC5803L();

  //initialisation des pins
  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, HIGH);

  pinMode(led1, OUTPUT);
  digitalWrite(led1, LOW);

  pinMode(led2, OUTPUT);
  digitalWrite(led2, LOW);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  digitalWrite(bouton_poussoire, INPUT);


  ServoAvance.attach(9);
  ServoBascule.attach(10);
  ServoRadar.attach(3);
  
//mise en position des servomoteurs
  ServoAvance.write(90 + avant * ( - gauche * debattement_avance_init / 2));
  ServoBascule.write(90);
  ServoRadar.write(90);
}
