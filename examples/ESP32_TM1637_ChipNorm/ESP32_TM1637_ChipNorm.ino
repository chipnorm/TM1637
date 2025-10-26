#include "ChipNorm_TM1637.h"

#define CLK 15 //CLK mit D15 verbinden
#define DIO 2 //DIO mit D2 verbinden

ChipNorm_TM1637 display(CLK, DIO); //Initialisiert den Sensor (Objekt "display" der Klasse "ChipNorm_TM1637" erstellt) 

void setup() {
  display.setBrightness(7); //Einstellung der Helligkeit zwischen 1 und 7
  display.clear(); //Display-Inhalt löschen
}

void loop() {
  // Beispiel 1: _ _ 9 _
  // d1=Nichts , d2=Nichts , d3=9, d4=Nichts
  display.write_numbers(-1, -1, 9, -1); 
  display.dot(false); // Schaltet den Doppelpunkt aus
  delay(2000);

  // Beispiel 2: 12:34
  // d1=1, d2=2, d3=3, d4=4
  display.write_numbers(1, 2, 3, 4);
  display.dot(true); // Schaltet den Doppelpunkt ein
  delay(2000);

  // Beispiel 3: Text A B C D
  // d1=1, d2=2, d3=3, d4=4
  display.write_text(A, B, C, D);
  display.dot(false); // Schaltet den Doppelpunkt aus
  delay(2000);

  //Beispiel 4: Manueller Modus
  // d1=Nichts  d2=H  d3=I  d4:-
  display.write_manuell(0b10000000, 0b01110110, 0b00000110, 0b01000000);
  display.dot(false); // Schaltet den Doppelpunkt aus
  delay(2000);

  //Anleitung zum Manuellen Modus:
  //
  //      A
  //     ---
  //  F |   | B
  //     -G-
  //  E |   | C
  //     ---
  //      D

  //Bit,Wert,Segment,Beschreibung
  //Bit 0 (1)   A,Oberes Segment
  //Bit 1 (2)   B,Oberes rechtes Segment
  //Bit 2 (4)   C,Unteres rechtes Segment
  //Bit 3 (8)   D,Unteres Segment
  //Bit 4 (16)  E,Unteres linkes Segment
  //Bit 5 (32)  F,Oberes linkes Segment
  //Bit 6 (64)  G,Mittleres Segment
  //Bit 7 (128) DP (Dot/Punkt) Dezimalpunkt

}
