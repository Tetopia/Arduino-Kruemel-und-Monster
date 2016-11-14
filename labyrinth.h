/*
  labyrinth.h - C++ Variante von Krümel und Monster für Arduino und eine LED-Matrix.
  Created by Theresa Thoma, November 13, 2016.
*/

#ifndef labyrinth_h
#define labyrinth_h

class Labyrinth
{
  public:
  Labyrinth(int breite, int hoehe);

  int breite;
  int hoehe;
  
  char zelle[8][8]; //'f' = frei; 'm' = mauer; 'k' = krümel

  boolean istMauer(int x, int y);
  boolean allesAufgegessen();
  void kruemelEssen(int x, int y);

  void labyrinthZeichnen();
};


#endif
