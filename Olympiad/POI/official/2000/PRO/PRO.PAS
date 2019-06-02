{*************************************************************************}
{*                                                                       *}
{*                   VII Olimpiada Informatyczna                         *}
{*                                                                       *}
{*   Rozwi¥zanie zadania: PROMOCJA                                       *}
{*   Plik:                PRO.PAS                                        *}
{*   Autor:               MARCIN SAWICKI                                 *}
{*************************************************************************}

{$A+,B-,D+,E-,F-,G-,I-,L+,N+,O-,P-,Q-,R-,S-,T+,V+,X+,Y+}
{$M 16384,0,655360}
program Promocja;

const
  MAX_n = 5000;

type
  ElemStogu = record
    t: LongInt;
    Ref: Integer;
  end;
  PStogZRef = ^StogZRef;
  StogZRef = record {struktura stogu z referencjami do drugiego stogu}
    Dane: array [0..2 * MAX_n - 1] of ElemStogu;
    IleDanych: Integer;
    Porzadek: Boolean; {true = na szczycie jest element min, false = max}
    StogRef: PStogZRef;  {referencja do partnera}
  end;

procedure InicjujStog (var S: StogZRef; P0: Boolean);
begin
  with S do
  begin
    IleDanych := 0;
    Porzadek := P0;
    StogRef := nil;
  end;
end;

procedure ZamienUwzglRef (var S: StogZRef; k1, k2: Integer);
var
  Pom: ElemStogu;
begin
  with S do
  begin
    Pom := Dane [k1];
    Dane [k1] := Dane [k2];
    Dane [k2] := Pom;
    if Dane [k1].Ref <> -1 then
      StogRef^.Dane [Dane [k1].Ref].Ref := k1;
    if Dane [k2].Ref <> -1 then
      StogRef^.Dane [Dane [k2].Ref].Ref := k2;
  end;
end;

function Por (b: Boolean; i1, i2: LongInt): Boolean;
begin
  if b then
    Por := i1 < i2
  else
    Por := i1 > i2;
end;

procedure StogNaDol (var S: StogZRef; k: Integer);
var
  c: Integer;
begin
  with S do
  begin
    c := 2 * k + 1;
    while c < IleDanych do
    begin
      if (c + 1 < IleDanych) and Por (Porzadek, Dane [c + 1].t, Dane [c].t) then
        Inc (c);
      if not Por (Porzadek, Dane [c].t, Dane [k].t) then
        Exit;
      ZamienUwzglRef (S, c, k);
      k := c;
      c := 2 * k + 1;
    end;
  end;
end;

procedure StogNaGore (var S: StogZRef; k: Integer);
var
  p: Integer;
begin
  with S do
  begin
    while k > 0 do
    begin
      p := (k - 1) div 2;
      if not Por (Porzadek, Dane [k].t, Dane [p].t) then
        Exit;
      ZamienUwzglRef (S, p, k);
      k := p
    end;
  end;
end;

procedure UsunElement (var S: StogZRef; k: Integer);
var
  w: ElemStogu;
begin
  with S do
  begin
    w := Dane [k];
    Dec (IleDanych);

    if w.Ref <> -1 then
    begin
      StogRef^.Dane [w.Ref].Ref := -1;
      UsunElement (StogRef^, w.Ref);
      Dane [k].Ref := -1;
    end;

    if k = IleDanych then
      Exit;

    ZamienUwzglRef (S, k, IleDanych);
    if Por (Porzadek, Dane [k].t, w.t) then
      StogNaGore (S, k)
    else
      StogNaDol (S, k);
  end;
end;

var
  f, o: Text;
  RachunkiMin, RachunkiMinOdwr: ^StogZRef;
  RachunkiMax, RachunkiMaxOdwr: ^StogZRef;
  n, i: Integer;
  k, j: LongInt;
  t1: LongInt;
  Koszt: Comp;
  IleRachunkowWUrnie: LongInt;



