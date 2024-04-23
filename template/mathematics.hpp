#ifndef MATHEMATICS
#define MATHEMATICS
#define MatrixMaxn 100
#include <cstring>
#include <iostream>

template <typename T>
class matrix
{
public:
    int length = MatrixMaxn, width = MatrixMaxn;
    T data[MatrixMaxn][MatrixMaxn];

    matrix() {}

    matrix(int _length, int _width) { length = _length, width = _width; }

    matrix(int _length, int _width, T init_value)
    {
        length = _length, width = _width;
        for (int i = 0; i < _length; i++)
            for (int j = 0; j < width; j++)
                data[i][j] = init_value;
    }

    matrix(int _length, int _width, T array_line[])
    {
        length = _length, width = _width;
        for (int i = 0; i < _length; i++)
            for (int j = 0; j < _width; j++)
                data[i][j] = array_line[i * _length + j];
    }

    matrix(int _length, int _width, T init_value, int mod)
    {
        length = _length, width = _width, MOD = mod;
        for (int i = 0; i < _length; i++)
            for (int j = 0; j < _width; j++)
                data[i][j] = init_value;
    }

    matrix(int _length, int _width, T array_line[], int mod)
    {
        length = _length, width = _width, MOD = mod;
        for (int i = 0; i < _length; i++)
            for (int j = 0; j < _width; j++)
                data[i][j] = array_line[i * _length + j];
    }

    T get(int x, int y) { return data[x - 1][y - 1]; }

    void valued(int x, int y, T value) { data[x - 1][y - 1] = value; }

    void debug_traverse()
    {
        for (int i = 0; i < this->length; i++)
        {
            for (int j = 0; j < this->width; j++)
                std::cout << data[i][j] << " ";
            std::cout << "\n";
        }
    }

    matrix operator+(const matrix &M) const
    {
        if (length != M.length || width != M.width)
            throw;
        matrix result(length, width);
        for (int i = 0; i < length; i++)
            for (int j = 0; j < width; j++)
                result.data[i][j] = (data[i][j] + M.data[i][j]) % MOD;
        return result;
    }

    matrix operator-(const matrix &M) const
    {
        if (length != M.length || width != M.width)
            throw;
        matrix result(length, width);
        for (int i = 0; i < length; i++)
            for (int j = 0; j < width; j++)
                result.data[i][j] = (data[i][j] - M.data[i][j]) % MOD;
        return result;
    }

    matrix operator*(const matrix &M) const
    {
        if (width != M.length)
            throw;
        matrix result(length, M.width);
        int temp;
        for (int i = 0; i < length; i++)
        {
            for (int k = 0; k < M.width; k++)
            {
                temp = data[i][k];
                for (int j = 0; j < width; j++)
                {
                    result.data[i][j] += M.data[k][j] * temp;
                    result.data[i][j] %= MOD;
                }
            }
        }
        return result;
    }

    matrix operator^(long long int x) const
    {
        matrix result(length, width), base(length, width);
        for (int i = 0; i < length; i++)
            result.data[i][i] = 1;
        for (int i = 0; i < length; i++)
            for (int j = 0; j < width; j++)
                base.data[i][j] = data[i][j] % MOD;
        while (x)
        {
            if (x & 1)
                result = result * base;
            base = base * base;
            x >>= 1;
        }
        return result;
    }

