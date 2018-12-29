(*************************************************************************
 *                                                                       *
 *                    IX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Rozwi±zanie zadania: Narciarze                                      *
 *   Plik:                nar.pas                                        *
 *   Autor:               Remigiusz Ró¿ycki                              *
 *************************************************************************)
const
  maxN = 5000;
  maxM = 3*maxN - 6; { maksymalna liczba krawedzi }
  maxV = 2*maxN - 4 + 1; { maksymalna liczba scian }

type
  polaczenie = record
    nast : integer;
    p : integer;
  end;

  Twierzcholki = array[1..maxN] of integer;
  Tkrawedzie = array[1..maxM] of polaczenie;
  Tsciany = array[1..maxV] of integer;

var
  n, m, v, m2 : integer;

  wierz : ^Twierzcholki;
  krawe : ^Tkrawedzie;
  sciany : ^Tsciany;
  krawe2 : ^Tkrawedzie;
  stopien : ^Tsciany;

  narciarze : integer;

procedure ReadIn;
var
  f : text;
  ilp, i, j, p: integer;
begin
  fillchar(wierz^,sizeof(wierz^),0);

  m := 0;

  assign(f,'nar.in');
  reset(f);
  readln(f,n);
  for i := 1 to n-1 do
  begin
    read(f, ilp);
    for j := 1 to ilp do
    begin
      read(f, p);
      inc(m);
      krawe^[m].nast := wierz^[i];
      krawe^[m].p := p;
      wierz^[i] := m;
    end;
  end;
  close(f);
end;

procedure WriteOut;
var
  f : text;
begin
  assign(f,'nar.out');
  rewrite(f);
  writeln(f, narciarze);
  close(f);
end;

procedure ZmienReprezentacje;
var
  stos : ^Twierzcholki;
  aktl : ^Twierzcholki;

  nastosie : integer;

  lista : ^Twierzcholki;
  zesciana : ^Twierzcholki;

  ns, pocz : integer;
begin
  m2 := 0;
  new(stos);
  new(lista);
  new(aktl);
  new(zesciana);

  fillchar(lista^,sizeof(lista^),0);

  fillchar(sciany^,sizeof(sciany^),0);
  fillchar(stopien^,sizeof(stopien^),0);

  stos^[1] := 1;
  aktl^[1] := wierz^[1];
  nastosie := 1;

  lista^[n] := 1;
  lista^[1] := 1;
  zesciana^[n] := 1;

  v := 1;

  while nastosie > 0 do
  begin
    if aktl^[nastosie] = 0 then dec(nastosie)
    else

    if lista^[krawe^[aktl^[nastosie]].p] = 0 then
    begin
      stos^[nastosie + 1] := krawe^[aktl^[nastosie]].p;
      aktl^[nastosie + 1] := wierz^[krawe^[aktl^[nastosie]].p];

      aktl^[nastosie] := krawe^[aktl^[nastosie]].nast;
      inc(nastosie);
    end
    else

    if lista^[krawe^[aktl^[nastosie]].p] > 0 then
    begin

      ns := nastosie;

      pocz := lista^[krawe^[aktl^[nastosie]].p];

      if v <> zesciana^[krawe^[aktl^[nastosie]].p] then
      begin
        inc(m2);
        krawe2^[m2].nast := sciany^[v];
        krawe2^[m2].p := zesciana^[krawe^[aktl^[nastosie]].p];
        sciany^[v] := m2;
        inc(stopien^[zesciana^[krawe^[aktl^[nastosie]].p]]);
      end;

      lista^[krawe^[aktl^[nastosie]].p] := stos^[nastosie];

      zesciana^[krawe^[aktl^[nastosie]].p] := v;

      while lista^[stos^[ns]] = 0 do
      begin
        lista^[stos^[ns]] := stos^[ns-1];
        zesciana^[stos^[ns]] := v;
        dec(ns);
      end;

      while pocz <> stos^[ns] do
      begin
        inc(m2);
        krawe2^[m2].nast := sciany^[v];
        krawe2^[m2].p := zesciana^[pocz];
        sciany^[v] := m2;

        inc(stopien^[zesciana^[pocz]]);

        pocz := lista^[pocz];
      end;
      aktl^[nastosie] := krawe^[aktl^[nastosie]].nast;
      inc(v);
    end;
  end;

  pocz := n;
  while pocz <> 1 do
  begin
    inc(m2);
    krawe2^[m2].nast := sciany^[v];
    krawe2^[m2].p := zesciana^[pocz];
    sciany^[v] := m2;
    inc(stopien^[zesciana^[pocz]]);
    pocz := lista^[pocz];
  end;

  dispose(stos);
  dispose(lista);
  dispose(aktl);
  dispose(zesciana);

end;


procedure SortujTopologicznie;
var
  stos : ^Twierzcholki;
  nastosie : integer;

  maxodl : ^Twierzcholki;

  aktl, w : integer;
begin
  new(maxodl);
  new(stos);

  nastosie := 1;

  fillchar(maxodl^,sizeof(maxodl^),0);

  stos^[nastosie] := v;
  inc(nastosie);

  while nastosie > 1 do
  begin
    dec(nastosie);
    w := stos^[nastosie];
    aktl := sciany^[w];

    while aktl <> 0 do
    begin
      dec(stopien^[krawe2^[aktl].p]);
      if maxodl^[krawe2^[aktl].p] <= maxodl^[w] then
      begin
        maxodl^[krawe2^[aktl].p] := maxodl^[w] +1;
      end;

      if stopien^[krawe2^[aktl].p] = 0 then
      begin
        stos^[nastosie] := krawe2^[aktl].p;
        inc(nastosie);
      end;
      aktl := krawe2^[aktl].nast;
    end;
  end;

  narciarze := maxodl^[1];

  dispose(stos);
  dispose(maxodl);
end;

begin
  new(wierz);
  new(krawe);

  ReadIn;

  new(sciany);
  new(krawe2);
  new(stopien);

  ZmienReprezentacje;

  SortujTopologicznie;
  WriteOut;
end.
