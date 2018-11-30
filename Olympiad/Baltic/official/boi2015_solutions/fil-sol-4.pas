{ Adam Karczmarz }

program fil4;

const
	MAXN = 6000;
  MAXK = 1000000;
var
  N, M, K, S, cur, en : longint;
  last, prev, e, h, anc : array[0 .. MAXN] of longint;
  cnt : array[0 .. MAXK] of longint;
  res : array[0 .. MAXN] of boolean;
  us : array[0 .. MAXK] of boolean;
  
procedure add(v : longint; delta : longint; x : longint);
var
  y, id, w : longint;
begin
  if v > N then begin
    exit;
  end;
  y := h[v] + delta;
  if y <= MAXK then begin
    inc(cnt[y], x);
  end;

  id := last[v];
  while id <> -1 do begin
    w := e[id];
    add(w, delta, x);
    id := prev[id];
  end
end;

procedure case1(v : longint);
var
  y, d, w, id : longint;
begin
  if v > N then begin
    y := K - h[v];
    if y > 0 then begin
      d := 1;
      while (d * d) <= y do begin
        if (y mod d = 0) and ((cnt[d] > 0) or (cnt[y div d] > 0)) then begin
          res[v] := true;
        end;
        inc(d);
      end;
    end;
    exit;
  end;
  add(v, S + 1 - h[v], 1);
  id := last[v];
  while id <> -1 do begin
    w := e[id];
    case1(w);
    id := prev[id];
  end;
  add(v, S + 1 - h[v], -1);
end;

procedure case2(v : longint);
var
  y, w, id, i : longint;
begin
  if v > N then begin
    for i := 0 to (cur - 1) do begin
      y := K - (h[v] - h[anc[i]]) - (S + 1);
      if (y >= 0) and us[y] then begin
        res[v] := true;
      end;
    end;
    exit;
  end;
  anc[cur] := v;
  inc(cur);
  id := last[v];
  while id <> -1 do begin
    w := e[id];
    case2(w);
    id := prev[id];
  end;
  dec(cur);
end;

procedure case3;
var
  i : longint;
begin
  for i := (N + 1) to (N + M) do begin
    if h[i] = K then begin
      res[i] := true;
    end;
  end;
end;

procedure main;
var
  i, p : longint;
begin
	Read(N, M, K, S);
  for i := 0 to (N + M) do begin
    res[i] := false;
    h[i] := 0;
    last[i] := -1;
  end;
  en := 0;
  cur := 0;
  for i := 0 to MAXK do begin
    cnt[i] := 0;
    us[i] := false;
  end;
  h[0] := 1;
  us[1] := true;
  for i := 1 to (N + M) do begin
    Read(p, h[i]);
    e[en] := i;
    prev[en] := last[p];
    last[p] := en;
    inc(en);
    inc(h[i], h[p]);
    if i <= N then begin
      inc(h[i]);
      us[h[i]] := true;
    end;
  end;
  case1(0);
  case2(0);
  case3();
  for i := (N + 1) to (N + M) do begin
    if res[i] then begin
      Writeln('YES');
    end else begin
      Writeln('NO');
    end;
  end;
end;

begin
  main;
end.
