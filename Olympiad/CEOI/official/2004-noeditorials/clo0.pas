{************************************************************************
*                                                                       *
*                                  CEOI 2004                            *
*                                                                       *
*   Sample solution:     Clouds                                         *
*   File:                CLO.PAS                                        *
*   Author:              PIOTR STANCZYK                                 *
************************************************************************}

{$R-}
const MAX_CLOUDS = 1000;
const CLOUD_SIZE = 1000;
var high_part, low_part  : qword;

TYPE point = RECORD
    x, y : longint;
END;


TYPE superlong = RECORD
    high, low : qword;
END;

TYPE crossing = RECORD
  posh, posl : int64;  { Relative position of the point }
  cloud : integer;     { Owner of the point             }
  kind  : byte;        { Type of intersection           }
END;

VAR
    clouds : integer;
    vel_x, vel_y : longint; { Velocity vector }
    cr_nr  : longint;
    cr : ARRAY [0..MAX_CLOUDS * CLOUD_SIZE] of crossing; { Vector of intersection points            }


function multiply(v1, v2 : qword) : superlong;
{ Multiplies two qwords and returns the result as superlong.
  This function assumes that multiplied values are at most 62-bits long     }
VAR
    x : qword;
BEGIN
  x := (v1 AND low_part) * (v2 shr 31) + (v1 shr 31) * (v2 AND low_part);
  multiply.low := (v1 AND low_part) * (v2 AND low_part);
  multiply.high := (v1 shr 31) * (v2 shr 31);
  multiply.low  := multiply.low + ((x AND low_part) shl 31);
  multiply.high := multiply.high + (x shr 31) + (multiply.low shr 62);
  multiply.low  := multiply.low AND high_part;
END;


function compare(a, b : crossing) : shortint;
{ Compares a position of two given crossing points }
VAR
    a1, b1 : superlong;
BEGIN
  a1 := multiply(a.posh, b.posl);
  b1 := multiply(a.posl, b.posh);
  if a1.high = b1.high then
  begin
    if a1.low = b1.low then compare := 0 else
    if a1.low < b1.low then compare := -1 else
    compare := 1;
  end else
  if a1.high < b1.high then compare := -1 else
  compare := 1;
END;

function side(a : point) : shortint;
{ Determines the location of a given point against velocity vector }
VAR
    x, wx, wy : int64;
        kx, ky : int64;
BEGIN
  wx := a.x;
  wy := a.y;
  kx := vel_x;
  ky := vel_y;
  x := kx * wy - ky * wx;
  if x = 0 then side := 0 else
  if x > 0  then side := 1 else
  side := -1;
END;

procedure Add_intersection(a, b : point; cloud : integer; kind : byte);
{ Examines an intersection point between velocity vector and (a,b) segment }
VAR
    c : crossing;
    wx, wy : int64;
BEGIN
  { The relative distance of the crossing point from the laser beam (point [0,0])
    is defined as c.posh/c.posl. In order to keep arithmetic precision we have
    to represent this value as a fraction }
  wx := a.x;
  wy := a.y;
  c.posh := b.y * wx - b.x * wy;
  c.posl := vel_y * (wx - b.x) - vel_x * (wy - b.y);
  if (c.posh < 0) AND (c.posl < 0) then
  begin
    c.posh := -c.posh;
    c.posl := -c.posl;
  end else
  if (c.posh < 0) OR (c.posl < 0) then exit;
  c.cloud := cloud;
  c.kind := kind;
  cr[cr_nr] := c;
  inc(cr_nr);
END;

procedure Read_Data;
{ Reads data and finds all intersection points }
VAR
    kind : byte;
    size, x, y, beg : integer;
    pos, f_side, l_side : integer;
    cloud  : ARRAY [0..CLOUD_SIZE-1] of point;
