(*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Randka                                           *
 *   Autor:             Zbigniew Wojna                                   *
 *   Zlozonosc czasowa: O(n*k)                                           *
 *   Opis:              Rozwiazanie powolne                              *
 *                                                                       *
 *************************************************************************)

Program randka;
const 
  MAXN = 500005;

var
  n,k,a,b,i,path1_ind,path2_ind : longint;
  wyn11,wyn12,wyn21,wyn22,max1,max2,min1,min2 : longint;
  graf, path1, path2 : array[0 .. MAXN] of longint;
  vis1, vis2 : array[0 .. MAXN] of boolean;


function max(a, b: longint) : longint;
begin
  max := a;
  if b > a then max := b;
end;

function min(a, b: longint) : longint;
begin
  min := a;
  if b < a then min := b;
end;
  
procedure func(a, b : longint; var w1, w2 : longint);
var
  out : Boolean;
begin
    out := False;

    while path1_ind <> 0 do begin
      vis1[path1[path1_ind - 1]] := false; 
      dec(path1_ind)
    end;
    while path2_ind <> 0 do begin
      vis2[path2[path2_ind - 1]] := false; 
      dec(path2_ind)
    end;

    while not vis1[a] do begin
      vis1[a] := true;
      path1[path1_ind] := a;
      inc(path1_ind);
      a := graf[a];
    end;
  
    while(b <> path1[path1_ind - 1]) and (not vis2[b]) do begin
      vis2[b] := true;
      path2[path2_ind] := b;
      inc(path2_ind);
      b := graf[b];
    end;
    path2[path2_ind] := b; 
    inc(path2_ind);
    vis2[b] := true;
  
    if(path1[path1_ind - 1] <> path2[path2_ind - 1]) then begin
      w1 := -1;
      w2 := -1;
      out := True;
    end;
    
    if not out then begin
      while (path1_ind <> 0) and (path2_ind <> 0) and 
      (path1[path1_ind - 1] = path2[path2_ind - 1]) do begin
        vis1[path1[path1_ind - 1]] := false;
        vis2[path2[path2_ind - 1]] := false;
        dec(path1_ind);
        dec(path2_ind);
      end;

      w1 := path1_ind;
      w2 := path2_ind;
    end;
end;

begin
  
  // inicjalizacja
  path1_ind := 0; path2_ind := 0;
  for i := 0 to MAXN do begin vis1[i] := false; vis2[i] := false; end;

  // IN
  readln(n,k);
  for i := 1 to n do read(graf[i]);

  // OUT
  for i := 1 to k do begin
    read(a,b);

    func(a, b, wyn11, wyn12);
    func(b, a, wyn22, wyn21);
    
    max1 := max(wyn11, wyn12);
    min1 := min(wyn11, wyn12);
    max2 := max(wyn21, wyn22);
    min2 := min(wyn21, wyn22);

    if(max2<max1) or ((max1=max2) and (min2<min1)) or 
        ((max1=max2) and (min1=min2) and (wyn11<wyn12)) then begin
      wyn11 := wyn21; 
      wyn12 := wyn22;
    end;

    writeln(wyn11,' ', wyn12);
  end;
end.


