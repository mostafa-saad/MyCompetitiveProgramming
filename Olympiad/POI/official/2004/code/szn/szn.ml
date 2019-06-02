(*************************************************************************
 *                                                                       *
 *                    XI Olimpiada Informatyczna                         *
 *                                                                       *
 *   Rozwi±zanie zadania: Sznurki                                        *
 *   Plik:                szn2.ml                                        *
 *   Autor:               Marcin Kubica                                  *
 *************************************************************************)

open Scanf;;
open Array;;
open List;;
let id x = x;;
let inf = 100000;;

(* Typ reprezentuj±cy dowolne drzewo ukorzenione. *)
type drzewo = Wezel of drzewo list;;

(* Wczytanie danych. Wynikiem jest drzewo i liczba sznurków. *)
let wczytaj_dane () = 
  (* Liczba wêz³ów. *)
  let n = scanf "%d " id
  in 
    let sasiedzi = make (n+1) []
    and odwiedzone = make (n+1) false
    and konce = ref 0
    in 
      (* Wczytanie krawêdzi. *)
      (* Wynikiem jest korzen - jeden z li¶ci. *)
      let rec wczytaj () = 
	let i = ref 1 
	in
	  begin
	    (* Wczytanie krawêdzi. *)
	    for j = 1 to n-1 do 
	      let a = scanf "%d " id
	      and b = scanf "%d " id
	      in begin
		sasiedzi.(a) <- b::sasiedzi.(a);
		sasiedzi.(b) <- a::sasiedzi.(b)
	      end
	    done;
	    (* Koñce sznurków. *)
	    for j = 1 to n do 
	      if length sasiedzi.(j) mod 2 = 1 then konce := !konce + 1
	    done; 
	    (* Wybór korzenia -- jeden z li¶ci. *)
	    while length sasiedzi.(!i) > 1 do i:= !i + 1 done;
	    !i 
	  end

      (* Konstrukcja drzewa - DFS. *)
      and dfs v = 
	begin
	  odwiedzone.(v) <- true;
	  Wezel  
	    (fold_left
	      (fun a w -> if odwiedzone.(w) then a else (dfs w)::a)
	      [] sasiedzi.(v))
	end

      in 
        let korzen = wczytaj ()
	in (dfs korzen, !konce / 2);;
        

(* Wybiera z listy fragment od i-tego do j-tego elementu. *)
let cut i j l = 
  let rec cut_iter i j l a = 
    if i > 1 then 
      cut_iter (i-1) (j-1) (tl l) a
    else if j > 0 then 
      cut_iter i (j-1) (tl l) (hd l :: a)
    else 
      rev a
  in
    cut_iter i j l [];;


(* Sprawdza ile pierwszych elementów z obu list *)
(* mo¿na po³±czyæ w pary o sumach <= d.         *)
let ile_par l1 l2 d = 
  let rec ile_par_iter l1 l2 a = 
    match (l1, l2) with
      ([], []) -> a | 
      (h1::t1, h2::t2) -> 
	if h1 + h2 + 2 <= d then 
	  ile_par_iter t1 t2 (a+1)
	else a |
      _ -> a
  in 
    ile_par_iter l1 l2 0;;
    
(* Sprawd¼ czy elementy listy posortowanej *)
(* nierosn±co mo¿na po³±czyæ w pary <= d   *)
let pary l d = 
  let dl = length l
  in 
    if dl mod 2 = 0 then 
      ile_par (cut 1 (dl / 2) l) (rev (cut (dl / 2 + 1) dl l)) d = dl / 2
    else false;;
      
