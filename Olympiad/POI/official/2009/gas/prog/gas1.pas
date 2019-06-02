(*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Gasnice (GAS)                                             *
 *   Plik:     gas1.pas                                                  *
 *   Autor:    Piotr Niedzwiedz                                          *
 *   Opis:     Rozwiazanie wzorcowe O(n*k)                               *
 *                                                                       *
 *                                                                       *
 *************************************************************************)

const
	nmx=100000;
	kmx=21;
VAR
	edge_to,edge_next: array[0..2*nmx] of longint;
	edge: array[0..nmx] of longint;	
	n,k,i,m,a,b,result: longint;
	s,tmp,mn: int64;
	up,need: array [0..nmx,0..kmx] of int64;


function min(a,b:int64):int64;
begin
	if a<b then min:=a
	else min:=b;
end;


procedure dfs(v,p:longint);
var 
	i,t,j:longint;
	mn:int64;
begin 
	for i:=0 to k do begin
		up[v][i]:=0; need[v][i]:=0;
	end;
	need[v][0]:=1;
	i:=edge[v];
	while i <> -1 do begin
		t:=edge_to[i];	
		if t <> p then begin
			dfs(t,v);
			for j:=0 to k-1 do begin
				up[v][j]:=up[v][j]+up[t][j+1];
				need[v][j+1]:=need[v][j+1]+need[t][j];
			end;
		end;
		i:=edge_next[i];
	end;
	mn:=(need[v][k]+s-1) div s;
	inc(result,mn);
	inc(up[v][k],mn*s);
	for i:=0 to k do begin
		mn:=min(up[v][i],need[v][i]);
		dec(up[v][i],mn);
		dec(need[v][i],mn);
	end;
	for i:=0 to k-1 do begin
		mn:=min(up[v][i+1],need[v][i]);
		dec(up[v][i+1],mn);
		dec(need[v][i],mn);
	end;
end;

procedure addEdge(a,b:longint);
begin
	edge_next[m]:=edge[a];
	edge_to[m]:=b;
	edge[a]:=m;
	inc(m);
end;

begin
	result:=0;
	readln(n,s,k);
	m:=0;
	for i:=0 to n-1 do edge[i]:=-1;
	for i:=0 to n-2 do begin
		readln(a,b);
		addEdge(a-1,b-1);
		addEdge(b-1,a-1);
	end; 
	dfs(0,-1);
	tmp:=0;
	for i:=k downto 0 do begin
		inc(tmp,up[0][i]);
		if tmp < need[0][i] then begin
			mn:=(need[0][i]-tmp+s-1)div s;
			inc(result,mn);
			inc(tmp,mn*s);
		end;
		dec(tmp,need[0][i]);
	end;
	writeln(result);	
end.
	
