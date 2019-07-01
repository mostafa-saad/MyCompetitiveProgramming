{* Program oceniajacy do zadania Konewka
 *
 * Czyta ze standardowego wejscia kolejno (wierszami):
 * 1) dwie liczby calkowite N, K,
 * 2) N liczb calkowitych oznaczajacych poczatkowe wysokosci drzew,
 * 3) liczbe naturalna q.
 *
 * Następnie czyta q wierszy, w ktorych znajduja się instrukcje postaci:
 *
 * "p a b" (reprezentujaca wykonanie funkcji "podlej(a,b)")
 * "d a b" (reprezentujaca wykonanie funkcji "dojrzale(a,b)")
 *
 * Program wywoluje odpowiednie funkcje ocenianej biblioteki i wypisuje
 * wyniki funkcji "dojrzale" na standardowe wyjscie *}

uses kon;

(* Dziwne nazwy, aby uniknac kolizji z nazwami uzywanymi przez biblioteke zawodnika *)

const FHksU_maxn = 300000;

var
  FHksU_num_calls, FHksU_i, FHksU_a, FHksU_b : LongInt;
  FHksU_call : Char;
  FHksU_n, FHksU_k : LongInt;
  FHksU_D : array[0..FHksU_maxn] of LongInt;

begin
  ReadLn(FHksU_n, FHksU_k);
  for FHksU_i := 0 to FHksU_n-1 do
      Read(FHksU_D[FHksU_i]);
  inicjuj(FHksU_n, FHksU_k, FHksU_D);
  ReadLn(FHksU_num_calls);
  for FHksU_i := 1 to FHksU_num_calls do
  begin
    ReadLn(FHksU_call, FHksU_a, FHksU_b);
    if FHksU_call = 'p' then
      podlej(FHksU_a, FHksU_b)
    else
      WriteLn(dojrzale(FHksU_a, FHksU_b));
  end;
end.
