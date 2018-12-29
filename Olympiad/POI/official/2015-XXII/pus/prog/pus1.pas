(******************************************************************************
 *                                                                            *
 *                    XXII Olimpiada Informatyczna                            *
 *                                                                            *
 *   Zadanie:              Pustynia                                           *
 *   Autor programu:       Bartosz Tarnawski                                    *
 *   Zlozonosc czasowa:    O((n + k) log n)                                   *
 *   Opis:                 Rozwiazanie wzorcowe                               *
 *                                                                            *
 *****************************************************************************)

const MAX_N = 100 * 1000;
const MAX_M = 200 * 1000;
const BN = 128 * 1024;
const MAX_D = 1000 * 1000 * 1000;

function min(a, b : longint) : longint;
begin
  if a < b then 
    min := a
  else 
    min := b;
end;

type
  BoundTree =
  object
    public
      constructor Init(n : longint);
      procedure add_value(l, r, v : longint);
      procedure remove(p : longint);
      procedure get_min(var value, point : longint);
    private
      cmin, cpoint, cadd : array[1..2 * BN - 1] of longint;
      procedure update(p : longint);
  end;
  
  constructor BoundTree.Init(n : longint);
  var
    i : longint;
  begin
    for i := 1 to 2 * BN - 1 do
      begin
        cmin[i] := 0;
        cadd[i] := 0;
      end;
    for i := 0 to BN - 1 do
      cpoint[i + BN] := i;
    for i := BN - 1 downto 1 do
      cpoint[i] := cpoint[2 * i];
    add_value(n, BN - 1, MAX_M + 1);
  end;

  procedure BoundTree.update(p : longint);
  var
    cl, cr : longint;
  begin
    assert(p <= BN);
    cl := cmin[2 * p] + cadd[2 * p];
    cr := cmin[2 * p + 1] + cadd[2 * p + 1];
//    //writeln('cl = ', cl, ' cr = ', cr);
    if cl < cr then
      begin
        cmin[p] := cl;
        cpoint[p] := cpoint[2 * p];
      end
    else
      begin
        cmin[p] := cr;
        cpoint[p] := cpoint[2 * p + 1];
      end
  end;

  procedure BoundTree.add_value(l, r, v : longint);
  begin
//    writeln('btr.add_value [', l, ', ', r, '] :', v);
    inc(l, BN); inc(r, BN);
    inc(cadd[l], v);
    if l <> r then
      inc(cadd[r], v);
    while (l div 2) <> (r div 2) do
      begin
        if l mod 2 = 0 then inc(cadd[l + 1], v);
        if r mod 2 = 1 then inc(cadd[r - 1], v);
        l := l div 2; r := r div 2;
        update(l); update(r);
      end;
    l := l div 2;
    while l <> 0 do
      begin
        update(l);
        l := l div 2;
      end;
  end;

  procedure BoundTree.remove(p : longint);
  begin
    add_value(p, p, MAX_M + 1);
  end;

  procedure BoundTree.get_min(var value, point : longint);
  begin
    value := cmin[1] + cadd[1];
    point := cpoint[1];
  end;

type
  DepthTree =
  object
    public
      constructor Init;
      procedure add_constraint(l, r, v : longint);
      function get_constraint(p : longint) : longint;
    private
      tab : array[1..2 * BN - 1] of longint;
  end;
  
  constructor DepthTree.Init;
  var
    i : longint;
  begin
    for i := 1 to 2 * BN - 1 do
      tab[i] := MAX_D + 1;
  end;

  function DepthTree.get_constraint(p : longint) : longint;
  var
    res : longint;
  begin
    res := MAX_D;
    inc(p, BN);
    while p <> 0 do
      begin
        res := min(res, tab[p]);
        p := p div 2;
      end;
    get_constraint := res;
  end;

  procedure DepthTree.add_constraint(l, r, v : longint);
  begin
