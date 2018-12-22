program princeza;

uses classes;

const MAXLOPOC = 100000;
const MAXSKOK = 100000;

type
   ppoint = ^point;
   point = record
      x, y : longint;
      d1, d2 : longint;
      skok : array[0..3] of ppoint;
   end;

function cmp_d1( A, B : pointer ) : longint;
var
   aa, bb : ppoint;
begin
   aa := A; bb := B;
   if aa^.d1 <> bb^.d1 then cmp_d1 := aa^.d1 - bb^.d1
                       else cmp_d1 := aa^.d2 - bb^.d2;
end;

function cmp_d2( A, B : pointer ) : longint;
var
   aa, bb : ppoint;
begin
   aa := A; bb := B;
   if aa^.d2 <> bb^.d2 then cmp_d2 := aa^.d2 - bb^.d2
                       else cmp_d2 := aa^.d1 - bb^.d1;
end;

var
   n, k : longint;
   i, j : longint;
   barica, next : ppoint;
   A, B : ppoint;

   lopoci : array[1..MAXLOPOC] of point;
   sorted_d1, sorted_d2 : TList;
   skokovi : array[1..MAXSKOK] of char;

begin
   readln( n, k );
   for i := 1 to k do read( skokovi[i] );
   readln;

   sorted_d1 := TList.Create;
   sorted_d2 := TList.Create;

   for i := 1 to n do begin
      readln( lopoci[i].x, lopoci[i].y );
      lopoci[i].d1 := lopoci[i].x + lopoci[i].y;
      lopoci[i].d2 := lopoci[i].x - lopoci[i].y;

      for j := 0 to 3 do lopoci[i].skok[j] := NIL;

      sorted_d1.add( @lopoci[i] );
      sorted_d2.add( @lopoci[i] );
   end;

   sorted_d1.Sort( @cmp_d1 );
   sorted_d2.Sort( @cmp_d2 );

   for i := 2 to n do begin
      A := sorted_d1[i-2];
      B := sorted_d1[i-1];
      if A^.d1 = B^.d1 then begin
         A^.skok[1] := B;
         B^.skok[2] := A;
      end;
   end;
   for i := 2 to n do begin
      A := sorted_d2[i-2];
      B := sorted_d2[i-1];
      if A^.d2 = B^.d2 then begin
         A^.skok[0] := B;
         B^.skok[3] := A;
      end;
   end;

   barica := @lopoci[1];
   for i := 1 to K do begin
      next := barica^.skok[ord(skokovi[i])-65];
      if next = NIL then continue;

      for j := 0 to 3 do
         if barica^.skok[j] <> NIL then
            barica^.skok[j]^.skok[3-j] := barica^.skok[3-j];
      barica := next;
   end;

   writeln( barica^.x, ' ', barica^.y );
end.
