/*
 Nom script : pm_gp2y10_qualite.ino
 Description : Mesure densite de particule fine avec un capteur SHART GP2Y10
               et indication de la qualite de l air
 Auteur : PHMARDUINO
 Date Creation : 20 mai 2018
 */

int pattecapteur=0;
int patteLEDIR=2;
int delai1=280;
int delai2=40;
float delaieteint=9680;
int mesure=0;
int dmicro;
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
  dmicro = densite *1000;
    
  Serial.print("Tension en volts : ");
  Serial.print(tension);
  Serial.print("  -  Densite particules (microg/m3) : ");
  Serial.print(dmicro);
  Serial.print(" - Qualite air : ");
  if (dmicro <= 35) Serial.println ("Excellent");
  if (dmicro >35 and dmicro <=75) Serial.println ("Moyen");
  if (dmicro >75 and dmicro <=115) Serial.println ("Pollution legere");
  if (dmicro >115 and dmicro <=150) Serial.println ("Pollution moderee");
  if (dmicro >150 and dmicro <=250) Serial.println ("Pollution importante");  
  if (dmicro >250 and dmicro <=500) Serial.println ("Pollution grave !!!!!");
    
  delay(1000);
}






