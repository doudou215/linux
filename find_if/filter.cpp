/*************************************************************************
	> File Name: filter.cpp
	> Author: 
	> Mail: 
	> Created Time: Fri 17 Jan 2020 12:36:14 AM PST
 ************************************************************************/
 #include<functional>
 #include<algorithm>
#include<iostream>
#include<vector>
using namespace std;

template<typename InIterator,typename OutIterator,
         typename elemType,typename pred>
OutIterator
filter1(InIterator it,InIterator end,OutIterator at,elemType val,pred comp){
    while((it=find_if(it,end,bind2nd(comp,val)))!=end){
            *at++=*it++;
    }
    return at;
}
vector<int> bind_adapter(const vector<int>&,int,less<int> &);
bool less_than(int,int);
bool bigger_than(int,int);
void display(vector<int>&);
vector<int> filter(vector<int>&,int,bool (*pred)(int,int));
int main(){
    const int size=12;
    int array[size]={1,22,20,133,1,3,4,5,8,11,12,16};
    vector<int> vec1(array,array+size);
    vector<int> vec2=filter(vec1,5,less_than);
    vector<int> vec3=filter(vec1,5,bigger_than);
    //display(vec2);
    //display(vec3);
    display(vec1);
    //sort(vec1.begin(),vec1.end(),greater<int> ());
    vector<int> vec4(8);
    filter1(vec1.begin(),vec1.end(),vec4.begin(),16,greater<int>());
    display(vec4);
    return 0;
}
void display(vector<int> &vec){
    for(int i=0;i<vec.size();i++)
        cout<<vec[i]<<' ';
    cout<<endl;
}

bool less_than(int tar,int src){
    return tar>src?1:0;
}

bool bigger_than(int tar,int src){
    return tar<src?1:0;
}

vector<int> filter(vector<int> &vec,int value,bool (*pred)(int tar,int src)){
    vector<int> ret;
    for(int i=0;i<vec.size();i++){
        if(pred(value,vec[i]))
            ret.push_back(vec[i]);
    }
    return ret;
}
vector<int> bind_adapter(const vector<int> &vec,int value,less<int> &lt){
    vector<int> ret;
    vector<int>::const_iterator it=vec.begin();
    while(it!=vec.end()){
        if((it=(find_if(it,vec.end(),bind2nd(lt,value))))!=vec.end()){
            ret.push_back(*it);
            it++;
        }
    }
    return ret;
}
