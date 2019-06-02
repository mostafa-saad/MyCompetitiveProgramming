(*************************************************************************
 *                                                                       *
 *                    IX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Rozwi±zanie zadania: Waga                                          *
 *   Plik:                wag.cpp                                        *
 *   Autor:               Marcin Mucha                                   *
 *************************************************************************)
const
N_MAX = 1000;
W_MAX = 50000;

var
   fin, fout	    : text;
   w		    : array[1..N_MAX] of word;
   sum		    : array[0..W_MAX] of word; { czy mozna uzyskac taka sume
                                                 a jesli tak, to jaki
						 jest najwiekszy odwaznik }
   w_best, sum_best : word;
   n		    : word;

procedure read_data;
var
   i : word;
begin
   assign( fin, 'wag.in');
   reset( fin);
   readln( fin, n);
   for i := 1 to n do readln( fin, w[i]);
   close( fin);
end;

procedure sort;
var
   i, j	: word;
   tmp	: word;
begin
   for i := 1 to n-1 do
      for j := i+1 to n do
	 if w[j] < w[i] then
	 begin tmp := w[i]; w[i] := w[j]; w[j] := tmp end;
end;

procedure gen_sum;
var
   i, j, k : word;
begin
   { zerowanie tablicy sum }
   j := 0;
   for i := 1 to n do inc( j, w[i]);
   sum[0] := 1;
   for i := 1 to j div 2 do sum[i] := 0; { zeby zbyt duzo nie zerowac,
                                           moze dane sa bardzo male }
   { generowanie sum }
   sum_best := 0;
   for i := 1 to n do
      for k := j div 2 downto w[i] do { od gory, zeby nie liczyc tego
                                        samego wiele razy }
	 if sum[k-w[i]] > 0 then
	 begin
	    if sum[k] = 0 then { tej sumy jeszcze nie bylo }
	       sum[k] := i
	    else
	    begin { ta sama suma przy pomocy roznych zestawow }
	       w_best := i;
	       sum_best := k
	    end
	 end
end;

procedure gen_subsets;
var
   i1, i2     : word;
   n1, n2     : word;
   set1, set2 : array[1..N_MAX] of word;
begin
   assign(fout,'wag.out');
   rewrite(fout);
   if sum_best = 0 then
   begin
      writeln(fout,'0 0');
      writeln(fout);
      writeln(fout)
   end
   else
   begin
      sum[0] := 0;
      i1 := sum_best; n1 := 0;
      while (i1 <> 0) do
      begin
         inc(n1);
	 set1[n1] := w[sum[i1]];
	 dec(i1,w[sum[i1]]);
      end;
      set2[1] := w[w_best];
      i2 := sum_best - w[w_best]; n2 := 1;
      while (i2 <> 0) do
      begin
         inc(n2);
	 set2[n2] := w[sum[i2]];
	 dec(i2,w[sum[i2]]);
      end;
      writeln(fout,n1,' ',n2);
      for i1 := 1 to n1 do
      begin
        write(fout,set1[i1]);
	if i1 < n1 then write(fout,' ')
	else writeln(fout)
      end;
      for i2 := 1 to n2 do begin
        write(fout,set2[i2]);
	if i2 < n2 then write(fout,' ')
	else writeln(fout)
      end;
   end;
   close(fout);
end;

begin
   read_data;
   sort;
   gen_sum;
   { na zmiennych w_best, sum_best mamy informacje o najlepszym rozwiazaniu }
   gen_subsets;
end.
