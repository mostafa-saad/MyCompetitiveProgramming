(*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: SKA (Skarbonki)                                *
 *   Plik:                ska.pas                                        *
 *   Autor:               Pawe³ Wolff                                    *
 *   Opis:                Rozwi±zanie wzorcowe zadania SKARBONKI         *
 *                                                                       *
 *************************************************************************)

program Skarbonki;


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

  numer: array [1..MAX_N] of longint;
    { ta tablica bêdzie potrzebna w funkcji IleCykli;
      numer[j] = 0: j-ty wierzcho³ek jest "nieodwiedzony"
      numer[j] = i: j-ty wierzcho³ek zosta³ "odwiedzony z wierzcho³ka i" }


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
  Dziêki temu, ¿e stopieñ wyj¶ciowy ka¿dego wierzcho³ka grafu wynosi 1,
  mo¿emy to zrobiæ w nastêpuj±cy sposób.
  Pocz±tkowo wszystkie wierzcho³ki oznaczamy jako "nieodwiedzone".
  Nastêpnie z ka¿dego wierzcho³ka (powiedzmy o numerze i) odwiedzamy
  "nieodwiedzone" od tej pory wierzcho³ki (z ka¿dego kolejnego wychodz±c
  jedyn± krawêdzi±), zaznaczaj±c, ¿e zosta³y "odwiedzone z wierzcho³ka i".
  Je¿eli napotkamy wierzcho³ek, który zosta³ ju¿
  "odwiedzony z wierzcho³ka j", to znaczy, ¿e:
  - znale¼li¶my nowy cykl, o ile i = j,
  - w przeciwnym razie dotarli¶my do wierzcho³ka, który znajduje siê
    na cyklu ju¿ wcze¶niej znalezionym bad¼ te¿ z którego wcze¶niej
    dotarli¶my do takowego cyklu. }
var
  i, j, lCykli: longint;

begin
  lCykli := 0;

  for i := 1 to n do
    numer[i] := 0;

  for i := 1 to n do begin
    j := i;
    while numer[j] = 0 do begin
      numer[j] := i;
      j := klucz[j];
    end;
    
    if numer[j] = i then
      Inc(lCykli);
  end;

  IleCykli := lCykli;
end;



begin
  WczytajDane;
  Writeln(IleCykli);
end.
