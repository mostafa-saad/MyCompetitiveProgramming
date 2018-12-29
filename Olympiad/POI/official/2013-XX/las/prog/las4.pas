(*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Laser                                         *
 *   Autor:                Jakub Sygnowski                               *
 *   Zlozonosc czasowa:    O(nk log n)                                   *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wzorcowe                          *
 *                                                                       *
 *************************************************************************)

program las;

const MAXN = 500007;
const MAXK = 101;
const INF = 1000000007;

type
	pkt = record
		x : longint;
		y : longint;
	end;
	pair = record
		fst : pkt;
		snd : longint;
	end;
var
	punkty : array[0..2*MAXN] of pair;
	poczatek, koniec, temp : pkt;
	n, k, wynik : longint;
	tab, przec, zamkniete, prawo : array[0..2*MAXN] of longint;
	numer : array[0..2*MAXN] of longint;
	wspolliniowe : array[0..2*MAXN] of boolean;
	dp : array[0..1, 0..2*MAXN] of longint;
(* punkty:
 *	fst - wspolrzedne punktu
 * 	snd: -1 jesli jest to koniec odcinka, 1 jesli poczatek
 * tab - tablica przechowujaca poczatki i konce odcinkow
 * po zrobieniu sortowania katowego. Liczba a (-a)
 * na pozycji i oznacza, ze i-te w kolejnosci zdarzenie 
 * to poczatek (koniec) a-tego odcinka (w kolejnosci
 * posortowania katowego)
 * przec - mowi ile odcinkow przetnie strzala wystrzelona
 * w kierunku i-tego (w kolejnosci posortowania
 * katowego) punktu (z dokladnoscia do punktow
 * wspolliniowych)
 * numer - nowy numer nadany odcinkowi. oznacza numer
 * konca danego odcinka posrod innych
 * zamkniete - najwiekszy numer odcinka takiego,
* ze konczy sie on wczesniej niz i-ty punkt
 * prawo - numer najwiekszego odcinka takiego, ze 
 * jest on przeciety przy strzale w punkt i
 * wspolliniowe - czy punkt i oraz i+1 leza na tej samej
 * prostej razem z 0,0?
 * dp[1,2] -numer najwczesniejszego konca odcinka, takiego, ze za pomocą
 * ([1]+1) strzalow w punkty z odcinkow o numerach [1..nr] mozna uzyskac
 * wynik [2] (jesli nie mozna uzyskac takiego wyniku
 * to INF)
 * inaczej: 'jak duzo poczatkowych odcinkow potrzebuje,
 * aby uzyskac wynik [2], zakladajac, ze zrobie
 * [1]+1 strzalow
 * uwaga: strzelam tylko w konce i poczatki odcinkow
 *)

function min(a,b: longint): longint;
begin
	if a < b then min := a
	else min := b;
end;

function max(a,b: longint): longint;
begin
	if a < b then max := b
	else max := a;
end;

function najwiekszy(strzalow, nastepny : longint) : longint;
(* najwiekszy wynik([2] z dp), jaki mozna uzyskac robiac 
 * (strzalow+1) strzalow, z ktorych najdalszy (w punkt
 * z odcinka o najwiekszym numerze) jest mniejszy niz 'nastepny'
 *)
var
	lowb, upb, proba : longint;
begin
	lowb := 0;
	upb := n;
	(* zalozenia (niezmiennik):
	 * dp[strzalow,lowb] < nastepny
	 * dp[strzalow,upb] >= nastepny
	 *)
	while lowb <> upb-1 do 
	begin
		proba := (lowb+upb) div 2;
		if dp[strzalow, proba] < nastepny then
			lowb := proba
		else
			upb := proba;
	end;
	najwiekszy := lowb;
end;

procedure inicjalizacja();
var
	i,j : longint;
begin
	for i:=0 to 1 do begin
		dp[i,0] := 0;
		for j:=0 to n-1 do
			dp[i,(j+1)] := INF;
	end;
end;

procedure pierwszywiersz();
(* wylicza dp[0], przec, prawo, zamkniete. zamiata.
 *)
var
	przecietych, najdalszy, ostatni, last, i,j : longint;
(* przecietych - ile odcinkow jest aktualnie przecietych
 * najdalszy - najwiekszy sposrod numerow odcinkow, ktore
 * zostaly juz 'otwarte'
 * ostatni - najwiekszy sposrod numerow odcinkow, ktore zostaly
 * juz zamkniete
 * last - pierwszy sposrod punktow, ktore leza na tej samej prostej
 * (wychodzacej z 0,0), co aktualny punkt; wszystkie takie punkty 
 * przetwarzam jednoczesnie
 *)
begin
	przecietych:=0;
	najdalszy:=0;
	ostatni:=0;
	last:=0;
	for i:=0 to (2*n)-1 do begin
		if wspolliniowe[i] then
			Continue
		else begin
		for j:=last to i do begin
			zamkniete[j] := ostatni;
			if tab[j] > 0 then begin
				przecietych := przecietych+1;
				najdalszy := max(najdalszy, tab[j]);
			end;
		end;
		dp[0, przecietych] := min(dp[0, przecietych],najdalszy);
		for j:=last to i do begin
			przec[j] := przecietych;
			prawo[j] := najdalszy;
		end;
		for j:=last to i do begin
		if tab[j] < 0 then begin
			przecietych := przecietych-1;
			ostatni := ostatni+1;
			end;
		end;
		last := i+1;
		end;
	end;
	for j:=n-1 downto 0 do
		dp[0, j] := min(dp[0, j], dp[0, j+1]);
