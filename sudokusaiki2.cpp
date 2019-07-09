//ナンプレをDFSで解く(cpuの命令をC++で再現したもの．main関数でfor文不使用)
#include<iostream>

using namespace std;

int mem[256]; //memory 0-255
int res[16]; //register 0-255

void init_mem(){
	for(int i=0;i<256;i++) mem[i]=0;
	for(int i=0;i<16;i++) res[i]+0;
    //init mem
    mem[0]=8;
    mem[1]=1;
    mem[6]=2;
    mem[19]=7;
    mem[20]=2;
    mem[22]=9;
    mem[30]=8;
    mem[37]=9;
    mem[42]=1;
    mem[45]=7;
    mem[50]=3;
    mem[53]=6;
    mem[54]=4;
    mem[62]=3;
    mem[63]=6;
    mem[66]=3;
    mem[69]=7;
    mem[70]=8;
    mem[71]=5;
    mem[77]=5;
    mem[79]=9;
    mem[80]=1;

    int c=162;
    for(int i=0;i<81;i++){
        int row=i/9;
        int column=i%9;
        mem[i+c]=(row/3)*3+column/3;
    }
}

int main(){
    init_mem();

    //make searchlist
    //res[0]=0; searching cell no.
    res[1]=81; //pointer
    res[15]=81;
makesearch:
    if(mem[res[0]]==0){
        mem[res[1]]=res[0];
        res[1]++;
    }
    if(res[0]==80) {
	goto main;
	}
    res[0]++;
    goto makesearch;

isput: 
    //calc row(res[3]),column(res[4])
    res[12]=res[1];
    res[3]=0;
    res[13]=0; //temp
    divide:
        next:
        if(res[12]==res[13]) goto end;
        res[13]++;
        if(res[13]==9){ //goto
            res[13]=0;
            res[3]++;
            res[12]-=9;
        }
        goto next;
    end:
    res[4]=res[13];
    //row check
    res[12]=res[1]-res[4];
    
    res[11]=0;
    rowcheck:
        res[10]=res[12]+res[11];
        res[10]=mem[res[10]];
        if(res[10]==res[2]){
		//cout<<"false due to same number in the row"<<endl;
		goto putfalse;
		}
        res[11]++; 
        if(res[11]==9) goto end3;
        goto rowcheck;
    end3:

    //columncheck
    res[13]=res[4];
    res[12]=0; //counter
    columncheck:
        res[11]=mem[res[13]];
        if(res[11]==res[2]){
		goto putfalse;
		}
        res[13]+=9; res[12]++;
        if(res[12]==9) goto end4;
        goto columncheck;
    end4:

    //boxcheck
    res[13]=162;
    res[5]=mem[res[13]+res[1]]; 
    res[12]=0;
    loop2:
        res[11]=mem[res[12]+res[13]];
        if(res[11]==res[5]){
            res[10]=mem[res[12]];
            if(res[10]==res[2]) {
				goto putfalse;
			}
        }
        res[12]++;
        if(res[12]==81) goto puttrue;
        goto loop2;

main:
    if(mem[res[15]]==0) goto finish;
    res[1]=mem[res[15]]; //search cell
    res[2]=mem[res[1]]+1;
    loop: 
    if(res[2]==10){
        res[14]=0;
        mem[res[1]]=0;
        res[15]--;
        goto main;
    }
    goto isput;
    putfalse:
    res[2]++; goto loop;

    puttrue:
        mem[res[1]]=res[2];
        res[15]++;
        goto main;
        
finish:
    //check
    for(int i=0;i<81;i++){
        cout<<mem[i];
		if(i%9==8) cout<<endl;
		else cout<<",";
    }
}
