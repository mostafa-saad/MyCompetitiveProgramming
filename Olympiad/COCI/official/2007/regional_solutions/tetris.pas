
(*
  Croatian Regional Competition in Informatics 2007
  Task TETRIS
  Programming language Pascal
*)

program tetris;

const MAXS = 100;

var
   v           : array[1..MAXS] of longint;
   s, f, i, rj : longint;

begin
   readln(s, f);
   if (f=4)or(f=7) then
   begin
      dec(f);
      for i:=1 to s do read(v[s-i+1]);
   end else
      for i:=1 to s do read(v[i]);

   rj := 0;
   case f of
     1:  begin
            rj:=s;
            for i:=1 to s-3 do
               if (v[i]=v[i+1])and(v[i]=v[i+2])and(v[i]=v[i+3]) then inc(rj);
         end;
     2:  begin
            for i:=1 to s-1 do
               if v[i]=v[i+1] then inc(rj);
         end;
     3:  begin
            for i:=1 to s-1 do
               if v[i]=v[i+1]+1 then inc(rj);
            for i:=1 to s-2 do
               if (v[i]=v[i+1])and(v[i]=v[i+2]-1) then inc(rj);
         end;
     5:  begin
            for i:=1 to s-2 do
               if ((v[i]-v[i+1]=1)or(v[i]-v[i+1]=0))and(v[i]=v[i+2]) then inc(rj);
            for i:=1 to s-1 do
               if abs(v[i]-v[i+1])=1 then inc(rj);
         end;
     6:  begin
            for i:=1 to s-2 do
               if (v[i+1]=v[i+2])and((v[i+1]-v[i]=1)or(v[i+1]-v[i]=0)) then inc(rj);
            for i:=1 to s-1 do
               if (v[i]=v[i+1])or(v[i]=v[i+1]+2) then inc(rj);
         end;
   end;
   writeln(rj);
end.
