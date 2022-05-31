#include <iostream>
#include <algorithm>
#include <stdexcept>

//**************************************************************************************//
template<typename vt , size_t height, size_t width>
class matrix;

template<typename vt , size_t height, size_t width>
bool operator==(const matrix<vt,height,width>& lhl,const matrix<vt,height,width>& rhl);

template<typename vt , size_t height, size_t width>
bool operator!=(const matrix<vt,height,width>& lhl,const matrix<vt,height,width>& rhl);

//*********************************************************************************//
template<typename vt , size_t height, size_t width>
class matrix{
    vt array[height][width];

public:
    matrix(){
        for (int i = 0; i <height ; ++i) {
            for (int j = 0; j < width; ++j) {
                array[i][j]=0;
            }
        }
    }

    matrix(const vt& num){
        for (int i = 0; i <height ; ++i) {
            for (int j = 0; j < width; ++j) {
                array[i][j]=num;
            }
        }
    }



    matrix(const matrix<vt,height,width>& other){
        for (int i = 0; i <height ; ++i) {
            for (int j = 0; j < width; ++j) {
                array[i][j]=other.array[i][j];
            }
        }
    }

    matrix<vt,height,width>& operator=(const matrix<vt,height,width>& other){
        for (int i = 0; i <height ; ++i) {
            for (int j = 0; j < width; ++j) {
                array[i][j]=other.array[i][j];
            }
        }
        return *this;
    }


    vt& at(const size_t& i, const size_t& j){return array[i][j];}
    const vt& at(const size_t& i, const size_t& j)const{return array[i][j];}

    friend bool operator==<>(const matrix<vt,height,width>& lhl,const matrix<vt,height,width>& rhl);
    friend bool operator!=<>(const matrix<vt,height,width>& lhl,const matrix<vt,height,width>& rhl);

    matrix<vt, height, width>& operator += (const matrix<vt,height,width>& lhl){
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                array[i][j]+= lhl.array[i][j];
            }
        }
        return *this;
    }


    matrix<vt, height, width>& operator -= (const matrix<vt,height,width>& lhl){
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                array[i][j] -= lhl.array[i][j];
            }
        }
        return *this;
    }

    matrix<vt, height, width>& operator *= (const matrix<vt,height,width>& a){
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                array[i][j]*= a.array[i][j];
            }
        }
        return *this;
    }

    const matrix<vt, height, width> operator - ()const{
        matrix<vt, height, width> res = *this;
        res*=-1;
        return res;
    }

    const matrix<vt, height, width> operator + () const {
        matrix<vt, height, width> res = *this;
        return res;
    }


    friend matrix<vt, height, width> operator + (const matrix<vt,height,width>& rhl , const matrix<vt,height,width>& lhl){
        matrix<vt,height,width> bruh=rhl;
        bruh+=lhl;
        return bruh;
    }

    friend matrix<vt, height, width> operator - (const matrix<vt,height,width>& lhl,const matrix<vt,height,width>& rhl){
        matrix<vt,height,width>bruh=lhl;
  
           bruh -= rhl;
           return bruh;
       
    }


    friend matrix<vt, height, width> operator *(const matrix<vt,height,width>& rhl,const matrix<vt,height,width>& lhl){
        matrix<vt,height,width> bruh=rhl;
        bruh *= lhl;
        return bruh;
    }

    bool areSame(){
        int first = array[0][0];
        for (int i = 1; i < height; i++){
            for (int j = 0; j < width; ++j) {
                if (array[i][j] != first )
                    return 0;
            }
        }
        return 1;
    }

    void print(){
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                std::cout<<array[i][j]<<" ";
            }
            std::cout<<std::endl;
        }
    }

    template<size_t heightb, size_t widthb>
    matrix<vt, height, widthb>& operator *= (const matrix<vt,heightb,widthb>& a){
        matrix<vt,height, widthb> bruh(*this);
        for (int i = 0; i <height ; ++i) {
            for (int j = 0; j < widthb; ++j) {
                int sum = 0;
                for(int k=0;k<width;k++)
                {
                    sum += (*this).at(i,k) * a.at(k,j);
                }
                bruh.at(i,j) = sum;
            }
        }
        *this=bruh;
        return *this;
    }


    matrix<vt, width, height> transposed()const{
        matrix<vt,width, height> bruh;
        matrix<vt,height,width>bro(*this);
        for (int i = 0; i < width; ++i) {
            for (int j = 0; j < height; ++j) {
                bruh.at(i,j)=bro.at(j,i);
            }
        }
        return bruh;
    }

    vt trace()const{
        vt sum=0;
        for (int i = 0; i < width; ++i) {
            for (int j = 0; j < height; ++j) {
                if(i==j){
                    sum+=(*this).at(i,j);
                }
            }
        }
        return sum;
    }


    int determinantOfMatrix(int matrix[height][height], int n)const;
    void subMatrix(int mat[height][height], int temp[height][height], int p, int q, int n)const;

    int det()const{
        matrix<vt,height,width>bro=*this;
        int s=determinantOfMatrix(bro.array, height);
        return s;
    }

};


//******************************************************************************//

template<typename vt , size_t height, size_t width>
bool operator==(const matrix<vt,height,width>& lhl,const matrix<vt,height,width>& rhl){
    for (int i = 0; i <height ; ++i) {
        for (int j = 0; j < width; ++j) {
            if(lhl.array[i][j]!=rhl.array[i][j]){
                return false;
            }
        }
    }
    return true;
}

template<typename vt , size_t height, size_t width>
bool operator!=(const matrix<vt,height,width>& lhl,const matrix<vt,height,width>& rhl){
    return !(lhl==rhl);
}

template<typename vt , size_t height, size_t width, size_t widthb,size_t heightb>
matrix<vt, height, widthb> operator *(const matrix<vt,height,width>& lhl,const matrix<vt,heightb,widthb>& rhl){
    matrix<vt,height, widthb> brh;
    for (int i = 0; i <height ; ++i) {
        for (int j = 0; j < widthb; ++j) {
            int sum = 0;
            for(int k=0;k<width;k++)
            {
                sum += lhl.at(i,k) * rhl.at(k,j);
            }
            brh.at(i,j) = sum;
        }
    }
    return brh;
}

//*****************************************************************************************//
template<typename vt , size_t height, size_t width>
void matrix<vt , height,width>::subMatrix(int mat[height][height], int temp[height][height], int p, int q, int n)const{
    int i = 0, j = 0;
    // filling the sub matrix
    for (int row = 0; row < n; row++){
        for (int col = 0; col < n; col++) {
            // skipping if the current row or column is not equal to the current
            // element row and column
            if (row != p && col != q) {
                temp[i][j++] = mat[row][col];
                if (j == n - 1) {
                    j = 0;
                    i++;
                }
            }
        }
    }
}

template<typename vt , size_t height, size_t width>
int matrix<vt , height,width>::determinantOfMatrix(int matrix[height][height], int n)const{
    int determinant = 0;
    if (n == 1) {
        return matrix[0][0];
    }
    if (n == 2) {
        return (matrix[0][0] * matrix[1][1]) - (matrix[0][1] * matrix[1][0]);
    }
    int temp[height][height], sign = 1;
    for (int i = 0; i < n; i++) {
        subMatrix(matrix, temp, 0, i, n);
        determinant += sign * matrix[0][i] * determinantOfMatrix(temp, n - 1);
        sign = -sign;
    }
    return determinant;
}
