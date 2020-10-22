#include<iostream>
#include<string>
#include<vector>

typedef std::vector<std::vector<int>> Matrix;

struct Edge {
    int outgoingVertex;
    int incomingVertex;
};

struct InputData {
    int numberVertices;
    int pathLength;
    std::vector<Edge> edges;
};

InputData ReadInput(std::istream& inputStream = std::cin);

Matrix ConvertEdgesToAdjacencyMatrix(const std::vector<Edge>& edges, int numberVertices);

const int module = 1000000007;

Matrix MultiplyMatrices(const Matrix& firstMatrix, const Matrix& secondMatrix);

Matrix RaiseMatrixToPower(const Matrix& matrix, int power);

int CountNumberPaths(InputData inputData, int startVertex);

void WriteResult(int result, std::ostream& outputStream = std::cout);

int main() {
    InputData inputData = ReadInput();
    const int result = CountNumberPaths(inputData, 0);
    WriteResult(result);
    return 0;
}