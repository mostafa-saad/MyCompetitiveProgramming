{*************************************************************************}
{*                                                                       *}
{*                   VII Olimpiada Informatyczna                         *}
{*                                                                       *}
{*   Rozwi¥zanie zadania: NARCIARZE                                      *}
{*   Plik:                NAR.PAS                                        *}
{*   Autor:               MAREK PAWLICKI                                 *}
{*************************************************************************}

{$M 65000, 0, 655360}
program Nar;
const
  (* Nazwa pliku wej˜ciowego. *)
  NazwaPlikuWe = 'NAR.IN';
  (* Nazwa pliku wyj˜ciowego. *)
  NazwaPlikuWy = 'NAR.OUT';
  (* Maksymalna liczba polan (wierzchoˆk¢w grafu). *)
  MaxN = 5000;
  (* Staˆa u¾ywana do oznaczenia elementu w tablicy (li˜cie s¥siedztwa)
     przechowuj¥cego liczb© wierzchoˆk¢w. *)
  indLiczbaWierz = 0;
type
  (* Lista s¥siedztwa - element 0 zawiera liczb© wierzchoˆk¢w na li˜cie. *)
  TListaSasiedztwa = array [0..MaxN] of Integer;
  PListaSasiedztwa = ^TListaSasiedztwa;
var
  (* Trasa zjazdowa - graf. *)
  T : array [1..MaxN] of PListaSasiedztwa;
  (* Tablica do markowania odwiedzonych wierzchoˆk¢w. *)
  Odwiedzony : array [1..MaxN] of Boolean;
  (* Liczba wierzchoˆk¢w. *)
  N : Integer;
  (* Odpowiedz - maksymalna liczba narciarzy. *)
  MaxNar : Integer;


  procedure WczytajDane;
  (* Wczytuje dane z pliku wej˜ciowego. *)
  var
    f : Text;
    i, nrp, lnast : Integer;
  begin
    Assign (f, NazwaPlikuWe);
    Reset (f);
    (* Liczba polan. *)
    Readln (f, N);
    (* Trasa. *)
    for nrp := 1 to N - 1 do begin
      Read (f, lnast);
      GetMem (T[nrp], (lnast + 1) * SizeOf (Integer));
      T[nrp]^[indLiczbaWierz] := lnast;
      for i := 1 to lnast do
        Read (f, T[nrp]^[i]);
      Readln (f)
    end;
    Close (f)
  end;

  procedure WypiszOdp;
  (* Wypisuje znalezione rozwi¥zanie do pliku wyj˜ciowego. *)
  var
    f : Text;
  begin
    Assign (f, NazwaPlikuWy);
    Rewrite (f);
    Writeln (f, MaxNar);
    Close (f)
  end;

  function Wglab (w : Integer) : Boolean;
  (* Realizuje przeszukanie grafu T w gˆ¥b od wierzchoˆka nr w.
     Zwraca ``true'' w przypadku sukcesu (dotarcia do mety). *)
  var
    i : Integer;
    s : Boolean;
  begin
    if w = N then
      (* Osi¥gni©to met©. *)
      Wglab := true
    else begin
      Odwiedzony [w] := true; s := false; i := 1;
      (* Przeszukuj a¾ do pierwszego sukcesu. *)
      while not s and (i <= T[w]^[indLiczbaWierz]) do begin
        if not Odwiedzony [T[w]^[i]] then
          s := Wglab (T[w]^[i]);
        Inc (i)
      end;
      Wglab := s
    end
  end;

  procedure ZnajdzRozwiazanie;
  (* Znajduje rozwi¥zanie metod¥ poszukiwania najbardziej skrajnej scie¾ki. *)
  var
    i : Integer;

    function UsunTraseBezposrednia : Boolean;
    (* Usuwa ewentualne bezpo˜rednie poˆ¥czenie 1-->N, zwraca ``true'', gdy
       takie poˆ¥czenie istniaˆo. *)
    var
      i, j, lnast : Integer;
      zn : Boolean;
    begin
      i := 1; zn := false; lnast := T[1]^[indLiczbaWierz];
      while (i <= lnast) and not zn do
        if T[1]^[i] = N then
          zn := true
        else
          Inc (i);
      if zn then begin
        for j := i to lnast - 1 do T[1]^[j] := T[1]^[j+1];
        Dec (T[1]^[indLiczbaWierz])
      end;
      UsunTraseBezposrednia := zn
    end;

  begin (* ZnajdzRozwiazanie *)
    for i := 1 to N do Odwiedzony [i] := false;
    if UsunTraseBezposrednia then
      i := 1
    else
      i := 0;
    while Wglab (1) do Inc (i);
    MaxNar := i
  end;

begin
  WczytajDane;
  ZnajdzRozwiazanie;
  WypiszOdp
end.