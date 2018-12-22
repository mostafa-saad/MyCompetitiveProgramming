
(*
  Croatian Open Competition in Informatics 2006/2007
  Contest 4 - Task ZBRKA
  Programming language Pascal
*)

program zbrka;

const maxk = 10001;
const mmod = 1000000007;

var
	 sad, prije: integer;
    n, k, i, j, tmp: longint;
    dp: array[0..1,0..maxk] of longint; (* koristimo samo dva retka matrice *)

begin
    readln( n, k );

    dp[1][0] := 1;
    for i := 2 to n do begin
        tmp := 0;
		  prije := (i-1) mod 2;
		  sad := i mod 2;
        for j := 0 to k do begin
            tmp := (tmp + dp[ prije, j ]) mod mmod;
            if( j >= i ) then tmp := (tmp - dp[ prije, j-i ] + mmod ) mod mmod;
            dp[ sad, j ] := tmp;
        end;
    end;

    writeln( dp[ n mod 2, k ] );
end.
