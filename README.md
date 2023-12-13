# rSVD_Kamaneh_Raganato_Terrana


## Overview

The primary goal of this project is to implement the Random SVD (rSVD) algorithm, which addresses standard matrix decompositions. These decompositions include the pivoted QR factorization, eigenvalue decomposition, and singular value decomposition (SVD).
The project emphasizes the use of randomization as a powerful tool for low-rank matrix approximation. This approach not only enhances the efficiency of utilizing modern computational architectures but also enables effective handling of massive data sets.



## Introduction

The Randomized Singular Value Decomposition (rSVD) is a method for approximating the singular value decomposition of a matrix. This technique is particularly useful for large matrices, where traditional SVD methods may be computationally expensive. Randomized SVD provides an efficient and scalable approach to decomposing a matrix into its singular value, left singular vector, and right singular vector components.

### Mathematical Formulation
Given a matrix $A \in \mathbb{R}^{m \times n}$, the randomized SVD aims to approximate the singular value decomposition as follows:

$$ A \approx U \Sigma V^T $$

Where:
- $U$ is the left singular vector matrix of size $m \times k$,
- $\Sigma$ is the diagonal matrix of singular values of size $k \times k$,
- $V^T$ is the transposed right singular vector matrix of size $k \times n$.

The randomized SVD proceeds as follows:

1. **Randomized Sampling:** Multiply $A$ by a randomly generated matrix $\Omega \in \mathbb{R}^{n \times k} $, where $k$ is a user-specified parameter: $$Y = A \Omega $$

2. **QR Factorization:** Perform QR factorization on $Y$ to obtain $Y = QR$, where $Q$ is an $m \times k$ matrix with orthonormal columns.

3. **Approximate SVD:** Compute the SVD of the product $Q^TA$, denoted as $$Q^TAV = \tilde{U} \Sigma V^T$$ where $\tilde{U}$ is an $k \times k$ matrix, $\Sigma$ is a $k \times k$ diagonal matrix, and $V^T$ is a $k \times n$ matrix.
            $$B = \tilde{U} \Sigma V^T$$

4. **Approximation:** The approximation of the original matrix $A$ is given by $$A = Q \tilde{U} \Sigma V^T$$




## Installation

1. Clone the repository:

    ```bash
    git clone https://github.com/AMSC22-23/rSVD_Kamaneh_Raganato_Terrana.git
    ```

2. Navigate to the project directory:

    ```bash
    cd rSVD_Kamaneh_Raganato_Terrana
    ```

3. Create a build directory:

    ```bash
    mkdir build
    cd build
    ```

4. Run CMake to generate build files:

    ```bash
    cmake ..
    ```

5. Build the project:

    ```bash
    make
    ```

## Usage

To run the main program:

```bash
./rSVD
```

To run tests:

```bash
make test
```

To clean up generated files:

```bash
make clean-all
```
To enable profiling and generate a profile output:

```bash
make profile
```