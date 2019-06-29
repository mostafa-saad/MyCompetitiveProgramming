{*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Zapytania (ZAP)                                            *}
{*   Plik:    zaps6.pas                                                  *}
{*   Autor:   Jakub Pawlewicz                                            *}
{*   Opis:    Rozwiazanie alternatywne O(n m^(3/4))                      *}
{*                                                                       *}
{*************************************************************************}
const
   MAX_M      = 50000;
   MAX_N      = 50000;
   MAX_HT_EXP = 20;

type
   Tres       = LongWord; { Zmienic na QWord, aby umozliwic wyniki 64-bitowe }
   Tquestion = record a, b : LongWord; end;
   Tentry    = record a, b : LongWord; c : Tres; end;

var
   question    : array[1..MAX_N] of Tquestion;
   questionidx : array[1..MAX_N] of LongInt;
   answer      : array[1..MAX_N] of QWord;
   ht         : array[0..(1 shl MAX_HT_EXP) - 1] of Tentry;
   ht_size     : LongWord;
   n, m         : LongWord;

procedure htInit;
var
   dest_size : QWord;
   i       : LongWord;
begin
   ht_size := 1;
   dest_size := QWord(n) * m;
   for i := 1 to MAX_HT_EXP do
      if ht_size >= dest_size then
   break
      else
   ht_size := ht_size * 2;
end;

function htGet(qa, qb : LongWord; var res : Tres) : Boolean;
begin
   with ht[(qb * m + qa) and (ht_size - 1)] do
      if (qa = a) and (qb = b) then begin
   htGet := true;
   res := c;
      end else
   htGet := false;
end;

procedure htSave(qa, qb : LongWord; qc : Tres);
begin
   with ht[(qb * m + qa) and (ht_size - 1)] do begin
      a := qa;
      b := qb;
      c := qc;
   end;
end;

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
   htInit;
end;

function max(a, b : LongWord) : LongWord;
begin
   if a > b then
      max := a
   else
      max := b;
end;

function coprimes(a, b : LongWord) : Tres;
var
   c     : Tres;
   d, d1, k, l : LongWord;
begin
   if b = 0 then
      coprimes := 0
   else if b = 1 then
      coprimes := a
   else if b = 2 then
      coprimes := 2 * a - a div 2
   else if htGet(a, b, c) then
      coprimes := c
   else begin
      { Tutaj mozna przekroczyc zakres, ale to nie szkodzi, gdyz
       ostateczny wynik bedzie miescil sie w liczbie 32-bitowej, a
       cale obliczenia mozna traktowac jak rachunki modulo 2^32. }
      c := Tres(a) * b;
      k := a div b;
      d := b;
      while sqr(k) <= a do begin
   l := b div d;
   d1 := max(a div (k + 1), b div (l + 1));
   Dec(c, (d - d1) * coprimes(k, l));
   d := d1;
   k := a div d;
      end;
      while d >= 2 do begin
   Dec(c, coprimes(a div d, b div d));
   Dec(d);
      end;
      htSave(a, b, c);
      coprimes := c;
   end;
end;

function less(i, j : LongInt) : Boolean;
begin
   less :=
   Int64(question[i].b) * question[j].a < Int64(question[i].a) * question[j].b;
end;

procedure SortQuestions; { ShellSort, krotki i wystarczajaco szybki }
const
   MAX_INCS = 12;
   incs : array[1..MAX_INCS] of LongInt  = 
      (33936, 13776, 4592, 1968, 861, 336, 112, 48, 21, 7, 3, 1);
var 
   i, j, k, h, q : LongInt;
begin
   for i := 1 to n do
      questionidx[i] := i;
   for k := 1 to MAX_INCS do begin
      h := incs[k];
      for i := h + 1 to n do begin
   q := questionidx[i];
   j := i;
         while (j > h) and less(q, questionidx[j - h]) do begin
      questionidx[j] := questionidx[j - h];
            Dec(j, h);
   end;
   questionidx[j] := q;
      end;
   end;
end;

procedure Solve;
var
   i, q  : LongInt;
begin
   SortQuestions;
   for i := 1 to n do begin
      q := questionidx[i];
      answer[q] := coprimes(question[q].a, question[q].b);
   end;
   for i := 1 to n do
      WriteLn(answer[i]);
end;

begin
   ReadQuestions;
   Solve;
end.
