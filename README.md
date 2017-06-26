# tiny-rpm
ATtiny85 Drehzahlmessung 

## verwendete Hardware Digispark
der Digispark ist ein kleines auf dem ATtiny85 basierendes Platinchen, das man direkt über den USB-Port seines Rechners flashen kann.
Programmiert wird das kleine Kerlchen mit der Arduino-IDE


im vorliegenden Projekt soll die Drehmessung an einem Windrad realisiert werden. 
Mit Hilfe eines Magneten und einem Hallsensor, werden die Umdrehungsimpulse des Rotors berührungslos aufgenommen.

Die Werte der aktuellen Drehzahl werden über ein 433MHZ Sender an einen Raspberry Pi vorgenommen, und dann z.B.:auf einer Webseite angezeigt.

