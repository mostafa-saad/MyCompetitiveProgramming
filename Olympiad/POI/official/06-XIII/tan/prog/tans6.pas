(*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: TAN (Tance w kolkach)                          *
 *   Plik:                tans6.pas                                      *
 *   Autor:               Tomasz Waleñ                                   *
 *   Opis:                Rozwiazanie brutalne (generujace wszystkie     *
 *                        kombinacje)                                    *
 *                                                                       *
 *************************************************************************)

program tan;
const
   MOD_ = 2005;
   MAXN = 5000;
var
   n,k,l  : longint;
   answer : longint;
   a      : array[1..MAXN] of boolean;

   procedure gen(cno,c:longint);
   var
       i,j:longint;
   begin
       if (cno=k+1) then begin
          for i:=1 to n do if (not a[i]) then exit;
          answer:=(answer+1) mod MOD_;
       end else if (c=1) then begin
          j:=-1;
          for i:=1 to n do if (not a[i]) then begin j:=i; break; end;
          if (j=-1) then exit;
          a[j]:=true;
          gen(cno,c+1);
          a[j]:=false;
       end else begin
          for i:=1 to n do if (not a[i]) then begin
             a[i]:=true;
             gen(cno,c+1);
             a[i]:=false;
          end;
          if (c>l) then gen(cno+1,1);
       end;
   end;

   procedure solve;
   begin
      fillchar(a,sizeof(a),0);
      gen(1,1);
   end;

begin
    readln(n,k,l);
    solve;
    writeln(answer);
end.
