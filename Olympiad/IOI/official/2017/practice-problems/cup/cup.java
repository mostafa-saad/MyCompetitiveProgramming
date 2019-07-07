import java.io.*;
import java.util.*;


class cup{
	final int maxn = 500000000;
	int x,tmp,tmp1,y;

	boolean same(int k) {
		long help=((1L)<<33)-1-((1L)<<k);
		return ((tmp&help)==(tmp1&help));
	}

	long f(long k) {
		for(int i=33;i>-1;i--)
			if(((k>>i)&1L) != 0L)
				return ((1L)<<i);
		return 0L;
	}

	public int[] find_cup() {
		int[] result = new int[2];

		x=y=tmp1=0;
		tmp=grader.ask_shahrasb(-2*maxn,-maxn);
		for(int i=0;i<31;i++)
		{
			long k=((1L)<<i);
			tmp1=grader.ask_shahrasb((int)(-2*maxn+k),Integer.valueOf(-maxn));
			if(same(i))
				y+=k^(tmp&k);
			else
				y+=(tmp&k);
		}
		x=y^tmp;
		if(-2*maxn+x>maxn)
			x-=f(x);
		result[0] = Integer.valueOf(-2*maxn+x);
		result[1] = Integer.valueOf(-maxn+(tmp^x));
		return result;
	}
}
