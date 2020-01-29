/*************************************************************************
	> File Name: class.cpp
	> Author: 
	> Mail: 
	> Created Time: Sun 26 Jan 2020 12:46:35 AM PST
 ************************************************************************/
#include<vector>
#include<iostream>
#include<string>


using namespace std;


class Triangular_iterator{
public:
    Triangular_iterator (int index): _index(index) {}
    bool operator==(const Triangular_iterator &rhs) const{
        return rhs._index == _index;
    }

    bool operator!=(const Triangular_iterator &rhs) const{
        return !(rhs==(*this));
    }
    int operator*() const;    
    Triangular_iterator& operator++(){
        _index++;
        check_integrity();
        return *(this);
    }
    Triangular_iterator operator++(int){
        _index++;
        check_integrity();
        return *(this);
    }
    void check_integrity() const;
    int _index;
    
};
class Triangular{
public:
    friend int Triangular_iterator::operator*() const;
    friend void Triangular_iterator::check_integrity() const;
    Triangular(string name):_name(name){
         _beg_pos=0;
    }
    ~Triangular() {}
    static void gen_elements(int length){
        if(length>_max_size)
            return;
        int index=_elem.size();
        if(!index){
            _elem.push_back(1);
            index=0;
        }
        for(;index<length;index++)
            _elem.push_back(_elem[index-1]*2);   
    }
    typedef Triangular_iterator iterator;
    Triangular_iterator begin() const{
        return Triangular_iterator(_beg_pos);
    }
    Triangular_iterator end() const{
        return Triangular_iterator(_beg_pos+_elem.size());
    }
    static vector<int> _elem;
private:
   
    static const int _max_size=1024;
    int _beg_pos;
    string _name;
};

vector<int> Triangular::_elem;
  
inline void Triangular_iterator::check_integrity() const{
    if(_index>Triangular::_max_size){
        cout<<"invalid index"<<endl;
        return;
    }
    if(_index>Triangular::_elem.size())
        Triangular::gen_elements(_index);

}

inline int Triangular_iterator::operator*() const{
    check_integrity();
    return Triangular::_elem[_index];
}
int main(){
    Triangular tri("a");
    Triangular::iterator it=tri.begin();
    Triangular::gen_elements(3);
    Triangular::iterator end=tri.end();
    cout<<Triangular::_elem[2]<<endl;

    return 0;
}


