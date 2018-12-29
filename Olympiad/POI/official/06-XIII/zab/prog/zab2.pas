(*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: ZAB (¯aby)                                     *
 *   Plik:                zab2.pas                                       *
 *   Autor:               Jakub Pawlewicz                                *
 *   Opis:                Faza szukania odleg³o¶ci: Algorytm wêdrowców   *
 *                        z u¿yciem kube³ków.                            *
 *                        Faza szukania szeroko¶ci: BFS + binary search  *
 *                                                                       *
 *************************************************************************)

type TPoint =
   record
      x, y : Longint;
   end;

function left(p        : TPoint) : TPoint;
begin
   left.x := p.x - 1;
   left.y := p.y;
end;

function right(p : TPoint) : TPoint;
begin
   right.x := p.x + 1;
   right.y := p.y;
end;

function down(p        : TPoint) : TPoint;
begin
   down.x := p.x;
   down.y := p.y - 1;
end;

function up(p : TPoint) : TPoint;
begin
   up.x := p.x;
   up.y := p.y + 1;
end;

procedure ReadPoint(var p : TPoint);
begin
   Read(p.x, p.y);
end;

function dist(a, b : TPoint) : Longint;
begin
   dist := sqr(a.x - b.x) + sqr(a.y - b.y);
end;

const
   MAX_LEN    = 1000;
   MAX_POINTS = MAX_LEN * MAX_LEN;

var
   size              : TPoint;
   s, e              : TPoint;
   electrodes        : array[1..MAX_POINTS] of TPoint;
   n                 : Longint;
   x,y               : Longint;
   dist_arr          : array[0..MAX_LEN+1,0..MAX_LEN+1] of Longint;

procedure ReadElectrodes;
var
   i : Longint;
begin
   for i := 1 to n do
      ReadPoint(electrodes[i]);
end;

function DistToElectrodes(p : TPoint) : Longint;
var
   i, d        : Longint;
begin
   DistToElectrodes := MaxLongint;
   for i := 1 to n do
   begin
      d := dist(p, electrodes[i]);
      if d < DistToElectrodes then
         DistToElectrodes := d;
   end;
end;

type
   TType       = (PLANE, QUARTER, HALFLINE);
   TDir        = (DRIGHT, DUP, DLEFT, DDOWN);
   TWalker     =
   record
      t      : TType;
      dir    : TDir;
      pos    : TPoint;
      source : TPoint;
   end;
   PWalkerList = ^TWalkerList;
   TWalkerList =
   record
      walker : TWalker;
      next   : PWalkerList;
   end;

function PrevDir(d : TDir) : TDir;
begin
   PrevDir := TDir((Ord(d) + 3) and 3);
end;

function MovePoint(p : TPoint; d : TDir) : TPoint;
begin
   case d of
     DRIGHT : MovePoint := right(p);
     DUP    : MovePoint := up(p);
     DLEFT  : MovePoint := left(p);
     DDOWN  : MovePoint := down(p);
   end;
end;

function GoodDirection(e : TDir; m, n : TPoint) : Boolean;
begin
   case e of
     DRIGHT : GoodDirection := n.x < m.x;
     DUP    : GoodDirection := n.y < m.y;
     DLEFT  : GoodDirection := m.x < n.x;
     DDOWN  : GoodDirection := m.y < n.y;
   end;
end;

function CreateWalker(t : TType; dir : TDir; pos, source : TPoint) : TWalker;
begin
   CreateWalker.t := t;
   CreateWalker.dir := dir;
   CreateWalker.pos := pos;
   CreateWalker.source := source;
end;

var
   walker_bucket     : array[0..2 * MAX_POINTS] of PWalkerList;
   walker_cur_bucket : Longint;
   walkers_count     : Longint;
   source            : array[1..MAX_LEN,1..MAX_LEN] of TPoint;

procedure AddWalker(walker : TWalker; d : Longint);
var
   l : PWalkerList;
begin
   New(l);
   l^.walker := walker;
   l^.next := walker_bucket[d];
   walker_bucket[d] := l;
   inc(walkers_count);
end;

function DelMinWalker : TWalker;
var
   l          : PWalkerList;
begin
   while walker_bucket[walker_cur_bucket] = nil do
      inc(walker_cur_bucket);
   l := walker_bucket[walker_cur_bucket];
   DelMinWalker := l^.walker;
   walker_bucket[walker_cur_bucket] := l^.next;
   Dispose(l);
   dec(walkers_count);
end;

procedure MovePlaneAndReduceDist(walker        : TWalker);
begin
   with walker.pos do
      if dist_arr[x, y] > 0 then
      begin
         dist_arr[x, y] := 1;
         source[x, y] := walker.source;
         AddWalker(walker, 1);
      end;
end;

procedure TryMovePlane(walker : TWalker);
var
   d : TDir;
begin
   with walker do
      for d := DRIGHT to DDOWN do
         MovePlaneAndReduceDist(CreateWalker(
                                QUARTER, d, MovePoint(pos, d), source));
end;

function TryMoveAndReduceDist(walker      : TWalker; destp : TPoint;
                              walker_dist : Longint) : Boolean;
begin
   if walker_dist < dist_arr[destp.x, destp.y] then
   begin
      dist_arr[destp.x, destp.y] := walker_dist;
      source[destp.x, destp.y] := walker.source;
      AddWalker(walker, walker_dist);
      TryMoveAndReduceDist := true;
   end
   else
      TryMoveAndReduceDist := false;