    matrix strassen(const matrix &M)
    {
        if (length != width || M.length != M.width)
            throw;

        int N = length;

        T **MatrixA11;
        T **MatrixA12;
        T **MatrixA21;
        T **MatrixA22;

        T **MatrixB11;
        T **MatrixB12;
        T **MatrixB21;
        T **MatrixB22;

        T **MatrixC11;
        T **MatrixC12;
        T **MatrixC21;
        T **MatrixC22;

        MatrixA11 = new int *[N / 2];
        MatrixA12 = new int *[N / 2];
        MatrixA21 = new int *[N / 2];
        MatrixA22 = new int *[N / 2];

        MatrixB11 = new int *[N / 2];
        MatrixB12 = new int *[N / 2];
        MatrixB21 = new int *[N / 2];
        MatrixB22 = new int *[N / 2];

        MatrixC11 = new int *[N / 2];
        MatrixC12 = new int *[N / 2];
        MatrixC21 = new int *[N / 2];
        MatrixC22 = new int *[N / 2];

        for (int i = 0; i < N / 2; i++)
        {
            MatrixA11[i] = new int[N / 2];
            MatrixA12[i] = new int[N / 2];
            MatrixA21[i] = new int[N / 2];
            MatrixA22[i] = new int[N / 2];

            MatrixB11[i] = new int[N / 2];
            MatrixB12[i] = new int[N / 2];
            MatrixB21[i] = new int[N / 2];
            MatrixB22[i] = new int[N / 2];

            MatrixC11[i] = new int[N / 2];
            MatrixC12[i] = new int[N / 2];
            MatrixC21[i] = new int[N / 2];
            MatrixC22[i] = new int[N / 2];
        }

        for (int i = 0; i < N / 2; i++)
        {
            for (int j = 0; j < N / 2; j++)
            {
                MatrixA11[i][j] = data[i][j];
                MatrixA12[i][j] = data[i][j + N / 2];
                MatrixA21[i][j] = data[i + N / 2][j];
                MatrixA22[i][j] = data[i + N / 2][j + N / 2];

                MatrixB11[i][j] = M.data[i][j];
                MatrixB12[i][j] = M.data[i][j + N / 2];
                MatrixB21[i][j] = M.data[i + N / 2][j];
                MatrixB22[i][j] = M.data[i + N / 2][j + N / 2];
            }
        }

        int **MatrixS1 = new int *[N / 2];
        int **MatrixS2 = new int *[N / 2];
        int **MatrixS3 = new int *[N / 2];
        int **MatrixS4 = new int *[N / 2];
        int **MatrixS5 = new int *[N / 2];
        int **MatrixS6 = new int *[N / 2];
        int **MatrixS7 = new int *[N / 2];
        int **MatrixS8 = new int *[N / 2];
        int **MatrixS9 = new int *[N / 2];
        int **MatrixS10 = new int *[N / 2];

        for (int i = 0; i < N / 2; i++)
        {
            MatrixS1[i] = new int[N / 2];
            MatrixS2[i] = new int[N / 2];
            MatrixS3[i] = new int[N / 2];
            MatrixS4[i] = new int[N / 2];
            MatrixS5[i] = new int[N / 2];
            MatrixS6[i] = new int[N / 2];
            MatrixS7[i] = new int[N / 2];
            MatrixS8[i] = new int[N / 2];
            MatrixS9[i] = new int[N / 2];
            MatrixS10[i] = new int[N / 2];
        }

        Matrix_Sub(N / 2, MatrixB12, MatrixB22, MatrixS1);
        Matrix_Sum(N / 2, MatrixA11, MatrixA12, MatrixS2);
        Matrix_Sum(N / 2, MatrixA21, MatrixA22, MatrixS3);
        Matrix_Sub(N / 2, MatrixB21, MatrixB11, MatrixS4);
        Matrix_Sum(N / 2, MatrixA11, MatrixA22, MatrixS5);
        Matrix_Sum(N / 2, MatrixB11, MatrixB22, MatrixS6);
        Matrix_Sub(N / 2, MatrixA12, MatrixA22, MatrixS7);
        Matrix_Sum(N / 2, MatrixB21, MatrixB22, MatrixS8);
        Matrix_Sub(N / 2, MatrixA11, MatrixA21, MatrixS9);
        Matrix_Sum(N / 2, MatrixB11, MatrixB12, MatrixS10);

        int **MatrixP1 = new int *[N / 2];
        int **MatrixP2 = new int *[N / 2];
        int **MatrixP3 = new int *[N / 2];
        int **MatrixP4 = new int *[N / 2];
        int **MatrixP5 = new int *[N / 2];
        int **MatrixP6 = new int *[N / 2];
        int **MatrixP7 = new int *[N / 2];

        for (int i = 0; i < N / 2; i++)
        {
            MatrixP1[i] = new int[N / 2];
            MatrixP2[i] = new int[N / 2];
            MatrixP3[i] = new int[N / 2];
            MatrixP4[i] = new int[N / 2];
            MatrixP5[i] = new int[N / 2];
            MatrixP6[i] = new int[N / 2];
            MatrixP7[i] = new int[N / 2];
        }
        Matrix_Mul(N / 2, MatrixA11, MatrixS1, MatrixP1);
        Matrix_Mul(N / 2, MatrixS2, MatrixB22, MatrixP2);
        Matrix_Mul(N / 2, MatrixS3, MatrixB11, MatrixP3);
        Matrix_Mul(N / 2, MatrixA22, MatrixS4, MatrixP4);
        Matrix_Mul(N / 2, MatrixS5, MatrixS6, MatrixP5);
        Matrix_Mul(N / 2, MatrixS7, MatrixS8, MatrixP6);
        Matrix_Mul(N / 2, MatrixS9, MatrixS10, MatrixP7);

        Matrix_Sum(N / 2, MatrixP5, MatrixP4, MatrixC11);
        Matrix_Sub(N / 2, MatrixC11, MatrixP2, MatrixC11);
        Matrix_Sum(N / 2, MatrixC11, MatrixP6, MatrixC11);
        Matrix_Sum(N / 2, MatrixP1, MatrixP2, MatrixC12);
        Matrix_Sum(N / 2, MatrixP3, MatrixP4, MatrixC21);
        Matrix_Sum(N / 2, MatrixP5, MatrixP1, MatrixC22);
        Matrix_Sub(N / 2, MatrixC22, MatrixP3, MatrixC22);
        Matrix_Sub(N / 2, MatrixC22, MatrixP7, MatrixC22);

        matrix result;

        for (int i = 0; i < N / 2; i++)
        {
            for (int j = 0; j < N / 2; j++)
            {
                result.valued(i, j, MatrixC11[i][j]);
                result.valued(i, i + N / 2, MatrixC12[i][j]);
                result.valued(i + N / 2, j, MatrixC21[i][j]);
                result.valued(i + N / 2, j + N / 2, MatrixC22[i][j]);
            }
        }

        return result;
    }

private:
    int MOD = INT32_MAX;

    void Matrix_Sum(int N, int **MatrixA, int **MatrixB, int **Sum_Matrix)
    {
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                Sum_Matrix[i][j] = MatrixA[i][j] + MatrixB[i][j];
    }

    void Matrix_Sub(int N, int **MatrixA, int **MatrixB, int **Sub_Matrix)
    {
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                Sub_Matrix[i][j] = MatrixA[i][j] - MatrixB[i][j];
    }

    void Matrix_Mul(int N, int **MatrixA, int **MatrixB, int **Mul_Matrix)
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                Mul_Matrix[i][j] = 0;
                for (int k = 0; k < N; k++)
                    Mul_Matrix[i][j] = Mul_Matrix[i][j] + MatrixA[i][k] * MatrixB[k][j];
            }
        }
    }
};

#endif
