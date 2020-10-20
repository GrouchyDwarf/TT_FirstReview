#include<iostream>
#include<string>
#include<vector>

typedef std::vector<std::vector<int>> Smegn;

std::vector<std::string> ReadInput(int& matrSize, int& n, int& pathLength, std::istream& inputStream = std::cin);

Smegn ConvertToSmegn(const std::vector<std::string>& input, int matrSize);

Smegn MultiplyMatrices(const Smegn& a, const Smegn& b, int mod);

Smegn BinpowMatrices(const Smegn& a, int n, int mod);

int64_t CountNumberPaths(const Smegn& matrix, int startVertex, int mod);

void WriteResult(int result, std::ostream& outputStream = std::cout);

int main() {
    int matrSize, n, pathLength;
    std::vector<std::string> paths = ReadInput(matrSize, n, pathLength);
    Smegn matrix = ConvertToSmegn(paths, matrSize);
    const int mod = 1000000007;
    matrix = BinpowMatrices(matrix, pathLength, mod);
    int result = CountNumberPaths(matrix, 0, mod);
    WriteResult(result);
    return 0;
}