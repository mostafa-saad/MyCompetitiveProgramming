{*************************************************************************}
{*                                                                       *}
{*                     XVI Olimpiada Informatyczna                       *}
{*                                                                       *}
{*   Zadanie: Architekci (ARC)                                           *}
{*   Plik:    parclib.h                                                  *}
{*   Autor:   Bartosz Gorski                                             *}
{*   Opis:    Interface modulu arclib dla Pascala                        *}
{*                                                                       *}
{*************************************************************************}

unit parclib;

interface

function inicjuj : longint;
function wczytaj : longint;
procedure wypisz(jakoscProjektu : longint);

implementation

{$Q-}

const MAGIC_BEGIN = -435634223;
const MAGIC_END = -324556462;

const MIN_K = 1;
const MAX_K = 1000000;
const MAX_N = 15000000;
const MIN_A = 1;
const MAX_A = 1000000000;
const MIN_TYP = 1;
const MAX_TYP = 3;
const MIN_PAR = 0;
const MAX_PAR = 1000000000;

const ERROR = 0;
const CORRECT = 1;

var
  init, is_end:boolean;
  lib_n, con_k, N, K, A, TYP, PAR, bre, len_sub, bou:longint;
  rand2_status:longint;

function rand2(a, b:longint):longint;
var x : longint;
begin
  rand2_status := rand2_status * 1103515245 + 12345;
  x := rand2_status;
  if x < 0 then x := -x;
  x := x shr 1;
  x := a + (x mod (b - a + 1));
  rand2 := x;
end;

function random_test:longint;
begin
  random_test := rand2(1, A);
end;

function decreasing_test:longint;
var tmp:longint;
begin
  if bre = 0 then begin
    bre := rand2(0, (N - lib_n + 1 - len_sub));
    tmp := A;
    A := A - rand2(0, (A - 1) div len_sub);
    dec(len_sub)
  end else begin
    dec(bre);
    tmp := rand2(1, A);
  end;
  decreasing_test := tmp;
end;

function increasing_test:longint;
begin
  increasing_test := bou - decreasing_test();
end;

procedure finish(res:longint; com:string);
begin
  if res = ERROR then
    writeln(com);
  halt;
end;

function inicjuj() : longint;
var magic_begin, magic_end:longint;
begin
  if init then
    finish(ERROR, 'Program zawodnika moze wywolac funkcje inicjuj tylko raz!!!');
  init := true;
  readln(K);
  if K > 0 then begin
    TYP := 0;
    N := MAX_N + 2;
    inicjuj := K;
  end else begin
    readln(magic_begin, TYP, N, K, A, PAR, magic_end);
    if (magic_begin <> MAGIC_BEGIN) or (TYP < MIN_TYP) or (TYP > MAX_TYP) then
      finish(ERROR, 'Program zawodnika nie moze korzystac z stdin!!!');
    if (N < 1) or (N > MAX_N) or (N < K) or (K > MAX_K) or (A < MIN_A) or (A > MAX_A) or (PAR < MIN_PAR) or (PAR > MAX_PAR) then
      finish(ERROR, 'Program zawodnika nie moze korzystac z stdin!!!');
    if magic_end <> MAGIC_END then
      finish(ERROR, 'Program zawodnika nie moze korzystac z stdin!!!');
    con_k := 0;
    lib_n := 0;
    is_end := false;
    if (TYP = 2) or (TYP = 3) then begin
      len_sub := PAR;
      bre := 0;
    end;
    if TYP = 2 then begin
      bou := A;
      dec(A);
    end;
    inicjuj := K;
  end;
end;

function wczytaj() : longint;
begin
  if not init then
    finish(ERROR, 'Program zawodnika nie wywolal funkcji inicjuj!!!');
  if (lib_n > N) or is_end then
    finish(ERROR, 'Program zawodnika wywolal funkcje wczytaj po otrzymaniu informacji o koncu ciagu!!!');
  if lib_n = N then
    wczytaj := 0
  else begin
    inc(lib_n);
    if TYP = 0 then begin
      readln(A);
      if A = 0 then is_end := true;
      wczytaj := A;
    end else if TYP = 1 then
      wczytaj := random_test()
    else if TYP = 2 then
      wczytaj := increasing_test()
    else if TYP = 3 then
      wczytaj := decreasing_test()
    else begin
      finish(ERROR, 'Nieznany typ testu');
      wczytaj := -1;
    end;
  end;
end;

procedure wypisz(jakoscProjektu : longint);
begin
  if not init then
    finish(ERROR, 'Program zawodnika nie wywolal funkcji inicjuj!!!');
  writeln(jakoscProjektu);
  inc(con_k);
  if con_k = K then
    finish(CORRECT, '');
end;

begin
  is_end := false;
  init := false;
  rand2_status := 198402041;
end.
