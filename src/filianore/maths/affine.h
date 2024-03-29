#ifndef _AFFINE_TRANSFORM_H
#define _AFFINE_TRANSFORM_H

#include "geometry.h"
#include <assert.h>
#include <iostream>

namespace filianore {

/*
// Matrix
*/
template <typename T, typename MatrixType>
class MatrixBase {
public:
    size_t size() const {
        return std::extent<decltype(MatrixType::data)>::value;
    }

    size_t rows() const {
        return sizeof(MatrixType::data) / sizeof(MatrixType::data[0]);
    }

    size_t cols() const {
        return sizeof(MatrixType::data[0]) / sizeof(int);
    }

    auto make_uniform(T val) {
        for (size_t m = 0; m < rows(); ++m) {
            for (size_t n = 0; n < cols(); ++n) {
                MatrixT().data[m][n] = val;
            }
        }
        return MatrixT();
    }

    auto make_identity(T val = 1) {
        for (size_t m = 0; m < rows(); ++m) {
            for (size_t n = 0; n < cols(); ++n) {
                if (m == n)
                    MatrixT().data[m][n] = val;
                else
                    MatrixT().data[m][n] = 0;
            }
        }
        return MatrixT();
    }

    T trace() {
        T tr = 0;
        // Check if its a square matrix - return 0 if not
        if (rows() != cols())
            return 0;

        for (size_t i = 0; i < rows(); ++i) {
            tr += MatrixT().data[i][i];
        }
        return tr;
    }

    using iterator = T *;
    using const_iterator = const T *;
    iterator begin() {
        return &MatrixT().data[0][0];
    }
    iterator end() {
        return &MatrixT().data[0][0] + size();
    }
    const_iterator begin() const {
        return &MatrixT().data[0][0];
    }
    const_iterator end() const {
        return &MatrixT().data[0][0] + size();
    }

    T &operator()(size_t m, size_t n) {
        return MatrixT().data[m][n];
    }
    const T &operator()(size_t m, size_t n) const {
        return MatrixT().data[m][n];
    }

protected:
    MatrixType &MatrixT() {
        return static_cast<MatrixType &>(*this);
    }

