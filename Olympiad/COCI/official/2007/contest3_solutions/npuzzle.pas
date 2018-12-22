
/*
  Croatian Open Competition in Informatics 2006/2007
  Contest 3 - Task NPUZZLE
  Programming language Pascal
*/

program npuzzle;

var
   a : array[1..4,1..5] of char;
   b : array[1..4,1..5] of char;
   i, razbacanost : integer;
   r1, s1 : integer;
   r2, s2 : integer;

begin
   b[1] := 'ABCD';
   b[2] := 'EFGH';
   b[3] := 'IJKL';
   b[4] := 'MNO#';

   for i := 1 to 4 do readln( a[i] );

   razbacanost := 0;

   for r1 := 1 to 4 do
      for s1 := 1 to 4 do
         for r2 := 1 to 4 do
            for s2 := 1 to 4 do
               if a[r1,s1] = b[r2,s2] then
                  razbacanost := razbacanost + abs(r1-r2) + abs(s1-s2);

   writeln( razbacanost );
end.
