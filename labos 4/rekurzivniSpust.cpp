#include <iostream>
#include <string>
#include <vector>

using namespace std;

void parser(string ulaz, int *citaj, vector<string> *neprocitani, int *krivo)
{
   int citajulaz = 0;
   (*neprocitani).push_back("S");
   if (ulaz[0] == 'a')
   {
      (*neprocitani).insert((*neprocitani).begin() + 1, "A");
      (*neprocitani).insert((*neprocitani).begin() + 2, "B");
      (*citaj)++;
      citajulaz++;
   }
   else if (ulaz[*citaj] == 'b')
   {
      (*neprocitani).insert((*neprocitani).begin() + 1, "B");
      (*neprocitani).insert((*neprocitani).begin() + 2, "A");
      (*citaj)++;
      citajulaz++;
   }
   else
   {
      return;
   }

   int zastavica = 0;
   while ((citajulaz < ulaz.length() && *citaj < (*neprocitani).size()) || (*neprocitani).at(*citaj) == "B")
   {
      for (int i = 0; i < citajulaz; i++)
         cout << ulaz[i];
      cout << endl;

      for (auto it = (*neprocitani).begin(); it != (*neprocitani).begin() + *citaj; it++)
         cout << *it;
      cout << endl;

      for (auto it = (*neprocitani).begin(); it != (*neprocitani).end(); it++)
         cout << *it;
      cout << endl;
      cout << endl;

      if (zastavica == 1 && ulaz[citajulaz] == 'b' && ulaz[citajulaz + 1] == 'c')
      {
         citajulaz += 2;
         zastavica = 0;
      }

      if ((*neprocitani).at(*citaj) == "A")
      {
         if (ulaz[citajulaz] == 'b')
         {
            (*neprocitani).insert((*neprocitani).begin() + *citaj + 1, "C");
            (*citaj)++;
            citajulaz++;
         }
         else if (ulaz[citajulaz] == 'a')
         {
            citajulaz++;
            (*citaj)++;
         }
         else
         {
            *krivo = 1;
            return;
         }
      }
      else if ((*neprocitani).at(*citaj) == "B")
      {
         if (ulaz[citajulaz] == 'c' && ulaz[citajulaz + 1] == 'c')
         {
            (*neprocitani).insert((*neprocitani).begin() + *citaj + 1, "S");
            (*citaj)++;
            citajulaz += 2;
            zastavica = 1;
         }
         else
         {
            (*citaj)++;
         }
      }
      else if ((*neprocitani).at(*citaj) == "C")
      {
         (*neprocitani).insert((*neprocitani).begin() + *citaj + 1, "A");
         (*neprocitani).insert((*neprocitani).begin() + *citaj + 2, "A");
         (*citaj)++;
      }
      else if ((*neprocitani).at(*citaj) == "S")
      {
         if (ulaz[citajulaz] == 'a')
         {
            (*neprocitani).insert((*neprocitani).begin() + *citaj + 1, "A");
            (*neprocitani).insert((*neprocitani).begin() + *citaj + 2, "B");
            (*citaj)++;
            citajulaz++;
         }
         else if (ulaz[citajulaz] == 'b')
         {
            (*neprocitani).insert((*neprocitani).begin() + *citaj + 1, "B");
            (*neprocitani).insert((*neprocitani).begin() + *citaj + 2, "A");
            (*citaj)++;
            citajulaz++;
         }
         else
         {
            *krivo = 1;
            return;
         }
      }
      else
      {
         *krivo = 1;
         return;
      }
   }
   *krivo = 1;
   return;
}

int main(void)
{
   string ulaz;
   vector<string> neprocitani;
   int citaj = 0;
   getline(cin, ulaz);
   int br = 0, krivo = 0;
   parser(ulaz, &citaj, &neprocitani, &krivo);
   for (auto it = (neprocitani).begin(); it != neprocitani.end(); it++)
   {
      if (br == citaj)
         break;
      cout << *it;
      br++;
   }
   cout << endl;
   if (!krivo)
      cout << "DA";
   else
      cout << "NE";
   cout << endl;
   cin.get();
   return 0;
}