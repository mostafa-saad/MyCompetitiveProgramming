{*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Zapytania (ZAP)                                            *}
{*   Plik:    zap0.pas                                                   *}
{*   Autor:   Jakub Pawlewicz                                            *}
{*   Opis:    Rozwiazanie wzorcowe O( sqrt(n) (n log n + m log m) )      *}
{*                                                                       *}
{*************************************************************************}
const
   MAX_M = 50000;
   MAX_N = 50000;

type
   Tquestion = record a, b : LongWord; end;
   TSplit    = record p, r : LongWord; end;

var
   question    : array[1..MAX_N] of Tquestion;
   questionidx : array[1..MAX_N] of LongInt;
   answer      : array[1..MAX_N] of QWord;
   F         : array[1..MAX_M] of TSplit;
   n, m         : LongWord;

procedure ReadQuestions;
var
   i, d : LongWord;
begin
   Read(n);
   m := 0;
   for i := 1 to n do
      with question[i] do begin
   read(a, b, d);
   a := a div d;
   b := b div d;
   if a < b then begin
      d := a;
      a := b;
      b := d;
   end;
   if a > m then
      m := a;
      end;
end;

procedure SortQuestions;
var
   next     : array[1..MAX_N] of LongInt;
   bucket  : array[1..MAX_M] of LongInt;
   i, j, q : LongInt;
begin
   for i := 1 to m do
      bucket[i] := 0;
   for i := 1 to n do
      with question[i] do begin
   next[i] := bucket[b];
   bucket[b] := i;
      end;
   j := 0;
   for i := 1 to m do begin
      q := bucket[i];
      while q <> 0 do begin
   Inc(j);
   questionidx[j] := q;
   q := next[q];
      end;
   end;
   
   for i := 1 to m do
      bucket[i] := 0;
   for i := n downto 1 do begin
      q := questionidx[i];
      with question[q] do begin
   next[q] := bucket[a];
   bucket[a] := q;
      end;
   end;
   j := 0;
   for i := 1 to m do begin
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
   if q <= m then begin
      SieveF(p, q * p);
      i := q;
      r := 1;
      while i <= m do begin
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
   for i := 1 to m do
      is_prime[i] := true;
   p := 2;
   p2 := 4;
   while p2 <= m do begin
      i := 2 * p;
      while i <=  m do begin
   is_prime[i] := false;
   inc(i, p);
      end;
      repeat
   inc(p2, 2 * p + 1);
   inc(p);
      until (p2 > m) or is_prime[p];
   end;
   for i := 1 to m do
      F[i].p := 1;
   for i := 2 to m do
      if is_prime[i] then
   SieveF(i, i);
end;

(* Counts numbers from set {1, ..., a} coprime with b *)
function CoprimeLineCount(a, b : LongWord) : LongWord;
begin
  if (b = 0) or (a = 0) then
     CoprimeLineCount := 0
  else if b = 1 then
     CoprimeLineCount := a
  else
     CoprimeLineCount := CoprimeLineCount(a, F[b].r) -
        CoprimeLineCount(a div F[b].p, F[b].r);
end;

procedure ProcessMonotonicSubsequence(var n : LongWord);
var
   prev1, prev2      : array[1..MAX_N] of LongInt;
   seq1, seq2      : array[0..MAX_N] of LongInt;
   seq1len, seq2len : LongInt;
   i, j, q, l, r, c : LongInt;
   a, b        : LongWord;
   count      : QWord;

procedure MoveTo(new_a, new_b : LongWord);
begin
   while (a <> new_a) or (b <> new_b) do
      if a < new_a then begin
   Inc(a);
   Inc(count, CoprimeLineCount(b, a));
      end else if a > new_a then begin
   Dec(count, CoprimeLineCount(b, a));
   Dec(a);
      end else if b < new_b then begin
   Inc(b);
   Inc(count, CoprimeLineCount(a, b));
      end else begin
   Dec(count, CoprimeLineCount(a, b));
   Dec(b);
      end;
end;

begin
   seq1len := 0;
   seq1[0] := 0;
   for i := n downto 1 do begin
      q := questionidx[i];
      b := question[q].b;
      l := 1;
      r := seq1len + 1;
      while l < r do begin
   c := (l + r) div 2;
   if b < question[seq1[c]].b then
      r := c
   else
      l := c + 1;
      end;
      if l > seq1len then
   seq1len := l;
      seq1[l] := q;
      prev1[q] := seq1[l - 1];
   end;

   seq2len := 0;
   seq2[0] := 0;
   for i := n downto 1 do begin
      q := questionidx[i];
      b := question[q].b;
      l := 1;
      r := seq2len + 1;
      while l < r do begin
   c := (l + r) div 2;
   if b > question[seq2[c]].b then
      r := c
   else
      l := c + 1;
      end;
      if l > seq2len then
   seq2len := l;
      seq2[l] := q;
      prev2[q] := seq2[l - 1];
   end;

   if seq1len > seq2len then
      q := seq1[seq1len]
   else
      q := seq2[seq2len];
   a := 0;
   b := question[q].b;
   count := 0;
   j := 0;
   for i := 1 to n do begin
      if q = questionidx[i] then begin
   MoveTo(question[q].a, question[q].b);
   answer[q] := count;
   if seq1len > seq2len then
      q := prev1[q]
   else
      q := prev2[q];
      end else begin
   Inc(j);
   questionidx[j] := questionidx[i];
      end;
   end;
   n := j;
end;

procedure Solve;
var
   rest  : LongWord;
   i  : LongInt;
begin
   SortQuestions;
   rest := n;
   repeat
      ProcessMonotonicSubsequence(rest);
   until rest = 0;
   for i := 1 to n do
      WriteLn(answer[i]);
end;

begin
   ReadQuestions;
   PrepareF;
   Solve;
end.
