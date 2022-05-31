#include <iostream>
#include <cmath>


//*********************************************************************//
template<size_t n>
class permutation;

template<size_t n>
bool operator<(const permutation<n> &,const permutation<n> &);

template<size_t n>
bool operator>(const permutation<n> &,const permutation<n> &);

template<size_t n>
bool operator<=(const permutation<n> &u, const permutation<n> &v);

template<size_t n>
bool operator>=(const permutation<n> &u, const permutation<n> &v);

template<size_t n>
bool operator==(const permutation<n> &u, const permutation<n> &v);

template<size_t n>
bool operator!=(const permutation<n> &,const permutation<n> &);

template<size_t n>
permutation<n> operator*(const permutation<n> &u, const permutation<n> &v);


//*****************************************************************//

template<size_t n>
class permutation{
    unsigned int arr[n];

public:

    permutation(){for(size_t i=0; i<n; i++){arr[i]=i;}}
    explicit permutation(const unsigned *array);
    permutation(const permutation<n>& other);
    permutation<n>& operator=(const permutation<n>& other);
    ~permutation<n>()=default;

    friend bool operator< <>(const permutation<n> &u, const permutation<n> &v);
    friend bool operator> <>(const permutation<n> &u, const permutation<n> &v);
    friend bool operator<=<>(const permutation<n> &u, const permutation<n> &v);
    friend bool operator>=<>(const permutation<n> &u, const permutation<n> &v);
    friend bool operator==<>(const permutation<n> &u, const permutation<n> &v);
    friend bool operator!=<>(const permutation<n> &u, const permutation<n> &v);

    unsigned int& operator[](const size_t position){return arr[position];};
    const unsigned int& operator[](const size_t position)const{return arr[position];};

    friend permutation<n> operator*<>(const permutation<n> &u,const permutation<n> &v);
    permutation<n>& operator*=(const permutation<n> &v);
    permutation<n>inverse() const;
    permutation<n> next() const;
    permutation<n> prev() const;

    //**************************************************//

    permutation<n>& operator++();
    permutation<n>& operator--();

    const permutation<n> operator++(int){permutation<n>temp(*this); ++(*this); return temp;}
    const permutation<n> operator--(int){permutation<n>temp(*this); --(*this); return temp;}

    //**************************************************//
    const void operator()(unsigned *array)const{
        unsigned int arr[n];
        for (int i = 0; i < n; ++i){arr[i]=array[i];}
        for (int i = 0; i < n; ++i) {array[(*this)[i]]=arr[i];}};


};

//*****************************************************************//

//***Constructors***//
template<size_t n>
permutation<n>::permutation(const unsigned *array){for(size_t i=0; i<n; i++){arr[i]=array[i];}}

template<size_t n>
permutation<n>::permutation(const permutation<n>& other){
    arr[0]=0;
    for (int i = 0; i < n; ++i) {
        arr[i] = other.arr[i];
    }
}

template<size_t n>
permutation<n>& permutation<n>::operator=(const permutation<n>& other) {
    for (int i = 0; i < n; ++i){this->arr[i] = other[i];}
    return *this;
}

//*****************************Logical operators************************************///

template<size_t n>
bool operator<(const permutation<n> &u,const permutation<n> &v){
    for (int i = 0; i <n ; ++i) {
        if(u[i]<v[i]){return true;}
        else if(u[i]>v[i]){return false;}
    }
    return false;
}

template<size_t n>
bool operator>(const permutation<n> &u,const permutation<n> &v){
    return v<u;
}

template<size_t n>
bool operator>=(const permutation<n> &u,const permutation<n> &v){
    return !(u<v);
}


template<size_t n>
bool operator<=(const permutation<n> &u,const permutation<n> &v){
    return !(v<u);
}

template<size_t n>
bool operator==(const permutation<n> &u,const permutation<n> &v){
    return !(u<v) && !(u>v);
}

template<size_t n>
bool operator!=(const permutation<n> &u,const permutation<n> &v){
    return u<v || v<u;
}


//***********************************Multiplication*************************************//

template<size_t n>
permutation<n> operator*(const permutation<n> &u, const permutation<n> &v){
    permutation<n> res;
    for (int i = 0; i <n; ++i) {res[i]=u[v[i]];}
    return res;
}

template<size_t n>
permutation<n>& permutation<n>::operator*=(const permutation<n> &v){return *this=(*this)*v;}

//**************************************METHODS*********************************************//

template<size_t n>
permutation<n> permutation<n>::inverse()const{
    permutation<n> res;
    for (int i = 0; i < n; ++i) {res[(*this)[i]]=i;}
    return res;}



//******************************************ARITHMETIC OPERATORS***************************//

//**************************************************//
template<size_t n>
permutation<n> permutation<n>::next() const{
    permutation<n>res= *this;
    ++res;
    return res;
}

//*********************************************
//**************************************************//
//1,0,2,3,4
//1,0,2,4,3
//1,0,3,2,4
//1,0,3,4,2
//1,0,4,2,3
//1,0,4,3,2
//1,2,0,3,4
//1,2,0,4,3
//**************************************************//

template<size_t n>
permutation<n> permutation<n>::prev() const{
    permutation<n>res= *this;
    --res;
    return res;
}

//*********************INCREMENT / DECREMENT OPERATOR*****************************//
template<size_t n>
permutation<n>& permutation<n>:: operator++(){
    int fix=0,iter=0;
    for (int i=1;i<n;++i){if ((*this)[i]>(*this)[i-1]){fix=i;}}

    int _n=n;
    if (fix!=0){
        for (int j=fix;j<n;++j){if ((*this)[j]>(*this)[fix-1]){iter=j;}}
        std::swap((*this)[fix-1],(*this)[iter]);
        while(fix<_n && _n--){std::swap((*this)[fix],(*this)[_n]);++fix;}
    }
    else{while(_n--){(*this)[_n]=_n;}}
    return *this;
}

//***DECREMENT****//

template<size_t n>
permutation<n>& permutation<n>:: operator--(){
    int fix=0,iter=0;
    for (int i=1;i<n;++i){if ((*this)[i]<(*this)[i-1]){fix=i;}}

    int _n=n;
    if (fix!=0){
        for (int j=fix;j<n;++j){if ((*this)[j]<(*this)[fix-1]){iter=j;}}
        std::swap((*this)[fix-1],(*this)[iter]);
       while(fix<_n && _n--){std::swap((*this)[fix],(*this)[_n]);++fix;}
    }
    else{while(_n--){(*this)[n-_n-1]=_n;}}
    return *this;
}
