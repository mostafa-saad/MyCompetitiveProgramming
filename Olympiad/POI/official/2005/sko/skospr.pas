(*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: SKO (Skoczki)                                  *
 *   Plik:                skospr.pas                                     *
 *   Autor:               Marcin Mucha, mucha@mimuw.edu.pl               *
 *   Opis:                Sprawdzaczka do zadania Skoczki                *
 *                        Sprawdzaczka pobiera dwa argumenty:            *
 *                        skospr output_zawodnika output_prawidlowy      *
 *                                                                       *
 *************************************************************************)
program SkoSpr;

type
   vector = record x, y	: longint end;

const
   MIN_COORD = -10000;
   MAX_COORD = 10000;

var
   f : text;
   a, b, u, v : vector;

function abs(x : longint) : longint;
begin
   if x >= 0 then abs := x else abs := -x
end; { abs }

procedure xch(var a, b : vector);
var
   c : vector;
begin
   c := a; a := b; b := c
end; { xch }

procedure xch_int(var a, b : longint);
var
   c : longint;
begin
   c := a; a := b; b := c
end; { xch_int }

function extended_gcd(a,b : longint; var k,l : longint) : longint;
var
   a_a, a_b, b_a, b_b : longint;

   procedure xch_ab;
   begin
      xch_int(a,b); xch_int(a_a,b_a); xch_int(a_b,b_b)
   end; { xch_ab }

begin
   a_a := 1; a_b := 0; b_a := 0; b_b := 1;
   if a < 0 then begin a := -a; a_a := -1 end;
   if b < 0 then begin b := -b; b_b := -1 end;
   if b < a then xch_ab;
   while a <> 0 do
   begin
      b_a := b_a - (b div a) * a_a;
      b_b := b_b - (b div a) * a_b;
      b := b mod a;
      xch_ab;
   end;
   k := b_a; l := b_b;
   extended_gcd := b;
end; { extended_gcd }

function gcd(a,b : longint) : longint;
var
   k, l	: longint;
begin
   gcd := extended_gcd(a,b,k,l);
end; { gcd }

function join_if_dependent(var u, v : vector) : boolean;
{ Funkcja sprawdza, czy u i v sa l.z, a jesli tak to }
{ zastepuje je jednym. Wynik umieszcza w u }
begin
   join_if_dependent := true;
   { Jeden z wektorow zdegenerowany }
   if (v.x=0) and (v.y=0) then exit;
   if (u.x=0) and (u.y=0) then begin u := v; exit end;
   { Oba pionowe badz poziome }
   if (u.x=0) and (v.x=0) then begin u.y := gcd(u.y,v.y); exit end;
   if (u.y=0) and (v.y=0) then begin u.x := gcd(u.x,v.x); exit end;
   { Oba ukosne }
   if (u.x*v.y=v.x*u.y) then
   begin
      u.x := abs(gcd(u.x,v.x));
      u.y := (v.y * u.x) div v.x;
      exit
   end;
   { Niezalezne }
   join_if_dependent := false
end; { join_dependent }

procedure normal_form(var u, v : vector);
{ Zamienia pare u, v na rownowazna w ktorej drugi wektor jest postaci (x,0) }
{ x moze byc rowne 0, jesli u, v sa l.z.                                    }
var
   gcdy		: longint;
   new_v, new_u	: vector;
   k,l		: longint;
begin
   { Zalezne }
   if join_if_dependent(u, v) then
   begin v.x := 0; v.y := 0; exit end;
   { Obliczamy wektor new_v - najkrotszy wektor poziomy }
   gcdy := gcd(u.y,v.y);
   new_v.x := abs(u.x*(v.y div gcdy)-v.x*(u.y div gcdy));
   new_v.y := 0;
   { Obliczamy wektor new_u - wektor o najmniejszej wspolrzednej y }
   extended_gcd(u.y,v.y,k,l);
   new_u.x := k*u.x+l*v.x;
   new_u.y := k*u.y+l*v.y;
   { Zmniejszanie drugiego wektora }
   if (new_v.x <> 0) then
   begin
      if (new_u.x < 0) or ((new_u.x = 0) and (new_u.y < 0)) then
      begin new_u.x := -new_u.x; new_u.y := -new_u.y end;
      new_u.x := new_u.x mod new_v.x
   end;
   u := new_u; v := new_v
end; { normal_form }
		
procedure test(x : longint; min, max : longint);
begin
   if (x < min) or (x > max) then
   begin
      writeln('ZLE: Liczba ',x,' spoza zakresu');
      halt(1)
   end
end;
	 
begin
   if paramcount <> 2 then
   begin
      writeln('Wolaj: skospr out_zawodnika out_wzorcowy');
      halt(1);
   end;
   assign(f,paramstr(1));
   reset(f);
   readln(f, u.x, u.y);  
   readln(f, v.x, v.y);
   test(u.x,MIN_COORD, MAX_COORD); 
   test(u.y,MIN_COORD, MAX_COORD); 
   test(v.x,MIN_COORD, MAX_COORD); 
   test(v.y,MIN_COORD, MAX_COORD);
   close(f);
   assign(f,paramstr(2));
   reset(f);
   readln(f, a.x, a.y);
   readln(f, b.x, b.y);
   close(f);
   normal_form(a,b);
   normal_form(u,v);
   { jeszcze raz --> added by CYFRA} 
   normal_form(u,v);
   normal_form(a,b);

   if (a.x <> u.x) or (a.y <> u.y) or (b.x <> v.x) or (b.y <> v.y) then
      writeln('ZLE')
   else
      writeln('OK')
end.
