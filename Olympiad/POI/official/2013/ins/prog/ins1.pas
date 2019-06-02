(*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Inspektor                                     *
 *   Autor:                Marcin Andrychowicz                           *
 *   Zlozonosc czasowa:    O((n + m) log m)                              *
 *   Zlozonosc pamieciowa: O(m)                                          *
 *   Opis:                 Rozwiazanie wzorcowe                          *
 *                                                                       *
 *************************************************************************)

const MAXM = 100000; // maksymalna liczba zeznan

var
test,tests,i,j,N,m,l,r,q,spi,jest,przedwczesnie,moze : Longint;
T,K,II,pierwsze,ostatnie,przychodza,wychodza,X : array[0..MAXM+1] of Longint;
ok : Boolean;

function min(a, b : Longint) : Longint;
begin
  if a < b then
    min := a
  else
    min := b;
end;

function max(a, b : Longint) : Longint;
begin
  if a > b then
    max := a
  else
    max := b;
end;

begin
	Read(tests);
	for test := 1 to tests do
	begin
		Read(N);
		Read(M);
		for i := 1 to M do
		begin
			Read(T[i]);
			Read(K[i]);
			Read(II[i]);
		end;
		
		l := 1;
		r := M;
		while r > l do
		begin
			q := (l + r + 1) div 2;
			ok := True;

			for i := 1 to M do
			begin
				przychodza[i] := 0;
				wychodza[i] := 0;
				pierwsze[i] := M + 1;
				ostatnie[i] := 0;
				X[i] := 0;
			end;

			for i := 1 to q do
			begin
				pierwsze[K[i]] := min(pierwsze[K[i]], T[i]);
				ostatnie[K[i]] := max(ostatnie[K[i]], T[i]);
			end;
			for i := 1 to N do
				if ostatnie[i] > 0 then
				begin
					inc(przychodza[pierwsze[i]]);
					inc(wychodza[ostatnie[i]]);
				end;

			for i := 1 to q do
				if (X[T[i]] > 0) and (not(X[T[i]] = II[i] + 1)) then
					ok := False
				else
					X[T[i]] := II[i] + 1;

			spi := N;
			jest := 0;
			przedwczesnie := 0;
			moze := 0;

			for i := 1 to M do
				if (X[i] > 0) and ok then
				begin

					for j := 1 to przychodza[i] do
					begin
						if przedwczesnie > 0 then
							dec(przedwczesnie)
						else
							dec(spi);
						inc(jest);
					end;

				while X[i] > jest + przedwczesnie + moze do
				begin
					inc(przedwczesnie);
					dec(spi);
				end;
				if X[i] < jest then
					ok := False
				else
					while X[i] < jest + przedwczesnie + moze do
					begin
						if moze > 0 then
							dec(moze)
						else
							dec(przedwczesnie);
					end;

					for j := 1 to wychodza[i] do
					begin
						dec(jest);
						inc(moze);
					end;

					if spi < 0 then
						ok := False;

				end;

			if ok then
				l := q
			else
				r := q - 1;
		end;
		Writeln(l);
	end;
end.
