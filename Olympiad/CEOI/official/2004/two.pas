{Lukasz Kowalik, 29/04/2004
 Model solution, O(n logn) time complexity)
}

const
  MAX_N = 20000;
  MAX_COST = 2000000000;

var
  n : LongInt; {number of trees}

  Distance : array [1..MAX_N+1] of LongInt;
  {Distance [i] = distance from the first tree to i-th tree; (n+1)-three = the sawmill in the valley}

  Weight : array [1..MAX_N] of LongInt; {Weight [i] = Sum of wight of trees from 1 to i}

  TotalCost : LongInt; {Cost of transportation when there is only one sawmill in the valley}
  MinCost : LongInt;   {The smallest cost found so far}


procedure ReadData;
var
  i : LongInt;
  d, w : LongInt;
begin
  ReadLn (n);

  Distance [1] := 0;
  ReadLn (Weight [1], Distance [2]);
  TotalCost := Weight [1] * Distance [2];

  for i := 2 to n do
  begin
    ReadLn (w, d);
    Weight [i] := Weight [i-1] + w;
    Distance [i+1] := Distance [i] + d;
    TotalCost := TotalCost + Weight [i] * d;
  end;
end;

function Min (a, b : LongInt) : LongInt;
begin
  if a <= b then Min := a else Min := b;
end;

{Computing the cost of transportation when the sawmills are placed in positions i, j.}
function GetCost (i, j : LongInt) : LongInt;
begin
  GetCost := TotalCost
          - Weight [i] * (Distance [j] - Distance [i])
          - Weight [j] * (Distance [n+1] - Distance [j]);
end;

{finds minimal cost when first sawmill is placed between MinPos1 and MaxPos1
 and the second one between MinPos2 and MaxPos2}
procedure Solve (MinPos1, MaxPos1, MinPos2, MaxPos2 : LongInt);
var
  i, j, Cost, Opt, OptCost : LongInt;
begin
  if MinPos1 >= MinPos2 then MinPos2 := MinPos1 + 1;
  if MaxPos1 >= MaxPos2 then MaxPos1 := MaxPos2 - 1;

  if (MinPos1 > MaxPos1) or (MinPos2 > MaxPos2) then Exit;

  {1. We compute optimal cost when the second sawmill is placed in (MinPos2 + MaxPos2) div 2}
    
  OptCost := MAX_COST + 1;
  j := (MinPos2 + MaxPos2) div 2;
  for i := MinPos1 to Min (MaxPos1, j - 1) do
  begin
    Cost := GetCost (i, j);
    if Cost < OptCost then
    begin
      Opt := i;
      OptCost := Cost;
    end;
  end;
   
  if OptCost < MinCost then MinCost := OptCost;

  {2. Let Opt(j) denote the optimal position of the higher sawmill when the lower
      one is located at $j$-th tree.
      
      We know that Opt (j) <= Opt for j < (MinPos2 + MaxPos2) div 2,
                   Opt (j) >= Opt for j > (MinPos2 + MaxPos2) div 2}

  Solve (MinPos1, Opt, MinPos2, (MinPos2 + MaxPos2) div 2 - 1);
  Solve (Opt, MaxPos1, (MinPos2 + MaxPos2) div 2 + 1, MaxPos2);

end;

begin
  ReadData;
  MinCost := MAX_COST + 1;
  Solve (1, n - 1, 2, n);
  WriteLn (MinCost);
end.
