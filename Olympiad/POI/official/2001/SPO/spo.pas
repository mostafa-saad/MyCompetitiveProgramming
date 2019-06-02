{*************************************************************************}
{*                                                                       *}
{*                   VIII Olimpiada Informatyczna                        *}
{*                                                                       *}
{*   Rozwi¹zanie zadania: SPOKOJNA KOMISJA                               *}
{*   Plik:                SPO.PAS                                        *}
{*   Autor:               TOMASZ WALEÑ                                   *}
{*************************************************************************}

{ program nale¿y kompilowaæ kompilatorem FreePascal }
program spokojna_komisja;
const
   f_in  = 'spo.in';
   f_out = 'spo.out';
   max_n = 8000;
type
   plist = ^tlist;
   tlist = record
              v : integer;
              n : plist;
           end;
var
   f      : text;
   n,m    : integer;
   g      : array[1..2*max_n] of plist; {graf zaleznosci}
   gr     : array[1..2*max_n] of plist; {odwrocony graf g}
   gc     : array[1..2*max_n] of plist;
   gcr    : array[1..2*max_n] of plist;
   gc_deg : array[1..2*max_n] of integer;

   status : array[1..2*max_n] of boolean;
   scc    : array[1..2*max_n] of integer; {silne spojne skladowe}
   scc_o  : array[1..2*max_n] of integer; {kolejnosc scc po posortowaniu}
   scc_el : array[1..2*max_n] of plist;   {elementy scc}
   scc_c  : integer; {ilosc silnych spojnych skladowych}
   {tabele potrzebne do obliczania spojnych skladowych}
   vis    : array[1..2*max_n] of integer;
   seq    : array[1..2*max_n] of integer;
   seq_no : integer;

   sol    : array[1..2*max_n] of boolean;

procedure add_edge(var l : plist;v:integer);
var
   tmp : plist;
begin
   new(tmp);
   tmp^.v:=v;
   tmp^.n:=l;
   l:=tmp;
end;

procedure read_data;
var
   i,a,b,a1,b1 : integer;
begin
   Assign(f,f_in);
   reset(f);
   readln(f,n,m);
   for i:=1 to 2*n do g[i]:=nil;
   for i:=1 to 2*n do gr[i]:=nil;
   for i:=1 to m do begin
      readln(f,a,b);
      if (b mod 2=1) then b1:=b+1 else b1:=b-1;
      if (a mod 2=1) then a1:=a+1 else a1:=a-1;
      add_edge(g[a],b1);
      add_edge(g[b],a1);
      add_edge(gr[b1],a);
      add_edge(gr[a1],b);
   end;
   close(f);
end; { read_data }

procedure dfs(x : integer);
var
   l : plist;
begin
   vis[x]:=1;

   l:=g[x];
   while (l<>nil) do begin
      if (vis[l^.v]=0) then dfs(l^.v);
      l:=l^.n;
   end;

   inc(seq_no);
   seq[seq_no]:=x;
   vis[x]:=seq_no;
end; { dfs }

procedure dfs_r(x : integer;scc_no:integer);
var
   l : plist;
begin
   vis[x]:=1;
   l:=gr[x];
   while (l<>nil) do begin
      if (vis[l^.v]=0) then dfs_r(l^.v,scc_no);
      l:=l^.n;
   end;
   scc[x]:=scc_no;
end; { dfs }

procedure find_scc;
var
   i,j : integer;
   l : plist;
