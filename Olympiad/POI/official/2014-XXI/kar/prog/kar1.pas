(*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Karty                                         *
 *   Autor:                Lech Duraj                                    *
 *   Zlozonosc czasowa:    O(n + m log n)                                *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wzorcowe                          *
 *                                                                       *
 *************************************************************************)

program Karty;
type 
  PI = array[0..1] of LongInt;
  matrix = array[0..1,0..1] of Boolean;
     
const 
  infty : LongInt = 1000000001;
  
var 
  cards : array[0..400001] of PI;       // wartosci kart
  {   Drzewo przedzialowe   }
  trans : array[0..800003] of matrix;   // macierz mozliwych przejsc z poczatku na koniec przedzialu
                                        // trans[x][p][q] = 1 wtedy i tylko wtedy, kiedy mozna ustawic przedzial wezla x nierosnaco tak,
                                        // aby skrajnie lewa karta byla w pozycji p, a prawa w pozycji q
  borders : array[0..800003] of PI;     // borders[x] = (poczatek,koniec) przedzialu x, pomocniczo
    


procedure fix(x: LongInt);              // naprawia wezel drzewa 
var 
  bleft, bright : LongInt;
  q,r,s,t : ShortInt;
begin
  bleft := borders[2*x][1];             // dwie karty w srodku przedzialu, na styku jego dzieci
  bright := borders[2*x+1][0];
  
  for q := 0 to 1 do 
    for r := 0 to 1 do
      trans[x][q][r] := false;
      
  for s := 0 to 1 do                    // dla wszystkich mozliwe kombinacji kart srodkowych...
    for t := 0 to 1 do
    begin
      if cards[bleft][s]>cards[bright][t] then  // ...ktore sa dozwolone...
        continue;
      for q := 0 to 1 do 
        for r := 0 to 1 do
          trans[x][q][r] := trans[x][q][r] or (trans[2*x][q][s] and trans[2*x+1][t][r]);        // ...ustaw na 1 odpowiednie wartosci w macierzy przejsc
    end;
end;

var n,m : LongInt;
    K : LongInt;
    i,t,x,y : LongInt;
    tmp : PI;
    q,r : ShortInt;
begin
  ReadLn(n);
  for i:=0 to n-1 do
    ReadLn(cards[i][0],cards[i][1]);
  
  K := 1;                               // uzupelnij liczbe kart do potegi dwojki
  while K<n do
    K := 2*K;
  for i := n to K-1 do
  begin
    cards[i][0] := infty;
    cards[i][1] := infty;
  end;
  
  for i:=0 to K-1 do                    // wypelnij dolny poziom drzewa (wezly K..2K-1)
  begin
    borders[K+i][0] := i;
    borders[K+i][1] := i;
    for q := 0 to 1 do 
      for r := 0 to 1 do
        trans[K+i][q][r] := (q=r);
  end;
  
  for i:=K-1 downto 1 do                // uzupelnij reszte drzewa od konca
  begin
    borders[i][0] := borders[2*i][0];
    borders[i][1] := borders[2*i+1][1];
    fix(i);
  end;
  
  ReadLn(m);                            // przerobienie zapytan
  for i:=0 to m-1 do
  begin
    ReadLn(x,y);
    x := x-1;
    y := y-1;
    tmp := cards[x];                   // zamien karty (wezlow drzewa nie trzeba, sa identyczne)
    cards[x] := cards[y];
    cards[y] := tmp;
    
    t := (K+x) div 2;                   // napraw sciezki od zmienionych wezlow
    while t>0 do
    begin
      fix(t);
      t := t div 2;
    end;
    t := (K+y) div 2;
    while t>0 do
    begin
      fix(t);
      t := t div 2;
    end;
    
    { Da sie ustawic cala tablice <=> ktores przejscie w wezle 1 jest mozliwe }    
    if trans[1][0][0] or trans[1][0][1] or trans[1][1][0] or trans[1][1][1] then 
      WriteLn('TAK')
    else
      WriteLn('NIE');
  end;
end.
