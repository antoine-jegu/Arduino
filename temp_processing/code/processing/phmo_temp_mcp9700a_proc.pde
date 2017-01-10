///////////////////////////////////////////////////////////////////////////////////////////
// Objet  : Affichage temperature sous forme graphique                                   //
// Nom skecth : phmo_temp_mcp9700a.pde                                                       //
// Auteur : phmo                                                                          //
// Création : Le 29 aout 2011                                                       //
// Mise à jour : Le 28 octobre 2011, 10 jan 2017                                        //
///////////////////////////////////////////////////////////////////////////////////////////

 //Import de la librairie communication serie
 import processing.serial.*;
 
 //Initialisation des variables
 Serial monPort;  //Déclatation port série pour la lecture des données envoyées par l'Arduino
 int mesure;      //Mesure lue sur le port 

//Initialisation des variables

 int temperature=25;      //Temperature mesurée par l'Arduino
 int tempmini=34;         //Temperature mini mesurée par l'Arduino
 int tempmax=12;          //Temperature maxi mesurée par l'Arduino
 int j;           //Indice de travail
 int k;           //Indice de travail
 int x=0;         //Abcisse
 int x0=0;        //Abcisse précédente
 int y=0;         //Ordonnée
 int y0;          //Ordonnée précédente
 PImage thermometre;
 PFont police;

