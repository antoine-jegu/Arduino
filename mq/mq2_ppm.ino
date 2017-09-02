/**************************************************************************** 
  Auteur : phmarduino
  Date:30/8/2017 
  Description : Detection de gaz combustible avec un capteur MQ2 
  Inspire des sources suivants :
  http://www.instructables.com/id/How-to-Detect-Concentration-of-Gas-by-Using-MQ2-Se/
  http://sandboxelectronics.com/?p=165
****************************************************************************/


/************************Hardware Related Macros************************************/

const int calibrationLed = 13;       // Sortie pour la LED indiquant un calibrage en cours
const int MQ_PIN=A0;                 // Entree analogique mesure tension retournee par le capteur
int RL_VALUE=1;                      // Load resistance en kilo ohms
float RO_CLEAN_AIR_FACTOR=9.8;      // RO_CLEAR_AIR_FACTOR = RS/RO avec air pur déduit du datasheet
 
/***********************Software Related Macros************************************/
int CALIBRATION_SAMPLE_TIMES=50;                    //define how many samples you are going to take in the calibration phase
int CALIBRATION_SAMPLE_INTERVAL=500;                //define the time interal(in milisecond) between each samples in the
                                                    //cablibration phase
int READ_SAMPLE_INTERVAL=50;                        //define how many samples you are going to take in normal operation
int READ_SAMPLE_TIMES=5;                            //define the time interal(in milisecond) between each samples in 
                                                    //normal operation
 
/**********************Application Related Macros**********************************/
#define         GAS_LPG             0   
#define         GAS_CO              1   
#define         GAS_SMOKE           2    
 
/*****************************Globals***********************************************/
float           LPGCurve[3]  =  {2.3,0.21,-0.47};   //two points are taken from the curve. 
                                                    //with these two points, a line is formed which is "approximately equivalent"
                                                    //to the original curve. 
                                                    //data format:{ x, y, slope}; point1: (lg200, 0.21), point2: (lg10000, -0.59) 
float           COCurve[3]  =  {2.3,0.72,-0.34};    //two points are taken from the curve. 
                                                    //with these two points, a line is formed which is "approximately equivalent" 
                                                    //to the original curve.
                                                    //data format:{ x, y, slope}; point1: (lg200, 0.72), point2: (lg10000,  0.15) 
float           SmokeCurve[3] ={2.3,0.53,-0.44};    //two points are taken from the curve. 
                                                    //with these two points, a line is formed which is "approximately equivalent" 
                                                    //to the original curve.
                                                    //data format:{ x, y, slope}; point1: (lg200, 0.53), point2: (lg10000,  -0.22)                                                     
float           Ro           =  10;                 //Ro is initialized to 10 kilo ohms


void setup()
{ 
  
  Serial.begin(9600);
  pinMode(calibrationLed,OUTPUT);
  digitalWrite(calibrationLed,HIGH);

  Serial.println("Calibrage en cours (le capteur doit etre dans un air pur sans gaz) ...");                       

  
  Ro = MQCalibration(MQ_PIN);           // Lancement du calibrage avec de l air pur         
  digitalWrite(calibrationLed,LOW);     // Calibrage termine        
  
  Serial.println("Calibrage termine ... ");                                
  Serial.print("Ro= ");
  Serial.print(Ro);
  Serial.println("kohm");
  delay(3000);
}
 
void loop()
{  
  long iPPM_LPG = 0;
  long iPPM_CO = 0;
  long iPPM_Smoke = 0;

  iPPM_LPG = MQGetGasPercentage(MQRead(MQ_PIN)/Ro,GAS_LPG);
  iPPM_CO = MQGetGasPercentage(MQRead(MQ_PIN)/Ro,GAS_CO);
  iPPM_Smoke = MQGetGasPercentage(MQRead(MQ_PIN)/Ro,GAS_SMOKE);

   Serial.print("Concentrations en >  ");
   
   Serial.print("Gaz combustible : ");
   Serial.print(iPPM_LPG);
   Serial.print(" ppm - ");   
   
   Serial.print("CO : ");
   Serial.print(iPPM_CO);
   Serial.print(" ppm - ");    

   Serial.print("Fumee : ");
   Serial.print(iPPM_Smoke);
   Serial.println(" ppm");  

   delay(200);
  
}
 
/****************** MQResistanceCalculation ****************************************/
// Calcul de la restistance RS du capteur dependant de la concentration en gaz
// avec la formule du pont diviseur de tension
float MQResistanceCalculation(int raw_adc)
{
  return ( ((float)RL_VALUE*(1023-raw_adc)/raw_adc));
}
 
/***************************** MQCalibration ****************************************/
// Calcul initilal de R0 sachant que RS/R0 egal à environ 9.83 en l absence de gaz
// comme indique dans le datasheet du MQ2
float MQCalibration(int mq_pin)
{
  int i;
  float val=0;

  for (i=0;i<CALIBRATION_SAMPLE_TIMES;i++) {            
    val += MQResistanceCalculation(analogRead(mq_pin));
    delay(CALIBRATION_SAMPLE_INTERVAL);
  }
  val = val/CALIBRATION_SAMPLE_TIMES;         
  val = val/RO_CLEAN_AIR_FACTOR;                                                      
  return val;                                  
}
 
/*****************************  MQRead *********************************************/
float MQRead(int mq_pin)
{
  int i;
  float rs=0;
  for (i=0;i<READ_SAMPLE_TIMES;i++) {
    rs += MQResistanceCalculation(analogRead(mq_pin));
    delay(READ_SAMPLE_INTERVAL);
  }
  rs = rs/READ_SAMPLE_TIMES;
  return rs;  
}
 
/*****************************  MQGetGasPercentage **********************************/
long MQGetGasPercentage(float rs_ro_ratio, int gas_id)
{
  if ( gas_id == GAS_LPG ) {
     return MQGetPercentage(rs_ro_ratio,LPGCurve);
  } else if ( gas_id == GAS_CO ) {
     return MQGetPercentage(rs_ro_ratio,COCurve);
  } else if ( gas_id == GAS_SMOKE ) {
     return MQGetPercentage(rs_ro_ratio,SmokeCurve);
  }    
 
  return 0;
}
 
/*****************************  MQGetPercentage **********************************/
long  MQGetPercentage(float rs_ro_ratio, float *pcurve)
{
  return (pow(10,( ((log10(rs_ro_ratio)-pcurve[1])/pcurve[2]) + pcurve[0])));
}

