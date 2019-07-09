//ナンプレをDFSで解く(再帰関数使用)
#include<iostream>
using namespace std;

#define True -1
#define False 0
#define N 9

int place[9][9]={{8,1,0,0,0,0,2,0,0},
                 {0,0,0,0,0,0,0,0,0},
                 {0,7,2,0,9,0,0,0,0},
                 {0,0,0,8,0,0,0,0,0},
                 {0,9,0,0,0,0,1,0,0},
                 {7,0,0,0,0,3,0,0,6},
                 {4,0,0,0,0,0,0,0,3},
                 {6,0,0,3,0,0,7,8,5},
                 {0,0,0,0,0,5,0,9,1}};

int printplace(){
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			cout<<place[i][j]<<" ";
		}
		cout<<endl;
	}
	return 0;
}

int find_blank(int *x, int *y){
	for(int i=0; i<N;i++){
		for(int j=0;j<N;j++){
			if(place[i][j]==0){
				*x=i; *y=j;
				return True;
			}
		}
	}
	return False;
}

int is_put(int x,int y,int k){
	for(int i=0;i<N;i++) if(place[i][y]==k) return False;
	for(int j=0;j<N;j++) if(place[x][j]==k) return False;
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			if(place[(x/3)*3+i][(y/3)*3+j]==k) return False;
		}
	}
	return True;
}

int check(){
	int x,y;
	if(find_blank(&x,&y)){
		for(int k=1;k<=N;k++){
			if(is_put(x,y,k)){
				place[x][y]=k;
				check();
				place[x][y]=0;
			}
		}
	}else{
			printplace();
		}
		return 0;
}

int main(){
	check();
	return 0;
}
