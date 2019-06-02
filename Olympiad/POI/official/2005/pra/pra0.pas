(*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: PRA (Prawoskrêtny wielb³ad)                    *
 *   Plik:                pra0.pas                                       *
 *   Autor:               Karol Cwalina                                  *
 *   Opis:                Rozwiazanie wzorcowe                           *
 *                        Z³o¿onosæ czasowa: O(n^2*logn)                 *
 *                        Porownywanie wektorow poprzez porownywanie     *
 *                        wczesniej policzonych katow; Oszczedna, tzn.   *
 *                        odrzuca nieprzydatne punkty z sortowania       *
 *                        w sortWzgledemPoKacie                          *
 *                                                                       *
 *************************************************************************)

program prawoskretny_wielblad;

const MaxN = 1000;
      Inf = 1234567890;

type Pkt = object
             x, y : Int64;
             procedure wczytaj;
             function kat : Int64; {kat to rosnaca funkcja kata skierowanego utworzonego pomiedzy polprosta OY a wketorem (x,y)}
           end;

  procedure Pkt.wczytaj;
  begin
    Readln (x,y);
  end;

  function Pkt.kat : Int64;
  var Duza : Int64; {gdyby mozna bylo deklarowac stale > 2^32, to bylaby stala}
  begin
    Duza := Int64(20000)*Int64(1000000);
    if x >= 0 then
      if y > 0 then Exit((Duza*x) div (x+y))
               else Exit(2*Duza - ((Duza*x) div (x-y)))
    else
      if y < 0 then Exit(2*Duza + ((Duza*x) div (x+y)))
               else Exit(4*Duza - ((Duza*x) div (x-y)));
  end;

  operator - (var a,b : Pkt) c : Pkt;
  begin
    c.x := a.x - b.x;
    c.y := a.y - b.y;
  end;

  operator <= (a,b : Pkt) c : Boolean;
  { A < B <=> wektor A lezy na lewo od B (zaczepione w (0,0)); = <=> wektory sa rownolegle }
  begin
    c := a.x*b.y - a.y*b.x <= 0;
  end;

type TPkt = array [0..MaxN-1] of Pkt;
     TLongIntVec = array [0..MaxN-1] of LongInt;
     TInt64Vec = array [0..MaxN-1] of Int64;
     Oaza = record
              sas : TLongIntVec;
              ile_pop,ile_nast : LongInt;
            end;
     TOaz = array [0..MaxN-1] of Oaza;
     TIle = array [0..MaxN-1,0..MaxN-1] of LongInt;

