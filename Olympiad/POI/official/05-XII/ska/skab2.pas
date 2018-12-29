(*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: SKA (Skarbonki)                                *
 *   Plik:                skab2.pas                                      *
 *   Autor:               Pawe³ Wolff                                    *
 *   Opis:                Rozwi±zanie niepoprawne zadania SKARBONKI      *
 *                                                                       *
 *************************************************************************)

program Skarbonki_b2;


const
  MAX_N = 1000000;


var
  n: longint;
  klucz: array [1..MAX_N] of longint;
    { klucz[i] = numer skarbonki, w której znajduje siê i-ty klucz;
      tablica ta definiuje graf skierowany: wierzcho³kami s± klucze
      o numerach 1, 2, ..., n, a krawêdzie prowadz± od wierzcho³ka 
      o numerze i do wierzcho³ka o numerze klucz[i] (dla wszystkich
      i = 1, 2, ..., n); zatem jest to graf, w którym stopieñ wyj¶ciowy
      ka¿dego wierzcho³ka jest równy 1 }


procedure WczytajDane;
var
  i: longint;

begin
  Readln(n);
  
  for i := 1 to n do
    Readln(klucz[i]);
end;


function IleCykli: longint;
{ Liczymy liczbê cykli w grafie zdefiniowanym przez tablicê klucz.
  Mo¿emy to zrobiæ (niepoprawnie) w nastêpuj±cy sposób.
  Bêdziemy odwiedzaæ wierzcho³ki grafu, poruszaj±c siê wzd³u¿ krawêdzi.
  Po przej¶ciu dan± krawêdzi±, bêdziemy j± usuwaæ.
  (Zauwa¿my zatem, ¿e w ka¿dym momencie dzia³ania algorytmu stopieñ
  wyj¶ciowy ka¿dego wierzcho³ka wynosi 0 lub 1.)
  Z ka¿dego wierzcho³ka (powiedzmy o numerze i), z którego wychodzi
  krawêd¼, rozpoczynamy odwiedzanie nastêpnych wierzcho³ków
  (poruszaj±c siê wzd³u¿ krawêdzi i przy tym usuwaj±c je).
  Takie odwiedzanie koñczy siê, gdy znajdziemy siê w wierzcho³ku, z którego
  nie wychodzi ¿adna krawêd¼. 
  Wówczas, je¶li numer tego wierzcho³ka
  - jest równy i, to znaczy, ¿e znale¼li¶my nowy cykl,
  - jest ró¿ny od i, to znaczy, ¿e dotarli¶my do wierzcho³ka, który
    znajduje siê na cyklu ju¿ wcze¶niej znalezionym bad¼ te¿ z którego
    wcze¶niej dotarli¶my do takowego cyklu. }
var
  i, j, pom, lCykli: longint;

begin
  lCykli := 0;

  for i := 1 to n do
    if klucz[i] <> 0 then begin
      j := i;
      repeat
        pom := klucz[j];
        klucz[j] := 0;
        j := pom;
      until klucz[j] = 0;
      
      if j = i then
        Inc(lCykli);
    end;

  IleCykli := lCykli;
end;


begin
  WczytajDane;
  Writeln(IleCykli);
end.
