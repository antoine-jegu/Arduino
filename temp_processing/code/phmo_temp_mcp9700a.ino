/* 
Objet : Mesure temperature avec un Microchip MCP9700A
Nom : phmo_temp_mcp9700A.ino
Infos sketch : 
 - Créé en 2015 le 08 12 par PHMO
 - Modifié le 10 janvier 2016
*/

#define PatteTemp 0 // La température est mesurée sur l entrée analogique A0
#define Tension 5 // La tension mesurée est de 5v lorsque le CAN (convertisseur) retourne 1023

float temperature;
float tension;

void setup() {
  Serial.begin(9600);
}

void loop () {
  tension = analogRead(PatteTemp)*Tension/1023.0;
  tension = tension - 0.5; // On enlève l'offset (décalage) de 5 mv retourné à 0 degré C
  temperature = tension / 0.01; // 10 mv soit 0,01 volt = 1 degré
  Serial.println(temperature); // Envoi de la température sur l'interface série pour Processing
  delay(500); // On attend 500 ms avant de faire une nouvelle mesure
}
