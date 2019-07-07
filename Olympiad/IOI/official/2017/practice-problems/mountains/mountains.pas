unit mountains;

interface

type 
	TIntArray = array of longint;

function maximum_deevs(y: TIntArray): longint;

implementation

type
    point = record
        x, y: int64;
    end;

var
    n, i, l, r, sum, last: longint;
    p: array [0..2005] of point;
    bn: point;
    dp: array [0..2005, 0..2005] of longint;

function ccw(a, b, c: point): int64;
begin
    ccw := (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
end;

function maximum_deevs(y: TIntArray): longint;
begin
    n := length(y);
    for i := 0 to n - 1 do
    begin
        p[i].y := y[i];
        p[i].x := i;
    end;
    for r := 1 to n do
    begin
        sum := 0;
        last := r - 1;
        bn.x := p[r - 1].x;
        bn.y := p[r - 1].y - 1;
        dp[r - 1][r] := 1;
        for l := r - 2 downto 0 do
        begin
            dp[l][r] := dp[l][r - 1];
            if ccw(p[l], bn, p[r - 1]) >= 0 then
            begin
                sum := sum + dp[l + 1][last];
                last := l;
                bn := p[l];
            end;
            if 1 + sum + dp[l][last] > dp[l][r] then
                dp[l][r] := 1 + sum + dp[l][last];
        end;
    end;
    maximum_deevs := dp[0][n];
end;

end.

