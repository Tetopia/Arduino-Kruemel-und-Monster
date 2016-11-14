#include "FastLED.h"
#include "labyrinth.h"
#include "spielfigur.h"

//Wie groß ist die LED-Matrix?
#define BREITE 8
#define HOEHE 8

//An welchen Pins sind die Knöpfe angeschlossen?
#define PIN_N 12
#define PIN_O 11
#define PIN_S 10
#define PIN_W 9

//An welchem Pin ist die Datenleitung der LED-Matrix angeschlossen?
#define LED_PIN 6

//Wie viele LEDs gibt es insgesammt?
#define NUM_LEDS (BREITE*HOEHE)

//Die LED-Matrix
CRGB led[BREITE][HOEHE];
//Die LEDs als eindimensionales Array
CRGB leds[NUM_LEDS];

//Das Labyrinth und die Spielfiguren
Labyrinth laby(BREITE,HOEHE);
Mampfi mampfi;
Monster monster;

//Die Variable start muss volatile sein, weil sie nur bei einem Interrupt gesetzt wird
volatile boolean start = false;

boolean ende = false;
boolean gewonnen = false;

void setup() 
{
  delay(1000);

  //die Pins, an denen die Knöpfe angeschlossen sind, werden zu Eingängen
  pinMode(PIN_N, INPUT_PULLUP);
  pinMode(PIN_O, INPUT_PULLUP);
  pinMode(PIN_S, INPUT_PULLUP);
  pinMode(PIN_W, INPUT_PULLUP);

  //Die Interrupts für die Knöpfe werden angelegt
  PCattachInterrupt(PIN_N, isrN, FALLING);
  PCattachInterrupt(PIN_O, isrO, FALLING);
  PCattachInterrupt(PIN_S, isrS, FALLING);
  PCattachInterrupt(PIN_W, isrW, FALLING);

  //Die LED-Matrix wird initialisiert
  FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(30);

  //Die Mauern und Krümel verteilen
  laby.labyrinthZeichnen();
}

void loop()
{
  if(start) //Sobald das Spiel gestartet wurde fangen Mampfi und die Monster das laufen an
  {
    mampfi.gehen(laby);
    monster.gehen(laby);
  }
  //das Krümel auf dem Feld, auf dem Mampfi ist, wird gelöscht
  laby.kruemelEssen(mampfi.posX, mampfi.posY);

  //Wenn alle Krümel aufgegessen sind, wird das Spiel beendet
  if(laby.allesAufgegessen()) 
  {
    ende = true;
    gewonnen = true;
  }
  //Wenn Mampfi und das Monster an der selben Stelle sind, 
  //also wenn das Monster Mampfi gefressen hat, dann wird das Spiel ebenfalls beendet
  else if(mampfi.posX == monster.posX && mampfi.posY == monster.posY)
  {
    ende = true;
    gewonnen = false;
  }

  //Die LEDs bekommen die entsprechenden Farben
  ledsSetzen();

  //Es werden 500 Millisekunden gewartet, bevor die Spielfiguren den nächsten Schritt machen
  delay(500);
}

void ledsSetzen()
{
  if(!ende) //Solange das spiel noch nicht zu Ende ist
  {
    //Mauern und Krümel entsprechend der Zellen verteilen
    for(int x = 0; x < BREITE; x++)
    {
      for(int y = 0; y < HOEHE; y++)
      {
        if(laby.zelle[x][y] == 'm') led[x][y] = CRGB::Blue;
        else if(laby.zelle[x][y] == 'k') led[x][y] = CRGB::Grey;
        else led[x][y] = CRGB::Black;
      }
    }
  
    //Mampfi und das Monster zeichnen
    led[mampfi.posX][mampfi.posY] = CRGB::Yellow;
    led[monster.posX][monster.posY] = CRGB::Red;
  }
  else //das Spiel ist zu Ende
  {
    CRGB farbe;
    //Wenn das Spiel gewonnen wurde, werden alle LEDs grün, ansonsten rot
    if(gewonnen) farbe = CRGB::Green;
    else farbe = CRGB::Red;
    for(int x = 0; x < BREITE; x++)
    {
      for(int y = 0; y < HOEHE; y++)
      {
        led[x][y] = farbe;
      }
    }
  }
  //Die gerade gesetzten LEDs müssen noch an die Matrix geschickt werden
  ledsAktualisieren();
}

void ledsAktualisieren()
{
  //Konvertierung des 2D-Arrays in das eindimensionale Array der LED-Matrix
  for(int i=0;i<NUM_LEDS;i++)
  {
    int x = i/HOEHE;
    int y = i%HOEHE;
    if(x%2 == 1) y = HOEHE-1-y;
    leds[i] = led[x][y];
  }
  
  //An die Matrix schicken 
  FastLED.show();
}

//Die Auswertung des Knopfdrucks in der Interrupt-Service-Routine
void isrKnopf(char c)
{
  //Das Spiel wird beim ersten Knopfdruck gestartet
  if(!start) start = true;
  //Mampfis Blickrichtung wird neu gesetzt
  mampfi.blickrichtung = c;
}

//Die Interrupt-Service-Routinen, die bei einem Knopfdruck ausgelöst werden
void isrN()
{
  isrKnopf('n');  
}
void isrO()
{
  isrKnopf('o');  
}
void isrS()
{
  isrKnopf('s');  
}
void isrW()
{
  isrKnopf('w');
}
