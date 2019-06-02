(*************************************************************************
 *                                                                       *
 *                    IX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Rozwi±zanie zadania: Protoko³y                                      *
 *   Plik:                pro.pas                                        *
 *   Autor:               Tomasz Waleñ                                   *
 *************************************************************************)
program pro;
const
   f_in	 = 'pro.in';
   f_out = 'pro.out';
   maxm	 = 100;
   maxl	 = 100;
   maxk	 = 10;

   maxa = 1000;
   maxp = 10000;

type
   tlong = array[0..maxa] of word; { tlong[0] -- dlugosc }
var
   f	   : text;
   k,n,m,l : longint;
   answer  : longint;


procedure read_data;
begin
   Assign(f,f_in);
   reset(f);
   readln(f,k,n,m,l);
   close(f);
end; { read_data }

procedure error(msg : string);
begin
   writeln('Error: ',msg);
   halt(1);
end; { error }

procedure tlong_print(var x : tlong);
var
   i	: integer;
   j,ii	: integer;
   tmp	: string;
begin
   for i:=x[0] downto 1 do begin
      tmp:='';
      j:=x[i];      
      for ii:=1 to 4 do begin
	 tmp:=chr(ord('0')+(j mod 10))+tmp;
	 j:=j div 10;
      end;
      write(tmp);
   end;
   writeln;
end; { tlong_print }

procedure tlong_set(var x : tlong;value:longint);
begin
   x[1]:=value mod maxp;
   x[2]:=value div maxp;
   if (x[2]>0) then x[0]:=2 else x[0]:=1;
end; { tlong_set }

procedure tlong_add(var x : tlong;var value:tlong;shift:word);
var
   i	   : integer;
   sum	   : word;
   m	   : word;
   new_len : integer;
begin
   if (shift>x[0]) then begin
      if (shift>maxa) then error('arithmetic overflow');
      for i:=x[0]+1 to shift do x[i]:=0;
      x[0]:=shift;
   end;
   
   m:=0;
   new_len:=x[0];
   for i:=1 to value[0]+1 do
   begin
      sum:=m;
      if (i<=value[0]) then sum:=sum+value[i];
      if (i+shift<=x[0]) then sum:=sum+x[i+shift];
      m:=sum div maxp;
      sum:=sum mod maxp;
      if (sum>0) or (i<value[0]+1) then begin
	 if (i+shift>maxa) then error('Arithmetic overflow');
	 x[i+shift]:=sum;
	 if (i+shift>new_len) then new_len:=i+shift;
      end;
   end;
   x[0]:=new_len;
end; { tlong_set }

procedure tlong_sub(var x : tlong;value:word);
var
   i : integer;   
begin
   if (x[1]>=value) then x[1]:=x[1]-value
   else begin
      x[1]:=maxp+x[1]-value;
      i:=2;
      while (i<=x[0]) do begin
	 if (x[i]>0) then begin
	    x[i]:=x[i]-1;
	    break;
	 end else begin
	    x[i]:=maxp-1;
	    inc(i);
	 end;
      end;
   end;
   
   i:=x[0];
   while (i>1) and (x[i]=0) do dec(i);
   x[0]:=i;
end; { tlong_set }

procedure tlong_sub2(var x : tlong;var value:tlong);
var
   i:integer;
   l1,l2:integer;
   mm:integer;   
begin
   l1:=x[0];
   l2:=value[0];
   
   i:=1;
   mm:=0;
   while (i<=l1) do begin
     if (i<=l2) then mm:=mm+value[i];
     if (x[i]>=mm) then begin
       x[i]:=x[i]-mm;
       mm:=0;
     end else begin
       x[i]:=x[i]+maxp-mm;
       mm:=1;
     end;
     inc(i);
     if (i>l2) and (m=0) then break;
   end;

   i:=l1;
   while (i>1) and (x[i]=0) do dec(i);   
   x[0]:=i;
end; { tlong_sub2 }


procedure tlong_mult(var x : tlong;value:longint);
var
   m   : longint;
   tmp : longint;
   i   : integer;
begin
   m:=0;
   for i:=1 to x[0]+1 do begin
      tmp:=0;
      if (i<=x[0]) then tmp:=x[i];
      tmp:=tmp*value;
      tmp:=tmp+m;
      m:=tmp div maxp;
      if (i>x[0]) and (tmp>0) then begin
	 x[0]:=i;
	 if (i>maxa) then error('Arithmetic overflow (mult)');
      end;
      x[i]:=tmp mod maxp;	 
   end;
end; { tlong_set }

procedure tlong_assign(var x : tlong;var value:tlong);
var
   i : integer;
begin
   x[0]:=value[0];
   for i:=1 to x[0] do x[i]:=value[i];
end; { tlong_assign }

procedure tlong_mult2(var x : tlong;var value:tlong);
var
   tmp	   : tlong;
   tmp_sum : tlong;
   i	   : integer;
begin
   tlong_set(tmp_sum,0);
   for i:=1 to value[0] do if (value[i]>0) then begin
      tlong_assign(tmp,x);
      tlong_mult(tmp,value[i]);
      tlong_add(tmp_sum,tmp,i-1);
   end;
   tlong_assign(x,tmp_sum);
end; { tlong_set }

function tlong_cmp(var x1,x2 : tlong):integer;
var
   l1,l2 : integer;
   i	 : integer;
begin
   l1:=x1[0];
   while (l1>1) and (x1[l1]=0) do dec(l1);
   x1[0]:=l1;

   l2:=x2[0];
   while (l2>1) and (x2[l2]=0) do dec(l2);
   x2[0]:=l2;

   if (l1<l2) then tlong_cmp:=-1
   else if (l1>l2) then tlong_cmp:=1
   else begin
      i:=l1;
      while (i>1) and (x1[i]=x2[i]) do dec(i);
      
      if (x1[i]<x2[i]) then tlong_cmp:=-1
      else if (x1[i]>x2[i]) then tlong_cmp:=1
      else tlong_cmp:=0;
   end;   
end; { tlong_assign }


procedure solve;
var
   i,j	: longint;
   tmp	: tlong;
   sum	: tlong;
   s    : array[0..maxm] of tlong;
   pow2	: tlong;
begin
   tlong_set(sum,k);
   tlong_assign(s[1],sum);

   for i:=2 to l-1 do begin
      tlong_mult(sum,k);
      tlong_assign(s[i],sum);
   end;
   
   tlong_mult(sum,k);
   tlong_sub(sum,k);
   tlong_assign(s[l mod maxm],sum);

   if (m<=l) then begin
      tlong_assign(sum,s[m mod maxm]);
   end;
   
   for i:=l+1 to m do begin
      tlong_mult(sum,k);
      tlong_assign(tmp,s[(i-l) mod maxm]);
      tlong_mult(tmp,k-1);
      tlong_sub2(sum,tmp);
      tlong_assign(s[i mod maxm],sum);
   end;


   {teraz trzeba obliczyc sum^(n/m)}
   j:=n div m;
   tlong_assign(tmp,sum);
   for i:=2 to j do begin
      tlong_mult2(tmp,sum);
   end;

   {answer=floor(log2(sum^(n/m)))}
   tlong_set(pow2,1);
   answer:=0;
   while (tlong_cmp(pow2,tmp)<=0) do begin
      tlong_mult(pow2,2);
      inc(answer);
   end;
   dec(answer);      
end; { solve }

procedure write_answer;
begin
   Assign(f,f_out);
   rewrite(f);
   Writeln(f,answer);
   close(f);
end;

begin
   read_data;
   solve;
   write_answer;
end.
