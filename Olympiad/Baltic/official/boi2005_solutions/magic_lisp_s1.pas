{
TASK: LISP
LANG: PASCAL
}
{$MODE TP}
program magic;
  const DF = 'LISP.IN';
        RF = 'LISP.OUT';

  var f: text;

  procedure spresti (N: longint;
                     var gerai: boolean; var ml, M: longint);
    var as, i: longint;
        c: char;
  begin
    as := 0; { atidarantys skliaustai }
    ml := 0; { paskutinysis uþdarantis magiðkas - kelis paprastus skl. atitinka }
    M := 0; { kiek viso yra magiðkø skliaustø }
    gerai := true;
    i := 1;
    while (i <= N) and gerai do
      begin
        if i mod 72 = 0
           then readln (f, c)
           else read (f, c);
        case c of
         '(': as := as + 1;
         ')': if as > 0
                 then as := as - 1
                 else if ml > 1
                         then ml := ml - 1
                         else gerai := false;
          ']': begin
                 M := M + 1;
                 if (as > 0) or (ml > 1)
                    then begin
                           if M = 1 { pirmasis rastas ']' }
                              then ml := as
                              else ml := ml - 1 + as;
                           as := 0;
                         end
                    else gerai := false;
               end;
           end;
        i := i + 1;
      end;
    gerai := gerai and (as = 0) and (ml > 0);
  end; { spræsti }

  procedure spausdinti (gerai: boolean; ml, M: longint);
    var i: longint;
  begin
    assign (f, RF);
    rewrite (f);
    if not gerai
       then writeln (f, 0)
       else begin
              writeln (f, 1);
              for i := 1 to M - 1 do
                 writeln (f, 1);
              writeln (f, ml);
            end;
    close (f);
  end; { spausdinti }

  var N, ml, M: longint;
      gerai: boolean;
begin
  assign (f, DF);
  reset (f);
  readln (f, N);
  spresti (N, gerai, ml, M);
  close (f);
  spausdinti (gerai, ml, M);
end.
