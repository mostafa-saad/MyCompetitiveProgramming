(*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Klocki                                        *
 *   Autor:                Szymon Stankiewicz, Karol Farbis              *
 *   Zlozonosc czasowa:    O(n)                                          *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie bledne                            *
 *                         Niepoprawnie sprawdza warunki niezbedne       *
 *                         do istnienia rozwiazania.                     *
 *                                                                       *
 *************************************************************************)

program klo;

const
    MAX_N = 1000007;

type
    plist = ^list;
    list = record
        next : plist;
        val : longint;
    end;

var
    K, p, q, n, act : longint;
    tab, gen, out : array[0..MAX_N-1] of longint;
    sort : array[0..MAX_N-1] of plist;

procedure add(a, b: longint);
var
    act : plist;
begin
    new(act);
    act^.val := a;
    act^.next := sort[b];
    sort[b] := act;
end;

procedure write_in(a : longint);
var
    i : longint;
begin
    for i:=0 to tab[a]-1 do begin
        gen[act] := a;
        inc(act);
    end;
end;

procedure myswap(i, j: longint);
var
    k : longint;
begin
    k := out[i];
    out[i] := out[j];
    out[j] := k;
end;

procedure reverse;
var
    i : longint;
begin
    i := 0;
    while i*2 < n do begin
        myswap(i, n-i-1);
        inc(i);
    end;
end;

procedure generate;
var
    i : longint;
    help : plist;
begin
    for i:=1 to MAX_N-1 do
        sort[i] := nil;
    for i:=1 to K do
        add(i, tab[i]);

    for i:=1 to MAX_N-1 do begin
        help := sort[i];
        while help <> nil do begin
            write_in(help^.val);
            help := help^.next;
        end;
    end;

    for i:=0 to n-1 do
        out[i] := gen[(n div 2 * ((n mod 2) xor (i mod 2))) + i div 2];

    if (out[0] <> p) and (out[n-1] <> q) then exit;
    if (out[0] <> q) and (out[n-1] <> p) then begin
        reverse;
        exit;
    end;
    if out[n-1] = q then
        reverse;
    myswap(0, 1);
    for i := 1 to n-2 do
        if out[i] = out[i+1] then
            myswap(i+1, i+2);
end;

procedure main;
var
    i,maxi,k2 : longint;
begin
    readln(K, p, q);
    for i:=1 to K do begin
        read(tab[i]);
        n := n + tab[i];
    end;
    if (n > 1) and (p = q) and (tab[p] < 2) then begin
        writeln(0);
        exit;
    end;

    maxi := 0;
    for i:=1 to K do
        if tab[i] > tab[maxi] then
            maxi := i;

    if tab[maxi] > (n+1) div 2 then begin
        writeln(0);
        exit;
    end;

    if tab[maxi] = (n+1) div 2 then begin
        if n mod 2 = 1 then
            if (p=q) and (p=maxi) then begin
                k2 := 1;
                for i:=0 to n-1 do
                    if i mod 2 = 0 then
                        write(maxi, ' ')
                    else begin
                        while (tab[k2] = 0) or (k2 = maxi) do inc(k2);
                        write(k2, ' ');
                        dec(tab[k2]);
                    end;
                exit
            end else begin
                writeln(0);
                exit;
            end
        else
            if (p <> q) and ((p = maxi) or (q = maxi)) then begin
                dec(tab[p]);
                dec(tab[q]);
                write(p, ' ');
                k2:=1;
                for i:=1 to n-2 do
                    if (i mod 2 = 1) xor (p = maxi) then begin
                        write(maxi, ' ');
                        dec(tab[maxi]);
                    end else begin
                        while (k2= maxi) or (tab[k2] = 0) do inc(k2);
                        write(k2, ' ');
                        dec(tab[k2]);
                    end;
                writeln(q)
            end else begin
                writeln(0);
                exit;
            end;
        exit;
    end;

    dec(tab[p]);
    dec(tab[q]);
    n := n - 2;
    generate;
    write(p, ' ');
    for i:=0 to n-1 do
        write(out[i], ' ');
    writeln(q);
end;

begin
    main
end.
