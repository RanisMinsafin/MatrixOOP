#include <gtest/gtest.h>

#include "matrix_oop.h"

TEST(GettersTest, test_0) {
  Matrix A(2, 3);
  EXPECT_EQ(2, A.get_rows());
  EXPECT_EQ(3, A.get_cols());
}

TEST(GettersTest, test_1) {
  Matrix A(1, 3);
  EXPECT_EQ(1, A.get_rows());
  EXPECT_EQ(3, A.get_cols());
}

TEST(GettersTest, test_2) {
  Matrix A(2, 4);
  EXPECT_EQ(2, A.get_rows());
  EXPECT_EQ(4, A.get_cols());
}

TEST(SettersTest, test_0) {
  Matrix A(2, 2);
  A.set_rows(3);
  A.set_cols(4);
  EXPECT_EQ(3, A.get_rows());
  EXPECT_EQ(4, A.get_cols());
}

TEST(DefaultConstructor, test_0) {
  Matrix A;
  EXPECT_EQ(0, A.get_rows());
  EXPECT_EQ(0, A.get_cols());
}

TEST(DefaultConstructor, test_1) {
  EXPECT_ANY_THROW({
    Matrix A;
    A(-1, -1) = 0;
  });
}

TEST(DefaultConstructor, test_2) {
  EXPECT_ANY_THROW({
    Matrix A;
    A(0, 5) = 0;
  });
}

TEST(ParamConstructor, test_0) {
  Matrix A(4, 3);
  EXPECT_EQ(4, A.get_rows());
  EXPECT_EQ(3, A.get_cols());
}

TEST(ParamConstructor, test_1) {
  EXPECT_ANY_THROW({ Matrix A(0, 3); });
}

TEST(ParamConstructor, test_2) {
  EXPECT_ANY_THROW({ Matrix A(-1, 3); });
}

TEST(CopyConstructor, test_0) {
  Matrix A(2, 2);
  Matrix B(A);
  EXPECT_EQ(true, B.EqMatrix(A));
}

TEST(CopyConstructor, test_1) {
  Matrix A(2, 1);
  Matrix B(A);
  EXPECT_EQ(true, B.EqMatrix(A));
}

TEST(CopyConstructor, test_2) {
  Matrix A(3, 4);
  Matrix B(A);
  EXPECT_EQ(true, B.EqMatrix(A));
}

TEST(MoveConstructor, test_0) {
  Matrix A(2, 2);
  Matrix B(std::move(A));

  EXPECT_EQ(2, B.get_rows());
  EXPECT_EQ(2, B.get_cols());
  EXPECT_EQ(0, A.get_rows());
}

TEST(Addition, test_0) {
  double matrix1[2][2] = {{1, 1}, {1, 1}};
  double matrix2[2][2] = {{6, 6}, {6, 6}};
  double result[2][2] = {{7, 7}, {7, 7}};

  Matrix mat1 = Matrix(2, 2);
  for (int i = 0; i < mat1.get_rows(); i++) {
    for (int j = 0; j < mat1.get_cols(); j++) {
      mat1(i, j) = matrix1[i][j];
    }
  }

  Matrix mat2 = Matrix(2, 2);
  for (int i = 0; i < mat2.get_rows(); i++) {
    for (int j = 0; j < mat2.get_cols(); j++) {
      mat2(i, j) = matrix2[i][j];
    }
  }

  mat1.SumMatrix(mat2);

  for (int i = 0; i < mat1.get_rows(); i++) {
    for (int j = 0; j < mat1.get_cols(); j++) {
      EXPECT_EQ(mat1(i, j), result[i][j]);
    }
  }
}

TEST(Addition, test_1) {
  double matrix[2][2] = {{2, 2}, {3, 3}};

  Matrix mat1 = Matrix(2, 2);
  for (int i = 0; i < mat1.get_rows(); i++) {
    for (int j = 0; j < mat1.get_cols(); j++) {
      mat1(i, j) = matrix[i][j];
    }
  }

  Matrix mat2 = Matrix();

  EXPECT_THROW(mat1.SumMatrix(mat2), std::logic_error);
}

