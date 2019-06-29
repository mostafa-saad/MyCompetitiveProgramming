{*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Megalopolis (MEG)                                          *}
{*   Plik:    meg1.pas                                                   *}
{*   Autor:   Anna Niewiarowska                                          *}
{*   Opis:    Rozwiazanie wzorcowe.                                      *}
{*                                                                       *}
{*************************************************************************}
program meg; 

var
  z:char;
  n,m,tree_size,x,y,j:longint;
  first_son: array[1..250000] of longint; 
  next_brother: array[1..250000] of longint;
  depth: array[1..250000] of longint; {odleglosc od wioski numer 1}
  number: array[0..250000] of longint; {numer w numeracji preorder}
  subtree_end: array[0..250000] of longint; {zakres poddrzewa w num. preorder}
  tree: array[0..600000] of longint; {drzewo przedzialowe}

procedure read_input();
var
  i:longint;
  a,b: longint;
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

function make_preorder(vertex:longint; num:longint; dep:longint): longint;
var
  son: longint;
begin
  number[vertex]:=num;
  depth[vertex]:=dep;
  num:=num+1;
  son:=first_son[vertex];
  while son<>0 do begin
    num:=make_preorder(son,num,dep+1);
    son:=next_brother[son];
  end;
  subtree_end[vertex]:=num-1;
  make_preorder:=num;
end;

procedure make_tree(); {tworzenie drzewa licznikowego}
var
  i: longint;
begin
  tree_size:=2;
  while tree_size<n do tree_size:=tree_size*2;
  tree_size:=tree_size*2;
  for i:=0 to n-1 do tree[i]:=0; 
end;

procedure change_interval(a:longint; b:longint; act_num:longint; act_size:longint);
var
  new_size:longint;
begin
  if (a<=0) and (b>=act_size-1) then begin
    tree[act_num]:=tree[act_num]+1;
  end
  else begin
    new_size:=act_size div 2;
    if (a < new_size) then change_interval(a,b,2*act_num+1,new_size);
    if (b >= new_size) then 
      change_interval(a-new_size,b-new_size,2*act_num+2,new_size);
  end;
end;

procedure change_road(a:longint; b:longint);
begin
  change_interval(number[b],subtree_end[b],0,tree_size div 2);
end;

function count_values(number:longint; act_num:longint; tree_size:longint; act_value:longint):longint;
var
  new_size:longint;
begin
  act_value:=act_value-tree[act_num];
  if (tree_size>1) then begin
    new_size:=tree_size div 2;
    if (number<new_size) then
      act_value:=count_values(number,2*act_num+1,new_size,act_value)
    else
      act_value:=count_values(number-new_size,2*act_num+2,new_size,act_value);
  end;
  count_values:=act_value;
end;

procedure trip(vertex:longint);
var
  a,d:longint;
begin
  d:=depth[vertex];
  a:=number[vertex];
  d:=count_values(a,0,tree_size div 2,d);
  writeln(d);  
end;

BEGIN
  read_input();
  make_preorder(1,0,0);
  make_tree();
  readln(m);
  for j:=1 to n+m-1 do begin
    read(z);
    if (z='A') then begin
      readln(x,y);
      change_road(x,y);
    end
    else begin
      readln(x);
      trip(x);
    end;
  end;
END.