program PROGI;
uses Crt;

const
    Max = 9;

type
    Tablica  = array [0..Max,0..Max] of real;
    TabPstwa = array [0..Max] of real;

var
    Newton,Prog : Tablica;
    Pstwo       : TabPstwa;

procedure ZapoczatkowanieNewtona;
    { Oblicza wartosci wspolczynnikow dwumianowych (symboli Newtona). }
    var
        n,k : integer;
    begin
        for n:=0 to Max do
            Newton[n,0]:=1;
        for k:=1 to Max do
            Newton[0,k]:=0;
        for n:=1 to Max do
            for k:=1 to Max do
                Newton[n,k]:=Newton[n-1,k-1]+Newton[n-1,k]
    end;

function Potega (x : real; n : integer) : real;
    { Oblicza potege x^n. }
    var
        p : real;
        i : integer;
    begin
        p:=1;
        for i:=1 to n do
            p:=p*x;
        Potega:=p
    end;

procedure Oblicz;
    var
        m,k,i,j : integer;
        Licznik,Mianownik,Znak,Suma : real;
    begin
        Pstwo[0]:=1;
        Pstwo[1]:=1;
        Pstwo[2]:=0.75;
        for m:=1 to Max do begin
            Prog[m,0]:=0;
            Prog[m,m]:=1
        end;
        Prog[2,1]:=0.5;
        for m:=3 to Max do begin
            { Obliczamy wartosci progow ze wzoru (1) }
            for k:=1 to m-1 do begin
                Licznik:=k*Pstwo[k-1]*Pstwo[m-k];
                Mianownik:=Licznik+(m-k)*Pstwo[k]*Pstwo[m-k-1];
                Prog[m,k]:=Licznik/Mianownik
            end;
            {tu obliczamy prawdopodobienstwa}
            Suma:=0;
            for i:=0 to m-1 do begin
                Znak:=1; {Znak = (-1)^j; dla j=0 mamy Znak=1}
                for j:=0 to m-1-i do begin
                    licznik:=Potega(Prog[m,i+1],i+j+1)-
                             Potega(Prog[m,i],i+j+1);
                    Suma:=Suma+Znak*Newton[m-1,i]*Newton[m-1-i,j]*
                               Pstwo[i]*Pstwo[m-1-i]*Licznik/(i+j+1);
                    Znak:=-Znak {Znak := Znak * (-1)}
                end;
            end;
            Pstwo[m]:=Suma
        end
    end;

procedure Wypisz;
    var
        i,j : integer;
        Plik : Text;
    begin
        assign(Plik,'ukl-teor.txt');
        rewrite(Plik);
        for i:=1 to Max do begin
            for j:=0 to i do
                write(Plik,Prog[i,j]:10:6);
            writeln(Plik);
            writeln(Plik,Pstwo[i]:10:6);
            writeln(Plik)
        end;
        close(Plik)
    end;

begin
    ZapoczatkowanieNewtona;
    Oblicz;
    Wypisz
end.
