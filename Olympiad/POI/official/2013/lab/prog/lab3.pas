(*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Labirynt                                      *
 *   Autor:                Maciej Borsz                                  *
 *   Zlozonosc czasowa:    O(n)                                          *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wzorcowe                          *
 *                                                                       *
 *************************************************************************)

program lab;
type
    point = record
        x: longint;
        y: longint;
    end;
    Pboxlist = ^boxlist;
    Pbox = ^box;
    Ppoints = ^points;
    Ppointlist = ^pointlist;
    boxlist = record
        value: ^box;
        next: Pboxlist;
    end;
    pointlist = record
        value: point;
        next: Ppointlist;
    end;
    points = record
        last: Ppointlist;
        first: Ppointlist;
    end;
    box = record
        w: longint;
        h: longint;
        last : Pboxlist;
        first: Pboxlist;
    end;
const
    MAXN  = 1000007;
var
    str: ansistring;
    n: longint;
    part: array [1..4, 1..MAXN] of char;
    part_size: array[1..4] of longint;
    part_box: array[1..4] of Pbox;
    result: points;
function test: boolean;
var i, sum: longint;
begin
    sum := 0;
    for i:= 1 to n do
        if str[i] = 'L' then
            inc(sum)
        else
            dec(sum);
    test := (sum = 4);
end;

procedure partition;
    var stack: array[0..MAXN] of char;
    var stack_pos: array[0..MAXN] of longint;
    var S, i, j, del: longint;
begin
    for i:= 0 to MAXN do
        stack[i] := char(0);
    S := 0;
    del := 0;
    for i:= 1 to n do
        begin
            stack[S] := str[i];
            stack_pos[S] := i;
            inc(S);

            if (S = 1) and (stack[0] = 'P') then
                begin
                    dec(S);
                    inc(del);
                end;
            if (S >= 2) and (stack[S-1] = 'P') and (stack[S-2] = 'L') then
                begin
                    dec(S);
                    dec(S);
                end;
        end;
    S:= S - del;

    for i:= 1 to 4 do
        begin
            part_size[i] := 0;
            j := stack_pos[i-1];
            while j <> stack_pos[i mod 4] do begin
                inc(part_size[i]);
                part[i, part_size[i]] := str[j];
                j := (j mod n) + 1;
            end;
            inc(part_size[i]);
            part[i, part_size[i]] := 'P';
        end;

end;


procedure add_list(var obj: Pbox; child: Pbox);
begin
    if (obj^.last = nil) then
        begin
            new(obj^.last);
            obj^.first := obj^.last;
        end
    else begin
        new(obj^.last^.next);
        obj^.last := obj^.last^.next;
    end;
    obj^.last^.next := nil;
    obj^.last^.value := child;
end;


procedure add_point(child: point);
begin
    if (result.last = nil) then
        begin
            new(result.last);
            result.first := result.last;
        end
    else begin
        new(result.last^.next);
        result.last := result.last^.next;
    end;
    result.last^.next := nil;
    result.last^.value := child;
end;


function rec(i: longint; var p: longint): Pbox;
var child: Pbox;
begin
    new(rec);
    rec^.w := 2;
    rec^.h := 0;
    inc(p);

    while part[i,p] = 'L' do begin
        child := rec(i, p);
        add_list(rec, child);
        rec^.w := rec^.w + child^.h;
        rec^.h := rec^.h + child^.w;
    end;

    inc(p);

    if rec^.last = nil then
        rec^.h := 1;

end;

function max(a: longint; b: longint): longint;
begin
    if a > b then
        max := a
    else
        max := b
end;


function add(p: point; x, y, rot: longint): point;
begin
    rot := ( rot -1 ) mod 4;
    add := p;
    if rot = 0 then
        begin
            add.x := add.x + x;
            add.y := add.y + y;
    end else if rot = 1 then
        begin
            add.x := add.x + y;
            add.y := add.y - x;
    end else if rot = 2 then
        begin
            add.x := add.x - x;
            add.y := add.y - y;
        end
    else if rot = 3 then
        begin
            add.x := add.x - y;
            add.y := add.y + x;
        end;

end;

procedure draw(b: PBox; p: point; rot: longint);
var ptr: Pboxlist;
begin
    add_point(p);
    p := add(p, b^.w-1, 0, rot);
    if b^.last = nil then
        begin
            add_point(p);
            p := add(p, 0, -1, rot);
        end
    else begin
        ptr := b^.first;
        while ptr <> nil do begin
            draw(ptr^.value, p, rot+1);
            p := add(p, ptr^.value^.w, -ptr^.value^.h, rot+1);
            ptr := ptr^.next;
        end;
    end;
    add_point(p);
end;

procedure print;
var last, ptr, next: Ppointlist;
begin
    result.last^.next := result.first;
    ptr := result.first;
    last := result.last;
    next := ptr^.next;
    while True do begin
        if not (((last^.value.x = ptr^.value.x) and
                        (ptr^.value.x = next^.value.x))
            or ((last^.value.y = ptr^.value.y) and
                        (ptr^.value.y = next^.value.y))) then
            writeln(ptr^.value.x, ' ', - ptr^.value.y);

        if (ptr = result.last) then break;
        ptr := ptr^.next;
        last := last^.next;
        next := next^.next;
    end;
end;

procedure solve;
var i,j, edge: longint;
    p: point;
begin
    edge := 0;
    for i:= 1 to 4 do begin
        j := 1;
        part_box[i] := rec(i, j);
        edge := max(max(edge, part_box[i]^.h), part_box[i]^.w);
    end;
    p.x := 0;
    p.y := 0;
    for i:= 1 to 4 do begin
        p := add(p, edge-1, 0, i);
        draw(part_box[i], p, i);
        p := add(p, 1, 0, i);
    end;
end;
begin
    readln(str);
    n := length(str);

    if not test() then
        writeln('NIE')
    else begin
        partition;
        solve;
        print;
    end;
end.
