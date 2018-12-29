(*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: ORK (Orka)                                     *
 *   Plik:                ork1.pas                                       *
 *   Autor:               Marek Cygan                                    *
 *   Opis:                Program wzorcowy, o zlozonosci obliczeniowej   *
 *                        oraz pamieciowej O((n + m) ^ 2)                *
 *                                                                       *
 *************************************************************************)

const MAX_N = 2000;      {maksymalny wymiar pola}
const INF = 2*MAX_N;     {maksymalna liczba skib}
var
  n, m : longint;        {wymiary pola (liczba wierszy, liczba kolumn)}
  k : longint;           {wytrzymalosc szkapy}
  t : array [0 .. MAX_N-1, 0 .. MAX_N-1] of longint;         {trudnosc pola}
  (*suma trudnosci pol od danego pola w prawo, do konca wiersza               *)
  prawo : array [0 .. MAX_N, 0 .. MAX_N] of longint;
  (*suma trudnosci pol od danego pola d dol do konca kolumny                  *)
  dol : array [0 .. MAX_N, 0 .. MAX_N] of longint;

(*wczytywanie danych wejsciowych*)
procedure czytaj;
var
  i, j : longint;
begin
  read(k,m,n);
  for i := 0 to n - 1 do
    for j := 0 to m - 1 do
      read(t[i][j]);
end;

function min(a, b : longint) : longint;
begin
  if (a <= b) then
    min := a
  else
    min := b;
end;

procedure transponuj;
var
  i, j : longint;
begin
  for i := 0 to n - 1 do
    for j := 0 to m - 1 do
      dol[i][j] := t[i][j];

  i := n;
  n := m;
  m := i;

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

(*obliczanie minimalnej liczby skib, przy zalozeniu ze wykonamy n ciec        *
 *poziomych                                                                   *)
function tnij : longint;
var
  i, prawe_ciecia : longint;
  wa, wb, ka, kb : longint;(*aktualne wymiary pola: gorny wiersz, dolny wiersz*
                            *lewa kolumna, prawa kolumna                      *)
begin
  tnij := n + m;
  licz_sumy;

  for i := 0 to m - 1 do
  begin
    prawe_ciecia := i;
    wa := 0;
    ka := 0;
    wb := n - 1;
    kb := m - 1;
    while (wa <= wb) and  (ka <= kb) do
    begin
      if prawo[wa][ka] - prawo[wa][kb+1] <= k then
      begin
        (*mozna wykonac ciecie gorne  *)
        if wa = wb then
          tnij := min(tnij, n + m - (kb - ka + 1));
        inc(wa);
      end else
        if prawo[wb][ka] - prawo[wb][kb+1] <= k then
        begin
          (*mozna wykonac ciecie dolne*)
          if (wa = wb) then
            tnij := min(tnij, n + m - (kb - ka + 1));
          dec(wb);
        end else
          if (dol[wa][kb] - dol[wb+1][kb] <= k) and (prawe_ciecia > 0) then
          begin
            (*mozna wykonac ciecie prawe*)
            dec(kb);
            dec(prawe_ciecia);
          end else
            if dol[wa][ka] - dol[wb+1][ka] <= k then
              inc(ka) (*ciecie lewe*)
            else
              wa := wb + 1; (*nie da sie wykonac zadnego ciecia, wyjscie z petli*)
    end;
  end;
end;

procedure licz;
var
  wynik : longint;
begin
  wynik := tnij;
  transponuj;
  wynik := min(wynik, tnij);
  writeln(wynik);
end;

begin
  czytaj;
  licz;
end.
