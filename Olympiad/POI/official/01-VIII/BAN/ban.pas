{*************************************************************************}
{*                                                                       *}
{*                   VIII Olimpiada Informatyczna                        *}
{*                                                                       *}
{*   Rozwi¹zanie zadania: BANK                                           *}
{*   Plik:                BAN.PAS                                        *}
{*   Autor:               MARCIN MUCHA                                   *}
{*************************************************************************}

{$R+,Q+}
program Bank;
const
  N_MAX = 8000;
  K_MAX = 4;

var
  wys_max, wys : array[1..N_MAX, 1..K_MAX] of word;
  n : word;
  akt: array [1..K_MAX] of longint;

type
  heap = record
     n : word;
     e, k : array[1..N_MAX] of word;
  end;

procedure heap_init( var h : heap);
begin
   h.n := 0
end;

function heap_empty( var h : heap) : boolean;
begin
   heap_empty := (h.n = 0);
end;

procedure heap_swap( var h : heap; i, j : word);
var
   tmp : word;
begin
   tmp := h.e[i]; h.e[i] := h.e[j]; h.e[j] := tmp;
   tmp := h.k[i]; h.k[i] := h.k[j]; h.k[j] := tmp
end;

procedure heap_up( var h : heap; i : word);
begin
   while (i > 1) do
   begin
      if (h.k[i div 2] > h.k[i]) then
         begin heap_swap( h, i div 2, i); i := i div 2 end
      else
         break
   end;
end;

procedure heap_down( var h : heap; i : word);
var
   j : word;
begin
   j := i;
   while true do
   begin
      if (2*i <= h.n) and (h.k[j] > h.k[2*i]) then j := 2*i;
      if (2*i+1 <= h.n) and (h.k[j] > h.k[2*i+1]) then j := 2*i+1;
      if j <> i then
         begin heap_swap( h, j, i); i := j end
      else
         break
   end;
end;

function heap_min( var h : heap) : word;
begin
   heap_min := h.k[1]
end;

function heap_get_min( var h : heap) : word;
begin
   heap_get_min := h.e[1];
   h.e[1] := h.e[h.n]; h.k[1] := h.k[h.n];
   dec( h.n);
   heap_down( h, 1)
end;

procedure heap_put( var h : heap; e, k : word);
begin
   inc( h.n);
   h.e[h.n] := e; h.k[h.n] := k;
   heap_up( h, h.n)
end;

procedure wczytaj_dane;
var
  f: text;
  i, k: integer;
begin
  assign( f, 'ban.in');
  reset( f);
  readln( f, n);
  for i := 1 to n do
  begin
     for k := 1 to K_MAX do
        read( f, wys_max[i, k]);
     for k := 1 to K_MAX do
        read( f, wys[i, k]);
  end;
  close( f)
end;

procedure oblicz;
var
   heaps : array[1..K_MAX] of heap;
   rez : array[1..K_MAX] of longint;
   i, j, k, e : word;
   zmiana : word;
begin
   for i := 1 to K_MAX do akt[i] := 0;
   for k := 1 to K_MAX do {ustalanie limitu na k-ta walute}
   begin
      for i := 1 to k do rez[i] := akt[i];
      for i := 1 to k do heap_init( heaps[i]);
      for i := 1 to n do heap_put( heaps[1], i, wys_max[i,1]-wys[i,1]);
      for i := 1 to n do
      begin
         {wybieramy kredyty mieszczace sie w limitach na waluty 1..k-1}
         for j := 1 to k-1 do
            while ( not heap_empty( heaps[j])) and ( heap_min(heaps[j]) <= rez[j]) do
            begin
               e := heap_get_min( heaps[j]);
               heap_put( heaps[j+1], e, wys_max[e,j+1]-wys[e,j+1])
            end;
         {najnizsze k}
         e := heap_get_min( heaps[k]);
         {trzeba zwiekszyc akt[k]?}
         if rez[k] < wys_max[e,k]-wys[e,k] then
         begin
            zmiana := wys_max[e,k]-wys[e,k]-rez[k];
            inc( rez[k], zmiana);
            inc( akt[k], zmiana)
         end;
         {realizujemy kredyt}
         for j := 1 to k do
            inc( rez[j], wys[e,j]);
      end;
   end;
end;

procedure wypisz_wynik;
var
  o: text;
  k: integer;
begin
  assign( o, 'ban.out');
  rewrite(o);
  for k := 1 to K_MAX do
  begin
    write( o, akt[k]);
    if k < K_MAX then
      write( o, ' ');
  end;
  writeln( o);
  close( o)
end;

begin
  wczytaj_dane;
  oblicz;
  wypisz_wynik;
end.
