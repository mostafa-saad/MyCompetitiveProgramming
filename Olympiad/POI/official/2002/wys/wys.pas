(*************************************************************************
 *                                                                       *
 *                    IX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Rozwi±zanie zadania: Wyspa                                          *
 *   Plik:                wys.pas                                        *
 *   Autor:               Tomasz Waleñ                                   *
 *************************************************************************)
program wys;
const
   maxn	 = 50000;
   f_in	 = 'wys.in';
   f_out = 'wys.out';
var
   f	: text;
   sol	: longint;
   dist	: array[1..maxn] of longint;
   n	: longint;
   sum	: longint;
   sum2	: longint; {sum div 2}

procedure read_data;
var
   i : longint;
begin
   Assign(f,f_in);
   reset(f);
   readln(f,n);
   for i:=1 to n do readln(f,dist[i]);
   close(f);
end; { read_data }

procedure check_sol(value,j : longint);
var
   tmp : longint;
begin
   tmp:=value;
   if tmp>sum-value then tmp:=sum-value;
   if tmp>sol then sol:=tmp;

   {sprawdzane na drugim koncu krawedzi}
   value:=value+dist[1+((j-1) mod n)];
   tmp:=value;
   if tmp>sum-value then tmp:=sum-value;
   if tmp>sol then sol:=tmp;
end; { check_sol }

procedure solve;
var
   i,j	: longint;
   s	: longint;
begin
   sol:=0;
   
   sum:=0;
   for i:=1 to n do sum:=sum+dist[i];
   sum2:=sum div 2;
   
   
   i:=1;j:=1;
   s:=0;
   while (s<=sum2) do begin
      s:=s+dist[j];
      inc(j);
   end;
   {teraz s > sum2}   
   dec(j);s:=s-dist[j];
   {teraz s <= sum2}
   check_sol(s,j);

   {szukanie maksymalnej odleglosci, gdy pierwsza druzyna zostaje
    zakwaterowana w miescie i}
   for i:=2 to n do begin
      s:=s-dist[i-1];
      while (s<=sum2) do begin
	 s:=s+dist[1+((j-1) mod n)];
	 inc(j);
      end;
      dec(j);s:=s-dist[1+((j-1) mod n)];
      
      check_sol(s,j);
      
   end;   
end; { solve }

procedure write_answer;
begin
   Assign(f,f_out);
   rewrite(f);
   Writeln(f,sol);
   close(f);
end;

begin
   read_data;
   solve;
   write_answer;
end.
