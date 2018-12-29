(*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:              Korale (KOR)                                  *
 *   Plik:                 kor1.pas                                      *
 *   Autor:                Wojciech Tyczynski                            *
 *   Opis:                 Rozwiazanie wzorcowe.                         *
 *   Zlozonosc czasowa:    O(n * (log n)^2)                              *
 *   Zlozonosc pamieciowa: O(n * log n)                                  *
 *                                                                       *
 *************************************************************************)


program Korale;

const MAX_N = 200000;
const MAX_LOG = 19;

type para = record
		first,second:longint;
				end;

var n : longint;
	 T : array [0..MAX_N] of longint;
	 W : array [0..1,0..MAX_LOG,0..MAX_N] of longint;
	 ilosc,size : longint;
	 K : array [0..2*MAX_N] of para;
	 co : array [0..MAX_N+1] of longint;
	 pot : array [0..MAX_LOG+1] of longint;
	 i,j,u,v : longint;
	 p,dl,ile : longint;
	 f : para;
	 res,ww : longint;
	 wynik : array [0..MAX_N+1] of longint;


function min(x,y:para):para;
begin
	if ((x.first<y.first) or ((x.first=y.first) and (x.second<y.second))) then
		min:=x
	else
		min:=y;
end;


function KMR(x:longint; dl:longint):para;
	var d:longint;
		 a,b:para;
begin
	d:=co[dl];
	a.first:=W[0,d,x]; a.second:=W[0,d,x+dl-pot[d]];
	b.first:=W[1,d,x+dl-pot[d]]; b.second:=W[1,d,x];
	KMR:=min(a,b);
end;


function znajdz(e:para):longint;
	var l,r,q:longint;
begin
	l:=0; r:=size-1;
	while (l<r) do begin
		q:=(l+r) div 2;
		if ((e.first<K[q].first) or 
			((e.first=K[q].first) and (e.second<=K[q].second))) then r:=q
		else l:=q+1;
	end;
	znajdz:=l;
end;


procedure unique;
	var i,j: longint;
begin
	i:=1;
	for j:=1 to size-1 do
		if ((K[j].first<>K[j-1].first) or(K[j].second<>K[j-1].second)) then begin
			K[i]:=K[j]; inc(i);
		end;
	size:=i;
end;


procedure sort(l,r:longint);
	var i,j:longint;
		 tmp,p:para;
begin
	i:=l; j:=r;
	p:=K[(l+r) div 2];
	repeat
		while ((K[i].first<p.first) or 
			((K[i].first=p.first) and (K[i].second<p.second))) do inc(i);
		while ((p.first<K[j].first) or
			((p.first=K[j].first) and (p.second<K[j].second))) do dec(j);
		if (i<=j) then begin
			tmp:=K[i];
			K[i]:=K[j];
			K[j]:=tmp;
			inc(i); dec(j);
		end;
	until (i>j);
	if (l<j) then sort(l,j);
	if (i<r) then sort(i,r);
end;


begin
	readln(n);
	for i:=0 to n-1 do
		read(T[i]);

	pot[0]:=1;
	for i:=1 to MAX_LOG do
		pot[i]:=2*pot[i-1];

	ilosc:=n;
	u:=1; v:=-1;
	for i:=1 to n do begin
		if (i=u) then begin
			inc(v); u:=2*u;
		end;
		co[i]:=v;
	end;

	p:=0; dl:=1;
	for i:=0 to n-1 do begin
		W[0,0,i]:=T[i];
		W[1,0,i]:=T[i];
	end;
	dl:=2*dl; inc(p);

	while (dl<=n) do begin
		size:=0;
		for i:=0 to n-dl do begin
			f.first:=W[0,p-1,i];
			f.second:=W[0,p-1,i+(dl div 2)];
			K[size]:=f; inc(size);

			f.first:=W[1,p-1,i+(dl div 2)];
			f.second:=W[1,p-1,i];
			K[size]:=f; inc(size);
		end;

		sort(0,size-1);
		unique;

		for i:=0 to n-dl do begin
			f.first:=W[0,p-1,i];
			f.second:=W[0,p-1,i+(dl div 2)];
			W[0,p,i]:=ilosc+znajdz(f);

			f.first:=W[1,p-1,i+(dl div 2)];
			f.second:=W[1,p-1,i];
			W[1,p,i]:=ilosc+znajdz(f);
		end;

		dl:=2*dl; inc(p); ilosc:=ilosc+size;
	end;


	res:=0;
	ww:=0;
	for i:=1 to n do begin
		for j:=0 to ((n div i)-1) do
			K[j]:=KMR(i*j,i);
	 	sort(0,((n div i)-1));
		ile:=1;
		for j:=1 to ((n div i)-1) do begin
			if ((K[j].first<>K[j-1].first) or (K[j].second<>K[j-1].second)) then 
				inc(ile);
		end;
		if (res<ile) then begin
			res:=ile; ww:=0;
		end;
		if (res=ile) then begin
			wynik[ww]:=i; inc(ww);
		end;
	end;

	writeln(res,' ',ww);
	for i:=0 to ww-2 do
		write(wynik[i],' ');
	writeln(wynik[ww-1]);
end.