    const MatrixType &MatrixT() const {
        return static_cast<const MatrixType &>(*this);
    }
};

// Base Matrix Class
template <typename T, size_t M, size_t N>
struct Matrix : MatrixBase<T, Matrix<T, M, N>> {
    T data[M][N];
};

// Matrix Operations
template <typename T, size_t M, size_t N>
FILIANORE_INLINE auto operator+(const Matrix<T, M, N> &a, const Matrix<T, M, N> &b) -> Matrix<T, M, N> const {
    Matrix<T, M, N> result;
    for (size_t m = 0; m < M; ++m) {
        for (size_t n = 0; n < N; ++n) {
            result.data[m][n] = a.data[m][n] + b.data[m][n];
        }
    }
    return result;
}

template <typename T, size_t M, size_t N>
FILIANORE_INLINE auto operator+=(Matrix<T, M, N> &a, const Matrix<T, M, N> &b) {
    for (size_t m = 0; m < M; ++m) {
        for (size_t n = 0; n < N; ++n) {
            a.data[m][n] += b.data[m][n];
        }
    }
    return a;
}

template <typename T, size_t M, size_t N>
FILIANORE_INLINE auto operator-(const Matrix<T, M, N> &a, const Matrix<T, M, N> &b) -> Matrix<T, M, N> const {
    Matrix<T, M, N> result;
    for (size_t m = 0; m < M; ++m) {
        for (size_t n = 0; n < N; ++n) {
            result.data[m][n] = a.data[m][n] - b.data[m][n];
        }
    }
    return result;
}

template <typename T, size_t M, size_t N>
FILIANORE_INLINE auto operator-=(Matrix<T, M, N> &a, const Matrix<T, M, N> &b) {
    for (size_t m = 0; m < M; ++m) {
        for (size_t n = 0; n < N; ++n) {
            a.data[m][n] -= b.data[m][n];
        }
    }
    return a;
}

template <typename T, size_t M, size_t N>
FILIANORE_INLINE auto operator*(const Matrix<T, M, N> &a, T s) -> Matrix<T, M, N> const {
    Matrix<T, M, N> result;
    for (size_t m = 0; m < M; ++m) {
        for (size_t n = 0; n < N; ++n) {
            result.data[m][n] = a.data[m][n] * s;
        }
    }
    return result;
}

template <typename T, size_t M, size_t N>
FILIANORE_INLINE auto operator*(const Matrix<T, M, N> &a, const Matrix<T, M, N> &b) -> Matrix<T, M, N> const {
    Matrix<T, M, N> result;
    for (size_t m = 0; m < M; ++m) {
        for (size_t n = 0; n < N; ++n) {
            for (size_t i = 0; i < N; ++i) {
                result.data[m][n] += a.data[m][i] * b.data[i][n];
            }
        }
    }
    return result;
}

template <typename T, typename U, size_t M, size_t N>
FILIANORE_INLINE auto pow(const Matrix<T, M, N> &a, U exp) {
    using V = decltype(a.data[0][0] * exp);
    Matrix<V, M, N> result = a;

    exp = std::abs(exp);
    for (size_t count = 1; count < exp; ++count) {
        result = result * a;
    }
    return result;
}

template <typename T, size_t M, size_t N>
FILIANORE_INLINE auto transpose(const Matrix<T, M, N> &a) {
    Matrix<T, M, N> result;

    for (size_t m = 0; m < M; ++m) {
        for (size_t n = 0; n < N; ++n) {
            result.data[m][n] = a.data[n][m];
        }
    }
    return result;
}

template <typename T, size_t M, size_t N>
FILIANORE_INLINE bool operator==(const Matrix<T, M, N> &a, const Matrix<T, M, N> &b) {
    for (size_t m = 0; m < M; ++m) {
        for (size_t n = 0; n < N; ++n) {
            if (a.data[m][n] != b.data[m][n])
                return false;
        }
    }
    return true;
}

template <typename T, size_t M, size_t N>
FILIANORE_INLINE bool operator!=(const Matrix<T, M, N> &a, const Matrix<T, M, N> &b) {
    for (size_t m = 0; m < M; ++m) {
        for (size_t n = 0; n < N; ++n) {
            if (a.data[m][n] != b.data[m][n])
                return true;
        }
    }
    return false;
}

// Inverse - Credit to pbrt for this one
template <typename T, size_t M, size_t N>
auto inverse(const Matrix<float, M, N> &a) {
    int indxc[N], indxr[N];
    int ipiv[N];
    memset(ipiv, 0, sizeof(ipiv));
    float minv[N][N];
    memcpy(minv, a.data, N * N * sizeof(T));
    for (int i = 0; i < N; i++) {
        int irow = 0, icol = 0;
        float big = 0.f;
        for (int j = 0; j < N; j++) {
            if (ipiv[j] != 1) {
                for (int k = 0; k < N; k++) {
                    if (ipiv[k] == 0) {
                        if (std::abs(minv[j][k]) >= big) {
                            big = float(std::abs(minv[j][k]));
                            irow = j;
                            icol = k;
                        }
                    } else if (ipiv[k] > 1)
                        std::cout << "Singular matrix in MatrixInvert" << std::endl;
                }
            }
        }
        ++ipiv[icol];
        if (irow != icol) {
            for (int k = 0; k < N; ++k)
                std::swap(minv[irow][k], minv[icol][k]);
        }
        indxr[i] = irow;
        indxc[i] = icol;
        if (minv[icol][icol] == 0) {
            std::cout << "Singular matrix in MatrixInvert" << std::endl;
        }
        float pivinv = 1.f / minv[icol][icol];
        minv[icol][icol] = 1.;
        for (int j = 0; j < N; j++)
            minv[icol][j] *= pivinv;
        for (int j = 0; j < N; j++) {
            if (j != icol) {
                float save = minv[j][icol];
                minv[j][icol] = 0;
                for (int k = 0; k < N; k++)
                    minv[j][k] -= minv[icol][k] * save;
            }
        }
    }
    int _j = N - 1;
    for (int j = _j; j >= 0; j--) {
        if (indxr[j] != indxc[j]) {
            for (int k = 0; k < N; k++)
                std::swap(minv[k][indxr[j]], minv[k][indxc[j]]);
        }
    }
    return Matrix<T, N, N>(minv);
}

// Matrix2
template <typename T>
struct Matrix<T, 2, 2> : MatrixBase<T, Matrix<T, 2, 2>> {
    T data[2][2];

    Matrix() {
        data[0][0] = data[0][1] = data[1][0] = data[1][1] = 0;
    }

    Matrix(T _m00, T _m01, T _m10, T _m11) {
        data[0][0] = _m00;
        data[0][1] = _m01;
        data[1][0] = _m10;
        data[1][1] = _m11;
    }

    Matrix(T mat[2][2]) {
        memcpy(data, mat, (2 * 2) * sizeof(T));
    }

    T determinant() {
        return (data[1][1] * data[0][0]) - (data[0][1] * data[1][0]);
    }
};

// Matrix3
template <typename T>
struct Matrix<T, 3, 3> : MatrixBase<T, Matrix<T, 3, 3>> {
    T data[3][3];

    Matrix() {
        data[0][0] = data[0][1] = data[0][2] = 0;
        data[1][0] = data[1][1] = data[1][2] = 0;
        data[2][0] = data[2][1] = data[2][2] = 0;
    }

