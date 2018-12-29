{*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Zapytania (ZAP)                                            *}
{*   Plik:    zaps2.pas                                                  *}
{*   Autor:   Jakub Pawlewicz                                            *}
{*   Opis:    Rozwiazanie naiwne O(n m^2 log m)                          *}
{*                                                                       *}
{*************************************************************************}
function Even(a  : LongInt) : Boolean;
begin
   Even := not Odd(a);
end;

function GCD(a, b : LongInt) : LongInt;
var
   shift : LongInt;
begin
   shift := 0;
   while true do begin
      if Even(a) then
   if Even(b) then begin
      Inc(shift);
      a := a shr 1;
      b := b shr 1;
   end else begin
      repeat
         a := a shr 1;
      until Odd(a);
   end
      else begin
   while Even(b) do
      b := b shr 1;
   break;
      end;
   end;
   while a <> b do begin
      if a < b then begin
   Dec(b, a);
   repeat
      b := b shr 1;
   until Odd(b);
      end else begin
   Dec(a, b);
   repeat
      a := a shr 1;
   until Odd(a);
      end;
   end;
   GCD := a shl shift;
end;

procedure Solve;
var
   n, i, a, b, d, x, y : LongInt;
begin
   Read(n);
   for i := 1 to n do begin
      Read(a, b, d);
      a := a div d;
      b := b div d;
      d := 0;
      for x := 1 to a do
   for y := 1 to b do
      if GCD(x, y) = 1 then
         Inc(d);
      WriteLn(d);
   end;
end;

begin
   Solve;
end.
