program reljef;

const MAXR = 100;
const MAXS = 100;

var 
	R, S, N, i, j, k: longint;
	a : array[1..MAXR,1..MAXS+1] of char;
   bio : array[1..MAXR,1..MAXS] of boolean;

   n_nakupina : longint;
   nakupina_r : array[1..MAXR*MAXS] of longint;
   nakupina_s : array[1..MAXR*MAXS] of longint;

function min( a, b : longint ) : longint;
begin
   if a < b then min := a else min := b;
end;
function max( a, b : longint ) : longint;
begin
   if a > b then max := a else max := b;
end;
   
procedure dfs( i, j : longint );
begin
   if (i < 1) or (i > R) then exit;
   if (j < 1) or (j > S) then exit;
   if a[i, j] = '.' then exit;
   if bio[i, j] then exit;
   bio[i, j] := true;
   
   n_nakupina := n_nakupina + 1;
   nakupina_r[n_nakupina] := i;
   nakupina_s[n_nakupina] := j;
   
   dfs( i-1, j );
   dfs( i+1, j );
   dfs( i, j-1 );
   dfs( i, j+1 );
end;

procedure srusi;
var
   i, j, k, rr, ss, padni : longint;
   najniza : array[1..MAXS] of longint;
begin
   for i := 1 to R do
      for j := 1 to S do
         bio[i,j] := false;

   for i := 1 to R do begin
      for j := 1 to S do begin
         if (a[i,j] = '.') or bio[i,j] then continue;
         
         n_nakupina := 1;
         dfs( i, j );

         for ss := 1 to S do najniza[ss] := 0;
         
         for k := 1 to n_nakupina do begin
            najniza[ nakupina_s[k] ] := max( najniza[ nakupina_s[k] ], nakupina_r[k] );
            a[nakupina_r[k], nakupina_s[k]] := '.';
         end;

         padni := R;         
         for ss := 1 to S do begin            
            if najniza[ss] = 0 then continue;
            rr := najniza[ss] + 1;
            while (rr <= R) and (a[rr,ss] = '.') do rr := rr + 1;           
            padni := min( padni, rr-najniza[ss]-1 );
         end;
         
         for k := 1 to n_nakupina do begin
            nakupina_r[k] := nakupina_r[k] + padni;
            a[nakupina_r[k], nakupina_s[k]] := 'x';
            bio[nakupina_r[k], nakupina_s[k]] := true;
         end;
      end;
   end;
end;

begin
   readln( R, S );
   for i := 1 to R do readln( a[i] );   

   readln( N );
   for k := 1 to N do begin
      read( i );
      i := R-i+1;      

      if k mod 2 = 1 then begin
         for j := 1 to S do         
            if a[i, j] = 'x' then begin
               a[i, j] := '.'; 
               break;
            end;
      end else begin
         for j := S downto 1 do 
            if a[i, j] = 'x' then begin
               a[i, j] := '.'; 
               break;
            end;
      end;
      
      srusi;
   end;

   for i := 1 to R do begin
      for j := 1 to S do
         write( a[i,j] );
      writeln;
   end;
end.