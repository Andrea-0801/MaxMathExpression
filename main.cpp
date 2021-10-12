#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
using namespace::std;
string outcome(int,int);
bool isOperator(char op){
    return (op=='+'||op=='*');
}

vector<int>num;
vector<char>op;
int anws[100][100];

int main(int argc, const char * argv[]) {
    string input,temp="";
    cin>>input; //12+3*5 30 17
    
    for(int i=0;i<input.length();i++){
        if(isOperator(input[i])){
            op.push_back(input[i]);
            num.push_back(atoi(temp.c_str()));
            temp="";
        }
        else{
            temp+=input[i];
        }
        
    }
    num.push_back(atoi(temp.c_str()));
    int len = int(num.size());
    int max[len][len];
    //int anws[len][len];
    
    
    
    for(int i=0;i<len;i++){
        for(int j=0;j<len;j++){
            max[i][j]=0;
            if(i==j){
                max[i][j]=num[i];
            }
        }
    }
        
        
        for(int L=2;L<=len;L++){
            for(int i=0;i<len-L+1;i++){
                int j = i+L-1;
                for(int k=i;k<j;k++){
                    int maxTemp=0;
                    if(op[k]=='+'){
                        maxTemp = max[i][k]+max[k+1][j];
                    }
                    else if(op[k]=='*'){
                        maxTemp = max[i][k]*max[k+1][j];
                    }
                    if(maxTemp>max[i][j]){
                        max[i][j]=maxTemp;
                        anws[i][j] = k;
                    }
                }
            }
        }
           /* for(int i=0;i<num.size();i++){
            cout<<" "<<num[i];
        }
        cout<<endl;
        for(int i=0;i<op.size();i++){
            cout<<" "<<op[i];
        }*/
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len; j++) {
            cout<<max[i][j]<<" ";
        }
        cout<<endl;
    }
    
      cout << outcome(0,len-1) << "\n";
        cout<<max[0][len-1] << "\n";
    /*for (int i = 0; i < len; i++) {
        for (int j = 0; j < len; j++) {
            cout << anws[i][j] << " \n"[j + 1 == len];
        }
    }*/
        return 0;

    }



string outcome(int i,int j){
    //cout<<i<<" "<<j<<endl;
    if(j==i){
        return to_string(num[i]);
    }
    else{
        int k = anws[i][j];
        //cout << k << "\n";
        return "("+outcome(i, k)+op[k]+outcome(k+1, j)+")";
        
    }
}
