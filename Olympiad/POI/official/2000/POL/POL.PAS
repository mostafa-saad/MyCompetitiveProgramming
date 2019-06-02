{*************************************************************************}
{*                                                                       *}
{*                   VII Olimpiada Informatyczna                         *}
{*                                                                       *}
{*   Rozwi•zanie zadania: PO-ùAMANA                                      *}
{*   Plik:                POL.PAS                                        *}
{*   Autor:               MARCIN MUCHA                                   *}
{*************************************************************************}

const
   fin_name = 'pol.in';
   fout_name = 'pol.out';

   N_MAX = 100;
   POINT_MAX = 2 * N_MAX + 2;{Jeden z punkt¢w (np.B) teæ trzeba pami©taÜ.}
                             {Dodatkowo jeden na straænika.}
   GRID_MAX = 2 * POINT_MAX + 1;{Trzeba teæ uwzgl©dniÜ zewn©trze.}

   NO_PATH = 255;

   NO_LINK = 0;
   LINK_LEFT = 1;  {x--}
   LINK_RIGHT = 2; {x++}
   LINK_DOWN = 4;  {y--}
   LINK_UP = 8;    {y++}
   LINK_ALL = LINK_LEFT OR LINK_RIGHT OR LINK_DOWN OR LINK_UP;


type
   t_grid_elem = record
      links : byte; {Poà•czenia z s•siadami.}
      hor, ver : byte; {Minimalny stopie‰ poàamanej
                        z A o ost. odcinku poz/pion.}
   end;

   t_grid_array = array[1..POINT_MAX] of longint;
   t_point = record x, y : longint end;
   t_segment = record p, q : t_point end;

   t_grid = array[1..GRID_MAX] of t_grid_elem;
   p_grid = ^t_grid;

var
   xs, ys : t_grid_array; {Posortowane tablice wsp¢àrz©dnych x i y.}
   x_no, y_no : word;{Liczba element¢w w tych tablicach.}
   x_grid_size, y_grid_size : word;{Liczba indeks¢w w siatce.}
   n : word;{Liczba odcink¢w.}
   a, b : t_point;
   segs : array[1..N_MAX] of t_segment;{Odcinki.}
   grid : array[1..GRID_MAX] of p_grid;{Siatka.}

procedure quicksort( var arr : t_grid_array; lo, hi: word);

procedure sort( l, r: word);
var
  i, j : word;
  x, y : longint;
begin
  i := l; j := r; x := arr[ ( l + r) div 2];
  repeat
    while arr[i] < x do inc( i);
    while x < arr[j] do dec( j);
    if i <= j then
    begin
      y := arr[i]; arr[i] := arr[j]; arr[j] := y;
      inc( i); dec( j)
    end
  until i > j;
  if l < j then sort( l, j);
  if i < r then sort( i, r)
end;

begin
  sort( lo, hi)
end;


procedure read_data;
var
   fin : text;
   i : word;
begin
   assign( fin, fin_name);
   reset( fin);
   readln( fin, a.x, a.y);
   readln( fin, b.x, b.y);
   readln( fin, n);
   for i := 1 to n do
      with segs[i] do
         readln( fin, p.x, p.y, q.x, q.y);
   close( fin)
end;

function get_ind( var arr : t_grid_array; arr_size : word; x : longint) : word;
{ Znajduje indeks wsp¢àrz©dnej w siatce arr (w tablicy xs albo ys). }
var
   i : word;
begin
   arr[arr_size + 1] := x + 1;
   i := 1;
   while arr[i] < x do inc( i);
   if arr[i] = x then
      get_ind := 2 * i
   else
      get_ind := 2 * i - 1
end;

procedure block( x, y : word);
begin
   grid[x]^[y].links := NO_LINK;
   grid[x - 1]^[y].links := grid[x - 1]^[y].links AND ( NOT LINK_RIGHT);
   grid[x + 1]^[y].links := grid[x + 1]^[y].links AND ( NOT LINK_LEFT);
   grid[x]^[y - 1].links := grid[x]^[y - 1].links AND ( NOT LINK_UP);
   grid[x]^[y + 1].links := grid[x]^[y + 1].links AND ( NOT LINK_DOWN)
