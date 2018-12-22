program kocke;

type coords = record x, y : integer end;

function makeCoords( x, y : integer ) : coords;
begin
   makeCoords.x := x;
   makeCoords.y := y;
end;

const target_x : array[1..5] of integer = ( 8, 7, 7, 7, 6 );
const target_y : array[1..5] of integer = ( 8, 8, 7, 6, 8 );

const dd : array[1..4] of char = ( 'L', 'U', 'R', 'D' );
const dx : array[1..4] of integer = ( -1, 0, 1, 0 );
const dy : array[1..4] of integer = ( 0, 1, 0, -1 );

type state = record robot, cube : coords end;

var
   cookie        : array[-8..8,-8..8,-8..8,-8..8] of integer;
   howDirection  : array[-8..8,-8..8,-8..8,-8..8] of integer;
   howState      : array[-8..8,-8..8,-8..8,-8..8] of state;
   currentCookie : integer;

   queue : array[0..99999] of state;
   head, tail : longint;

   robot, P : coords;
   cubes : array[1..5] of coords;
   cross : boolean;
   i, j, x, y, fifth : integer;

procedure queuePush( S : state );
begin
   queue[tail] := S;
   inc(tail);
   if tail = 100000 then tail := 0;
end;
function queuePop : state;
begin
   queuePop := queue[head];
   inc(head);
   if head = 100000 then head := 0;
end;

procedure reconstruct( S : state );
begin
   if howDirection[S.robot.x][S.robot.y][S.cube.x][S.cube.y] = 0 then exit;

   reconstruct( howState[S.robot.x][S.robot.y][S.cube.x][S.cube.y] );
   write( dd[howDirection[S.robot.x][S.robot.y][S.cube.x][S.cube.y]] );
end;

procedure move( A : integer; destination : coords );
var
   S, T : state;
   i, d, d2 : integer;
   ok : boolean;
begin
   S.robot := robot;
   S.cube := cubes[A];

   inc(currentCookie);
   cookie[S.robot.x][S.robot.y][S.cube.x][S.cube.y] := currentCookie;
   howDirection[S.robot.x][S.robot.y][S.cube.x][S.cube.y] := 0;

   head := 0;
   tail := 0;

   queuePush( S );

   while true do begin
      S := queuePop;

      for d := 1 to 4 do begin
         T := S;
         T.robot.x := T.robot.x + dx[d];
         T.robot.y := T.robot.y + dy[d];
         if (T.robot.x < -8) or (T.robot.x > 8) then continue;
         if (T.robot.y < -8) or (T.robot.y > 8) then continue;

         ok := true;
         for i := 1 to 5 do begin
            if i = A then continue;
            if (T.robot.x = cubes[i].x) and (T.robot.y = cubes[i].y) then ok := false;
         end;
         if not ok then continue;

         if (T.robot.x = T.cube.x) and (T.robot.y = T.cube.y) then begin
            T.cube.x := T.cube.x + dx[d];
            T.cube.y := T.cube.y + dy[d];
            if (T.cube.x < -8) or (T.cube.x > 8) then continue;
            if (T.cube.y < -8) or (T.cube.y > 8) then continue;

            if (T.cube.x = destination.x) and (T.cube.y = destination.y) then begin
               howDirection[T.robot.x][T.robot.y][T.cube.x][T.cube.y] := d;
               howState[T.robot.x][T.robot.y][T.cube.x][T.cube.y] := S;

               cubes[A] := destination;
               robot := T.robot;

               reconstruct( T );

               exit;
            end;

            for d2 := 1 to 4 do begin
               for i := 1 to 5 do begin
                  if i = A then continue;
                  if (T.cube.x + dx[d2] = cubes[i].x) and (T.cube.y + dy[d2] = cubes[i].y) then ok := false;
               end;
            end;

            if not ok then continue;
         end;

         if cookie[T.robot.x][T.robot.y][T.cube.x][T.cube.y] = currentCookie then continue;
         cookie[T.robot.x][T.robot.y][T.cube.x][T.cube.y] := currentCookie;
         howDirection[T.robot.x][T.robot.y][T.cube.x][T.cube.y] := d;
         howState[T.robot.x][T.robot.y][T.cube.x][T.cube.y] := S;
         queuePush( T );
      end;
   end;
end;

function peek( x, y : integer ) : integer;
var
   i : integer;
begin
   for i := 1 to 5 do begin
      if (cubes[i].x = x) and (cubes[i].y = y) then begin
         peek := i;
         exit;
      end;
   end;
   peek := 0;
end;

function neighbourCount( x, y : integer ) : integer;
var
   d, i, ret : integer;
begin
   ret := 0;
   for d := 1 to 4 do
      for i := 1 to 5 do
         if (cubes[i].x = x + dx[d]) and (cubes[i].y = y + dy[d]) then
            inc(ret);
   neighbourCount := ret;
end;

begin
   robot.x := 0;
   robot.y := 0;
   for i := 1 to 5 do readln( cubes[i].x, cubes[i].y );

   for i := 1 to 5 do
      for j := 2 to 5 do
         if cubes[i].x > cubes[j].x then begin
            P := cubes[i];
            cubes[i] := cubes[j];
            cubes[j] := P;
         end;

   cross := false;
   for x := -5 to 5 do
      for y := -5 to 5 do
         if neighbourCount( x, y ) = 4 then begin
            P := makeCoords( x, y );
            cross := true;
         end;

   if cross and ((P.x <> 0) or (P.y <> 0)) then begin
      move( peek( P.x, P.y+1 ), P );

      fifth := 0;
      for i := 1 to 5 do
         if (abs( P.x - cubes[i].x ) >= 2) or (abs( P.y - cubes[i].y ) >= 2) then
            fifth := i;

      move( fifth, makeCoords( P.x, P.y-2 ) );
   end else begin
      if cross then
         if peek( 0, 3 ) = 0 then
            move( peek( 0, 1 ), makeCoords( 0, 2 ) )
         else
            move( peek( 1, 0 ), makeCoords( 2, 0 ) );

      for i := 1 to 5 do
         move( i, makeCoords( target_x[i], target_y[i] ) );
   end;
   writeln;
end.
