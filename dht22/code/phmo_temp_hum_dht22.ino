/* 
Objet : Mesure temperature et hygrometrie avec un capteur dht22
Nom : phmo_temp_humi_dht22.ino
Infos sketch : 
 - Créé le 10 jan 2017
*/

#include "DHT.h" // ajout de la bibliothèque DHT

#define DHTPIN 7        // patte de l'arduino sur laquelle se fait la mesure
#define DHTTYPE DHT22   // type de sonde

DHT dht(DHTPIN, DHTTYPE); // instanciation objet dht

void setup() {
Serial.begin(9600); // ouverture connexion serie
Serial.println("Tets DHT22 ----------------------");  //

dht.begin(); 
}

void loop() {

float h = dht.readHumidity();    // lecture humidité et affectation a une variable de type float
float t = dht.readTemperature(); // lecture température et affectation a une variable de type float

// test si retour sonde dht2  ok ou pas ...
if (isnan(t) || isnan(h)) {
Serial.println("Erreur de lecture sonde dht22");
} else {
//affichage des donnees sur la console serie
Serial.print("Humidite : " ); 
Serial.print(h);
Serial.print( " %\t ");
Serial.print(" Temperature : " );
Serial.print(t);
Serial.println(" C ");
delay(1000); // attente de 1 seconde avant de refaire une mesure
}

}
