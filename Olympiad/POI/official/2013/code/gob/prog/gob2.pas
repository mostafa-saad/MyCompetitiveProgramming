(*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Gobeliny                                      *
 *   Autor:                Adam Polak                                    *
 *   Zlozonosc czasowa:    O(n^2)                                        *
 *   Opis:                 Rozwiazanie wzorcowe                          *
 *                                                                       *
 *************************************************************************)

program gob2;

const 
    EPS = 0.000000001;

const
    INF = 100000000.0;

type Point = record
    x, y: Double;
end;

type Line = record
    normal: Point;
    c: Double;
end;

var 
testCases : Integer;
n : Integer;
P : array[0..1000] of Point;
dark : array[0..1000] of Boolean;

function diff(a, b: Point) : Point;
begin
    diff.x := a.x - b.x;
    diff.y := a.y - b.y;
end;

function prod(a, b: Point) : Double;
begin
    prod := a.x * b.x + a.y * b.y;
end;

function mul(a: Point; k: Double) : Point;
begin
    mul.x := a.x * k;
    mul.y := a.y * k;
end;

function rot90(a: Point) : Point;
begin
    rot90.x := -a.y;
    rot90.y := a.x;
end;

function det(a, b: Point) : Double;
begin
    det := a.x * b.y - a.y * b.x;
end;

function convex(a, b, c: Point) : Boolean;
begin
    if det(diff(b,a),diff(c,b)) < -EPS then
        convex := true
    else
        convex := false;
end;

function pointInsideTriangle(x, a, b, c: Point) : Boolean;
begin
    if convex(a,b,x) and convex(b,c,x) and convex(c,a,x) then
        pointInsideTriangle := true
    else
        pointInsideTriangle := false;
end;

function cosine(i1, i2, x: Point) : Double;
begin
    cosine := det(diff(i2,i1),diff(x,i1)) / sqrt((x.x-i1.x)*(x.x-i1.x)+(x.y-i1.y)*(x.y-i1.y));
end;

function isBetter(i1, i2, best, cand: Point) : Boolean;
begin
    if cosine(i1,i2,best) < cosine(i1,i2,cand) then
        isBetter := true
    else
        isBetter := false;
end;

function makeLine(a, b: Point) : Line;
begin
    makeLine.normal := rot90(diff(b,a));
    makeLine.c := prod(makeLine.normal, a);
end;

function parallel(a, b: Line) : Boolean;
begin
    if abs(det(a.normal, b.normal)) < EPS then
        parallel := true
    else
        parallel := false;
end;

function intersect(a, b: Line) : Point;
begin
    intersect := mul(rot90(diff(mul(a.normal,b.c),mul(b.normal,a.c))),1/det(a.normal,b.normal))
end;

function isStarShaped() : Boolean;
var
line1, line2: Line;
v: Point;
l, h, tmp: Double;
ok: Boolean;
i, j: Integer;
begin

    for i := 0 to n-1 do
    begin
        line1 := makeLine(P[i], P[(i+1) mod n]);
        v := diff(P[(i+1) mod n], P[i]);
        l := -INF;
        h := INF;
        ok := true;
        for j := 0 to n-1 do if not (i = j) then
        begin
            line2 := makeLine(P[j], P[(j+1) mod n]);
            if parallel(line1, line2) then
            begin
                if prod(line2.normal, P[i]) > line2.c then ok := false;
            end
            else
            begin
                tmp := prod(v, intersect(line1, line2));
                if det(line1.normal, line2.normal) > 0 then
                begin
                    if tmp > l then l := tmp;
                end
                else
                begin
                    if tmp < h then h := tmp;
                end;
            end;
        end;
        if (l + EPS < h) and ok then Exit(true);
    end;

    isStarShaped := false;

end;

