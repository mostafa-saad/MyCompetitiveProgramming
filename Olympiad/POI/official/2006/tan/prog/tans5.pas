(*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: TAN (Tance w kolkach)                          *
 *   Plik:                tans5.pas                                      *
 *   Autor:               Tomasz Waleñ                                   *
 *   Opis:                Rozwiazanie nieoptymalne, o z³o¿onoœci O(n^2)  *
 *                                                                       *
 *************************************************************************)

program tan;
const
   MOD_ = 2005;
   MAXN = 5000;
var
   n,k,l     : longint;
   answer    : array[0..MAXN,0..MAXN] of integer;
   factorial : array[0..MAXN] of longint;
   mn        : array[0..MAXN] of longint;

   procedure init;
   var
     i,j:longint;
   begin
     factorial[0]:=1;
     for i:=1 to n do factorial[i]:=(i*factorial[i-1]) mod MOD_;

     for i:=0 to n do
        for j:=0 to n do if (j*l>i) then answer[i,j]:=0 else answer[i,j]:=-1;

     fillchar(mn,sizeof(mn),0);
     for i:=l to n do begin
       mn[i]:=1;
       for j:=i-1 downto i-l+1 do mn[i]:=(j*mn[i]) mod MOD_;
     end;

     for i:=l to n do answer[i,1]:=factorial[i-1];
   end;

   function count(nn,kk:longint) : longint;
   var
       i,j:longint;
       res:longint;
   begin
       if (answer[nn,kk]<>-1) then begin
          count:=answer[nn,kk];
    exit;
       end;

       res:=0;
       if ((nn-1 mod MOD_)<>0) then res:=(res+(nn-1)*count(nn-1,kk)) mod MOD_;

       if (mn[nn]<>0) then res:=(res+mn[nn]*count(nn-l,kk-1)) mod MOD_;

       count:=res;
       answer[nn,kk]:=res;
   end;

   procedure solve;
   begin
      count(n,k);
   end;

begin
    readln(n,k,l);
    init;
    solve;
    writeln(answer[n,k]);
end.