end;

function TryForcedMove(e           : TDir; walker : TWalker; destp : TPoint;
                       walker_dist : Longint) : Boolean;
begin
   if GoodDirection(e, walker.source, source[destp.x, destp.y]) then
   begin
      AddWalker(walker, walker_dist);
      TryForcedMove := true;
   end
   else
      TryForcedMove := false;
end;

procedure TryMoveHalfline(walker : TWalker);
var
   e0 : TDir;
   w0 : TWalker;
   d0 : Longint;
begin
   e0 := walker.dir;
   w0 := CreateWalker(HALFLINE, e0, MovePoint(walker.pos, e0), walker.source);
   d0 := dist(w0.pos, w0.source);
   if not TryMoveAndReduceDist(w0, w0.pos, d0) and
      (dist_arr[w0.pos.x, w0.pos.y] > 0) then
      TryForcedMove(e0, w0, w0.pos, d0);
end;

procedure TryMoveQuarter(walker        : TWalker);
var
   e0, e1     : TDir;
   w0, w1     : TWalker;
   d0, d1     : Longint;
   w1_created : Boolean;
begin
   e1 := walker.dir;
   w1 := CreateWalker(QUARTER, e1, MovePoint(walker.pos, e1), walker.source);
   d1 := dist(w1.pos, w1.source);
   w1_created := true;

   if dist_arr[w1.pos.x, w1.pos.y] < 0 then
   begin
      TryMoveHalfline(CreateWalker(
                      walker.t, PrevDir(e1), walker.pos, walker.source));
      Exit;
   end;

   if not TryMoveAndReduceDist(w1, w1.pos, d1) then
      if not TryForcedMove(e1, w1, w1.pos, d1) then
         w1_created := false;

   e0 := PrevDir(e1);
   if w1_created then
      w0 :=
      CreateWalker(HALFLINE, e0, MovePoint(walker.pos, e0), walker.source)
   else
      w0 :=
      CreateWalker(QUARTER, e1, MovePoint(walker.pos, e0), walker.source);
   d0 := dist(w0.pos, w0.source);
   if not TryMoveAndReduceDist(w0, w0.pos, d0) and
      (dist_arr[w0.pos.x, w0.pos.y] > 0) then
      if not TryForcedMove(e0, w0, w0.pos, d0) then
         if not w1_created then
            TryForcedMove(e1, w0, w0.pos, d0);
end;

procedure TryMove(walker : TWalker);
begin
   case walker.t of
     PLANE    : TryMovePlane(walker);
     QUARTER  : TryMoveQuarter(walker);
     HALFLINE : TryMoveHalfline(walker);
   end;
end;

procedure ComputeDistArr;
var
   p : TPoint;
   i : Longint;
   x : Longint;
   y : Longint;
begin
   for x := 0 to size.x + 1 do
      for y := 0 to size.y + 1 do
         if (x = 0) or (x > size.x) or (y = 0) or (y > size.y) then
            dist_arr[x, y] := -1
         else
            dist_arr[x, y] := MaxLongint;

   for i := 0 to sqr(size.x) + sqr(size.y) do
      walker_bucket[i] := nil;
   walker_cur_bucket := 0;

   walkers_count := 0;
   for i := 1 to n do
   begin
      p := electrodes[i];
      AddWalker(CreateWalker(PLANE, TDir(0), p, p), 0);
      dist_arr[p.x, p.y] := 0;
      source[p.x, p.y] := p;
   end;

   while walkers_count > 0 do
      TryMove(DelMinWalker);
end;

var
   queue                  : array[1..MAX_POINTS] of TPoint;
   queue_start, queue_end : Longint;
   queued                 : array[1..MAX_LEN,1..MAX_LEN] of Boolean;

function TryFindPath(width : Longint) : Boolean;
var
   p : TPoint;

procedure TryVisit(p : TPoint);
begin
   if (dist_arr[p.x, p.y] >= width) and not queued[p.x, p.y] then
   begin
      queued[p.x, p.y] := true;
      inc(queue_end);
      queue[queue_end] := p;
   end;
end;

begin
   for x := 1 to size.x do
      for y := 1 to size.y do
         queued[x, y] := false;
   queue_start := 1;
   queue_end := 1;
   queue[1] := s;
   queued[s.x, s.y] := true;

   TryFindPath := false;
   while queue_start <= queue_end do
   begin
      if queued[e.x, e.y] then
      begin
         TryFindPath := true;
         break;
      end;
      p := queue[queue_start];
      inc(queue_start);
      if p.x > 1 then
         TryVisit(left(p));
      if p.x < size.x then
         TryVisit(right(p));
      if p.y > 1 then
         TryVisit(down(p));
      if p.y < size.y then
         TryVisit(up(p));
   end;
end;

function ComputeWidth : Longint;
var
   l, p, m : Longint;
begin
   p := dist_arr[s.x, s.y] + 1;
   l := 0;
   while l + 1 < p do
   begin
      m := (l + p) div 2;
      if TryFindPath(m) then
         l := m
      else
         p := m;
   end;
   ComputeWidth := l;
end;

begin
   ReadPoint(size);
   ReadPoint(s);
   ReadPoint(e);
   Read(n);
   ReadElectrodes;
   ComputeDistArr;
   Writeln(ComputeWidth);
end.
