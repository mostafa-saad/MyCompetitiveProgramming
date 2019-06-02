(*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Kodowanie (KOD)                                           *
 *   Plik:     kods5.pas                                                 *
 *   Autor:    Piotr Niedzwiedz                                          *
 *   Opis:     Rozwiazanie wolne O(n*L). Nie korzysta z faktu, ze kody   *
 *             maja wspolnbe prefiksy.                                   *
 *                                                                       *
 *************************************************************************)

const
	nmx=1500000;
VAR
	S: array [0..1,0..nmx] of longint;
	W,stack,LF,Q,P: array [0..nmx] of longint;
	m,h,n,l,i,t,j,z,wynik,wh,qh,len: longint;
	lok:boolean;
	wazny,synch: array [0..nmx] of boolean;
	znak:char;

function go(v,leaf,lim:longint):longint;
var
	w:longint;
begin
	qh:=0;
	w:=LF[leaf];
	while (P[w] <> -1) and (lim>0) do begin
		dec(lim);
		if S[0][P[w]] = w then
			Q[qh]:=0
		else
			Q[qh]:=1;
		w:=P[w];
		inc(qh);
	end;
	if lim <> 0 then lok:=false;
	while qh <> 0 do begin
		dec(qh);
		if S[0][v]=0 then v:=0;
		v:=S[Q[qh]][v];
	end;	
	go:=v;
end;

begin
	readln(m);
	P[0]:=-1;
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
			P[n]:=stack[h-1];
			stack[h]:=n;
			S[0][n]:=0;S[1][n]:=0;
			inc(h); inc(n);
		end;	
	end;
	wh:=0;
	for i:=0 to n-1 do begin
		wazny[i]:=false; synch[i]:=true;
	end;
	for j:=0 to l-1 do begin
		lok:=true;
		len:=1;
		while true do begin
			t:=go(i,j,len);
			if not lok then break;
			inc(len);
			if not wazny[t] then begin
				wazny[t]:=true;
				W[wh]:=t;
				inc(wh);
			end;
		end;
	end;
	i:=0;
	while i<wh do begin
		for j:=0 to l-1 do begin
			t:=go(W[i],j,nmx);
			if not wazny[t] then begin
				wazny[t]:=true;
				W[wh]:=t;
				inc(wh);
			end;
		end;
		inc(i);
	end;
	for i:=0 to wh-1 do begin
		for j:=0 to l-1 do begin
			t:=go(W[i],j,nmx);
			if S[0][t] <> 0 then	synch[LF[j]]:=false;
		end;
	end;
	wynik:=0;
	for i:=0 to l-1 do 
		if synch[LF[i]] then inc(wynik);
	writeln(wynik);
	for i:=0 to l-1 do 
		if synch[LF[i]] then writeln(i+1);
end.
	