begin
  Assign (f, 'PRO.IN');
  Reset (f);
  Assign (o, 'PRO.OUT');
  ReWrite (o);

  New (RachunkiMin);
  New (RachunkiMinOdwr);
  New (RachunkiMax);
  New (RachunkiMaxOdwr);

  InicjujStog (RachunkiMin^, True);
  InicjujStog (RachunkiMinOdwr^, False);
  InicjujStog (RachunkiMax^, False);
  InicjujStog (RachunkiMaxOdwr^, True);
  RachunkiMinOdwr^.StogRef := RachunkiMin;
  RachunkiMaxOdwr^.StogRef := RachunkiMax;
  RachunkiMin^.StogRef := RachunkiMinOdwr;
  RachunkiMax^.StogRef := RachunkiMaxOdwr;

  Koszt := 0.0;
  IleRachunkowWUrnie := 0;

  ReadLn (f, n);
  for i := 0 to n - 1 do
  begin
    { w ka¾dym ze stog¢w trzymamy najwy¾ej 2 * (n - i) liczb }
    Read (f, k);
    if RachunkiMin^.IleDanych > 2 * (n - i) then {zb©dny na 100%}
      UsunElement (RachunkiMinOdwr^, 0); {automatycznie usuwa par©}

    if RachunkiMax^.IleDanych > 2 * (n - i) then {zb©dny na 100%}
      UsunElement (RachunkiMaxOdwr^, 0); {automatycznie usuwa par©}

    for j := 0 to k - 1 do
    begin
      Read (f, t1);
      Inc (IleRachunkowWUrnie);

      if (RachunkiMin^.IleDanych = 2 * (n - i)) {st¢g peˆen}
        and (RachunkiMinOdwr^.Dane [0].t > t1) then {mamy lepszy element}
          UsunElement (RachunkiMinOdwr^, 0); {automatycznie usuwa par©}
      if RachunkiMin^.IleDanych < 2 * (n - i) then {potrzeba doda† element}
      begin {RachunkiMin.IleDanych = RachunkiMinOdwr.IleDanych !}
        with RachunkiMin^, Dane [IleDanych] do
        begin
          t := t1;
          Ref := IleDanych;
          Inc (IleDanych);
        end;
        with RachunkiMinOdwr^, Dane [IleDanych] do
        begin
          t := t1;
          Ref := IleDanych;
          Inc (IleDanych);
        end;
        StogNaGore (RachunkiMin^, RachunkiMin^.IleDanych - 1);
        StogNaGore (RachunkiMinOdwr^, RachunkiMinOdwr^.IleDanych - 1);
      end;

      if (RachunkiMax^.IleDanych = 2 * (n - i)) {st¢g peˆen}
        and (RachunkiMaxOdwr^.Dane [0].t < t1) then {mamy lepszy element}
          UsunElement (RachunkiMaxOdwr^, 0); {automatycznie usuwa par©}
      if RachunkiMax^.IleDanych < 2 * (n - i) then {trzeba doda† element}
      begin {RachunkiMax.IleDanych = RachunkiMaxOdwr.IleDanych !}
        with RachunkiMax^, Dane [IleDanych] do
        begin
          t := t1;
          Ref := IleDanych;
          Inc (IleDanych);
        end;
        with RachunkiMaxOdwr^, Dane [IleDanych] do
        begin
          t := t1;
          Ref := IleDanych;
          Inc (IleDanych);
        end;
        StogNaGore (RachunkiMax^, RachunkiMax^.IleDanych - 1);
        StogNaGore (RachunkiMaxOdwr^, RachunkiMaxOdwr^.IleDanych - 1);
      end;

    end;
    ReadLn (f);

    Koszt:=Koszt+(RachunkiMax^.Dane [0].t - RachunkiMin^.Dane [0].t);

    if IleRachunkowWUrnie = RachunkiMax^.IleDanych then
         {w parze stog¢w ,,Max'' s¥ wszystkie rachunki, kt¢re s¥ w urnie,
          wi©c najmniejszy trzeba usun¥†}
      UsunElement (RachunkiMaxOdwr^, 0);

    UsunElement (RachunkiMin^, 0); { automatycznie usuwa odp.
                                         elem. stogu RachunkiMinOdwr }

    Dec (IleRachunkowWUrnie);

    { to samo z najwi©kszym rachunkiem z urny}
    if IleRachunkowWUrnie = RachunkiMin^.IleDanych then
      UsunElement (RachunkiMinOdwr^, 0);

    UsunElement (RachunkiMax^, 0);

    Dec (IleRachunkowWUrnie);
  end;
  WriteLn (o, Koszt:0:0);
  Close (f);
  Close (o);
end.

