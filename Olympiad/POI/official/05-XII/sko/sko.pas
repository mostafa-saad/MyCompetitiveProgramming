(*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: SKO (Skoczki)                                  *
 *   Plik:                sko.pas                                        *
 *   Autor:               Marcin Mucha, mucha@mimuw.edu.pl               *
 *   Opis:                Program wzorcowy do zadania Skoczki            *
 *                                                                       *
 *************************************************************************)
program Skoczki;
const
   N_MAX =  100;

type
   vector = record x, y	: longint end;

var
   f : text;
   n : integer;
   v : array[1..N_MAX] of vector;

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
      if (new_u.x < 0) then begin new_u.x := -new_u.x; new_u.y := -new_u.y end;
      new_u.x := new_u.x mod new_v.x
   end;
   u := new_u; v := new_v
end; { normal_form }

procedure reduce;
var
   i : integer;
begin
   normal_form(v[n-1],v[n]);
   for i := n-2 downto 1 do
   begin
      normal_form(v[i],v[i+1]);
      join_if_dependent(v[i+1],v[i+2])
   end;
   { Tylko po to, zeby v[1] sie zmniejszyl }
   normal_form(v[1],v[2]);
end; { reduce }

var
   i : integer;
			 
begin
   read(n);
   for i := 1 to n do
      read(v[i].x, v[i].y);
   reduce;
   writeln(v[1].x, ' ', v[1].y);
   writeln(v[2].x, ' ', v[2].y);
end.