end;

procedure swap( var x, y : word);
var
   t : word;
begin
   t := x;
   x := y;
   y := t
end;

procedure preprocess;
var
   i, j : word;
   x1, x2, y1, y2, x, y : word;
begin
   {Inicjacja tablic punkt¢w.}

   for i := 1 to n do
      begin
         xs[2 * i - 1] := segs[i].p.x;
         xs[2 * i] := segs[i].q.x;
         ys[2 * i - 1] := segs[i].p.y;
         ys[2 * i] := segs[i].q.y
      end;
   xs[2 * n + 1] := b.x;
   ys[2 * n + 1] := b.y;

   quicksort( xs, 1, 2 * n + 1);
   quicksort( ys, 1, 2 * n + 1);

   {Usuwanie duplikat¢w.}

   i := 1; j := 2;
   while ( j <= 2 * n + 1) do
      begin
         if xs[i] <> xs[j] then
            begin
               inc( i);
               xs[i] := xs[j]
            end;
         inc( j)
      end;
   x_no := i;

   i := 1; j := 2;
   while ( j <= 2 * n + 1) do
      begin
         if ys[i] <> ys[j] then
            begin
               inc( i);
               ys[i] := ys[j]
            end;
         inc( j)
      end;
   y_no := i;

   {Przydzielanie pami©ci na siatk©.}

   x_grid_size := 2 * x_no + 1;
   y_grid_size := 2 * y_no + 1;
   for i := 1 to x_grid_size do
      getmem( grid[i], sizeof( t_grid_elem) * y_grid_size);

   {Inicjacja siatki.}

   for i := 1 to x_grid_size do
      for j := 1 to y_grid_size do
         begin
            grid[i]^[j].links := LINK_ALL;
            grid[i]^[j].hor := NO_PATH;
            grid[i]^[j].ver := NO_PATH
         end;

   for i := 1 to x_grid_size do
      begin
         grid[i]^[1].links := LINK_ALL AND ( NOT LINK_DOWN);
         grid[i]^[y_grid_size].links := LINK_ALL AND ( NOT LINK_UP)
      end;

   for i := 1 to y_grid_size do
      begin
         grid[1]^[i].links := grid[1]^[i].links AND ( NOT LINK_LEFT);
         grid[x_grid_size]^[i].links := grid[x_grid_size]^[i].links AND ( NOT LINK_RIGHT)
      end;

   {Dopuszczamy tylko àamane o wierzchoàkach caàkowitych.}

   for i := 2 to x_grid_size - 1 do
      if odd( i) and ( xs[(i + 1) div 2] - xs[i div 2] = 1) then
         for j := 1 to y_grid_size do
            grid[i]^[j].links := grid[i]^[j].links AND ( NOT LINK_UP) AND ( NOT LINK_DOWN);

   for j := 2 to y_grid_size - 1 do
      if odd( j) and ( ys[(j + 1) div 2] - ys[j div 2] = 1) then
         for i := 1 to x_grid_size do
            grid[i]^[j].links := grid[i]^[j].links AND ( NOT LINK_LEFT) AND ( NOT LINK_RIGHT);

   {Umieszczanie odcink¢w w siatce.}

   for i := 1 to n do
      begin
         x1 := get_ind( xs, x_no, segs[i].p.x);
         y1 := get_ind( ys, y_no, segs[i].p.y);
         x2 := get_ind( xs, x_no, segs[i].q.x);
         y2 := get_ind( ys, y_no, segs[i].q.y);
         if x1 > x2 then swap( x1, x2);
         if y1 > y2 then swap( y1, y2);
         for x := x1 to x2 do
            for y := y1 to y2 do
               block( x, y)
      end
end;

const
   DIR_HOR = 0;
   DIR_VER = 1;

type
   p_queue_elem = ^t_queue_elem;
   t_queue_elem = record
      x, y : word;
      dir : byte;
      next : p_queue_elem
   end;

var
   q_head, q_tail : p_queue_elem;

procedure q_init;
begin
   q_head := nil; q_tail := nil
