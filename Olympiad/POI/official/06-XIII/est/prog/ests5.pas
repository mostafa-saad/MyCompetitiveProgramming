(*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: EST (Estetyczny Tekst)                         *
 *   Plik:                ests5.pas                                      *
 *   Autor:               Jakub Radoszewski                              *
 *   Opis:                Rozwiazanie nieoptymalne.                      *
 *                        Obliczana jest tylko wynikowa tablica, a       *
 *                        pozostale na jej podstawie.                    *
 *                        Zlozonosc: O(n^3) (z usprawnieniami)           *
 *                                                                       *
 *************************************************************************)

const INF : Int64 = 2000000000;
const MAX_N = 2100;

var
  tab : array[0..MAX_N] of LongInt;
  mniejsze, wieksze, wynik : array[0..MAX_N, 0..MAX_N] of Int64;
  n, i, dod, od, q : LongInt;
  mini, m, poprz : LongInt;


function suma(z1, z2 : LongInt) : LongInt;
begin
	if z1 = 0 then
    suma := tab[z2]
  else
	  suma := tab[z2] - tab[z1 - 1]
end; {suma}

function min(a, b : Int64) : Int64;
begin
  if a < b then
    min := a
  else
    min := b
end; {min}

begin
  ReadLn(m, n);
	for i := 0 to n - 1 do
  begin
		Read(tab[i]);
		Inc(tab[i]);
		if i <> 0 then
      Inc(tab[i], tab[i - 1])
	end; {for}
	Inc(m);

  for dod := 0 to n - 1 do
  begin
		mniejsze[0][dod] := INF;
		wieksze[0][dod] := INF;
		wynik[0][dod] := INF;
		if suma(0, dod) <= m then
    begin
			mniejsze[0][dod] := suma(0, dod);
			wieksze[0][dod] := -suma(0, dod);
			wynik[0][dod] := Int64(0)
		end {if}
	end; {for}

  for dod := 1 to n - 1 do
  begin
    for od := 1 to dod do
    begin
			wynik[od][dod] := INF;
			if suma(od, dod) <= m then
      begin
				for poprz := 0 to od - 1 do
  				if suma(poprz, od - 1) <= m then
          begin
	  				if suma(od, dod) <= suma(poprz, od - 1) then
		  				wynik[od][dod] := min(wynik[od][dod], mniejsze[poprz][od - 1]
                                                    - suma(od, dod));
				  	if suma(od, dod) >= suma(poprz, od - 1) then
					  	wynik[od][dod] := min(wynik[od][dod], wieksze[poprz][od - 1]
                                                    + suma(od, dod))
        end {for}
			end {if}
		end; {for}
    for od := 1 to dod do
    begin
			mniejsze[od][dod] := min(INF, wynik[od][dod] + suma(od, dod));
			mniejsze[od][dod] := min(mniejsze[od][dod], mniejsze[od - 1][dod])
		end; {for}
    for od := dod downto 1 do
    begin
			wieksze[od][dod] := min(INF, wynik[od][dod] - suma(od, dod));
			if od <> dod then
				wieksze[od][dod] := min(wieksze[od][dod], wieksze[od + 1][dod])
		end {for}
	end; {for}
  
	mini := INF;
  for i := 0 to n - 1 do
    mini := min(mini, wynik[i][n - 1]);
  WriteLn(mini)
end. {program}
