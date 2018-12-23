(*
 * Approved solution of the task "Football league"
 * Author: Jakub Radoszewski, 2004.05.27
 *)

var 
  i, k, l, n : Integer;


{This function gets the number of turn and the number of team, both in the
range between 0 and n-2 and counts the number of the team which should
play with team i-th in the k-th turn}
function p(k,i : Integer) : Integer;
var
  j : Integer;
begin
  j := (k - i) mod (n - 1);
  if j < 0 then 
    j := j + n - 1;
  if i <> j then
    p := j
  else
    p := n - 1
end; {p}


{This procedure counts and writes the solution}
procedure write_solution;
begin
  for k := 0 to n - 2 do
  begin
    l := (k + 1) div 2;
    for i := 0 to n div 2 - 1 do
    begin
      if odd(k) then 
        Write(p(k,l + i) + 1,' ',l + i + 1)
      else
        Write(l + i + 1,' ',p(k,l + i) + 1);
      if i < n div 2 - 1 then
        write(' ')
    end; {for}
    WriteLn;
  end {for}
end; {write_solution}


begin
  ReadLn(n);
  WriteLn(n-2);
  write_solution;
end. {program}