BEGIN
  Readln(clouds, vel_x, vel_y);
  vel_x := -vel_x;
  vel_y := -vel_y;

  for x := 0 to clouds - 1 do
  begin
    Read(size);
    for y := 0 to size - 1 do
      Read(cloud[y].x, cloud[y].y);
    pos := 0;
    while side(cloud[pos]) = 0 do inc(pos); { Finds a vertex not located above velocity vector }
    f_side := side(cloud[pos]);
    y := 1;
    while y <= size do
    begin
      l_side := f_side;
      f_side := side(cloud[(pos + y) MOD size]);
      if l_side * f_side = 1 then
        inc(y); { Vertices are located on the same side -> no intersection }
      if l_side * f_side = -1 then
      begin { Vertices are located on a different sides -> intersection found }
        Add_intersection(cloud[(size + pos + y - 1) MOD size], cloud[(pos + y) MOD size], x, 0);
        inc(y);
      end;
      if l_side * f_side = 0 then
      begin { Vertex is located directly above velocity vector -> further verification }
        beg := pos + y;
        while side(cloud[(pos + y) MOD size]) = 0 do inc(y);
        f_side := side(cloud[(pos + y) MOD size]);
        if pos + y <> beg + 1 then
        begin
          if l_side = f_side then kind := 1 else kind := 2;
          Add_intersection(cloud[(pos + y) MOD size], cloud[(pos + y - 1) MOD size], x, kind);
          Add_intersection(cloud[(size + beg - 1) MOD size], cloud[beg MOD size], x, 1);
        end else
        begin
          if l_side = f_side then kind := 3 else kind := 0;
          Add_intersection(cloud[(pos + y) MOD size], cloud[(size + pos + y - 1) MOD size], x, kind);
        end;
      end;
    end;
  end;
END;


function Count_Result : longint;
{ Searches the sorted list of intersection points and calculates the result }
VAR
  inside  : ARRAY[0..MAX_CLOUDS - 1] of boolean; { is a cloud directly above the laser beam }
  on_edge : ARRAY[0..MAX_CLOUDS - 1] of boolean; { is an edge of a cloud directly above the laser beam }
  am_edges, am_inside, result, x : longint;
  location : crossing;
BEGIN
  am_inside := 0;
  am_edges := 0;
  result := 0;
  location.posh := 0; { Sets the actual location to the    }
  location.posl := 1; { initial position of the laser beam }

  for x := 0 to clouds - 1 do
  begin
    inside[x] := false;
    on_edge[x] := false;
  end;

  for x := 0 to cr_nr - 1 do
  begin
    if (am_inside = 0) AND (am_edges = 0) AND (compare(location, cr[x]) <> 0) then
      inc(result);

    location := cr[x];

    if (location.kind = 1) OR (location.kind = 2) then { Intersection changes the state of an edge }
    begin
      on_edge[location.cloud] := NOT on_edge[location.cloud];
      if on_edge[location.cloud] then inc(am_edges) else dec(am_edges);
    end;

    if (location.kind = 0) OR (location.kind = 2) then { Intersection changes the state of a cloud }
    begin
      inside[location.cloud] := NOT inside[location.cloud];
      if inside[location.cloud] then inc(am_inside) else dec(am_inside);
    end;
  end;
  Count_Result := result;
END;

procedure Rotate(b, e : longint);
VAR
  tr       : crossing;
  x, swap : longint;
BEGIN
  for x := b to e do
  begin
    swap := random(e - b + 1) + b;
    tr := cr[x];
    cr[x] := cr[swap];
    cr[swap] := tr;
  end;
END;

function partition(b, e : longint) : longint;
VAR
  x, tr : crossing;
BEGIN
  x := cr[b];
  dec(b);
  inc(e);
  while true do
  begin
    repeat dec(e); until compare(x, cr[e]) <> -1;
    repeat inc(b); until compare(x, cr[b]) <> 1;
    if b < e then
    begin
      tr := cr[e];
      cr[e] := cr[b];
      cr[b] := tr;
    end else
    begin
      partition := e;
      exit;
    end;
  end;
END;

procedure quicksort(b, e : longint);
VAR
  el : longint;
BEGIN
  if b < e then
  begin
    el := partition(b, e);
    quicksort(b, el);
    quicksort(el + 1, e);
  end;
END;

var i,j:longint;
	tmp:crossing;
BEGIN
  low_part := 2147483647;                 { 2^31 - 1 }
  high_part := low_part * (low_part + 2); { 2^62 - 1 }
  Randomize();
  cr_nr := 0;
  Read_Data();
  Rotate(0, cr_nr - 1);
  {for i:=1 to cr_nr - 1 do 
  begin
    j:=random(i);
	tmp:=cr[i];
	cr[i]:=cr[j];
	cr[j]:=tmp;
  end;}
  quicksort(0, cr_nr - 1);
  Writeln(Count_Result());
END.
