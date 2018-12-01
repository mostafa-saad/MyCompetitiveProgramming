{
TASK: LISP
LANG: PASCAL
}
program Magic_Parenthesis_solution;

var
  data, answer: text;
  n, m, i, brackets, magic_br: longint;
  br: string;

procedure bad;
begin
  close(answer);
  rewrite(answer);
  writeln(answer, 0);
  close(answer);
  halt;
end;

begin
  assign(data, 'LISP.IN'); reset(data);
  readln(data, n, m);

  assign(answer, 'LISP.OUT'); rewrite(answer);
  writeln(answer, 1);
  brackets := 0; magic_br := 0;
  for i := 1 to n do
  begin
    if i mod 72 = 1 then
      readln(data, br);
    case br[(i - 1) mod 72 + 1] of
      '(': inc(brackets);
      ')': dec(brackets);
      ']':
      begin
        if magic_br + 1 < m then
          writeln(answer, 1);
        dec(brackets);
        inc(magic_br);
      end;
    end;
    if brackets < 0 then
      bad();
  end;
  writeln(answer, brackets + 1);

  close(data); close(answer);
end.
