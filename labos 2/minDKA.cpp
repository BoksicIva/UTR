#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
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

vector<string> dohvatljiva_stanja(vector<string> prijelazi, string pocetnoStanje)
{
   vector<string> dohvatljivaStanja, noviprijelaz;
   dohvatljivaStanja.push_back(pocetnoStanje);
   unsigned int duzina = 0;
   while (duzina != dohvatljivaStanja.size())
   {
      duzina = dohvatljivaStanja.size();
      for (unsigned int i = 0; i < duzina; i++)
      {
         for (unsigned int j = 0; j < prijelazi.size(); j++)
         {
            noviprijelaz = uredi_prijelaze(prijelazi[j]);
            if (noviprijelaz[0] == dohvatljivaStanja[i])
            {
               dohvatljivaStanja.push_back(noviprijelaz[2]);
            }
         }
         dohvatljivaStanja = slozi_abecedno(dohvatljivaStanja);
      }
   }
   dohvatljivaStanja = slozi_abecedno(dohvatljivaStanja);
   return dohvatljivaStanja;
}

vector<string> izbaci_nedohvatljiva_stanja_iz_prijelaza(vector<string> prijelazi, vector<string> dohvatljivaStanja)
{
   int duljina = prijelazi.size();
   vector<string> noviprijelazi, novi;
   for (int i = 0; i < duljina; i++)
   {
      novi = uredi_prijelaze(prijelazi[i]);
      if (find(dohvatljivaStanja.begin(), dohvatljivaStanja.end(), novi[0]) != dohvatljivaStanja.end() &&
          find(dohvatljivaStanja.begin(), dohvatljivaStanja.end(), novi[2]) != dohvatljivaStanja.end())
         noviprijelazi.push_back(prijelazi[i]);
   }
   return noviprijelazi;
}

vector<string> makni_istovjetna_iz_prijelaza(vector<string> *prijelazi, string izbaci, string zamnijeni)
{
   vector<string> novi;
   for (unsigned int i = 0; i < (*prijelazi).size(); i++)
   {
      novi = uredi_prijelaze((*prijelazi)[i]);
      if (novi[2] == izbaci)
      {
         (*prijelazi)[i] = novi[0] + "," + novi[1] + "->" + zamnijeni;
      }
   }
   return *prijelazi;
}

void uredi_pocetno_stanje(string zamijeni, string *pocetnoStanje)
{
   *pocetnoStanje = zamijeni;
}

vector<string> algoritam3(vector<string> *prijelazi, vector<string> dohvatljivaStanja, vector<string> prihvatljivaStanja, string *pocetnoStanje)
{
   unsigned int n = dohvatljivaStanja.size();
   int tablica[n][n];
   int brojac = 0;

   for (unsigned int i = 0; i < n; i++)
      for (unsigned int j = 0; j < n; j++)
         tablica[i][j] = 0;

   for (unsigned int i = 0; i < n; i++)
   {
      for (unsigned int j = 0; j < i; j++)
      {
         if (find(prihvatljivaStanja.begin(), prihvatljivaStanja.end(), dohvatljivaStanja[i]) == prihvatljivaStanja.end() &&
             find(prihvatljivaStanja.begin(), prihvatljivaStanja.end(), dohvatljivaStanja[j]) != prihvatljivaStanja.end())
         {
            brojac++;
            tablica[i][j] = 1; //prvi korak algoritma
         }

         if (find(prihvatljivaStanja.begin(), prihvatljivaStanja.end(), dohvatljivaStanja[i]) != prihvatljivaStanja.end() &&
             find(prihvatljivaStanja.begin(), prihvatljivaStanja.end(), dohvatljivaStanja[j]) == prihvatljivaStanja.end())
         {
            brojac++;
            tablica[i][j] = 1;
         }
      }
   }
   vector<string> novii, novij;
   int pomocnibrojac = 0;

   while (pomocnibrojac < brojac)
   {
      brojac = pomocnibrojac;
      for (unsigned int i = 0; i < (*prijelazi).size() - 1; i++)
      {
         for (unsigned int j = i + 1; j < (*prijelazi).size(); j++)
         {
            novii = uredi_prijelaze((*prijelazi)[i]);
            novij = uredi_prijelaze((*prijelazi)[j]);
            if (novii[1] == novij[1])
            {
               for (unsigned int x = 0; x < n - 1; x++)
               {
                  for (unsigned int y = x + 1; y < n; y++)
                  {
                     if (novii[0] == dohvatljivaStanja[x] && novij[0] == dohvatljivaStanja[y])
                     {
                        auto it_x = std::find(dohvatljivaStanja.begin(), dohvatljivaStanja.end(), novii[2]);
                        int index_x = distance(dohvatljivaStanja.begin(), it_x);
                        auto it_y = std::find(dohvatljivaStanja.begin(), dohvatljivaStanja.end(), novij[2]);
                        int index_y = distance(dohvatljivaStanja.begin(), it_y);
                        if (tablica[index_x][index_y] == 1 || tablica[index_y][index_x] == 1)
                        {
                           if (x >= y)
                              tablica[x][y] = 1;
                           else
                              tablica[y][x] = 1;
                        }
                     }
                  }
               }
            }
         }
      }
      for (unsigned int i = 1; i < n; i++)
      {
         for (unsigned int j = 0; j < i; j++)
            if (tablica[i][j] == 1)
               pomocnibrojac++;
      }
   }

   /* for (int i = 1; i < n; i++)
   {
      for (int j = 0; j < i; j++)
         cout << tablica[i][j] << " "; //              ---> ispisuje tablicu
      cout << endl;
   }*/
   vector<string> izbaci;
   vector<int> indeksi;
   for (int i = n - 1; i > 0; i--)
   {
      for (int j = i - 1; j >= 0; j--)
         if (tablica[i][j] == 0)
         {
            izbaci.push_back(dohvatljivaStanja[i]);
            (*prijelazi) = makni_istovjetna_iz_prijelaza(prijelazi, dohvatljivaStanja[i], dohvatljivaStanja[j]);
            if (dohvatljivaStanja[i] == *pocetnoStanje)
               uredi_pocetno_stanje(dohvatljivaStanja[j], pocetnoStanje);
            //cout << dohvatljivaStanja[i] << "     " << dohvatljivaStanja[j] << endl;
            dohvatljivaStanja[i] = dohvatljivaStanja[j];
         }
   }
   dohvatljivaStanja = slozi_abecedno(dohvatljivaStanja);

   return dohvatljivaStanja;
}