//    writeln('dtr.add_constraint(', l, ', ', r, ', ', v, ')');
    inc(l, BN); inc(r, BN);
    tab[l] := min(tab[l], v);
    tab[r] := min(tab[r], v);
    while (l div 2) <> (r div 2) do
      begin
        if l mod 2 = 0 then tab[l + 1] := min(tab[l + 1], v);
        if r mod 2 = 1 then tab[r - 1] := min(tab[r - 1], v);
        l := l div 2; r := r div 2;
      end;
  end;

type
  Measurement =
  record
    l, r, k, min_constr : longint;
  end;

var
  n, s, m : longint;
  depth : array[0..MAX_N - 1] of longint;
  meas : array[0..MAX_M - 1] of Measurement;
  btr : BoundTree;
  dtr : DepthTree;

  constr : array[0..MAX_M - 1] of longint;
  iter : array[0..MAX_N - 1, 1..2] of longint;

procedure read_input;
var
  i, j, p, d, x, it: longint;
  info : array[0..MAX_M - 1, 1..2] of longint;
  how_many, hiter : array[0..MAX_N - 1] of longint;
begin
  read(n, s, m);
  btr.Init(n);
  dtr.Init;
//  writeln('n = ', n, ' s = ', s, ' m = ', m);
  for i := 0 to n - 1 do
    begin
      depth[i] := 0;
      how_many[i] := 0;
    end;
  for i := 0 to s - 1 do
    begin
      read(p, d);
      dec(p);
      depth[p] := d;
    end;
  it := 0;
  for i := 0 to m - 1 do
    begin
      with meas[i] do
        begin
          read(l, r, k);
          dec(l); dec(r);
          min_constr := MAX_D;
          btr.add_value(l, r, 1);
          for j := 0 to k - 1 do
            begin
              read(x);
              dec(x);
              btr.add_value(x, x, -1);
              info[it][1] := x;
              info[it][2] := i;
              inc(how_many[x]);
              inc(it);
            end;
        end;
    end;
  it := 0;
  for i := 0 to n - 1 do
    begin
      iter[i][1] := it;
      hiter[i] := it;
      iter[i][2] := it + how_many[i] - 1;
//      writeln('(', iter[i][1], ', ', iter[i][2], ', ', hiter[i], ')');
      inc(it, how_many[i]);
    end;
  for i := 0 to it - 1 do
    begin
      x := info[i][1];
      constr[hiter[x]] := info[i][2];
      inc(hiter[x]);
    end;
  for i := 0 to n - 1 do
    begin
//      write(i, ': ');
      for it := iter[i][1] to iter[i][2] do
//        write(constr[it]);
//      writeln;
    end;
end;

procedure failure;
begin
  writeln('NIE');
  halt(0);
end;

procedure solve;
var
  value, p, d, cnt, i : longint;
begin
  for cnt := 1 to n do
    begin
//      writeln('cnt = ', cnt);
      btr.get_min(value, p);
//      writeln('value = ', value, ' p = ', p);
      if value <> 0 then failure;
      btr.remove(p);
      d := dtr.get_constraint(p);
//      writeln('d = ', d);
      if (d <= 0) or (d > MAX_D) then failure;
      if depth[p] <> 0 then
        begin
          if depth[p] > d then failure;
        end
      else
        depth[p] := d;
//      writeln('depth[', p, '] = ', depth[p]);
      for i := iter[p][1] to iter[p][2] do
        with meas[constr[i]] do
          begin
            if (depth[p] - 1) < min_constr then
              min_constr := depth[p] - 1;
            dec(k);
//            writeln('k = ', k);
            if k = 0 then
              begin
                dtr.add_constraint(l, r, min_constr);
                btr.add_value(l, r, -1);
              end;
          end;
    end;
end;

procedure write_output;
var
  i : longint;
begin
  writeln('TAK');
  for i := 0 to n - 1 do
    write(depth[i], ' ');
  writeln;
end;

begin
  read_input;
  solve;
  write_output;
end.
