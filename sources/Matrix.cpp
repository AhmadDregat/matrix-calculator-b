#include "Matrix.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <cstring>

using namespace std;
namespace zich
{

    /*
    Constructor
    */
    Matrix::Matrix(vector<double> mat, int row, int col)
    {
        if (mat.size() != row * col)
        {
            throw invalid_argument("Inaccurate values were entered.");
        }
        if (row <= 0 || col <= 0)
        {
            throw invalid_argument("The matrix data must be positive and different from 0.");
        }
        this->row = row;
        this->col = col;
        double num = 0;
        for (size_t i = 0; i < row; i++)
        {
            vector<double> v;
            for (size_t j = 0; j < col; j++)
            {
                v.push_back(mat[num++]);
            }
            this->myMatrix.push_back(v);
        }
    }

    Matrix::~Matrix()
    {
        for (unsigned int i = 0; i < this->row; i++)
        {
            this->myMatrix[i].clear();
        }
        this->myMatrix.clear();
    }

    Matrix::Matrix(int row, int col)
    {
        if (row <= 0 || col <= 0)
        {
            throw invalid_argument("The matrix data must be positive and different from 0.");
        }
        this->row = row;
        this->col = col;
        for (size_t i = 0; i < row; i++)
        {
            vector<double> mat;
            for (size_t j = 0; j < col; j++)
            {
                mat.push_back(0);
            }
            this->myMatrix.push_back(mat);
        }
    }

    Matrix operator+(const Matrix &m1, const Matrix &m2)
    {
        Matrix ans(m1.row, m1.col);
        if (m1.row != m2.row || m1.col != m2.col)
        {
            throw invalid_argument("The matrices should be identical");
        }
        for (unsigned int i = 0; i < m1.row; i++)
        {
            for (unsigned int j = 0; j < m1.col; j++)
            {
                ans.myMatrix[i][j] = m1.myMatrix[i][j] + m2.myMatrix[i][j];
            }
        }
        return ans;
    }

    void operator+=(Matrix &m1, const Matrix &m2)
    {
        if (m1.row != m2.row || m1.col != m2.col)
        {
            throw invalid_argument("The matrices should be identical");
        }
        for (unsigned int i = 0; i < m1.row; i++)
        {
            for (unsigned int j = 0; j < m1.col; j++)
            {
                m1.myMatrix[i][j] += m2.myMatrix[i][j];
            }
        }
    }

    Matrix operator+(const Matrix &m)
    {
        Matrix ans{m.row, m.col};
        int row = m.row;
        int col = m.col;
        for (unsigned int i = 0; i < row; i++)
        {
            for (unsigned int j = 0; j < col; j++)
            {
                ans.myMatrix[i][j] = abs(m.myMatrix[i][j]);
            }
        }
        return ans;
    }

    Matrix operator+(const Matrix &m, double scalar)
    {
        Matrix ans{m.row, m.col};
        for (unsigned int i = 0; i < m.row; i++)
        {
            for (unsigned int j = 0; j < m.col; j++)
            {
                ans.myMatrix[i][j] = m.myMatrix[i][j] + scalar;
            }
        }
        return ans;
    }

    Matrix operator+(double scalar, const Matrix &m)
    {
        Matrix ans{m.row, m.col};
        for (unsigned int i = 0; i < m.row; i++)
        {
            for (unsigned int j = 0; j < m.col; j++)
            {
                ans.myMatrix[i][j] = scalar + m.myMatrix[i][j];
            }
        }
        return ans;
    }

    void operator+=(Matrix &m, double scalar)
    {
        for (unsigned int i = 0; i < m.row; i++)
        {
            for (unsigned int j = 0; j < m.col; j++)
            {
                m.myMatrix[i][j] += scalar;
            }
        }
    }

