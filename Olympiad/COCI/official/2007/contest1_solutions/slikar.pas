
(*
  Croatian Open Competition in Informatics 2006/2007
  Contest 1 - Task SLIKAR
  Programming language Pascal
*)

program slikar;

var
   i, j, r, s   : integer;
   stanje, novo : array[0..51, 0..51] of char;
   rj           : integer;
   gotovo       : boolean;

begin
   readln(r, s);
   for i:=1 to r do begin
      for j:=1 to s do
         read(stanje[i, j]);
      readln;
      stanje[i, 0]   := 'X';
      stanje[i, s+1] := 'X';
   end;

   for j:=0 to s+1 do begin
      stanje[0, j]   := 'X';
      stanje[r+1, j] := 'X';
   end;

   rj := 0;
   repeat
      rj := rj+1;

      novo := stanje;
      (* Oznaci polja na koja slikar moze doci *)
      for i:=1 to r do
         for j:=1 to s do
            if ( stanje[i, j-1] = 'S' ) or
               ( stanje[i, j+1] = 'S' ) or
               ( stanje[i-1, j] = 'S' ) or
               ( stanje[i+1, j] = 'S' ) then
            begin
               if stanje[i, j] = '.' then
                  novo[i, j] := 'S'
               else if stanje[i, j] = 'D' then begin
                  writeln( rj );
                  exit;
               end;
            end;
      stanje := novo;

      (* Prosiri poplavu *)
      for i:=1 to r do
         for j:=1 to s do
            if ( stanje[i, j-1] = '*' ) or
               ( stanje[i, j+1] = '*' ) or
               ( stanje[i-1, j] = '*' ) or
               ( stanje[i+1, j] = '*' ) then
            begin
               if stanje[i, j] in ['.', 'S'] then
                  novo[i, j] := '*';
            end;
      stanje := novo;

      (* Gotovi smo ako nema polja na kojem slikar moze biti (sve
         poplavljeno) *)
      gotovo := true;
      for i:=1 to r do
         for j:=1 to s do
            if stanje[i, j] = 'S' then
               gotovo := false;
   until gotovo;

   (* Pokoj im dusi *)
   writeln('KAKTUS');
end.
