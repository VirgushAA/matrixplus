#include "matrix_oop.h"

// Constructors / Destructor
Matrix::Matrix() {}
// Parameterized constructor
Matrix::Matrix(int rows, int cols) {
  rows_ = rows;
  cols_ = cols;
  Allocate();
}
// Copy constructor
Matrix::Matrix(const Matrix& other) {
  rows_ = other.rows_;
  cols_ = other.cols_;
  Allocate();
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}
// Move constructor
Matrix::Matrix(Matrix&& other) {
  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = other.matrix_;
  other.rows_ = other.cols_ = 0;
  other.matrix_ = nullptr;
}
// Destructor
Matrix::~Matrix() { Destroy(); }
//

// Overloads
// Assignment operator overload
Matrix& Matrix::operator=(const Matrix& other) {
  if (this != &other) {
    Destroy();
    rows_ = other.rows_;
    cols_ = other.cols_;
    Allocate();
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        matrix_[i][j] = other.matrix_[i][j];
      }
    }
  }
  return *this;
}
// Move assigment operator
Matrix& Matrix::operator=(Matrix&& other) {
  if (this != &other) {
    Destroy();
    rows_ = other.rows_;
    cols_ = other.cols_;
    matrix_ = other.matrix_;
    other.rows_ = other.cols_ = 0;
    other.matrix_ = nullptr;
  }
  return *this;
}
Matrix& Matrix::operator+=(const Matrix& other) {
  SumMatrix(other);
  return *this;
}
Matrix Matrix::operator+(const Matrix& other) {
  Matrix tmp(*this);
  tmp += other;
  return tmp;
}
Matrix& Matrix::operator-=(const Matrix& other) {
  SubMatrix(other);
  return *this;
}
Matrix Matrix::operator-(const Matrix& other) {
  Matrix tmp(*this);
  tmp -= other;
  return tmp;
}
Matrix& Matrix::operator*=(const Matrix& other) {
  MulMatrix(other);
  return *this;
}
Matrix Matrix::operator*(const Matrix& other) {
  Matrix tmp(*this);
  tmp *= other;
  return tmp;
}
Matrix& Matrix::operator*=(const double num) {
  MulNumber(num);
  return *this;
}
Matrix Matrix::operator*(const double num) {
  Matrix tmp(*this);
  tmp *= num;
  return tmp;
}
Matrix operator*(const double num, const Matrix& m) {
  auto tmp = m;
  tmp *= num;
  return tmp;
}
bool Matrix::operator==(const Matrix& other) { return EqMatrix(other); }
double& Matrix::operator()(int row, int col) {
  if (row >= rows_ || col >= cols_) {
    throw std::out_of_range(
        "Incorrect input, matrices should have the same size");
  }
  return matrix_[row][col];
}
double Matrix::operator()(int row, int col) const {
  if (row >= rows_ || col >= cols_) {
    throw std::out_of_range(
        "Incorrect input, matrices should have the same size");
  }
  return matrix_[row][col];
}

// Assigning and freeing
void Matrix::SetRows(int rows) {
  ReAllocate(rows, cols_);
  Matrix::rows_ = rows;
}
void Matrix::SetCols(int cols) {
  ReAllocate(rows_, cols);
  Matrix::cols_ = cols;
}
int Matrix::GetRows() { return Matrix::rows_; }
int Matrix::GetCols() { return Matrix::cols_; }
void Matrix::Allocate() {
  matrix_ = new double*[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_]();
  }
}
void Matrix::ReAllocate(int new_rows, int new_cols) {
  Matrix tmp = std::move(*this);
  rows_ = new_rows;
  cols_ = new_cols;
  Allocate();
  if (tmp.rows_ <= new_rows) {
    new_rows = tmp.rows_;
  }
  if (tmp.cols_ <= new_cols) {
    new_cols = tmp.cols_;
  }
  for (int i = 0; i < new_rows; i++) {
    for (int j = 0; j < new_cols; j++) {
      matrix_[i][j] = tmp.matrix_[i][j];
    }
  }
}
void Matrix::Create_matrix(int r, int c) {
  rows_ = r;
  cols_ = c;
  Allocate();
}
void Matrix::Destroy() {
  if (matrix_ != nullptr) {
    for (int i = rows_ - 1; i >= 0; i--) {
      if (matrix_[i] != nullptr) {
        delete[] matrix_[i];
      }
    }
    delete[] matrix_;
  }
  cols_ = 0;
  rows_ = 0;
}

