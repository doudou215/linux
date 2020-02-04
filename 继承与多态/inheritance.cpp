/*************************************************************************
	> File Name: inheritance.cpp
	> Author: 
	> Mail: 
	> Created Time: Sat 01 Feb 2020 12:25:06 AM PST
 ************************************************************************/

#include<iostream>
#include<string>
#include<vector>



using namespace std;

class num_sequence{
public:
    num_sequence() {}
    virtual ~num_sequence()  {}
    virtual int elem(int pos) const=0;
    virtual const char* what_am_i() const=0;
    virtual ostream& print(ostream &os=cout) const=0;

protected:
    const static int _max_size=1024;
    virtual void gen_elems(int pos) const=0;
    bool check_intergrity(int pos,int size) const;
};


ostream& operator<<(ostream &os,const num_sequence& rhs) {
        return rhs.print(os);
    }
const int num_sequence::_max_size;


bool num_sequence::check_intergrity(int pos,int size) const{
    if(pos<0||pos>_max_size){
        cout<<"error pos"<<endl;
        return false;
    }
    if(pos>size)
        gen_elems(pos);
    return true;
}


class Fibonacci: public num_sequence{
public:
    Fibonacci(int len,int beg):_len(len),_beg(beg){}
    virtual const char* what_am_i() const;
    virtual void gen_elems(int pos) const;
    virtual int  elem(int pos) const;
    virtual ostream& print(ostream &os=cout) const;
protected:
    int _len;
    static vector<int> _elems;
    int _beg;
};

vector<int> Fibonacci::_elems;

const char* Fibonacci::what_am_i() const{
    return "Fibonacci";
}

int Fibonacci::elem(int pos) const{
    if(check_intergrity(pos,_elems.size())==false)
        return 0;
    return _elems[pos-1];

}


void Fibonacci::gen_elems(int pos) const{
    if(_elems.size()==0){
        _elems.push_back(1);
        _elems.push_back(1);
    }

    for(int i=2;i<pos;i++){
        int data=_elems[i-1]+_elems[i-2];
        _elems.push_back(data);
    }
}


ostream& Fibonacci::print(ostream& os) const{
    int elem_pos=_beg-1;
    int end_pos=elem_pos+_len;
    
    if(!check_intergrity(end_pos,_elems.size())){
        return os;
    }

    while(elem_pos<end_pos)
        os<<_elems[elem_pos++]<<' ';

    return os;
}





int main(){
    Fibonacci f(1,10);
    f.print();
    num_sequence *ps=&f;
    ps->print();
    return 0;

}
