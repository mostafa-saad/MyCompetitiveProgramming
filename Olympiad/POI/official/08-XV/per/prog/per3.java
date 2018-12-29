/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Permutacja (PER)                                          *
 *   Plik:     per3.java                                                 *
 *   Autor:    Wojciech Tyczynski, Marcin Pilipczuk                      *
 *   Opis:     Rozwiazanie o złożoności O(z+n(lgz+lgm)+(lgm)^2).         *
 *                                                                       *
 *************************************************************************/

import java.io.*;
import java.util.*;

public class per3 implements Runnable{
    public static void main(String[] args){
        new Thread(new per3()).start();
    }

    final static int MAX_N = 300000;

    int n,m;    // liczby z tresci zadania
    int[] T;    // permutacja z zadania
    int najw;    // najwiekszy element w permutacji
    int h;      // wysokosc drzewa licznikowego
    int[] ilosc;  // wezly drzewa licznikowego
    int[] pod,wyk;    // m=pod[0]^wyk[0] * ...
    int[] dziel;    // m=dziel[0]*dziel[1]*.. oraz NWD(dziel[i],dziel[j])=1 dla i<>j
    int s;      // ilosc roznych liczb pierwszych dzielacych m

    public per3(){
        pod = new int[10];
        wyk = new int[10];
        dziel = new int[10];
        ilosc = new int[1048601];
        T = new int[MAX_N];
    }

    // rozszerzony algorytm Euklidesa
    // dostajac na wejsciu liczby a oraz b
    // zwraca trojke liczb takich, ze a*res[0]+b*res[1]=NWD(x,y)
    int NWD(int a, int b, long[] res)
    {
        if (b == 0)
        {
            res[0] = a; res[1] = 0;
            return a;
        }
        else
        {
            long[] r1 = new long[2];
            int d1 = NWD(b,a%b,r1);
            res[0]=r1[1];
            res[1]=r1[0]-r1[1]*(a/b);
            return d1;
        }
    }


    // funkcja obliczajaca odwrotnosc pewnej liczby s modulo t
    // na wejsciu musi byc spelniony warunek NWD(s,t)=1
    int odwrotnosc(int s, int t)
    {
        long[] r = new long[2];
        NWD(s,t,r);
        return (int)((r[0]%t+t)%t);
    }

    int najwiekszy_element(int[] tab, int n){
        int x = tab[0];
        for (int i = 0; i < n; ++i)
            if (x < tab[i])
                x = tab[i];
        return x;
    }
    // fukcja ktora buduje pelne statyczne drzewo licznikowe
    // najw - najwiekszy element permutacji T
    // h    - wysokosc drzewa
    void buduj_drzewo()
    {
        najw=najwiekszy_element(T, n);

        // aby wygodnie korzystalo sie z drzewa
        // potrzebujemy aby mialo conajmniej najw+1 lisci
        // ktore kolejno beda odpowiadac liczbom 0,..,najw
        for(h=0; (1<<h)<najw+1; h++);

        // teraz liscie drzewa maja w tablicy numery 2^h,..,2^(h+1)-1
        int pom=(1<<h);

        for(int i=0; i<n; i++)
            ilosc[pom+T[i]]++;
        for(int i=pom-1; i>0; i--)
            ilosc[i]=ilosc[2*i]+ilosc[2*i+1];
    }


    // funkcja modyfikujaca drzewo licznikowe
    // wstaw(x,ile) zmienia ilosc elementow x o ile
    void wstaw(int x, int ile)
    {
        int i=(1<<h)+x;
        ilosc[i]+=ile;i/=2;
        while (i != 0)
        {
            ilosc[i]=ilosc[2*i]+ilosc[2*i+1];
            i/=2;
        }
    }


    // fukcja zwracajaca ilosc elementow mniejszych niz x
    int mniejsze(int x)
    {
        int i=(1<<h)+x,res=0;
        while (i>1)
        {
            if (i%2 != 0)
                res+=ilosc[i-1];
            i/=2;
        }
        return res;
    }

    // fukcja rozkladajaca m na czynniki pierwsze
    // po wywolaniu tej funkcji mamy:
    // m=pod[0]^wyk[0]*pod[1]^wyk[1]*..
    void rozklad_m()
    {
        int M=m;
        s=0;
        for(int i=2; i*i<=m; i++)
            if (M%i==0)
            {
                int il=0,t=1;
                while (M%i==0){
                    M/=i; il++; t*=i;
                }
                pod[s]=i;
                wyk[s]=il;
                dziel[s++]=t;
            }
        if (M>1)
        {
            pod[s]=M;
            wyk[s]=1;
            dziel[s++]=M;
        }
    }


