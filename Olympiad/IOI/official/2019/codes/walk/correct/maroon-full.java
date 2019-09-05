import java.util.*;

class walk {
	int lower_bound(int[]a,int n,int v){
		int lw=-1,up=n;
		while(up-lw>1){
			int mid=(up+lw)/2;
			if(a[mid]<v)lw=mid;
			else up=mid;
		}
		return up;
	}
	int lower_bound(long[]a,int n,long v){
		int lw=-1,up=n;
		while(up-lw>1){
			int mid=(up+lw)/2;
			if(a[mid]<v)lw=mid;
			else up=mid;
		}
		return up;
	}
	int unique(int[] x,int xlen){
		int n=0,last=-1;
		for(int i=0;i<xlen;i++){
			if(last<x[i])
				x[n++]=x[i];
			last=x[i];
		}
		return n;
	}
	int unique(long[] x,int xlen){
		int n=0;
		long last=-1;
		for(int i=0;i<xlen;i++){
			if(last<x[i])
				x[n++]=x[i];
			last=x[i];
		}
		return n;
	}
	static final int V=2000000010;
	long pack(long a,long b){
		return a*V+b;
	}
	class BIT{
		int[] buf;
		public BIT(int n){
			buf=new int[n];
		}
		void Add(int i,int v){
			for(;i<buf.length;i+=((i+1)&(-i-1)))
				buf[i]+=v;
		}
		void Insert(int i){
			Add(i,1);
		}
		void Erase(int i){
			Add(i,-1);
		}
		int GetBelow(int i){
			int cnt=0;
			for(i--;i>=0;i-=((i+1)&(-i-1)))
				cnt+=buf[i];
			if(cnt==0)return -1;
			int res=0;
			for(int w=17;w>=0;w--){
				int nx=res+(1<<w);
				if(nx<=buf.length&&buf[nx-1]<cnt){
					res=nx;
					cnt-=buf[nx-1];
				}
			}
			return res;
		}
	}
	static class DistIdx implements Comparable<DistIdx>{
		long d;
		int i;
		public DistIdx(long dd,int ii){
			d=dd;
			i=ii;
		}
		@Override
		public int compareTo(DistIdx r){
			return Long.compare(d,r.d);
		}
	}
	public long min_distance(int[] x, int[] h, int[] l, int[] r, int[] y, int s, int g) {
		if(s>g){
			int tmp=s;
			s=g;
			g=tmp;
		}
		int n=x.length;
		int m=l.length;
		int mmax=m*3;
		int smax=m*12+2;
		for(int k=0;k<2;k++)
		{
			int w=s;
			if(k==1)w=g;
			
			int[] pa=new int[n];
			int[] pb=new int[n];
			int ps=1;
			pa[0]=h[w];
			pb[0]=w;
			
			int[] qa=new int[n];
			int[] qb=new int[n];
			int qs=1;
			qa[0]=h[w];
			qb[0]=w;
			
			for (int i=w-1;i>=0;i--)
				if (h[i]>pa[ps-1]){
					pa[ps]=h[i];
					pb[ps++]=i;
				}
			for (int i = w + 1; i < n; i++)
				if(h[i]>qa[qs-1]){
					qa[qs]=h[i];
					qb[qs++]=i;
				}
			
			int nxm=0;
			int[] ll=new int[mmax];
			int[] rr=new int[mmax];
			int[] yy=new int[mmax];
			
			for(int i=0;i<m;i++)
			{
				if (l[i] < w && w < r[i])
				{
					int a, b;
					{
						int j=lower_bound(pa,ps,y[i]);
						a = pb[j];
					}
					{
						int j=lower_bound(qa,qs,y[i]);
						b = qb[j];
					}
					if (l[i] < a)
					{
						ll[nxm]=l[i];
						rr[nxm]=a;
						yy[nxm]=y[i];
						nxm++;
					}
					if (a < b)
					{
						ll[nxm]=a;
						rr[nxm]=b;
						yy[nxm]=y[i];
						nxm++;
					}
					if (b < r[i])
					{
						ll[nxm]=b;
						rr[nxm]=r[i];
						yy[nxm]=y[i];
						nxm++;
					}
				}
				else
				{
					ll[nxm]=l[i];
					rr[nxm]=r[i];
					yy[nxm]=y[i];
					nxm++;
				}
			}
			l = ll;
			r = rr;
			y = yy;
			m=nxm;
		}
		
		long[] posYX=new long[smax];
		int ps=2;
		posYX[0]=x[s];
		posYX[1]=x[g];
		{
			long[] xty=new long[m*2];
			for(int i=0;i<m;i++){
				xty[i*2]=((long)x[l[i]]*2+0)*V+y[i]+V/2;
				xty[i*2+1]=((long)x[r[i]]*2+1)*V-y[i]+V/2;
			}

			Arrays.sort(xty);
			int[] ys=y.clone();
			Arrays.sort(ys,0,m);
			int ycnt=unique(ys,m);
			BIT bit=new BIT(ycnt);
			
			for(int qq=0;qq<xty.length;qq++)
			{
				int j=(int)(xty[qq]/V/2);
				int t=(int)(xty[qq]/V%2);
				int i=(int)(xty[qq]%V-V/2);
				if(t==1)i=-i;
				posYX[ps++]=pack(i,j);
				int w=lower_bound(ys,ycnt,i);
				int itr=bit.GetBelow(w);
				if (itr>=0)
					posYX[ps++]=pack(ys[itr],j);
				if (t == 0)
					bit.Insert(w);
				else
					bit.Erase(w);
			}

			Arrays.sort(posYX,0,ps);
			ps=unique(posYX,ps);
		}
		
		int vs = ps;
		int[] deg=new int[vs*2];
		int[] ea=new int[vs*2];
		int[] eb=new int[vs*2];
		int[] ec=new int[vs*2];
		int es=0;
		
		for(int i=0;i<m;i++)
		{
			int k = lower_bound(posYX,ps,pack(y[i],x[l[i]]));
			while (k + 1 < ps && posYX[k + 1] <= pack(y[i], x[r[i]]))
			{
				deg[k]++;
				deg[k+1]++;
				ea[es]=k;
				eb[es]=k+1;
				ec[es]=(int)(posYX[k+1]%V-posYX[k]%V);
				k++;
				es++;
			}
		}

		long[] posXY=new long[ps];
		for(int i=0;i<ps;i++)
			posXY[i]=pack(posYX[i]%V,posYX[i]/V);
		Arrays.sort(posXY);
		for(int i=0;i<vs-1;i++)
		{
			if (posXY[i]/V == posXY[i+1]/V)
			{
				ea[es]=lower_bound(posYX,ps,pack(posXY[i]%V,posXY[i]/V));
				eb[es]=lower_bound(posYX,ps,pack(posXY[i+1]%V,posXY[i+1]/V));
				deg[ea[es]]++;
				deg[eb[es]]++;
				ec[es]=(int)(posXY[i+1]%V-posXY[i]%V);
				es++;
			}
		}
		
		int[] eto=new int[es*2];
		int[] ecost=new int[es*2];
		int[] head=deg.clone();
		for(int i=0;i<vs-1;i++)
			head[i+1]+=head[i];
		
		for(int i=0;i<es;i++){
			head[ea[i]]--;
			eto[head[ea[i]]]=eb[i];
			ecost[head[ea[i]]]=ec[i];
			head[eb[i]]--;
			eto[head[eb[i]]]=ea[i];
			ecost[head[eb[i]]]=ec[i];
		}
		
		final long infLL=1000000000000000000L;
		long[] dist=new long[vs];
		for(int i=0;i<vs;i++)dist[i]=infLL;
		
		PriorityQueue<DistIdx> pq=new PriorityQueue<>();
		dist[0]=0;
		pq.add(new DistIdx(0,0));
		while (!pq.isEmpty())
		{
			DistIdx di=pq.poll();
			long d=di.d;
			int v=di.i;
			if (dist[v] != d)
				continue;
			if(v==1)return d;
			for(int i=head[v];i<head[v]+deg[v];i++){
				int to=eto[i];
				long cs=d+ecost[i];
				if(dist[to]>cs){
					dist[to]=cs;
					pq.add(new DistIdx(cs,to));
				}
			}
		}

		return -1;
	}
}
