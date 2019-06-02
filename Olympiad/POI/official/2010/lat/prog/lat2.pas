(*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:           Latarnia (LAT)                                   *
 *   Plik:              lat2.pas                                         *
 *   Autor:             Wojciech Smietanka                               *
 *   Opis:              Rozwiazanie wzorcowe.                            *
 *   Zlozonosc czasowa: O((n + m) * W * log ((n + m) * W))               *
 *                                                                       *
 *************************************************************************)

type
    rectangle=record 
                  xl, yl, xu, yu : longint; 
                  id: longint; 
               end; 
    event=record
            y:longint;     
            x1,x2,id:longint; 
            add:boolean; 
           end; 

const 
    max_r = 607; 
    max_e = 2600000;
    max_ref = 1024;  
    MAX_H = 1010;  
    const multiply = 1070000; { multiply > max_reflections ** 2 } 
var
    t:array[0..1,0..max_r] of rectangle; 
    w:array[0..max_e] of event; 
    smax, all, v1, v2: array[0..max_e] of longint; 
    n: array[0..1] of longint; 
    res, tres: array[0..max_r] of boolean; 
    plus, v1l, v2l, i, j, NN, O, pw, cc, k, ps, max_val, a1, a2, ec: longint; 
    inter: array[0..max_r,0..1] of longint; 
    r:rectangle;  

    function scale(a:longint; var r:rectangle) : rectangle; 
        var 
            ret : rectangle; 
        begin
            ret.xl := (multiply * r.xl) div a; 
            ret.yl := (multiply * r.yl) div a; 
            ret.xu := (multiply * r.xu) div a; 
            ret.yu := (multiply * r.yu) div a; 
            ret.id := r.id; 
            scale := ret;            
        end; 

    function max(a,b:longint):longint; 
        begin
            if a > b then max := a
            else max := b; 
        end; 

    function min(a,b:longint):longint; 
        begin
            if a < b then min := a
            else min := b; 
        end; 

    function find_max_cover(a,acc:longint):longint; 
        begin
            if (a >= NN) then find_max_cover := a 
            else begin
                acc := acc + all[a]; 
                if (smax[2*a]+all[2*a]+acc = smax[a]+acc) then find_max_cover := find_max_cover(2*a,acc) 
                else find_max_cover := find_max_cover(2*a+1,acc); 
            end;            
        end;         

    procedure init(_N, _O:longint); 
        var i : longint; 
        begin             
            O := _O; 
            NN := _N; 
            while ((NN and (NN-1)) > 0) do inc(NN); 
            for i := 1 to 2 * NN do 
                begin
                    smax[i]:=0; 
                    all[i]:=0;
                end;
            for i := 0 to max_r - 1 do 
                begin
                   inter[i,0] := 0; 
                   inter[i,1] := -1; 
                   tres[i] := false; 
                end;              
        end;     

    procedure update_node(a:longint); 
        begin
            smax[a] := max(smax[2*a]+all[2*a], smax[2*a+1]+all[2*a+1]); 
        end;          

    procedure add(a,b,val,id:longint; recursive:boolean); 
        var
          tmp,va,vb,it:longint; 
        begin 
            if (id <> 0) then begin
                    if val > 0 then begin
                        inter[id,0] := a; 
                        inter[id,1] := b;                         
                    end 
                    else begin
                        inter[id,0] := 0; 
                        inter[id,1] := -1; 
                        if tres[id] then exit;  
                    end;
           end;        
            va:=a + NN; 
            vb:=b + NN; 
            all[va]:=all[va]+val; 
            while ((va shr 1) <> (vb shr 1)) do begin
                if ((va and 1) = 0) then all[va+1]:=all[va+1]+val; 
                if ((vb and 1) = 1) then all[vb-1]:=all[vb-1]+val; 
                va:=(va shr 1); 
                vb:=(vb shr 1); 
                update_node(va); 
                update_node(vb); 
             end; 

             while (va <> 1) do 
                begin
                    va:=(va shr 1); 
                    update_node(va); 
                end; 

            if (not recursive) then exit; 

            while (smax[1]+all[1]=O) do begin 
                it := 1; 
                tmp := find_max_cover(1, 0) - NN;  
                            
                 while it <= n[0] do begin
                     if (max(inter[it,0], tmp) < min(inter[it,1], tmp + 1)) then 
                        begin
                           add(inter[it,0],inter[it,1],-1,it,false); 
                            tres[it] := true; 
                           it:=n[0]; 
                        end;                          
                     inc(it); 
                end;                         
            end;                     
        end;     
         
    procedure qsort1(a,b:longint); 
        var 
           l,m,r:longint; 
           tmp:event;        
        begin            
            m := w[(a + b) div 2].y; 
            l := a; 
            r := b; 

            repeat
                while (w[l].y < m) do inc(l); 
                while (w[r].y > m) do dec(r);  
                if (l <= r) then begin 
                    tmp := w[l]; 
                    w[l] := w[r]; 
                    w[r] := tmp; 
                    inc(l); 
                    dec(r);                    
                end;         
            until l >= r; 
            if (a < r) then qsort1(a, r); 
            if (l < b) then qsort1(l, b); 
        end;
     
    procedure qsort2(a,b:longint); 
        var 
           l,m,r:longint; 
           tmp:longint; 
        begin            
            m := v1[(a + b) div 2]; 
            l := a; 
            r := b; 

            repeat
                while (v1[l] < m) do inc(l); 
                while (v1[r] > m) do dec(r);  
                if (l <= r) then begin 
                    tmp := v1[l]; 
                    v1[l] := v1[r]; 
                    v1[r] := tmp; 
                    inc(l); 
                    dec(r);                    
                end;         
            until l >= r; 
            if (a < r) then qsort2(a, r); 
            if (l < b) then qsort2(l, b); 
        end;
       
    function convert(a:longint):longint; 
        var i1, i2, i3:longint; 
        begin
            i1 := 0; 
            i3 := v2l; 
            i2 := 0;  
            while (i3 - i1 > 1) do 
                begin
                    i2 := (i1 + i3) div 2; 
                    if (v2[i2] <= a) then i1 := i2 
                    else i3 := i2; 
                end;                    
           convert:=i1; 
        end; 

             