    // funkcja wykonujaca szybkie potegowanie
    // dostajac na wejsciu x,n,m, oblicza x^n mod m
    int potega(int x, int n, int m)
    {
        long res=1,akt=(long)x;
        while (n != 0)
        {
            if (n%2 == 1)
            {
                res=(res*akt)%m;
                n--;
            }
            akt=(akt*akt)%m;
            n/=2;
        }
        return (int)res;
    }


    // trzy funkcje do obslugi naszej reprezentacji liczb
    // gdzie liczba pierwsza dla tej reprezentacji jest pod[nr]
    // 1) funkcja zwracajaca wartosc modulo dziel[nr]
    // 2) funkcja mnozaca liczbe w naszej reprezentacji przez int
    // 3) funkcja dzielaca liczbe w naszej reprezentacji przez int

    public static class Para{
        public int first;
        public int second;
    }

    int wartosc(Para x, int nr)
    {
        if (x.second>=wyk[nr])
            return 0;
        return (int)((((long)potega(pod[nr],x.second,dziel[nr]))*x.first)%dziel[nr]);
    }


    Para pomnoz(Para wo, int x, int nr)
    {
        int p=pod[nr];
        Para w = new Para();
        w.first = wo.first; w.second=wo.second;
        while (x%p==0){
            w.second++; x/=p;
        }
        w.first=(int)(((long)(w.first)*x)%dziel[nr]);
        return w;
    }


    Para podziel(Para wo, int x, int nr)
    {
        int p=pod[nr];
        Para w = new Para();
        w.first = wo.first; w.second=wo.second;
        while (x%p==0){
            w.second--; x/=p;
        }
        w.first=(int)(((long)(w.first)*odwrotnosc(x,dziel[nr]))%dziel[nr]);
        return w;
    }


    // funkcja obliczajaca SO i zwracajaca wynik w naszej reprezentacji
    // gdzie liczba pierwsza dla tej reprezentacji jest pod[nr]
    // oraz S0=(n-1)!/[l1!*...*lnajw!]
    Para oblicz_S0(int nr)
    {
        Para res= new Para();
        res.first = 1; res.second = 0;
        for(int i=2; i<n; i++)
            res=pomnoz(res,i,nr);

        int pom=(1<<h);
        for(int i=1; i<=najw; i++)
            for(int j=2; j<=ilosc[pom+i]; j++)
                res=podziel(res,j,nr);

        return res;
    }


    // funkcja skladajaca wynik z chinskiego twierdzenia o resztach
    // dane wejsciowe reprezentuja: m=dziel[0]*..*dziel[s-1]
    // ponadto wynik = a[i] (modulo dziel[i])
    int chinskie_twierdzenie(int s, int[] a)
    {
        int[] w = new int[10], c = new int[10];
        for(int i=0; i<s; i++)
        {
            w[i]=m/dziel[i];
            c[i]=(int)(((long)(w[i]))*odwrotnosc(w[i],dziel[i]));
        }

        long res=0;
        for(int i=0; i<s; i++)
            res+=((long)a[i])*c[i];
        res%=m;
        return (int)res;
    }


    // funkcja obliczajaca wynik - po dokladny sposob dzialania
    // odsylam do opracowania
    int oblicz_wynik()
    {
        Para[] temp = new Para[10];
        int[] a = new int[10];
        int ile;

        ile=mniejsze(T[0]);
        for(int i=0; i<s; i++)
        {
            temp[i]=oblicz_S0(i);
            a[i]=0;

            if (ile!=0)
            {
                temp[i]=pomnoz(temp[i],ile,i);
                a[i]=wartosc(temp[i],i);
                temp[i]=podziel(temp[i],ile,i);
            }
        }

        for(int i=1; i<n-1; i++)
        {
            for(int j=0; j<s; j++)
            {
                temp[j]=pomnoz(temp[j],ilosc[(1<<h)+T[i-1]],j);
                temp[j]=podziel(temp[j],n-i,j);
            }

            wstaw(T[i-1],-1);
            ile=mniejsze(T[i]);
            if (ile == 0)
                continue;

            for(int j=0; j<s; j++)
            {
                temp[j]=pomnoz(temp[j],ile,j);
                a[j]+=(int)(wartosc(temp[j],j));
                a[j]%=dziel[j];
                temp[j]=podziel(temp[j],ile,j);
            }
        }

        return (chinskie_twierdzenie(s,a)+1)%m;
    }

    public void run(){
        try{
            BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
            String linia = br.readLine();
            StringTokenizer st = new StringTokenizer(linia);
            n = Integer.parseInt(st.nextToken());
            m = Integer.parseInt(st.nextToken());
            linia = br.readLine();
            st = new StringTokenizer(linia);
            for (int i = 0; i < n; ++i)
                T[i] = Integer.parseInt(st.nextToken());
            buduj_drzewo();
            rozklad_m();

            int res=oblicz_wynik();
            System.out.println(res);
        }catch(Exception e){
            throw new RuntimeException(e);
        }
    }
};

