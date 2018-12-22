program avogadro;

const MAX = 100000;

type
   nodeptr = ^node;
   node = record
      data : longint;
      next : nodeptr;
   end;

var
   n : longint;
   a : array[1..3, 1..MAX] of longint;
   erased : array[1..MAX] of boolean;

   columns : array[1..MAX] of nodeptr;
   freq : array[1..MAX,1..3] of longint;

   i, r, c, number, ret : longint;
   it : nodeptr;

   jobsTop : longint;
   jobs : array[1..3*MAX] of longint;

procedure push( x : longint );
begin
   inc( jobsTop );
   jobs[jobsTop] := x;
end;
function pop() : longint;
begin
   pop := jobs[jobsTop];
   dec( jobsTop );
end;

begin
   readln( n );
   for i := 1 to n do begin
      columns[i] := NIL;
      erased[i] := false;
      for r := 1 to 3 do freq[i][r] := 0;
   end;

   for r := 1 to 3 do begin
      for c := 1 to n do begin
         read( a[r,c] );

         new( it );
         it^.data := c;
         it^.next := columns[a[r,c]];
         columns[a[r,c]] := it;

         inc( freq[a[r][c],r] );
      end;
      readln;
   end;

   jobsTop := 0;
   for i := 1 to n do
      if (freq[i,2] = 0) or (freq[i,3] = 0) then
         push( i );

   ret := 0;
   while jobsTop > 0 do begin
      number := pop();

      it := columns[number];
      while it <> NIL do begin
         if erased[it^.data] = false then begin
            erased[it^.data] := true;
            inc( ret );

            for r := 1 to 3 do begin
               dec( freq[a[r,it^.data],r] );
               if freq[a[r,it^.data],r] = 0 then
                  push( a[r,it^.data] );
            end;
         end;
         it := it^.next;
      end;
   end;
   writeln( ret );
end.