begin
   for i:=1 to 2*n do vis[i]:=0;
   seq_no:=0;
   for i:=1 to 2*n do if (vis[i]=0) then dfs(i);

   for i:=1 to 2*n do vis[i]:=0;
   for i:=1 to 2*n do scc[i]:=-1;
   scc_c:=0;
   for i:=2*n downto 1 do begin
      j:=seq[i];
      if (vis[j]=0) then begin
         inc(scc_c);
         dfs_r(j,j);
      end;
   end;
{
   Write('scc: ');
   for i:=1 to 2*n do Write(scc[i],' ');
   Writeln;
}
   for i:=1 to 2*n do scc_el[i]:=nil;
   for i:=1 to 2*n do add_edge(scc_el[scc[i]],i);

   for i:=1 to 2*n do gc[i]:=nil;
   for i:=1 to 2*n do gcr[i]:=nil;
   for i:=1 to 2*n do gc_deg[i]:=0;
   for i:=1 to 2*n do begin
      l:=g[i];
      while (l<>nil) do begin
         if (scc[i]<>scc[l^.v]) then begin
            add_edge(gc[scc[i]],scc[l^.v]);
            inc(gc_deg[scc[i]]);
            add_edge(gcr[scc[l^.v]],scc[i]);
         end;
         l:=l^.n;
      end;
   end;
end; { find_scc }

procedure sort;
var
   i,j,k : integer;
   jj    : integer;
   l     : plist;
begin
   for i:=1 to 2*n do vis[i]:=0;
   j:=0;
   for i:=1 to 2*n do begin
      k:=scc[i];
      if (gc_deg[k]=0) and (vis[k]=0) then begin
         vis[k]:=1;
         inc(j);
         scc_o[j]:=k;
      end;
   end;
   k:=0;
   while (k<j) do begin
      jj:=j;
      for i:=k+1 to j do begin
         l:=gcr[scc_o[i]];
         while (l<>nil) do begin
            dec(gc_deg[l^.v]);
            if (gc_deg[l^.v]=0) and (vis[l^.v]=0) then begin
               vis[l^.v]:=1;
               inc(jj);
               scc_o[jj]:=l^.v;
            end;
            l:=l^.n;
         end;
      end;
      k:=j;
      j:=jj;
   end;

   if j<>scc_c then begin
      Writeln('BLAD! silne spojne skladowe tworza cykl k=',k,' j=',j,' scc_c=',scc_c);
      readln;
      halt(1);
   end;
end; { sort }

procedure mark(scc_no : integer);
var
   l : plist;
begin
   if (status[scc_no]) then begin
{      Writeln('mark no=',scc_no);}
      status[scc_no]:=false;
      l:=gcr[scc_no];
      while (l<>nil) do begin
         mark(l^.v);
         l:=l^.n;
      end;
   end;
end;

procedure solve;
var
   i,j,k : integer;
   l     : plist;
begin
{   Write('find_scc ... ');}
   find_scc;
{   Writeln('ok');}

   for i:=1 to 2*n do status[i]:=true;
   for i:=1 to n do if (scc[2*i]=scc[2*i-1]) then mark(scc[2*i]);
   {tu trzeba posortowac topologicznie scc}
{   Write('sort ... ');   }
   sort;
{   Writeln('ok');}


   for i:=1 to 2*n do sol[i]:=false;

{   Write('find_solution... ');}
   for i:=1 to scc_c do begin
      j:=scc_o[i];
      if (status[j]) then begin
         {dodajemy wierzcholki z tej skladowej do rozwiazania}
         {i usuwamy silne spojne skladowe z drugimi osobami z partii}
         l:=scc_el[j];
{        if (l<>nil) then Writeln('ok j=',j);      }
         while (l<>nil) do begin
            k:=l^.v;
            sol[k]:=true;
            if (k mod 2=1) then k:=k+1 else k:=k-1;
            mark(scc[k]);
            l:=l^.n;
         end;
      end;
   end;
{   Writeln('ok');}
end; { solve }

procedure write_answer;
var
   i,j : integer;
   ok  : boolean;
begin
   ok:=true;
   for i:=1 to n do if not (sol[2*i] xor sol[2*i-1]) then ok:=false;
   Assign(f,f_out);
   rewrite(f);
   if (ok) then begin
      for i:=1 to 2*n do if (sol[i]) then Writeln(f,i);
   end else Writeln(f,'NIE');
   close(f);
end; { write_answer }


begin
   read_data;
   solve;
   write_answer;
end.
