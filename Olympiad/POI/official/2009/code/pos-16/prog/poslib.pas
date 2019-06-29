(*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Poszukiwania (POS)                                        *
 *   Plik:     poslib.pas                                                *
 *   Autor:    Juliusz Sompolski                                         *
 *   Opis:     Biblioteka interaktywna                                   *
 *                                                                       *
 *************************************************************************)

{
	Mozliwe strategie:
	S_SPRAWIEDLIWA: odpowiada dla z gory wybranego pietra
	S_PESYMISTYCZNA: udziela odpowiedzi tak, aby otrzymywac pesymistyczny koszt.
	S_OPTYMISTYCZNA: udziela odpowiedzi tak, aby poprawiac szacowanie na pesymistyczny koszt.
}
unit poslib;

interface

procedure inicjuj(var n_, a_, b_: longint);

function pytaj(c : char; x: longint): boolean;

procedure odpowiedz(wynik: longint);

implementation

const MAGIC=512345678;
const MAGIC_BEGIN=-92345678;
const MAGIC_END=-98765432;
const MAGIC_OUT=-880403;
const MAXRAND=1000000000;

const MAXN=1000000000;
const MAXAB=10000;

const MIN_S=0;
const MAX_S=2;
const S_SPRAWIEDLIWA=0;
const S_PESYMISTYCZNA=1;
const S_OPTYMISTYCZNA=2;

const OK=1;
const ERR=0;

var Q:array[0..100*MAXAB] of longint; // Q[i] - maksymalna liczba pieter wsrod ktorych mozna znalezc odpowiedz kosztem i
var l,r:longint; // przedzial w ktorym Bajtek moze wiedziec, ze jest odpowiedz.
var w:longint; // maksymalny koszt jaki pesymistycznie musi jeszcze poniesc Bajtek
var koszt:int64; // koszt jaki poniosl juz Bajtek

var N,A,B:longint; // dane
var strategia:integer; // strategia wykorzystywana przez biblioteke
var pietro:longint; // pietro - jezeli S_SPRAWIEDLIWA

var zainicjowane:boolean = FALSE; // czy zostalo juz wywolana funkcja inicjuj

var use_interactive:boolean = FALSE;

procedure interactive_inicjuj(var n_, a_, b_: longint);
begin
	if (N < 1) or (N > MAXN) or (A < 1) or (A > MAXAB) or (B < 1) or (B > MAXAB) or (pietro < 1) or (pietro > N) then begin
		writeln('Nieprawidlowe dane!');
		halt(0);
	end;
	koszt := 0;
	n_ := N; a_ := A; b_ := B;
end;

function interactive_pytaj(c : char; x: longint): boolean;
begin
	if (c = 'W') then begin
		if (pietro > x) then begin
			koszt := koszt+A;
			interactive_pytaj := TRUE;
		end else begin
			koszt := koszt+B;
			interactive_pytaj := FALSE;
		end;
	end else begin (* c == 'N' *)
		if(pietro < x) then begin
			koszt := koszt+A;
			interactive_pytaj := TRUE;
		end else begin
			koszt := koszt+B;
			interactive_pytaj := FALSE;
		end;
	end;
end;

procedure interactive_odpowiedz(wynik: longint);
begin
    writeln(MAGIC_OUT);
	if (wynik = pietro) then begin
        writeln('wynik=1 n=', N, ' a=', A, ' b=', B, 'strategia=-1 pietro=', pietro);
        writeln('Bajtkowi udalo sie zgadnac. Wydal ', koszt, ' bajtalarow.');
	end else begin
        writeln('wynik=0 n=', N, ' a=', A, ' b=', B, 'strategia=-1 pietro=', pietro);
        writeln('Bajtek nie zgadl. Podal pietro', wynik, ', a powinien ', pietro, '. Wydal ', koszt, ' bajtalarow.');
	end;
	halt(0);
end;

