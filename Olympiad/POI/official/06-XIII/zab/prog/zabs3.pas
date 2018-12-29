(*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: ZAB (¯aby)                                     *
 *   Plik:                zabs3.pas                                      *
 *   Autor:               Jakub Pawlewicz                                *
 *   Opis:                Faza szukania odleg³o¶ci: Przegl±danie         *
 *                        wszystkich elektrod.                           *
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
   MAX_LEN          = 1000;
   MAX_POINTS       = MAX_LEN * MAX_LEN;

var
   size              : TPoint;
   s, e              : TPoint;
   electrodes        : array[1..MAX_POINTS] of TPoint;
   n                 : Longint;
   x, y              : Longint;
   dist_arr          : array[1..MAX_LEN,1..MAX_LEN] of Longint;

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

procedure ComputeDistArr;
var
   p   : TPoint;
   x,y : Longint;
begin
   for x := 1 to size.x do
      for y := 1 to size.y do begin
         p.x := x;
	 p.y := y;
         dist_arr[x, y] := DistToElectrodes(p);
      end;
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
