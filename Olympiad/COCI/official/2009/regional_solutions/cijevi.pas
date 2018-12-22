program cijevi;

const MAXR = 25;
const MAXS = 25;

var
   R, S, i, j : longint;
   a : array[1..MAXR, 1..MAXS+1] of char;

function lijevo( i, j : longint ) : boolean;
begin
   if (j > 1) and ((a[i,j-1]='+') or (a[i,j-1]='-') or (a[i,j-1]='1') or (a[i,j-1]='2')) then lijevo := true else lijevo := false;
end;
function desno( i, j : longint ) : boolean;
begin
   if (j < S) and ((a[i,j+1]='+') or (a[i,j+1]='-') or (a[i,j+1]='3') or (a[i,j+1]='4')) then desno := true else desno := false;
end;
function gore( i, j : longint ) : boolean;
begin
   if (i > 1) and ((a[i-1,j]='+') or (a[i-1,j]='|') or (a[i-1,j]='1') or (a[i-1,j]='4')) then gore := true else gore := false;
end;
function dolje( i, j : longint ) : boolean;
begin
   if (i < R) and ((a[i+1,j]='+') or (a[i+1,j]='|') or (a[i+1,j]='2') or (a[i+1,j]='3')) then dolje := true else dolje := false;
end;

begin
   readln( R, S );
   for i := 1 to R do readln( a[i] );
   
   for i := 1 to R do begin
      for j := 1 to S do begin
         if a[i,j] <> '.' then continue;

         if lijevo(i,j) and desno(i,j) and gore(i,j) and dolje(i,j) then writeln( i, ' ', j, ' +' )
         else if lijevo(i,j) and desno(i,j) then writeln( i, ' ', j, ' -' )
         else if   gore(i,j) and dolje(i,j) then writeln( i, ' ', j, ' |' )
         else if  desno(i,j) and dolje(i,j) then writeln( i, ' ', j, ' 1' )
         else if  desno(i,j) and  gore(i,j) then writeln( i, ' ', j, ' 2' )
         else if lijevo(i,j) and  gore(i,j) then writeln( i, ' ', j, ' 3' )
         else if lijevo(i,j) and dolje(i,j) then writeln( i, ' ', j, ' 4' );
      end;
   end;  
end.
