(*************************************************************************
 *                                                                       *
 *                       X Olimpiada Informatyczna                       *
 *                                                                       *
 *   Rozwi±zanie zadania: Trójmian                                       *
 *   Plik:                tro.pas                                        *
 *   Autor:               Wojciech Dudek                                 *
 *************************************************************************)

program Tro;
const
  PLIK_WE       = '';
  PLIK_WY       = '';
  MAX           = 34;

type
  int = int64;
  wsp = integer;

var
  pot3 : array [-1..MAX] of int;
  suma : array [-1..MAX] of int;

procedure count;
var
  i :integer;
begin
  pot3[0]:=1;
  suma[0]:=1;
  for i:=1 to MAX do begin
    pot3[i]:=pot3[i-1]*3;
    suma[i]:=suma[i-1] + pot3[i];
  end;
end;

function szukajS (m:int) :int;
var
  i     :integer;
begin
  i:=-1;
  repeat 
    inc (i);
  until (m <= suma[i]);
  szukajS := i;
end;

function solveX (z,m,n :int) :wsp; forward;
function solveY (z,m,n : int) :wsp;
var
  w,p,s :int;
  koniec :boolean;
begin
  w := pot3[z];
  p := 2 * w;
  s := p + suma[z-1];
  if m < p then begin {Y górne}
    solveY := solveY (z-1,m-w,n);
  end else if m > s then begin {Y dolne}
    repeat
      koniec := true;
      if n < 2*(m-s) then solveY := solveY (z-1,m-p,n)
      else if n < w then solveY := 0
      else begin 
        n:= n - w;
        koniec := false;
      end;
    until koniec;
  end else begin {X}
    if n <=  2*(m - p) then solveY:= solveX (z-1,m-p,n)
    else if n < w then solveY := 0
    else begin 
      n := n - w;
      if n <=  2*(m - p) then solveY:= (solveX (z-1,m-p,n)*2) mod 3
      else solveY := 0;
    end;
  end;
end;
  
function solveX (z,m,n : int) :wsp;
var
  w :int;
  koniec :boolean;
begin
  w := pot3[z];
  if z <= 0 then begin solveX := 1
  end else if m <= suma[z-1] then begin {X górne}
    solveX := solveX (z-1,m,n);
  end else if m >= w then begin {X dolne}
    repeat
      koniec := true;
      if n <= 2*(m-w) then solveX := solveX (z-1,m-w,n)
      else if n < w then solveX := 0
      else begin 
        n := n - w; 
        koniec := false;
      end;
    until koniec;
  end else begin {Y}
    if n <= 2*m - w then solveX := solveY (z-1,m,n)
    else if n < w then solveX := 0
    else if n <= 2*m then solveX := solveY (z-1,m,2*m-n)
    else solveX:= 0;
  end;
end;

function solve (m,n : int) :wsp;
begin
  solve := solveX (szukajS(m),m,n);
end;

var k,j :word;
var i,n :int;
var fin, fout :text;
begin
  count;
  Assign (fin, '');
  Reset (fin);
  Assign (fout, '');
  Rewrite (fout);
  ReadLn (fin, k);
  for j:=1 to k do begin
    ReadLn (fin, n,i);
    if i> 2*n then WriteLn ('zle');
    WriteLn (fout, solve (n,i));
  end;
  Close (fin);
  Close (fout);
end.
