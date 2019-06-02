{*************************************************************************
 *                                                                       *
 *                    XI Olimpiada Informatyczna                         *
 *                                                                       *
 *   Rozwi±zanie zadania: Maksymalne Rzêdy Permutacji                    *
 *   Plik:                mak.pas                                        *
 *   Autor:               Pawe³ Wolff                                    *
 *************************************************************************}

program MakWer;


const
  MAX_N = 10000;
  MAX_NK = 670000;
  MAX_PRIMES = 1300; { p_1300 > MAX_N }
  MAX_LEN = 29;
  WORD_BITS = 16;
  MAX_WORD = 65535;
  MAX_D = 10;


type
  BigNumber =
    record 
      len: integer;
      a  : array [0..MAX_LEN - 1] of word;
    end;

  RankT =
    record
      R : BigNumber;
      pa: integer;
    end;


var
  prime: array [1..MAX_PRIMES] of integer;
  noPrimes: integer;
  index: array [0..MAX_N + 1] of longint;
  rank: array [0..MAX_NK] of RankT;

  

function Min(a, b: integer): integer;
begin
  if a < b then
    Min := a
  else
    Min := b;
end;

function Max(a, b: integer): integer;
begin
  if a > b then
    Max := a
  else
    Max := b;
end;



procedure Word2BigNumber(var a: BigNumber; x: Word);
begin
  if x = 0 then
    a.len := 0
  else begin
    a.a[0] := x;
    a.len := 1;
  end;
end;


procedure Ass(var a, b: BigNumber);
{ a := b }
var
  i: integer;
begin
  a.len := b.len;
  for i := 0 to a.len - 1 do
    a.a[i] := b.a[i];
end;


procedure Add(var a, b: BigNumber);
var
  i, c, len: integer;
  d, e: longint;
begin
  len := Max(a.len, b.len);
  c := 0;
  for i := 0 to len do begin

    if i < a.len then
      d := a.a[i]
    else
      d := 0;

    if i < b.len then
      e := b.a[i]
    else
      e := 0;

    Inc(d, e + c);
    c := d shr WORD_BITS;
    a.a[i] := d and MAX_WORD;
  end;
  
  if a.a[len] = 0 then
    a.len := len - 1
  else
    a.len := len;
end;


procedure MulWord(var c, a: BigNumber; b: word);
var
  i: integer;
  b1, d: longint;
begin
  if b = 0 then
    c.len := 0
  else begin
    b1 := longint(b);
    d := 0;
    for i := 0 to a.len - 1 do begin
      d := longint(a.a[i]) * b1 + d;
      c.a[i] := d and MAX_WORD;
      d := d shr WORD_BITS;
    end;
    i := a.len;
    if d <> 0 then begin
      c.a[i] := d;
      Inc(i);
    end;
    c.len := i;
  end;
end;


function Less(var a, b: BigNumber): boolean;
var
  i: integer;
begin
  if a.len <> b.len then
    Less := (a.len < b.len)
  else begin
    i := a.len - 1;
    while (i >= 0) and (a.a[i] = b.a[i]) do
      Dec(i);

    Less := (i >= 0) and (a.a[i] < b.a[i]);
  end;
end;


procedure GenPrimes(maxPrime: integer);
var
  i, j: integer;
  t: array [2..MAX_N] of boolean;
begin
  for j := 2 to maxPrime do
    t[j] := true;

  for i := 2 to maxPrime div 2 do
    begin
      j := 2 * i;
      while j <= maxPrime do begin
        t[j] := false;
        Inc(j, i);
      end;
    end;

  noPrimes := 0;
  for i := 2 to maxPrime do
    if t[i] then begin
      Inc(noPrimes);
      prime[noPrimes] := i;
    end;
end;


procedure GenSolutions(n: integer);
var
  i, j: integer;
  R, maxR: BigNumber;
  pa, maxPa: longint;

begin
  index[0] := 0;
  index[1] := 1;
  Word2BigNumber(rank[0].R, 1);

  for i := 1 to n do begin
    Word2BigNumber(rank[index[i]].R, 1);
    rank[index[i]].pa := 1;

    j := 1;
    while (j <= noPrimes) and (prime[j] <= i) do begin
      pa := prime[j];
      Ass(maxR, rank[index[i] + j - 1].R);
      MulWord(R, rank[index[i - pa] + Min(j - 1, index[i - pa + 1] - index[i - pa] - 1)].R, i);
      if not Less(maxR, R) then
        break;
      
      maxPa := 0;      
      while pa <= i do begin
        MulWord(R, rank[index[i - pa] + Min(j - 1, index[i - pa + 1] - index[i - pa] - 1)].R, pa);
        if Less(maxR, R) then begin
          Ass(maxR, R);
          maxPa := pa;
        end;
        pa := pa * prime[j];
      end;

      Ass(rank[index[i] + j].R, maxR);
      rank[index[i] + j].pa := maxPa;
      Inc(j);
    end;

    index[i + 1] := index[i] + j;
  end;
end;


procedure WritePermutation(n: integer);
var
  i, j, u, k, sum: integer;
  cycle: array [1..MAX_PRIMES] of integer;
  tmp: array [1..MAX_PRIMES] of integer;
  
  procedure MergeSort(l, r: integer);
  var
    m, v: integer;
  begin
    if l < r then begin
      m := (l + r) div 2;
      MergeSort(l, m);
      MergeSort(m + 1, r);
      i := l;
      j := m + 1;
      u := l;
      while (i <= m) or (j <= r) do begin
        if (j > r) or (i <= m) and (cycle[i] < cycle[j]) then begin
          tmp[u] := cycle[i];
          Inc(i);
        end
        else begin
          tmp[u] := cycle[j];
          Inc(j);
        end;
        Inc(u);
      end;

      for v := l to r do
        cycle[v] := tmp[v];
    end;
  end;

begin
  k := 0;
  i := n;
  j := noPrimes;

  while i > 0 do begin
    j := Min(j, index[i + 1] - index[i] - 1);
    while rank[index[i] + j].pa = 0 do
      Dec(j);

    Inc(k);
    cycle[k] := rank[index[i] + j].pa;

    Dec(i, cycle[k]);
    if j > 0 then
      Dec(j);
  end;

  MergeSort(1, k);
  
  sum := 0;
  for i := 1 to k do begin
    for j := 1 to cycle[i] do begin
      Write(sum + (j mod cycle[i]) + 1);
      if (i = k) and (j = cycle[i]) then
        Writeln
      else
        Write(' ');
    end;
    Inc(sum, cycle[i]);
  end;
end;



var i, d: integer;
    n: array [1..MAX_D] of integer;
    maxN: integer;
    
begin
  Readln(d);
  maxN := 0;
  for i := 1 to d do begin
    Readln(n[i]);
    maxN := max(maxN, n[i]);
  end;
    
  GenPrimes(maxN);

  GenSolutions(maxN);

  for i := 1 to d do
    WritePermutation(n[i]);
end.
