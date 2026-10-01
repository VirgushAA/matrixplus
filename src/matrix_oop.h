#ifndef MATRIX_OOP_H
#define MATRIX_OOP_H

#include <cmath>
#include <exception>
#include <iostream>

class Matrix {
 private:
  int rows_, cols_;
  double** matrix_;

 public:
  Matrix();                        // Constructor
  Matrix(int rows, int cols);      // Parameterized constructor
  Matrix(const Matrix& other);  // Copy constructor
  Matrix(Matrix&& other);       // Move constructor
  ~Matrix();                       // Destructor

  // Operators overload
  Matrix& operator=(const Matrix& other);  // Assignment
  Matrix& operator=(Matrix&& other);       // Move Assignment
  bool operator==(const Matrix& other);

  Matrix& operator+=(const Matrix& other);
  Matrix operator+(const Matrix& other);
  Matrix& operator-=(const Matrix& other);
  Matrix operator-(const Matrix& other);
  Matrix& operator*=(const Matrix& other);
  Matrix operator*(const Matrix& other);  // this * other
  Matrix& operator*=(const double num);
  Matrix operator*(const double num);
  friend Matrix operator*(const double num, const Matrix& m);
  double& operator()(int row, int col);
  double operator()(int row, int col) const;

  // Accessors, mutators, allocators
  int GetRows();
  int GetCols();
  void SetRows(int rows);
  void SetCols(int cols);
  void Create_matrix(int r, int c);
  void Allocate();
  void ReAllocate(int new_rows, int new_cols);
  void Destroy();

  // Matrix operations
  Matrix Transpose();
  bool EqMatrix(const Matrix& other);
  void MulNumber(const double num);
  void SumMatrix(const Matrix& other);
  void SubMatrix(const Matrix& other);
  void MulMatrix(const Matrix& other);

  double Determinant();
  void minor(Matrix& A, Matrix& result, int p, int q);
  double det(Matrix& A, int n);

  Matrix CalcComplements();
  Matrix InverseMatrix();

  // Misc
  // void Dump();
  void Fill(double numbers[]);
};
Matrix operator*(const double num, const Matrix& m);  // num * m
#endif