(*************************************************************************
 *                                                                       *
 *                    IX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Rozwi±zanie zadania: Komiwoja¿er Bajtazar                           *
 *   Plik:                kom.pas                                        *
 *   Autor:               Tomasz Waleñ                                   *
 *************************************************************************)
const
   maxn	 = 50000;
   maxnn = 16;
   maxm	 = 5000;
   f_in	 = 'kom.in';
   f_out = 'kom.out';
type
   plist = ^tlist;
   tlist = record
	      v	: word;
	      n	: plist;
	   end;
var
   f	 : text;
   n,m	 : longint;
   g	 : array[1..maxn] of plist;
   trasa : array[0..maxm] of word;
   p	 : array[0..maxnn,1..maxn] of word;
   odw	 : array[1..maxn] of boolean;
   {numer wierzcholka w numeracji pre-order}
   nr_pre    : array[1..maxn] of word;
   {rozmiar poddrzewa dla danego wierzcholka (liczac z nim samym)}
   rozmiar : array[1..maxn] of word;
   gl    : array[1..maxn] of word;
   suma  : longint;
   licznik   : longint;

procedure dodaj_kr(var l : plist;v:word);
var
   tmp : plist;
begin
   new(tmp);
   tmp^.v:=v;
   tmp^.n:=l;
   l:=tmp;
end;

procedure wczytaj_dane;
var
   i   : longint;
   a,b : word;
begin
   for i:=1 to maxn do g[i]:=nil;
      
   Assign(f,f_in);
   reset(f);
   readln(f,n);
   for i:=1 to n-1 do begin
      readln(f,a,b);
      dodaj_kr(g[a],b);
      dodaj_kr(g[b],a);
   end;
   readln(f,m);
   trasa[0]:=1;   
   for i:=1 to m do readln(f,trasa[i]);
   close(f);
end; { wczytaj_dane }

procedure dfs(v	: word);
var
   l : plist;
begin
   inc(licznik);
   nr_pre[v]:=licznik;
   
   odw[v]:=true;
   l:=g[v];
   while (l<>nil) do begin
      if (not odw[l^.v]) then begin
	 p[0,l^.v]:=v;
	 odw[l^.v]:=true;
	 gl[l^.v]:=gl[v]+1;
	 dfs(l^.v);
      end;
      l:=l^.n;
   end;
   rozmiar[v]:=licznik+1-nr_pre[v];
end;

{zwraca true jesli u jest potomkiem v}
function potomek(u,v : word):boolean;
begin
   potomek:=(nr_pre[u]>=nr_pre[v]) and (nr_pre[u]<nr_pre[v]+rozmiar[v]);
end; { potomek }

function lca(u,v : word):word;
var
   i : longint;
   j : integer;
begin
   if (potomek(u,v)) then lca:=v
   else if (potomek(v,u)) then lca:=u
   else begin
      i:=u;
      j:=maxnn;
      while (j>=0) do begin
	 if (potomek(v,p[j,i])) then j:=j-1
	 else i:=p[j,i];
      end;
      lca:=p[0,i];
   end;
end;

procedure oblicz;
var
   odleglosc : longint;
   i,j	     : word;
begin
   fillchar(p,sizeof(p),0);
   fillchar(odw,sizeof(odw),0);
   fillchar(gl,sizeof(gl),0);
   licznik:=0;
   dfs(1);

   p[0,1]:=1;
   for i:=1 to maxnn do 
      for j:=1 to n do p[i,j]:=p[i-1,p[i-1,j]];  

   suma:=0;
   for i:=0 to m-1 do
   begin
      odleglosc:=gl[trasa[i]]+gl[trasa[i+1]]-2*gl[lca(trasa[i],trasa[i+1])];
      suma:=suma+odleglosc;
   end;
end; { oblicz }

procedure zapisz_wynik;
begin
   Assign(f,f_out);
   rewrite(f);
   writeln(f,suma);
   close(f);
end; { zapisz_wynik }


begin
   wczytaj_dane;
   oblicz;
   zapisz_wynik;
end.
