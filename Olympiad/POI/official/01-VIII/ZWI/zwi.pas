{*************************************************************************}
{*                                                                       *}
{*                   VIII Olimpiada Informatyczna                        *}
{*                                                                       *}
{*   Rozwi¹zanie zadania: ZWIEDZANIE MIASTA                              *}
{*   Plik:                ZWI.PAS                                        *}
{*   Autor:               TOMASZ WALEÑ                                   *}
{*************************************************************************}

{$I+,$R+}
program zwi;
const
   f_in  = 'zwi.in';
   f_out = 'zwi.out';
   maxn  = 10000;
type
   plist = ^tlist;
   tlist = record
              v   : integer;
              no  : integer;
              n   : plist;
           end;
   tedge = record
              l,s : integer;
           end;

var
   f       : text;
   n       : integer;
   m       : integer;
   g       : array[1..maxn] of plist;
   e       : array[1..2*maxn] of tedge;
   cycle   : array[1..2*maxn] of integer;
   p       : array[1..2*maxn] of integer;
   c_no    : integer;
   vis_e   : array[1..2*maxn] of boolean;
   answer  : boolean;
   c_start : integer;

procedure add_edge(var lst : plist;v,no:integer);
var
   tmp : plist;
begin
   new(tmp);
   tmp^.v:=v;
   tmp^.no:=no;
   tmp^.n:=lst;
   lst:=tmp;
end;

procedure read_data;
var
   a,b,l,s : integer;
   i       : integer;
begin
   Assign(f,f_in);
   reset(f);
   readln(f,n);
   m:=2*n;
   for i:=1 to n do g[i]:=nil;
   for i:=1 to m do begin
      readln(f,a,b,l,s);
      add_edge(g[a],b,i);
      add_edge(g[b],a,i);
      e[i].l:=l;
      e[i].s:=s;
   end;
   close(f);
end; { read_data }

procedure euler(v : integer);
var
   i : integer;
   l : plist;
begin
   l:=g[v];
   while (l<>nil) do begin
      if (not vis_e[l^.no]) then begin
         i:=l^.no;
         vis_e[i]:=true;
         euler(l^.v);
         inc(c_no);
         cycle[c_no]:=i;
         p[c_no]:=v;
      end;
      l:=l^.n;
   end;
end;


procedure solve;
var
   i,j   : integer;
   sum   : longint;
   min_r : longint;
   min_s : integer;
begin
   {sprawdzenie czy rozwiazanie jest mozliwe}
   sum:=0;
   for i:=1 to m do sum:=sum+e[i].s-e[i].l;

   if (sum>=0) then begin
      answer:=true;
      {szukanie cyklu eulera}
      c_no:=0;
      fillchar(vis_e,sizeof(vis_e),0);
      euler(1);

      {teraz trzeba znalezc krawedz z minimalnym zainteresowaniem}
      min_r:=0;
      min_s:=1;
      j:=cycle[1];
      sum:=e[j].s-(e[j].l div 2);
      for i:=2 to c_no do begin
         j:=cycle[i];
         sum:=sum-(e[j].l div 2);
         if (sum<min_r) then begin min_s:=i; min_r:=sum; end;
         sum:=sum+e[j].s;
         sum:=sum-(e[j].l div 2);
      end;
      c_start:=min_s;
   end else begin
      answer:=false;
   end;
end; { solve }

procedure write_answer;
var
   i : integer;
   j : integer;
begin
   Assign(f,f_out);
   rewrite(f);
   if (answer) then begin
      Writeln(f,'TAK');
      Writeln(f,m);
      Writeln(f,cycle[c_start],' ',p[c_start]);
      j:=c_start;
      for i:=2 to m do begin
         inc(j);
         if (j>m) then j:=1;
         Writeln(f,cycle[j]);
      end;
   end else begin
      Writeln(f,'NIE');
   end;
   close(f);
end; { write_answer }

begin
   read_data;
   solve;
   write_answer;
end.
