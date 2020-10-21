#include<iostream>
#include<string>
#include<vector>

typedef std::vector<std::vector<int>> Smegn;

struct InputData {
    int numberVertices;
    int numberPaths;
    int pathLength;
    std::vector<std::string> paths;
};

InputData ReadInput(std::istream& inputStream = std::cin);

Smegn ConvertToSmegn(const std::vector<std::string>& paths, int numberVertices);

Smegn MultiplyMatrices(const Smegn& firstMatrix, const Smegn& secondMatrix, int mod);

Smegn BinpowMatrices(const Smegn& matrix, int power, int mod);

int CountNumberPaths(const std::vector<std::string>& paths, int pathLength, int numberVertices, int startVertex, int mod);

void WriteResult(int result, std::ostream& outputStream = std::cout);

int main() {
    InputData inputData = ReadInput();
    const int mod = 1000000007;
    int result = CountNumberPaths(inputData.paths, inputData.pathLength, inputData.numberVertices, 0, mod);
    WriteResult(result);
    return 0;
}