procedure wypisz(e:event); 
begin
    writeln(e.y,' ',e.x1,' ',e.x2); 
end; 
    
begin
    readln(n[0], n[1]); 
    for i := 0 to 1 do 
        for j := 0 to n[i] - 1 do 
            readln(t[i,j].xl,t[i,j].yl,t[i,j].xu,t[i,j].yu); 

    pw := 2; 
    for i:=0 to n[0] do res[i] := false;  
    ec := 0; 

    while (pw <= max_ref) do begin
        v1l := 0; 
        for k := 1 to pw do 
            begin
                ps := k mod 2; 
                for i := 0 to n[ps]-1 do 
                    begin
                       v1[v1l] := (t[ps][i].xl * multiply) div k; 
                       inc(v1l); 
                       v1[v1l] := (t[ps][i].xu * multiply) div k; 
                       inc(v1l); 
                    end; 
            end;
           
            qsort2(0, v1l-1);  
        v2l := 1; 
        v2[0] := v1[0]; 
        for i := 1 to v1l - 1 do 
            if v1[i] > v1[i-1] then 
                begin
                    v2[v2l] := v1[i]; 
                    inc(v2l); 
                end;                     

        max_val := (MAX_H * multiply) div pw; 
        ec := 0;  

        for k := 1 to pw do 
            begin
                ps := k mod 2; 
                for i := 0 to n[ps]-1 do begin
                    r := scale(k, t[ps][i]); 
                    if (R.yl >= max_val) or (R.xu <= -max_val) or (R.xl >= max_val) then
                        continue; 
                    a1 := convert(r.xl); 
                    a2 := convert(r.xu);                     
                    w[ec].x1 := a1;      
                    w[ec].x2 := a2; 
                    w[ec].y := R.yl * 2; 
                    w[ec].add := true; 
                    if (k = pw) then w[ec].id := i + 1 else w[ec].id := 0; 
                    inc(ec); 

                    w[ec].x1 := a1;      
                    w[ec].x2 := a2; 
                    w[ec].y := R.yu * 2 - 1; 
                    w[ec].add := false; 
                    if (k = pw) then w[ec].id := i + 1 else w[ec].id := 0; 
                    inc(ec);               
                end;                                    
            end;         
            qsort1(0, ec-1); 
            init(v2l, pw); 
            for i:=0 to ec-1 do begin
                if w[i].add then plus := 1 else plus := -1; 
                if (w[i].id = 0) or (not res[w[i].id]) then 
                     add(w[i].x1,w[i].x2,plus,w[i].id,true);            
            end; 
            for i:=1 to n[0] do if tres[i] then res[i] := true;                 
        pw := pw * 2; 
    end; 

    cc := 0;
    for i := 1 to n[0] do 
        if res[i] then cc := cc + 1; 

    writeln(cc); 
    for i := 1 to n[0] do 
        if res[i] then write(i,' '); 

    writeln();     
end. 
