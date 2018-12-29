{*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Biura (BIU)                                                *}
{*   Plik:    biub1.pas                                                  *}
{*   Autor:   Adam Iwanicki                                              *}
{*   Opis:    Rozwi±zanie nieprawidlowe wypisujace zawsze ze kazdy       *}
{*            pracownik moze pracowac osobno                             *}
{*                                                                       *}
{*************************************************************************}
Program Biura;

var n,m,i:LongInt;

begin
  ReadLn(n,m);
  
  WriteLn(n);
  for i:=1 to n do
    Write('1 ');
  WriteLn;
end.

