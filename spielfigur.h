/*
  spielfigur.h - C++ Variante von Krümel und Monster für Arduino und eine LED-Matrix.
  Created by Theresa Thoma, November 13, 2016.
*/
#include "labyrinth.h"

#ifndef spielfigur_h
#define spielfigur_h

class Spielfigur
{
  public:
  Spielfigur();
  
  int posX;
  int posY;
  char blickrichtung; //'n', 's', 'w', 'o'

  boolean gehen(char richtung, Labyrinth laby);
};

class Mampfi : public Spielfigur
{
  public:
  Mampfi();

  void gehen(Labyrinth laby);
};

class Monster : public Spielfigur
{
  public:
  Monster();

  void gehen(Labyrinth laby);
};

#endif
