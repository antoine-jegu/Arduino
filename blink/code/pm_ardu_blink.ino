void setup()
{
Serial.begin(9600);
pinMode( 13 , OUTPUT);
}

void loop()
{
Serial.print( "Allumage de la LED" );
Serial.println("");
digitalWrite( 13 , HIGH );
delay( 1000 );
Serial.print( "Extinction de la LED" );
Serial.println("");
digitalWrite( 13 , LOW );
delay( 1000 );
}


