#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

vector<string> string_u_vektor(string input, string delimianator)
{
   string cutinput;
   vector<string> vektor;
   while (input.find(delimianator) != string::npos)
   {
      cutinput = input.substr(0, input.find(delimianator));
      vektor.push_back(cutinput);
      input.erase(0, input.find(delimianator) + delimianator.size());
   }
   vektor.push_back(input);
   return vektor;
}

vector<string> slozi_abecedno(vector<string> ulaz)
{
   sort(ulaz.begin(), ulaz.end());
   ulaz.erase(unique(ulaz.begin(), ulaz.end()), ulaz.end());
   return ulaz;
}

vector<string> uredi_prijelaze(string prijelazi)
{
   vector<string> novi, pom;
   novi = string_u_vektor(prijelazi, ",");
   pom = string_u_vektor(novi[1], "->");
   novi[1] = pom[0];
   novi.insert(novi.begin() + 2, pom[1]);
   return novi;
}

vector<string> sljedeceStanje(vector<string> izlaz, vector<string> prijelazi)
{
   vector<string> novi;
   for (unsigned int i = 0; i < prijelazi.size(); i++)
   {
      novi = uredi_prijelaze(prijelazi[i]);
      for (unsigned int j = 0; j < izlaz.size(); j++)
      {
         if ((izlaz[j] == novi[0]) && (novi[1] == "$"))
         {
            for (unsigned int k = 2; k < novi.size(); k++)
            {
               if ((izlaz[j] != novi[k]) && (novi[k] != "#"))
               {
                  izlaz.push_back(novi[k]);
                  // cout << novi[k];
               }
            }
         }
      }
   }
   izlaz = slozi_abecedno(izlaz);
   return izlaz;
}

void fja_prijelaza(vector<string> nizovi, string pocetnoStanje, int i, vector<string> prijelazi)
{
   int zastava;
   string pom;
   vector<string> stanje, prijelaz, niz, noviprijelaz, izlaz, noviizlaz;
   niz = string_u_vektor(nizovi[i], ",");
   stanje.push_back(pocetnoStanje);
   int vel, vel2;
   do
   {
      vel = stanje.size();
      stanje = sljedeceStanje(stanje, prijelazi);
      vel2 = stanje.size();
   } while (vel < vel2);

   for (unsigned int i = 0; i < stanje.size() - 1; i++)
      cout << stanje[i] << ",";
   cout << stanje[stanje.size() - 1] << "|";
   unsigned int x = 0;
   while (x < niz.size())
   {
      zastava = 0;
      while ((stanje.size() != 0))
      {

         for (unsigned int y = 0; y < prijelazi.size(); y++)
         {
            noviprijelaz = uredi_prijelaze(prijelazi[y]);
            
            if ((noviprijelaz[0] == stanje.front()) && (noviprijelaz[1] == niz[x]))
            {
               for (unsigned int k = 2; k < noviprijelaz.size(); k++)
                  if (noviprijelaz[k] != "#")
                  {
                     izlaz.push_back(noviprijelaz[k]);
                     zastava = 1;
                   
                  }
            }
         }
         stanje.erase(stanje.begin());
      }
      int vel, vel2;
      if (zastava == 0)
         izlaz.push_back("#");
      izlaz = slozi_abecedno(izlaz);
      do
      {
         vel = izlaz.size();
         izlaz = sljedeceStanje(izlaz, prijelazi);
         vel2 = izlaz.size();
      } while (vel < vel2);

      izlaz = slozi_abecedno(izlaz);

      for (unsigned int z = 0; z < izlaz.size() - 1; z++)
         cout << izlaz[z] << ",";

      cout << izlaz[izlaz.size() - 1];

      stanje = izlaz;

      if (x < niz.size() - 1)
         cout << "|";

      x++;
      izlaz.clear();
   }
}

int main(void)
{
   vector<string> nizovi, prijelazi, noviprijelaz;
   string ulazninizovi, skupStanja, abeceda, prihvatljivaStanja, pocetnoStanje, ulaz;

   getline(cin, ulazninizovi);
   getline(cin, skupStanja);
   getline(cin, abeceda);
   getline(cin, prihvatljivaStanja);
   getline(cin, pocetnoStanje);
   int zaustavi = 0;
   while (zaustavi == 0)
   {
      getline(cin, ulaz);
      if ((ulaz == "\0")) 
         zaustavi = 1;
      else
         prijelazi.push_back(ulaz);
   }

 
   nizovi = string_u_vektor(ulazninizovi, "|");

 

   for (unsigned int i = 0; i < nizovi.size(); i++)
   {
      fja_prijelaza(nizovi, pocetnoStanje, i, prijelazi);
      cout << endl;
   }

   return 0;
}