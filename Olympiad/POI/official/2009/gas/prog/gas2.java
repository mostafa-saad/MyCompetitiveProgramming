/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Gasnice (GAS)                                             *
 *   Plik:     gas2.java                                                 *
 *   Autor:    Piotr Niedzwiedz                                          *
 *   Opis:     Rozwiazanie wzorcowe O(n*k)                               *
 *                                                                       *
 *                                                                       *
 *************************************************************************/

import java.util.*;
import java.io.*;


class Solution{
	final int nmx=100000,kmx=21;
	long [][] up,need;
	int n,k;
	long s,result;
	List<Integer> []E;
	long min(long a,long b){
		if(a<b) return a;
		return b;
	}
	void dfs(int v,int p){
		for(int i=0;i<=k;i++) {up[v][i]=0; need[v][i]=0;}
		need[v][0]=1;
		for (Integer to : E[v])
			if (!to.equals(p)){
				dfs(to,v);
				for(int i=0;i<k;i++){
					need[v][i+1]=need[v][i+1]+need[to][i];
					up[v][i]=up[v][i]+up[to][i+1];
				}
			}
		long x=(need[v][k]+s-1)/s;
		result+=x;
		up[v][k]+=x*s;
		for(int i=0;i<=k;i++){
			x=min(need[v][i],up[v][i]);
			need[v][i]-=x;
			up[v][i]-=x;
		}
		for(int i=0;i<k;i++){
			x=min(need[v][i],up[v][i+1]);
			need[v][i]-=x;
			up[v][i+1]-=x;
		}
	}
	Solution(){
		result=0;
		Scanner in = new Scanner(new InputStreamReader(System.in));
		n=in.nextInt();
		s=in.nextLong();
		k=in.nextInt();
		E=new ArrayList[n];
		up=new long[n][k+1];
		need=new long[n][k+1];
		for(int i=0;i<n;i++) E[i]=new ArrayList<Integer>();
		int a,b;
		for(int i=0;i<n-1;i++){
			a=in.nextInt();b=in.nextInt();
			E[a-1].add(b-1);
			E[b-1].add(a-1);
		}
		dfs(0,-1);
		long h=0;
		for(int i=k;i>=0;i--){
			h+=up[0][i];
			if(h<need[0][i]){
				long x=(need[0][i]-h+s-1)/s;
				result+=x;
				h+=x*s;
			}
			h-=need[0][i];
		}		
		System.out.println(result);
	}
};

public class gas2
{
	public static void main (String[] argv) throws IOException{
		new Solution();
	}
}

