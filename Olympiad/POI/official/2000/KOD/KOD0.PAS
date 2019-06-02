program Kody_Drzew_Binarnych;

{Wersja najprostsza; autor programu: W. Guzicki}

uses Crt;



const

    MaxN = 19;



type

    Tablica = array [0..MaxN] of longint;



var

    Catalan : Tablica;



procedure Oblicz_Liczby_Catalana;

    var

        k,i  : integer;

        suma : longint;

    begin

        {Stosujemy wz¢r rekurencyjny.}

        Catalan[0]:=1;

        Catalan[1]:=1;

        for k:=2 to MaxN do begin

            suma:=0;

            for i:=0 to k-1 do

                suma:=suma+Catalan[i]*Catalan[k-i-1];

            Catalan[k]:=suma

        end

    end;



function Kod (cp : char; n : longint; k : integer) : String;

    {cp : litera pocz¥tkowa kodu drzewa;

     n  : numer kodu drzewa w˜r¢d drzew maj¥cych wierzchoˆki

          oznaczone literami od cp do ck; zakˆadamy, ¾e liczba

          nr nie przekracza liczby Catalana C[k];

     k  : liczba wierzchoˆk¢w drzewa}

    var

        l,p             : integer; {liczba wierzchoˆk¢w w lewym

                                    i prawym poddrzewie}

        Suma            : longint; {suma iloczyn¢w liczb Catalana}

        Suma_Poprzednia : longint;

        m               : longint;

        n1,n2           : longint; {numery lewego i prawego poddrzewa}

        znak            : char;

    begin

        if (k=0) then

            Kod:=''

        else if (k=1) then

            Kod:=cp

        else begin

            Suma:=0;

            l:=-1;

            p:=k;

            repeat

                l:=l+1;

                p:=p-1;

                Suma_Poprzednia:=Suma;

                Suma:=Suma+Catalan[l]*Catalan[p];

            until (Suma>=n);

            znak:=chr(ord(cp)+l);

            m:=n-Suma_Poprzednia;

            n1:=((m-1) div Catalan[p])+1;

            n2:=((m-1) mod Catalan[p])+1;

            Kod:=znak+Kod(cp,n1,l)+Kod(succ(znak),n2,p)

        end

    end;



var

    Input_File : Text;

    Output_File : Text;

    n    : longint;

    k    : integer;



begin

    Oblicz_Liczby_Catalana;

    assign(Input_File,'kod.in');

    reset(Input_File);

    assign(Output_File,'kod1.out');

    rewrite(Output_File);

    readln(Input_File,n,k);

    writeln(Output_File,Kod('a',n,k));

    close(Input_File);

    close(Output_File)

end.

