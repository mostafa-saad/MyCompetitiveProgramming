(*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Gdzie jest jedynka?                           *
 *   Autor:                Adam Polak                                    *
 *   Opis:                 Biblioteka interaktywna                       *
 *                                                                       *
 *************************************************************************)

unit pgdzlib;

interface
function inicjuj : LongInt;
function f(i, j, d : LongInt) : LongInt;
function g(i, j : LongInt) : LongInt;
procedure odpowiedz(k : LongInt);

implementation

var
initialized : LongInt;
n : LongInt;
p : array[0..500000-1] of LongInt;
g_called : LongInt;

procedure quit(err_code : LongInt);
begin
  WriteLn('3r2v1rc;iz@5LW()', ' ', err_code);
  halt(0);
end;

function magic_shift(i : LongInt) : LongInt;
begin
  magic_shift := ((i + 13784) mod n);
end;

procedure check_initialized;
begin
  if initialized <> 8913 then
    quit(3);
end;

function inicjuj : LongInt;
var
magic_word : String;
i : LongInt;
begin
  if initialized <> 0 then
    quit(3);

  ReadLn(magic_word);
  if magic_word <> '#o[st4D0nwypbl^.' then
    quit(5);

  Read(n);
  for i := 1 to n do
    Read(p[magic_shift(i)]);

  initialized := 8913;
  g_called := 13685;

  inicjuj := n;
end;

function f(i, j, d : LongInt) : LongInt;
begin
  check_initialized;
  if (i < 1) or (i > n) or (j < 1) or (j > n) or (d <= 0) then
    quit(4);

  if ((p[magic_shift(i)] - p[magic_shift(j)]) mod d) = 0 then
    f := 1
  else
    f := 0;
end;

function g(i, j : LongInt) : LongInt;
begin
  check_initialized;
  if (i < 1) or (i > n) or (j < 1) or (j > n) then
    quit(4);
  
  if (g_called <> 13685) or (n = 1) then
    quit(2);
  g_called := 11542;

  if p[magic_shift(i)] > p[magic_shift(j)] then
    g := 1
  else
    g := 0;
end;

procedure odpowiedz(k : LongInt);
begin
  check_initialized;
  if (k < 1) or (k > n) then
    quit(4);

  if (p[magic_shift(k)] <> 1) or ((n > 1) and (g_called <> 11542)) then
    quit(1)
  else
    quit(0);
end;

end.