//Traitements d'initialisation
void setup() {
  
 //Initialisations port série
 println(Serial.list());    // Affichage dans la console de la liste des ports serie du PC
 //Le nom du port ici COM10 doit être adapté en fonction de votre contexte
 monPort = new Serial(this, "COM10", 9600);   //Initialisation de la communicaiton port serie
 monPort.bufferUntil('\n'); //Attend la réception d'un fin de ligne pour généer un serialEvent() 
 
 //Initialisatiopns graphiques
 size (1000,610);
 background(#9FB84D);
 smooth();  //On active le lissage

 //Dessin des cadres -------------------------
 stroke(0);
 strokeWeight(1);
 fill(230);
 rect (20,20,210,500); //Thermometre
 rect (20,525,210,65); //Textes
 rect (240,20,750,500); //Courbe historique

 //Dessin des titres  -------------------------
 fill(255,0,0);
 text("Température instantanée", 35, 40);
 text("Historique température", 520, 40);
 fill(0,0,255);

 textSize (42);
 text("Suivi température", 420, 570);
 textSize (12);


 //Dessin du thermomètre -----------------------
 fill(50);
 noStroke();
 rect(100,70,20,420);
 ellipse(110, 490, 40, 40);

 //Dessin du réservoir
 ellipse(110, 70, 20, 20);
 fill(#0BB305);
 ellipse(110, 490, 30, 30);

 //Gradations et textes tous les 5 degrés
 fill(50);
 strokeWeight(2);
 stroke(50);

 //à gauche
 for (int i = 0; i < 11; i++) {
      j=i*40;
      k=i*5;
      line(90, 475-j, 100,475-j);
      text(k+" °C", 50, 475-j);
  }

 //à droite
 for (int i = 0; i < 11; i++) {
      j=i*40;
      k=i*5;
      line(120, 475-j, 130,475-j);
      text(k+" °C", 140, 475-j);
 }

 //Gradations fines des degrés
 
 //à gauche
 strokeWeight(1);
 stroke(50);
 for (int i = 0; i < 50; i++) {
         j=i*8;
         line(95, 475-j, 100,475-j);
 }
 
 //à droite
 strokeWeight(1);
 stroke(50);
 for (int i = 0; i < 50; i++) {
          j=i*8;
          line(120, 475-j, 125,475-j);
 }

 //Affichage courbe -----------------------

 //Tracé des axes
 fill(0,0,255);
 stroke(#0650E4);
 strokeWeight(2);
  
 //horizontal
 line (290,475,960,475);
 triangle(960, 475, 950, 480, 950, 470);
 text("Température (°C)", 250, 40);
 
 //vertical
 line (290,475,290,50);
 triangle(290, 50, 295, 60, 285, 60);
 text("Temps", 910, 510);

 //Gradations et textes tous les 5 degrés
 fill(0,0,255);
 strokeWeight(2);
 stroke(#0650E4);
 for (int i = 0; i < 11; i++) {
     j=i*40;
     k=i*5;
     line(285, 475-j, 290,475-j);
     text(k, 260, 480-j);
 }

 //Gradations fines des degrés
 strokeWeight(1);
 stroke(#0650E4);
 for (int i = 0; i < 50; i++) {
          j=i*8;
          line(285, 475-j, 290,475-j);
 }

 //Gradations des minutes
 strokeWeight(2);
 for (int i = 0; i < 11; i++) {
          j=i*60;
          line(290+j, 475, 290+j,480);
          text(i, 295+j, 490);
 }

}

//Traitements itératifs 
 void draw() {
        // Pas de traitement car tout est réalisé dans la fonction serialEvent()

   }

//Traitements à réception d'une fin de ligne
 void serialEvent (Serial monPort) {
 
 //Récupération sur le port série de la tension sous forme de chaine de caractères
 
 String tensionCar = monPort.readStringUntil('\n');
 if (tensionCar != null) {
      tensionCar = trim(tensionCar); // Suppression des blancs
      int tensionNum = int(tensionCar);  // Conversion tensoin en caractères en décimal et calcul température
      float temperature = 1000 * tensionNum * 1.1 / 1024;
      int tempInt = int(temperature);
      println ("La temperature est de : " + temperature + " degrés : " + tempInt);
 
      //Dessin graphe avec temperature actuelle -----------------------
      stroke (0,255,0);
      strokeWeight(1);
  
      //dessin du nouveau point sur la courbe
      x0=x; // Mémorisation abscisse point précédent
      x=x+5; // L'Arduino envoie une nouvelle mesure de température toutes les 5 secondes
      if (x >600) {x=5;}
    
      y0=y; // Mémorisation ordonnée point précédent
      y = tempInt*8; // Un degré correpond à 8 points sur les ordonnées
    
      if (y > tempmax*8)  {tempmax = y/8;} //Mise à jour temp max
      if (y < tempmini*8) {tempmini = y/8;} //Mise à jour temp min
    
      if (x == 5) {   //Si on rédémarre une nouvelle courbe
        noStroke();
        fill(230);
        rect(291,65,655,410); //Effacement courbe précédente
        point(x+287,475-y);
      }
      else {
        line(x0+287,475-y0,x+286,475-y);
      }
  
      //Dessin thermometre avec temperature actuelle -----------------------
      temperature=y/8;
      noStroke();
      fill(#0BB305);
      rect(105,475-temperature*8,10,temperature*8+5);
      fill(#08F500);
      rect(110,480-temperature*8,3,temperature*8-5);
    
      //Affichage des températures ----------------
    
      //Dessin des cadres -------------------------
      stroke(0);
      strokeWeight(1);
      fill(230);
      rect (20,525,210,65);
    
      //Dessin du thermomètre -----------------------
      fill(50);
      noStroke();
      rect(100,70,20,420);
      ellipse(110, 490, 40, 40);
    
      // Dessin du réservoir
      ellipse(110, 70, 20, 20);
      fill(#0BB305);
      ellipse(110, 490, 30, 30);
    
      //Dessin temperature actuelle -----------------------
      noStroke();
      fill(#0BB305);
      rect(105,475-temperature*8,10,temperature*8+5);
      fill(#08F500);
      rect(110,480-temperature*8,3,temperature*8-5);
    
      noStroke();
      fill(230);
      rect(160,500,70,20); //effacement texte précédent heure
      rect(25,500,60,20); //effacement texte précédent date
      fill(0,0,255);
      text(hour()+" : "+minute()+" : "+second(), 160, 514);
      text(day()+" / "+month()+" / "+year(), 25, 514);
    
      //Textes
      fill(0,0,255);
      text("Température actuelle :", 40, 540);
      text("Température mini :", 40, 560);
      text("Température max :", 40, 580);
      textAlign(RIGHT);
      fill(#0BB305);
      text(temperature+" °C", 220, 540);
      fill(0,0,255);
      text(tempmini+" °C", 220, 560);
      fill(255,0,0);
      text(tempmax+" °C", 220, 580);
      textAlign(LEFT);
   
   }
 }
