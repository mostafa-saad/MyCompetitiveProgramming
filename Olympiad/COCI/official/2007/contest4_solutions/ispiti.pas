
(*
  Croatian Open Competition in Informatics 2006/2007
  Contest 4 - Task ISPITI
  Programming language Pascal
*)

program ispiti;

const maxn = 200000;
      maxt = 524288;

type event = record    (* jedan dogadjaj iz ulaza: type = 1 za dolazak ucenika, a 2 za upit *)
    who, tip: longint;
end;

type ucenik = record
    a, b: longint;
    index: longint; (* indeks ucenika u sortiranom nizu ucenika *)
    sorted_index: longint; (* indeks ucenika u ulazu *)
end;

var
    m, n, i, j: longint;
    tree: array[0..maxt] of longint;
    U: array[0..maxn] of ucenik;
    E: array[0..maxn] of event;
    c: char;

function pair_cmp( x, y: ucenik ):boolean; begin (* sortiranje po drugom, pa prvom broju *)
    if x.b <> y.b then pair_cmp := (x.b < y.b)
    else pair_cmp := (x.a < y.a);
end;

function index_cmp( x, y: ucenik ):boolean; begin (* sortiranje po indeksu ucenika *)
    index_cmp := (x.index < y.index);
end;

function master_cmp( x,y: ucenik; k: longint ):boolean; begin
    if k = 0 then master_cmp := pair_cmp( x, y )
    else master_cmp := index_cmp( x, y );
end;

function bolji( uc1, uc2: longint ):longint; begin  (* usporedjuje po prvom broju ucenike, i pazi na prazna mjesta u stablu *)
    if uc1 = -1 then begin bolji := uc2; exit; end;
    if uc2 = -1 then begin bolji := uc1; exit; end;
    if U[uc1].a < U[uc2].a then bolji := uc2
    else bolji := uc1;
end;

procedure update( i, lo, hi, uc: longint ); (* dodaj ucenika uc u tournament tree *)
var mid: longint;
begin
    if (lo > U[uc].sorted_index) or (hi < U[uc].sorted_index) then exit;

    if lo = hi then tree[i] := uc (* ako smo na listu stabla, zapisi uc *)
    else begin
        mid := (lo+hi) div 2;

        update( 2*i, lo, mid, uc ); (* odi lijevo *)
        update( 2*i+1, mid+1, hi, uc ); (* odi desno *)

        tree[i] := bolji( tree[2*i], tree[2*i+1] ); (* u trenutni zapisi "bolji" od dva podstabla *)
    end;
end;

(* i u query i u update proceduri, varijabla i pamti trenutnu poziciju u stablu, a lo i hi pamte u kojem podintervalu trazimo *)

function query( i, lo, hi, uc: longint ): longint; (* vrati prvi desno koji ima prvi broj veci od ucenika uc *)
var t, mid: longint;
begin
    if hi <= U[uc].sorted_index then
        begin query := -1; exit; end; (* ako se uc nalazi ljevo od podintervala [lo, hi) vrati -1 *)

    if (tree[i] = -1) or (U[tree[i]].a < U[uc].a) then
        begin; query := -1; exit; end; (* ako u podintervalu nema ucenika ili je najveci prvi broj manji od onoga u uc, vrati -1 *)

    if lo = hi then begin query := tree[i]; exit; end;

    mid := (lo+hi) div 2; (* novi podintervali su [lo, mid) i [mid, hi) *)

    t := query( 2*i, lo, mid, uc );
    if t <> -1 then query := t (* ako u lijevom podintervalu ima netko veci od njega, vrati rezultat, nema potrebe da idemo u desni *)
    else query := query( 2*i+1, mid+1, hi, uc ); (* vrati prvi veci u desnom podintervalu *)
end;

procedure load; begin
    readln( n );
    for i := 0 to n-1 do begin (* prvo sve ucitamo, onda rjesavamo problem *)
        read( c );
        if c = 'D' then begin
            readln( U[m].a, U[m].b );
            U[m].index := m;
            E[i].who := m;
            inc( m );
            E[i].tip := 1;
        end else begin
            readln( E[i].who ); dec( E[i].who );
            E[i].tip := 2;
        end;
    end;
end;

procedure swap( var a, b: ucenik );
var tmp: ucenik;
begin
    tmp := a;
    a := b;
    b := tmp;
end;

procedure sortiraj( l, r, k: longint ); (* qsort *)
var mid: ucenik;
    x,y: longint;
begin
    if r-l < 2 then exit;
    if r-l = 2 then begin
        if master_cmp( U[l+1], U[l], k ) then swap( U[l], U[l+1] );
        exit;
    end;

    mid := U[(l+r) div 2];
    y := l;

    for x := l to r-1 do  (* sve strogo manje stavi na pocetak *)
        if( master_cmp( U[x], mid, k ) ) then begin
            swap( U[x], U[y] );
            inc( y );
        end;

    sortiraj( l, y, k ); (* sortiraj sve strogo manje *)

    for x := y to r-1 do (* sve jednake stavi poslije ovih manjih *)
        if( ( (k = 0) and (U[x].b = mid.b) and (U[x].a = mid.a) ) or ( (k = 1) and (U[x].index = mid.index) ) ) then begin
            swap( U[x], U[y] );
            inc( y );
        end;

    sortiraj( y, r, k ); (* sortiraj sve strogo vece *)
end;

procedure sazmi; begin   (* sazimanje po broju b *)
    sortiraj( 0, m, 0 );
    for i := 0 to m-1 do U[i].sorted_index := i;
    sortiraj( 0, m, 1 );
end;

procedure solve; begin    (* rjesavanje upita *)
    for i := 0 to maxt-1 do tree[i] := -1;
    for i := 0 to n-1 do begin
        if E[i].tip = 1 then update( 1, 0, m-1, E[i].who )
        else begin
            j := query( 1, 0, m-1, E[i].who );
            if j = -1 then writeln( 'NE' )
            else writeln( j+1 );
        end;
    end;
end;

begin
    load;
    sazmi;
    solve;
end.
