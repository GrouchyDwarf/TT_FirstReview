#include <iostream>
#include <string>
#include <vector>

typedef std::vector<std::vector<int>> Matrix;

const int MODULUS = 1000000007;

struct Edge {
    int outgoingVertex;
    int incomingVertex;
};

struct GraphParameters {
    int numberVertices;
    int pathLength;
    std::vector<Edge> edges;
};

GraphParameters ReadInput(std::istream& inputStream = std::cin);

Matrix ConvertEdgesToAdjacencyMatrix(const std::vector<Edge>& edges, const int numberVertices);

Matrix MultiplyMatrices(const Matrix& firstMatrix, const Matrix& secondMatrix);

Matrix RaiseMatrixToPower(const Matrix& matrix, const int power);

int CountNumberPaths(const GraphParameters& graphParameters, const int startVertex);

void WriteResult(const int result, std::ostream& outputStream = std::cout);

int main() {
    const GraphParameters graphParameters = ReadInput();
    const int numberPathsFromFirstVertex = CountNumberPaths(graphParameters, 0);
    WriteResult(numberPathsFromFirstVertex);
    return 0;
}