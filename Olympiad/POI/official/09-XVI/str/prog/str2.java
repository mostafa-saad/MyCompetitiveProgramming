/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Straz pozarna (STR)                                       *
 *   Plik:     str2.java                                                 *
 *   Autor:    Tomasz Kulczynski                                         *
 *   Opis:     Rozwiazanie wzorcowe O((p+z)*log(p+z))                    *
 *                                                                       *
 *************************************************************************/

import java.io.*;
import java.util.*;


public class str2 implements Runnable {

int min(int a,int b)
{
    return a<b?a:b;
}

int max(int a,int b)
{
    return a<b?b:a;
}

int abs(int x)
{
	return x<0?-x:x;
}

public class wekt implements Comparable
{
    int a[];
    public wekt(int b,int c,int d,int e,int f)
    {
        a=new int[5];
        a[0]=b;
        a[1]=c;
        a[2]=d;
        a[3]=e;
        a[4]=f;
    }
    public wekt(long b,int c,int d,int e,int f)
    {
        a=new int[5];
        a[0]=(int)b;
        a[1]=c;
        a[2]=d;
        a[3]=e;
        a[4]=f;
    }
    public wekt(long b,int c,int d,long e,long f)
    {
        a=new int[5];
        a[0]=(int)b;
        a[1]=c;
        a[2]=d;
        a[3]=(int)e;
        a[4]=(int)f;
    
    }
    public wekt(long b,int c,int d,int e,long f)
    {
        a=new int[5];
        a[0]=(int)b;
        a[1]=c;
        a[2]=d;
        a[3]=e;
        a[4]=(int)f;
    
    }
	public int compareTo(Object a) {
		wekt x=(wekt)a;
		int i;
		for(i=0;i<4;i++) 
			if(this.a[i]!=x.a[i])
				return this.a[i]<x.a[i]?-1:1;
		return 0;
	}
};

final static int Z = (int)1e5;
final static int P = (int)1e5;
final static int inf = (int)1e9;

int n,m,z,p,x[],y[],w[];
Vector< wekt > x1,x2,x3,x4;

public str2()
{
    x=new int[Z];
    y=new int[Z];
    w=new int[3*P];
    e=new int[2*M];
    x1=new Vector<wekt>();
	x2=new Vector<wekt>();
	x3=new Vector<wekt>();
	x4=new Vector<wekt>();
}

int sign(int x)
{
    if(x==0) return 0;
    return x>0?1:-1;
}

Vector<Integer> u;
Integer uu[];

int szukaj(int a)
{
    int l=0,p=u.size()-1,s;
    while(l<p)
    {
        s=(l+p)/2;
        if(uu[s]<a) l=s+1;
        else p=s;
    }
    return l;
}

final static int M = 1<<19;
int e[];

void insert(int a)
{
    a+=M;
    while(a!=0)
    {
        e[a]++;
        a/=2;
    }
}

int pyt(int a)
{
    int ret=0;
    a+=M;
    while(a>1)
    {
        if(a%2!=0)
            ret+=e[a-1];
        a/=2;
    }
    return ret;
}

int pytaj(int a,int b)
{
    return pyt(b+1)-pyt(a);
}

wekt xx[];

void zamiec(Vector< wekt > x)
{
	u=new Vector<Integer>();
    int i;
    for(i=0;i<(int)x.size();i++)
        if(x.elementAt(i).a[1]>=0 && x.elementAt(i).a[3]>x.elementAt(i).a[4])
        {
            x.set(i,x.elementAt(x.size()-1));
            x.removeElementAt(x.size()-1);
        } 
    xx=new wekt[x.size()];
    for(i=0;i<xx.length;i++)
    	xx[i]=x.elementAt(i);
    Arrays.sort(xx);
    for(i=0;i<xx.length;i++) 
    	x.set(i,xx[i]);
    for(i=0;i<2*M;i++) 
        e[i]=0;
    for(i=0;i<(int)x.size();i++)
        if(x.elementAt(i).a[1]<0)
            u.add(x.elementAt(i).a[2]);
        else
        {
            u.add(x.elementAt(i).a[3]);
            u.add(x.elementAt(i).a[4]);
        }
    uu=new Integer[u.size()];
    for(i=0;i<uu.length;i++)
    	uu[i]=u.elementAt(i);
    Arrays.sort(uu);
    for(i=0;i<(int)x.size();i++)
        if(x.elementAt(i).a[1]<0)
            insert(szukaj(x.elementAt(i).a[2]));
        else
            w[x.elementAt(i).a[1]]+= pytaj( szukaj(x.elementAt(i).a[3]), szukaj(x.elementAt(i).a[4]) ) * x.elementAt(i).a[2];
}

public static void main(String args[])
{
    new Thread(new str2()).start();
}

public void run()
{
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    try
    {
    String t[]=br.readLine().split(" ");
      n = Integer.parseInt(t[0]);
      m = Integer.parseInt(t[1]);
      z = Integer.parseInt(t[2]);
      p = Integer.parseInt(t[3]);
    int i,j,k;
    for(i=0;i<z;i++)
    {
        t=br.readLine().split(" ");
        x[i] = Integer.parseInt(t[0]);
        y[i] = Integer.parseInt(t[1]);
    }
    for(j=0;j<p;j++)
    {
        int a,b,c,d,komu=0;
        t=br.readLine().split(" ");
        a = Integer.parseInt(t[0]);
        b = Integer.parseInt(t[1]);
        c = Integer.parseInt(t[2]);
        d = Integer.parseInt(t[3]);
        if(a>c) komu=1;
        if(a==c)
        {
            if(b>d) komu=1;
            x2.add( new wekt( (b+d-1)/2,      3*j+komu,  1, 0,            inf ) );
            x2.add( new wekt( (b+d)/2,    3*j+2,     1,  0,           inf ) );
        }
        else if(b==d)
        {
            x1.add( new wekt( (a+c-1)/2,      3*j+komu,  1,  0,           inf ) );
            x1.add( new wekt( (a+c)/2,    3*j+2,     1,  0,           inf ) );

        }
        else if(abs(a-c)==abs(b-d))
        {
            if(a+b==c+d)
            {
                x3.add( new wekt( inf+c-b-1,  3*j+komu,  1, min(b,d)+1,   max(b,d)-1 ) );
                x3.add( new wekt( inf+c-b,    3*j+2,     1, min(b,d),     max(b,d)-1 ) );
                x1.add( new wekt( max(a,c)-1, 3*j+komu,  1, max(b,d),     inf ) );
                x1.add( new wekt( max(a,c),   3*j+2,     1, max(b,d),     inf ) );

                x1.add( new wekt( min(a,c),   3*j+2,     1, 0,            min(b,d)-1 ) );

                w[3*j+2]+=z;
                x2.add( new wekt( max(b,d)-1,     3*j+2,     1, 0    ,   max(a,c) ) );
                x2.add( new wekt( inf,            3*j+2,    -1, 0    ,   max(a,c) ) );
                x2.add( new wekt( max(b,d)-1,     3*j+2,    -1, 0    ,   inf ) );
            }
            else
            {
                x4.add( new wekt( b+c-1,      3*j+komu,  1, min(b,d)+1,   max(b,d)-1 ) );
                x4.add( new wekt( b+c,        3*j+2,     1, min(b,d)+1,   max(b,d) ) );
                x1.add( new wekt( max(a,c)-1, 3*j+komu,  1, 0,            min(b,d) ) );
                x1.add( new wekt( max(a,c),   3*j+2,     1, 0,            min(b,d) ) );

                x1.add( new wekt( min(a,c),   3*j+2,     1, max(b,d)+1,   inf ) );

                x2.add( new wekt( min(b,d),   3*j+2,     1, max(a,c)+1,   inf ) );
            }
        }
        else if(abs(a-c)>abs(b-d))
        {
            if(sign(a-c)==sign(b-d))
            {
                long s=a+b;
                s+=c+d;
                x4.add( new wekt( (s-1)/2,            3*j+komu,  1, min(b,d),     max(b,d) ) );
                x4.add( new wekt( s/2,                3*j+2,     1, min(b,d),     max(b,d) ) );
                x1.add( new wekt( (s-1)/2-max(b,d),   3*j+komu,  1, max(b,d)+1,   inf ) );
                x1.add( new wekt( s/2-max(b,d),       3*j+2,     1, max(b,d)+1,   inf ) );
                x1.add( new wekt( (s-1)/2-min(b,d),   3*j+komu,  1, 0,            min(b,d)-1 ) );
                x1.add( new wekt( s/2-min(b,d),       3*j+2,     1, 0,            min(b,d)-1 ) );
            }
            else
            {
                long s=inf+a-b;
                s+=inf+c-d;
                x3.add( new wekt( (s-1)/2,                3*j+komu,  1, min(b,d),     max(b,d) ) );
                x3.add( new wekt( s/2,                    3*j+2,     1, min(b,d),     max(b,d) ) );
                x1.add( new wekt( (s-1)/2-inf+max(b,d),   3*j+komu,  1, max(b,d)+1,   inf ) );
                x1.add( new wekt( s/2-inf+max(b,d),       3*j+2,     1, max(b,d)+1,   inf ) );
                x1.add( new wekt( (s-1)/2-inf+min(b,d),   3*j+komu,  1, 0,            min(b,d)-1 ) );
                x1.add( new wekt( s/2-inf+min(b,d),       3*j+2,     1, 0,            min(b,d)-1 ) );
            }
        }
        else
        {
            if(sign(a-c)==sign(b-d))
            {
                long s=a+b;
                s+=c+d;
                x4.add( new wekt( (s-1)/2,    3*j+komu,  1, (s-1)/2-max(a,c)+1,   (s-1)/2-min(a,c) ) );
                x4.add( new wekt( s/2,        3*j+2,     1, s/2-max(a,c)+1,   s/2-min(a,c)     ) );
                x1.add( new wekt( inf,        3*j+komu,  1, 0,                (s-1)/2-max(a,c) ) );
                x1.add( new wekt( inf,        3*j+2,     1, 0,                s/2-max(a,c)     ) );
            }
            else
            {
                long s=inf+a-b;
                s+=inf+c-d;
                x3.add( new wekt( (s-1)/2,    3*j+komu,  1, min(a,c)+inf-(s-1)/2,     max(a,c)+inf-(s-1)/2-1 ) );
                x3.add( new wekt( s/2,        3*j+2,     1, min(a,c)+inf-s/2,         max(a,c)+inf-s/2-1 ) );
                x1.add( new wekt( inf,        3*j+komu,  1, max(a,c)+inf-(s-1)/2,     inf      ) );
                x1.add( new wekt( inf,        3*j+2,     1, max(a,c)+inf-s/2,         inf      ) );
            }
        }
        w[3*j+1-komu]=-1;
    }
    for(i=0;i<z;i++)
        x1.add( new wekt( x[i], -1, y[i] ,0,0) );
    zamiec(x1);
    for(i=0;i<z;i++)
        x2.add( new wekt( y[i], -1, x[i] ,0,0) );
    zamiec(x2);
    for(i=0;i<z;i++)
        x3.add( new wekt( inf+x[i]-y[i], -1, y[i] ,0,0) );
    zamiec(x3);
    for(i=0;i<z;i++)
        x4.add( new wekt( x[i]+y[i], -1, y[i] ,0,0) );
    zamiec(x4);
    for(j=0;j<p;j++)
    {
        for(k=0;k<2;k++)
            if(w[3*j+k]<0)
            {
                w[3*j+k]=z-w[3*j+2];
                w[3*j+2]-=w[3*j+1-k];
            }
        System.out.println(""+w[3*j]+" "+w[3*j+1]+" "+w[3*j+2]);
    }
    }
    catch(IOException e){};
}

};
