#include <Arduino.h>
#include <SD.h>

#define sdCardPinChipSelect   53                          
#define nomDuFichier "temp.xls"

File monFichier;


// Broches
const int pinAnalog = A0; // Lecture analogique
const int pinDigital = 2; // Lecture numérique (si utilisé)

void setup() {
  Serial.begin(9600);       // Initialisation du port série
  pinMode(pinDigital, INPUT);

  Serial.println(F("Étape 1 : Initialisation de la carte SD :"));
  if (!SD.begin(sdCardPinChipSelect)) {
    Serial.println(F("Échec de l'initialisation !"));
    while (1);   
  }
  Serial.println(F("Initialisation terminée."));
  Serial.println();

  monFichier = SD.open(nomDuFichier, FILE_WRITE);
  if (monFichier) {
    monFichier.close();  // Fermer immédiatement le fichier
    Serial.println(F("Fichier de températures prêt à enregistrer."));
  } else {
    Serial.println(F("Échec de l'ouverture du fichier pour initialisation !"));
    while (1);
  }
  
}


void loop() {
  int valeurAnalogique = analogRead(pinAnalog); // Lecture analogique
  int etatDigital = digitalRead(pinDigital);   // Lecture numérique

  // Conversion en pourcentage (optionnel)
  float humidite = map(valeurAnalogique, 0, 1023, 100, 0);

  Serial.print("Humidité (analogique) : ");
  Serial.print(humidite);
  Serial.println("%");

  Serial.print("État (numérique) : ");
  Serial.println(etatDigital == HIGH ? "Sec" : "Humide");

  delay(1000); // Pause de 1 seconde
}
