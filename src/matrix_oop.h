#ifndef SRC_MATRIX_OOP_H_
#define SRC_MATRIX_OOP_H_

#include <cmath>
#include <iostream>
#include <utility>

class Matrix {
 public:
  // Accessors (or Getters)
  int get_rows() const noexcept;
  int get_cols() const noexcept;

  // Mutators (or Setters)
  void set_rows(int new_rows);
  void set_cols(int new_cols);

  // Constructors
  Matrix();
  Matrix(int rows, int cols);
  Matrix(const Matrix& other);
  Matrix(Matrix&& other);

  // Destructor
  ~Matrix();

  // Operators overloading
  Matrix operator+(const Matrix& other);
  Matrix operator-(const Matrix& other);
  Matrix operator*(const Matrix& other);
  Matrix operator*(const double number);
  bool operator==(const Matrix& other);
  Matrix& operator=(const Matrix& other);
  Matrix& operator=(Matrix&& other);
  Matrix operator+=(const Matrix& other);
  Matrix operator-=(const Matrix& other);
  Matrix operator*=(const Matrix& other);
  Matrix operator*=(const double number);
  double& operator()(int row, int col);

  // Matrix operations
  bool EqMatrix(const Matrix& other);
  void SumMatrix(const Matrix& other);
  void SubMatrix(const Matrix& other);
  void MulNumber(const double num) const noexcept;
  void MulMatrix(const Matrix& other);
  Matrix Transpose() const;
  Matrix CalcComplements() const;
  double Determinant() const;
  Matrix InverseMatrix() const;

 private:
  int rows_;
  int cols_;
  double** matrix_{};

  void MatrixOverwrite(Matrix& result, int rows, int cols);
  void CreateMatrix();
  void CopyMatrix(const Matrix& other);
  void DeleteMatrix();
  double GetDeterminant() const;
  void GetMinor(Matrix& minor, int skip_row, int skip_col) const;
  void GetAddition(Matrix& result) const;
};

#endif  // SRC_MATRIX_OOP_H_