    Matrix(T _m00, T _m01, T _m02, T _m10, T _m11, T _m12, T _m20, T _m21, T _m22) {
        data[0][0] = _m00;
        data[0][1] = _m01;
        data[0][2] = _m02;
        data[1][0] = _m10;
        data[1][1] = _m11;
        data[1][2] = _m12;
        data[2][0] = _m20;
        data[2][1] = _m21;
        data[2][2] = _m22;
    }

    Matrix(T mat[3][3]) {
        memcpy(data, mat, (3 * 3) * sizeof(T));
    }

    T determinant() {
        return data[0][0] * (data[1][1] * data[2][2] - data[1][2] * data[2][1]) -
               data[0][1] * (data[1][0] * data[2][2] - data[1][2] * data[2][0]) +
               data[0][2] * (data[1][0] * data[2][1] - data[1][1] * data[2][0]);
    }
};

// Matrix4
template <typename T>
struct Matrix<T, 4, 4> : MatrixBase<T, Matrix<T, 4, 4>> {
    T data[4][4];

    Matrix() {
        data[0][0] = data[0][1] = data[0][2] = data[0][3] = 0;
        data[1][0] = data[1][1] = data[1][2] = data[1][3] = 0;
        data[2][0] = data[2][1] = data[2][2] = data[2][3] = 0;
        data[3][0] = data[3][1] = data[3][2] = data[3][3] = 0;
    }

    Matrix(T _m00, T _m01, T _m02, T _m03,
           T _m10, T _m11, T _m12, T _m13,
           T _m20, T _m21, T _m22, T _m23,
           T _m30, T _m31, T _m32, T _m33) {
        data[0][0] = _m00;
        data[0][1] = _m01;
        data[0][2] = _m02;
        data[0][3] = _m03;
        data[1][0] = _m10;
        data[1][1] = _m11;
        data[1][2] = _m12;
        data[1][3] = _m13;
        data[2][0] = _m20;
        data[2][1] = _m21;
        data[2][2] = _m22;
        data[2][3] = _m23;
        data[3][0] = _m30;
        data[3][1] = _m31;
        data[3][2] = _m32;
        data[3][3] = _m33;
    }

    Matrix(T mat[4][4]) {
        memcpy(data, mat, (4 * 4) * sizeof(T));
    }

    T determinant() {
        Matrix<T, 3, 3> m1 = Matrix<T, 3, 3>(data[1][1], data[1][2], data[1][3], data[2][1], data[2][2], data[2][3], data[3][1], data[3][2], data[3][3]);
        Matrix<T, 3, 3> m2 = Matrix<T, 3, 3>(data[1][0], data[1][2], data[1][3], data[2][0], data[2][2], data[2][3], data[3][0], data[3][2], data[3][3]);
        Matrix<T, 3, 3> m3 = Matrix<T, 3, 3>(data[1][0], data[1][1], data[1][3], data[2][0], data[2][1], data[2][3], data[3][0], data[3][1], data[3][3]);
        Matrix<T, 3, 3> m4 = Matrix<T, 3, 3>(data[1][0], data[1][1], data[1][2], data[2][0], data[2][1], data[2][2], data[3][0], data[3][1], data[3][2]);

        return data[0][0] * m1.determinant() - data[0][1] * m2.determinant() + data[0][2] * m3.determinant() - data[0][3] * m4.determinant();
    }
};

/*
// Transform
*/
class Transform {
public:
    Matrix<float, 4, 4> mat, matInv;

    Transform() {}

    Transform(const float _mat[4][4]) {
        mat = Matrix<float, 4, 4>(_mat[0][0], _mat[0][1], _mat[0][2], _mat[0][3],
                                  _mat[1][0], _mat[1][1], _mat[1][2], _mat[1][3],
                                  _mat[2][0], _mat[2][1], _mat[2][2], _mat[2][3],
                                  _mat[3][0], _mat[3][1], _mat[3][2], _mat[3][3]);
        matInv = inverse<float>(mat);
    }

    Transform(const Matrix<float, 4, 4> &_mat)
        : mat(_mat), matInv(inverse<float>(_mat)) {}

    Transform(const Matrix<float, 4, 4> &_mat, const Matrix<float, 4, 4> &_matInv)
        : mat(_mat), matInv(_matInv) {}

    Transform operator*(Transform t2) {
        Matrix<float, 4, 4> m1 = mat * t2.mat;
        Matrix<float, 4, 4> m2 = t2.matInv * matInv;
        return Transform(m1, m2);
    }

    bool operator==(const Transform &t) const {
        return t.mat == mat && t.matInv == matInv;
    }

    bool operator!=(const Transform &t) const {
        return t.mat != mat || t.matInv != matInv;
    }

