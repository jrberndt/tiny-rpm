#include "Rpm-Tiny.h"
#include "Ringspeicher.h"
// #define DEBUG


const int Rpm_Signal_Pin          = 1;

const int Error_Taste_Pin     = 2;
const int Error_LED           = 3;
const int Watchdog_Taste_Pin  = 4;
const int Watchdog_LED        = 5;
const int Ready_Taste_Pin     = 6;
const int Ready_LED           = 7;

//-------------------------------------------------
void setup() {

  pinMode(Error_Taste_Pin , INPUT);
  pinMode(Error_LED , OUTPUT);

  pinMode(Watchdog_Taste_Pin , INPUT);
  pinMode(Watchdog_LED, OUTPUT);

  pinMode(Ready_Taste_Pin , INPUT);
  pinMode(Ready_LED, OUTPUT); 


  pinMode(LED_BUILTIN, OUTPUT);


  init_StatusLED();

  // DEBUG muss bei Bedarf eingeschaltet werden
  #ifdef DEBUG  
    Serial.begin(9600);
    while (!Serial) ;
    Serial.println("Programm startet nicht");
  #endif DEBUG

  pinMode(Rpm_Signal_Pin , INPUT);
}
//-------------------------------------------------

// 
unsigned long prevProbe_ms;
int Rpm_Signal;
int Rpm_Signal_alt;
float UproMinute;

/*           
 *        U
 * upm = ----- (Anzahl Schwingungen pro 60 Sek)
 *        t 
 *        
 *             1
 * freq = ---------- in Hz (Anzahl Schwingungen pro Sek.)
 *          periode
 *          
 * Periode (P) entspricht 1 Schwingung (U)
 * 
 *         1
 * upm = ----------------- * 60
 *     t (ms) * 1000 
 *
 * 
 */
float get_rpmTime( int Probe ) {

  unsigned long currentMillis = millis();

  Rpm_Signal_alt = Rpm_Signal;
  Rpm_Signal = digitalRead(Probe);
  if ( Rpm_Signal != Rpm_Signal_alt && Rpm_Signal == LOW ) {

    if ( millis() < prevProbe_ms ) { //Ueberlauf....
      currentMillis = sizeof(long) - 1 - prevProbe_ms;
    } else {
      currentMillis = millis() - prevProbe_ms;
    }
    
    return 60 / currentMillis / 1000;
  }
  
}






void loop() {

  UproMinute = get_rpmTime( Rpm_Signal_Pin );

  if ( !digitalRead(Error_Taste_Pin) )    { bitSet(Status,0); } else { bitClear(Status,0); }
  if ( !digitalRead(Watchdog_Taste_Pin) ) { bitSet(Status,1); } else { bitClear(Status,1); }
  if ( !digitalRead(Ready_Taste_Pin) )    { bitSet(Status,2); } else { bitClear(Status,2); }


  // Ausgabe der Programmzustaende  
  StausLED( Watchdog_LED );

}

/*
 *   Serial.print(!digitalRead(Error_Taste_Pin) ); Serial.print(!digitalRead(" - "));
  Serial.print(!digitalRead(Watchdog_Taste_Pin) ); Serial.print(!digitalRead(" - "));
  Serial.println  (!digitalRead(Ready_Taste_Pin) );
  
  Serial.println(Status,BIN);
*/




