/*
 * =========================================================================================
 * Name        : dsaLib.h
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - Bach Khoa University
 * Description : Library for Assignment 2 - Data structures and Algorithms - Spring 2018
 * =========================================================================================
 */

#ifndef A02_DSALIB_H
#define A02_DSALIB_H

#include <string>
#include <math.h>
#include <vector>

using namespace std;


class DSAException {
    int     _error;
    string  _text;
public:

    DSAException() : _error(0), _text("Success") {}
    DSAException(int err) : _error(err), _text("Unknown Error") {}
    DSAException(int err, const char* text) : _error(err), _text(text) {}

    int getError() { return _error; }
    string& getErrorText() { return _text; }
};

template <class T>
class List {
public:
    virtual void    clean() = 0;
    virtual void    clone(void*) = 0;
    virtual bool    isEmpty() = 0;
    virtual size_t  getSize() = 0;
    virtual T&      at(int i) = 0;
    virtual T&      operator[](int i) = 0;

    virtual bool    find(T& a, int& idx) = 0;
    virtual T*      find(T& a) = 0;
    virtual T*      find(T& a, bool (*eqCmp)(T&, T&)) = 0;
    virtual int     insert(int i, T& a) = 0;
    virtual int     insert(int i, T&& a) = 0;
    virtual int     remove(int i) = 0;
    virtual int     remove(T& a, bool (*eqCmp)(T&, T&)) = 0;

    virtual int     push_back(T& a) = 0;
    virtual int     push_back(T&& a) = 0;
    virtual int     insertHead(T& a) = 0;
    virtual int     insertHead(T&& a) = 0;
    virtual int     removeHead() = 0;
    virtual int     removeLast() = 0;

    virtual void    traverse(void (*op)(T&)) = 0;
    virtual void    traverse(void (*op)(T&, void*), void* pParam) = 0;

    virtual void    reverse() = 0;
};

template <class T>
struct L1Item {
    T data;
    L1Item<T> *pNext;

    L1Item(T &a) : data(a), pNext(NULL) {}
    L1Item(T &a, void* next) : data(a), pNext((L1Item<T>*)next) {}
    L1Item(T &&a) : data(std::move(a)), pNext(NULL) {}
    L1Item(T &&a, void* next) : data(std::move(a)), pNext((L1Item<T>*)next) {}
};

template <class T>
class L1List : public List<T> {
    L1Item<T>   *_pHead;
    size_t      _size;
public:
    L1List() : _pHead(NULL), _size(0) {}
    ~L1List(){clean();};

    // TODO: Code
    void    clean(){
        while(_pHead){
            L1Item<T> *p = _pHead;
            _pHead = _pHead->pNext;
            delete p;
            p = NULL;
        }
    }

    // TODO: Code
    void    clone(void*){
        return;
    }

    bool    isEmpty() { return _pHead == NULL; }
    size_t  getSize() { return _size; }

    // TODO: Code
    T&      at(int i){
        if(i < 0 || i > _size) throw -1;
        L1Item<T> *p = _pHead;
        while(i > 0){
            p = p->pNext;
            i--;
        }
        return p->data;
    }

    // TODO: Code
    T&      operator[](int i){
        if(i < 0 || i > _size) throw -1;
        L1Item<T> *p = _pHead;
        while(i > 0){
            p = p->pNext;
            i--;
        }
        return p->data;
    }

    // TODO: Code
    bool    find(T& a, int& idx){
        L1Item<T> *p = _pHead;
        idx = 0;
        while(p){
            if(p->data == a){
                return true;
            }
            idx++;
            p = p->pNext;
        }
        return false;
    }

    // TODO: Code
    T*      find(T& a){
        L1Item<T> *p = _pHead;
        while(p){
            if(p->data == a){
                return &p->data;
            }
            p = p->pNext;
        }
        throw -1;
    }

    // TODO: Code
    T*      find(T& a, bool (*eqCmp)(T&, T&)){
        L1Item<T> *p = _pHead;
        while(p){
            if(p->data == a){
                return &p->data;
            }
            p = p->pNext;
        }
        throw -1;
    }
    
    // TODO: Code
    int     insert(int i, T& a){
        if(i == 0) return insertHead(a);
        L1Item<T> *pPre = _pHead;
        L1Item<T> *pCur = pPre->pNext;
        while(i > 1){
            i--;
            pPre = pCur;
            pCur = pCur->pNext;
        }
        pPre->pNext = new L1Item<T>(a, pCur);
        _size++;
        return 0;
    }

