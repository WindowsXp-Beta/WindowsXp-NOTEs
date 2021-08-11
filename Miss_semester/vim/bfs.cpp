//  main.cpp
//  BFS解迷宫问题
//
//  Created by 了不起的杰弗里斯 on 2020/1/29.
//  Copyright © 2020 了不起的杰弗里斯. All rights reserved.
//

#include "header.h"
    struct node{
        int x,y;
        node(int a=0,int b=0):x(a),y(b){}
        friend ostream &operator<<(ostream &,node &);
    };
    ostream &operator<<(ostream &out,node &a){
        out<<"("<<a.x<<","<<a.y<<")";
        return out;
    }
    int main(int argc, const char * argv[]) {
        int * *maze;
        node * *fa;
        int row,col,i,j;
        node cur,last;//cur表示正在遍历的点，last表示它是从哪一个点来的
        cout<<"请输入迷宫的行数与列数\n";
        cin>>row>>col;
        maze=new int *[row];
        fa=new node *[row];
        cout<<"请输入迷宫，0代表可通过，100代表不可通过\n";
        for(i=0;i<row;++i){
            maze[i]=new int [col];
            fa[i]=new node [col];
            for(j=0;j<col;++j)
                cin>>maze[i][j];
        }
        for(i=0;i<row;++i){
            for(j=0;j<col;++j)cout<<maze[i][j]<<" ";cout<<endl;
        }cout<<endl;

        linkqueue<node> qu;
        cur.x=cur.y=0;
        qu.enQueue(cur);
        while(!qu.isEmpty()){
            last=qu.deQueue();

            if(last.x!=0&&maze[last.x-1][last.y]==0)
            {cur.x=last.x-1;   cur.y=last.y;
                if(cur.x!=0&&cur.y!=0){
                    maze[cur.x][cur.y]=maze[last.x][last.y]+1;
                    fa[cur.x][cur.y]=last;
                    qu.enQueue(cur);}
            }

            if(last.y!=col-1&&maze[last.x][last.y+1]==0)
            {cur.x=last.x;cur.y=last.y+1;
                if(cur.x==row-1&&cur.y==col-1)break;
                maze[cur.x][cur.y]=maze[last.x][last.y]+1;
                fa[cur.x][cur.y]=last;
                qu.enQueue(cur);
            }

            if(last.x!=row-1&&maze[last.x+1][last.y]==0)
            {cur.x=last.x+1;cur.y=last.y;
                if(cur.x==row-1&&cur.y==col-1)break;//到达出口
                maze[cur.x][cur.y]=maze[last.x][last.y]+1;
                fa[cur.x][cur.y]=last;
                qu.enQueue(cur);
            }

            if(last.y!=0&&maze[last.x][last.y-1]==0)
            {cur.x=last.x;cur.y=last.y-1;
                if(cur.x!=0&&cur.y!=0){
                    maze[cur.x][cur.y]=maze[last.x][last.y]+1;
                    fa[cur.x][cur.y]=last;
                    qu.enQueue(cur);}
            }/*for(i=0;i<row;++i){
            for(j=0;j<col;++j)cout<<maze[i][j]<<" ";cout<<endl;
        }cout<<endl;*/
        }
        maze[cur.x][cur.y]=maze[last.x][last.y]+1;
        fa[cur.x][cur.y]=last;
        /*for(i=0;i<row;++i){
            for(j=0;j<col;++j)cout<<maze[i][j]<<" ";cout<<endl;
        }cout<<endl;*/

        vector<node> v;
        while(cur.x!=0&&cur.y!=0){
            v.push_back(fa[cur.x][cur.y]);
            cur=fa[cur.x][cur.y];
        }
        v.push_back(cur);
        while (!v.empty()){
            cout<<v.back()<<"->";
            v.pop_back();
        }cout<<"end";

        /*int length=maze[cur.x][cur.y]+1;
        node *path=new node[length];
        path[length-1]=cur;
        last=cur;
        for(i=length-2;i>=0;--i){
            if(last.x!=0&&maze[last.x-1][last.y]<maze[last.x][last.y]){
                path[i].x=last.x-1;path[i].y=last.y;
                last=path[i];continue;
            }
            if(last.y!=col-1&&maze[last.x][last.y+1]<maze[last.x][last.y]){
                path[i].x=last.x;path[i].y=last.y+1;
                last=path[i];continue;
            }
            if(last.x!=row-1&&maze[last.x+1][last.y]<maze[last.x][last.y]){
                path[i].x=last.x+1;path[i].y=last.y;
                last=path[i];continue;
            }
            if(last.y!=0&&maze[last.x][last.y-1]<maze[last.x][last.y]){
                path[i].x=last.x;path[i].y=last.y-1;
                last=path[i];continue;
            }
        }
        for(i=0;i<length;++i){
            cout<<path[i]<<'\t';
        }
        delete []path;*/
        return 0;
    }

