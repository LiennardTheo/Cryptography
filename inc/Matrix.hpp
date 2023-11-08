#pragma once
#include <iostream>
#include <vector>
#include <stdexcept>
#include <math.h>

namespace mat {
    template<typename T, int rows, int cols>
    class Matrix {
        public:
            // Constructeur par défaut
            Matrix() {
                matrix_.resize(rows, std::vector<T>(cols));
            }

            Matrix (const std::initializer_list<std::initializer_list<T>>& list) {
                matrix_.resize(rows, std::vector<T>(cols));
                if (list.size() != rows || list.begin()->size() != cols) {
                    throw std::invalid_argument("Invalid initializer list size for assignment");
                }
                size_t row = 0;
                for (const auto& sublist : list) {
                    size_t col = 0;
                    for (const auto& value : sublist) {
                        matrix_[row][col] = value;
                        ++col;
                    }
                    ++row;
                }
            }

            // Constructeur avec initialisation
            Matrix(const std::vector<std::vector<T>>& matrix) {
                if (matrix.size() != rows || matrix[0].size() != cols) {
                    throw std::runtime_error("La taille de la matrice ne correspond pas à la taille spécifiée.");
                }
                matrix_ = matrix;
            }

            // Opérateur d'addition
            Matrix<T, rows, cols> operator+(const Matrix<T, rows, cols>& other) const {
                Matrix<T, rows, cols> result;
                for (int i = 0; i < rows; ++i) {
                    for (int j = 0; j < cols; ++j) {
                        result.matrix_[i][j] = matrix_[i][j] + other.matrix_[i][j];
                    }
                }
                return result;
            }

            //equality operator
            bool operator==(const Matrix<T, rows, cols>& other) const {
                for (int i = 0; i < rows; ++i) {
                    for (int j = 0; j < cols; ++j) {
                        if (matrix_[i][j] != other.matrix_[i][j]) {
                            return false;
                        }
                    }
                }
                return true;
            }

            // Opération d'addition et affectation
            void operator+=(const Matrix<T, rows, cols>& other) {
                for (int i = 0; i < rows; ++i) {
                    for (int j = 0; j < cols; ++j) {
                        matrix_[i][j] += other.matrix_[i][j];
                    }
                }
            }

            // Opérateur de soustraction
            Matrix<T, rows, cols> operator-(const Matrix<T, rows, cols>& other) const {
                Matrix<T, rows, cols> result;
                for (int i = 0; i < rows; ++i) {
                    for (int j = 0; j < cols; ++j) {
                        result.matrix_[i][j] = matrix_[i][j] - other.matrix_[i][j];
                    }
                }
                return result;
            }

            // Opération de soustraction et affectation
            void operator-=(const Matrix<T, rows, cols>& other) {
                for (int i = 0; i < rows; ++i) {
                    for (int j = 0; j < cols; ++j) {
                        matrix_[i][j] -= other.matrix_[i][j];
                    }
                }
            }

            // Opérateur de multiplication
            template<int otherCols>
            Matrix<T, rows, otherCols> operator*(const Matrix<T, cols, otherCols>& other) const {
                Matrix<T, rows, otherCols> result;
                for (int i = 0; i < rows; ++i) {
                    for (int j = 0; j < otherCols; ++j) {
                        for (int k = 0; k < cols; ++k) {
                            result.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
                        }
                    }
                }
                return result;
            }

            // Opérateur de multiplication et affectation
            template<int otherCols>
            void operator*=(const Matrix<T, cols, otherCols>& other) {
                Matrix<T, rows, otherCols> result;
                for (int i = 0; i < rows; ++i) {
                    for (int j = 0; j < otherCols; ++j) {
                        for (int k = 0; k < cols; ++k) {
                            result.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
                        }
                    }
                }
                matrix_ = result.matrix_;
            }

            // Opérateur de multiplication par un scalaire
            Matrix<T, rows, cols> operator*(const T& scalar) const {
                Matrix<T, rows, cols> result;
                for (int i = 0; i < rows; ++i) {
                    for (int j = 0; j < cols; ++j) {
                        result.matrix_[i][j] = matrix_[i][j] * scalar;
                    }
                }
                return result;
            }

            // Opérateur de multiplication par un scalaire et affectation
            void operator*=(const T& scalar) {
                for (int i = 0; i < rows; ++i) {
                    for (int j = 0; j < cols; ++j) {
                        matrix_[i][j] *= scalar;
                    }
                }
            }

            // Opérateur de division
            Matrix<T, rows, cols> operator/(const T& scalar) const {
                Matrix<T, rows, cols> result;
                for (int i = 0; i < rows; ++i) {
                    for (int j = 0; j < cols; ++j) {
                        result.matrix_[i][j] = matrix_[i][j] / scalar;
                    }
                }
                return result;
            }

            // Opérateur de division et affectation
            void operator/=(const T& scalar) {
                for (int i = 0; i < rows; ++i) {
                    for (int j = 0; j < cols; ++j) {
                        matrix_[i][j] /= scalar;
                    }
                }
            }

            // Méthode pour accéder aux éléments de la matrice

            T& operator()(int row, int col) {
                return matrix_[row][col];
            }

            const T& operator()(int row, int col) const {
                return matrix_[row][col];
            }

            // Méthode pour afficher la matrice
            void print() const {
                for (int i = 0; i < rows; ++i) {
                    for (int j = 0; j < cols; ++j) {
                        std::cout << matrix_[i][j] << " ";
                    }
                    std::cout << std::endl;
                }
            }

            void printB() const {
                for (int i = 0; i < rows; ++i) {
                    for (int j = 0; j < cols; ++j) {
                        printf("%d ", matrix_[i][j]);
                    }
                    std::cout << std::endl;
                }
            }

            // Méthode pour afficher la matrice avec std::cout
            friend std::ostream& operator<<(std::ostream& os, const Matrix<T, rows, cols>& matrix) {
                for (int i = 0; i < rows; ++i) {
                    for (int j = 0; j < cols; ++j) {
                        os << matrix.matrix_[i][j] << " ";
                    }
                    if (i != rows - 1)
                        os << std::endl;
                }
                return os;
            }

            // Méthode pour définir le contenu de la matrice
            void set(const std::vector<std::vector<T>>& matrix) {
                if (matrix.size() != rows || matrix[0].size() != cols) {
                    throw std::runtime_error("La taille de la matrice ne correspond pas à la taille spécifiée.");
                }
                matrix_ = matrix;
            }

            std::vector<std::vector<T>> matrix_;
    };
}