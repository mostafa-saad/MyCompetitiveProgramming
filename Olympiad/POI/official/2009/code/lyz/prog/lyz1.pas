(*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Lyzwy (LYZ)                                               *
 *   Plik:     lyz1.pas                                                  *
 *   Autor:    Juliusz Sompolski                                         *
 *   Opis:     Rozwiazanie wzorcowe O((n+m)*log(n))                      *
 *                                                                       *
 *************************************************************************)

const MAX_N=200000;
const MAX_N2=262144;
const KORZEN=1;

var n, m, k, d:longint;


{ Drzewo przedzialowe }
type WEZEL = record
	suma, mx_lewy, mx_prawy, mx:int64
end;

var drz:Array[1..2*MAX_N2] of WEZEL;
    ile:longint;

function rodzic(v:longint):longint; begin rodzic := v div 2; end;
function lsyn(v:longint):longint; begin lsyn := 2*v; end;
function psyn(v:longint):longint; begin psyn := 2*v+1; end;
function max(a,b:int64):int64;
begin
	if a > b then max := a else max := b;
end;
function min(a,b:longint):longint;
begin
	if a < b then min := a else min := b;
end;

{ Zmienia ilosc czlonkow o rozmiarze stopy x o w i uaktualnia drzewo }
procedure ustaw(x,w:longint);
	var v:longint;
begin
	{ Ustawia wartosc w wierzcholku reprezentujacym przedzial jednoelementowy }
	v := ile + x;
	drz[v].suma := drz[v].suma + w;
	drz[v].mx := max(drz[v].suma, 0);
	drz[v].mx_lewy := drz[v].mx; drz[v].mx_prawy := drz[v].mx;

	{ Poprawia idac w gore drzewa }
	while (v <> KORZEN) do begin
		v := rodzic(v);
		drz[v].suma := drz[lsyn(v)].suma + drz[psyn(v)].suma;
		drz[v].mx_lewy := max(drz[lsyn(v)].mx_lewy, drz[lsyn(v)].suma + drz[psyn(v)].mx_lewy);
		drz[v].mx_prawy := max(drz[psyn(v)].mx_prawy, drz[psyn(v)].suma + drz[lsyn(v)].mx_prawy);

		drz[v].mx := max(drz[lsyn(v)].mx, drz[psyn(v)].mx);
		drz[v].mx := max(drz[v].mx, drz[lsyn(v)].mx_prawy + drz[psyn(v)].mx_lewy);
	end;
end;

var i,r,x:longint;

BEGIN
	{ Inicjalizacja }
	read(n); read(m); read(k); read(d);
	ile := 1;
	while (ile <= n-d) do ile *= 2;
	for i := 1 to n-d do ustaw(i, -k);
	
	{ Przetwarzanie zdarzen }
	for i := 1 to m do begin
		read(r); read(x);
		ustaw(r, x);
		if (drz[KORZEN].mx <= int64(k) * int64(d)) then writeln('TAK') else writeln('NIE');
	end;
END.
