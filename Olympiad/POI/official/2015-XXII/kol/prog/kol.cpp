/******************************************************************************
 *                                                                            *
 *                    XXII Olimpiada Informatyczna                            *
 *                                                                            *
 *   Zadanie:              Kolekcjoner Bajtemonow                             *
 *   Zlozonosc czasowa:    O(n)                                               *
 *   Zlozonosc pamieciowa: O(sqrt(A))                                         *
 *   Opis:                 Rozwiazanie wzorcowe                               *
 *****************************************************************************/

#include "ckollib.h"
#include<cstdio>
using namespace std;

const int mod = 65536;
int Pierwsza_polowa_liczby[mod];
int Druga_polowa_liczby[mod];


int main(){
  int nowa_karta = karta();
  int pierwszy_pamietany_rodzaj = -1;
  int drugi_pamietany_rodzaj = -1;
  
  int liczba_kart_rodzaju_pierwszego = -1;
  int liczba_kart_rodzaju_drugiego = -1;
  
  //W celu ustalenia liczby kart tego samego rodzaju wybieramy pierwsza napotkana karte,
  //i zliczamy jej wystapienia. Na wypadek gdyby tak karta okazala sie brakujaca karta,
  // liczymy rowniez wystapienia drugiej karty (pierwszej innej niz pierwsza zapamietana)
  
  while(nowa_karta){
    //printf("%d\n", nowa_karta);
    if(pierwszy_pamietany_rodzaj == -1){ //karta pierwszego rodzaju nie jest okreslona, wiec zapisujemy
      pierwszy_pamietany_rodzaj = nowa_karta;
      liczba_kart_rodzaju_pierwszego = 1;
    }
    else{
      if(pierwszy_pamietany_rodzaj == nowa_karta){ //napotkana karta jest taka sama jak karta pierwszego rodzaju
        liczba_kart_rodzaju_pierwszego++;
      }
      else{
        if(drugi_pamietany_rodzaj == -1){ //napotkana karta jest pierwsza karta inna od pierwszej zapisanej karty
          drugi_pamietany_rodzaj = nowa_karta;
          liczba_kart_rodzaju_drugiego = 1;
        }
        else{
          if(drugi_pamietany_rodzaj == nowa_karta) liczba_kart_rodzaju_drugiego++; //napotkana karta jest karta drugiego rodzaju
        }
      }
    }
    
    Pierwsza_polowa_liczby[nowa_karta%mod]++; //pierwsza 'cyfra' w zapisie napotkanej karty
    Druga_polowa_liczby[nowa_karta/mod]++; //druga 'cyfra' w zapisie napotkanej karty
    nowa_karta = karta();
  }
  //Koniec wczytywania danych.
  
  //sprawdzamy, czy oba rodzaje liczonych przez nas kart wystapily tyle samo razy
  if(liczba_kart_rodzaju_pierwszego == liczba_kart_rodzaju_drugiego){
    //jezeli tak to wiemy ile powinno byc kart kazdego rodzaju
    //sprawdzamy jakie 'cyfry' wystapily niepodzielna przez liczbe kart razy
    //na kazda pozycje bedzie to dokladnie jedna taka cyfra
    int Odpowiedz=0;
    for(int i = 0; i < mod; i++){
      if(Pierwsza_polowa_liczby[i]%liczba_kart_rodzaju_drugiego){
        Odpowiedz += i;
      }
      if(Druga_polowa_liczby[i]%liczba_kart_rodzaju_drugiego){
        Odpowiedz += i*mod;
      }
    }
    odpowiedz(Odpowiedz);
    return 0;
  }
  //kart pierwszego i drugiego rodzaju jest inna liczba, karta ktorej mamy mniej ( o ile nie bylo tylko jednej karty)
  //jest ta, ktora zostala skradziona
  if(liczba_kart_rodzaju_drugiego == -1){
    odpowiedz(pierwszy_pamietany_rodzaj);
    return 0;
  }
  if(liczba_kart_rodzaju_pierwszego > liczba_kart_rodzaju_drugiego) odpowiedz(drugi_pamietany_rodzaj);
  else odpowiedz(pierwszy_pamietany_rodzaj);
  return 0;
}