{
Oblicza lub zwraca spamietane Q[i]
}
function q_(i:longint):longint;
begin
	if i < 0 then begin q_ := 0; exit; end;
	if Q[i] = 0 then begin // jesli nie bylo jeszcze obliczone, to oblicz
		{ Majac do dyspozycji i bajtalarow zadajemy pytanie
		i albo zostajemy z i-a bajtalarami i maksymalnie mozemy obsluzyc i-a pieter
		albo zostajemy z i-b bajtalarami i maksymalnie mozemy obsluzyc i-b pieter
		}
		Q[i] := q_(i-a) + q_(i-b);
		if Q[i] = 0 then Q[i] := 1; // zawsze mozna zgadnac jak sie ma jedno pietro.
	end;
	q_ := Q[i];
end;


{
Wypisuje output do danego wyniku. Nie konczy, bo jeszcze mozna wypisac komentarz.
}
procedure wypisz_wynik(wynik:integer);
begin
	writeln(MAGIC_OUT); // zaczecie outputu od magicznej liczby
	writeln('wynik=',wynik,' n=',N,' a=',A,' b=',B,' strategia=',strategia,' pietro=',pietro);
end;

{
Inicjuje gre pomiedzy Bajtkiem i Bitocym.
}
procedure inicjuj(var n_, a_, b_: longint);
	var magic_begin1,magic_end1,step:longint;
begin
	if zainicjowane then begin
		wypisz_wynik(ERR);
		writeln('Program zawodnika moze wolac funkcje inicjuj tylko raz.');
		halt(0);
	end;
	zainicjowane := TRUE;
	read(magic_begin1);
	if (magic_begin1<>MAGIC_BEGIN) then begin
    { Interactive mode }
    N := magic_begin1;
    read(A, B, pietro);
    use_interactive := TRUE;
    interactive_inicjuj(n_, a_, b_);
	end else
  begin
    read(N); read(A); read(B); read(strategia); read(pietro); read(magic_end1);
    if (N<1) or (N>MAXN) or (A<1) or (A>MAXAB) or (B<1) or (B>MAXAB) or (strategia<MIN_S)
        or (strategia>MAX_S) or (pietro<1) or (pietro>N) or (magic_end1<>MAGIC_END) then begin
      wypisz_wynik(ERR);
      writeln('Program zawodnika nie moze wczytywac zadanego inputu.');
      halt(0);
    end;
    
    l := 1; r := N;
    
    // Wyznacza koszt jaki musi poniesc Bajtek.
    step := 1;
    w := step;
    repeat
      w := w - step;
      while q_(w) < n do w := w + step;
      step := step div 2;
    until step = 0;
    
    koszt := 0;
    n_ := N; a_ := A; b_ := B;
  end;
end;

{
Odpowiada na pytanie Bajtka zgodnie z przybrana strategia.
}
function pytaj(c : char; x: longint): boolean;
	var nie_szer,tak_szer:longint; // dlugosci przedzialow otrzymanych po odpowiedzi nie lub tak
	var koszt_nie,koszt_tak:longint; // pesymistyczne koszty gdy odpowie sie NIE, badz TAK.
	var w2:longint;
	var odp:boolean = TRUE;
