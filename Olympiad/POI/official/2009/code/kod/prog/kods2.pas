(*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Kodowanie (KOD)                                           *
 *   Plik:     kods5.pas                                                 *
 *   Autor:    Piotr Niedzwiedz                                          *
 *   Opis:     Rozwiazanie wolne O(n^2). Przeszukiwania bez spamietywania*
 *                                                                       *
 *************************************************************************)

const
	nmx=1500000;
VAR
	S: array [0..1,0..nmx] of longint;
	W,stack,LF: array [0..nmx] of longint;
	m,h,n,l,i,z,wynik,wh: longint;
	wazny,synch: array [0..nmx] of boolean;
	znak:char;

procedure dfs1(x,y:longint);
begin
	if S[0][y] = 0 then begin
		if not wazny[x] then begin
			wazny[x]:=true;
			W[wh]:=x;
			inc(wh);
		end;
	end else begin
		if S[0][x]=0 then x:=0;
		dfs1(S[0][x],S[0][y]);
		dfs1(S[1][x],S[1][y]);
	end;
end;

procedure dfs2(x,y:longint);
begin
	if S[0][y] = 0 then begin
		if not wazny[x] then begin
			wazny[x]:=true;
			W[wh]:=x;
			inc(wh);
		end;
	end else begin
		if S[0][x]=0 then x:=0;
		dfs2(S[0][x],S[0][y]);
		dfs2(S[1][x],S[1][y]);
	end;
end;

procedure dfs3(x,y:longint);
begin
	if S[0][y]=0 then begin
		if S[0][x]<>0 then
	  		synch[y]:=false;
	end else begin
		if S[0][x]=0 then x:=0;
		dfs3(S[0][x],S[0][y]);
		dfs3(S[1][x],S[1][y]);
	end;
end;


begin
	readln(m);
	h:=1; stack[0]:=0; n:=1; l:=0;
	for i:=0 to m-1 do begin
		read(znak);
		if (znak = 'B') then 
			dec(h)
		else if (znak = 'X') then begin
			LF[l]:=stack[h-1];
			inc(l);
		end
		else begin
			z:=ord(znak)-ord('0');
			S[z][stack[h-1]]:=n;
			stack[h]:=n;
			S[0][n]:=0;S[1][n]:=0;
			inc(h); inc(n);
		end;	
	end;
	wh:=0;
	for i:=0 to n-1 do begin
		wazny[i]:=false; synch[i]:=true;
	end;
	for i:=0 to n-1 do dfs1(0,i);
	i:=0;
	while i<wh do begin
		dfs2(W[i],0);
		inc(i);
	end;
	for i:=0 to wh-1 do dfs3(W[i],0);
	wynik:=0;
	for i:=0 to l-1 do 
		if synch[LF[i]] then inc(wynik);
	writeln(wynik);
	for i:=0 to l-1 do 
		if synch[LF[i]] then writeln(i+1);
end.
	
