program skakavac_prog;

const inf = 1000000000;

function abs(x : longint) : longint; begin if x < 0 then abs := -x else abs := x; end;
function max(a, b : longint) : longint; begin if a > b then max := a else max := b; end;

type
   pskakavac = ^skakavac;
   skakavac = 
   record
      r, c    : integer;
      val, dp : longint;
   end;

function cmp(a, b : skakavac) : longint;
begin
   if a.val > b.val then cmp := -1
   else if a.val < b.val then cmp := 1
   else cmp := 0;
end;

type best4 = object
   best : array[0..3] of pskakavac;
   procedure update(S : pskakavac);
   function query(r, c : longint) : longint;
end;

procedure best4.update(S : pskakavac);
var i : longint;
begin
   for i:=3 downto 0 do begin
      if S^.dp <= best[i]^.dp then break;

      if i+1 < 4 then best[i+1] := best[i];
      best[i] := S;
   end;
end;
   
function best4.query(r, c : longint) : longint;
var i : longint;
begin
   query := -inf;
   for i:=0 to 3 do begin
      if (abs(r-best[i]^.r) <= 1) and (abs(c-best[i]^.c) <= 1) then continue;
      query := best[i]^.dp;
      break;
   end;
end;

procedure swap(var a, b : skakavac); var t : skakavac; begin t := a; a := b; b := t; end;

procedure qsort(var arr : array of skakavac; l, r: longint);
var x, y : longint;
    mid  : skakavac;
begin
    if r-l < 2 then exit;
    if r-l = 2 then begin
        if cmp(arr[l+1], arr[l]) < 0 then swap(arr[l], arr[l+1]);
        exit;
    end;

    mid := arr[(l+r) div 2];
    y := l;

    for x := l to r-1 do  (* sve strogo manje stavi na pocetak *)
        if cmp(arr[x], mid) < 0 then begin
            swap(arr[x], arr[y]);
            inc(y);
        end;

    qsort(arr, l, y); (* sortiraj sve strogo manje *)

    for x:=y to r-1 do (* sve jednake stavi poslije ovih manjih *)
        if cmp(arr[x], mid) = 0 then begin
            swap(arr[x], arr[y]);
            inc(y);
        end;

    qsort(arr, y, r); (* sortiraj sve strogo vece *)
end;

var
   niz       : array[0..1500*1500] of skakavac;
   R, C      : array[0..1500] of best4;
   n, r0, c0 : longint;
   i, j      : longint;
   next, S   : pskakavac;

begin
   read(n, r0, c0); dec(r0); dec(c0);

   next := @niz[0];
   for i:=0 to n-1 do begin
      for j:=0 to n-1 do begin
         next^.r := i;
         next^.c := j;
         next^.dp := 1;
         read(next^.val);
         inc(next);
      end;
   end;

   next^.r := -5;
   next^.c := -5;
   next^.dp := -inf;

   for i:=0 to n-1 do 
      for j:=0 to 3 do begin
         R[i].best[j] := next;
         C[i].best[j] := next;
      end;

   qsort(niz, 0, n*n);

   i := 0;
   while i < n*n do begin
      j := i;
      while (j < n*n) and (niz[j].val = niz[i].val) do begin
         S := @niz[j];

         if S^.r-1 >= 0 then S^.dp := max(S^.dp, 1+R[S^.r-1].query(S^.r, S^.c));
         if S^.c-1 >= 0 then S^.dp := max(S^.dp, 1+C[S^.c-1].query(S^.r, S^.c));
         if S^.r+1 <  n then S^.dp := max(S^.dp, 1+R[S^.r+1].query(S^.r, S^.c));
         if S^.c+1 <  n then S^.dp := max(S^.dp, 1+C[S^.c+1].query(S^.r, S^.c));

         inc(j);
      end;

      j := i;
      while (j < n*n) and (niz[j].val = niz[i].val) do begin
         S := @niz[j];

         R[S^.r].update(S);
         C[S^.c].update(S);

         if (S^.r = r0) and (S^.c = c0) then writeln(S^.dp);
         
         inc(j);
      end;
      
      i := j;
   end;
end.