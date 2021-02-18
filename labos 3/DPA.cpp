#include <iostream>
#include <vector>
#include <string>
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

vector<string> uredi_prijelaze(string prijelazi)
{
   vector<string> novi, pom;
   novi = string_u_vektor(prijelazi, ",");
   pom = string_u_vektor(novi[2], "->");
   novi[2] = pom[0];
   novi.insert(novi.begin() + 3, pom[1]);
   return novi;
}

vector<string> stavi_na_stog(vector<string> stog, string izlaz)
{
   string pom;
   for (unsigned int i = 0; i < izlaz.size(); i++)
   {
      pom = izlaz[i];
      stog.insert(stog.begin() + i, pom);
   }
   return stog;
}

bool je_li_prihvatljivo(string stanje, string prihvatljivaStanja)
{
   vector<string> prihvatljiva;
   prihvatljiva = string_u_vektor(prihvatljivaStanja, ",");
   int sadrzi = 0;
   for (unsigned int i = 0; i < prihvatljiva.size(); i++)
      if (prihvatljiva[i] == stanje)
         sadrzi = 1;
   if (sadrzi)
      return 1;
   else
      return 0;
}

void e_prijelaz(string *stanje, vector<string> *stog, vector<string> prijelazi)
{
   vector<string> noviprijelaz;
   string znak;
   znak = (*stog).front();
   (*stog).erase((*stog).begin());
   int ima = 0;
   for (unsigned int y = 0; y < prijelazi.size(); y++)
   {
      noviprijelaz = uredi_prijelaze(prijelazi[y]);
      if (noviprijelaz[0] == *stanje && noviprijelaz[2] == znak && noviprijelaz[1] == "$")
      {
         if (noviprijelaz[4] != "$")
            *stog = stavi_na_stog(*stog, noviprijelaz[4]);

         *stanje = noviprijelaz[3];
         cout << *stanje << "#";

         if ((*stog).size() > 0)
         {
            unsigned int vel = (*stog).size();
            for (unsigned int z = 0; z < vel; z++)
               cout << (*stog)[z];
         }
         else
         {
            cout << "$";
         }
         cout << "|";
         ima = 1;
         break;
      }
   }
   if (!ima)
   {
      (*stog) = stavi_na_stog(*stog, znak);
   }
}

void fja_prijelaza(vector<string> nizovi, string pocetnoStanje, string pocetniZnakStoga, int i, vector<string> prijelazi, string prihvatljivaStanja)
{
   cout << pocetnoStanje << "#" << pocetniZnakStoga << "|";
   vector<string> niz, stog, noviprijelaz, stogpom;
   string stanje = pocetnoStanje, znak, pom;
   niz = string_u_vektor(nizovi[i], ",");
   stog.push_back(pocetniZnakStoga);
   unsigned int x = 0, ima;
   while (x < niz.size())
   {
      znak = stog.front();
      stog.erase(stog.begin());
      ima = 0;
      for (unsigned int y = 0; y < prijelazi.size(); y++)
      {
         noviprijelaz = uredi_prijelaze(prijelazi[y]);
         if (noviprijelaz[0] == stanje && noviprijelaz[2] == znak && noviprijelaz[1] == niz[x])
         {
            if (noviprijelaz[4] != "$")
               stog = stavi_na_stog(stog, noviprijelaz[4]);
            stanje = noviprijelaz[3];
            ima = 1;
            x++;
            cout << stanje << "#";
            if (stog.size() > 0)
            {
               unsigned int vel = stog.size();
               for (unsigned int z = 0; z < vel; z++)
                  cout << stog[z];
            }
            else
            {
               cout << "$";
               stog = stavi_na_stog(stog, "$");
            }

            cout << "|";
         }

         else if (noviprijelaz[0] == stanje && noviprijelaz[2] == znak && noviprijelaz[1] == "$")
         {

            if (noviprijelaz[4] != "$")
               stog = stavi_na_stog(stog, noviprijelaz[4]);
            stanje = noviprijelaz[3];
            ima = 1;
            cout << stanje << "#";
            if (stog.size() > 0)
            {
               for (unsigned int z = 0; z < stog.size(); z++)
                  cout << stog[z];
            }
            else
            {
               cout << "$";
               stog = stavi_na_stog(stog, "$");
            }
            cout << "|";
         }

         if (ima)
            break;
      }
      if (!ima)
      {
         cout << "fail|0" << endl;
         break;
      }
   }

   if (ima)
   {
      pom = "";
      stogpom = stog;
      while (pom != stanje || stogpom.size() != stog.size())
      {
         pom = stanje;
         stogpom = stog;
         if (!je_li_prihvatljivo(stanje, prihvatljivaStanja))
            e_prijelaz(&stanje, &stog, prijelazi);
         else
            break;
      }
      cout << je_li_prihvatljivo(stanje, prihvatljivaStanja) << endl;
   }
}

int main(void)
{
   vector<string> prijelazi, nizovi;

   string ulazninizovi, skupStanja, skupUlZnakova, skupZnakovaStoga, prihvatljivaStanja, pocetnoStanje, pocetniZnakStoga, ulaz;

   getline(cin, ulazninizovi);
   getline(cin, skupStanja);
   getline(cin, skupUlZnakova);
   getline(cin, skupZnakovaStoga);
   getline(cin, prihvatljivaStanja);
   getline(cin, pocetnoStanje);
   getline(cin, pocetniZnakStoga);

   while (getline(cin, ulaz))
   { //citanje iz datoteke,bez entera
      prijelazi.push_back(ulaz);
   }

   nizovi = string_u_vektor(ulazninizovi, "|");

   for (unsigned int i = 0; i < nizovi.size(); i++)
   {
      fja_prijelaza(nizovi, pocetnoStanje, pocetniZnakStoga, i, prijelazi, prihvatljivaStanja);
   }
   return 0;
}