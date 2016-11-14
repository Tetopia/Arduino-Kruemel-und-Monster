#include "Arduino.h"
#include "labyrinth.h"

//Konstruktor für das Labyrinth
Labyrinth::Labyrinth(int breite, int hoehe)
{
  zelle[breite][hoehe] = {'f'};
  this->breite = breite;
  this->hoehe = hoehe;
}

//ist in der Zelle bei den gegebenen Koordinaten x und y eine Mauer?
//return true, wenn es eine Mauer ist; false, wenn das Feld begehbar ist
boolean Labyrinth::istMauer(int x, int y)
{
  if(zelle[x][y] == 'm') return true;
  else return false;
}

//wurden alle Krümel aufgegessen?
//return true, wenn keine Krümel mehr da sind; false, wenn noch irgendwo eins rumliegt
boolean Labyrinth::allesAufgegessen()
{
  boolean aufgegessen = true;
  for(int x = 0; x < breite; x++)
  {
    for(int y = 0; y < hoehe; y++)
    {
      if(zelle[x][y] == 'k') aufgegessen = false;
    }
  }
  return aufgegessen;
}

//Löscht das Krümel bei den gegebenen Koordinaten x und y
void Labyrinth::kruemelEssen(int x, int y)
{
  zelle[x][y] = 'f';
}

//Erstellt die Mauern und Krümel zu beginn des Spiels
void Labyrinth::labyrinthZeichnen()
{
  //Die Mauern zeichnen
  for(int x = 0; x < breite; x++)
  {
    for(int y = 0; y < hoehe; y++)
    {
      zelle[x][y] = 'f';
    }
  }
  
  for(int x = 0; x < breite; x++)
  {
    zelle[x][7] = 'm';
  }
  zelle[0][6] = 'm';
  zelle[7][6] = 'm';
  
  for(int x = 0; x < breite; x++)
  {
    zelle[x][5] = 'm';
  }
  zelle[1][5] = 'f';
  zelle[6][5] = 'f';
  
  zelle[3][4] = 'm';
  
  zelle[0][3] = 'm';
  zelle[1][3] = 'm';
  zelle[3][3] = 'm';
  zelle[5][3] = 'm';
  zelle[6][3] = 'm';
  zelle[7][3] = 'm';
  
  zelle[1][2] = 'm';
  
  zelle[1][1] = 'm';
  zelle[2][1] = 'm';
  zelle[3][1] = 'm';
  zelle[4][1] = 'm';
  zelle[5][1] = 'm';
  zelle[7][1] = 'm';
  
  zelle[7][0] = 'm';

  for(int x = 0; x < breite; x++)
  {
    for(int y = 0; y < hoehe; y++)
    {
      if(zelle[x][y] != 'm') zelle[x][y] = 'k';
    }
  }
}
