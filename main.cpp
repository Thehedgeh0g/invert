#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

void printMatrix(double matrix[3][3])
{
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            cout << fixed << setprecision(3) << matrix[i][j] << "\t";
        }
        cout << endl;
    }
}

void invertMatrix(double matrix[3][3], double result[3][3])
{
    double det = matrix[0][0] * (matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1]) -
                 matrix[0][1] * (matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0]) +
                 matrix[0][2] * (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0]);

    if (det == 0)
    {
        cerr << "\n"
                "The matrix is singular; there is no inverse matrix." << endl;
        exit(EXIT_FAILURE);
    }

    double invDet = 1.0 / det;

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            result[i][j] = ((matrix[(i + 1) % 3][(j + 1) % 3] * matrix[(i + 1) % 3][(j + 2) % 3]) -
                            (matrix[(i + 2) % 3][(j + 1) % 3] * matrix[(i + 2) % 3][(j + 2) % 3])) * invDet;
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cerr << "Invalid argument count \n " <<
                "Usage: replace.exe " << argv[0] << " <matrix file>" << endl;
        return EXIT_FAILURE;
    }

    ifstream inputFile(argv[1]);
    if (!inputFile.is_open())
    {
        cerr << "Can not open file " << argv[1] << endl;
        return EXIT_FAILURE;
    }

    double matrix[3][3];
    double result[3][3];

    for (auto& i : matrix)
    {
        for (double& j : i)
        {
            if (!(inputFile >> j))
            {
                cerr << "Can not read matrix from file" << endl;
                return EXIT_FAILURE;
            }
        }
    }

    inputFile.close();

    invertMatrix(matrix, result);

    cout << "Inverted matrix:" << endl;
    printMatrix(result);

    return 0;
}
