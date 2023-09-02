#include "matrix_oop.h"

// Gets the number of rows in the matrix
int Matrix::get_rows() const noexcept { return rows_; }

// Gets the number of cols in the matrix
int Matrix::get_cols() const noexcept { return cols_; }

// Sets the number of rows in the matrix
void Matrix::set_rows(int new_rows) {
  if (new_rows < 1) {
    throw std::logic_error("Invalid size of matrix");
  }
  Matrix result(new_rows, cols_);
  int tmp_rows = rows_ < new_rows ? rows_ : new_rows;

  MatrixOverwrite(result, tmp_rows, cols_);
  *this = std::move(result);
}

// Sets the number of columns in the matrix
void Matrix::set_cols(int new_cols) {
  if (new_cols < 1) {
    throw std::logic_error("Invalid size of matrix");
  }
  Matrix result(rows_, new_cols);
  int tmp_cols = cols_ < new_cols ? cols_ : new_cols;

  MatrixOverwrite(result, rows_, tmp_cols);
  *this = std::move(result);
}

// Overwrites the current matrix
void Matrix::MatrixOverwrite(Matrix& result, int rows, int cols) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      result.matrix_[i][j] = matrix_[i][j];
    }
  }
}

// A basic constructor that initialises a matrix of some predefined dimension
Matrix::Matrix() : rows_(), cols_() {}

// Parametrized constructor with number of rows and columns
Matrix::Matrix(int rows, int cols) {
  if (rows < 1 || cols < 1) {
    throw std::logic_error("Invalid size of matrix");
  }
  rows_ = rows;
  cols_ = cols;
  CreateMatrix();
}

// Copy constructor
Matrix::Matrix(const Matrix& other) : rows_(other.rows_), cols_(other.cols_) {
  if (this != &other) {
    CopyMatrix(other);
  }
}

// Move constructor
Matrix::Matrix(Matrix&& other) {
  if (this != &other) {
    rows_ = std::exchange(other.rows_, 0);
    cols_ = std::exchange(other.cols_, 0);
    matrix_ = std::exchange(other.matrix_, nullptr);
  }
}

// Destructor
Matrix::~Matrix() { DeleteMatrix(); }

// Addition of two matrices
Matrix Matrix::operator+(const Matrix& other) {
  Matrix result(*this);
  result.SumMatrix(other);
  return result;
}

// Subtraction of one matrix from another
Matrix Matrix::operator-(const Matrix& other) {
  Matrix result(*this);
  result.SubMatrix(other);
  return result;
}

// Matrix multiplication
Matrix Matrix::operator*(const Matrix& other) {
  Matrix result(*this);
  result.MulMatrix(other);
  return result;
}

// Matrix multiplication by a number
Matrix Matrix::operator*(const double number) {
  Matrix result(*this);
  result.MulNumber(number);
  return result;
}

// Checks for matrices equality (EqMatrix)
bool Matrix::operator==(const Matrix& other) { return this->EqMatrix(other); }

// Copy assignment operator
Matrix& Matrix::operator=(const Matrix& other) {
  if (this == &other) {
    return *this;
  }

  DeleteMatrix();
  rows_ = other.rows_;
  cols_ = other.cols_;
  CopyMatrix(other);

  return *this;
}

// Move assignment operator
Matrix& Matrix::operator=(Matrix&& other) {
  if (this == &other) {
    return *this;
  }

  rows_ = std::exchange(other.rows_, 0);
  cols_ = std::exchange(other.cols_, 0);
  matrix_ = std::exchange(other.matrix_, nullptr);

  return *this;
}

// Addition assignment (SumMatrix)
Matrix Matrix::operator+=(const Matrix& other) {
  this->SumMatrix(other);
  return *this;
}
// Difference assignment (SubMatrix)
Matrix Matrix::operator-=(const Matrix& other) {
  this->SubMatrix(other);
  return *this;
}

// Multiplication assignment (MulMatrix)
Matrix Matrix::operator*=(const Matrix& other) {
  this->MulMatrix(other);
  return *this;
}

// Multiplication assignment (MulNumber)
Matrix Matrix::operator*=(const double number) {
  this->MulNumber(number);
  return *this;
}

// Indexation by matrix elements (row, column)
double& Matrix::operator()(int row, int col) {
  if (row < 0 || col < 0 || row >= rows_ || col >= cols_)
    throw std::logic_error("Index is outside the matrix");
  return matrix_[row][col];
}

