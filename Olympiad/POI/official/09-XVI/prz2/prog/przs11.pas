(*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Przechadzka Bajtusia (PRZ)                                *
 *   Plik:     przs11.pas                                                *
 *   Autor:    Jakub Lacki                                               *
 *   Opis:     Rozwiazanie nieoptymalne. Dla kazdego zapytania           *
 *             wykonuje BFSa.                                            *
 *                                                                       *
 *************************************************************************)

const MAXN = 400;
const MAXD = 100;
const ROZMIAR_ALF = 26;
const ROZM_G = MAXN*MAXN*(ROZMIAR_ALF+1);
const ZNAK_HASH = chr(ord('a') + ROZMIAR_ALF);
const INF = 100000000;


//Reprezentacja grafu

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

 procedure czysc;
 begin
    poczatek_kolejki := 0;
    koniec_kolejki := 0;
end;

// Funkcja generujaca jednowymiarowe indeksy wierzcholkow w grafie par

function stworz_indeks(w1, w2: longint; znak : char): longint;
begin 
    stworz_indeks:= w1*MAXN*(ROZMIAR_ALF+1) + w2*(ROZMIAR_ALF+1) + ord(znak)-ord('a');    
 end;


var odleglosc, poprzedni : array[0..ROZM_G-1] of longint;
    czym_doszlismy : array [0..ROZM_G-1] of char;
    graf_trans : array[0..MAXN-1, 0..ROZMIAR_ALF] of wierzcholek;
    graf : array[0..MAXN-1] of wierzcholek;
czy_koncowy : array [0..ROZM_G-1] of boolean;

procedure wczytaj_graf(n, m : longint);
    var a, b, i, k : longint;
	zn : char;
begin 

    for  k:=0 to ROZMIAR_ALF do
    for  i:=0 to n-1 do
	graf_trans[i,k].lista_krawedzi := nil;
    for  i:=0 to n-1 do
	graf[i].lista_krawedzi := nil;

    for  i:=0 to m-1 do
    begin 
	read(a, b, zn, zn);
	dec(a);
	dec(b);
	dodaj(graf_trans[b,ord(zn)-ord('a')], a, zn);
	dodaj(graf[a], b, zn);
     end;
 end;

procedure znajdz_koncowe(n : longint);
    var ind, i, j, k : longint;
begin
    for i:=0 to n-1 do
	for j:=0 to n-1 do
	for k:=0 to ROZMIAR_ALF do
	begin
		ind := stworz_indeks(i, j, chr(k+ord('a')));
		if(i = j) then
		    czy_koncowy[ind] := true
		else
		    czy_koncowy[ind] := false;
	end;
end;
    
procedure odtworz_wynik(poczatek, n : longint);
var akt, dl, ind, najblizszy, min_odleglosc, i, k : longint;
    wynik : ansistring;
begin
    min_odleglosc := INF;
    for i:=0 to n-1 do
	for k:=0 to ROZMIAR_ALF do
	begin
	    ind := stworz_indeks(i, i, chr(k+ord('a')));
	    if(odleglosc[ind] < min_odleglosc) then
	    begin
		min_odleglosc := odleglosc[ind];
		najblizszy := ind;
	    end;
	end;

    akt := najblizszy;
    if(min_odleglosc = INF) then
    begin
	writeln('-1');
	exit;
    end;
   
    wynik := ''; 
    dl := odleglosc[akt];
    write(dl, ' ');
    for i:=0 to dl do
	wynik := wynik + ' ';

    while(poprzedni[akt] <> -1) do
    begin
	if(odleglosc[akt] mod 2 <> 0) then
	    wynik[odleglosc[akt] div 2 + 1] := czym_doszlismy[akt]
	else
	    wynik[dl-odleglosc[akt] div 2 + 1] := czym_doszlismy[akt];
	akt := poprzedni[akt];
    end;
    writeln(wynik);
end;

procedure bfs(n, p, k: longint);
var akt, poczatek, w1, w2, dokad, i, j, l, lit : longint;
    pptr : Wwezel;
    znalazlem : boolean;

begin
    czysc;  
    for l:=0 to ROZMIAR_ALF do
    for i:=0 to n-1 do
	for j:=0 to n-1 do
	begin
	    akt := stworz_indeks(i, j, chr(l+ord('a')));
	    odleglosc[akt] := INF;
	end;
    
    poczatek := stworz_indeks(p, k, ZNAK_HASH);
    odleglosc[poczatek] := 0;
    poprzedni[poczatek] := -1;
    wstaw(poczatek);

    znalazlem := false;
    while((not czy_pusta) and (not znalazlem)) do
    begin 
	akt := wyjmij;
	w1 := akt div ((ROZMIAR_ALF+1)*MAXN);
	w2 := (akt div (ROZMIAR_ALF+1)) mod MAXN;
	lit := akt mod (ROZMIAR_ALF+1);
	if(lit = ROZMIAR_ALF) then
	begin 
	    pptr := graf[w1].lista_krawedzi;
	    while (pptr <> nil) do
	    begin 
		dokad := stworz_indeks(pptr^.dokad, w2, pptr^.znak);
		if(odleglosc[dokad] > odleglosc[akt] + 1) then
		begin 
		    odleglosc[dokad] := odleglosc[akt] + 1;
		    poprzedni[dokad] := akt;
		    czym_doszlismy[dokad] := pptr^.znak;
		    if(czy_koncowy[dokad]) then
		    begin
			znalazlem := true;
			break;
		    end;
		    wstaw(dokad);
		end;
		pptr := pptr^.nastepny;
	     end;
	end
	else
	begin
	    pptr := graf_trans[w2,lit].lista_krawedzi;
	    while (pptr<>nil) do
	    begin 
		dokad := stworz_indeks(w1, pptr^.dokad, ZNAK_HASH);
		if(odleglosc[dokad] > odleglosc[akt] + 1) then
		begin 
		    odleglosc[dokad] := odleglosc[akt] + 1;
		    poprzedni[dokad] := akt;
		    czym_doszlismy[dokad] := pptr^.znak;
		    if(czy_koncowy[dokad]) then
		    begin
			znalazlem := true;
			break;
		    end;
		    wstaw(dokad);
		end;
	    pptr := pptr^.nastepny;
	    end;
	 end;
     end;
    odtworz_wynik(poczatek, n);
end;

var n, m, d, i : longint;
    zapytania : array [0..MAXD-1] of longint;

begin 
    read(n, m);
    wczytaj_graf(n, m);
    znajdz_koncowe(n);
    read(d);
    for i:=0 to d-1 do
	read(zapytania[i]);
    for  i:=0 to d-2 do
	bfs(n, zapytania[i]-1, zapytania[i+1]-1);
end.