var pun : TPkt; {pun - tablica punktow reprezentujacych oazy}
    oaz : TOaz; {oaz - tablica oaz}
    ile : TIle; {ile - tablica wartosci ile[a,b] (patrz opracowanie)}
    n,odp : LongInt; {n - liczba oaz, odp - odpowiedz}
    kat : TInt64Vec; {kat - stablicowane katy wykorzystywane w sortWzgledemPoKacie (stablicowanie pozwala uniknac wielokrotnego wyliczania wartosci i znaczaco przyspiesza --- patrz pra1.cpp)}

  function MAX (a,b : LongInt) : LongInt;
  begin
    if a >= b then Exit(a)
              else Exit(b);
  end;

  function VEC(a,b : LongInt) : Pkt;
  begin
    VEC := pun[b]-pun[a];
  end;

  procedure Wczytaj;
  var i,j : LongInt;
  begin
    Readln (n);
    for i := 0 to n-1 do pun[i].wczytaj;

    for i := 0 to n-1 do
      for j := 0 to n-1 do ile[i,j] := -Inf;
  end;

  procedure SortPkt (d,g : LongInt);
  var l,p : LongInt;
      s,z : Pkt;

    function Mniej (var a,b : Pkt) : Boolean;
    { Porownuje w "porzadku zegarowym" wzgledem pun[1] (1-szej oazy, do ktorej mamy dojsc), traktujac punkty jak wektory zaczepione w (0,0) }
    var k1,k2 : Int64;
        Duza : Int64;  {gdyby mozna bylo deklarowac stale > 2^32, to bylaby stala}
    begin
      Duza := Int64(20000)*Int64(1000000);
      k1 := (4*Duza + a.kat - pun[1].kat) mod (4*Duza); {dzieki temu kat jest liczba z przedzialu [0,4*Duza)}
      k2 := (4*Duza + b.kat - pun[1].kat) mod (4*Duza); {dzieki temu kat jest liczba z przedzialu [0,4*Duza)}
      Mniej := k1 < k2;
    end;

  begin
    l := d; p := g;
    s := pun[(d+g) shr 1];
    repeat
      while Mniej(pun[l],s) do Inc(l);
      while Mniej(s,pun[p]) do Dec(p);
      if l <= p then begin
        z := pun[l];
        pun[l] := pun[p];
        pun[p] := z;
        Inc(l); Dec(p);
      end;
    until l > p;
    if d < p then SortPkt(d,p);
    if l < g then SortPkt(l,g);
  end;

  procedure SortW (var co : TLongIntVec;
                   d,g : LongInt);
  var l,p,s,z : LongInt;
  begin
    if d >= g then Exit;
    l := d; p := g;
    s := co[(d+g) shr 1];
    repeat
      while kat[co[l]] < kat[s] do Inc(l);
      while kat[s] < kat[co[p]] do Dec(p);
      if l <= p then begin
        z := co[l];
        co[l] := co[p];
        co[p] := z;
        Inc(l); Dec(p);
      end;
    until l > p;
    SortW (co,d,p);
    SortW (co,l,g);
  end;

  procedure SortWzgledemPoKacie (ss : LongInt;
                                 wzgledem : Pkt;
                                 var co : TLongIntVec;
                                 d,g : LongInt);
  { Sortuje przekazana tablice w "porzadku zegarowym" wzgledem wektora wzgledem, odpowiadajacemu 12-ej w tym porzadku
    ss - srodek sortowania, tzn. nr punktu w ktorym tymczasowo zaczepiamy srodek ukladu wspolrzednych }
  var i : LongInt;
      kz : Int64; {kz - kat zwrocony przez wektor wzgledem ktorego sortujemy}
      Duza : Int64; {gdyby mozna bylo deklarowac stale > 2^32, to bylaby stala}
  begin
    Duza := Int64(20000)*Int64(1000000);
    kz := wzgledem.kat;
    for i := d to g do
      kat[co[i]] := (4*Duza + VEC(ss,co[i]).kat - kz) mod (4*Duza);
    SortW (co,d,g);
  end;

  procedure SortujListy;
  { Buduje listy oaz[].sas i sortuje je w porzadku zegarowym (kazda z czesci: oazy poprzedzajace i nastepne osobno);
   porzadek sortowan jest taki, by dla a < ile_pop i ile_pop <= c1 < c2 < ile_pop+ile_nast zachodzilo: w_prawo (a,b,c1) => w_prawo(a,b,c2) }
  var a,b,c : LongInt;
  begin
    for b := 1 to n-1 do begin
      if b > 1 then oaz[b].ile_pop := 0 {tylko do oazy nr 1 mozna pojsc z oazy nr 0 !!!}
      else begin
        oaz[b].ile_pop := 1;
        oaz[b].sas[0] := 0;
      end;
      oaz[b].ile_nast := 0;

      for a := 1 to b-1 do
        if VEC(a,b) <= VEC(a,0) then begin {odrzucamy te oazy, z ktorych nie da sie dojsc nie przecinajac naszej trasy}
          oaz[b].sas[ oaz[b].ile_pop ] := a;
          Inc(oaz[b].ile_pop);
        end;
      for c := b+1 to n-1 do
        if VEC(b,c) <= VEC(b,0) then begin {odrzucamy te oazy, do ktorych nie da sie dojsc nie przecinajac naszej trasy}
          oaz[b].sas[ oaz[b].ile_pop+oaz[b].ile_nast ] := c;
          Inc(oaz[b].ile_nast);
        end;

      SortWzgledemPoKacie (b,VEC(b,0),oaz[b].sas,0,oaz[b].ile_pop-1);
      SortWzgledemPoKacie (b,VEC(0,b),oaz[b].sas,
                        oaz[b].ile_pop,oaz[b].ile_pop+oaz[b].ile_nast-1);
    end;
  end;

  procedure Sortuj;
  { Wykonuje dwa sortowania: wszystkich oaz oraz list sasiadow kazdej z oaz w "porzadku zegarowym" }
  var i : LongInt;
  begin
    for i := n-1 downto 0 do pun[i] := pun[i]-pun[0];

    SortPkt(2,n-1);
    SortujListy;
  end;

  function w_prawo (a,b,c : LongInt) : Boolean;
  { Sprawdza, czy zakret pun[a],pun[b],pun[c] jest zakretem w prawo }
  begin
    w_prawo := VEC(a,b) <= VEC(b,c); {to wystarczy tylko dlatego, ze odrzucilismy juz tych poprzednikow i nastepcow, z ktorych nie da sie dojsc bez przecinania trasy}
  end;

  procedure Licz;
  { Wylicza liczby ile[a,b] }
  var a,b,c,maxi : LongInt;
  begin
    odp := 1;
    ile[0,1] := 1;
    for b := 1 to n-1 do begin
      a := 0; c := oaz[b].ile_pop;
      maxi := -Inf;
      while c < oaz[b].ile_pop+oaz[b].ile_nast do begin
        while (a < oaz[b].ile_pop) and w_prawo(oaz[b].sas[a],b,oaz[b].sas[c]) do begin
          maxi := MAX(maxi,ile[oaz[b].sas[a],b]);
          Inc(a);
        end;
        ile[b,oaz[b].sas[c]] := MAX(ile[b,oaz[b].sas[c]],1+maxi);
        odp := MAX(odp,ile[b,oaz[b].sas[c]]);
        Inc(c);
      end;
    end;
  end;

begin
  Wczytaj;

  Sortuj;
  Licz;

  Writeln (odp);
end.
