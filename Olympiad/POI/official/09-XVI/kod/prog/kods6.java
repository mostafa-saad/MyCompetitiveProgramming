/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Kodowanie (KOD)                                           *
 *   Plik:     kods6.java                                                *
 *   Autor:    Piotr Niedzwiedz                                          *
 *   Opis:     Rozwiazanie wolne O(n*L). Nie korzysta z faktu, ze kody   *
 *             maja wspolne prefiksy.                                    *
 *                                                                       *
 *************************************************************************/

import java.util.*;
import java.io.*;


class Solution{
	final int nmx=1500000;
	int [][] S;
	int [] L,X,Y,W,P,Q;
	int n,l,wh,qh;
	boolean [] wazny,synch;
	boolean lok;

	int go(int v,int leaf,int lim){
		qh=0;
		int w=L[leaf];
		while(P[w] != -1 && lim>0){
			lim--;
			Q[qh++]=(S[0][P[w]]==w)?0:1;
			w=P[w];
		}
		if (lim!=0) lok=false;
		while(qh>0){
			qh--;
			if(S[0][v]==0) v=0;
			v=S[Q[qh]][v];
		}
		return v;
	}
	Solution()
	{
		Scanner in = new Scanner(new InputStreamReader(System.in));
		S=new int[2][nmx];
		L=new int[nmx];X=new int[nmx];Y=new int[nmx]; W=new int[nmx]; Q=new int[nmx]; P=new int[nmx];
		wazny=new boolean[nmx];synch=new boolean[nmx];
		n=1; l=0;
		P[0]=-1;
		int m=in.nextInt(),h=1,z;
		String s=in.next();
		for(int i=0;i<m;i++)
			switch (s.charAt(i))
			{
				case 'B':
					h--;
					break;
				case 'X':
					L[l++]=X[h-1];
					break;
				default:
					z=s.charAt(i)-'0';
					S[z][X[h-1]]=n;
					P[n]=X[h-1];
					X[h++]=n++;
					break;
			}
		for(int j=0;j<l;j++)
		{
			lok=true;
			int l=1;
			for(;;){
				int t=go(0,j,l);
				if(!lok) break;
				l++;
				if(!wazny[t]){
					wazny[t]=true;
					W[wh++]=t;		
				}
			}
		}
		for(int i=0;i<wh;++i){
			for(int j=0;j<l;j++){
				int t=go(W[i],j,nmx);
				if(!wazny[t]){
					wazny[t]=true;
					W[wh++]=t;		
				}
			}
		}
		for(int i=0;i<l;i++)	synch[L[i]]=true;
		for(int i=0;i<n;i++) if (wazny[i]) {
			for(int j=0;j<l;j++){
				int t=go(i,j,nmx);
				if (S[0][t]!=0) synch[L[j]]=false;
			}
		}
		int wynik=0;
		for(int i=0;i<l;i++) if(synch[L[i]]) wynik++;
		System.out.println(wynik);
		for(int i=0;i<l;i++) if(synch[L[i]]) System.out.println(i+1);
	}
};

public class kods6
{
	public static void main (String[] argv) throws IOException{
		new Solution();
	}
}

