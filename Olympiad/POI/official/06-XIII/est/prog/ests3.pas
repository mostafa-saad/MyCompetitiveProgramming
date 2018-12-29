(*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: EST (Estetyczny Tekst)                         *
 *   Plik:                ests3.pas                                      *
 *   Autor:               Jakub Radoszewski                              *
 *   Opis:                Rozwiazanie nieoptymalne.                      *
 *                        Programowanie dynamiczne O(n^3), dodatkowo     *
 *                        kazda tablica jest wyliczana osobno.           *
 *                                                                       *
 *************************************************************************)

const MAX_N = 2100;
const INF = 2000000000;

var
  tab : array[0..MAX_N] of LongInt;
  mniejsze, wieksze, wynik : array[0..MAX_N, 0..MAX_N] of LongInt;
  n, m, i, dod, od, poprz, mini : LongInt;


function suma(z1, z2 : LongInt) : LongInt;
begin
	if z1 = 0 then
    suma :=tab[z2]
  else
  	suma := tab[z2] - tab[z1 - 1]
end; {suma}

function min(a, b : LongInt) : LongInt;
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
			wynik[0][dod] := 0
		end {if}
	end; {for}

	
	(* Kazda tablice wyliczamy osobno *)
  for od := 1 to n - 1 do
    for dod := od to n - 1 do
    begin
			mniejsze[od][dod] := INF;
			wieksze[od][dod] := INF;
			wynik[od][dod] := INF;
			if suma(od, dod) <= m then
      begin
        for poprz := 0 to od - 1 do
        begin
  				if suma(od, dod) <= suma(poprz, od - 1) then
          begin
	  				mniejsze[od][dod] := min(mniejsze[od][dod],
                                     mniejsze[poprz][od - 1]);
		  			wieksze[od][dod] := min(wieksze[od][dod], mniejsze[poprz][od - 1]
                                                      - 2 * (suma(od, dod)));
			  		wynik[od][dod] := min(wynik[od][dod], mniejsze[poprz][od - 1]
                                                  - suma(od, dod))
  				end; {if}
  				if (suma(od, dod) >= suma(poprz, od - 1)) then
          begin
	  				mniejsze[od][dod] := min(mniejsze[od][dod], wieksze[poprz][od - 1]
                                                        + 2 * suma(od, dod));
		  	  	wieksze[od][dod] := min(wieksze[od][dod], wieksze[poprz][od - 1]);
			  		wynik[od][dod] := min(wynik[od][dod], wieksze[poprz][od - 1]
                                                  + suma(od, dod))
  				end {if}
				end {for}
			end {if}
		end; {for}
    
	mini := INF;
	for i := 0 to n - 1 do
    mini := min(mini, wynik[i][n - 1]);

	WriteLn(mini)
end. {program}