end;

procedure liczdp();
var 
	i, j, wczesniej : longint;
begin
	for i:=1 to k-1 do begin
		for j:=0 to (2*n)-1 do begin
			if tab[j] > 0 then begin
(* mam dany poczatek odcinka. chce uzyskac jak najlepszy wynik,
 * oddajac i-1 strzalow w odcinki o numerach < j (tzn. lezacych 
 * na lewo od punktu j) oraz strzelajac raz w koniec odcinka
 * zaczynajacego sie w j (jest to tab[j]-ty koniec w kolejnosci
 * posortowania katowego)
 *)
			wczesniej := najwiekszy((i-1) mod 2, zamkniete[j] + 1);
			dp[i mod 2, wczesniej+przec[j]] := 
				min(dp[i mod 2, wczesniej+przec[j]],prawo[j]);
			end
			else begin
			wczesniej := najwiekszy((i-1) mod 2,zamkniete[j]+1);
			dp[i mod 2,wczesniej+przec[j]] := 
				min(dp[i mod 2,wczesniej+przec[j]],prawo[j]);
			end; (*???*)
		end;
		for j:=n-1 downto 0 do 
			dp[i mod 2,j] := min(dp[i mod 2,j], dp[i mod 2,j+1]);
(* rozpropaguj korzystne zmiany, zeby mozna bylo korzystac
 * z wyszukiwania binarnego
 *)		
	end;
end;

function det(a, b: pkt): int64;
begin
	det := int64(a.x)*int64(b.y) - int64(a.y)*int64(b.x);
end;

function compare(a,b: pkt): boolean;

begin
	if det(a,b) <> 0 then
		compare := det(a,b) > 0
	else
		compare := int64(a.x)*int64(a.x) + int64(a.y)*int64(a.y) < int64(b.x)*int64(b.x) + int64(b.y)*int64(b.y);
end;

function compare2(a,b: pair): boolean;

begin
	if det(a.fst, b.fst) <> 0 then
		compare2 := det(a.fst, b.fst) > 0
	else if a.snd <> b.snd then
		compare2 := a.snd > b.snd
	else
		compare2 := compare(a.fst, b.fst);
end;

(*mergesort*)

procedure merge(a1, a2, b1, b2 : longint);
var
	i, start : longint;
	tmp : array[0..2*MAXN] of pair;
begin
	start := a1;
	i := start;
	while (a1 <= a2) and (b1 <= b2) do begin
		if compare2(punkty[a1], punkty[b1]) then begin
			tmp[i] := punkty[a1];
			i := i+1;
			a1 := a1 + 1;			
		end
		else begin
			tmp[i] := punkty[b1];
			b1 := b1 + 1;
			i := i+1;
		end;
	end;
	while a1 <= a2 do begin
		tmp[i] := punkty[a1];
		a1 := a1 + 1;
		i := i + 1;
	end;
	while b1 <= b2 do begin
		tmp[i] := punkty[b1];
		b1 := b1 + 1;
		i := i + 1;
	end;
	for i:=start to b2 do
		punkty[i] := tmp[i];
end;

procedure sort(a, b : longint);
var
	srodek : longint;
begin
	if a < b then begin
		srodek := (a+b) div 2;
		sort(a,srodek);
		sort(srodek+1,b);
		merge(a,srodek,srodek+1,b);
	end;
end;

procedure naprosta();
(* Robi sortowanie katowe po punktach, zmieniajac problem
 * z dwuwymiarowego na jednowymiarowy
 *)
var 
	i, otwarty : longint;

begin
	sort(0,2*n-1);
	otwarty := 1;
	for i:=0 to (2*n-1) do begin
		if (i <> 2*n -1) and (det(punkty[i].fst, punkty[i+1].fst) = 0) then
			wspolliniowe[i] := true;
		if punkty[i].snd < 0 then begin
			tab[i] := -otwarty;
			numer[-punkty[i].snd] := otwarty;
			otwarty := otwarty+1;
		end;
	end;
	for i:=0 to (2*n-1) do 
		if punkty[i].snd > 0 then
			tab[i] := numer[punkty[i].snd];
end;

var
	i,j : longint;
begin
	wynik := 0;
	readln(k,n);
	for i:=0 to n-1 do begin
		readln(poczatek.x, poczatek.y, koniec.x, koniec.y);
		if compare(koniec, poczatek) then begin
			temp := poczatek;
			poczatek := koniec;
			koniec := temp;
		end;
		punkty[2*i].fst := poczatek;
	        punkty[2*i].snd := i+1;
		punkty[2*i+1].fst := koniec;
		punkty[2*i+1].snd := -i-1;
	end;
	naprosta();
	inicjalizacja();
	pierwszywiersz();
	liczdp();
	for i:=0 to 1 do
		for j:=0 to n do
			if dp[i,j] <> INF then
				wynik := max(wynik, j);
(* cos roznego od INF w dp[i][j] oznacza, ze mozna, korzystajac dokladnie 
 * z i strzalow i strzelajac w odcinki, ktorych konce maja numery
 * w przedziale [1..dp[i][j]] uzyskac wynik j
 *)		
	writeln(wynik);
end.
