# Matrix Library (Matrix+)

Matrix is a C++ library that provides matrix manipulation functionalities. It allows you to create, manipulate, and perform various operations on matrices. The library is implemented in accordance with the C++17 standard and follows the Google C++ style guide.

## Table of Contents

- [Installation](#installation)
- [Usage](#usage)
- [Matrix Operations](#matrix-operations)
- [Makefile](#makefile)

## Installation

To use the Matrix library, follow these steps:

1. Clone the repository to your local machine:
   ```bash
   git clone <repository_url>
   ```

2. Navigate to the `src` folder:
   ```bash
   cd Matrix/src
   ```

3. Build the library using the provided Makefile:
   ```bash
   make
   ```

This will generate a static library file named `matrix_oop.a`.

## Usage

To utilize the Matrix library in your C++ project, include the `matrix_oop.h` header file and link with the `matrix_oop.a` library.

Here's an example of how to create and manipulate matrices:

```cpp
#include "matrix_oop.h"

#include "matrix_oop.h"
#include <iostream>

int main() {
    // Create a 3x3 matrix
    Matrix matrix(3, 3);

    // Fill the matrix with values (all elements become 1.0)
    matrix.MulNumber(1.0);

    // Print the matrix
    for (int i = 0; i < matrix.get_rows(); i++) {
        for (int j = 0; j < matrix.get_cols(); j++) {
            std::cout << matrix(i, j) << " ";
        }
        std::cout << std::endl;
    }

    // Create another 3x3 matrix and fill it with values (all elements become 2.0)
    Matrix anotherMatrix(3, 3);
    anotherMatrix.MulNumber(2.0);

    // Perform matrix addition
    Matrix result = matrix + anotherMatrix;

    // Print the result
    for (int i = 0; i < result.get_rows(); i++) {
        for (int j = 0; j < result.get_cols(); j++) {
            std::cout << result(i, j) << " ";
        }
        std::cout << std::endl;
    }

    // Access and mutate matrix elements
    matrix(1, 1) = 5.0;  // Set the element at row 1, column 1 to 5.0
    double element = matrix(1, 1);  // Get the element at row 1, column 1

    // Get the number of rows and columns
    int rows = matrix.get_rows();
    int cols = matrix.get_cols();

    return 0;
}

```

## Matrix Operations

The Matrix library provides a variety of matrix operations, including:

- Addition
- Subtraction
- Multiplication
- Matrix-Scalar multiplication
- Transposition
- Determinant calculation
- Matrix inversion

These operations can be performed using operator overloading and member functions, as demonstrated in the usage example.

## Makefile

The provided Makefile includes the following targets:

- `all`: Builds the Matrix library and tests.
- `clean`: Cleans the generated object files and executables.
- `test`: Builds and runs the unit tests using Google Test.

To use a target, run `make <target_name>` in the `src` directory.