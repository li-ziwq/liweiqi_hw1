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
    if(a.rows == b.rows && a.cols == b.cols)
    {
        Matrix m = create_matrix(a.rows, a.cols);
        for(int i = 0; i < a.rows; i++)
        {
            for(int j = 0; j < a.cols; j++)
            {
                m.data[i][j] = a.data[i][j] + b.data[i][j];
            }
        }
        return m;
    }else{
        printf("Error: Matrix a and b must have the same rows and cols.\n");
        return create_matrix(0, 0);
    }
}

Matrix sub_matrix(Matrix a, Matrix b)
{
    if(a.rows == b.rows && a.cols == b.cols)
    {
        Matrix m = create_matrix(a.rows, a.cols);
        for(int i = 0; i < a.rows; i++)
        {
            for(int j = 0; j < a.cols; j++)
            {
                m.data[i][j] = a.data[i][j] - b.data[i][j];
            }
        }
        return m;
    }else{
        printf("Error: Matrix a and b must have the same rows and cols.\n");
        return create_matrix(0, 0);
    }
}

Matrix mul_matrix(Matrix a, Matrix b)
{
    if(a.cols == b.rows)
    {
        Matrix m = create_matrix(a.rows, b.cols);
        for(int i = 0; i < a.rows; i++)
        {
            for(int j = 0; j < b.cols; j++)
            {
                m.data[i][j] = 0;
                for(int k = 0; k < a.cols; k++)
                {
                    m.data[i][j] += a.data[i][k] * b.data[k][j];
                }
            }
        }
        return m;
    }else{
        printf("Error: Matrix a and b must have the same rows and cols.\n");
        return create_matrix(0, 0);
    }
    
}

Matrix scale_matrix(Matrix a, double k)
{
    Matrix m = create_matrix(a.rows, a.cols);
    for(int i = 0; i < a.rows; i++)
    {
        for(int j = 0; j < a.cols; j++)
        {
            m.data[i][j] = a.data[i][j] * k;
        }
    }
    return m;
}

Matrix transpose_matrix(Matrix a)
{
    Matrix m = create_matrix(a.cols, a.rows);
    for(int i = 0; i < a.rows; i++)
    {
        for(int j = 0; j < a.cols; j++)
        {
            m.data[j][i] = a.data[i][j];
        }
    }
    return m;
}

double det_matrix(Matrix a)
{
    if(a.rows == a.cols)
    {
        
    }else{
        printf("Error: Matrix a must be a square matrix.\n");
        return 0;
    }
    
}

Matrix inv_matrix(Matrix a)
{
    // ToDo
    return create_matrix(0, 0);
}

int rank_matrix(Matrix a)
{
    // ToDo
    return 0;
}

double trace_matrix(Matrix a)
{
    // ToDo
    return 0;
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