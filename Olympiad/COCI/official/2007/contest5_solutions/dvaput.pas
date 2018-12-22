
(*
  Croatian Open Competition in Informatics 2006/2007
  Contest 5 - Task DVAPUT
  Programming language Pascal
*)

program dvaput;

const
   MAXLEN  = 200000;
   MAXHASH = 200003;

type node = record
   hash, key, next : longint;
end;

var
   nnodes         : longint;
   nodes          : array[1..MAXLEN] of node;
   tablica        : array[0..MAXHASH-1] of longint;
   L              : longint;
   str            : array[1..MAXLEN] of char;
   i, lo, hi, mid : longint;

col, ins:longint;

function trazi2(K : longint) : boolean;
var
   hash, sub, i, p, j : longint;
   isti               : boolean;
begin
   if K = 0 then begin
      trazi2 := true;
      exit;
   end;

   while nnodes > 0 do begin
      tablica[ nodes[nnodes].hash ] := -1;
      nnodes := nnodes-1;
   end;

   hash := 0; sub := 1;
   for i:=1 to K do begin
      sub := (26*sub) mod MAXHASH;
      hash := (26*hash + ord(str[i])) mod MAXHASH;
   end;

   sub := MAXHASH - sub;

   for i:=K to L do begin
      p := tablica[hash];
      while p <> -1 do begin
         isti := true;
         for j:=0 to K-1 do
            if str[ nodes[p].key+j ] <> str[ i-K+1+j ] then begin
               isti := false;
               break;
            end;

         if isti then begin
            trazi2 := true;
            exit;
         end;

         p := nodes[p].next;
      end;

      ins := ins+1;
      if tablica[hash] <> -1 then
         col := col+1;
      nnodes := nnodes+1;
      nodes[nnodes].hash := hash;
      nodes[nnodes].key  := i-K+1;
      nodes[nnodes].next := tablica[hash];
      tablica[hash] := nnodes;

      hash := (26*hash + sub*ord(str[i-K+1]) + ord(str[i+1])) mod MAXHASH;
   end;

   trazi2 := false;
end;

begin
   readln(L);
   for i:=1 to L do
      read(str[i]);

   for i:=0 to MAXHASH-1 do
      tablica[i] := -1;

   lo := 0; hi := L-1;
   while lo<hi do begin
      mid := (lo+hi+1) div 2;

      if trazi2(mid) then
         lo := mid
      else
         hi := mid-1;
   end;

   writeln(lo);
end.
