/******************************************************************************
Lecture temperature, pression atmospherique et humidite à l'aide
d'un capteur BME280
Code base sur les exemples de Sparkfun
Auteur : phmo
Date : 28 mai 2017
******************************************************************************/

#include <stdint.h>
#include "SparkFunBME280.h"
//Library pour I2C uniquement
#include "Wire.h"

//Creation d un objet monCapteur de type BME280
BME280 monCapteur;

void setup()
{
	monCapteur.settings.commInterface = I2C_MODE;
	monCapteur.settings.I2CAddress = 0x76;
	
	//Configuration du capteur//
	monCapteur.settings.runMode = 3;
	monCapteur.settings.tStandby = 0;
	monCapteur.settings.filter = 0;
	monCapteur.settings.tempOverSample = 1;
  monCapteur.settings.pressOverSample = 1;
	monCapteur.settings.humidOverSample = 1;
	
	Serial.begin(9600);
	Serial.println("Demarrage du BME280 ...");
	
	delay(10);  //Delai attente demarrage capteur, le BME280 demande 2ms pour démarrer.
  Serial.print("ID du capteur : ");
	Serial.println(monCapteur.begin(), HEX); // Chargement configuration

}

void loop()
{

	Serial.print("Temperature: ");
	Serial.print(monCapteur.readTempC(), 2);
	Serial.print(" degres C");

	Serial.print("\t Pression: ");
	Serial.print(monCapteur.readFloatPressure()/100, 2);
	Serial.print(" hPa");

	Serial.print("\t Humidite relative : ");
	Serial.print(monCapteur.readFloatHumidity(), 2);
	Serial.println(" %");

	delay(1000);

}
