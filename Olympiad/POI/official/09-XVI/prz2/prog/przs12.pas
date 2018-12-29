(*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Przechadzka Bajtusia (PRZ)                                *
 *   Plik:     przs12.pas                                                *
 *   Autor:    Jakub Lacki                                               *
 *   Opis:     Rozwiazanie nieoptymalne. Operuje na grafie o m^2         *
 *             krawedziach, ale na kazde zapytanie odpowiada szybko.     *
 *                                                                       *
 *************************************************************************)

const MAXN = 400;
const MAXD = 100;
const ROZMIAR_ALF = 26;
const ROZM_G = MAXN*MAXN*(ROZMIAR_ALF+1);
const ZNAK_HASH = chr(ord('a') + ROZMIAR_ALF);
const INF = 100000000;

type Wwezel = ^wezel;
    wezel = record
    
    nastepny: Wwezel;
    dokad : longint;
end;

type wierzcholek = record
    lista_krawedzi: Wwezel;
end;


procedure dodaj(var w: wierzcholek; d: longint);
    var nowy: ^wezel;
begin 
    new(nowy);
    nowy^.dokad := d;
    nowy^.nastepny := w.lista_krawedzi;
    w.lista_krawedzi := nowy;
 end;

//Implementacja kolejki

var kolejka : array[0..ROZM_G-1] of longint;
    poczatek_kolejki, koniec_kolejki : longint;

procedure czysc;
begin 
    poczatek_kolejki := 0;
    koniec_kolejki := 0;
 end;

procedure wstaw(nr: longint);
begin 
    kolejka[koniec_kolejki] := nr;
    inc(koniec_kolejki);
 end;

function wyjmij: longint;
begin 
    wyjmij := kolejka[poczatek_kolejki];
    inc(poczatek_kolejki);
 end;

function czy_pusta(): boolean;
begin 
    czy_pusta := (koniec_kolejki = poczatek_kolejki);
 end;

function stworz_indeks(w1, w2:longint): longint;
begin 
    stworz_indeks:= w1*MAXN + w2;    
 end;

var graf, graf_trans : array[0..MAXN-1, 0..ROZMIAR_ALF-1] of wierzcholek;

var odleglosc, poprzedni : array[0..ROZM_G-1] of longint;
    czym_doszlismy : array [0..ROZM_G-1] of char;

procedure wczytaj_graf(n, m :longint);
     var a, b, i, k, j : longint;
	zn : char;
begin 
    for  i:=0 to n-1 do
    begin 
	for  k:=0 to ROZMIAR_ALF-1 do
	    graf[i,k].lista_krawedzi := nil;
	    graf_trans[i,k].lista_krawedzi := nil;
	for  j:=0 to n-1 do
	    if(i <> j) then
		odleglosc[stworz_indeks(i, j)] := INF
	    else
		odleglosc[stworz_indeks(i, j)] := 0;
     end;

    for  i:=0 to m-1 do
    begin 
	read(a, b, zn, zn);
	dec(a);
	dec(b);
	dodaj(graf[a][ord(zn)-ord('a')], b);
	dodaj(graf_trans[b][ord(zn)-ord('a')], a);
	odleglosc[stworz_indeks(a, b)] := 1;
	czym_doszlismy[stworz_indeks(a, b)] := zn;
     end;
 end;

procedure bfs(n: longint);
var akt, poczatek, w1, w2, dokad, i, j, k : longint;
    pptr, pptr2 : Wwezel;
begin 


    for k:=0 to 1 do
    for i:=0 to n-1 do
	for  j:=0 to n-1 do
	begin 
	    poczatek := stworz_indeks(i, j);
	    if(odleglosc[poczatek] = k) then
	    begin 
		poprzedni[poczatek] := -1;
		wstaw(poczatek);
	     end;
	 end;

    while( not czy_pusta) do
    begin 
	akt := wyjmij;
	w1 := akt div MAXN;
	w2 := akt mod MAXN;
	
	for k:=0 to ROZMIAR_ALF-1 do
	begin
	    pptr := graf[w2, k].lista_krawedzi;
	    while (pptr <> nil) do
	    begin
		pptr2 := graf_trans[w1, k].lista_krawedzi;
	    	while (pptr2 <> nil) do
	    	begin
		   dokad := stworz_indeks(pptr2^.dokad, pptr^.dokad);
		   if(odleglosc[dokad] > odleglosc[akt] + 2) then
		   begin 
		    odleglosc[dokad] := odleglosc[akt] + 2;
		    poprzedni[dokad] := akt;
		    czym_doszlismy[dokad] := chr(k+ord('a'));
		    wstaw(dokad);
		   end;
		   pptr2 := pptr2^.nastepny;
  		end;
		pptr := pptr^.nastepny;
	     end;
	end;
     end;
 end;

procedure zapytanie(p, k: longint);
var akt, dl, i : longint;
    wynik : ansistring;
begin 

    akt := stworz_indeks(p, k);
    if(odleglosc[akt] = INF) then
    begin 
	writeln('-1');
	Exit;
     end;
    
    dl := odleglosc[akt];
    write(dl, ' ');
    for i:=0 to dl do
	wynik := wynik + ' ';
    while(poprzedni[akt] <> -1) do
    begin 
	wynik[dl div 2 - odleglosc[akt] div 2+1] := czym_doszlismy[akt];
	wynik[dl div 2 + (odleglosc[akt]-1) div 2+1] := czym_doszlismy[akt];
	akt := poprzedni[akt];
     end;
    if(odleglosc[akt] = 1) then
	wynik[dl div 2+1] := czym_doszlismy[akt];
    writeln(wynik);
 end;


var n, m, d, i : longint;
    zapytania : array [0..MAXD-1] of longint;

begin 
    read(n, m);
    wczytaj_graf(n, m);
    bfs(n);
    read(d);
    for i:=0 to d-1 do
	read(zapytania[i]);
    for  i:=0 to d-2 do
	zapytanie(zapytania[i]-1, zapytania[i+1]-1);
end.

