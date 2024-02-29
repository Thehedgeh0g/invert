#include <iostream>
#include <fstream>
#include <iomanip>

void printMatrix(double matrix[3][3])
{
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            std::cout << std::fixed << std::setprecision(3) << matrix[i][j] << "\t";
        }
        std::cout << std::endl;
    }
}

void invertMatrix(double matrix[3][3], double result[3][3])
{
    double det = matrix[0][0] * (matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1]) -
                 matrix[0][1] * (matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0]) +
                 matrix[0][2] * (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0]);

    if (det == 0)
    {
        std::cout << "\n"
                "The matrix is singular; there is no inverse matrix.\n";
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

int Invert(const std::string& inputFilePath, double result[3][3])
{
    std::ifstream inputFile(inputFilePath);
    if (!inputFile.is_open())
    {
        std::cout << "Can not open file " << inputFilePath << std::endl;
        return EXIT_FAILURE;
    }

    double matrix[3][3];

    for (auto& i : matrix)
    {
        for (double& j : i)
        {
            if (!(inputFile >> j))
            {
                std::cout << "Can not read matrix from file\n";
                return EXIT_FAILURE;
            }
        }
    }

    inputFile.close();

    invertMatrix(matrix, result);
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << "Invalid argument count \n " <<
                "Usage: replace.exe " << argv[0] << " <matrix file>\n";
        return EXIT_FAILURE;
    }

    double result[3][3];

    if (Invert(argv[1], result) == EXIT_FAILURE)
    {
        return EXIT_FAILURE;
    }

    std::cout << "Inverted matrix:\n";
    printMatrix(result);

    return 0;
}
