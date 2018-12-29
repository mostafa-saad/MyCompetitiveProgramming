(*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Inspektor                                     *
 *   Autor:                Marcin Andrychowicz                           *
 *   Zlozonosc czasowa:    O(n^2 * m * log m)                            *
 *   Zlozonosc pamieciowa: O(m)                                          *
 *   Opis:                 Rozwiazanie wolne                             *
 *                                                                       *
 *************************************************************************)

program zbrs5;

const MAXN = 307;
const INF = MAXN * 2;

var
i,j,m,p,test,tests,N,M3,MM,binl,binr,wolni,ll,rr : Integer;
T,K,II,l,r,X,wol : array[0..MAXN] of Integer;
dp : array[0..MAXN+1,0..MAXN+1,0..MAXN+1] of Integer;
ok : Boolean;

function min(a, b : Integer) : Integer;
begin
	if a < b then
		min := a
	else
		min := b;
end;

function max(a, b : Integer) : Integer;
begin
	if a > b then
		max := a
	else
		max := b;
end;

procedure set_max(i, m, p, v : Integer);
begin
	if dp[i][m][p] < v then
		dp[i][m][p] := v;
end;

begin
	Read(tests);
	for test := 1 to tests do
	begin
		Read(N);
		read(MM);
		for i := 1 to MM do
		begin
			Read(T[i]);
			Read(K[i]);
			Read(II[i]);
		end;

		binl := 1;
		binr := MM;
		while binr > binl do
		begin

			M3 := (binl + binr + 1) div 2;
			ok := True;
			for i := 0 to MM+1 do
			begin
				X[i] := INF;
				l[i] := 0;
				r[i] := 0;
			end;

			for i := 1 to M3 do
			begin
				if X[T[i]] = INF then
					X[T[i]] := II[i] + 1
				else if not(X[T[i]] = II[i] + 1) then
					ok := False;
			end;

			wolni := 0;
			for i := 1 to N do
			begin
				ll := MM + 1;
				rr := 0;
				for j := 1 to M3 do
					if K[j] = i then
					begin
					 ll := min(ll, T[j]);
					 rr := max(rr, T[j]);
					end;
				if rr = 0 then
					wolni := wolni + 1
				else
				begin
					for j := ll to rr do
					begin
						X[j] := X[j] - 1;
						if X[j] < 0 then
							ok := False;
					end;	
					l[ll] := l[ll] + 1;
					r[rr] := r[rr] + 1;
				end;
			end;

			for i := 0 to MM+1 do
				for m := 0 to N do
					for p := 0 to N do
						dp[i][m][p] := -1;
			dp[0][0][0] := wolni;

			if ok then
				for i := 0 to MM+1 do
				begin
					if i > 0 then
						for m := 0 to N do
							for p := 0 to N do
								set_max(i, min(m+r[i-1],N), max(p-l[i],0), dp[i-1][m][p]);
					for m := 0 to N do
						for p := 0 to N do
						begin
							set_max(i, m+1, p, dp[i][m][p] - 1);
							set_max(i, m, p+1, dp[i][m][p]);
						end;
					for m := N downto 1 do
						for p := 0 to N do
							set_max(i, m-1, p, dp[i][m][p]);
					if X[i] < INF/2 then
						for m := 0 to N do
							for p := 0 to N do
								if not(m + p = X[i]) then
									dp[i][m][p] := -1;
				end;

			if dp[MM+1][0][0] < 0 then
				ok := False;
			
			if ok then
				binl := M3
			else
				binr := M3-1;

		end;
		Writeln(binl);
	end;
end.


			// X
			if(X[i] < INF/2)
				for(int m=0; m<=N; m++)
					for(int p=0; p<=N; p++)
						if(m + p != X[i])
							dp[i][m][p] = -1;
		}

		if(dp[MM+1][0][0] < 0)
			ok = false;

		if(ok)
			binl = M;
		else
			binr = M-1;
	}

	cout << binr << endl;
	}
}