    Vector3f point_transform(const Vector3f &pt) const {
        float xp = mat.data[0][0] * pt.x + mat.data[0][1] * pt.y + mat.data[0][2] * pt.z + mat.data[0][3];
        float yp = mat.data[1][0] * pt.x + mat.data[1][1] * pt.y + mat.data[1][2] * pt.z + mat.data[1][3];
        float zp = mat.data[2][0] * pt.x + mat.data[2][1] * pt.y + mat.data[2][2] * pt.z + mat.data[2][3];
        float wp = mat.data[3][0] * pt.x + mat.data[3][1] * pt.y + mat.data[3][2] * pt.z + mat.data[3][3];

        if (wp == 1.0) {
            return Vector3f(xp, yp, zp);
        } else {
            assert(wp != 0);
            return Vector3f(xp, yp, zp) / wp;
        }
    }

    Vector3f vector_transform(const Vector3f &v) const {
        return Vector3f(mat.data[0][0] * v.x + mat.data[0][1] * v.y + mat.data[0][2] * v.z,
                        mat.data[1][0] * v.x + mat.data[1][1] * v.y + mat.data[1][2] * v.z,
                        mat.data[2][0] * v.x + mat.data[2][1] * v.y + mat.data[2][2] * v.z);
    }

    friend Transform inverse(const Transform &t) {
        return Transform(t.matInv, t.mat);
    }

    bool swaps_handedness() const {
        float det = mat.data[0][0] * (mat.data[1][1] * mat.data[2][2] - mat.data[1][2] * mat.data[2][1]) -
                    mat.data[0][1] * (mat.data[1][0] * mat.data[2][2] - mat.data[1][2] * mat.data[2][0]) +
                    mat.data[0][2] * (mat.data[1][0] * mat.data[2][1] - mat.data[1][1] * mat.data[2][0]);
        return det < 0;
    }
};

static Transform translate(float x, float y, float z) {
    Matrix<float, 4, 4> m(1.f, 0.f, 0.f, x,
                          0.f, 1.f, 0.f, y,
                          0.f, 0.f, 1.f, z,
                          0.f, 0.f, 0.f, 1.f);

    Matrix<float, 4, 4> mInv(1.f, 0.f, 0.f, -x,
                             0.f, 1.f, 0.f, -y,
                             0.f, 0.f, 1.f, -z,
                             0.f, 0.f, 0.f, 1.f);

    return Transform(m, mInv);
}

static Transform scale(float x, float y, float z) {
    assert(x != 0 && y != 0 && z != 0);

    Matrix<float, 4, 4> m(x, 0.f, 0.f, 0.f,
                          0.f, y, 0.f, 0.f,
                          0.f, 0, z, 0.f,
                          0.f, 0.f, 0.f, 1.f);

    Matrix<float, 4, 4> mInv(1.f / x, 0.f, 0.f, 0.f,
                             0.f, 1.f / y, 0, 0,
                             0.f, 0, 1.f / z, 0,
                             0.f, 0.f, 0.f, 1.f);

    return Transform(m, mInv);
}

static Transform rotate_x(float angle, bool inRadians = false) {
    float sin_t = std::sin(angle);
    float cos_t = std::cos(angle);

    if (!inRadians) {
        sin_t = std::sin(filianore::radians<float>(angle));
        cos_t = std::cos(filianore::radians<float>(angle));
    }

    Matrix<float, 4, 4> m(1.f, 0.f, 0.f, 0.f,
                          0.f, cos_t, -sin_t, 0.f,
                          0.f, sin_t, cos_t, 0.f,
                          0.f, 0.f, 0.f, 1.f);

    return Transform(m, transpose(m));
}

static Transform rotate_y(float angle, bool inRadians = false) {
    float sin_t = std::sin(angle);
    float cos_t = std::cos(angle);

    if (!inRadians) {
        sin_t = std::sin(filianore::radians<float>(angle));
        cos_t = std::cos(filianore::radians<float>(angle));
    }

    Matrix<float, 4, 4> m(cos_t, 0.f, sin_t, 0.f,
                          0.f, 1.f, 0.f, 0.f,
                          -sin_t, 0.f, cos_t, 0.f,
                          0.f, 0.f, 0.f, 1.f);

    return Transform(m, transpose(m));
}

static Transform rotate_z(float angle, bool inRadians = false) {
    float sin_t = std::sin(angle);
    float cos_t = std::cos(angle);

    if (!inRadians) {
        sin_t = std::sin(filianore::radians<float>(angle));
        cos_t = std::cos(filianore::radians<float>(angle));
    }

    Matrix<float, 4, 4> m(cos_t, -sin_t, 0.f, 0.f,
                          sin_t, cos_t, 0.f, 0.f,
                          0.f, 0.f, 1.f, 0.f,
                          0.f, 0.f, 0.f, 1.f);

    return Transform(m, transpose(m));
}

} // namespace filianore

#endif