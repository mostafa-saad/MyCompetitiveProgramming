unit collapse;

interface

type
  ArrayOfLongint = array of longint;

function simulateCollapse(N: longint; T_, X_, Y_, W_, P_: ArrayOfLongint): ArrayOfLongint;

implementation

uses math;

type Compare=function(var a,b:longint):boolean;
function lowerBound(var v:array of longint;l,r:longint;a:longint;c:Compare):longint; var i:longint; begin l-=1; while l+1<r do begin i:=(l+r)div 2; if c(v[i],a) then l:=i else r:=i; end; exit(r); end;
procedure swap(var a,b:longint); var t:longint; begin t:=a; a:=b; b:=t; end;
procedure sort(var v:array of longint;l,r:longint;c:Compare); var i,j,k:longint; begin while r-l>4 do begin i:=l+1; j:=(l+r)div 2; k:=r-1; if c(v[i],v[j]) then if c(v[j],v[k]) then swap(v[l],v[j]) else if c(v[i],v[k]) then swap(v[l],v[k]) else swap(v[l],v[i]) else if c(v[i],v[k]) then swap(v[l],v[i]) else if c(v[j],v[k]) then swap(v[l],v[k]) else swap(v[l],v[j]); i:=l+1; j:=r-1; while true do begin while c(v[i],v[l]) do i+=1; while c(v[l],v[j]) do j-=1; if i>=j then break; swap(v[i],v[j]); i+=1; j-=1; end; sort(v,i,r,c); r:=i; end; for i:=0 to r-l-2 do for j:=l to r-2 do if c(v[j+1],v[j]) then swap(v[j],v[j+1]); end;

const
  BLOCK_SIZE: longint = 333;

var
	C, Q: longint;
  T, X, Y, W, P: array of longint;
  uf: array of longint;
  historyLen: longint;
  historyKey, historyVal: array [0 .. 1000010] of longint;

function cmpEdge(var i, j: longint): boolean;
begin
  if Y[i] <> Y[j] then exit(Y[i] < Y[j]) else if X[i] <> X[j] then exit(X[i] < X[j]) else exit(i < j);
end;
function cmpQuery(var i, j: longint): boolean;
begin
  if P[i] <> P[j] then exit(P[i] < P[j]) else exit(i < j);
end;

function root(u: longint): longint;
begin
  if uf[u] < 0 then begin
    exit(u);
  end else begin
    uf[u] := root(uf[u]);
    exit(uf[u]);
  end;
end;
function connect(u, v: longint): boolean;
begin
  u := root(u);
  v := root(v);
  if u = v then exit(false);
  if uf[u] > uf[v] then swap(u, v);
  uf[u] += uf[v];
  uf[v] := u;
  exit(true);
end;

procedure assignSaving(key, val: longint);
begin
  if uf[key] <> val then begin
    historyKey[historyLen] := key;
    historyVal[historyLen] := uf[key];
    historyLen += 1;
    uf[key] := val;
  end;
end;
function rootSaving(u: longint): longint;
begin
  if uf[u] < 0 then begin
    exit(u);
  end else begin
    assignSaving(u, rootSaving(uf[u]));
    exit(uf[u]);
  end;
end;
function connectSaving(u, v: longint): boolean;
begin
  u := rootSaving(u);
  v := rootSaving(v);
  if u = v then exit(false);
  if uf[u] > uf[v] then swap(u, v);
  assignSaving(u, uf[u] + uf[v]);
  assignSaving(v, u);
  exit(true);
end;

function simulateCollapse(N: longint; T_, X_, Y_, W_, P_: ArrayOfLongint): ArrayOfLongint;
var
  ans: array of longint;
  edges, queries: array of longint;
  edgesLen, queriesLen: longint;
  link: array of longint;
  cntGlobal, cntLocal: longint;
  e, f, g, h, i, j, k, u, phase: longint;
