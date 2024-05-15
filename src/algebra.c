#include "algebra.h"
#include <stdio.h>
#include <math.h>

Matrix create_matrix(int row, int col)
{
    Matrix m;
    m.rows = row;
    m.cols = col;
    return m;
}

Matrix add_matrix(Matrix a, Matrix b)
{
    if (a.rows == b.rows && a.cols == b.cols)
    {
        Matrix m = create_matrix(a.rows, a.cols);
        for (int i = 0; i < a.rows; i++)
        {
            for (int j = 0; j < a.cols; j++)
            {
                m.data[i][j] = a.data[i][j] + b.data[i][j];
            }
        }
        return m;
    }
    else
    {
        printf("Error: Matrix a and b must have the same rows and cols.\n");
        return create_matrix(0, 0);
    }
}

Matrix sub_matrix(Matrix a, Matrix b)
{
    if (a.rows == b.rows && a.cols == b.cols)
    {
        Matrix m = create_matrix(a.rows, a.cols);
        for (int i = 0; i < a.rows; i++)
        {
            for (int j = 0; j < a.cols; j++)
            {
                m.data[i][j] = a.data[i][j] - b.data[i][j];
            }
        }
        return m;
    }
    else
    {
        printf("Error: Matrix a and b must have the same rows and cols.\n");
        return create_matrix(0, 0);
    }
}

Matrix mul_matrix(Matrix a, Matrix b)
{
    if (a.cols == b.rows)
    {
        Matrix m = create_matrix(a.rows, b.cols);
        for (int i = 0; i < a.rows; i++)
        {
            for (int j = 0; j < b.cols; j++)
            {
                m.data[i][j] = 0;
                for (int k = 0; k < a.cols; k++)
                {
                    m.data[i][j] += a.data[i][k] * b.data[k][j];
                }
            }
        }
        return m;
    }
    else
    {
        printf("Error: The number of cols of matrix a must be equal to the number of rows of matrix b.\n");
        return create_matrix(0, 0);
    }
}

Matrix scale_matrix(Matrix a, double k)
{
    Matrix m = create_matrix(a.rows, a.cols);
    for (int i = 0; i < a.rows; i++)
    {
        for (int j = 0; j < a.cols; j++)
        {
            m.data[i][j] = a.data[i][j] * k;
        }
    }
    return m;
}

Matrix transpose_matrix(Matrix a)
{
    Matrix m = create_matrix(a.cols, a.rows);
    for (int i = 0; i < a.rows; i++)
    {
        for (int j = 0; j < a.cols; j++)
        {
            m.data[j][i] = a.data[i][j];
        }
    }
    return m;
}

Matrix cofactor_matrix(Matrix a, int x, int y)
{
    if (a.rows == 1 || a.cols == 1)
    {
    }

    Matrix m = create_matrix(a.rows - 1, a.cols - 1);

    int new_i = 0;
    for (int i = 0; i < a.rows; ++i)
    {
        if (i == x - 1)
            continue;

        int new_j = 0;
        for (int j = 0; j < a.cols; ++j)
        {
            if (j == y - 1)
                continue;

            m.data[new_i][new_j] = a.data[i][j];
            new_j++;
        }
        new_i++;
    }

    return m;
}

double det_matrix(Matrix a)
{
    if (a.rows != a.cols)
    {
        printf("Error: The matrix must be square.");
        return 0;
    }
    else if (a.rows == 1)
    {
        return a.data[0][0];
    }
    else if (a.rows == 2)
    {
        return a.data[0][0] * a.data[1][1] - a.data[0][1] * a.data[1][0];
    }
    else
    {
        double det = 0;
        for (int j = 0; j < a.cols; ++j) 
        {
            Matrix cofactor = cofactor_matrix(a, 1, j + 1); 
            det += a.data[0][j] * (j % 2 ? -1 : 1) * det_matrix(cofactor);
        }
        return det;
    }
}

Matrix
inv_matrix(Matrix a)
{
    if (a.cols != a.rows)
    {
        printf("Error: The matrix must be a square matrix.\n");
        return create_matrix(0, 0);
    }
    else if (det_matrix(a) == 0)
    {
        printf("Error: The matrix is singular.\n");
        return create_matrix(0, 0);
    }
    else
    {
        Matrix m = create_matrix(a.rows, a.cols);
        for (int i = 0; i < a.rows; i++)
        {
            for (int j = 0; j < a.cols; j++)
            {
                m.data[i][j] = ((i + j) % 2 ? -1 : 1) * det_matrix(cofactor_matrix(a, j + 1, i + 1));
            }
        }
        for (int i = 0; i < a.rows; i++)
        {
            for (int j = 0; j < a.cols; j++)
            {
                m.data[i][j] /= det_matrix(a);
            }
        }
        return m;
    }
}

int rank_matrix(Matrix a)
{
    int rank = 0;
    int min = a.rows > a.cols ? a.cols : a.rows;

    for (int i = 0; i < min; i++)
    {
        if (a.data[i][i] == 0)
        {
            for (int j = i + 1; j < a.rows; j++)
            {
                if (a.data[j][i] != 0)
                {
                    double temp;
                    for (int k = 0; k < a.cols; k++)
                    {
                        temp = a.data[i][k];
                        a.data[i][k] = a.data[j][k];
                        a.data[j][k] = temp;
                    }
                    break;
                }
            }
        }
        for (int j = i + 1; j < a.rows; j++)
        {
            double factor;
            factor = a.data[j][i] / a.data[i][i];
            for (int k = 0; k < a.cols; k++)
            {
                a.data[j][k] = a.data[j][k] - factor * a.data[i][k];
            }
        }
    }
    for (int i = 0; i < min; i++)
    {
        if (a.data[i][i] != 0)
        {
            rank++;
        }
    }
    return rank;
}

double trace_matrix(Matrix a)
{
    if (a.cols != a.rows)
    {
        printf("Error: The matrix must be square.\n");
        return 0;
    }
    double trace = 0;
    for (int i = 0; i < a.rows; i++)
    {
        trace += a.data[i][i];
    }
    return trace;
}

void print_matrix(Matrix a)
{
    for (int i = 0; i < a.rows; i++)
    {
        for (int j = 0; j < a.cols; j++)
        {
            // 按行打印，每个元素占8个字符的宽度，小数点后保留2位，左对齐
            printf("%-8.2f", a.data[i][j]);
        }
        printf("\n");
    }
}