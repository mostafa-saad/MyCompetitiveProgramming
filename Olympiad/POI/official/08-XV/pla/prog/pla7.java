/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Plakatowanie (PLA)                                        *
 *   Plik:     pla7.java                                                 *
 *   Autor:    Marcin Pilipczuk, Michal Pilipczuk                        *
 *   Opis:     Rozwiazanie wzorcowe O(n*log n) za pomoca drzew           *
 *             przedzialowych wedlug pomyslu Marka Cygana.               *
 *                                                                       *
 *************************************************************************/
import java.io.*;
import java.util.*;

public class pla7 implements Runnable{
    public static void main(String[] args){
        new Thread(new pla7()).start();
    }

    final static int zz=262200;
    final static int MAX=270000;
    final static int MAX2=700000;
    final static int inf=2000*1000*1000;

    int[] tree, local_left, local_right;
    int p,q,h,n,k,dump,result,c_l,c_r;

    void reset(){
        for (int i = 0; i < 2*MAX; ++i)
            tree[i] = inf;
    }

    void insert(int gdzie,int co){
        p=gdzie+zz;
        while ((p>0)&&(tree[p]>co)){
            tree[p]=co; 
            p=(p>>1);
        }
    }

    void ff(int gdzie, ArrayList<Integer> aku){
        if ((gdzie>=zz)&&((tree[gdzie]=h)!=0)){
            aku.add(gdzie-zz);
        } else {
            if (tree[gdzie<<1]==h){ff(gdzie<<1,aku);}
            if (tree[(gdzie<<1)+1]==h){ff((gdzie<<1)+1,aku);}
        }
    }

    void find(int a,int b, ArrayList<Integer> aku){
        p=a+zz-1;
        q=b+zz+1;
        h=inf;
        while ((p>>1)!=(q>>1)){
            if (((p%2)==0)&&(tree[p+1]<h)){h=tree[p+1];}
            if (((q%2)==1)&&(tree[q-1]<h)){h=tree[q-1];}
            p=(p>>1); q=(q>>1);
        }
        p=a+zz-1;
        q=b+zz+1;
        c_l=0; c_r=0;
        while ((p>>1)!=(q>>1)){
            if ((p%2==0)&&(tree[p+1]==h)){local_left[c_l++]=(p+1);}
            if ((q%2==1)&&(tree[q-1]==h)){local_right[c_r++]=(q-1);}
            p=(p>>1); q=(q>>1);
        }    
        for (int i = 0; i < c_l; ++i)
            ff(local_left[i],aku);
        for (int i = c_r - 1; i >= 0; --i)
            ff(local_right[i],aku);
    }

    void zaglebiaj(int lo,int hi){
        if (lo<=hi){
            result++;
            ArrayList<Integer> cur = new ArrayList<Integer>();
            find(lo,hi,cur);
            int m=cur.size();
            zaglebiaj(lo,cur.get(0)-1);
            for (int i = 0; i < m-1; ++i)
                zaglebiaj(cur.get(i)+1,cur.get(i+1)-1);
            zaglebiaj(cur.get(m-1)+1,hi);
        }
    }

    public void run(){
        try{
            tree = new int[2*MAX];
            local_left = new int[30];
            local_right = new int[30];
            reset();
            BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
            String linia = br.readLine();
            StringTokenizer st = new StringTokenizer(linia);
            n = Integer.parseInt(st.nextToken());
            int wyn = 0;
            for (int i = 0; i < n; ++i){
                linia = br.readLine();
                st = new StringTokenizer(linia);
                st.nextToken();
                int w = Integer.parseInt(st.nextToken());
                insert(i, w);
            }
            zaglebiaj(0, n-1);
            System.out.println(result);
        }catch(Exception e){
            throw new RuntimeException(e);
        }
    }
};
