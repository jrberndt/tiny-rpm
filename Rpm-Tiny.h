#ifndef Rpm-Tiny_h
#define Rpm-Tiny_h

#include "Arduino.h"
/**************************************************************************************
	Author: J.Berndt
	Datum:	06-2017
***************************************************************************************/

int Status;   // hier werden die jeweiligen Fehler ODER-Verknüpft

void StausLED( int LEDPin = LED_BUILTIN);
int fkt_Interval(unsigned long *pTimer, long _Interval );
void blink(unsigned long *pTimer, long _Interval, int _LED, int _PulsePause = 1 );

/**************************************************************************************
 * Author: J.Berndt
 * Datum:  06.2017
 * 
 * Ansteuerung der Meldungs-LED
 * es soll nur eine LED als Rückmeldung für alle Programmzustände genutzt werden z.B.:
 * Bereit -> 0,5Hz
 * Fehler -> 2,0Hz
 * 
 * über die Variable "Status" wird der Takt der LED gesteuert
 * 
 * die Variable Status wird bitweise mit den MSG_... Konstanten verknüpft
 * -> die niedrigste setzt sich durch.
 * 
 * Status wird im Prg folgendermassen gesetzt (ODER-verknueft):
 *  Status = Status | MSG_ERROR;
 *  
 **************************************************************************************/

const unsigned long ERROR_MS = 100;   // halbe Blinkzeit (bei PP_.. = 1) in ms 
const int MSG_ERROR = 0x1;            // Bitmaske 
const int PP_ERROR = 10;              // Puls-Pausen-Verhaeltnis
unsigned long prevError_ms;           // Zwischenspeicher zur Zeitberechnung

const unsigned long WATCHDOG_MS = 250;
const int MSG_WATCHDOG = 0x2;
const int PP_WATCHDOG = 10;
unsigned long prevWD_ms;

const unsigned long FREI_MS = 100;
const int MSG_FREI = 0x4;
const int PP_FREI = 100;
unsigned long prevFrei_ms;

const unsigned long READY_MS = 2000;
const int MSG_READY = 0x8;
const int PP_READY = 100;
unsigned long prevReady_ms;

void init_StatusLED()
{
  prevError_ms = millis();
  prevWD_ms = prevError_ms;
  prevFrei_ms = prevError_ms;
  prevReady_ms = prevError_ms;
}

/*
 * nur die wichtstigste Meldung darf durchkommen
 * siehe oben
 */
void StausLED( int LEDPin = LED_BUILTIN) {

  // Wenn kein Fehler vorliegt soll das Ready-Signal kommen
  if ( Status == 0 ) { Status = Status | 0x8; }

  if ( Status & 0x1 ) {
    blink(&prevError_ms, ERROR_MS, LEDPin, PP_ERROR );
  } else { 
    if (Status & 0x2  ) {
      blink(&prevWD_ms, WATCHDOG_MS, LEDPin, PP_WATCHDOG );
    } else { 
      if (Status & 0x4 ) {
        blink(&prevFrei_ms, FREI_MS, LEDPin, PP_FREI );
      } else { 
        if (Status & 0x8 ) {
          blink(&prevReady_ms, READY_MS, LEDPin, PP_READY );
        }
      }
    }
  }
  
}


/*************************************************************
 * Author: J.Berndt
 * Datum:  06.2017
 * 	
 * Inteval-Messung  
**************************************************************/
int fkt_Interval(unsigned long *pTimer, long _Interval ) {

  unsigned long currentMillis = millis();
  if (currentMillis - *pTimer >= _Interval) {
    *pTimer = currentMillis;
    return true;
  } else {
    return false;
  }
}


/************************************************************************************
 * Author: J.Berndt
 * Datum:  06.2017
 *   
 * laesst eine LED nach vorgegebenem Interval blinken
 ************************************************************************************/
void blink(unsigned long *pTimer, long _Interval, int _LED, int _PulsePause = 1 ) {

  if (digitalRead(_LED) == LOW) {
    if ( fkt_Interval( pTimer, _Interval ) ) {
      digitalWrite(_LED, HIGH); 
    }
  } else {
    if ( fkt_Interval( pTimer, _Interval / _PulsePause ) ) {
      digitalWrite(_LED, LOW); 
     }
  }

}



#endif

