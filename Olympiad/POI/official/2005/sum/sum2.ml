(*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: SUM (Sumy Fibbonacciego)                       *
 *   Plik:                sum2.cpp                                       *
 *   Autor:               Marcin Kubica                                  *
 *   Opis:                Rozwiazanie wzorcowe                           *
 *                        Jêzyk: Ocaml                                   *
 *                                                                       *
 *************************************************************************)

(* pomocnicze *)
open List;;
let id x = x;;
let compose f g = function x -> f(g x);;
let rec iterate n f =
  if n = 0 then id else compose (iterate (n-1) f) f;;
open Scanf;;
let scanf = fscanf stdin;;


(* Liczby s± reprezentowane jako listy cyfr, w kolejno¶ci od mniej do *)
(* bardziej znacz±cych. Dane s± znormalizowane, tzn. zawieraj± tylko  *)
(* cyfry 0 i 1, przy czym 1-ki nie s±siaduj± ze sob±.                 *)
(* W procedurach pomocniczych dane nie musz± byæ znormalizowane, tzn. *)
(* mog± pojawiaæ siê 2-ki, a 1-ki mog± s±siadowaæ ze sob±.            *)
(* Reprezentacja odwrócona oznacza kolejno¶æ cyfr od bardziej do      *)
(* mniej znacz±cych.                                                  *)

(* Zwykle sumowanie kolejnych cyfr na kolejnych pozycjach.            *)
(* Dane znormalizowane, wynik nie, ale w wyniku 2-ki mog± s±siadowaæ  *)
(* tylko z 0-mi.                                                      *)
let sum l1 l2 = 
  let rec s l1 l2 a = 
    match l1 with 
      []     -> (rev a) @ l2 |
      h1::t1 -> match l2 with
        []     -> (rev a) @ l1 |
        h2::t2 -> s t1 t2 ((h1 + h2)::a)
  in s l1 l2 [];;
  
(* Normalizacja liczby nie znormalizowanej. 2-ki mog± s±siadowaæ      *)
(* tylko z 0-mi. W wyniku cyfry > 0 mog± s±siadowaæ tylko z 0-mi.     *)
(* Je¶li w danych by³y 2-ki, to w wyniku te¿ mog± byæ.                *)
let normalize l = 
  let rec rm_leading_zeros l = 
    match l with
      0::t -> rm_leading_zeros t |
      _    -> l
  in let rec norm c a l =       
    match l with
      []   -> rev (rm_leading_zeros a) |
      0::t -> 
        if c = 0 then                        (* 0 -> 0 *)
          norm 0 (0::a) t 
        else if c = 1 then                   (* 010 -> 010 *) 
          norm 0 (0::1::a) t  
        else if c mod 2 = 0 then             (* 01^(2k)0 -> 00(01)^k *)
          norm 1 (iterate (c/2 - 1) (fun x -> 0::1::x) (0::0::a)) t
        else                                 (* 01^(2k+1) -> 010(01)^k *)
          norm 1 (iterate (c/2 - 1) (fun x -> 0::1::x) (0::0::1::a)) t |
      1::t -> norm (c+1) a t |                   
      2::0::t -> match c with
        0 -> norm 0 (0::2::a) t |            (* 020 -> 020 *)
        1 -> norm 2 (0::a) t |               (* 0120 -> 0011 *)
        2 -> norm 2 (0::1::a) t              (* 01120 -> 01011 *)
  in norm 0 [] (l@[0; 0; 0]);;
    

(* Eliminacja dwójek ze znormalizowanej liczby. *)
let eliminate l = 
  (* Eliminacja sekwencji 102 i 002.                        *)
  (* Dane znormalizowane, ale mog± zawieraæ 2-ki.           *)
  (* Wynik nie zawiera sekwencji 102, ani 002, a po ka¿dej  *)
  (* 2-ce mamy ci±g: 1*0.                                   *)
  (* Ci±g jest przetwarzany od cyfr bardziej znacz±cych.    *)
  let elim_102_002 ll = 
    let rec epom rl a =
      match rl with 
        []         -> a | 
        2::0::1::t -> epom (2::t) (1::1::a) | (* 102 -> 211 *)
        2::0::0::t -> epom t (1::1::1::a)   | (* 002 -> 111 *)
        h::t       -> epom t (h::a)
    in epom (0::(rev ll)) []
  
  (* Z ci±gu powsta³ego po usuniêciu 102 i 002 usuwa prefiks 02. *)
  and elim_front_02 ll = 
    match ll with
      0::2::t -> 2::1::t |   (* [02] -> [21] *)
      x       -> x

  (* Z wyniku poprzedniej procedury usuwa wiod±c± dwójkê.   *)
  (* W wyniku, nie wystêpuje sekwencja 102, ani 002, a      *)
  (* ka¿da 2-ka jest poprzedzona 1-k±, 00 lub 20, a po niej *)
  (* wystêpuje 1*0.                                         *)
  and elim_front_2 ll = 
    (* Korzystamy z nastêpuj±cych wzorów:                            *)
    (* [2(1^(2k))0] = [(01)^(k+1)]                                   *)
    (* [2(1^(2k+1))0] = [1(01)^(k+1)]                                *)
    (* Poniewa¿ w danych nie by³o 002, wiêc w wyniku nie bêdzie 102. *)
    let rec ef2 t a = 
      match t with
        1::1::tt -> ef2 tt (0::1::a) |
        1::0::tt -> 1::a @ tt |
        0::tt    -> a @ tt
    in 
      match ll with
        2::t -> ef2 t [0;1] |
        x    -> x

  (* Eliminacja 2-ek z ci±gu, który nie zawiera 102, 002, ani *)
  (* te¿ prefiksów 02 i 2. Wynik nie jest znormalizowany.     *)
  (* W trakcie przetwarzania mo¿e siê pojawiæ 1102.           *)
  and elim2 li = 
    let rec e2 ll a = 
      match ll with 
        1::1::0::2::t -> e2 (1::2::t) (0::0::a) | (* 1102 -> 0012 *)
        (* 0::0::2::t    -> e2 (1::1::t) (1::a) |     (* 002 -> 111 *) *)
        1::2::0::t    -> e2 (1::1::t) (0::a) |     (* 120 -> 011 *)
        1::2::1::t    -> e2 (1::2::t) (0::a) |     (* 121 -> 012 *)
        0::t          -> e2 t (0::a) | 
        1::t          -> e2 t (1::a) |
        []            -> rev a 
    in e2 li []
      
  in 
    normalize (elim2 (elim_front_2 (elim_front_02 (elim_102_002 l))));;

(* Dodawanie, koszt liniowy. *)
let add x y = eliminate (normalize (sum x y));;

(* Wczytywanie
 danych *)
let read_in () = 
  let read_fib () = 
    let n = scanf "%d " id 
    in rev (iterate n (fun l -> (scanf "%d " id) :: l) [])
  in 
    let x = read_fib()
    and y = read_fib()
    in (x, y);;
    
(* Wypisywanie wynikow *)
let write_out l = 
  begin
    print_int (length l);
    iter (fun x -> print_string " "; print_int x) l;
    print_newline()
  end;;

(* Program glowny *)
let main () = 
  let (x, y) = read_in ()
  in write_out (add x y);;
  
main ();;
