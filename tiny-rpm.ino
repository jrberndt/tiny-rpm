#include <RingBufCPP.h>
#include <RingBufHelpers.h>

#include "Rpm-Tiny.h"
// #define DEBUG


const int RPM_SIGNAL_PIN          = 0;
const int LED__BUILTIN            = 1;   // beim Digispark ist die LED auf 1


//-------------------------------------------------
void setup() {

  pinMode(LED__BUILTIN, OUTPUT);

  init_StatusLED();

  // DEBUG muss bei Bedarf eingeschaltet werden
  #ifdef DEBUG  
    Serial.begin(9600);
    while (!Serial) ;
    Serial.println("Programm startet nicht");
  #endif DEBUG

  pinMode(RPM_SIGNAL_PIN , INPUT);
}
//-------------------------------------------------


void loop() {

  UproMinute = get_rpmTime( RPM_SIGNAL_PIN );



  // Ausgabe der Programmzustaende  
  StatusLED( LED__BUILTIN );

}

/*
 *   Serial.print(!digitalRead(Error_Taste_Pin) ); Serial.print(!digitalRead(" - "));
  Serial.print(!digitalRead(Watchdog_Taste_Pin) ); Serial.print(!digitalRead(" - "));
  Serial.println  (!digitalRead(Ready_Taste_Pin) );
  
  Serial.println(Status,BIN);
*/




