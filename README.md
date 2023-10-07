# 2D Matrix Tiling Multiplication

This repository contains an optimized program that performs matrix multiplication using a tiling optimization technique. Tiling is known to enhance cache utilization by breaking larger matrices into smaller submatrices or tiles, allowing for efficient multiplication.

## Table of Contents
- [Features](#features)
- [Getting Started](#getting-started)
    - [Prerequisites](#prerequisites)
    - [Compilation](#compilation)
    - [Usage](#usage)
    - [Testing](#testing)
- [Author](#author)


## Features
- Efficient matrix multiplication with tiling optimization.
- Compatibility check for matrix dimensions before multiplication.
- Unit testing to compare tiled results against a baseline non-tiled multiplication.
- Interactive CLI for users to input matrix dimensions, tile size, and matrix values.

## Getting Started

### Prerequisites

Ensure you have a C++ compiler installed on your machine. This code has been written in C++ and requires a compiler supporting C++11 or later.

### Compilation

##### Clone the repository to your local machine:

```bash
git clone https://github.com/[YourUsername]/MatrixTilingMultiplication.git
cd MatrixTilingMultiplication
```

##### Compile the program using:
```
g++ -g ./src/tile_matmul.cpp -std=gnu++2a -Wall -o main
```

### Usage

##### Run the compiled program:
```
./main
```
######  You'll be prompted to:

- Enter the dimensions of matrix A.
- Enter the dimensions of matrix B.
- Input the desired tile size.
- Provide the matrix values for A and B.

### Testing

After the multiplication, the program runs a unit test to compare the results from the tiled multiplication against a baseline matrix multiplication. Any discrepancies will be reported, ensuring the accuracy of the optimization.

## Author

- Me
