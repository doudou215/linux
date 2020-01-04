/*************************************************************************
	> File Name: fib.cpp
	> Author: 
	> Mail: 
	> Created Time: Sat 04 Jan 2020 06:53:27 AM PST
 ************************************************************************/

#include<iostream>
#include<vector>

using namespace std;

const vector<int>* fibon_seq(int );
bool is_size_ok(int );
bool fib_elem(int ,int &);
const vector<int>* my_seq(int);
template <typename elemType>
void display_message(string &msg,vector<elemType> &elems){
    cout<<msg;
    for(int i=0;i<elems.size();i++){
        cout<<elems[i]<<' ';
    }
}
int main(){
    int a;
    fib_elem(10,a);
    return 0;
}

bool is_size_ok(int size){
    if(size<0||size>1024){
        cout<<"error posizion"<<endl; 
        return false;
    }
    return true;
}
const vector<int>* fibon_seq(int size){
    static vector<int> elem;
    if(!is_size_ok(size)){
        return 0;
    }
    for(int i=0;i<size;i++){
        if(i==0||i==1)
            elem.push_back(i);
        else
            elem.push_back(elem[i-1]+elem[i-2]);
    }       
    return &elem;
}
const vector<int>* my_seq(int size){
    static vector<int> elem1;
    if(!is_size_ok(size))
        return 0;
    for(int i=0;i<size;i++){
        elem1.push_back(i+1);
    }
    return &elem1;
}
bool fib_elem(int size,int &ele){
    const vector<int>* (*seq_array[])(int)={my_seq,fibon_seq};
    const vector<int>* (*index)(int);
    for(int i=0;i<2;i++){
        index=seq_array[i];
        const vector<int>* ptr=index(size);
        if(!ptr){
            ele=0;
            return false;
        }
        ele=(*ptr)[size-1];
        cout<<seq_array[i]<<' '<<ele<<endl;
    }
    return true;
}
