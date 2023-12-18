#ifndef __T_MATRIX_H___
#define __T_MATRIX_H___

#include <assert.h>

#include <cstdlib>
#include <iostream>
#include <vector>

template<typename T>
class Matrix {
 private:
  int row;
  int col;
  std::vector<std::vector<T> > mat;

 public:
  Matrix() : row(0), col(0) {}
  Matrix(int r, int c) : row(r), col(c) {
    for (int i = 0; i < row; i++) {
      std::vector<T> lst(c);
      mat.push_back(lst);
    }
  }
  Matrix(const Matrix<T> & rhs) : row(rhs.row), col(rhs.col), mat(rhs.mat) {}
  ~Matrix() {}
  Matrix<T> & operator=(const Matrix<T> & rhs) {
    if (this != &rhs) {
      mat.clear();
      row = rhs.row;
      col = rhs.col;
      mat = rhs.mat;
    }
    return *this;
  }
  int getRows() const { return row; }
  int getColumns() const { return col; }
  const std::vector<T> & operator[](int idx) const {
    assert(row > idx && idx >= 0);
    return mat[idx];
  }
  std::vector<T> & operator[](int idx) {
    assert(row > idx && idx >= 0);
    return mat[idx];
  }
  bool operator==(const Matrix<T> & rhs) const {
    if (row != rhs.row || col != rhs.col || mat != rhs.mat) {
      return false;
    }
    return true;
  }
  Matrix<T> operator+(const Matrix<T> & rhs) const {
    assert(row == rhs.row && col == rhs.col);
    Matrix<T> res(row, col);
    for (int i = 0; i < row; i++) {
      for (int j = 0; j < col; j++) {
        res[i][j] = mat[i][j] + rhs[i][j];
      }
    }
    return res;
  }
};
template<typename T>
std::ostream & operator<<(std::ostream & s, const Matrix<T> & rhs) {
  if (rhs.getRows() == 0) {
    s << "[  ]";
    return s;
  }
  s << "[ ";
  for (int i = 0; i < rhs.getRows() - 1; i++) {
    s << rhs[i] << ",\n";
  }
  s << rhs[rhs.getRows() - 1] << " ]";
  return s;
}

template<typename T>
std::ostream & operator<<(std::ostream & s, const std::vector<T> & rhs) {
  s << "{";
  for (size_t i = 0; i < rhs.size() - 1; i++) {
    s << rhs[i] << ", ";
  }
  if (rhs.size() != 0) {
    s << rhs[rhs.size() - 1] << "}";
  }
  else {
    s << "}";
  }
  return s;
}

//YOUR CODE GOES HERE!

#endif
