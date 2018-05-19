/*
 Nom script : pm_gp2y10.ino
 Description : Mesure densite de particule fine avec un capteur SHART GP2Y10
 Auteur : PHMARDUINO
 Date Creation : 17 mai 2018
 */

int pattecapteur=0;
int patteLEDIR=2;
int delai1=280;
int delai2=40;
float delaieteint=9680;
int mesure=0;
float tension = 0;
float densite = 0;

void setup(){
  Serial.begin(9600);
  pinMode(patteLEDIR,OUTPUT);
}

void loop(){
  digitalWrite(patteLEDIR,LOW); // On allume la LED IR
  delayMicroseconds(delai1);
  mesure=analogRead(pattecapteur); // Lecture valeur capteur
  delayMicroseconds(delai2);
  digitalWrite(patteLEDIR,HIGH); // On eteint la LED IR
  delayMicroseconds(delaieteint);
  tension = mesure*5.0/1024;
  densite = 0.17*tension-0.09;
  if (densite < 0 )densite = 0;
  if (densite > 0.5) densite = 0.5;
    
  Serial.print("Tension en volts : ");
  Serial.print(tension);
  Serial.print("  -  Densite particules en mg par m3 : ");
  Serial.println(densite);
    
  delay(1000);
}