// Checks matrices for equality with each other
bool Matrix::EqMatrix(const Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    return false;
  }
  double eps = 1.0e-7;
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (fabs(matrix_[i][j] - other.matrix_[i][j]) > eps) {
        return false;
      }
    }
  }
  return true;
}

// Adds the second matrix to the current one
void Matrix::SumMatrix(const Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::logic_error("Different matrix dimensions");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = matrix_[i][j] + other.matrix_[i][j];
    }
  }
}

// Subtracts another matrix from the current one
void Matrix::SubMatrix(const Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::logic_error("Different matrix dimensions");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = matrix_[i][j] - other.matrix_[i][j];
    }
  }
}

// Multiplies the current matrix by a number
void Matrix::MulNumber(const double num) const noexcept {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = matrix_[i][j] * num;
    }
  }
}

// Multiplies the current matrix by the second matrix
void Matrix::MulMatrix(const Matrix& other) {
  if (cols_ != other.rows_) {
    throw std::logic_error(
        "The number of columns of the first matrix is not equal to the number "
        "of rows of the second matrix");
  }
  Matrix result(rows_, other.cols_);

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      result(i, j) = 0;
      for (int n = 0; n < other.rows_; n++) {
        result.matrix_[i][j] += matrix_[i][n] * other.matrix_[n][j];
      }
    }
  }
  *this = std::move(result);
}
// Creates a new transposed matrix from the current one and returns it
Matrix Matrix::Transpose() const {
  Matrix result(cols_, rows_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      result.matrix_[i][j] = matrix_[j][i];
    }
  }
  return result;
}
// Calculates the algebraic addition matrix of the current one and returns it
Matrix Matrix::CalcComplements() const {
  if (rows_ != cols_) {
    throw std::length_error("The matrix is not square");
  }
  Matrix result(cols_, rows_);
  GetAddition(result);
  return result;
}

// Gets the algebraic addition of matrix
void Matrix::GetAddition(Matrix& result) const {
  if (rows_ > 1) {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        double determinant = 0;
        Matrix minor(this->rows_ - 1, this->cols_ - 1);
        GetMinor(minor, i, j);
        determinant = minor.Determinant();
        result.matrix_[i][j] = pow(-1, (i + j)) * determinant;
        minor.DeleteMatrix();
      }
    }
  }
}

// Calculates and returns the determinant of the current matrix
double Matrix::Determinant() const {
  if (rows_ != cols_) {
    throw std::length_error("The matrix is not square");
  }
  return GetDeterminant();
}

// Calculates determinant
double Matrix::GetDeterminant() const {
  double result = 0;
  if (rows_ == 1) {
    result = matrix_[0][0];
  } else {
    for (int j = 0; j < cols_; j++) {
      Matrix minor(this->get_rows() - 1, this->get_cols() - 1);
      GetMinor(minor, 0, j);
      result += matrix_[0][j] * pow(-1, j) * minor.GetDeterminant();
      minor.DeleteMatrix();
    }
  }
  return result;
}

// Calculates minor
void Matrix::GetMinor(Matrix& minor, int skip_row, int skip_col) const {
  int no_skip_row = 0, no_skip_col = 0;
  for (int i = 0; i < rows_; i++) {
    if (i == skip_row) continue;
    no_skip_col = 0;
    for (int j = 0; j < cols_; j++) {
      if (j == skip_col) continue;
      minor.matrix_[no_skip_row][no_skip_col] = matrix_[i][j];
      no_skip_col++;
    }
    no_skip_row++;
  }
}

// Calculates and returns the inverse matrix
Matrix Matrix::InverseMatrix() const {
  if (this->rows_ < 2) {
    throw std::logic_error("Rows can not be less than 2");
  }
  double eps = 1.0e-7;
  double determinant = Determinant();
  if (fabs(determinant) < eps) {
    throw std::logic_error("Matrix determinant is 0");
  }

  Matrix result(this->rows_, this->cols_);
  Matrix complements = this->CalcComplements();
  result = complements.Transpose();
  result.MulNumber(1 / determinant);
  return result;
}

// Allocs memory to matrix
void Matrix::CreateMatrix() {
  matrix_ = new double*[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_];
  }
}

// Copies the values from the given matrix 'other' into the current matrix.
void Matrix::CopyMatrix(const Matrix& other) {
  CreateMatrix();
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

// Deletes the dynamically allocated memory for the matrix
void Matrix::DeleteMatrix() {
  if (matrix_ != nullptr) {
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
    this->rows_ = 0;
    this->cols_ = 0;
    this->matrix_ = nullptr;
  }
}