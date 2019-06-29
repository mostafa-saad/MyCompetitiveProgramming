{*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Zapytania (ZAP)                                            *}
{*   Plik:    zaps4.pas                                                  *}
{*   Autor:   Jakub Pawlewicz                                            *}
{*   Opis:    Rozwiazanie dynamiczne O(m^2 log log m)                    *}
{*                                                                       *}
{*************************************************************************}
const
   MAX_M = 50000;
   MAX_N = 50000;

type
   Tres      = LongWord; { Zmienic na QWord, aby umozliwic wyniki 64-bitowe }
   Tquestion = record a, b : LongWord; end;
   TSplit    = record p, r : LongWord; end;

var
   question   : array[1..MAX_N] of Tquestion;
   questionidx   : array[1..MAX_N] of LongInt;
   answer   : array[1..MAX_N] of TRes;
   F     : array[1..MAX_M] of TSplit;
   n, maxa, maxb : LongWord;

procedure ReadQuestions;
var
   i, d : LongWord;
begin
   Read(n);
   maxa := 0;
   maxb := 0;
   for i := 1 to n do
      with question[i] do begin
   Read(a, b, d);
   a := a div d;
   b := b div d;
   if a > b then begin
      d := a;
      a := b;
      b := d;
   end;
   if a > maxa then
      maxa := a;
   if b > maxb then
      maxb := b;
      end;
end;

procedure SortQuestions;
var
   next     : array[1..MAX_N] of LongInt;
   bucket  : array[1..MAX_M] of LongInt;
   i, j, q : LongInt;
begin
   for i := 1 to maxb do
      bucket[i] := 0;
   for i := 1 to n do
      with question[i] do begin
   next[i] := bucket[b];
   bucket[b] := i;
      end;
   j := 0;
   for i := 1 to maxb do begin
      q := bucket[i];
      while q <> 0 do begin
   Inc(j);
   questionidx[j] := q;
   q := next[q];
      end;
   end;
   
   for i := 1 to maxa do
      bucket[i] := 0;
   for i := n downto 1 do begin
      q := questionidx[i];
      with question[q] do begin
   next[q] := bucket[a];
   bucket[a] := q;
      end;
   end;
   j := 0;
   for i := 1 to maxa do begin
      q := bucket[i];
      while q <> 0 do begin
   Inc(j);
   questionidx[j] := q;
   q := next[q];
      end;
   end;
end;

procedure SieveF(p, q : LongWord);
var
   i, r  : LongWord;
begin
   if q <= maxa then begin
      SieveF(p, q * p);
      i := q;
      r := 1;
      while i <= maxa do begin
   if F[i].p = 1 then begin
      F[i].p := p;
      F[i].r := r;
   end;
   Inc(i, q);
   Inc(r);
      end;
   end;
end;

procedure PrepareF;
var
   is_prime : array[1..MAX_M] of Boolean;
   i, p, p2    : LongWord;
begin
   for i := 1 to maxa do
      is_prime[i] := true;
   p := 2;
   p2 := 4;
   while p2 <= maxa do begin
      i := 2 * p;
      while i <=  maxa do begin
   is_prime[i] := false;
   Inc(i, p);
      end;
      repeat
   Inc(p2, 2 * p + 1);
   Inc(p);
      until (p2 > maxa) or is_prime[p];
   end;
   for i := 1 to maxa do
      F[i].p := 1;
   for i := 2 to maxa do
      if is_prime[i] then
   SieveF(i, i);
end;

procedure Solve;
var
   a, b, i   : LongWord;
   q       : LongInt;
   c       : array[0..MAX_M] of TRes;
   coprime_a : array[0..MAX_M] of LongWord;

procedure FindCoprimes;
var
   is_coprime : array[1..MAX_M] of Boolean;
   i, p, r    : LongWord;
begin
   for i := 1 to maxb do
      is_coprime[i] := true;
   r := a;
   while r <> 1 do begin
      p := F[r].p;
      r := F[r].r;
      i := p;
      while i <= maxb do begin
   is_coprime[i] := false;
   Inc(i, p);
      end;
   end;
   coprime_a[0] := 0;
   for i := 1 to maxb do begin
      coprime_a[i] := coprime_a[i - 1];
      if is_coprime[i] then
   Inc(coprime_a[i]);
   end;
end;

var
   tmp : LongWord;

begin
   SortQuestions;
   a := 0;
   b := maxb;
   for i := 0 to maxb do
      c[i] := 0;
   i := 1;
   q := questionidx[i];
   while true do begin
      if (question[q].a = a) and (question[q].b = b) then begin
   answer[q] := c[b];
   if i = n then
      break;
   Inc(i);
   q := questionidx[i];
      end else if b = maxb then begin
   Inc(a);
   b := 0;
   FindCoprimes;
      end else begin
   Inc(b);
   Inc(c[b], coprime_a[b]);
      end;
   end;
   for i := 1 to n do
      WriteLn(answer[i]);
end;

begin
   ReadQuestions;
   PrepareF;
   Solve;
end.
