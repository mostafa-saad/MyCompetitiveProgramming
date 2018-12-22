program mortadela;
var X0,Y0,Xi,Yi,n,i:integer;
    cijena:real;
begin
     readln(X0,Y0);
     readln(n);

     cijena:=X0/Y0;

     for i:=1 to n do
     begin
          readln(Xi,Yi);

          if Xi/Yi<cijena then
             cijena:=Xi/Yi;
     end;

     writeln(cijena*1000:0:2);

readln;
end.