    Matrix operator-(const Matrix &m1, const Matrix &m2)
    {
        Matrix ans(m1.row, m1.col);
        if (m1.row != m2.row || m1.col != m2.col)
        {
            throw invalid_argument("The matrices should be identical");
        }
        for (unsigned int i = 0; i < m1.row; i++)
        {
            for (unsigned int j = 0; j < m1.col; j++)
            {
                ans.myMatrix[i][j] = m1.myMatrix[i][j] - m2.myMatrix[i][j];
            }
        }
        return ans;
    }

    void operator-=(Matrix &m1, const Matrix &m2)
    {
        if (m1.row != m2.row || m1.col != m2.col)
        {
            throw invalid_argument("The matrices should be identical");
        }
        for (unsigned int i = 0; i < m1.row; i++)
        {
            for (unsigned int j = 0; j < m2.col; j++)
            {
                m1.myMatrix[i][j] -= m2.myMatrix[i][j];
            }
        }
    }

    Matrix operator-(const Matrix &m)
    {
        Matrix ans{m.row, m.col};
        int row = m.row;
        int col = m.col;
        for (unsigned int i = 0; i < row; i++)
        {
            for (unsigned int j = 0; j < col; j++)
            {
                ans.myMatrix[i][j] = m.myMatrix[i][j] * (-1);
            }
        }
        return ans;
    }

    Matrix operator-(const Matrix &m, double scalar)
    {
        Matrix ans{m.row, m.col};
        for (unsigned int i = 0; i < m.row; i++)
        {
            for (unsigned int j = 0; j < m.col; j++)
            {
                ans.myMatrix[i][j] = m.myMatrix[i][j] - scalar;
            }
        }
        return ans;
    }

    Matrix operator-(double scalar, const Matrix &m)
    {
        Matrix ans{m.row, m.col};
        for (unsigned int i = 0; i < m.row; i++)
        {
            for (unsigned int j = 0; j < m.col; j++)
            {
                ans.myMatrix[i][j] = scalar - m.myMatrix[i][j];
            }
        }
        return ans;
    }

    void operator-=(Matrix &m, double scalar)
    {
        for (unsigned int i = 0; i < m.row; i++)
        {
            for (unsigned int j = 0; j < m.col; j++)
            {
                m.myMatrix[i][j] -= scalar;
            }
        }
    }

    Matrix operator*(const Matrix &m1, const Matrix &m2)
    {
        Matrix ans = Matrix(m1.row, m2.col);
        if (m1.col != m2.row)
        {
            throw invalid_argument("The multiplication operation cannot be performed - the number of columns in the first matrix must be equal to the number of rows in the second matrix");
        }
        for (size_t i = 0; i < m1.row; i++)
        {
            for (size_t j = 0; j < m2.col; j++)
            {
                ans.myMatrix[i][j] = 0;
                for (size_t n = 0; n < m2.row; n++)
                {
                    ans.myMatrix[i][j] += m1.myMatrix[i][n] * m2.myMatrix[n][j];
                }
            }
        }
        return ans;
    }

    void operator*=(Matrix &m1, const Matrix &m2)
    {
        m1 = operator*(m1, m2);
    }

    Matrix operator*(const Matrix &m, double scalar)
    {
        Matrix ans{m.row, m.col};
        for (unsigned int i = 0; i < m.row; i++)
        {
            for (unsigned int j = 0; j < m.col; j++)
            {
                ans.myMatrix[i][j] += m.myMatrix[i][j] * scalar;
            }
        }
        return ans;
    }

    Matrix operator*(double scalar, const Matrix &m)
    {
        Matrix ans{m.row, m.col};
        for (unsigned int i = 0; i < m.row; i++)
        {
            for (unsigned int j = 0; j < m.col; j++)
            {
                ans.myMatrix[i][j] += scalar * m.myMatrix[i][j];
            }
        }
        return ans;
    }

    void operator*=(Matrix &m, int scalar)
    {
        for (unsigned int i = 0; i < m.row; i++)
        {
            for (unsigned int j = 0; j < m.col; j++)
            {
                m.myMatrix[i][j] *= scalar;
            }
        }
    }