// Matrix operations
bool Matrix::EqMatrix(const Matrix& other) {
  bool ret = true;
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    ret = false;
  } else {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        if (labs(matrix_[i][j] - other.matrix_[i][j]) >= 1e-7) {
          ret = false;
        }
      }
    }
  }
  return ret;
}
Matrix Matrix::Transpose() {
  Matrix tmp{cols_, rows_};
  for (int i = 0; i < tmp.rows_; i++) {
    for (int j = 0; j < tmp.cols_; j++) {
      tmp.matrix_[i][j] = matrix_[j][i];
    }
  }
  return tmp;
}
void Matrix::SumMatrix(const Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::out_of_range(
        "Incorrect input, matrices should have the same size");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = matrix_[i][j] + other.matrix_[i][j];
    }
  }
}
void Matrix::SubMatrix(const Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::out_of_range(
        "Incorrect input, matrices should have the same size");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = matrix_[i][j] - other.matrix_[i][j];
    }
  }
}
void Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = matrix_[i][j] * num;
    }
  }
}
void Matrix::MulMatrix(const Matrix& other) {
  if (cols_ != other.rows_) {
    throw std::out_of_range(
        "Incorrect input, second matrix should have the same number of rows as "
        "first matrix number of collumns");
  }
  Matrix tmp(rows_, other.cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      for (int k = 0; k < other.rows_; k++) {
        tmp.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  (*this) = std::move(tmp);
}
void Matrix::minor(Matrix& A, Matrix& result, int p, int q) {
  int i = 0, j = 0;
  for (int row = 0; row < A.rows_; row++) {
    for (int col = 0; col < A.cols_; col++) {
      if (row != p && col != q) {
        result.matrix_[i][j++] = A.matrix_[row][col];
        if (j == A.rows_ - 1) {
          j = 0;
          i++;
        }
      }
    }
  }
  result.rows_ = A.rows_ - 1;
  result.cols_ = A.cols_ - 1;
}
double Matrix::det(Matrix& A, int n) {
  double D = 0, N = A.rows_;
  if (n == 2) {
    D = A.matrix_[0][0] * A.matrix_[1][1] - A.matrix_[0][1] * A.matrix_[1][0];
  } else {
    Matrix temp(N, N);
    int sign = 1;
    for (int f = 0; f < n; f++) {
      minor(A, temp, 0, f);
      D += sign * A.matrix_[0][f] * det(temp, n - 1);
      sign = -sign;
    }
    temp.rows_ = temp.cols_ = N;
  }
  return D;
}
double Matrix::Determinant() {
  double result = 0;
  if (rows_ != cols_) {
    throw std::out_of_range("Incorrect input, matrix is not square");
  } else if (rows_ == 1) {
    result = matrix_[0][0];
  } else {
    result = det(*this, rows_);
  }
  return result;
}
Matrix Matrix::CalcComplements() {
  Matrix result(rows_, cols_);
  if (rows_ != cols_) {
    throw std::out_of_range("Incorrect input, matrix is not square");
  } else {
    if (rows_ == 1) {
      result.matrix_[0][0] = 1.0;
    } else {
      Matrix tmp(rows_, cols_);
      for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
          minor(*this, tmp, i, j);
          result.matrix_[i][j] = tmp.Determinant();
          result.matrix_[i][j] *= pow(-1, (i + j));
        }
      }
      tmp.cols_ = tmp.rows_ = rows_;
    }
  }
  return result;
}
Matrix Matrix::InverseMatrix() {
  if (Determinant() == 0)
    throw std::out_of_range("Incorrect input, matrix determinant is 0");
  auto tmp = CalcComplements().Transpose();
  tmp.MulNumber((1 / Determinant()));
  return tmp;
}

// Misc
void Matrix::Fill(double numbers[]) {
  int k = 0;
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = numbers[k];
      k++;
    }
  }
}
// void Matrix::Dump() {
//   printf("matrix:\n");
//   for (int i = 0; i < rows_; i++) {
//     for (int j = 0; j < cols_; j++) {
//       printf("%lf  ", matrix_[i][j]);
//     }
//     printf("\n");
//   }
// }