TEST(Addition, test_2) {
  double matrix1[2][3] = {{1, 2, 3}, {4, 5, 6}};
  double matrix2[3][2] = {{7, 8}, {9, 10}, {11, 12}};

  Matrix mat1 = Matrix(2, 3);
  for (int i = 0; i < mat1.get_rows(); i++) {
    for (int j = 0; j < mat1.get_cols(); j++) {
      mat1(i, j) = matrix1[i][j];
    }
  }

  Matrix mat2 = Matrix(3, 2);
  for (int i = 0; i < mat2.get_rows(); i++) {
    for (int j = 0; j < mat2.get_cols(); j++) {
      mat2(i, j) = matrix2[i][j];
    }
  }

  EXPECT_THROW(mat1.SumMatrix(mat2), std::logic_error);
}

TEST(Subtraction, test_0) {
  double matrix1[2][2] = {{11, 2}, {3, 4}};
  double matrix2[2][2] = {{2, 1}, {1, 2}};
  double expected[2][2] = {{9, 1}, {2, 2}};

  Matrix mat1 = Matrix(2, 2);
  for (int i = 0; i < mat1.get_rows(); i++) {
    for (int j = 0; j < mat1.get_cols(); j++) {
      mat1(i, j) = matrix1[i][j];
    }
  }

  Matrix mat2 = Matrix(2, 2);
  for (int i = 0; i < mat2.get_rows(); i++) {
    for (int j = 0; j < mat2.get_cols(); j++) {
      mat2(i, j) = matrix2[i][j];
    }
  }

  mat1.SubMatrix(mat2);

  for (int i = 0; i < mat1.get_rows(); i++) {
    for (int j = 0; j < mat1.get_cols(); j++) {
      EXPECT_EQ(mat1(i, j), expected[i][j]);
    }
  }
}

TEST(Subtraction, test_1) {
  double matrix[2][2] = {{2, 2}, {3, 3}};

  Matrix mat1 = Matrix(2, 2);
  for (int i = 0; i < mat1.get_rows(); i++) {
    for (int j = 0; j < mat1.get_cols(); j++) {
      mat1(i, j) = matrix[i][j];
    }
  }

  Matrix mat2 = Matrix();

  EXPECT_THROW(mat1.SubMatrix(mat2), std::logic_error);
}

TEST(Subtraction, test_2) {
  double matrix1[2][3] = {{1, 2, 3}, {4, 5, 6}};
  double matrix2[3][2] = {{7, 8}, {9, 10}, {11, 12}};

  Matrix mat1 = Matrix(2, 3);
  for (int i = 0; i < mat1.get_rows(); i++) {
    for (int j = 0; j < mat1.get_cols(); j++) {
      mat1(i, j) = matrix1[i][j];
    }
  }

  Matrix mat2 = Matrix(3, 2);
  for (int i = 0; i < mat2.get_rows(); i++) {
    for (int j = 0; j < mat2.get_cols(); j++) {
      mat2(i, j) = matrix2[i][j];
    }
  }

  EXPECT_THROW(mat1.SubMatrix(mat2), std::logic_error);
}

TEST(MatrixMultiplication, test_0) {
  double matrix1[2][2] = {{2, 2}, {3, 3}};
  double matrix2[2][2] = {{2, 1}, {1, 2}};
  double expected[2][2] = {{6, 6}, {9, 9}};

  Matrix mat1 = Matrix(2, 2);
  for (int i = 0; i < mat1.get_rows(); i++) {
    for (int j = 0; j < mat1.get_cols(); j++) {
      mat1(i, j) = matrix1[i][j];
    }
  }

  Matrix mat2 = Matrix(2, 2);
  for (int i = 0; i < mat2.get_rows(); i++) {
    for (int j = 0; j < mat2.get_cols(); j++) {
      mat2(i, j) = matrix2[i][j];
    }
  }

  mat1.MulMatrix(mat2);

  for (int i = 0; i < mat1.get_rows(); i++) {
    for (int j = 0; j < mat1.get_cols(); j++) {
      EXPECT_EQ(mat1(i, j), expected[i][j]);
    }
  }
}

TEST(MatrixMultiplication, test_1) {
  double matrix[2][2] = {{2, 2}, {3, 3}};

  Matrix mat1 = Matrix(2, 2);
  for (int i = 0; i < mat1.get_rows(); i++) {
    for (int j = 0; j < mat1.get_cols(); j++) {
      mat1(i, j) = matrix[i][j];
    }
  }

  Matrix mat2 = Matrix();

  EXPECT_THROW(mat1.MulMatrix(mat2), std::logic_error);
}

