#include "Arduino.h"
#include "spielfigur.h"
#include "labyrinth.h"

Spielfigur::Spielfigur()
{
  posX = 0;
  posY = 0;
}

Mampfi::Mampfi()
{
  posX = 5;
  posY = 2;
}

Monster::Monster()
{
  posX = 2;
  posY = 3;
}

boolean Spielfigur::gehen(char richtung, Labyrinth laby)
{
  int posYNeu = posY;
  int posXNeu = posX;
  boolean erfolgreich = false;
  
  if(richtung == 'n')
  {
    posYNeu ++;
    if (posYNeu >= laby.hoehe) posYNeu = 0;
  }
  if(richtung == 'o')
  {
    posXNeu ++;
    if (posXNeu >= laby.breite) posXNeu = 0;
  }
  if(richtung == 's')
  {
    posYNeu --;
    if (posYNeu < 0) posYNeu = laby.hoehe-1;
  }
  if(richtung == 'w')
  {
    posXNeu --;
    if (posXNeu < 0) posXNeu = laby.breite-1;
  }
  
  if(!laby.istMauer(posXNeu, posYNeu))
  {
     posY = posYNeu;
     posX = posXNeu;
     erfolgreich = true;
  }
  return erfolgreich;
}

void Monster::gehen(Labyrinth laby)
{
  long zufall = random(7);
  if(zufall == 0) this->blickrichtung = 'n';
  else if(zufall == 1) this->blickrichtung = 'o';
  else if(zufall == 2) this->blickrichtung = 's';
  else if(zufall == 3) this->blickrichtung = 'w';

  if(!Spielfigur::gehen(this->blickrichtung, laby))
  {
    Monster::gehen(laby);
  }
}

void Mampfi::gehen(Labyrinth laby)
{
  Spielfigur::gehen(this->blickrichtung, laby);
}
