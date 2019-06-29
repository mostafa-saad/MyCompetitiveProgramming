{*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Megalopolis (MEG)                                          *}
{*   Plik:    megs2.pas                                                  *}
{*   Autor:   Anna Niewiarowska                                          *}
{*   Opis:    Program poprawny, ale za wolny: dla kazdej krawedzi w      *}
{*            drzewie pamietamy, czy jest ona droga czy autostrada i za  *}
{*            kazdym razem sprawdzamy wszystkie krawedzie do wioski 1    *}
{*                                                                       *}
{*************************************************************************}
program megs2;

var
  par: array[1..250000] of longint; {ojciec w drzewie}
  is_road: array[1..250000] of longint; {czy droga nie jest autostrada}
  n,m,x,y,i: longint; 
  z:char;
  
procedure read_input();
var
  a,b,i: longint;
begin
  readln(n);
  for i:=1 to n do is_road[i]:=1;
  for i:=1 to n-1 do begin
    readln(a,b);
    par[b]:=a;
  end;
end;

function count_roads(vertex: longint):longint;
var
  act: longint;
begin
  act:=0;
  while vertex<>1 do begin
    act:=act+is_road[vertex];
    vertex:=par[vertex];
  end;
  count_roads:=act;
end;

begin
  read_input();
  readln(m);
  for i:=1 to n+m-1 do begin
    read(z);
    if z='A' then begin
      readln(x,y);
      if (x>y) then y:=x;
      is_road[y]:=0;
    end
    else begin
      readln(x);
      writeln(count_roads(x));
    end;
  end;
end.
