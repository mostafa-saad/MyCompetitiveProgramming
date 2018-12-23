(*
 * An alternative correct and optimal solution for the task Football league
 * Author: Jakub Radoszewski
 *)

const
  MAX_N=1000;

var
  t : array[1..MAX_N] of Integer;
  n, i, j : Integer;
  head, tail : Integer;

function next(index : Integer) : Integer;
begin
  if index = n - 1 then
    next := 1
  else
    next := index + 1;
end; {next}


begin
  Read(n);
  WriteLn(n-2);
  for i := n div 2 + 1 to n - 1 do
    t[i - n div 2] := i;

  {The first round is very simple, and also the odd one, so it is considered
  separately}
  Write('1 ',n,' ');
  for i := 2 to n div 2 do
  begin
    Write(i,' ',t[n div 2 + 1 - i]);
    if i < n div 2 then
      Write(' ')
    else
      WriteLn
  end; {for}
  
  head := 1;
  tail := n div 2 - 1;
  
  {And now we create the remaining (n/2)-1 rounds in pairs}
  for i := 1 to n div 2 - 1 do
  begin
    t[tail + 1] := next(t[tail]);
    Inc(head);
    Inc(tail);

    {The first round of two}
    for j := 1 to n div 2 - 1 do
      Write(t[tail + 1 - j],' ',i + j,' ');
    WriteLn(n,' ',i + n div 2);

    {The second round of two}
    Write(i + 1,' ',n,' ');
    for j := 1 to n div 2 - 1 do
    begin
      Write(i + j + 1,' ',t[tail + 1 - j]);
      if j <> n div 2 - 1 then
        Write(' ')
      else
        WriteLn
    end {for}
  end {for}
end {program}.
