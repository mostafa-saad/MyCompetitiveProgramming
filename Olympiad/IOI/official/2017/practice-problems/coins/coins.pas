unit coins;

interface
type
    TIntArray = array of longint;

function coin_flips(b: TIntArray; c: longint): TIntArray;
function find_coin(b: TIntArray): longint;

implementation

function coin_flips(b: TIntArray; c: longint): TIntArray;
var
    flips: TIntArray;
    i, x: longint;
begin
    x := 0;
    for i := 0 to 63 do
    begin
        x := x xor (b[i] * i);
    end;
    setLength(flips, 1);
    flips[0] := c xor x;
	coin_flips := flips;
end;

function find_coin(b: TIntArray): longint;
var
    x, i: longint;
begin
    x := 0;
    for i := 0 to 63 do
    begin
        x := x xor (b[i] * i);
    end;
    find_coin := x;
end;

end.