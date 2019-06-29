/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Kodowanie (KOD)                                           *
 *   Plik:     kods3.java                                                *
 *   Autor:    Piotr Niedzwiedz                                          *
 *   Opis:     Rozwiazanie wolne O(n^2). Przeszukiwania bez spamietywania*
 *                                                                       *
 *************************************************************************/

import java.util.*;
import java.io.*;


class Solution{
	final int nmx=1500000;
	int [][] S;
	int [] L,X,Y,W;
	int n,l,wh;
	boolean [] wazny,synch;
	void dfs1(int x,int y){
		if (S[0][y]==0){
			if(!wazny[x]){
				wazny[x]=true;
				W[wh++]=x;
			}
		}
		else{
		  	if (S[0][x]==0) x=0;
			dfs1(S[0][x],S[0][y]);
			dfs1(S[1][x],S[1][y]);
		}
	}
	void dfs2(int x,int y){
		if (S[0][y]==0){
			if(!wazny[x]){
				wazny[x]=true;
				W[wh++]=x;
			}
		}
		else{
			if (S[0][x]==0) x=0;
			dfs2(S[0][x],S[0][y]);
			dfs2(S[1][x],S[1][y]);
		}
	}
	void dfs3(int x,int y){
		if (S[0][y]==0){
			if(S[0][x]!=0) synch[y]=false;
		}
		else{
			if (S[0][x]==0) x=0;
			dfs3(S[0][x],S[0][y]);
			dfs3(S[1][x],S[1][y]);
		}
	}
	Solution()
	{
		Scanner in = new Scanner(new InputStreamReader(System.in));
		S=new int[2][nmx];
		L=new int[nmx];X=new int[nmx];Y=new int[nmx]; W=new int[nmx];
		wazny=new boolean[nmx];synch=new boolean[nmx];
		n=1; l=0;
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
						X[h++]=n++;
				break;
			}
		for(int i=0;i<n;i++) wazny[i]=false;	
		for(int i=0;i<n;i++) dfs1(0,i);
		for(int i=0;i<wh;++i) dfs2(W[i],0);
		for(int i=0;i<l;i++) synch[L[i]]=true;
		for(int i=0;i<wh;i++) dfs3(W[i],0);	

		int wynik=0;

		for(int i=0;i<l;i++) if(synch[L[i]]) wynik++;
		System.out.println(wynik);
		for(int i=0;i<l;i++) if(synch[L[i]]) System.out.println(i+1);
	}
};

public class kods3
{
	public static void main (String[] argv) throws IOException{
		new Solution();
	}
}

