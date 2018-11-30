program portals;
const INF = 10000;
const dr: array [1..4] of Integer = (-1, 0, 1, 0);
const dc: array [1..4] of Integer = (0, 1, 0, -1);
type rec = record rr, cc: Integer; dist, next: Longint; end;
type pair = record rr, cc: Integer; end;
var r, c: Integer;
    a: array [1..1002, 1..1002] of Char;
    startr, startc, endr, endc: Integer;
    disttowall: array [1..1002, 1..1002] of Integer;
    shootcoord: array [1..4, 1..1002, 1..1002] of Integer;
    tt: array [1..1002, 1..1002] of Longint;
    linkedlist: array [1..10000000] of rec;
    nextfortime: array [0..1000000] of Longint;
    q: array [1..2000000] of pair;

procedure readinput;
var i, j: Integer;
begin
  readln(r, c);
  for i := 2 to r+1 do
  begin
    for j := 2 to c+1 do
    begin
      read(a[i, j]);
      if a[i, j] = 'S' then
      begin
        startr := i;
        startc := j;
        a[i, j] := '.';
      end
      else if a[i, j] = 'C' then
      begin
        endr := i;
        endc := j;
        a[i, j] := '.';
      end;
    end;
    readln;
  end;
  r := r + 2;
  c := c + 2;
  for i := 1 to c do
  begin
    a[1, i] := '#';
    a[r, i] := '#';
  end;
  for i := 1 to r do
  begin
    a[i, 1] := '#';
    a[i, c] := '#';
  end;
end;


procedure calcdisttowall;
var
  qs, qe: Longint;
  i, j, k, ni, nj: Integer;
begin
  qs := 1; qe := 1;
  for i := 1 to r do
    for j := 1 to c do
      if a[i, j] = '#' then
      begin
        q[qe].rr := i;
        q[qe].cc := j;
        qe := qe + 1;
        disttowall[i, j] := 0;
      end
      else
        disttowall[i, j] := INF;
  while qs <> qe do
  begin
    i := q[qs].rr;
    j := q[qs].cc;
    qs := qs + 1;
    for k := 1 to 4 do
    begin
      ni := i + dr[k];
      nj := j + dc[k];
      if (1 <= ni) and (ni <= r) and (1 <= nj)
        and (nj <= c) and (disttowall[ni, nj] = INF) then
      begin
        disttowall[ni, nj] := 1 + disttowall[i, j];
        q[qe].rr := ni;
        q[qe].cc := nj;
        qe := qe + 1;
      end;
    end;
  end;
end;


procedure calcshootcoords;
var i, j, ii, ij: Integer;
begin
  for i := 1 to r do
  begin
    for j := 1 to c do
    begin
      { up and left }
      if a[i, j] = '#' then
      begin
        shootcoord[1, i, j] := i;
        shootcoord[4, i, j] := j;
      end
      else
      begin
        shootcoord[1, i, j] := shootcoord[1, i-1, j];
        shootcoord[4, i, j] := shootcoord[4, i, j-1];
      end;
      
      { right and down }
      ii := r - i + 1;
      ij := c - j + 1;
      if a[ii, ij] = '#' then
      begin
        shootcoord[2, ii, ij] := ij;
        shootcoord[3, ii, ij] := ii;
      end
      else
      begin
        shootcoord[2, ii, ij] := shootcoord[2, ii, ij+1];
        shootcoord[3, ii, ij] := shootcoord[3, ii+1, ij];
      end;
    end;
  end;
end;


function wintime: Longint;
var nextrecid: Longint;
  
  procedure improvetime(rr, cc: Integer; newdist: Longint);
  begin
    if tt[rr, cc] <= newdist then exit;
    tt[rr, cc] := newdist;
    linkedlist[nextrecid].rr := rr;
    linkedlist[nextrecid].cc := cc;
    linkedlist[nextrecid].dist := newdist;
    linkedlist[nextrecid].next := nextfortime[newdist];
    nextfortime[newdist] := nextrecid;
    nextrecid := nextrecid + 1;
  end;
  
  procedure process(id: Longint);
  var rr, cc, k, nr, nc: Integer;
    dist: Longint;
  begin
    rr := linkedlist[id].rr;
    cc := linkedlist[id].cc;
    dist := linkedlist[id].dist;
    if dist <> tt[rr, cc] then exit;
    
    for k := 1 to 4 do
    begin
      nr := rr + dr[k];
      nc := cc + dc[k];
      if (1 <= nr) and (nr <= r) and (1 <= nc) and (nc <= c)
        and (a[nr, nc] = '.') then
        improvetime(nr, nc, dist + 1);
    end;
    
    improvetime(shootcoord[1, rr, cc]+1, cc, dist + disttowall[rr, cc]);
    improvetime(shootcoord[3, rr, cc]-1, cc, dist + disttowall[rr, cc]);
    improvetime(rr, shootcoord[2, rr, cc]-1, dist + disttowall[rr, cc]);
    improvetime(rr, shootcoord[4, rr, cc]+1, dist + disttowall[rr, cc]);
  end;

var curtime: Longint;
  i, j: Longint;
begin
  nextrecid := 1;
  for i := 1 to r do
    for j := 1 to c do
      tt[i, j] := 100000000;
  for i := 0 to 1000000 do
    nextfortime[i] := 0;
  tt[startr, startc] := 0;
  linkedlist[nextrecid].rr := startr;
  linkedlist[nextrecid].cc := startc;
  linkedlist[nextrecid].dist := 0;
  linkedlist[nextrecid].next := 0;
  nextfortime[0] := nextrecid;
  nextrecid := nextrecid + 1;
  for curtime := 0 to 1000000 do
  begin
    i := nextfortime[curtime];
    while i <> 0 do
    begin
      if (linkedlist[i].rr = endr) and (linkedlist[i].cc = endc) then
        exit(curtime);
      process(i);
      i := linkedlist[i].next;
    end;
  end;
end;


var i, j: Integer;
begin
  readinput;
  calcdisttowall;
  calcshootcoords;
  writeln(wintime);
end.
