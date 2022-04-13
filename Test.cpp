#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "Matrix.hpp"
#include "doctest.h"
#include <ctime>

using namespace std;
using namespace zich;

TEST_CASE("oparetion (+)")
{
    for (double i = 1; i < 100; i++)
    {
        vector<double> arr = {i, 0, i, 0, i, 0, i, 0, i};
        Matrix mat1{arr, 3, 3};
        CHECK(mat1 == mat1);
    }

    for (double i = 1; i < 100; i++)
    {
        vector<double> arr1 = {i, i, i, i};
        vector<double> arr2 = {i + 6, i + 6, i + 6, i + 6};
        vector<double> arr3 = {5, 5, 5, 5};
        Matrix mat1{arr1, 2, 2};
        Matrix mat2{arr2, 2, 2};
        Matrix mat3{arr3, 2, 2};
        CHECK(mat3 == mat1 + 4);    // Matrix + scalar
        CHECK(mat2 == 4 + mat1);    // scalar + Matrix
        CHECK(mat2 + mat3 == mat3); // Matrix + Matrix
    }

    for (double i = 1; i < 100; i++)
    {
        vector<double> arr1 = {i, i, i, i};
        vector<double> arr2 = {i + 6, i + 6, i + 6, i + 6};
        vector<double> arr3 = {5, 5, 5, 5};
        Matrix mat1{arr1, 2, 2};
        Matrix mat2{arr2, 2, 2};
        Matrix mat3{arr3, 2, 2};
        mat1 += 4;
        CHECK(mat1 == mat2);
        mat1 += mat3;
    }
}

TEST_CASE("oparetion (*)")
{

    for (double i = 0; i < 100; i++)
    {
        vector<double> arr1 = {0, 0, i, 0, i, 0, i, 0, 0};
        vector<double> arr2 = {0, 0, i * i, 0, i * i, 0, i * i, 0, 0};
        vector<double> arr3 = {0, 0, i * 5, 0, i * 5, 0, i * 5, 0, 0};
        Matrix mat1{arr1, 3, 3};
        Matrix mat2{arr2, 3, 3};
        Matrix mat3{arr3, 3, 3};

        CHECK(mat1 * mat3 == mat3); // Martix * Matrix
        CHECK(mat2 * 5 == mat3);    // Martix * scalar
        CHECK(5 * mat2 == mat3);    // scalar * Martix
    }
    for (double i = 0; i < 100; i++)
    {
        vector<double> arr1 = {0, 0, i, 0, i, 0, i, 0, 0};
        vector<double> arr2 = {1, 1, 1, 1, 1, 1, 1, 1, 1};
        Matrix mat1{arr1, 3, 3};
        Matrix mat2{arr2, 3, 3};
        mat1 *= 5;
        CHECK(mat1 == mat1 * 5);
        mat1 *= mat2;
        CHECK(mat1 * mat2 == mat1);
    }
}

TEST_CASE("oparetion (-)")
{

    for (double i = 1; i < 100; i++)
    {

        vector<double> arr1 = {1, 1, 1, 1, 1, 1, 1, 1, 1};
        vector<double> arr2 = {i - 4, i - 4, i - 4, i - 4, i - 4, i - 4, i - 4, i - 4, i - 4};
        vector<double> arr3 = {i - 5, i - 5, i - 5, i - 5, i - 5, i - 5, i - 5, i - 5, i - 5};
        Matrix mat1{arr1, 3, 3};
        Matrix mat2{arr2, 3, 3};
        Matrix mat3{arr3, 2, 3};
        mat1 -= 3;
        CHECK(mat1 == mat2);
        mat1 -= mat2;
        CHECK(mat1 == mat3);
    }

    for (double i = 10; i < 100; i++)
    {
        vector<double> arr = {i, i, i, i};
        vector<double> arr1 = {i - 2, i - 2, i - 2, i - 2};
        vector<double> arr2 = {10, 10, 10, 10};
        vector<double> arr3 = {i - 10, i - 10, i - 10, i - 10};
        Matrix mat{arr, 2, 2};
        Matrix mat1{arr1, 2, 2};
        Matrix mat2{arr2, 2, 2};
        Matrix mat3{arr2, 2, 2};
        CHECK(mat1 == mat - 2);
        CHECK(mat1 == 2 - mat);
        CHECK(mat - mat2 == mat3);
    }

    for (double i = 0; i < 100; i++)
    {
        vector<double> arr = {i, 0, i, 0, i, 0, i, 0, i};
        Matrix mat{arr, 3, 3};
        CHECK(mat == -(mat));
    }
}

TEST_CASE("check comparisons")
{
    for (double i = 0; i < 100; i++)
    {
        vector<double> arr1 = {i, i, i, i};
        vector<double> arr2 = {i, i, i, i + 1};
        vector<double> arr3 = {i, i, i + 1, i + 1};

        Matrix mat1{arr1, 2, 2};
        Matrix mat2{arr2, 2, 2};
        Matrix mat3{arr3, 2, 2};

        CHECK(mat1 < mat2);
        CHECK(mat1 < mat3);
        CHECK(mat2 >= mat2);
        CHECK(mat2 <= mat3);
        CHECK(mat3 < mat1);
        CHECK(mat3 != mat2);
        CHECK_FALSE(mat3 >= mat1);
        CHECK_FALSE(mat3 >= mat2);

        CHECK_FALSE(mat1 > mat2);
    }
}

TEST_CASE("check output")
{
    vector<double> arr = {2.8, 5.6, 4.6, 8.9};
    Matrix mat{arr, 2, 2};
    CHECK_NOTHROW(cout << mat << endl);
}

TEST_CASE("wrong size matrix - input, +, -, * ")
{
    srand((unsigned)time(0));
    double randomNum;
    for (double i = 1; i < 50; i++)
    {

        randomNum = (double)(rand() % 100) + 6;

        vector<double> arr = {i, 0, i, 0};
        vector<double> arr1 = {i, 0, i, 0, 1, i, 0, 1, i};
        CHECK_THROWS(Matrix mat(arr, 1, 1));
        CHECK_THROWS(Matrix mat(arr, 0, 6));
        if (randomNum != randomNum)
        {
            CHECK_THROWS(Matrix mat(arr, randomNum, randomNum));
        }
        if (randomNum != randomNum)
        {
            CHECK_THROWS(Matrix mat(arr, randomNum, randomNum));
        }
        if (randomNum != randomNum)
        {
            Matrix mat(arr, randomNum, randomNum);
            Matrix mat1(arr1, randomNum, randomNum);
            CHECK_THROWS(mat * randomNum);
        }
        if (randomNum != randomNum)
        {
            Matrix mat(arr, randomNum, randomNum);
            Matrix mat1(arr1, randomNum, randomNum);
            CHECK_THROWS(mat + mat1);
            CHECK_THROWS(mat - mat1);
        }
    }
}