    bool operator<(const Matrix &m1, const Matrix &m2)
    {
        if (m1.row != m2.row || m1.col != m2.col)
        {
            throw invalid_argument("The size of the matrixes have to be the same");
        }
        double sum_m1 = 0;
        double sum_m2 = 0;
        for (unsigned int i = 0; i < m1.row; i++)
        {
            for (unsigned int j = 0; j < m1.col; j++)
            {
                sum_m1 += m1.myMatrix[i][j];
            }
        }
        for (unsigned int i = 0; i < m2.row; i++)
        {
            for (unsigned int j = 0; j < m2.col; j++)
            {
                sum_m2 += m2.myMatrix[i][j];
            }
        }
        return sum_m1 < sum_m2;
    }

    bool operator<=(const Matrix &m1, const Matrix &m2)
    {
        if (m1.row != m2.row || m1.col != m2.col)
        {
            throw invalid_argument("The size of the matrixes have to be the same");
        }
        double sum_m1 = 0;
        double sum_m2 = 0;
        for (unsigned int i = 0; i < m1.row; i++)
        {
            for (unsigned int j = 0; j < m1.col; j++)
            {
                sum_m1 += m1.myMatrix[i][j];
            }
        }
        for (unsigned int i = 0; i < m2.row; i++)
        {
            for (unsigned int j = 0; j < m2.col; j++)
            {
                sum_m2 += m2.myMatrix[i][j];
            }
        }
        return sum_m1 <= sum_m2;
    }

    bool operator>(const Matrix &m1, const Matrix &m2)
    {
        if (m1.row != m2.row || m1.col != m2.col)
        {
            throw invalid_argument("The size of the matrixes have to be the same");
        }
        double sum_m1 = 0;
        double sum_m2 = 0;
        for (unsigned int i = 0; i < m1.row; i++)
        {
            for (unsigned int j = 0; j < m1.col; j++)
            {
                sum_m1 += m1.myMatrix[i][j];
            }
        }
        for (unsigned int i = 0; i < m2.row; i++)
        {
            for (unsigned int j = 0; j < m2.col; j++)
            {
                sum_m2 += m2.myMatrix[i][j];
            }
        }
        return sum_m1 > sum_m2;
    }

    bool operator>=(const Matrix &m1, const Matrix &m2)
    {
        if (m1.row != m2.row || m1.col != m2.col)
        {
            throw invalid_argument("The size of the matrixes have to be the same");
        }
        double sum_m1 = 0;
        double sum_m2 = 0;
        for (unsigned int i = 0; i < m1.row; i++)
        {
            for (unsigned int j = 0; j < m1.col; j++)
            {
                sum_m1 += m1.myMatrix[i][j];
            }
        }
        for (unsigned int i = 0; i < m2.row; i++)
        {
            for (unsigned int j = 0; j < m2.col; j++)
            {
                sum_m2 += m2.myMatrix[i][j];
            }
        }
        return sum_m1 >= sum_m2;
    }

    bool operator==(const Matrix &m1, const Matrix &m2)
    {
        if (m1.row != m2.row || m1.col != m2.col)
        {
            throw invalid_argument("The size of the matrixes have to be the same");
        }
        for (unsigned int i = 0; i < m1.row; i++)
        {
            for (unsigned int j = 0; j < m2.col; j++)
            {
                if (m1.myMatrix[i][j] != m2.myMatrix[i][j])
                {
                    return false;
                }
            }
        }
        return true;
    }

    bool operator!=(const Matrix &m1, const Matrix &m2)
    {
        if (m1.row != m2.row || m1.col != m2.col)
        {
            throw invalid_argument("The size of the matrixes have to be the same");
        }
        return (!(operator==(m1, m2)));
    }