TEST(MultiplicationByNumber, test_0) {
  double matrix[2][2] = {{1, 2}, {3, 4}};
  double number = 0.5;
  double expected[2][2] = {{0.5, 1}, {1.5, 2}};

  Matrix mat = Matrix(2, 2);
  for (int i = 0; i < mat.get_rows(); i++) {
    for (int j = 0; j < mat.get_cols(); j++) {
      mat(i, j) = matrix[i][j];
    }
  }

  mat.MulNumber(number);

  for (int i = 0; i < mat.get_rows(); i++) {
    for (int j = 0; j < mat.get_cols(); j++) {
      EXPECT_EQ(mat(i, j), expected[i][j]);
    }
  }
}

TEST(EqualityOperator, test_0) {
  double matrix1[2][2] = {{1, 2}, {3, 4}};
  double matrix2[2][2] = {{1, 2}, {3, 4}};

  Matrix mat1 = Matrix(2, 2);
  for (int i = 0; i < mat1.get_rows(); i++) {
    for (int j = 0; j < mat1.get_cols(); j++) {
      mat1(i, j) = matrix1[i][j];
    }
  }

  Matrix mat2 = Matrix(2, 2);
  for (int i = 0; i < mat2.get_rows(); i++) {
    for (int j = 0; j < mat2.get_cols(); j++) {
      mat2(i, j) = matrix2[i][j];
    }
  }

  EXPECT_TRUE(mat1.EqMatrix(mat2));
  EXPECT_TRUE(mat2.EqMatrix(mat1));
}

