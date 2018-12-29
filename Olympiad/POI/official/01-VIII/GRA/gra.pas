{*************************************************************************}
{*                                                                       *}
{*                   VIII Olimpiada Informatyczna                        *}
{*                                                                       *}
{*   Rozwi¹zanie zadania: GRA  W ZIELONE                                 *}
{*   Plik:                GRA.PAS                                        *}
{*   Autor:               TOMASZ WALEÑ                                   *}
{*************************************************************************}

program gra;
const
   f_in  = 'gra.in';
   f_out = 'gra.out';
   maxn  = 3000;
   maxm  = 30000;
type
   plist = ^tlist;
   tlist = record
              v : integer;
              n : plist;
           end;
var
   f       : text;
   g       : array[1..maxn] of plist; {graf G}
   gt      : array[1..maxn] of plist; {transpozycja G}
   deg     : array[1..maxn] of integer;
   degt    : array[1..maxn] of integer;
   zie     : array[1..maxn] of integer; {zielone wierzcholki}
   c       : array[1..maxn] of integer;
   s       : array[1..maxn] of integer;
   l       : array[1..maxn] of integer;
   o       : array[1..maxn] of integer;
   a,b,n,z : integer;

procedure add_edge(var ll : plist;dest:integer);
var
   tmp : plist;
begin
   new(tmp);
   tmp^.v:=dest;
   tmp^.n:=ll;
   ll:=tmp;
end;

procedure read_data;
var
   i,j,k : integer;
begin
   Assign(f,f_in);
   reset(f);
   readln(f,a,b);
   n:=a+b;
   for i:=1 to n do degt[i]:=0;
   for i:=1 to n do g[i]:=nil;
   for i:=1 to n do gt[i]:=nil;
   for i:=1 to n do
   begin
      read(f,c[i]);
      read(f,deg[i]);
      for j:=1 to deg[i] do begin
         read(f,k);
         add_edge(g[i],k);
         inc(degt[k]);
         add_edge(gt[k],i);
      end;
      readln(f);
   end;
   close(f);
   z:=0;
   for i:=1 to n do if (c[i]=1) then begin
      inc(z);
      zie[z]:=i;
   end;
end; { read_data }

{zaznaczenie wszystkich wierzcho³ków z których
 I gracz mo¿e wymusiæ doj¶cie do zielonego wierzcho³ka}
procedure mark_v;
var
   qh,qt : integer;
   q     : array[0..maxn] of integer;
   i,j,k : integer;
   dodaj : boolean;
   adj   : plist;
begin
   for i:=1 to n do l[i]:=deg[i];
   for i:=1 to n do o[i]:=0;

   {dodawanie zielonych wierzcholkow do kolejki}
   qh:=0; qt:=0;
   for i:=1 to n do if c[i]=1 then
   begin
      q[qt]:=i;inc(qt);
      o[i]:=1;
   end;

   {*}
   while (qh<>qt) do
   begin
      i:=q[qh];qh:=(qh+1) mod maxn;
      adj:=gt[i];
      while (adj<>nil) do begin
         k:=adj^.v;
         dec(l[k]);
         dodaj:=false;
         if (o[k]=0) then
            if (k<=a) then dodaj:=true
            else if (l[k]=0) then dodaj:=true;
         if (dodaj) then begin
            o[k]:=1;
            q[qt]:=k;
            qt:=(qt+1) mod maxn;
         end;
         adj:=adj^.n;
      end;
   end;
end;


procedure solve;
var
   i,j  : integer;
   usun : boolean;
   k    : integer;
begin
   repeat
      mark_v;
      j:=0; k:=0;
      {usuniecie zielonych wierzcholkow, z ktorych
       mo¿na wyj¶ci poza zbiór o}
      for i:=1 to n do if (c[i]=1) then
      begin
         inc(k);
         usun:=false;
         if (i<=a) and (l[i]=deg[i]) then usun:=true
         else if (i>a) and (l[i]>0) then usun:=true;

         if (usun) then begin
            c[i]:=0;
            inc(j);
         end;
      end;
   until j=0;
   for i:=1 to n do if o[i]=1 then s[i]:=1 else s[i]:=0;
{   for i:=1 to n do Writeln('i=',i,' o[i]=',o[i],' l[i]=',l[i]);}
end; { solve }

procedure write_answer;
var
   i,j : integer;
begin
   j:=0;
   for i:=1 to n do if s[i]=1 then inc(j);
   Assign(f,f_out);
   rewrite(f);
   Writeln(f,j);
   for i:=1 to n do if s[i]=1 then Writeln(f,i);
   close(f);
end; { write_answer }

begin
   read_data;
   solve;
   write_answer;
end.
