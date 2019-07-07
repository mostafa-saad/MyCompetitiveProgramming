unit cup;

interface
uses graderlib;

function find_cup(): TIntArray;

implementation

const
    maxn: longint = 500 * 1000 * 1000;
    one: int64 = 1;

var
    x, tmp, tmp1, y: int64;

function same(k: int64): boolean;
var
    help: int64;
begin
    help := (one shl 33) - one - (one shl k);
    same := (tmp and help) = (tmp1 and help);
end;

function f(k: int64): int64;
var
    i: longint;
begin
    for i := 33 downto 0 do
    begin
        if ((k shr i) and 1) = 1 then
        begin
            f := one shl i;
            exit;
        end;
    end;
    f := 0;
end;

function find_cup(): TIntArray;
var
    i: longint;
    k: int64;
    result: TIntArray;
begin
    x := 0;
    y := 0;
    tmp1 := 0;
    tmp := ask_shahrasb(-2 * maxn, -maxn);

    for i := 0 to 30 do
    begin
        k := one shl i;
        tmp1 := ask_shahrasb(-2 * maxn + k, -maxn);
        if same(i) then
            y := y + (k xor (tmp and k))
        else
            y := y + (tmp and k);
    end;

    x := y xor tmp;

    if -2 * maxn + x > maxn then
        x := x - f(x);
        
    setlength(result, 2);
    result[0] := -2 * maxn + x;
    result[1] := -maxn + (tmp xor x);
    find_cup := result;
end;

end.
