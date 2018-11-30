/* Tug of War
   Autor: Piotr Smulewicz
 */

import java.util.Vector;
import java.util.Scanner;

public class tug{

public static void main(String[] args){
final int SIZE =30001;
final int MAX_STRENGHT=20;
final int BACK_PACK_SIZE=SIZE*MAX_STRENGHT+1;
int[][] persons = new int[SIZE*2][2];
int[] str = new int[SIZE*2];
boolean[] assigned = new boolean[SIZE*2];
//Vector<Integer> vector = new Vector<Integer>();
//Vector[] spots = new Vector[100];
Vector<Vector<Integer>> spots = new Vector<Vector<Integer>>();
int[] item = new int[BACK_PACK_SIZE];
int[] opt = new int[SIZE*2];
boolean[] back_pack = new boolean[BACK_PACK_SIZE+1];
	int n,j,s,a,b,pe,mi,k,sum_all,sum,res;
	sum=0;
	mi=0;
	sum_all=0;
	
	Scanner input = new Scanner(System.in);
	res=BACK_PACK_SIZE;
	n=input.nextInt();
	k=input.nextInt();
	for(int i=0;i<n*2+2;i++)
		spots.add(new Vector<Integer>());
	for(int i=0;i<n*2;i++){
		a=input.nextInt();
		b=input.nextInt();
		s=input.nextInt();
		str[i]=s;
		persons[i][0]=a*2;
		persons[i][1]=b*2+1;
		spots.get(a*2).add(i);
		spots.get(b*2+1).add(i);
	}
	for(int s_pe=0;s_pe<2*n;s_pe++){
		pe=s_pe;
		while(!assigned[pe]){
			for(j=0;j<2;j++){
				mi=persons[pe][j];
				if(opt[mi]+1==spots.get(mi).size()){
					assigned[pe]=true;
					sum+=(1-2*(mi%2))*str[pe];
					mi=persons[pe][1-j];
					opt[mi]++;
					break;

				}
			}
			if(spots.get(mi).size()==opt[mi]+1){
				int poz=0;
				while(assigned[spots.get(mi).get(poz)] && poz<spots.get(mi).size())
					poz++;
				if(poz<spots.get(mi).size())
					pe=spots.get(mi).get(poz);
				else
					break;
			}else
				break;
		}
	}
	item[Math.abs(sum)]++;
	sum_all+=Math.abs(sum);
	for(int s_pe=0;s_pe<2*n;s_pe++){
		sum=0;
		pe=s_pe;
		int st=0;
		int mi2=persons[pe][1];
		if(assigned[pe])continue;
		while(!assigned[pe]){
			sum+=(1-2*st)*str[pe];
			assigned[pe]=true;
			mi=persons[pe][st];
			int poz=0;
			while(poz<spots.get(mi).size() && assigned[spots.get(mi).get(poz)]) poz++;
			if(poz<spots.get(mi).size())
				pe=spots.get(mi).get(poz);
			st=1-st;
		}
		if(mi!=mi2){
			System.out.println("NO");
			return;
		}
		if(sum!=0)
			item[Math.abs(sum)]++;
		sum_all+=Math.abs(sum);
	}
	back_pack[0]=true;
	for(int i=0;i<BACK_PACK_SIZE;i++){
		if(item[i]==0)continue;
		for(j=BACK_PACK_SIZE/2;j>=0;--j){
			if(back_pack[j]){
				for(int l=1;l<=item[i] && back_pack[j+l*i]==false ;l++)
					back_pack[j+l*i]=true;
			}
		}
	}
	for(j=BACK_PACK_SIZE;j>=0;--j){
		if(back_pack[j])
			res=Math.min(res,Math.abs(sum_all-2*j));
	}
	if(res<=k)
		System.out.println("YES");
	else
		System.out.println("NO");	
}
}
