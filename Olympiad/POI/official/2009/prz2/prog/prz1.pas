(*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Przechadzka Bajtusia (PRZ)                                *
 *   Plik:     prz1.pas                                                  *
 *   Autor:    Jakub Lacki                                               *
 *   Opis:     Rozwiazanie wzorcowe. Czas: O((A+d)*n^2+m*n);             *
 *             Pamiec O(A*n^2)                                           *
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
    znak :char;
end;

type wierzcholek = record
    lista_krawedzi: Wwezel;
end;


procedure dodaj(var w: wierzcholek; d: longint; z : char);
    var nowy: ^wezel;
begin 
    new(nowy);
    nowy^.dokad := d;
    nowy^.znak := z;
    nowy^.nastepny := w.lista_krawedzi;
    w.lista_krawedzi := nowy;
 end;

 // Implementacja kolejki

var kolejka : array[0..ROZM_G-1] of longint;
    poczatek_kolejki, koniec_kolejki : longint;


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

// Funkcja generujaca jednowymiarowe indeksy wierzcholkow w grafie par

function stworz_indeks(w1, w2: longint; znak : char): longint;
begin 
    stworz_indeks:= w1*MAXN*(ROZMIAR_ALF+1) + w2*(ROZMIAR_ALF+1) + ord(znak)-ord('a');    
 end;


var odleglosc, poprzedni : array[0..ROZM_G-1] of longint;
    czym_doszlismy : array [0..ROZM_G-1] of char;
    graf : array[0..MAXN-1, 0..ROZMIAR_ALF] of wierzcholek;
    graf_trans : array[0..MAXN-1] of wierzcholek;

procedure wczytaj_graf(n, m : longint);
    var a, b, i, k : longint;
	zn : char;
begin 

    for  k:=0 to ROZMIAR_ALF do
    for  i:=0 to n-1 do
	graf[i,k].lista_krawedzi := nil;
    for  i:=0 to n-1 do
	graf_trans[i].lista_krawedzi := nil;

    for  i:=0 to m-1 do
    begin 
	read(a, b, zn, zn);
	dec(a);
	dec(b);
	dodaj(graf[a,ord(zn)-ord('a')], b, zn);
	dodaj(graf_trans[b], a, zn);
     end;
 end;


procedure znajdz_koncowe(n : longint);
    var ind, i, j, k : longint;
	pptr : Wwezel;
begin 
    for i:=0 to n-1 do
	for j:=0 to n-1 do
	    for  k:=0 to ROZMIAR_ALF do
	    begin 
		ind := stworz_indeks(i, j, chr(k+ord('a')));
		if(i = j) and (k = ROZMIAR_ALF) then
		    odleglosc[ind] := 0
		else
		    odleglosc[ind] := INF;
	     end;

    for  k:=0 to ROZMIAR_ALF do
    for  i:=0 to n-1 do
    begin
	pptr := graf[i,k].lista_krawedzi;
	while (pptr <> nil) do
	begin
	    odleglosc[stworz_indeks(i, pptr^.dokad, ZNAK_HASH)] := 1;
	    czym_doszlismy[stworz_indeks(i, pptr^.dokad, ZNAK_HASH)] := pptr^.znak;
	    pptr := pptr^.nastepny;
	end;
    end;
 end;
    

procedure bfs(n : longint);
var akt, poczatek, w1, w2, dokad, i, j, k, lit : longint;
    pptr : Wwezel;
begin 

    for k:=0 to 1 do
    for i:=0 to n-1 do
	for  j:=0 to n-1 do
	begin 
	    poczatek := stworz_indeks(i, j, ZNAK_HASH);
	    if(odleglosc[poczatek] = k) then
	    begin 
		poprzedni[poczatek] := -1;
		wstaw(poczatek);
	     end;
	 end;
    while( not czy_pusta) do
    begin 
	akt := wyjmij;
	w1 := akt div ((ROZMIAR_ALF+1)*MAXN);
	w2 := (akt div (ROZMIAR_ALF+1)) mod MAXN;
	lit := akt mod (ROZMIAR_ALF+1);
	if(lit = ROZMIAR_ALF) then
	begin 
	    pptr := graf_trans[w1].lista_krawedzi;
	    while (pptr <> nil) do
	    begin 
		dokad := stworz_indeks(pptr^.dokad, w2, pptr^.znak);
		if(odleglosc[dokad] > odleglosc[akt] + 1) then
		begin 
		    odleglosc[dokad] := odleglosc[akt] + 1;
		    poprzedni[dokad] := akt;
		    czym_doszlismy[dokad] := pptr^.znak;
		    wstaw(dokad);
		 end;
		pptr := pptr^.nastepny;
	     end;
	 end
	else
	begin 
	    pptr := graf[w2,lit].lista_krawedzi;
	    while (pptr<>nil) do
	    begin 
		dokad := stworz_indeks(w1, pptr^.dokad, ZNAK_HASH);
		if(odleglosc[dokad] > odleglosc[akt] + 1) then
		begin 
		    odleglosc[dokad] := odleglosc[akt] + 1;
		    poprzedni[dokad] := akt;
		    czym_doszlismy[dokad] := pptr^.znak;
		    wstaw(dokad);
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
    
    akt := stworz_indeks(p, k, ZNAK_HASH);
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
	if((dl-odleglosc[akt]) mod 2 = 0) then
	    wynik[(dl-odleglosc[akt]) div 2 + 1] := czym_doszlismy[akt]
	else
	    wynik[dl-1-(dl-odleglosc[akt]) div 2 + 1] := czym_doszlismy[akt];
	akt := poprzedni[akt];
     end;
    if(odleglosc[akt] = 1) then
	wynik[dl div 2 + 1] := czym_doszlismy[akt];
    writeln(wynik);
 end;


var n, m, d, i : longint;
    zapytania : array [0..MAXD-1] of longint;

begin 
    read(n, m);
    wczytaj_graf(n, m);
    znajdz_koncowe(n);
    bfs(n);
    read(d);
    for i:=0 to d-1 do
	read(zapytania[i]);
    for  i:=0 to d-2 do
	zapytanie(zapytania[i]-1, zapytania[i+1]-1);
end.

