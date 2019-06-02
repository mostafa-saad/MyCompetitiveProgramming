unit zga;

interface

const ILE_LICZB = 9;

procedure inicjalizuj;
procedure nowa_rozgrywka;
function kolejna_liczba (x : Double) : Integer;

implementation

procedure inicjalizuj;
begin
{ ta funkcja zostanie wywolana tylko raz, na poczatku;
  tutaj mozesz zainicjalizowac zmienne }
end;

procedure nowa_rozgrywka;
begin
{ ta funkcja zostanie wywolana na poczatku kazdej rozgrywki;
  tutaj mozesz zainicjalizowac zmienne zwiazane z jedna rozgrywka }
end;

function kolejna_liczba (x : Double) : Integer;
begin
{ parametr x okresla kolejna wylosowana liczbe;
  tutaj wpisz kod strategii obliczajacej, ktora co do wielkosci liczba w zestawie jest x
  wynik powinien byc zwrocony przez funkcje }
end;

end.
