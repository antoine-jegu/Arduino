/**************************************************************************** 
  Auteur : phmarduino
  Sketch : mq2_calcul_r0.ino
  Date : 31/8/2017 
  Description : Calcul R0 en Kohms du detecteur de gaz combustible MQ2
                Un préchauffage du capteur de 24 heures est nécessaire
                pour avoir une mesure fiable de R0
****************************************************************************/
void setup() {
    Serial.begin(9600);
}

void loop() {
    float mesure = 0; // Mesure numerique brute VOUT
    float tension;    // VOUT en volts au bornes de RL en sortie du pont diviseur
                      // forme de RS (resistance capteur) et RL (resistance de charge)
    float RS_air;     // Valeur resistance capteur RS capteur dans de l air pur
    float R0;         // Resistance capteur RS pour 1000ppm de H2 dans un air pur
                      // Pour le calcul ulterieur concentration gaz en ppm
                      // L'objectif de ce sketch est de calculer cette valeur

    /*--- moyenne sur 100 mesures de VOUT ---*/
    for(int x = 0 ; x < 10 ; x++)
    {
        mesure = mesure + analogRead(A0);
    }
    mesure = mesure/10.0;
    /*-----------------------------------------------*/

    tension = (mesure/1023)*5.0;
    RS_air = (5.0-tension)/tension; // Pont diviseur avec RL = 1 Kohm
    R0 = RS_air/9.8;     // Le ratio RS/R0 est de 9.8 pour l'air (sans gaz)
                         // comme indique dans le datasheet

    Serial.print("Mesure = ");
    Serial.print(mesure);
    Serial.print(" - ");

    Serial.print("Tension = ");
    Serial.print(tension);
    Serial.print("V - ");

    Serial.print("R0 en Kohms = ");
    Serial.println(R0);
    delay(2000);

}
