#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <map>
#include <algorithm>
using namespace::std;
string outcome(int,int,bool);
bool isOperator(char op){
    return (op=='+'||op=='*'||op=='-');
}

vector<int>num;
vector<char>op;
int anwsMax[100][100];
int anwsMin[100][100];
int kMax[100][100], kMin[100][100];
int fromMax[100][100], fromMin[100][100];

int main(int argc, const char * argv[]) {
    string input,temp="";
    cin>>input; //12+3*5 30 17 // -5*3--2
    int i=0;
    int n=0;
    
    if(input[0]=='-'){
        i=1;
        temp="";
        while (!isOperator(input[i])) {
            temp +=input[i];
            i++;
        }
        
        n = atoi(temp.c_str());
        num.push_back(-n);
        
    }
    bool haveNeg=false;
    temp = "";
    for(;i<input.length();i++){
        
        
        if(i!=0 && input[i]=='-'&&isOperator(input[i-1])){
                haveNeg = true;
        }
        
        
        else if(isOperator(input[i])){
            op.push_back(input[i]);
            
            if(!haveNeg&&temp!="")
                num.push_back(atoi(temp.c_str()));
                
            else if(haveNeg){
                n = atoi(temp.c_str());
                num.push_back(-n);
                haveNeg=false;
            }
            temp="";
        }
        else{
            temp+=input[i];
        }
        
    }
    if(haveNeg){
        num.push_back(-atoi(temp.c_str()));
    }
    else num.push_back(atoi(temp.c_str()));
    
    int len = int(num.size());
    int a,b,c,d; //maxmax,maxmin,minmax,minmin

    
    
    for(int i=0;i<len;i++){
        for(int j=0;j<len;j++){
            anwsMax[i][j]=INT_MIN;
            anwsMin[i][j]=INT_MAX;
            if(i==j){
                anwsMax[i][j]=num[i];
                anwsMin[i][j]=num[i];
            }
        }
    }
        
        
    for(int L=2;L<=len;L++){
        for(int i=0;i<len-L+1;i++){
           int j = i+L-1;
            for(int k=i;k<j;k++){
                
                if(op[k]=='+'){
                    d = anwsMax[i][k]+anwsMax[k+1][j];
                    c = anwsMax[i][k]+anwsMin[k+1][j];
                    b = anwsMin[i][k]+anwsMax[k+1][j];
                    a = anwsMin[i][k]+anwsMin[k+1][j];
                }
                else if(op[k]=='*'){
                    d = anwsMax[i][k]*anwsMax[k+1][j];
                    c = anwsMax[i][k]*anwsMin[k+1][j];
                    b = anwsMin[i][k]*anwsMax[k+1][j];
                    a = anwsMin[i][k]*anwsMin[k+1][j];
                }
                else if(op[k]=='-'){
                    d = anwsMax[i][k]-anwsMax[k+1][j];
                    c = anwsMax[i][k]-anwsMin[k+1][j];
                    b = anwsMin[i][k]-anwsMax[k+1][j];
                    a = anwsMin[i][k]-anwsMin[k+1][j];
                }
                
                int array[4] = {a,b,c,d};
                
                for(int x=0;x<4;x++){
                    if(array[x]>anwsMax[i][j]){
                        anwsMax[i][j] = array[x];
                        kMax[i][j] = k;
                        fromMax[i][j] = x;
                    }
                    if(array[x]<anwsMin[i][j]){
                        anwsMin[i][j] = array[x];
                        kMin[i][j] = k;
                        fromMin[i][j] = x;
                    }
                }
            }
        }
    }
   cout << outcome(0,len-1,true) << "\n"; //true -> anwsMax
   return 0;

    }



string outcome(int i,int j,bool MaxOrNot){
    //cout<<i<<" "<<j<<endl;
    
    if(j==i){
        return to_string(num[i]);
    }
    else{
        if(MaxOrNot){
            int from = fromMax[i][j];
            bool l = from & 2; //與10 and  只取左邊的值
            bool r = from & 1; //與01 and  只取右邊的值
            int k = kMax[i][j];
            return "("+outcome(i, k,l )+op[k]+outcome(k+1, j,r)+")";

        }
        else {
            int from = fromMin[i][j];

            bool l = from & 2;
            bool r = from & 1;
            int k = kMin[i][j];
            return "("+outcome(i, k,l)+op[k]+outcome(k+1, j,r)+")";

        }
    }
}
/*
 5-8+7*4-8+9
 -11+22--11-22
 2-7*5+1-4+8*3
 */
