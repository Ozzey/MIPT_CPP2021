#include <iostream>
#include <cstddef>
#include <algorithm>

class layered_matrix {
private:
    int **values;
    size_t n;

public:
    layered_matrix() = delete;
    layered_matrix(size_t n);
    ~layered_matrix();
    layered_matrix(const layered_matrix &m);
    layered_matrix& operator=(const layered_matrix &m);
    int get_sum(size_t x1, size_t y1, size_t x2, size_t y2) const;
};

layered_matrix::layered_matrix(size_t matrix_size) {
    n = matrix_size;
    values = new int*[n];
    for (size_t i = 0; i < n; i++)
        values[i] = new int[n];
    int *a;
    a = new int[2*n];
    for (size_t i = 1; i < 2*n; i++) {
        a[i] = (i <= n ? (n - i + 1) : i - n + 1);
    }
    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < n; j++)
            values[i][j] = a[n - i + j] - 1;
    delete[] a;
}

layered_matrix::~layered_matrix() {
    for (size_t i = 0; i < n; i++)
        delete values[i];
    delete values;
}

layered_matrix::layered_matrix(const layered_matrix  &m) : n(m.n) {
    values = new int*[n];
    for (size_t i = 0; i < n; i++)
        values[i] = new int[n];
    for (size_t i = 0; i < n; i++)
        for(size_t j = 0; j < n; j++)
            values[i][j] = m.values[i][j];
}

layered_matrix& layered_matrix::operator=(const layered_matrix &m) {
    n = m.n;
    values = new int*[n];
    for (size_t i = 0; i < n; i++)
        values[i] = new int[n];
    for (size_t i = 0; i < n; i++)
        for(size_t j = 0; j < n; j++)
            values[i][j] = m.values[i][j];
    return *this;
}

int layered_matrix::get_sum(size_t x1, size_t y1, size_t x2, size_t y2)
const {
    int sum = 0;
    for (int i = std::min(x1,x2); i <= std::max(x1,x2); i++)
        for (int j = std::min(y1,y2); j <= std::max(y1,y2); j++)
            if (i == x1 || i == x2 || j == y1 || j == y2)
                sum += values[i][j];
    return sum;
}

//driver code