begin
	C := Length(T_);
	Q := Length(W_);
  setlength(T, C);
  setlength(X, C);
  setlength(Y, C);
  for i := 0 to C - 1 do begin
    T[i] := T_[i];
    X[i] := X_[i];
    Y[i] := Y_[i];
  end;
  setlength(W, Q);
  setlength(P, Q);
  for h := 0 to Q - 1 do begin
    W[h] := W_[h];
    P[h] := P_[h];
  end;
  
  setlength(ans, Q);
  for h := 0 to Q - 1 do begin
    ans[h] := N;
  end;
  setlength(queries, Q);
  setlength(uf, N);
  
  for phase := 0 to 1 do begin
    for i := 0 to C - 1 do begin
      if X[i] > Y[i] then begin
        swap(X[i], Y[i]);
      end;
    end;
    
    setlength(edges, C);
    edgesLen := 0;
    for i := 0 to C - 1 do begin
      if T[i] = 0 then begin
        edges[edgesLen] := i;
        edgesLen += 1;
      end;
    end;
    sort(edges, 0, edgesLen, @cmpEdge);
    setlength(link, C);
    for i := 0 to C - 1 do begin
      link[i] := C;
    end;
    for j := 0 to C - 1 do begin
      if T[j] = 1 then begin
        e := lowerBound(edges, 0, edgesLen, j, @cmpEdge) - 1;
        if e >= 0 then begin
          i := edges[e];
          if (X[i] = X[j]) and (Y[i] = Y[j]) then begin
            link[i] := j;
            link[j] := i;
          end;
        end;
      end;
    end;
    
    i := 0;
    while i < C do begin
      { solve for cable plans [i, j) }
      j := min(i + BLOCK_SIZE, C);
      queriesLen := 0;
      for h := 0 to Q - 1 do begin
        if (i <= W[h]) and (W[h] < j) then begin
          queries[queriesLen] := h;
          queriesLen += 1;
        end;
      end;
      sort(queries, 0, queriesLen, @cmpQuery);
      
      for u := 0 to N - 1 do begin
        uf[u] := -1;
      end;
      cntGlobal := 0;
      
      e := 0;
      for f := 0 to queriesLen - 1 do begin
        h := queries[f];
        { global edges }
        while (e < edgesLen) and (Y[edges[e]] <= P[h]) do begin
          if (edges[e] < i) and (j <= link[edges[e]]) then begin
            if connect(X[edges[e]], Y[edges[e]]) then begin
              cntGlobal += 1;
            end;
          end;
          e += 1;
        end;
        { path compression }
        for k := i to j - 1 do begin
          if ((T[k] = 0) and (k <= W[h]) and (W[h] < link[k])) or ((T[k] = 1) and (link[k] <= W[h]) and (W[h] < k)) then begin
            if Y[k] <= P[h] then begin
              root(X[k]);
              root(Y[k]);
            end;
          end;
        end;
        { backtracking }
        historyLen := 0;
        cntLocal := 0;
        for k := i to j - 1 do begin
          if ((T[k] = 0) and (k <= W[h]) and (W[h] < link[k])) or ((T[k] = 1) and (link[k] <= W[h]) and (W[h] < k)) then begin
            if Y[k] <= P[h] then begin
              if connectSaving(X[k], Y[k]) then begin
                cntLocal += 1;
              end;
            end;
          end;
        end;
        ans[h] -= cntGlobal;
        ans[h] -= cntLocal;
        for g := historyLen - 1 downto 0 do begin
          uf[historyKey[g]] := historyVal[g];
        end;
      end;
      
      i := j;
    end;
    
    for i := 0 to C - 1 do begin
      X[i] := N - 1 - X[i];
      Y[i] := N - 1 - Y[i];
    end;
    for h := 0 to Q - 1 do begin
      P[h] := N - 2 - P[h];
    end;
  end;
  
  exit(ans);
end;

end.
