program lubenica;

const MAXN = 20;

var
   N, H, i, j, t, state  : longint;
   next, lastthrown, rep : longint;
   nfriends, friendmask  : array[0..MAXN] of longint;
   when                  : array[0..1 shl MAXN] of longint;
   thrown                : array[0..1 shl MAXN] of int64;
   row                   : string;
   total                 : int64;

begin
   readln(N, H);
   for i:=0 to N-1 do begin
      readln(row);
      for j:=0 to N-1 do begin
         if row[j+1] = '1' then begin
            inc(nfriends[i]);
            friendmask[i] := friendmask[i] or (1 shl j);
         end;
      end;
   end;

   for i:=0 to (1 shl N)-1 do when[i] := -1;

   state := friendmask[0];
   when[state] := 1;
   thrown[state] := nfriends[0];
   total := thrown[state];

   t := 2;
   while t <= H do begin
      next := 0; lastthrown := 0;
      for i:=0 to N-1 do begin
         if state and (1 shl i) <> 0 then begin
            next := next xor friendmask[i];
            lastthrown := lastthrown + nfriends[i];
         end else
            lastthrown := lastthrown + 2*nfriends[i];
      end;
      state := next;
      total := total + lastthrown;

      if when[state] = -1 then begin
         when[state] := t;
         thrown[state] := total;
      end else begin
         rep := (H-t) div (t-when[state]);
         t := t + rep * (t-when[state]);
         total := total + rep * (total-thrown[state]);
         for i:=0 to (1 shl N)-1 do when[i] := -1;
      end;
      inc(t);
   end;
   writeln(total);
end.