TEST(AssignmentOperator, test_0) {
  Matrix A(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;

  Matrix B = A;

  EXPECT_TRUE(A == B);
}

TEST(AdditionAssignmentOperator, test_0) {
  Matrix A(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;

  Matrix B(2, 2);
  B(0, 0) = 5;
  B(0, 1) = 6;
  B(1, 0) = 7;
  B(1, 1) = 8;

  A += B;

  EXPECT_EQ(6, A(0, 0));
  EXPECT_EQ(8, A(0, 1));
  EXPECT_EQ(10, A(1, 0));
  EXPECT_EQ(12, A(1, 1));
}

TEST(SubtractionAssignmentOperator, test_0) {
  Matrix A(2, 2);
  A(0, 0) = 5;
  A(0, 1) = 6;
  A(1, 0) = 7;
  A(1, 1) = 8;

  Matrix B(2, 2);
  B(0, 0) = 1;
  B(0, 1) = 2;
  B(1, 0) = 3;
  B(1, 1) = 4;

  A -= B;

  EXPECT_EQ(4, A(0, 0));
  EXPECT_EQ(4, A(0, 1));
  EXPECT_EQ(4, A(1, 0));
  EXPECT_EQ(4, A(1, 1));
}

TEST(MultiplicationAssignmentWithNumberOperator, test_0) {
  Matrix A(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;

  double num = 2.5;

  A *= num;

  EXPECT_EQ(2.5, A(0, 0));
  EXPECT_EQ(5.0, A(0, 1));
  EXPECT_EQ(7.5, A(1, 0));
  EXPECT_EQ(10.0, A(1, 1));
}

TEST(IndexingOperator, test_0) {
  Matrix A(2, 2);
  A(0, 0) = 10;
  A(0, 1) = 20;
  A(1, 0) = 3;
  A(1, 1) = 4;

  EXPECT_EQ(10, A(0, 0));
  EXPECT_EQ(4, A(1, 1));
}

TEST(Transpose, test_0) {
  double matrix[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  double expected[3][3] = {{1, 4, 7}, {2, 5, 8}, {3, 6, 9}};

  Matrix mat = Matrix(3, 3);
  for (int i = 0; i < mat.get_rows(); i++) {
    for (int j = 0; j < mat.get_cols(); j++) {
      mat(i, j) = matrix[i][j];
    }
  }

  Matrix transposed = mat.Transpose();

  for (int i = 0; i < transposed.get_rows(); i++) {
    for (int j = 0; j < transposed.get_cols(); j++) {
      EXPECT_EQ(transposed(i, j), expected[i][j]);
    }
  }
}

TEST(Determinant, test_0) {
  Matrix A(3, 3);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(0, 2) = 3;
  A(1, 0) = 4;
  A(1, 1) = 5;
  A(1, 2) = 6;
  A(2, 0) = 7;
  A(2, 1) = 8;
  A(2, 2) = 9;

  double det = A.Determinant();

  EXPECT_EQ(0, det);
}

TEST(InverseMatrix, test_0) {
  Matrix A(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;

  Matrix B = A.InverseMatrix();

  EXPECT_NEAR(-2, B(0, 0), 1e-6);
  EXPECT_NEAR(1, B(0, 1), 1e-6);
  EXPECT_NEAR(1.5, B(1, 0), 1e-6);
  EXPECT_NEAR(-0.5, B(1, 1), 1e-6);
}

TEST(OperatorPlusEqual, test_0) {
  double matrix1[2][2] = {{1, 2}, {3, 4}};
  double matrix2[2][2] = {{2, 3}, {4, 5}};
  double result[2][2] = {{3, 5}, {7, 9}};

  Matrix matrixA = Matrix(2, 2);
  for (int i = 0; i < matrixA.get_rows(); i++) {
    for (int j = 0; j < matrixA.get_cols(); j++) {
      matrixA(i, j) = matrix1[i][j];
    }
  }

  Matrix matrixB = Matrix(2, 2);
  for (int i = 0; i < matrixB.get_rows(); i++) {
    for (int j = 0; j < matrixB.get_cols(); j++) {
      matrixB(i, j) = matrix2[i][j];
    }
  }

  matrixA += matrixB;

  EXPECT_EQ(matrixA.get_rows(), 2);
  EXPECT_EQ(matrixA.get_cols(), 2);

  for (int i = 0; i < matrixA.get_rows(); i++) {
    for (int j = 0; j < matrixA.get_cols(); j++) {
      EXPECT_EQ(matrixA(i, j), result[i][j]);
    }
  }
}

TEST(OperatorPlusEqual, test_1) {
  double matrix1[2][2] = {{1, 2}, {3, 4}};
  double result[2][2] = {{2, 4}, {6, 8}};

  Matrix matrixA = Matrix(2, 2);
  for (int i = 0; i < matrixA.get_rows(); i++) {
    for (int j = 0; j < matrixA.get_cols(); j++) {
      matrixA(i, j) = matrix1[i][j];
    }
  }

  matrixA += matrixA;

  EXPECT_EQ(matrixA.get_rows(), 2);
  EXPECT_EQ(matrixA.get_cols(), 2);

  for (int i = 0; i < matrixA.get_rows(); i++) {
    for (int j = 0; j < matrixA.get_cols(); j++) {
      EXPECT_EQ(matrixA(i, j), result[i][j]);
    }
  }
}

TEST(OperatorPlusEqual, test_2) {
  double matrix1[2][2] = {{1, 2}, {3, 4}};
  double matrix2[3][3] = {{2, 3, 4}, {5, 6, 7}, {8, 9, 10}};

  Matrix matrixA = Matrix(2, 2);
  for (int i = 0; i < matrixA.get_rows(); i++) {
    for (int j = 0; j < matrixA.get_cols(); j++) {
      matrixA(i, j) = matrix1[i][j];
    }
  }

  Matrix matrixB = Matrix(3, 3);
  for (int i = 0; i < matrixB.get_rows(); i++) {
    for (int j = 0; j < matrixB.get_cols(); j++) {
      matrixB(i, j) = matrix2[i][j];
    }
  }

  EXPECT_THROW({ matrixA += matrixB; }, std::logic_error);

  EXPECT_EQ(matrixA.get_rows(), 2);
  EXPECT_EQ(matrixA.get_cols(), 2);

  for (int i = 0; i < matrixA.get_rows(); i++) {
    for (int j = 0; j < matrixA.get_cols(); j++) {
      EXPECT_EQ(matrixA(i, j), matrix1[i][j]);
    }
  }
}

TEST(OperatorMinusEqual, test_0) {
  double matrix1[2][2] = {{1, 2}, {3, 4}};
  double matrix2[2][2] = {{2, 3}, {4, 5}};
  double result[2][2] = {{-1, -1}, {-1, -1}};

  Matrix matrixA = Matrix(2, 2);
  for (int i = 0; i < matrixA.get_rows(); i++) {
    for (int j = 0; j < matrixA.get_cols(); j++) {
      matrixA(i, j) = matrix1[i][j];
    }
  }

  Matrix matrixB = Matrix(2, 2);
  for (int i = 0; i < matrixB.get_rows(); i++) {
    for (int j = 0; j < matrixB.get_cols(); j++) {
      matrixB(i, j) = matrix2[i][j];
    }
  }

  matrixA -= matrixB;

  EXPECT_EQ(matrixA.get_rows(), 2);
  EXPECT_EQ(matrixA.get_cols(), 2);

  for (int i = 0; i < matrixA.get_rows(); i++) {
    for (int j = 0; j < matrixA.get_cols(); j++) {
      EXPECT_EQ(matrixA(i, j), result[i][j]);
    }
  }
}

TEST(OperatorMinusEqual, test_1) {
  double matrix1[2][2] = {{1, 2}, {3, 4}};
  double result[2][2] = {{0, 0}, {0, 0}};

  Matrix matrixA = Matrix(2, 2);
  for (int i = 0; i < matrixA.get_rows(); i++) {
    for (int j = 0; j < matrixA.get_cols(); j++) {
      matrixA(i, j) = matrix1[i][j];
    }
  }

  matrixA -= matrixA;

  EXPECT_EQ(matrixA.get_rows(), 2);
  EXPECT_EQ(matrixA.get_cols(), 2);

  for (int i = 0; i < matrixA.get_rows(); i++) {
    for (int j = 0; j < matrixA.get_cols(); j++) {
      EXPECT_EQ(matrixA(i, j), result[i][j]);
    }
  }
}

TEST(OperatorMinusEqual, test_2) {
  double matrix1[2][2] = {{1, 2}, {3, 4}};
  double matrix2[3][3] = {{2, 3, 4}, {5, 6, 7}, {8, 9, 10}};

  Matrix matrixA = Matrix(2, 2);
  for (int i = 0; i < matrixA.get_rows(); i++) {
    for (int j = 0; j < matrixA.get_cols(); j++) {
      matrixA(i, j) = matrix1[i][j];
    }
  }

  Matrix matrixB = Matrix(3, 3);
  for (int i = 0; i < matrixB.get_rows(); i++) {
    for (int j = 0; j < matrixB.get_cols(); j++) {
      matrixB(i, j) = matrix2[i][j];
    }
  }

  EXPECT_THROW({ matrixA -= matrixB; }, std::logic_error);
  EXPECT_EQ(matrixA.get_rows(), 2);
  EXPECT_EQ(matrixA.get_cols(), 2);

  for (int i = 0; i < matrixA.get_rows(); i++) {
    for (int j = 0; j < matrixA.get_cols(); j++) {
      EXPECT_EQ(matrixA(i, j), matrix1[i][j]);
    }
  }
}

TEST(MultiplyEqual, test_0) {
  double matrix1[2][2] = {{2, 3}, {4, 5}};
  double matrix2[2][2] = {{1, 2}, {3, 4}};
  double expected[2][2] = {{11, 16}, {19, 28}};

  Matrix mat1 = Matrix(2, 2);
  for (int i = 0; i < mat1.get_rows(); i++) {
    for (int j = 0; j < mat1.get_cols(); j++) {
      mat1(i, j) = matrix1[i][j];
    }
  }

  Matrix mat2 = Matrix(2, 2);
  for (int i = 0; i < mat2.get_rows(); i++) {
    for (int j = 0; j < mat2.get_cols(); j++) {
      mat2(i, j) = matrix2[i][j];
    }
  }

  Matrix result = mat1 * mat2;

  for (int i = 0; i < result.get_rows(); i++) {
    for (int j = 0; j < result.get_cols(); j++) {
      EXPECT_EQ(result(i, j), expected[i][j]);
    }
  }
}

TEST(MultiplyEqualSelfAssignment, test_0) {
  double matrix1[2][2] = {{1, 2}, {3, 4}};
  double result[2][2] = {{7, 10}, {15, 22}};

  Matrix matrixA = Matrix(2, 2);
  for (int i = 0; i < matrixA.get_rows(); i++) {
    for (int j = 0; j < matrixA.get_cols(); j++) {
      matrixA(i, j) = matrix1[i][j];
    }
  }

  matrixA *= matrixA;

  EXPECT_EQ(matrixA.get_rows(), 2);
  EXPECT_EQ(matrixA.get_cols(), 2);

  for (int i = 0; i < matrixA.get_rows(); i++) {
    for (int j = 0; j < matrixA.get_cols(); j++) {
      EXPECT_EQ(matrixA(i, j), result[i][j]);
    }
  }
}

TEST(MultiplyEqualDifferentSizes, test_0) {
  double matrix1[2][2] = {{1, 2}, {3, 4}};
  double matrix2[3][3] = {{2, 3, 4}, {5, 6, 7}, {8, 9, 10}};

  Matrix matrixA = Matrix(2, 2);
  for (int i = 0; i < matrixA.get_rows(); i++) {
    for (int j = 0; j < matrixA.get_cols(); j++) {
      matrixA(i, j) = matrix1[i][j];
    }
  }

  Matrix matrixB = Matrix(3, 3);
  for (int i = 0; i < matrixB.get_rows(); i++) {
    for (int j = 0; j < matrixB.get_cols(); j++) {
      matrixB(i, j) = matrix2[i][j];
    }
  }

  EXPECT_THROW({ matrixA *= matrixB; }, std::logic_error);

  EXPECT_EQ(matrixA.get_rows(), 2);
  EXPECT_EQ(matrixA.get_cols(), 2);

  for (int i = 0; i < matrixA.get_rows(); i++) {
    for (int j = 0; j < matrixA.get_cols(); j++) {
      EXPECT_EQ(matrixA(i, j), matrix1[i][j]);
    }
  }
}

TEST(MultiplyEqualNumber, test_0) {
  double matrix[2][2] = {{1, 2}, {3, 4}};
  double number = 2;
  double result[2][2] = {{2, 4}, {6, 8}};

  Matrix matrixA = Matrix(2, 2);
  for (int i = 0; i < matrixA.get_rows(); i++) {
    for (int j = 0; j < matrixA.get_cols(); j++) {
      matrixA(i, j) = matrix[i][j];
    }
  }

  matrixA *= number;

  EXPECT_EQ(matrixA.get_rows(), 2);
  EXPECT_EQ(matrixA.get_cols(), 2);

  for (int i = 0; i < matrixA.get_rows(); i++) {
    for (int j = 0; j < matrixA.get_cols(); j++) {
      EXPECT_EQ(matrixA(i, j), result[i][j]);
    }
  }
}

TEST(MultiplyEqualNumber, test_1) {
  double matrix[2][2] = {{1, 2}, {3, 4}};
  double number = 0;
  double result[2][2] = {{0, 0}, {0, 0}};

  Matrix matrixA = Matrix(2, 2);
  for (int i = 0; i < matrixA.get_rows(); i++) {
    for (int j = 0; j < matrixA.get_cols(); j++) {
      matrixA(i, j) = matrix[i][j];
    }
  }

  matrixA *= number;

  EXPECT_EQ(matrixA.get_rows(), 2);
  EXPECT_EQ(matrixA.get_cols(), 2);

  for (int i = 0; i < matrixA.get_rows(); i++) {
    for (int j = 0; j < matrixA.get_cols(); j++) {
      EXPECT_EQ(matrixA(i, j), result[i][j]);
    }
  }
}

TEST(MultiplyEqualNumber, test_2) {
  double matrix[2][2] = {{1, 2}, {3, 4}};
  double number = -1;
  double result[2][2] = {{-1, -2}, {-3, -4}};

  Matrix matrixA = Matrix(2, 2);
  for (int i = 0; i < matrixA.get_rows(); i++) {
    for (int j = 0; j < matrixA.get_cols(); j++) {
      matrixA(i, j) = matrix[i][j];
    }
  }

  matrixA *= number;

  EXPECT_EQ(matrixA.get_rows(), 2);
  EXPECT_EQ(matrixA.get_cols(), 2);

  for (int i = 0; i < matrixA.get_rows(); i++) {
    for (int j = 0; j < matrixA.get_cols(); j++) {
      EXPECT_EQ(matrixA(i, j), result[i][j]);
    }
  }
}

int main() {
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}