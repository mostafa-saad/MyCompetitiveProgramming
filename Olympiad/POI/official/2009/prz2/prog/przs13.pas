(*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Przechadzka Bajtusia (PRZ)                                *
 *   Plik:     przs13.pas                                                *
 *   Autor:    Jakub Lacki                                               *
 *   Opis:     Rozwiazanie nieoptymalne. Dziala na grafie o m^2          *
 *             krawedziach i dla kazdego zapytania wykonuje BFSa.        *
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

procedure wczytaj_graf(n, m :longint);
     var a, b, i, k : longint;
	zn : char;
begin 
    for  i:=0 to n-1 do
    begin 
	for  k:=0 to ROZMIAR_ALF-1 do
	    graf[i,k].lista_krawedzi := nil;
	    graf_trans[i,k].lista_krawedzi := nil;
     end;

    for  i:=0 to m-1 do
    begin 
	read(a, b, zn, zn);
	dec(a);
	dec(b);
	dodaj(graf[a][ord(zn)-ord('a')], b);
	dodaj(graf_trans[b][ord(zn)-ord('a')], a);
     end;
 end;

var czy_koncowy : array [0..ROZM_G-1] of longint;
    znak_koncowy : array[0..ROZM_G-1] of char;

procedure buduj_graf(n : longint);
var i, j, l : longint;
    pptr : Wwezel;
begin 
    for i:=0 to n-1 do
	for  j:=0 to n-1 do
	    czy_koncowy[stworz_indeks(i, j)] := 0;

    for i:=0 to n-1 do
	for  l:=0 to ROZMIAR_ALF-1 do
	begin
		pptr := graf[i,l].lista_krawedzi;
		while(pptr <> nil) do
		begin
			czy_koncowy[stworz_indeks(i, i)] := 1;
			czy_koncowy[stworz_indeks(i, pptr^.dokad)] := 2;
			znak_koncowy[stworz_indeks(i, pptr^.dokad)] := chr(l+ord('a'));
			pptr := pptr^.nastepny;
		end;
	end;
 end;
    
var odleglosc, poprzedni : array[0..ROZM_G-1] of longint;
    czym_doszlismy : array [0..ROZM_G-1] of char;

procedure bfs(n, poczatek : longint);
var akt, w1, w2, dokad, i, j, k, dl : longint;
    min_odleglosc, najblizszy_w, ind : longint;
    pptr, pptr2 : Wwezel;
    wynik : ansistring;
begin 
    for i:=0 to n-1 do
	for  j:=0 to n-1 do
	    odleglosc[stworz_indeks(i, j)] := INF;


    odleglosc[poczatek] := 0;
    poprzedni[poczatek] := -1;

    czysc;
    wstaw(poczatek);
    while( not czy_pusta) do
    begin 
	akt := wyjmij;
	w1 := akt div MAXN;
	w2 := akt mod MAXN;
	for k:=0 to ROZMIAR_ALF-1 do
	begin
	    pptr := graf[w1, k].lista_krawedzi;
	    while (pptr <> nil) do
	    begin
		pptr2 := graf_trans[w2, k].lista_krawedzi;
	    	while (pptr2 <> nil) do
	    	begin
		   dokad := stworz_indeks(pptr^.dokad, pptr2^.dokad);
		   if(odleglosc[dokad] > odleglosc[akt] + 1) then
		   begin 
		    odleglosc[dokad] := odleglosc[akt] + 1;
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

 
    najblizszy_w := -1;
    min_odleglosc := INF;
    for i:=0 to n-1 do
    for j:=0 to n-1 do
	begin 
	    ind := stworz_indeks(i, j);
	    if((czy_koncowy[ind]<>0) and (2*odleglosc[ind]+czy_koncowy[ind]-1 < min_odleglosc)) then
	    begin 
		min_odleglosc := 2*odleglosc[ind]+czy_koncowy[ind]-1;
		najblizszy_w := ind;
	     end;
	 end;
    
    if(najblizszy_w = -1) then
	writeln('-1')
    else
    begin 
	dl := min_odleglosc;
	for i:=0 to dl do
		wynik := wynik + ' ';
	if(czy_koncowy[najblizszy_w] = 2) then
	    wynik[dl div 2 +1] := znak_koncowy[najblizszy_w];
	
	write(dl, ' ');
	akt := najblizszy_w;
	while(akt <> poczatek) do
	begin 
	    wynik[odleglosc[akt]] := czym_doszlismy[akt];
	    wynik[dl-odleglosc[akt]+1] := czym_doszlismy[akt]; 
	    akt := poprzedni[akt];
	 end;
	writeln(wynik);
     end;

 end;


var n, m, d, i : longint;
    droga : array [0..MAXD-1] of longint;

begin 
    read(n, m);
    wczytaj_graf(n, m);
    buduj_graf(n);
    read(d);
    for i:=0 to d-1 do
	read(droga[i]);

    for  i:=0 to d-2 do
	bfs(n, stworz_indeks(droga[i]-1, droga[i+1]-1)); 
end.

