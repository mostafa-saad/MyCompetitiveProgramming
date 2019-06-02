(*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Wyspa (WYS)                                               *
 *   Plik:     wys7.ml                                                    *
 *   Autor:    Pawel Parys                                               *
 *   Opis:     Rozwiazanie wzorcowe O(n+m)                               *
 *                                                                       *
 *************************************************************************)


(*///////////// punkty: *)

type punkt = { x : float; y : float };;

let len p =
    sqrt (p.x*.p.x+.p.y*.p.y);;


let il_wek a b = 
    a.x*.b.y-.a.y*.b.x;;


let razy_stala p k = 
    { x = p.x*.k; 
      y = p.y*.k };;

let dodaj a b = {
    x = a.x+.b.x;
    y = a.y+.b.y };;

let odejmij a b = {
    x = a.x-.b.x;
    y = a.y-.b.y };;


let pkt_przec a b c d = (* punkt przeciecia linii a-b z c-d *)
    let p1 = il_wek (odejmij a c) (odejmij d c) in (* pole trojkata a-c-d *)
    let p2 = il_wek (odejmij a b) (odejmij d c) in (* pole czworokata a-b-c-d *)
    let k = p1/.p2 in
    dodaj a (razy_stala (odejmij b a) k);; (* a-(b-a)*k *)

(*//////////// program wlasciwy: *)

let mAX_N = 60000;;
let mAX_M = 1000000;;

(* wszystkie numeracje od 0 *)

let punkty = Array.create mAX_N { x = 0.; y = 0. };;

(* krawedzie, ktorych nie ma (czyli te z wejscia) *)
let brakujace_tab = Array.create mAX_M 0;; (* dokad krawedz *)
let brakujace_next = Array.create mAX_M 0;; (* wskaznik na nastepna krawedz z tego wierzcholka (lub -1) *)
let brakujace_first = Array.create mAX_N (-1);; (* wskaznik na pierwsza krawedz z tego wierzcholka (lub -1) *)

let ostatni = Array.create mAX_N (-1);; (* najwiekszy wierzcholek, do ktorego mamy krawedz *)
    (* lub -1 jesli nie zadnego wiekszego niz ostatni dla wczesniejszych wierzcholkow *)

let czy_obstawiana = Array.create mAX_N false;; (* tablica tymczasowa: czy krawedz z aktualnego jest blokowana *)

(* trasa *)
let ile_stos = ref 0;;
let stos_nr = Array.create mAX_N 0;;  (* poczatek krawedzi (koniec jest w ostatni[]) *)
let stos_prz = Array.create mAX_N { x = 0.; y = 0. };; (* punkt przeciecia z poprzednia (dla pierwszej punkt startowy) *)

let czy_na_lewo p a b =
    il_wek (odejmij p punkty.(a)) (odejmij punkty.(b) punkty.(a))<0.;;


    (* wczytywanie *)
let line = read_line ();;
let poz_sp = (String.index line ' ');; (* gdzie jest spacja *)
let n = int_of_string (String.sub line 0 poz_sp);;
let m = int_of_string (String.sub line (poz_sp+1) (String.length line - poz_sp - 1));;
for a = 0 to n-1 do
    let line = read_line () in
    let poz_sp = (String.index line ' ') in (* gdzie jest spacja *)
    punkty.(a) <- { 
        x = float_of_string (String.sub line 0 poz_sp); 
        y = float_of_string (String.sub line (poz_sp+1) (String.length line - poz_sp - 1)) }
done;;
for a = 0 to m-1 do
    let line = read_line () in
    let poz_sp = (String.index line ' ') in (* gdzie jest spacja *)
    let i = int_of_string (String.sub line 0 poz_sp) in
    let j = int_of_string (String.sub line (poz_sp+1) (String.length line - poz_sp - 1)) in
    brakujace_tab.(a) <- j-1;
    brakujace_next.(a) <- brakujace_first.(i-1);
    brakujace_first.(i-1) <- a;
done;;

(* znajdowanie krawedzi po ktorych w ogole warto chodzic *)
let max_ost = ref 0;;
for a = 0 to n-1 do
    let i = ref brakujace_first.(a) in
    while (!i>=0) do
        czy_obstawiana.(brakujace_tab.(!i)) <- true;
        i := brakujace_next.(!i)
    done;
    ostatni.(a) <- -1;
    let b = ref (n-1) in
    while !b >= !max_ost+1 do
        if czy_obstawiana.(!b) then
            czy_obstawiana.(!b) <- false
        else begin
            ostatni.(a) <- !b;
            max_ost := !b; (* opuszczamy petle *)
        end;
        b := !b-1
    done
    (* wewnetrzna petla zrobi w sumie najwyzej m obrotow *)
done;;

(* szukanie trasy *)
(* (z zalozenia jakas trasa istnieje) *)
stos_nr.(0) <- 0;;
stos_prz.(0) <- punkty.(0);
ile_stos := 1;
for a = 1 to n-1 do 
    if (ostatni.(a)>=0) then
      let dzialaj = ref true in
      while (!dzialaj) do
        dzialaj := false;
        let ost = stos_nr.(!ile_stos-1) in
        let prz = pkt_przec punkty.(ost) punkty.(ostatni.(ost)) punkty.(a) punkty.(ostatni.(a)) in
        (* na pewno proste nie sa rownolegle (z zalozenia) *)
        if (!ile_stos>1) then begin
            let poprz = stos_nr.(!ile_stos-2) in (* przedostatni *)
            if czy_na_lewo prz poprz ostatni.(poprz) then begin (* ostatnia krawedz na stosie niepotrzebna *)
                ile_stos := !ile_stos-1;
                dzialaj := true;
            end
        end;
        if !dzialaj = false then begin
            stos_nr.(!ile_stos) <- a;
            stos_prz.(!ile_stos) <- prz;
            ile_stos := !ile_stos+1;
        end
      done
done;;

(* liczenie dlugosci trasy *)
stos_prz.(!ile_stos) <- punkty.(n-1);; (* wstawiamy ostatni punkt *)
let dl = ref 0.;;
for a = 0 to !ile_stos-1 do
    dl := !dl +. len (odejmij stos_prz.(a+1) stos_prz.(a));
done;;

print_float !dl;;
print_newline ();;
