(*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Ptaszek                                       *
 *   Autor:                Aleksander Lukasiewicz                        *
 *   Zlozonosc czasowa:    O(qn)                                         *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wzorcowe                          *
 *                                                                       *
 *************************************************************************)

program Ptaszek;

const max_n = 1000003;
const inf = 1000000008;

var
  n, k, q, test, i, stop, x, candidate1, candidate2: longint;
  d : array[1..max_n] of longint;
  w : array[1..max_n] of longint;
  L : array[0..1, 0..max_n] of longint;
  front, back : array[0..1] of longint;

procedure Clean(x, stop : longint);
var ind : longint;
begin
  ind := x mod 2;
  while (front[ind] < back[ind]) and (L[ind][ front[ind] ] < stop) do
    inc(front[ind]);
end;

function Get_Candidate(x, i : longint) : longint;
var ind, M, add : longint;
begin
  ind := x mod 2;
  if front[ind] = back[ind] then
    Get_Candidate := INF
  else
  begin
    M := L[ind][ front[ind] ];
    if d[M] > d[i] then
      add := 0
    else
      add := 1;
    Get_Candidate := x + add;
  end;
end;

procedure Update(x, i : longint);
var ind : longint;
begin
  ind := x mod 2;
  while (front[ind] < back[ind]) and (d[i] > d[ L[ind][ back[ind] - 1 ] ]) do
    dec(back[ind]);
  L[ind][ back[ind] ] := i;
  inc(back[ind]);
end;
  
begin
  Read(n);
  for i := 1 to n do
  begin
    Read(d[i]);
  end;

	Read(q);

	for test := 1 to q do
	begin

	Read(k);

  w[1] := 0;
  x := 0;
  L[0][0] := 1;
  front[0] := 0;
  front[1] := 0;
  back[0] := 1;
  back[1] := 0;

  for i := 2 to n do
  begin
    stop := i-k;
    if stop < 1 then
      stop := 1;

    Clean(x,stop);
    Clean(x+1, stop);

    if front[x mod 2] = back[x mod 2] then
		inc(x);

	candidate1 := Get_Candidate(x, i);
	candidate2 := Get_Candidate(x+1, i);

	w[i] := candidate1;
	if candidate2 < candidate1 then
	  w[i] := candidate1;
	Update(w[i], i);
  end;
  
  Writeln(w[n]);

	for i := 1 to n+1 do
	begin
		L[0][i] := 0;
		L[1][i] := 0;
		w[i] := 0;
	end;

	end;
end.

