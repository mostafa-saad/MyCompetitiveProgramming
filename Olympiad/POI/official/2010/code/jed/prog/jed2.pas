(*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:              Jedynki (JED)                                 *
 *   Plik:                 jed2.pas                                      *
 *   Autor:                Przemyslaw Horban                             *
 *   Opis:                 Rozwiazanie wzorcowe.                         *
 *   Zlozonosc czasowa:    O(n)                                          *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *                                                                       *
 *************************************************************************)

const
    MAX_N = 1000000;
    BIG_INT_CAPACITY = 3 * MAX_N + 1000;

type
    BigInt = record
        bLen : array [0..BIG_INT_CAPACITY] of Longint;
        bVal : array [0..BIG_INT_CAPACITY] of Byte;
        size, itSteps, itNextBlock : Longint;
        itValue : Byte;
    end;

var
    sz : Longint;
    N, tmpBB, tmpBB2, ls, ps : BigInt;

function readBigInt(var b : BigInt) : Longint;
var
    i, sz : Longint;
    v : Byte;
begin
    sz := 0;
    v := 1;
    with b do
    begin
        readln(size);
        for i := size - 1 downto 0 do
        begin
            read(bLen[i]);
            sz := sz + bLen[i];
            bVal[i] := v;
            v := 1 - v;
        end;
    end;
    readBigInt := sz;
end;

procedure writeBigInt(var b : BigInt);
var 
    i : Longint;
begin
    with b do
    begin
        writeln(size);
        for i := size - 1 downto 0 do
        begin
            write(bLen[i]);
            if i > 0 then
                write(' ')
            else
                write(chr(10));
        end;
    end;
end;

procedure push(var b : BigInt; len, v : Longint);
begin
    //writeln('push len:', len, ' val:', v);
    if len > 0 then
        with b do
        begin
            if (size = 0) or (bVal[size - 1] <> v) then
            begin
                bVal[size] := v;
                bLen[size] := len;
                inc(size);
            end
            else
                bLen[size - 1] := bLen[size - 1] + len;
        end;
end;

procedure ofInt(var b : BigInt; n : Longint);
begin
    b.size := 0;
    while n <> 0 do
    begin
        push(b, 1, n mod 2);
        n := n div 2;
    end;
end;

procedure setToStart(var b : BigInt);
begin
    b.itSteps := 0;
    b.itValue := 0;
    b.itNextBlock := 0;
end;

function atEnd(var b : BigInt) : Boolean;
begin
    atEnd := (b.itSteps = 0) and (b.itNextBlock = b.size);
end;

procedure rewind(var b : BigInt);
begin
    if (b.itSteps = 0) and (b.itNextBlock < b.size) then
    begin
        b.itSteps := b.bLen[b.itNextBlock];
        b.itValue := b.bVal[b.itNextBlock];
        inc(b.itNextBlock);
    end;
end;

procedure step(var b : BigInt; len : Longint);
begin
    while (len > 0) and (not atEnd(b)) do
    begin
        rewind(b);
        if len > b.itSteps then
        begin
            len := len - b.itSteps;
            b.itSteps := 0;
        end else
        begin
            b.itSteps := b.itSteps - len;
            len := 0;
        end;
    end;
end;

procedure safeGetBlock(var b : BigInt; var v : Longint;
                       var l : Longint; defaultLen : Longint);
begin
    if atEnd(b) then
    begin
        v := 0;
        l := defaultLen;
    end else
    begin
        v := b.itValue;
        l := b.itSteps;
    end;
end;

procedure operate(var r : BigInt; var b1 : BigInt;
                  var b2 : BigInt; subtraction : Boolean);
var
    v1, v2, l1, l2, l, c : Longint;
begin
    r.size := 0;
    c := 0;
    while (not atEnd(b1)) or (not atEnd(b2)) do
    begin
        rewind(b1); rewind(b2);
        //writeln('While l1,l2 = ', b1.itSteps, ',', b2.itSteps);
        safeGetBlock(b1, v1, l1, b2.itSteps);
        safeGetBlock(b2, v2, l2, b1.itSteps);
        l := l1;
        if l > l2 then l := l2;
        step(b1, l); step(b2, l);
        //writeln('Block of len:', l, ' and values:', v1, ',', v2);
        if subtraction then v2 := -v2;
        l1 := 4 + 3 * v1 + 3 * v2 + c; { Magic }
        push(r, 1, (l1 and 1));
        push(r, l - 1, (l1 and 2) div 2);
        if (l1 and 4) <> 0 then c := 0
        else if (l1 and 8) <> 0 then c := 1
        else c := -1;
    end;
    if c = 1 then push(r, 1, 1)
    else if c = -1 then
    begin
        writeln('ERROR: c == -1');
        halt;
    end;
    while (r.size > 0) and 
          ((r.bVal[r.size - 1] = 0) or (r.bLen[r.size - 1] = 0)) do
        dec(r.size);
end;

procedure add(var r : BigInt; var b1 : BigInt; var b2 : BigInt);
begin
    operate(r, b1, b2, false);
end;

procedure sub(var r : BigInt; var b1 : BigInt; var b2 : BigInt);
begin
    operate(r, b1, b2, true);
end;

function bit(var b : BigInt; index : Longint) : Byte;
begin
    setToStart(b);
    while (not atEnd(b)) and (index > 0) do
    begin
        rewind(b);
        if index > b.itSteps then
        begin
            index := index - b.itSteps;
            b.itSteps := 0;
        end
        else
        begin
            b.itSteps := b.itSteps - index;
            index := 0;
        end;
    end;
    bit := 0;
    if not atEnd(b) then
    begin 
        rewind(b);
        bit := b.itValue;
    end;
end;

procedure makePow(var b : BigInt; k : Longint);
begin
    b.size := 0;
    push(b, k, 0);
    push(b, 1, 1);
end;

BEGIN
{ test code for addition and subtraction
    for i := 10020 to 10030 do
    begin
        for j := 10000 to 10010 do
        begin
            writeln('Test ', i, ' ', j);
            ofInt(tmpBB, i);
            ofInt(tmpBB2, j);
            setToStart(tmpBB);
            setToStart(tmpBB2);
            sub(N, tmpBB, tmpBB2);
            ofInt(ls, i - j);
            writeBigInt(N);
            writeBigInt(ls);
        end;
    end;
    }

    sz := readBigInt(N);
    ofInt(tmpBB, (N.size + 1) div 2);
    setToStart(tmpBB); setToStart(N); step(N, 1); add(ps, tmpBB, N);

    if bit(N, sz - 2) = 0 then
    begin
        makePow(tmpBB, sz - 2);
        setToStart(N); setToStart(tmpBB); sub(tmpBB2, N, tmpBB);
        ofInt(tmpBB, 1);
        setToStart(tmpBB); setToStart(tmpBB2); add(ls, tmpBB, tmpBB2);
    end else
    begin
        makePow(ls, sz - 1);
    end;

    setToStart(ps); setToStart(ls); add(tmpBB, ps, ls);
    ofInt(tmpBB2, sz);
    setToStart(tmpBB); setToStart(tmpBB2); sub(ps, tmpBB, tmpBB2);

    writeBigInt(ps);
END.
