/**************************************************************************** 
  Auteur : phmarduino
  Sketch : mq2_reg_sensib_dout.ino
  Date : 31/8/2017 
  Description : Reglage de la sensibilté seuil DOUT avec potentiometre
****************************************************************************/
void setup() {
    pinMode(12,INPUT);
    Serial.begin(9600);
}

void loop() {
    float mesure = 0; // Mesure numerique brute VOUT
    float tension;    // VOUT en volts au bornes de RL en sortie du pont diviseur
                      // forme de RS (resistance capteur) et RL (resistance de charge)
    float RS;          // Valeur resistance capteur RS
    float R0 = 2 ;   // Resistance capteur RS pour 1000ppm de H2 dans un air pur
    float RS_R0;

    /*--- moyenne sur 10 mesures de VOUT ---*/
    for(int x = 0 ; x < 10 ; x++)
    {
        mesure = mesure + analogRead(A0);
    }
    mesure = mesure/10.0;
    /*-----------------------------------------------*/
    int DOUT = digitalRead(12);
    tension = (mesure/1023)*5.0; // en volts
    RS = (5.0-tension)/tension; // en kilo ohms cf RL = 1 kilo
    RS_R0 = RS/R0;

    Serial.print("Mesure = ");
    Serial.print(mesure);
    Serial.print(" - ");

    Serial.print("Tension = ");
    Serial.print(tension);
    Serial.print("V - ");

    Serial.print("RS en Kohms = ");
    Serial.print(RS);
    
    Serial.print(" - Ratio RS/R0 = ");
    Serial.print(RS_R0);

    Serial.print(" - DOUT = ");
    Serial.println(DOUT);
    
    delay(200);

}
