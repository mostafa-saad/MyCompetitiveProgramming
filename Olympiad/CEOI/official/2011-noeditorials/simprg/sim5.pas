(* Verification solution for the task SIM (Similarity)
 * Author: Jakub Radoszewski
 * Date: July 2011
 * Imlementation as in the CEOI 2011 booklet.
 *)

var
  p, t : AnsiString;
  n, m, i : LongInt;
  similarity : Int64;
  a : array['a' .. 'z'] of LongInt;
  ch : Char;

begin
  ReadLn(p);
  ReadLn(t);
  n := Length(p);
  m := Length(t);

  for ch := 'a' to 'z' do
    a[ch] := 0;

  similarity := 0;
  for i := 1 to m do
  begin
    if i <= n then
      a[p[i]] := a[p[i]] + 1;
    similarity := similarity + a[t[i]];
    if i >= m - n + 1 then
      a[p[n - m + i]] := a[p[n - m + i]] - 1;
  end;

  WriteLn(similarity);
end.
