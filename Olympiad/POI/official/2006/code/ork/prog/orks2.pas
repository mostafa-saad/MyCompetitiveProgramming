(*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: ORK (Orka)                                     *
 *   Plik:                orks2.pas                                      *
 *   Autor:               Marek Cygan                                    *
 *   Opis:                Rozwiazanie nieoptymalne, o zlozonosci:        *
 *                        obliczeniowej O(n*m*log(n+m))                  *
 *                        oraz pamieciowej O(n^2)                        *
 *                                                                       *
 *************************************************************************)

const MAX_N = 2000;                                     {maksymalny wymiar pola}
const INF = 2*MAX_N;                                    {maksymalna liczba skib}
var
  n, m : longint;                 {wymiary pola (liczba wierszy, liczba kolumn)}
  k : longint;                                             {wytrzymalosc szkapy}
  t : array [0 .. MAX_N-1, 0 .. MAX_N-1] of longint;             {trudnosc pola}
  (*suma trudnosci pol od danego pola w prawo do konca wiersza                *)
  prawo : array [0 .. MAX_N, 0 .. MAX_N] of longint;
  (*suma trudnosci pol od danego pola d dol do konca kolumny                  *)
  dol : array [0 .. MAX_N, 0 .. MAX_N] of longint;

(*wczytywanie danych wejsciowych*)
procedure czytaj;
var
  i, j : longint;
begin
  read(k, m, n);
  for i := 0 to n - 1 do
    for j := 0 to m - 1 do
      read(t[i][j]);
end;

procedure zamien(var a, b: longint);
var
  c : longint;
begin
  c := a;
  a := b;
  b := c;
end;

procedure transponuj;
var
  i, j : longint;
begin
  for i := 0 to n - 1 do
    for j := 0 to m - 1 do
      dol[i][j] := t[i][j];

  zamien(n, m);
  for i := 0 to n - 1 do
    for j := 0 to m - 1 do
      t[i][j] := dol[j][i];
end;

procedure licz_sumy;
var
  i, j : longint;
begin
  (*liczenie sum czesciowych*)
  for i := 0 to n do
  begin
    dol[i][m] := 0;
    prawo[i][m] := 0;
  end;

  for j := 0 to m do
  begin
    dol[n][j] := 0;
    prawo[n][j] := 0;
  end;

  for i := n - 1 downto 0 do
    for j := m - 1 downto 0 do
    begin
      dol[i][j] := t[i][j] + dol[i+1][j];
      prawo[i][j] := t[i][j] + prawo[i][j+1];
    end;
end;


(*czy da sie zaorac pole uprawne wykonujac dokladnie n ciec poziomych oraz    *
 *co najwyzej lewe_ciecia ciec lewych oraz co najwyzej prawe_ciecia ciec      *
 *prawych                                                                     *)
function mozna_zaorac(lewe_ciecia, prawe_ciecia : longint) : boolean;
var
  wa, wb, ka, kb : longint; (*aktualne wymiary pola: gorny wiersz,dolny wiersz*
                             *lewa kolumna, prawa kolumna                     *)
begin
  wa := 0;
  ka := 0;
  wb := n - 1;
  kb := m - 1;
  mozna_zaorac := true;
  while (wa <= wb) do
  begin
    if prawo[wa][ka] - prawo[wa][kb+1] <= k then
      (*mozna wykonac ciecie gorne  *)
      inc(wa)
    else
       if prawo[wb][ka] - prawo[wb][kb+1] <= k then
         (*mozna wykonac ciecie dolne*)
         dec(wb)
       else
         if (dol[wa][kb] - dol[wb+1][kb] <= k) and (prawe_ciecia > 0) then
         begin
           (*mozna wykonac ciecie prawe*)
           dec(kb);
           dec(prawe_ciecia);
         end else
            if (dol[wa][ka] - dol[wb+1][ka] <= k) and (lewe_ciecia > 0) then
            begin
              (*ciecie lewe*)
              inc(ka);
              dec(lewe_ciecia);
            end else
              begin
                (*nie da sie wykonac zadnego ciecia*)
                mozna_zaorac := false;
                wa := wb + 1;
              end;
  end;
end;

function min(a, b : longint) : longint;
begin
  if (a <= b) then
    min := a
  else
    min := b;
end;

procedure licz;
var
  wynik, l, r, srodek, i, lewe_ciecia : longint;
begin
  wynik := INF;
  for i := 0 to 1 do
  begin
    (*wykonujemy dla pola oryginalnego oraz obroconego*)
    licz_sumy;
    for lewe_ciecia := 0 to m - 1 do
    begin
      l := 0;
      r := m - lewe_ciecia - 1;
      (*binarnie wyszukujemy liczbe prawych ciec*)
      while l < r do
      begin
        srodek := (l + r) div 2;
        if (mozna_zaorac(lewe_ciecia, srodek)) then
          r := srodek
        else
          l := srodek + 1;
      end;
      if (mozna_zaorac(lewe_ciecia, l)) then
        wynik := min(wynik, lewe_ciecia + l + n);
    end;
    transponuj;
  end;
  writeln(wynik);
end;

begin
  czytaj;
  licz;
end.
