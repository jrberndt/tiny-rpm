#ifndef Ringspeicher_h
#define Ringspeicher_h

#include "Arduino.h"


class Ringspeicher
{
  private:
  int MaxItems;         // Groesse des Ringspeichers
  int First;            // 1.Speicheradresse Default 0
  int Last;             // letzte Speicheradresse 
  int firstItem;        // ältester DS
  int lastItem;         // jüngster DS
  int read_nextItem;
  int write_nextItem;
  int ItemCount;        // 

  
  public:
  Ringspeicher(int elemente=100);
  float get_nextItem();
  float set_nextItem(float Item);
};

Ringspeicher::Ringspeicher(int elemente=20) {
  
  MaxItems=elemente;
  firstItem=0;
  lastItem=MaxItems-1;
  
}


//Ringspeicher::



#endif
