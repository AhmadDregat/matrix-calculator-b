#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

namespace zich{

    class Matrix{
        private:

            int row, col;
            vector<vector<double>> myMatrix;

        public:
            /*
            Constructor
            */
            Matrix(vector<double> mat, int row, int col);
            ~Matrix();
            Matrix(int row, int col);

            /*
            Functions for oparetion (+) 
            */
            friend Matrix operator+(const Matrix& m1, const Matrix& m2);
            friend void operator+=(Matrix& m1, const Matrix& m2);
            friend Matrix operator+(const Matrix& m1); //Unari - copy the matrix

            friend Matrix operator+(const Matrix& m, double scalar);
            friend Matrix operator+(double scalar, const Matrix& m);
            friend void operator+=(Matrix& m, double scalar);

            /*
            Functions for oparetion (-) 
            */
            friend Matrix operator-(const Matrix& m1, const Matrix& m2);
            friend void operator-=(Matrix& m1, const Matrix& m2);
            friend Matrix operator-(const Matrix& m1); //Unari *(-1)

            friend Matrix operator-(const Matrix& m, double scalar);
            friend Matrix operator-(double scalar, const Matrix& m);
            friend void operator-=(Matrix& m, double scalar);

            /*
            Functions for oparetion (*) 
            */           
            friend Matrix operator*(const Matrix& m1, const Matrix& m2);
            friend void operator*=(Matrix& m1, const Matrix& m2);

            friend Matrix operator*(const Matrix& m, double scalar);
            friend Matrix operator*(double scalar, const Matrix& m);
            friend void operator*=(Matrix& m, int scalar);
            
            /*
            Functions for comparisons
            */
            friend bool operator<(const Matrix& m1, const Matrix& m2);
            friend bool operator<=(const Matrix& m1, const Matrix& m2);
            friend bool operator>(const Matrix& m1, const Matrix& m2);
            friend bool operator>=(const Matrix& m1, const Matrix& m2);
            friend bool operator==(const Matrix& m1, const Matrix& m2);
            friend bool operator!=(const Matrix& m1, const Matrix& m2);

            /*
            Functions for ++1 / --1
            */
            friend Matrix operator++(Matrix& m); //opertion ++matrix 
            friend Matrix operator--(Matrix& m); //opertion --matrix
            friend Matrix operator++(Matrix& m, int num); //opertion matrix++
            friend Matrix operator--(Matrix& m, int num); //opertion matrix--

            /*
            Functions for input and output 
            */
            friend istream& operator>>(istream&, Matrix&);
            friend ostream& operator<<(ostream&, const Matrix&);      
    };
}