    // TODO: Code
    int     insert(int i, T&& a){
        if(i == 0) return insertHead(a);
        L1Item<T> *pPre = _pHead;
        L1Item<T> *pCur = pPre->pNext;
        while(i > 1){
            i--;
            pPre = pCur;
            pCur = pCur->pNext;
        }
        pPre->pNext = new L1Item<T>(std::move(a), pCur);
        _size++;
        return 0;
    }

    // TODO: Code
    int     remove(int i){
        if(i == 0) return removeHead();
        L1Item<T> *pPre = _pHead;
        L1Item<T> *pCur = pPre->pNext;
        while(i > 1){
            i--;
            pPre = pCur;
            pCur = pCur->pNext;
        }
        pPre->pNext = pCur->pNext;
        delete pCur;
        pCur = NULL;
        _size--;
        return 0;
    }

    // TODO: Code
    int     remove(T& a, bool (*eqCmp)(T&, T&)){
        if(_pHead->data == a) return removeHead();
        L1Item<T> *pPre = _pHead;
        L1Item<T> *pCur = pPre->pNext;
        while(pCur){
            if(pCur->data == a){
                pPre->pNext = pCur->pNext;
                delete pCur;
                pCur = NULL;
                _size--;
                return 0;
            }
            pPre = pCur;
            pCur = pCur->pNext;
        }
        return -1;
    }

    int     push_back(T& a);
    int     push_back(T&& a);
    int     insertHead(T& a);
    int     insertHead(T&& a);
    int     removeHead();
    int     removeLast();

    // TODO: Code
    void    reverse(){
        L1Item<T> *pPre = NULL;
        L1Item<T> *pCur = _pHead;
        L1Item<T> *pNex = NULL;
        while(pCur){
            pNex = pCur->pNext;
            pCur->pNext = pPre;
            pPre = pCur;
            pCur = pNex;
        }
        _pHead = pPre;
    }

    void    traverse(void (*op)(T&)) {
        L1Item<T>   *p = _pHead;
        while (p) {
            op(p->data);
            p = p->pNext;
        }
    }
    void    traverse(void (*op)(T&, void*), void* pParam) {
        L1Item<T>   *p = _pHead;
        while (p) {
            op(p->data, pParam);
            p = p->pNext;
        }
    }
};

/// Insert item to the end of the list
/// Return 0 if success
template <class T>
int L1List<T>::push_back(T &a) {
    if (_pHead == NULL) {
        _pHead = new L1Item<T>(a);
    }
    else {
        L1Item<T>   *p = _pHead;
        while (p->pNext) p = p->pNext;
        p->pNext = new L1Item<T>(a);
    }

    _size++;
    return 0;
}

template <class T>
int L1List<T>::push_back(T &&a) {
    if (_pHead == NULL) {
        _pHead = new L1Item<T>(std::move(a));
    }
    else {
        L1Item<T>   *p = _pHead;
        while (p->pNext) p = p->pNext;
        p->pNext = new L1Item<T>(std::move(a));
    }

    _size++;
    return 0;
}

/// Insert item to the front of the list
/// Return 0 if success
template <class T>
int L1List<T>::insertHead(T &a) {
    L1Item<T>   *p = new L1Item<T>(a);
    p->pNext = _pHead;
    _pHead = p;
    _size++;
    return 0;
}

template <class T>
int L1List<T>::insertHead(T&& a) {
    L1Item<T>   *p = new L1Item<T>(std::move(a));
    p->pNext = _pHead;
    _pHead = p;
    _size++;
    return 0;
}

/// Remove the first item of the list
/// Return 0 if success
template <class T>
int L1List<T>::removeHead() {
    if(_pHead) {
        L1Item<T>* p = _pHead;
        _pHead = p->pNext;
        delete p;
        _size--;
        return 0;
    }
    return -1;
}

/// Remove the last item of the list
/// Return 0 if success
template <class T>
int L1List<T>::removeLast() {
    if(_pHead) {
        if(_pHead->pNext) {
            L1Item<T>* prev = _pHead;
            L1Item<T>* pcur = prev->pNext;
            while(pcur->pNext) {
                prev = pcur;
                pcur = pcur->pNext;
            }
            delete pcur;
            prev->pNext = NULL;
        }
        else {
            delete _pHead;
            _pHead = NULL;
        }
        _size--;
        return 0;
    }
    return -1;
}