(* S(v,d) dla nieparzystej liczby potomków v,   *)
(* na podstawie d oraz [S(w1,d); ...; S(wp,d)]. *)
let nieparzyste ls d = 
  let dl = length ls
  in
    if pary (tl ls) d then 
      (* Najd³u¿szy sznurek mo¿e wychodziæ do góry. *)
      (* Szukamy krótszego.                         *)
      let i = ile_par (cut 1 (dl/2) ls) 
	              (rev (cut (dl/2 + 2) dl ls)) d
      in
        if i = dl/2 then 
          (* ¦rodkowy (co do d³ugo¶ci) sznurek mo¿e *)
	  (* wychodziæ do góry. Szukamy krótszego.  *)
	  let j = ile_par (cut (dl/2 + 1) (dl-1) ls) 
	                  (rev (cut 1 (dl/2) ls)) d
	  in 
	    nth ls (j + dl/2) + 1
	else nth ls i + 1
    else 
      (* Nie da siê. *)
      inf

(* S(v,d) dla parzystej liczby potomków v,      *)
(* na podstawie d oraz [S(wp,d); ...; S(w1,d)]. *)
let parzyste ls d =
  if pary ls d then 
    (* Z v wychodzi nowy sznurek. *)
    0
  else 
    if hd ls + 1 <= d then 
      (* Najd³u¿szy z wychodz±cych sznurków koñczymy, *)
      (* a pozosta³ych mamy nieparzyst± liczbê.       *)
      nieparzyste (tl ls) d
    else
      if nieparzyste (tl ls) d <= d then 
        (* Najd³u¿szy z wychodz±cych sznurków przechodzi  *)
        (* do góry, o ile pozosta³e nie s± d³u¿sze ni¿ d. *)
        hd ls + 1
      else
        (* Nie da siê. *)
        inf;;

(* Obliczenie S(v,d) na podstawie d oraz [S(w1,d); ...; S(wp,d)]. *)
let s d l = 

  (* Posortowana nierosn±co lista  [S(w1,d); ...; S(wp,d)]. *)
  let l_sort =
    let por x y = if x < y then 1 else if x > y then -1 else 0
    in sort por l

  in
    if length l mod 2 = 1 then 
      (* Nieparzysta liczba potomków. *)
      nieparzyste l_sort d
    else
      (* Parzysta liczba potomków. *)
      parzyste l_sort d;;


(* Analiza danego drzewa.           *)
(* Obliczane s±:                    *)
(* - wysoko¶æ drzewa h,             *)
(* - ¶rednica drzewa sr,            *)
(* - sl = [S(v,0); ... ; S(v, sr)]. *)
let rec analiza (Wezel l) = 
  (* Poddaj analizie poddrzewa. *)
  let w = map analiza l 
  in 

    (* Wysoko¶æ i ¶rednica drzewa. *)
    let (h, sr)  = 
      (* Dwie najwiêksze wysoko¶ci poddrzew. *)
      let (h1, h2) = 
	fold_left (fun (a1, a2) (h, _, _) -> 
	  if h >= a1 then (h, a1) else 
	  if h >= a2 then (a1, h) else (a1, a2)) 
	  (-1, -1) w
      in 
        (h1 + 1,
	 fold_left (fun a (_,s,_) -> max a s) (h1 + h2 + 2) w)
    in 

      (* [S(v,0); ... ; S(v, sr)] *)
      let sl = 
        (* Iteracja obliczaj±ca S(v, d) dla kolejnych d. *)
        let rec s_iter d ll ak = 
          (* Ogon listy, przy czym je¶li pusty, to *)
	  (* dublowana jest g³owa.                 *)
          let tail l = 
            match l with 
              [x]  -> [x] |
              h::t -> t |
	      _ -> failwith "tail: l = []"
          in 
            if d > sr then rev ak else 
              s_iter (d+1) 
                (map tail ll) 
                ((s d (map hd ll)) :: ak)
          in 
            s_iter 0 (map (fun (_, _, l) -> l) w)[]

      in (h, sr, sl);;

(* Minimalne ograniczenie na d³ugo¶æ sznurków. *)
let ograniczenie t = 
  let (_, sr, sl) = analiza t 
  in 
    snd (fold_left (fun (d, m) s -> (d+1, min (max d s) m)) (0, inf) sl) ;;


let (t, n) = wczytaj_dane ()
in 
  begin
    print_int n;
    print_string " ";
    print_int (ograniczenie t);
    print_newline ()
  end;;
  