    Matrix operator++(Matrix &m)
    {
        for (unsigned int i = 0; i < m.row; i++)
        {
            for (unsigned int j = 0; j < m.col; j++)
            {
                m.myMatrix[i][j]++;
            }
        }
        return m;
    }

    Matrix operator--(Matrix &m)
    {
        for (unsigned int i = 0; i < m.row; i++)
        {
            for (unsigned int j = 0; j < m.col; j++)
            {
                m.myMatrix[i][j]--;
            }
        }
        return m;
    }

    Matrix operator++(Matrix &m, int num)
    {
        Matrix cpy(m.row, m.col);
        for (unsigned int i = 0; i < m.row; i++)
        {
            for (unsigned int j = 0; j < m.col; j++)
            {
                cpy.myMatrix[i][j] = m.myMatrix[i][j];
                m.myMatrix[i][j]++;
            }
        }
        return cpy;
    }

    Matrix operator--(Matrix &m, int num)
    {
        Matrix cpy(m.row, m.col);
        for (unsigned int i = 0; i < m.row; i++)
        {
            for (unsigned int j = 0; j < m.col; j++)
            {
                cpy.myMatrix[i][j] = m.myMatrix[i][j];
                m.myMatrix[i][j]--;
            }
        }
        return cpy;
    }

    istream &operator>>(istream &in, Matrix &m)
    {
        vector<string> rows_vector;
        size_t row = 0;
        size_t col = 0;
        size_t space = 0;
        string input;
        string tmp;
        getline(in, input);

        tmp = "";
        for (unsigned int i = 0; i < input.size(); i++)
        {
            tmp += input[i];
            if (input[i] == ']')
            {
                rows_vector.push_back(tmp);
                i += 2;
                tmp = "";
            }
        }
        vector<double> all_nums;
        for (unsigned int i = 0; i < rows_vector.size(); i++)
        {
            string str = rows_vector[i];
            if (str[0] != '[' || str[str.length() - 1] != ']')
            {
                throw invalid_argument("Invalid syntax");
            }
            if (i == 0)
            {
                tmp = "";
                for (unsigned int j = 1; j < str.length() - 1; j++)
                {
                    if (str[j] == ' ')
                    {
                        space++;
                        double num = stod(tmp);
                        tmp = "";
                        all_nums.push_back(num);
                    }
                    else
                    {
                        tmp += str[j];
                        if (j == str.length() - 2)
                        {
                            double num = stod(tmp);
                            all_nums.push_back(num);
                            space++;
                        }
                    }
                }
                col = space;
            }
            else
            {
                tmp = "";
                space = 0;
                for (unsigned int j = 1; j < str.length() - 1; j++)
                {
                    if (str[j] == ' ')
                    {
                        space++;
                        double num = stod(tmp);
                        tmp = "";
                        all_nums.push_back(num);
                    }
                    else
                    {
                        tmp += str[j];
                        if (j == str.length() - 2)
                        {
                            double num = stod(tmp);
                            all_nums.push_back(num);
                            space++;
                        }
                    }
                }
                if (space != col)
                {
                    throw invalid_argument("The rows shoulde be the same");
                }
            }
        }

        m.myMatrix.clear();
        m.row = rows_vector.size();
        m.col = col;

        size_t num1 = 0;
        for (size_t i = 0; i < m.row; i++)
        {
            vector<double> vec;
            for (size_t j = 0; j < m.col; j++)
            {
                vec.push_back(all_nums[num1++]);
            }
            m.myMatrix.push_back(vec);
        }
        return in;
    }

    ostream &operator<<(ostream &out, const Matrix &m)
    {
        for (unsigned int i = 0; i < m.row; i++)
        {
            out << "[";
            for (unsigned int j = 0; j < m.col; j++)
            {
                out << m.myMatrix[i][j];
                if (j == m.col - 1)
                {
                    out << "]";
                }
                else
                {
                    out << " ";
                }
            }
            if (i != m.row - 1)
            {
                out << endl;
            }
        }
        return out;
    }

}