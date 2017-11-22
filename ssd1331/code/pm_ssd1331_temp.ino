//Programme   : Affichage temperature, pression, humidite 
//              sur ecran OLED couleur SSD1331 mesure avec
//              un capteur BME280
//Auteur      : PHMARDUINO
//Date        : Le 21 11 2017
//Commentaire : Base sur les sources ADAFRUIT ET SPARKFUN

#include <stdint.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1331.h>
#include "SparkFunBME280.h"
#include "Wire.h"
#include <SPI.h>

//Instanciation dun objet de type BME280
BME280 mySensor;

//Definition pattes ecran oled SSD1331
#define sclk 13
#define mosi 11
#define cs   10
#define rst  9
#define dc   8

//Definition des couleurs
#define BLACK           0x0000
#define BLUE            0x001F
#define RED             0xF800
#define GREEN           0x07E0
#define CYAN            0x07FF
#define MAGENTA         0xF81F
#define YELLOW          0xFFE0
#define WHITE           0xFFFF

//Initilisalisation ecran Oled
Adafruit_SSD1331 display = Adafruit_SSD1331(cs, dc, rst);

// Declaration des variables pour les mesures
  float temp;   //Variable stockage température
  float pres;   //Variable stockage pression 
  float hum;    //Variable stockage humidite  

void setup(void)
{
  mySensor.settings.commInterface = I2C_MODE;
  mySensor.settings.I2CAddress = 0x76;
  mySensor.settings.runMode = 3; //Normal mode
  mySensor.settings.tStandby = 0;
  mySensor.settings.filter = 0;
  mySensor.settings.tempOverSample = 1;
  mySensor.settings.pressOverSample = 1;
  mySensor.settings.humidOverSample = 1;
  
  Serial.begin(57600);
  Serial.print("Demarrage du BME280...");
  
  delay(10);  //On laisee au BME280 le temps de demarrer, a minima 2ms
  Serial.println(mySensor.begin(), HEX);
  
  //Informations initiales a afficher
  display.begin();
  display.fillScreen(BLACK);
  
  display.fillRect(0, 0, 96, 15, YELLOW);
  display.drawRect(0, 0, 96, 15, WHITE);
  
  display.fillRect(0, 16, 96, 15, WHITE);
  display.drawRect(0, 16, 96, 15, BLUE);

  display.fillRect(0, 32, 96, 15, WHITE);
  display.drawRect(0, 32, 96, 15, BLUE);

  display.fillRect(0, 48, 96, 15, WHITE);
  display.drawRect(0, 48, 96, 15, BLUE);
  

  display.setTextSize(1);
  display.setTextColor(BLUE);
  display.setCursor( 20, 5 );
  display.print( "MESURES" );
}

void loop(void)
{
  //Lecture donnees
  Serial.print("Temperature : ");
  temp = mySensor.readTempC();
  Serial.print(temp, 2);
  Serial.println(" degres C");

  Serial.print("Pression : ");
  pres = mySensor.readFloatPressure()/100.0;
  Serial.print(pres, 2);
  Serial.println(" hPa");

  Serial.print("%RH : ");
  hum = mySensor.readFloatHumidity();
  Serial.print(hum, 2);
  Serial.println(" %");
  
  Serial.println();

  //Actualisation affichage

  display.fillRect(0, 16, 96, 15, WHITE);
  display.fillRect(0, 32, 96, 15, WHITE);
  display.fillRect(0, 48, 96, 15, WHITE);
  display.setTextSize(1);
  display.setTextColor(RED);
  display.setCursor( 3, 20 );
  display.print("T: ");
  display.setCursor( 3, 36 );
  display.print("P: ");
  display.setCursor( 3, 52 );
  display.print("H: ");
  
  display.setCursor( 17, 20 );
  display.print( temp );
  display.setCursor( 17, 36 );
  display.print( pres );
  display.setCursor( 17, 52 );
  display.print( hum );

  display.setCursor( 65, 20 );
  display.print("deg C");
  display.setCursor( 65, 36 );
  display.print("hPa");
  display.setCursor( 65, 52 );
  display.print("%");

  delay(1000);
}


