#ifndef RpmTelegram_h
#define RpmTelegram_h
#include "Arduino.h"

/* Author:J.Berndt
 * Datum: 06.2017
 * 
 * 
 * SNO    Gerätenummer  0..7 Konstante beim jeweiligen Gerät
 * 0 ->   Master
 * 1..7   Slaves
 * 
 * CMD    Kommando
 * 0 ->   Hi      Master
 * 1 ->   Hi      Slave
 * 2 ->   ACK     Master
 * 3 ->   ACK     Slave
 * 
 * 
 * SQN  Sequenznummer 
 * TST  Timestamp     in Milliskunden
 * DTA  Daten         ### Datentyp sthet noch nicht fest
 * 
 */


// Gerätenummer 1..7  ### wird in der Anwendungsspezifischen Headerdatei definiert
// const int  SNO =  4;

// Sequenznummer
unsigned int SQN=0;

// Timestamp
unsigned long TST;

// Daten

int registriert = LOW;




#endif
