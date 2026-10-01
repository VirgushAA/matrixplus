#include <gtest/gtest.h>

#include "../matrix_oop.h"

TEST(Constructors, Default) {
  int rows = 3, cols = 3;
  Matrix a;
  a.Create_matrix(rows, cols);
  EXPECT_EQ(a.GetRows(), rows);
  EXPECT_EQ(a.GetCols(), cols);
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetCols(); j++) {
      EXPECT_EQ(a(i, j), 0);
    }
  }
}
TEST(Constructors, ConstCallOP) {
  int rows = 3, cols = 3;
  const Matrix a(rows, cols);
  EXPECT_EQ(a(1, 1), 0);
  EXPECT_THROW(a(4, 1), std::out_of_range);
}
TEST(Constructors, Param) {
  int rows = 3, cols = 3;
  Matrix a(rows, cols);
  EXPECT_EQ(a.GetRows(), rows);
  EXPECT_EQ(a.GetCols(), cols);
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetCols(); j++) {
      EXPECT_EQ(a(i, j), 0);
    }
  }
}
TEST(Constructors, COPY) {
  int rows = 3, cols = 3;
  Matrix a;
  a.Create_matrix(rows, cols);
  Matrix b(a);
  EXPECT_EQ(b.GetRows(), rows);
  EXPECT_EQ(b.GetCols(), cols);
  for (int i = 0; i < b.GetRows(); i++) {
    for (int j = 0; j < b.GetCols(); j++) {
      EXPECT_EQ(b(i, j), 0);
    }
  }
}
TEST(Constructors, Move) {
  int rows = 3, cols = 3;
  Matrix a;
  a.Create_matrix(rows, cols);
  Matrix b(std::move(a));
  EXPECT_EQ(b.GetRows(), rows);
  EXPECT_EQ(b.GetCols(), cols);
  for (int i = 0; i < b.GetRows(); i++) {
    for (int j = 0; j < b.GetCols(); j++) {
      EXPECT_EQ(b(i, j), 0);
    }
  }
}
TEST(assignments, SetCols) {
  int rows = 3, cols = 3;
  Matrix a;
  a.Create_matrix(rows, cols);
  a.SetCols(5);
  a.SetRows(5);
  EXPECT_EQ(a.GetRows(), 5);
  EXPECT_EQ(a.GetCols(), 5);
}
TEST(misc, Fill) {
  int rows = 3, cols = 3;
  Matrix a(rows, cols);
  double mat[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  a.Fill(mat);
  int count = 1;
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetCols(); j++) {
      EXPECT_EQ(a(i, j), count);
      count++;
    }
  }
}
TEST(Overloads, Plus_Summ) {
  int rows = 3, cols = 3;
  Matrix a(rows, cols);
  double mat[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  a.Fill(mat);
  Matrix b(a);
  Matrix c = a + b;
  auto d = Matrix(1, 1);
  int count = 1;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      EXPECT_EQ(c(i, j), count * 2);
      count++;
    }
  }
  EXPECT_THROW(a + d, std::out_of_range);
}
TEST(Overloads, Eq) {
  int rows = 3, cols = 3;
  Matrix a(rows, cols);
  double mat[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  double mat2[] = {2, 2, 3, 4, 5, 6, 7, 8, 9};
  a.Fill(mat);
  Matrix b(a);
  auto aa = Matrix(rows, cols);
  aa.Fill(mat2);
  auto c = Matrix(1, 1);
  EXPECT_TRUE(a == b);
  EXPECT_FALSE(c == b);
  EXPECT_FALSE(a == aa);
}
TEST(Overloads, Mull_Mat) {
  int rows = 3, cols = 3;
  auto a = Matrix(rows, cols);
  double mat[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  double anss[] = {30, 36, 42, 66, 81, 96, 102, 126, 150};
  a.Fill(mat);
  auto b = Matrix(a);
  auto c = a * b;
  auto d = Matrix(1, 1);
  int count = 0;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      EXPECT_EQ(c(i, j), anss[count]);
      count++;
    }
  }
  EXPECT_THROW(a * d, std::out_of_range);
}
TEST(Overloads, Mull_Num) {
  const int rows = 3, cols = 3;
  auto a = Matrix(rows, cols);
  double mat[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  a.Fill(mat);
  auto mul = 1.23 * a;
  auto c = a * 5;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      EXPECT_EQ(c(i, j), a(i, j) * 5);
    }
  }
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      EXPECT_EQ(mul(i, j), a(i, j) * 1.23);
    }
  }
}
TEST(Overloads, Minus_Sub) {
  int rows = 3, cols = 3;
  auto a = Matrix(rows, cols);
  double mat[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  a.Fill(mat);
  auto b = Matrix(a);
  auto d = Matrix(1, 1);
  Matrix c = a - b;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      EXPECT_EQ(c(i, j), 0);
    }
  }
  EXPECT_THROW(a - d, std::out_of_range);
}
TEST(Overloads, Assignment) {
  int rows = 3, cols = 3;
  auto a = Matrix(rows, cols);
  double mat[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  a.Fill(mat);
  auto b = Matrix(1, 1);
  b = a;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      EXPECT_EQ(b(i, j), a(i, j));
    }
  }
  EXPECT_THROW(a(10, 10), std::out_of_range);
}
TEST(Mat_opts, Inverse) {
  int rows = 3, cols = 3;
  auto a = Matrix(rows, cols);
  auto b = Matrix(rows, cols);
  double mat1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  double mat2[] = {1000, 4, 7, 2, 5, 8, 3, 6, 9};
  a.Fill(mat2);
  b.Fill(mat1);
  auto d = Matrix(1, 3);
  auto answer = a.InverseMatrix();
  double ans[] = {
      0.001001001001001001,  -0.002002002002002002, 0.001001001001001001,
      -0.002002002002002002, -2.9959959959959961,   2.6646646646646648,
      0.001001001001001001,  1.997997997997998,     -1.6656656656656657};
  int count = 0;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      EXPECT_DOUBLE_EQ(answer(i, j), ans[count]);
      count++;
    }
  }
  auto f_calc = Matrix(1, 2);
  EXPECT_THROW(f_calc.CalcComplements(), std::out_of_range);
  auto f_dist = Matrix(1, 1);
  f_calc = f_dist.CalcComplements();
  EXPECT_EQ(f_calc(0, 0), 1);
  EXPECT_EQ(f_dist.Determinant(), 0);
  EXPECT_THROW(d.InverseMatrix(), std::out_of_range);
  EXPECT_THROW(b.InverseMatrix(), std::out_of_range);
}

int main() {
  ::testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}