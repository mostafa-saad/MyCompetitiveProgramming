(******************************************************************************
 *                                                                            *
 *                    XXII Olimpiada Informatyczna                            *
 *                                                                            *
 *   Zadanie:              Logistyka                                          *
 *   Autor programu:       Bartosz Tarnawski                                  *
 *   Zlozonosc czasowa:    O(m (log n + log m))                               *
 *   Opis:                 Rozwiazanie weryfikujace                           *
 *****************************************************************************)


const MAX_N = 1000 * 1000;
const SZ = 1024 * 1024;

var
    n, m : longint;
    typ_zdarzenia : array[0..MAX_N] of boolean;
    zdarzenia : array[0..MAX_N] of array[1..2] of longint;
    uprawnienia, odleglosci : array[0..MAX_N] of longint;
    tr_licz, tr_sum : array[0..2 * SZ] of int64;

{ http://www.pp4s.co.uk/main/tu-ss-sort-quick.html }
procedure Quicksort(Left, Right: longint; var Ints : array of longint);
var
  ptrLeft, ptrRight, Pivot, Temp: longint;
begin
  ptrLeft := Left;
  ptrRight := Right;
  Pivot := Ints[(Left + Right) div 2];
  repeat
    while (ptrLeft < Right) and (Ints[ptrLeft] < Pivot) do
      inc(ptrLeft);
    while (ptrRight > Left) and (Ints[ptrRight] > Pivot) do
      dec(ptrRight);
    if ptrLeft <= ptrRight then  
      begin
        if ptrLeft < ptrRight then
          begin
            Temp := Ints[ptrLeft];
            Ints[ptrLeft] := Ints[ptrRight];
            Ints[ptrRight] := Temp;
          end;
        inc(ptrLeft);
        dec(ptrRight);
     end;
  until ptrLeft > ptrRight; 
  if ptrRight > Left then
    Quicksort(Left, ptrRight, Ints);
  if ptrLeft < Right then
    Quicksort(ptrLeft, Right, Ints);
end;    


function odl_na_id(odl : longint) : longint;
var
    l, mid, r : longint;
begin
    l := 0;
    r := m - 1;
    while l < r do
        begin
            mid := l + (r - l) div 2;
            if odleglosci[mid] < odl then
                l := mid + 1
            else
                r := mid;
        end;
    odl_na_id := l;
end;


procedure init(var t : array of int64);
var
    i : longint;
begin
    for i := 1 to 2 * SZ do
        t[i] := 0;
end;

procedure dodaj(x : longint; v : int64; var t : array of int64);
begin
    inc(x, SZ);
    inc(t[x], v);
    x := x div 2;
    while x <> 0 do
        begin
            t[x] := t[2 * x] + t[2 * x + 1];
            x := x div 2;
        end;
end;

function suma(l, r : longint; var t : array of int64) : int64;
var
    wyn : int64;
begin
    if l > r then
        begin
            suma := 0;
            exit;
        end;
    inc(l, SZ);
    inc(r, SZ);
    wyn := t[l];
    if l <> r then
        inc(wyn, t[r]);
    while (l div 2) <> (r div 2) do
        begin
            if (l mod 2) = 0 then
                inc(wyn, t[l + 1]);
            if (r mod 2) = 1 then
                inc(wyn, t[r - 1]);
            l := l div 2;
            r := r div 2;
        end;
    suma := wyn;
end;


procedure zmien(kto, typ : longint);
var
    odl, id : longint;
begin
    odl := uprawnienia[kto];
    if odl <> 0 then
        begin
            id := odl_na_id(odl);
            dodaj(id, typ, tr_licz);
            dodaj(id, typ * odl, tr_sum);
        end;
end;

var
    i, a, b, id : longint;
    calosc, reszta : int64;
    typ : char;
begin
    readln(n, m);
    for i := 0 to m - 1 do
        begin
            readln(typ, a, b);
            zdarzenia[i][1] := a;
            zdarzenia[i][2] := b;
            if typ = 'U' then
                typ_zdarzenia[i] := true
            else
                typ_zdarzenia[i] := false;
            odleglosci[i] := b;
        end;

    quicksort(0, m - 1, odleglosci);
    
    init(tr_licz);
    init(tr_sum);

    for i := 0 to m - 1 do
        begin
            a := zdarzenia[i][1];
            b := zdarzenia[i][2];
            if typ_zdarzenia[i] then
                begin
                    zmien(a, -1);
                    uprawnienia[a] := b;
                    zmien(a, 1);
                end
            else
                begin
                    id := odl_na_id(b);
                    calosc := suma(id, m, tr_licz);
                    reszta := suma(0, id - 1, tr_sum);
                    if int64(a - calosc) * int64(b) <= reszta then
                        writeln('TAK')
                    else
                        writeln('NIE');
                end;
        end;
end.
