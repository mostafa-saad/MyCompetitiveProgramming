(*
  Przykladowe rozwiazanie zadania Licytacja (niezbyt madre)
*)
uses pliclib;

var n: longint;
var x: longint;

begin
  n := inicjuj();
  while true do
  begin
    alojzy(1); { Alojzy zawsze pasuje }
    x := bajtazar(); { Wczytujemy ruch Bajtazara, ale go ignorujemy }
  end;
end.