vector<string> izbaci_simbole(vector<string> prijelazi)
{
   vector<string> novi, novisimboli;
   for (unsigned int i = 0; i < prijelazi.size(); i++)
   {
      novi = uredi_prijelaze(prijelazi[i]);
      novisimboli.push_back(novi[1]);
   }
   novisimboli = slozi_abecedno(novisimboli);
   return novisimboli;
}

vector<string> uredi_prihvatljiva(vector<string> dohvatljivaStanja, vector<string> prihvatljivaStanja)
{
   vector<string> novi;
   for (unsigned int i = 0; i < prihvatljivaStanja.size(); i++)
   {

      if (find(dohvatljivaStanja.begin(), dohvatljivaStanja.end(), prihvatljivaStanja[i]) != dohvatljivaStanja.end())
         novi.push_back(prihvatljivaStanja[i]);
   }
   return novi;
}

void ispisi_vektor(vector<string> ispis)
{
   if (ispis.size() >= 1)
   {
      for (unsigned int i = 0; i < ispis.size() - 1; i++)
         cout << ispis[i] << ",";
      cout << ispis[ispis.size() - 1] << endl;
   }
   else
      cout << endl;
}

int main(void)
{
   string skupstanja, skupsimbola, skupprihvatljivihstanja, pocetnoStanje, ulaz;
   vector<string> stanja, simboli, prihvatljivaStanja, prijelazi, dohvatljivaStanja, dohvatljivaStanjanova;

   getline(cin, skupstanja);
   stanja = string_u_vektor(skupstanja, ",");

   getline(cin, skupsimbola);
   simboli = string_u_vektor(skupsimbola, ",");

   getline(cin, skupprihvatljivihstanja);
   prihvatljivaStanja = string_u_vektor(skupprihvatljivihstanja, ",");

   getline(cin, pocetnoStanje);

 

   while (getline(cin, ulaz))
   { //citanje iz datoteke,bez entera
      prijelazi.push_back(ulaz);
   }

   dohvatljivaStanja = dohvatljiva_stanja(prijelazi, pocetnoStanje);

   /*for (int i = 0; i < dohvatljivaStanja.size(); i++)            //provjera dohvatljivih stanja
      cout << dohvatljivaStanja[i] << "   ";*/

   prijelazi = izbaci_nedohvatljiva_stanja_iz_prijelaza(prijelazi, dohvatljivaStanja);

   /* for (int i = 0; i < prijelazi.size(); i++) //provjera dohvatljivih stanja   // provjera prijelaza nakon izbacivanja nedohvatljivih stanja
      cout << prijelazi[i] << endl;*/

   dohvatljivaStanja = algoritam3(&prijelazi, dohvatljivaStanja, prihvatljivaStanja, &pocetnoStanje);
   prijelazi = izbaci_nedohvatljiva_stanja_iz_prijelaza(prijelazi, dohvatljivaStanja);

   ispisi_vektor(dohvatljivaStanja);

   simboli = izbaci_simbole(prijelazi);

   ispisi_vektor(simboli);

   prihvatljivaStanja = uredi_prihvatljiva(dohvatljivaStanja, prihvatljivaStanja);
   ispisi_vektor(prihvatljivaStanja);

   cout << pocetnoStanje << endl;

   for (unsigned int i = 0; i < prijelazi.size(); i++)
   {
      cout << prijelazi[i] << endl;
   }

   return 0;
}