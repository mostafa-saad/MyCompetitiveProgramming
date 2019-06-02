(*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: TAN (Tance w kolkach)                          *
 *   Plik:                tans4.ml                                       *
 *   Autor:               Marcin Kubica                                  *
 *   Opis:                Rozwiazanie nieoptymalne.                      *
 *                        £atwe rozwi±zanie funkcyjne, programowanie     *
 *                        dynamiczne. Wszystkie dzia³ania arytmetyczne   *
 *                        s± wykonywane modulo rok.                      *
 *                                                                       *
 *************************************************************************)

open Array;;
open Scanf;;
let rok = 2005;;
let modulo x = x mod rok;;

(* Z³o¿enie: f(f(.. (f a x) (x+1)) ..) y. *)
let zloz f x y a =
  let rec iter x a =
    if x > y then a else iter (x+1) (modulo (f a x))
  in iter x a;;

(* Suma f(x) + ... + f(y) *)
let suma f x y = zloz (fun a x -> a + f x) x y 0;;


(* Liczenie wyniku za pomoc± programowania dynamicznego *)
let policz n k l =
  (* Tablica spamiêtuj±ca warto¶ci f. *)
  let tab = make_matrix (n+1) (k+1) (-1)

  (* Tablica spamiêtuj±ca warto¶ci funkcji wybór. *)
  and w = make_matrix (n+1) (n+1) (-1)
  in

    (* Kó³ko zawieraj±ce n-te dziecko mo¿e zostaæ wybrane na *)
    (* (n - i + 1) * ... * (n - 1) sposobów.                 *)
    let rec wybierz n i =
      if w.(n).(i) <> -1 then w.(n).(i) else
        let wynik =
          if i = 1 then 1
          else ((n - i + 1) * wybierz n (i-1)) mod rok
        in begin
          w.(n).(i)<- wynik;
          wynik
        end
    in

      (* Rekurencyjny wzór ze spamiêtywaniem. *)
      let rec f n k =
        if tab.(n).(k) <> -1 then tab.(n).(k) else
          let wynik =
            if k = 0 then
              if n = 0 then 1
              else 0
            else
              if n < k * l then 0
              else
                suma
                  (fun i -> wybierz n i * f (n-i) (k-1))
                  l
                  (n - (k-1) * l)
          in begin
            tab.(n).(k) <- wynik;
            wynik
          end
      in
        f n k;;

begin
  let (n, k, l) = scanf "%d %d %d" (fun n k l -> (n, k, l))
  in begin
    (if n>1000 then let rec f a = f a in f ());
    print_int (policz n k l);
    print_newline()
  end
end;;
