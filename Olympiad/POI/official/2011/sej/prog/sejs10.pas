(*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Sejf                                             *
 *   Autor:             Pawel Parys                                      *
 *   Zlozonosc czasowa: O(sqrt(n)+k*liczbadzielnikow(n)^2)               *
 *   Opis:              Rozwiazanie powolne                              *
 *                      przerywa po znalezieniu d i swiadka, kolejnosc   *
 *                      malejaca                                         *
 *                                                                       *
 *************************************************************************)

var
    ile_p : longint;
    pierwsze : array[0..64] of int64;
    wielokrotnosci : array[0..64] of longint;

procedure rozloz(n : int64);
{ zwraca liste dzielnikow pierwszych+liczba wielokrotnosci (w zmiennych ile_p, pierwsze, wielokrotnosci) }
var 
    p : longint;
    ile : longint;
begin 
    ile_p := 0;
    p := 2;
    if p*(int64(p))<=n then begin {dla p=2}
        ile := 0;
        while (n mod p)=0 do begin
            inc(ile);
            n := n div p;
        end;
        if ile>0 then begin
            pierwsze[ile_p] := p;
            wielokrotnosci[ile_p] := ile;
            inc(ile_p);
        end;
        inc(p);
    end;
    while p*(int64(p))<=n do begin {dla p nieparzystych} 
        ile := 0;
        while (n mod p)=0 do begin
            inc(ile);
            n := n div p;
        end;
        if ile>0 then begin
            pierwsze[ile_p] := p;
            wielokrotnosci[ile_p] := ile;
            inc(ile_p);
        end;
        p := p+2; { zwiekszamy o 2, co przyspiesza 2 razy i jest prawie tak szybki jak w c++ }
    end;
    if n>1 then begin
        pierwsze[ile_p] := n;
        wielokrotnosci[ile_p] := 1;
        inc(ile_p);
    end;
end;

var
    ile_dz : longint;
    dzielniki : array[0..20000] of int64;

procedure sortuj_dzielniki;
{ sortuje tablice dzielniki (quicksort) }
    procedure QuicksortRecur(start, stop: longint);

        function Split(start, stop: longint): integer; { bierze piewszy i ostatni, zwraca punkt podzialu }
        var
            left, right: longint; 
            pivot: int64;

            procedure swap(var a, b: int64);
            var
                t: int64;
            begin
                t := a;
                a := b;
                b := t
            end;

        begin { Split }
            pivot := dzielniki[start];
            left := start+1;
            right := stop;
            while left<=right do begin
                while (left<=stop) and (dzielniki[left]<pivot) do
                    inc(left);
                while (right>start) and (dzielniki[right]>=pivot) do
                    dec(right);
                if left<right then 
                    swap(dzielniki[left], dzielniki[right]);
            end;
            swap(dzielniki[start], dzielniki[right]);
            Split := right
        end;

    var
        splitpt: longint; { element dzielacy }

    begin { QuicksortRecur }
	if start<stop then begin
            splitpt := Split(start, stop);
            QuicksortRecur(start, splitpt-1);
            QuicksortRecur(splitpt+1, stop);
        end
    end;
                    
begin
    QuicksortRecur(0, ile_dz-1)
end;

procedure znajdz_dzielniki(n : int64);
{ zwraca posortowana liste dodatnich dzielnikow liczby n (w tym 1 i n) - w zmiennych ile_dz, dzielniki }
var 
    ile : array[0..64] of longint; { ile razy bierzemy ktora liczbe pierwsza }
    dz : int64;
    a : longint;
begin
    ile_dz := 0;
    rozloz(n);
    dz := 1;
    for a := 0 to 64 do 
        ile[a] := 0;
    while true do begin
        dzielniki[ile_dz] := dz;
        inc(ile_dz);
        a := 0;
        while true do begin
            if a>=ile_p then begin
                sortuj_dzielniki;
                exit;
            end
            else
            if ile[a]<wielokrotnosci[a] then begin
                inc(ile[a]);
                dz := dz*pierwsze[a];
                break;
            end
            else
                while ile[a]>0 do begin
                    dec(ile[a]);
                    dz := dz div pierwsze[a];
                end;
            inc(a);
        end;
    end;
end;

var
    a, b, k : longint;
    n, d : int64;
    m : array[0..249999] of int64;
    ok : boolean;

begin
    readln(n, k);
    for a := 0 to k-1 do 
        read(m[a]);
    znajdz_dzielniki(n);
    for a := 0 to ile_dz-1 do begin
        d := dzielniki[a];
        if ((n mod d)>0) or ((m[k-1] mod d)>0) then
            continue;
        ok := true;
        for b := 0 to k-2 do 
            if (m[b] mod d)=0 then begin
                ok := false;
                break;
            end;
        if ok then begin 
            writeln(n div d);
            halt;
        end;
    end;
end.