end;

procedure q_put( x, y : word; d : byte);
var
   p : p_queue_elem;
begin
   new( p);
   p^.x := x; p^.y := y; p^.dir := d; p^.next := nil;
   if q_head = nil then
      begin q_head := p; q_tail := p end
   else
      begin q_tail^.next := p; q_tail := p end
end;

procedure q_get( var x, y : word; var d : byte);
var
   p : p_queue_elem;
begin
   x := q_head^.x; y := q_head^.y; d := q_head^.dir;
   p := q_head^.next;
   dispose( q_head);
   q_head := p;
   if p = nil then
      q_tail := nil
end;

function q_empty : boolean;
begin
   q_empty := ( q_head = nil);
end;

procedure q_get_all;
var
   p : p_queue_elem;
begin
   while q_head <> nil do
      begin
         p := q_head^.next;
         dispose( q_head);
         q_head := p
      end;
   q_tail := nil;
end;

procedure BFS;
var
   fout : text;
   x, y : word;
   x1, y1 : word;
   d : byte;
   target_x, target_y : word;
   deg : byte;
begin
   target_x := get_ind( xs, x_no, b.x); target_y := get_ind( ys, y_no, b.y);
   x := get_ind( xs, x_no, a.x); y := get_ind( ys, y_no, a.y);
   grid[x]^[y].hor := 0;
   grid[x]^[y].ver := 0;
   q_init;
   q_put( x, y, DIR_HOR);
   q_put( x, y, DIR_VER);

   repeat
      q_get( x, y, d);
      if ( d = DIR_HOR) then
         begin
            deg := grid[x]^[y].hor;
            if ( grid[x]^[y].ver > deg + 1) then
               grid[x]^[y].ver := deg + 1;
            x1 := x; y1 := y;
            while ( y1 > 1) and
                  ( grid[x1]^[y1].links AND LINK_DOWN > 0) and
                  ( grid[x1]^[y1-1].ver > deg + 1) do
               begin
                  dec( y1);
                  grid[x1]^[y1].ver := deg + 1;
                  q_put( x1, y1, DIR_VER)
               end;
            x1 := x; y1 := y;
            while ( y1 < y_grid_size) and
                  ( grid[x1]^[y1].links AND LINK_UP > 0) and
                  ( grid[x1]^[y1+1].ver > deg + 1) do
               begin
                  inc( y1);
                  grid[x1]^[y1].ver := deg + 1;
                  q_put( x1, y1, DIR_VER)
               end
         end
      else
         begin
            deg := grid[x]^[y].ver;
            if ( grid[x]^[y].hor > deg + 1) then
               grid[x]^[y].hor := deg + 1;
            x1 := x; y1 := y;
            while ( x1 > 1) and
                  ( grid[x1]^[y1].links AND LINK_LEFT > 0) and
                  ( grid[x1-1]^[y1].hor > deg + 1) do
               begin
                  dec( x1);
                  grid[x1]^[y1].hor := deg + 1;
                  q_put( x1, y1, DIR_HOR)
               end;
            x1 := x; y1 := y;
            while ( x1 < x_grid_size) and
                  ( grid[x1]^[y1].links AND LINK_RIGHT > 0) and
                  ( grid[x1+1]^[y1].hor > deg + 1) do
               begin
                  inc( x1);
                  grid[x1]^[y1].hor := deg + 1;
                  q_put( x1, y1, DIR_HOR)
               end
         end
   until q_empty or ( ( x = target_x) and ( y = target_y));
   q_get_all;

   assign( fout, fout_name);
   rewrite( fout);
   with grid[target_x]^[target_y] do
      if ( hor = NO_PATH) and ( ver = NO_PATH) then
         writeln( fout, 'BRAK')
   else if hor < ver then
      writeln( fout, hor)
   else
      writeln( fout, ver);
   close( fout)
end;

procedure clean_up;
var
   i : word;
begin
   for i := 1 to x_grid_size do
      freemem( grid[i], sizeof( t_grid_elem) * y_grid_size)
end;


begin
   read_data;
   preprocess;
   BFS;
   clean_up;
end.