function singleTest() : Boolean;
var 
i, i1, i2, i3, best, temp: Integer;
found: Boolean;
buf: String;
allLight, allDark, allDark1, allDark2: Boolean;
line1, line2, line3: Line;
l, h, temp_d: Double;
v: Point;
begin
    Read(n);
    for i := 0 to n-1 do Read(P[i].x, P[i].y);
    Readln();
    for i := 0 to n-1 do
    begin
        Readln(buf);
        if buf = 'C' then
            dark[i] := true
        else
            dark[i] := false;
    end;

    allDark := true;
    allLight := true;
    for i := 0 to n-1 do
        if dark[i] then
            allLight := false
        else
            allDark := false;

    if allDark then Exit(false);

    if allLight then Exit(isStarShaped());

    while True do
    begin
        if n = 3 then Exit(false);

        found := false;
        for i1 := 0 to n-1 do
        begin
            i2 := (i1+1) mod n;
            i3 := (i2+1) mod n;
            if dark[i1] and dark[i2] and convex(P[i1], P[i2], P[i3]) then
            begin
                found := True;
                break;
            end;
        end;

        if not found then break;

        best := -1;

        for i := 0 to n-1 do
            if (not (i = i1)) and (not (i = i2)) and (not (i = i3)) and pointInsideTriangle(P[i], P[i1], P[i2], P[i3]) then
            begin
                if best = -1 then
                    best := i;
                if isBetter(P[i1], P[i2], P[best], P[i]) then
                    best := i;
            end;

        if best = -1 then
        begin
            for i := i2+1 to n-1 do
            begin
                P[i-1] := P[i];
                dark[i-1] := dark[i];
            end;
            n := n - 1;
            continue;
        end;
        
        i1 := i2;
        i2 := best;

        if i2 < i1 then
        begin
            temp := i1;
            i1 := i2;
            i2 := temp;
        end;

        allDark1 := true;
        allDark2 := true;
        
        for i := 0 to n-1 do
            if not dark[i] then
            begin
                if (i>=i1) and (i<i2) then
                    allDark1 := false
                else
                    allDark2 := false;
            end;

        if (not allDark1) and (not allDark2) then Exit(false);

        if allDark1 then
        begin
            for i := i2 to n-1 do
            begin
                P[i-(i2-i1-1)] := P[i];
                dark[i-(i2-i1-1)] := dark[i];
            end;
            dark[i1] := true;
            n := n - (i2-i1-1);
        end
        else
        begin
            for i := i1 to i2 do
            begin
                P[i-i1] := P[i];
                dark[i-i1] := dark[i];
            end;
            n := (i2-i1+1);
            dark[n-1] := true;
        end;

    end;

    for i := 0 to n-1 do if (dark[i]) and (dark[(i+1) mod n]) then Exit(false);
    
    for i := 0 to n-1 do if (dark[(i+1) mod n]) and (convex(P[i], P[(i+1) mod n], P[(i+2) mod n]) = convex(P[(i+1) mod n], P[(i+2) mod n], P[(i+3) mod n])) then Exit(false);

    i1 := 0;
    while not dark[i1] do i1 := i1+1;
    i2 := i1+1;
    while (i2<n) and (not dark[i2]) do i2 := i2+1;
    if i2 = n then
    begin
        line1 := makeLine(P[i1], P[(i1+1) mod n]);
        v := diff(P[(i1+1) mod n], P[i1]);
        l := -INF;
        h := INF;
        for i := 0 to n-1 do if not (i = i1) then
        begin
            line2 := makeLine(P[i], P[(i+1) mod n]);
            if parallel(line1, line2) then
            begin
                if prod(line2.normal, P[i1]) > line2.c then Exit(false);
            end 
            else
            begin
                temp_d := prod(v, intersect(line1, line2));
                if det(line1.normal, line2.normal) > 0 then
                begin
                    if temp_d > l then l := temp_d;
                end
                else
                begin
                    if temp_d < h then h := temp_d;
                end;
            end;
        end;
        if l + EPS > h then Exit(false);
    end
    else
    begin
        line1 := makeLine(P[i1], P[(i1+1) mod n]);
        line2 := makeLine(P[i2], P[(i2+1) mod n]);
        if parallel(line1, line2) then Exit(false);
        v := intersect(line1, line2);
        for i := 0 to n-1 do
        begin
            line3 := makeLine(P[i], P[(i+1) mod n]);
            if (dark[i]) and (abs(prod(line3.normal, v) - line3.c) > EPS) then Exit(false);
            if (not dark[i]) and (prod(line3.normal, v) > line3.c - EPS) then Exit(false);
        end;
    end;

    singleTest := true;
end;

begin
    Read(testCases);
    while testCases > 0 do
    begin
        if singleTest() then
            Writeln('TAK')
        else
            Writeln('NIE');
        testCases := testCases - 1;
    end;
end.