/************************************************************************
 * This section is for AVL tree
 ************************************************************************/
template <class T>
struct AVLNode {
    T           _data;
    AVLNode<T>   *_pLeft, *_pRight;
#ifdef AVL_USE_HEIGHT
    int         _height;
    AVLNode(T &a) : _data(a), _pLeft(NULL), _pRight(NULL), _height(1) {}
#else
    int         _bFactor;
    AVLNode(T &a) : _data(a), _pLeft(NULL), _pRight(NULL), _bFactor(0) {}
#endif
};

template <class T>
class AVLTree {
    AVLNode<T> *_pRoot;
public:
    AVLTree() : _pRoot(NULL) {}
    ~AVLTree() { destroy(_pRoot); }

    bool find(T& key, T* &ret) { return find(_pRoot, key, ret); }
    bool insert(T& key) { return insert(_pRoot, key); }
    bool remove(T& key) { return remove(_pRoot, key); }
    void traverseNLR(void (*op)(T&)) { traverseNLR(_pRoot, op); }
    void traverseLNR(void (*op)(T&)) { traverseLNR(_pRoot, op); }
    void traverseLRN(void (*op)(T&)) { traverseLRN(_pRoot, op); }

protected:

    // TODO: Code
    void destroy(AVLNode<T>* &pR){
        if(pR == NULL) return;
        destroy(pR->_pLeft);
        destroy(pR->_pRight);
        delete pR;
    }

    bool find(AVLNode<T> *pR, T& key, T* &ret);

    // TODO: Code
    bool insert(AVLNode<T>* &pR, T& a){
        if(pR == NULL){
            pR = new AVLNode<T>(a);
            return true;
        }
        if(a < pR->data){
            if(insert(pR->_pLeft, a) == false) return false;
            if(pR->_bFactor == 0){
                pR->_bFactor = -1;
                return true;
            }
            if(pR->_bFactor == 1){
                pR->_bFactor = 0;
                return false;
            }
            if(pR->_bFactor == -1){
                rotRight(pR);
                pR->_bFactor = 0;
                pR->_pRight->_bFactor = 0;
                return false;
            }
        }
        rotLeft(pR);
        if(pR->_bFactor == -1){
            pR->_bFactor = 0;
            pR->_pLeft->_bFactor = 0;
            pR->_pRight->_bFactor = 1;
            return false;
        }
        if(pR->_bFactor = 1){
            pR->_bFactor = 0;
            pR->_pRight->_bFactor = 0;
            pR->_pLeft->_bFactor = -1;
            return false;
        }
    }

    // TODO: Code
    bool remove(AVLNode<T>* &pR, T& a){

    }

    // TODO: Code
    void traverseNLR(AVLNode<T> *pR, void (*op)(T&)){
        op(pR->data);
        if(pR->_pLeft) traverseNLR(pR->_pLeft, op);
        if(pR->_pRight) traverseNLR(pR->_pRight, op);
    }

    // TODO: Code
    void traverseLNR(AVLNode<T> *pR, void (*op)(T&)){
        if(pR->_pLeft) traverseNLR(pR->_pLeft, op);
        op(pR->data);
        if(pR->_pRight) traverseNLR(pR->_pRight, op);
    }

    // TODO: Code
    void traverseLRN(AVLNode<T> *pR, void (*op)(T&)){
        if(pR->_pLeft) traverseNLR(pR->_pLeft, op);
        if(pR->_pRight) traverseNLR(pR->_pRight, op);
        op(pR->data);
    }

    // TODO: Code
    void rotLeft(AVLNode<T>* &pR){
        if(pR == NULL) return;
        AVLNode<T> *p = pR->_pRight;
        pR->_pRight = p->_pLeft;
        p->_pLeft = pR;
        pR = p;
    }

    // TODO: Code
    void rotRight(AVLNode<T>* &pR){
        if(pR == NULL) return;
        AVLNode<T> *p = pR->_pLeft;
        pR->_pLeft = p->_pRight;
        p->_pRight = pR;
        pR = p;
    }

    // TODO: Code
    void rotLR(AVLNode<T>* &pR){
        rotLeft(pR->_pLeft);
        rotRight(pR);
    }

    // TODO: Code
    void rotRL(AVLNode<T>* &pR){
        rotRight(pR->_pRight);
        rotLeft(pR);
    }

    bool balanceLeft(AVLNode<T>* &pR);
    bool balanceRight(AVLNode<T>* &pR);
};

#endif //A02_DSALIB_H