begin
  if use_interactive then
    pytaj := interactive_pytaj(c, x)
  else begin
    if not zainicjowane then begin
      wypisz_wynik(ERR);
      writeln('Program zawodnika nie wywolal funkcji inicjuj.');
      halt(0);
    end;
    if (c <> 'N') and (c <>'W') then begin
      wypisz_wynik(ERR);
      writeln('Nieprawidlowy argument do pytaj.');
      halt(0);
    end;
    
    {
    Wyznaczanie, czy pytanie jest optymalne
    }
    if (c = 'N') and ((x <= l) or (x > r)) then begin
      wypisz_wynik(ERR);
      writeln('Pytanie czy nizej niz ',x,', gdy przedzial poszukiwan zawezony jest do [',l,',',r,'], jest nieoptymalne.');
      halt(0);
    end;
    if (c = 'W') and ((x < l) or (x >= r)) then begin
      wypisz_wynik(ERR);
      writeln('Pytanie czy wyzej niz ',x,', gdy przedzial poszukiwan zawezony jest do [',l,',',r,'], jest nieoptymalne.');
      halt(0);
    end;
    
    if (c = 'W') then begin nie_szer := x-l+1; tak_szer := r-x; end
    else { c == 'N' } begin tak_szer := x-l; nie_szer := r-x+1; end;
    
    if(q_(w - B) < nie_szer) then begin // po odpowiedzi NIE zwieksza sie szacowanie na pesymistyczny koszt
      w2 := w - B; while(q_(w2) < nie_szer) do w2:=w2+1;
      wypisz_wynik(ERR);
      writeln('Mozliwy pesymistyczny koszt: ',koszt+w,'. Po zadaniu tego pytania - ',koszt+w2+B,'.');
      halt(0);
    end;
    if(q_(w - A) < tak_szer) then begin // po odpowiedzi TAK zwieksza sie szacowanie na pesymistyczny koszt
      w2 := w - A; while(q_(w2) < tak_szer) do w2:=w2+1;
      wypisz_wynik(ERR);
      writeln('Mozliwy pesymistyczny koszt: ',koszt+w,'. Po zadaniu tego pytania - ',koszt+w2+A,'.');
      halt(0);
    end;
    
    {
    Wyznaczenie odpowiedzi na pytanie w zaleznosci od strategii
    }
    koszt_nie := w - B; koszt_tak := w - A; // pesymistyczne koszty gdy odpowie sie NIE, badz TAK.
    while(q_(koszt_nie) >= nie_szer) do koszt_nie:=koszt_nie-1;
    while(q_(koszt_tak) >= tak_szer) do koszt_tak:=koszt_tak-1;
    koszt_nie := koszt_nie + 1; koszt_tak := koszt_tak + 1;
    
    if (strategia = S_SPRAWIEDLIWA) then begin
      if (c = 'W') then begin if (pietro > x) then odp := TRUE else odp := FALSE; end
      else { c == 'N' } begin if (pietro < x) then odp := TRUE else odp := FALSE; end;
    end else if(strategia = S_PESYMISTYCZNA) then begin
      if(koszt_nie + B > koszt_tak + A) then odp := FALSE else odp := TRUE;
    end else if(strategia = S_OPTYMISTYCZNA) then begin
      if(koszt_nie + B > koszt_tak + A) then odp := TRUE else odp := FALSE;
    end;
    
    {
    Udzielanie odpowiedzi
    }
    if(odp = TRUE) then begin
      if (c = 'W') then l := x+1 else { c == 'N' } r := x-1;
      w := koszt_tak;
      koszt := koszt+A;
    end else { odp = FALSE } begin
      if (c = 'W') then r := x else { c == 'N' } l := x;
      w := koszt_nie;
      koszt := koszt+B;
    end;
    pytaj := odp;
  end;
end;

{
Weryfikuje odpowiedz otrzymana od Bajtka
}
procedure odpowiedz(wynik: longint);
begin
  if use_interactive then
    interactive_odpowiedz(wynik)
  else begin
    if not zainicjowane then begin
      wypisz_wynik(ERR);
      writeln('Program zawodnika nie wywolal funkcji inicjuj.');
      halt(0);
    end;
    
    if (l = r) and (l = wynik) then begin // ok
      wypisz_wynik(OK);
      writeln('Koszt: ',koszt,'.');
      halt(0);
    end;
    if(l <> r) then begin // jeszcze nie dosc pytan aby udzielic jednoznacznej odpowiedzi
      wypisz_wynik(ERR);
      writeln('Przedzial [',l,', ',r,'], do ktorego zawezono obszar poszukiwan, nie jest jednopunktowy.');
      halt(0);
    end;
    if(l <> wynik) then begin // zly wynik
      wypisz_wynik(ERR);
      writeln('Oczekiwano pietra ',l,', wczytano pietro ',wynik,'.');
      halt(0);
    end;
  end;
end;

begin
end.
