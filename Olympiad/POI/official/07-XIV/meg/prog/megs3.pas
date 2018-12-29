{*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Megalopolis (MEG)                                          *}
{*   Plik:    megs3.pas                                                  *}
{*   Autor:   Anna Niewiarowska                                          *}
{*   Opis:    Program poprawny, ale za wolny: dla kazdego wierzcholka    *}
{*            trzymamy jego aktualna odleglosc od wioski numer 1         *}
{*                                                                       *}
{*************************************************************************}
program megs3;

var
  first_son: array[1..250001] of longint;
  next_brother: array[1..250001] of longint;
  act_depth: array[1..250001] of longint;
  n,m,x,y,j: longint;
  z: char;
  
procedure read_input();
var
  i,a,b: longint;
begin
  readln(n);
  for i:=1 to n do begin
    first_son[i]:=0;
    next_brother[i]:=0;
  end;
  for i:=1 to n-1 do begin
    readln(a,b);
    next_brother[b]:=first_son[a];
    first_son[a]:=b;
  end;
end;

procedure count_depth(vertex:longint; value:longint);
var
  son:longint;
begin
  act_depth[vertex]:=value;
  son:=first_son[vertex];
  while son<>0 do begin
    count_depth(son,value+1);
    son:=next_brother[son];
  end;
end;

procedure change_road(vertex: longint);
var
  son:longint;
begin
  act_depth[vertex]:=act_depth[vertex]-1;
  son:=first_son[vertex];
  while son<>0 do begin
    change_road(son);
    son:=next_brother[son];
  end;
end;

BEGIN
  read_input();
  count_depth(1,0);

  readln(m);
  for j:=1 to n+m-1 do begin
    read(z);
    if (z='A') then begin
      readln(x,y);
      if (x>y) then y:=x;
      change_road(y);
    end
    else begin
      readln(x);
      writeln(act_depth[x]);
    end;
  end;

END.