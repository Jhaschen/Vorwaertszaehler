#include "ATMega32_utility_bib.h"


#define delay 250


int main(void) {

  // Richtungsregister für die LEDs auf Ausgang
   DDRC = 0b11111111;
   // Alle LEDs aus
   LED_PORT = 0b11111111;

   UART Seriell(8,0,1,9600) ; // Init 8 Zeichenbits, keine Parität, 1 StoppBit, 9600 Bit/s
   Button B; // Neue Instanz der Klasse Button anlegen

  char buffer[50]; //Buffer Array für Zeichenkette (50 Zeichen)
  sprintf(buffer," Vorwaertszaehler\n \r'"); // String Printf: schreibt eine Zeichenkette in den Buffer
  Seriell.uart_puts(buffer);
  uint8_t Cnt=0; // Zählvariable
  uint8_t State=0;// Taster gedrückt
   while (1)
   {


     // Schalter in welchem Zustand das Programm ist.
   		switch (State)
   		{
   			// State == 0 => Diesen Programmabschnitt ausführen
   		  case 0:
           // Abfrage ob Taster_read()==2 == 1, d.h. Taste gedrückt
   			  // "switch-case"-Anweisung, d.h. andernfalls wären wir gar nicht an dieser Stelle.
   		    if (B.Button_read()==2)
   		    {
             // Zähler um 1 erhöhen
     	      Cnt = Cnt + 1;

             // Zustandswechsel 0 => 1: Taste gedrückt
   			    State =   1;

             // Neuen Zählerstand auf den LEDs ausgeben
             PORTC = ~Cnt;

             // Erst einmal das Tastenprellen abwarten ehe wir weitermachen...
   		      _delay_ms(1);
   		    }
   			  else
   			  {
   				  // Nur über den "Leer"-Übergang 0=>0 aus dem Zustandsdiagramm zu veranschaulichen.
   				  // Lässt man "normalerweise" weg.
   			  }
   			  break;

   			// State == 1 => Diesen Programmabschnitt ausführen
   			case 1:
           // Abfrage ob Taster_read()!=2, d.h. Taste nicht gedrückt

   		    // "switch-case"-Anweisung, d.h. andernfalls wären wir gar nicht an dieser Stelle.
       		if (B.Button_read()!=2)
   		    {
             // Zustandswechsel 1 => 0: Taste nicht (mehr) gedrückt
   			    State = 0;

             // Erst einmal das Tastenprellen abwarten ehe wir weitermachen...
   		      _delay_ms(1);
   		    }
   			  else
   			  {
   				  // Nur über den "Leer"-Übergang 1=>1 aus dem Zustandsdiagramm zu veranschaulichen.
   				  // Lässt man "normalerweise" weg.
   			  }
   			  break;

   			// Default: Wenn ((State != 0) && (State != 1)) => Fehler: Fall darf bei korrektem Programm nicht auftreten.
   			default:
   			  break;
   		}
   	}
 return 0;
}
