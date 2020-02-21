/*************************************************************************
	> File Name: binaryTree.cpp
	> Author: 
	> Mail: 
	> Created Time: Thu 06 Feb 2020 02:08:07 AM PST
 ************************************************************************/
#include<string>
#include<vector>
#include<iostream>
using namespace std;


template<typename elemType>
class BinaryTree;

template<typename valType>
class BTnode{
public:
    friend class BinaryTree<valType>;
    BTnode(const valType &val);
    void insert_val(const valType &val);
    void remove_value(const valType &val,BTnode *&prev);
    static void lchild_leaf(BTnode *leaf,BTnode *subtree);
    void preorder(BTnode *p,ostream &os);
    ~BTnode() { }
private:
    valType _val;
    int _cnt;
    BTnode *_lchild;
    BTnode *_rchild;
};


template<typename elemType>
inline void BTnode<elemType>::
preorder(BTnode *p,ostream &os){
    if(p){
        os<<p->_val<<endl;
        preorder(p->_lchild,os);
        preorder(p->_rchild,os);
    }
}
template<typename elemType>
inline void BTnode<elemType>::
lchild_leaf(BTnode *leaf,BTnode *subtree){
	while(subtree->_lchild)
		subtree=subtree->_lchild;
	subtree->_lchild=leaf;
}

template<typename elemType>
inline void BTnode<elemType>::
    insert_val(const elemType &val){
        if(val==_val){
            _cnt++;
        }
        else if(val<_val){
            if(!_lchild)
                _lchild=new BTnode(val);
            else
                _lchild->insert_val(val);
        }
        else{
            if(!_rchild)
                _rchild=new BTnode(val);
            else
                _rchild->insert_val(val);
        }
    }

template<typename valType>
inline BTnode<valType>::BTnode(const valType &val):_val(val){
    _cnt=0;
    _lchild=0;
    _rchild=0;
}



template<typename elemType>
class BinaryTree{
public:
    BinaryTree();
    ~BinaryTree() { }
    BinaryTree(const BinaryTree &rhs);
    BinaryTree& operator=(const BinaryTree &rhs);
    bool empty() {return _root==0;}
    void clear();
    void insert(const elemType &val);
    void remove(const elemType &val);
    void root_remove();
    void preorder();
private:
    BTnode<elemType> *_root;
    void copy(BTnode<elemType> *tar,BTnode<elemType> *src);
    void clear(BTnode<elemType> *node);
};

template<typename elemType>
inline void BinaryTree<elemType>::
preorder(){
        if(_root)
            _root->preorder(_root,cout);
}


template<typename elemType>
inline void BinaryTree<elemType>::
root_remove(){
	BTnode<elemType> *tmp;
    tmp=_root;
	if(_root->_rchild){
		if(_root->_lchild){
			BTnode<elemType>::lchild_leaf(_root->_lchild,_root->_rchild);
		}		
		_root=_root->_rchild;	
	}
	else if(_root->_lchild){
		_root=_root->_lchild;
	}
	delete tmp;
}

template<typename elemType>
inline BinaryTree<elemType>::
    BinaryTree():_root(0){}

template<typename elemType>
inline BinaryTree<elemType>::
    BinaryTree(const BinaryTree &rhs){
        copy(_root,rhs._root);
    }
template<typename elemType>
inline BinaryTree<elemType>&
BinaryTree<elemType>::
    operator=(const BinaryTree& rhs){
        if(this!=&rhs){
            clear();
            copy(_root,rhs._root);
        }
        return *this;
    }

template<typename elemType>
inline void BinaryTree<elemType>::
    insert(const elemType &val){
        if(!_root){
            _root=new BTnode<elemType>(val);
        }
        else
            _root->insert_val(val);
    }

template<typename elemType>
inline void BinaryTree<elemType>::
remove(const elemType &val){
	if(_root){
		if(_root->_val==val)
			root_remove();
		else
			_root->remove_value(val,_root);

	}

}

template<typename elemType>
void BTnode<elemType>::remove_value(const elemType &val,BTnode *&prev){
	if(_val>val){
		if(_lchild)
			_lchild->remove_value(val,_lchild);
		return;
	}
	else if(_val<val){
		if(_rchild)
			_rchild->remove_value(val,_rchild);
		return;
	}
    if(_rchild){
		prev=_rchild;
		if(_lchild)
			BTnode<elemType>::lchild_leaf(_lchild,_rchild);
    }
	else if(_lchild)
		prev=_lchild;
    delete this;
}

template<typename elemType>
void BinaryTree<elemType>::
clear(){
	if(!_root)
		clear(_root);
	_root=0;
}

template<typename elemType>
void BinaryTree<elemType>::
clear(BTnode<elemType> *p){
	if(p)
	{
		clear(p->_lchild);
		clear(p->_rchild);
		delete p;
	}
}



int main(){
    BinaryTree<string> bt;
    bt.insert("Pig");
    bt.insert("Monkey");
    bt.insert("Tigger");
    bt.insert("Dog");
    bt.insert("Chris");
    bt.insert("Roo");
    bt.insert("Rachel");
    bt.preorder();
    cout<<endl;
    bt.remove("Dog");
    bt.preorder();
    cout<<"\ndelete whole tree";
    bt.clear();
    bt.preorder();
    return 0;
}



