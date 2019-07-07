import java.lang.*;

class mountains {

    private static final int MAX = 20;
	int[] h = new int[MAX];
	boolean[][] mark = new boolean[MAX][MAX];
    public int maximum_deevs(int y[]) {
		int n = y.length;
		for(int i=0;i<n;i++)h[i]=y[i];
		for(int i=0;i<n;i++)
			for(int j=i+1;j<n;j++){
				mark[i][j]=true;
				for(int k=i+1;k<j;k++)
					if(cross(i,j,k)>0)
						mark[i][j]=false;
			}
		int ans = 0;
		for(int i=0;i<(1<<n);i++){
			boolean mark1=true;
			for(int j=0;j<n;j++)
				for(int k=j+1;k<n;k++)
					if(mark[j][k] && (((i>>j)&1) > 0) && (((i>>k)&1) > 0))
						mark1=false;
						if(mark1){
							ans=Math.max(ans,Integer.bitCount(i));
						}
		}
		return ans;
	} 
	public long cross(int i,int j,int k){
		  return (j-i)*(h[k]-h[i])-(h[j]-h[i])*(k-i);
	}
}

