(*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Panele sloneczne                              *
 *   Autor:                Tomasz Syposz                                 *
 *   Zlozonosc czasowa:    O(n sqrt m)                                   *
 *   Zlozonosc pamieciowa: O(1)                                          *
 *   Opis:                 Rozwiazanie wzorcowe                          *
 *                                                                       *
 *************************************************************************)

Uses math;

VAR
  PM:longint;
  n:longint;
  a:longint;
  b:longint;
  c:longint;
  d:longint;
  i:longint;
 cn:longint;
  t:longint;

PROCEDURE zapytanie();
VAR
  odp:longint;
BEGIN
  odp := 0;
  Read(a);
  Read(b);
  Read(c);
  Read(d);
  PM:=Round(Sqrt(Max(b, d))) + 5;
//   małe odpowiedzi
  for i:=PM downto 1 do
  BEGIN
    if ((a-1) div i <> b div i) and ((c-1) div i <> d div i) then
    BEGIN
      odp := i;
      break;
    END;
  END;
  //duże odpowiedzi
  for t := 1 to PM do
  BEGIN
    i := b div t;
    if (i < odp) then break;
    if ((a-1) div i <> b div i) and ((c-1) div i <> d div i) then
    BEGIN
      odp := i;
      break;
    END;
  END;
  
  for t:=1 to PM do
  BEGIN
    i := d div t;
    if (i < odp) then break;
    if ((a-1) div i <> b div i) and ((c-1) div i <> d div i) then
    BEGIN
      odp := i;
      break;
    END;
  END;
  writeLn(odp);
END;


BEGIN
  read(n);
  for cn:=1 to n do
  BEGIN
    zapytanie();
  END;
END.
