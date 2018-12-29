{
  Implementacja przyk³adowego modulu HSM dla zawodnika w Pascalu
  Autor: Tomek Czajka
}

unit hsm;

interface

function sprawdz(pin: array of Longint; a: array of Longint): Boolean;

procedure wynik(pin: array of Longint);


implementation

const zainicjowany: Boolean = false;
const zapytania: Longint = 0;
var zaszyfrowany: array[0..3] of Longint;

procedure inicjuj;
var
  buf: String;
  i,x: Longint;
  
begin
  write('Podaj zaszyfrowany numer karty (szesnastkowo): ');
  read(buf);
  if length(buf)<4 then begin
    writeln('Za krotki');
    halt(1);
  end;
  for i:=0 to 3 do begin
    if (buf[i+1]>='0') and (buf[i+1]<='9') then x:=ord(buf[i+1])-ord('0')
    else if (buf[i+1]>='a') and (buf[i+1]<='f') then x:=ord(buf[i+1])-ord('a')+10
    else if (buf[i+1]>='A') and (buf[i+1]<='F') then x:=ord(buf[i+1])-ord('A')+10
    else begin
      writeln('Zla litera');
      halt(1);
    end;
    zaszyfrowany[i] := x;
  end;
  zainicjowany := true;
end;

function sprawdz(pin: array of Longint; a: array of Longint): Boolean;
var i: Longint;
begin
  if not zainicjowany then inicjuj();
  
  inc(zapytania);

  for i:=0 to 3 do begin
    if (pin[i]<0) or (pin[i]>9) then begin
      writeln('PIN spoza zakresu');
      halt(1)
    end
  end;
  
  for i:=0 to 15 do begin
    if (a[i]<0) or (a[i]>9) then begin
      writeln('element tablicy konwersji spoza zakresu');
      halt(1)
    end
  end;

  for i:=0 to 3 do begin
    if pin[i]<>a[zaszyfrowany[i]] then exit(false);
  end;
  
  exit(true);
end;

procedure wynik(pin: array of Longint);
var
  i: Longint;
  a: array [0..15] of Longint;
begin
  for i:=0 to 15 do a[i]:=i mod 10;
  
  if sprawdz(pin,a) then writeln('OK')
  else writeln('ZLE');
  
  dec(zapytania);
  
  writeln('Liczba zapytan: ', zapytania);
  halt(0);
end;

begin
end.
