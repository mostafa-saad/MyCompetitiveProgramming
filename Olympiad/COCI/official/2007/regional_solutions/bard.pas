
(*
  Croatian Regional Competition in Informatics 2007
  Task BARD
  Programming language Pascal
*)

program bard;

const
   MAXN = 100;
   MAXV = 50;

var
   n, v, i, j, k          : integer;
   npjesama, veceras, tko : integer;
   zna                    : array[1..MAXN, 1..MAXV] of boolean;
   prisutan               : array[1..MAXN] of boolean;
   pjevase                : array[1..MAXV] of boolean;
   znasve                 : boolean;

begin
   npjesama := 0;
   readln(n);
   readln(v);

   for i:=1 to n do
      for j:=1 to v do
         zna[i, j] := false;

   for i:=1 to v do begin
      for j:=1 to n do
         prisutan[j] := false;
      for j:=1 to npjesama do
         pjevase[j] := false;

      read(veceras);
      for j:=1 to veceras do begin
         read(tko);
         prisutan[tko] := true;
      end;
      readln;

      if prisutan[1] then begin
         npjesama := npjesama + 1;
         pjevase[npjesama] := true;
      end else begin
         for j:=1 to npjesama do
            for k:=1 to n do
               if prisutan[k] and zna[k, j] then
                  pjevase[j] := true;
      end;

      for k:=1 to n do
         for j:=1 to npjesama do
            if prisutan[k] and pjevase[j] then
               zna[k, j] := true;
   end;

   for i:=1 to n do begin
      znasve := true;
      for j:=1 to npjesama do
         if not zna[i, j] then
            znasve := false;
      if znasve then writeln(i);
   end;
end.
