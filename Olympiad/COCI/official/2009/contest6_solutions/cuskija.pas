program cuskija;

const maxn = 10000;

var
   i, n, tmp: longint;
   a: array[0..2,0..maxn] of longint; // a[i] je lista brojeva iz ulaza koji pri dijeljenju s tri daju ostatak i
   na: array[0..2] of longint; // na[i] oznacava koliko trenutno ima brojeva u a[i]

// moze kaze da li se svi brojevi koji daju ostatak jedan ili dva mogu sloziti u "k" nizova,
// tako da unutar jednog niza vrijedi da suma nijedna dva susjedna nije djeljiva sa tri
function moze( k: longint ): boolean;
begin
     moze := true;
     if k < 0 then moze := false;
     if k = 0 then moze := (na[1] + na[2] = 0);
     if k = 1 then moze := ((na[1] = 0) or (na[2] = 0));
     if k > na[1]+na[2] then moze := false;
end;


// pop(m) uzme jedan broj koji ima ostatak m sa tri iz niza a i ispise ga
function pop( m: longint ):boolean;
begin
     if na[m] = 0 then pop := false
     else begin
          write( a[ m, na[m]-1 ], ' ' );
          dec( na[m] );
          pop := true;
     end;
end;

// slaze ulazne brojeve sa ostatkom 1 ili 2 u k grupa, a izmedju grupa stavlja broj dijeljiv s tri
procedure slozi( k: longint );
begin
     while( k > 0 ) do begin
            if k = 1 then while ( pop(1) or pop(2) ) do;
            if k = 2 then begin
            if na[1] = 0 then pop(2)
               else
                   if na[2] = 0 then pop(1)
                   else while( pop(1) ) do;
            end;
            if k > 2 then begin
               if na[1] > 0 then pop(1)
               else pop(2);
            end;
            pop( 0 );
            dec( k );
     end;
end;

begin
     // ucitavanje
     read( n );
     for i := 0 to n-1 do begin
         read( tmp );
         a[ tmp mod 3, na[ tmp mod 3 ] ] := tmp;
         inc( na[ tmp mod 3 ] );
     end;
     // skombinira da li ce prva i zadnja grupa biti broj dijeljiv s tri ili ne, i onda pozove slozi
     if moze( na[0]-1 ) then begin
        pop( 0 );
        slozi( na[0] );
        exit;
     end;
     if moze( na[0] ) then slozi( na[0] )
     else if moze( na[0]+1 ) then slozi( na[0]+1 )
     else writeln( 'impossible' );
end.
