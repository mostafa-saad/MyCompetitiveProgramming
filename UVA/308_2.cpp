// Src: https://github.com/hashemsellat/CompetitiveProgramming/blob/master/UVA/308.cpp

#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define ii pair<int,int>
map<int,int> M,M1;
int cnter=1,cnter1=1;
const int N = 1000;
const int AD= 0;
int a[N][N];
int di[]={0,0,1,-1};
int dj[]={1,-1,0,0};
int calc(int x){
    if(M[x])
        return M[x];
    M[x]=cnter;
    cnter+=2;
    return M[x];
}
int calc1(int y){
    if(M1[y])
        return M1[y];
    M1[y]=cnter1;
    cnter1+=2;
    return M1[y];
}
int vis[N][N],vis2[N][N];
bool isValid(int i,int j){
    //cout<<i<<" "<<j<<endl;
   // system("pause");
    if(i==N||j==N||i<0||j<0)
        return 0;
    if(vis2[i][j])
        return 1;
    vis2[i][j]=1;
    if(a[i][j])
        return 1;
    bool ret=1;
    for(int k=0;k<4;k++){
        int ni=i+di[k],
            nj=j+dj[k];
        if(!isValid(ni,nj))
            ret=0;
    }
    return ret;
}
void fill_(int i,int j){
    if(a[i][j])
    {
        vis[i][j]=1;
        return;
    }
    vis[i][j]=1;
    for(int k=0;k<4;k++){
        int ni=i+di[k],
            nj=j+dj[k];
        if(vis[ni][nj])
            continue;
        fill_(ni,nj);
    }
}
void fill_2(int i,int j){
    if(vis[i][j]!=1)
        return;
    vis[i][j]=2;
    for(int k=0;k<4;k++){
        int ni=i+di[k],
            nj=j+dj[k];
        if(vis[ni][nj]==2)
            continue;
        fill_2(ni,nj);
    }
}
main(){
    int n;
    ios_base::sync_with_stdio(false);
    while(cin>>n){
        vector<int> xx,yy;
        vector<ii> st,ed;
        if(n==0)    break;
        memset(vis2,0,sizeof(vis2));
        memset(vis,0,sizeof(vis));
        cnter1=cnter=1;
        M.clear();
        M1.clear();
        memset(a,0,sizeof(a));
        for(int i=0;i<n;i++){
           // cout<<i<<endl;
            int x1,y1,x2,y2;
            cin>>x1>>y1>>x2>>y2;
            st.push_back(ii(x1,y1));
            ed.push_back(ii(x2,y2));
            xx.push_back(x1);
            xx.push_back(x2);
            yy.push_back(y1);
            yy.push_back(y2);
        }
        //cout<<"HOO"<<endl;
        sort(xx.begin(),xx.end());
        sort(yy.begin(),yy.end());
        int sz=xx.size();
        for(int i=0;i<sz;i++){
          //  cout<<i<<endl;
            calc(xx[i]);
            calc1(yy[i]);
        }
        //cout<<"HERE"<<endl;
        for(int i=0;i<n;i++){
            //cout<<st[i].first<<" "<<st[i].second<<" "<<ed[i].first<<" "<<ed[i].second<<endl;
            st[i].first=calc(st[i].first);
            st[i].second=calc1(st[i].second);
            ed[i].first=calc(ed[i].first);
            ed[i].second=calc1(ed[i].second);
            if(st[i].first==ed[i].first){
                for(int j=min(st[i].second,ed[i].second);j<=max(st[i].second,ed[i].second);j++){
                    a[st[i].first][j]=1;
                }
            }
            else{
                for(int j=min(st[i].first,ed[i].first);j<=max(st[i].first,ed[i].first);j++){
                    a[j][st[i].second]=1;
                }
            }
        }

    /*    for(int i=0;i<20;i++)
        {
            for(int j=0;j<20;j++)
                cout<<a[i][j];
            cout<<endl;
        }*/

       for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                if(!vis2[i][j]&&!a[i][j]){
                    if(isValid(i,j)){
                        fill_(i,j);
                        //cout<<i<<" "<<j<<endl;
                    }
                }
            }
        }
        int cnt=0;

        /*for(int i=0;i<10;i++)
        {
            for(int j=0;j<10;j++)
                cout<<vis[i][j];
            cout<<endl;
        }*/
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                if(vis[i][j]==1){
                    cnt++;
                    fill_2(i,j);
                }
            }
        }
        cout<<cnt<<endl;
    }
}
