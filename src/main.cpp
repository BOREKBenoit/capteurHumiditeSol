#include <Arduino.h>
#include <SD.h>
#include <Wire.h>
#include <DHT.h>
#include <Adafruit_Sensor.h>

#define sdCardPinChipSelect   53                          
#define humiditeSol "sol.xls"
#define humiditeAir "hair.xls"
#define temperatureAir "tair.xls"

File humideSol;
File humideAir;
File tempAir;

#define DHTPIN 3
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);


// Broches
const int pinAnalog = A0; // Lecture analogique
const int temperature = 3; // Lecture numérique (si utilisé)


void setup() {
  dht.begin();
  
  Serial.begin(9600);       // Initialisation du port série

  pinMode(temperature, INPUT);


  Serial.println("///////INITIALISATION///////////////");
  Serial.println("///////CAPTEUR D'HUMIDITE, TEMPERATURE ET SOL ///////////////");
  delay(500);

  Serial.println(F("Étape 1 : Initialisation de la carte SD :"));
  if (!SD.begin(sdCardPinChipSelect)) {
    Serial.println(F("Échec de l'initialisation !"));
    while (1);   
  }
  Serial.println(F("Initialisation terminée."));
  Serial.println();

  delay(1000);

  humideSol = SD.open(humiditeSol, FILE_WRITE);
  if (humideSol) {
    humideSol.close();  // Fermer immédiatement le fichier
    Serial.println(F("Fichier de capture du sol prêt à enregistrer."));
  } else {
    Serial.println(F("Échec de l'ouverture du fichier pour initialisation !"));
    while (1);
  }

  delay(1000);

  humideAir = SD.open(humiditeAir, FILE_WRITE);
  if (humideAir) {
    humideAir.close();  // Fermer immédiatement le fichier
    Serial.println(F("Fichier de capture de l'humidité de l'air prêt à enregistrer."));
  } else {
    Serial.println(F("Échec de l'ouverture du fichier pour initialisation !"));
    while (1);
  }
  delay(1000);
  tempAir = SD.open(temperatureAir, FILE_WRITE);
  if (tempAir) {
    tempAir.close();  // Fermer immédiatement le fichier
    Serial.println(F("Fichier de capture de la température de l'air prêt à enregistrer."));
  } else {
    Serial.println(F("Échec de l'ouverture du fichier pour initialisation !"));
    while (1);
  }
  delay(1000);
  Serial.println("////////FIN INITIALISATION//////////////");
  delay(500);
}





void loop() {
  


  // Lire la température
    float temp = dht.readTemperature();  // Lire la température en Celsius
    float hum = dht.readHumidity();  // Lire l'humidité en %

    if (isnan(temp)) {
      Serial.println(F("Échec de la lecture de la température!"));
      while(1);
      
  
    }
    if (isnan(hum)) {
      Serial.println(F("Échec de la lecture de l'humidité!"));
      while(1);
    }

  int valeurAnalogique = analogRead(pinAnalog); // Lecture analogique
  // Conversion en pourcentage (optionnel)
  int sol = map(valeurAnalogique, 0, 1023, 100, 0);
 // Serial.print("Valeur brute analogique : "); Pour deboguage en cas de bug
  //Serial.println(valeurAnalogique);











  

   humideSol = SD.open(humiditeSol, FILE_WRITE);
    if (humideSol) {
      humideSol.print(sol);  // Enregistrer la température
      humideSol.println();  // Ajouter un retour à la ligne
      humideSol.close();    // Fermer le fichier
      Serial.print(F("Humidité du sol enregistrée: "));
      Serial.println(sol);
    } else {
      Serial.println(F("Erreur d'ouverture du fichier pour l'écriture !"));
    }


     humideAir = SD.open(humiditeAir, FILE_WRITE);
    if (humideAir) {
      humideAir.print(hum);  // Enregistrer la température
      humideAir.println();  // Ajouter un retour à la ligne
      humideAir.close();    // Fermer le fichier
      Serial.print(F("Humidité de l'air enregistrée: "));
      Serial.println(hum);
    } else {
      Serial.println(F("Erreur d'ouverture du fichier pour l'écriture !"));
    }


     tempAir = SD.open(temperatureAir, FILE_WRITE);
    if (tempAir) {
      tempAir.print(temp);  // Enregistrer la température
      tempAir.println();  // Ajouter un retour à la ligne
      tempAir.close();    // Fermer le fichier
      Serial.print(F("Température enregistrée: "));
      Serial.println(temp);
    } else {
      Serial.println(F("Erreur d'ouverture du fichier pour l'écriture !"));
    }



  delay(5000); // Pause de 5 secondes
}


