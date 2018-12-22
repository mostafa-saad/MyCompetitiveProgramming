program ime;
var L,N,P,K,i,j,max1,max2,tko1,tko2,koliko:integer;
    orah:array[1..1000] of integer;
begin
     readln(L);
     readln(N);

     for i:=1 to L do
         orah[i]:=1;

     max1:=0; max2:=0; tko1:=1; tko2:=1;
     for i:=1 to N do
     begin
          readln(P,K);

          if K-P+1>max1 then begin max1:=K-P+1; tko1:=i; end;

          koliko:=0;
          for j:=P to K do
          begin
              if orah[j]=1 then
              begin
                   koliko:=koliko+1;
                   orah[j]:=0;
              end;
          end;

          if koliko>max2 then begin max2:=koliko; tko2:=i; end;
     end;

     writeln(tko1);
     writeln(tko2);



readln;
end.
