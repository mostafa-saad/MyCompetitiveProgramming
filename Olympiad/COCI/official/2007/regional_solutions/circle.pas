
(*
  Croatian Regional Competition in Informatics 2007
  Task CIRCLE
  Programming language Pascal
*)

program circle;

const MAXK = 10;

var
   n, k, i, j, l, m : longint;
   krug             : string;
   c                : char;

   stari, novi   : array[1..1 shl MAXK] of string;
   starih, novih : longint;

procedure dodaj(var k : string);
var i, j : longint;
   najmanji, trenutni : string;
begin
   najmanji := k;
   trenutni := k;
   for j:=1 to n do
   begin
      for i:=1 to n do
         trenutni[i]:=k[1+(i+j) mod n];
      trenutni[n+1] := trenutni[1];
      if trenutni<najmanji then najmanji := trenutni;
   end;
   for i:=1 to novih do
      if novi[i]=najmanji then exit;
   inc(novih);
   novi[novih] := najmanji;
end;

begin
   readln(n, k);
   readln(krug);
   krug := krug + krug[1];
   for i:=1 to k do
   begin
      for j:=1 to n do
         if krug[j]<>krug[j+1] then
            krug[j]:='W' else
               krug[j]:='B';
      krug[n+1] := krug[1];
   end;

   novih := 1;
   novi[1]:= krug;

   for i:=1 to k do
   begin
      for j:=1 to novih do stari[j] := novi[j];
      starih := novih;
      novih := 0;
      for j:=1 to starih do
         for m:=1 to 2 do
         begin
            if m = 1 then c := 'W' else c := 'B';
            krug[1] := c;
            for l:=1 to n do
               if stari[j][l]='B' then
                  krug[l+1]:=krug[l]
               else
                  krug[l+1]:=chr(ord('B') + ord('W') - ord(krug[l]));
            if krug[n+1]=krug[1] then dodaj(krug);
         end;
   end;

   writeln(novih);
end.
