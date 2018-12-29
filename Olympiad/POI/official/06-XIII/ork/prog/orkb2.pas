(*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: ORK (Orka)                                     *
 *   Plik:                orkb2.pas                                      *
 *   Autor:               Marek Cygan                                    *
 *   Opis:                Rozwiazanie wolne o zlozonosci obliczeniowej   *
 *                        oraz pamieciowej O(n^2 * m^2)                  *
 *                                                                       *
 *************************************************************************)

const MAX_N = 85;            (*maksymalny wymiar pola, zmniejszony z powodu   *
                              *wiekszego zapotrzebowania na pamiec            *)
const INF = 2*MAX_N;                                    {maksymalna liczba skib}

var
  n, m : longint;                 {wymiary pola (liczba wierszy, liczba kolumn)}
  k : longint;                     {wytrzymalosc szkapy}
  t : array [0 .. MAX_N - 1, 0 .. MAX_N - 1] of longint;         {trudnosc pola}
(*suma trudnosci pol od danego pola w prawo, do konca wiersza oraz od danego  *
  pola d dol, do konca kolumny                                                *)
  prawo, dol : array [0 .. MAX_N, 0 .. MAX_N] of longint;
{tablica do spamietywania  }
  mem : array [0 .. MAX_N - 1, 0 .. MAX_N - 1, 0 .. MAX_N - 1, 0 .. MAX_N - 1] of byte;

(*wczytywanie danych wejsciowych*)
procedure czytaj;
var i, j : longint;
begin
  read(k,m,n);
  for i := 0 to n - 1 do
  begin
    for j := 0 to m - 1 do
      read(t[i][j]);
  end;
end;

procedure licz_sumy;
var i, j : longint;
begin
  (*liczenie sum czesciowych*)
  for i := 0 to n - 1 do
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
      dol[i][j] := t[i][j] + dol[i + 1][j];
      prawo[i][j] := t[i][j] + prawo[i][j + 1];
    end;
end;

function min(a, b : byte) : byte;
begin
  if (a <= b) then
    min := a
  else
    min := b;
end;

function value(wa, wb, ka, kb : longint) : byte;
begin
  if (wa > wb) or (ka > kb) then
    value := 0
  else
    if (mem[wa][wb][ka][kb] < INF) then
      value := mem[wa][wb][ka][kb]
    else
      begin
        value := INF;
        if (prawo[wa][ka] - prawo[wa][kb + 1] <= k) then
          (*mozna wykonac ciecie gorne  *)
          value := min(value, value(wa + 1, wb, ka, kb) + 1);
        if (prawo[wb][ka] - prawo[wb][kb + 1] <= k) then
          (*mozna wykonac ciecie dolne*)
          value := min(value, value(wa, wb - 1, ka, kb) + 1);
        if (dol[wa][kb] - dol[wb + 1][kb] <= k) then
          (*mozna wykonac ciecie prawe*)
          value := min(value, value(wa, wb, ka, kb - 1) + 1);
        if (dol[wa][ka] - dol[wb + 1][ka] <= k) then
          (*mozna wykonac ciecie lewe*)
          value := min(value,value(wa, wb, ka + 1, kb) + 1);
        mem[wa][wb][ka][kb] := value;
      end;
end;

procedure licz;
var
  a, b, c, d : longint;
begin
  licz_sumy();
  for a := 0 to n - 1 do
    for b := a to n - 1 do
      for c := 0 to m - 1 do
        for d := c to m - 1 do
          mem[a][b][c][d] := INF;
  writeln(value(0, n - 1, 0, m - 1));
end;

begin
  czytaj();
  licz();
end.
