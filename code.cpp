#include <iostream>
#include <string>
#include <vector>

typedef std::vector<std::vector<int>> Matrix;

const int MODULUS = 1000000007;
const int INDEXING_SHIFT = 1;

struct Edge {
    int outgoingVertex;
    int incomingVertex;
};

struct GraphParameters {
    int numberVertices;
    int pathLength;
    std::vector<Edge> edges;
};

GraphParameters ReadInput(std::istream& inputStream = std::cin) {
    int numberEdges;
    GraphParameters graphParameters;
    inputStream >> graphParameters.numberVertices;
    inputStream >> numberEdges;
    inputStream >> graphParameters.pathLength;
    if (numberEdges < 0) {
        throw std::invalid_argument("Number of edges can't be negative!!!");
    }
    graphParameters.edges.resize(numberEdges);
    for (int i = 0; i < numberEdges; ++i) {
        inputStream >> graphParameters.edges[i].outgoingVertex;
        inputStream >> graphParameters.edges[i].incomingVertex;
    }
    return graphParameters;
}

Matrix ConvertEdgesToAdjacencyMatrix(const std::vector<Edge>& edges, const int numberVertices) {
    Matrix matrix(numberVertices, std::vector<int>(numberVertices, 0));
    for (int i = 0; i < edges.size(); ++i) {
        if (edges[i].outgoingVertex < 0 || edges[i].outgoingVertex >= numberVertices) {
            throw std::invalid_argument("Such outgoing vertex doesn't exist!!!");
        }
        if (edges[i].incomingVertex < 0 || edges[i].incomingVertex >= numberVertices) {
            throw std::invalid_argument("Such incoming vertex doesn't exist!!!");
        }
        matrix[edges[i].outgoingVertex][edges[i].incomingVertex] += 1;
    }
    return matrix;
}

Matrix MultiplyMatrices(const Matrix& firstMatrix, const Matrix& secondMatrix) {
    if (firstMatrix[0].size() != secondMatrix.size()) {
        throw std::invalid_argument("Incompatible matrix sizes!!!");
    }
    Matrix multipliedMatrix(firstMatrix.size());
    for (int i = 0; i < firstMatrix.size(); ++i) {
        multipliedMatrix[i].resize(secondMatrix[0].size());
        for (int j = 0; j < secondMatrix[0].size(); ++j) {
            multipliedMatrix[i][j] = 0;
            for (int k = 0; k < firstMatrix[0].size(); ++k) {
                //does not always fit into long
                multipliedMatrix[i][j] = (multipliedMatrix[i][j] +
                    static_cast<int64_t>(firstMatrix[i][k]) * secondMatrix[k][j])
                    % MODULUS;
            }
        }
    }
    return multipliedMatrix;
}

Matrix RaiseMatrixToPower(const Matrix& matrix, const int power) {
    if (power == 0) {
        Matrix identityMatrix(matrix.size());
        for (int i = 0; i < matrix.size(); ++i) {
            identityMatrix[i].resize(matrix[i].size());
            for (int j = 0; j < matrix[i].size(); ++j) {
                if (i == j) {
                    identityMatrix[i][j] = 1;
                } else {
                    identityMatrix[i][j] = 0;
                }
            }
        }
        return identityMatrix;
    }
    if (power % 2 == 0) {
        const Matrix multipliedMatrix = MultiplyMatrices(matrix, matrix);
        const Matrix raisedToPowerMatrix = RaiseMatrixToPower(multipliedMatrix, power / 2);
        return raisedToPowerMatrix;
    } else {
        const Matrix raisedToPowerMatrix = RaiseMatrixToPower(matrix, power - 1);
        const Matrix multipliedMatrix = MultiplyMatrices(raisedToPowerMatrix, matrix);
        return multipliedMatrix;
    }
}

int CountNumberPaths(GraphParameters graphParameters, const int startVertex) {
    if (graphParameters.numberVertices < 1) {
        throw std::invalid_argument("Number of vertices can't be less than one - labyrinth does not exist!!!");
    }
    if (graphParameters.pathLength < 0) {
        throw std::invalid_argument("Path length can't be negative!!!");
    }
    for (int i = 0; i < graphParameters.edges.size(); ++i) {
        graphParameters.edges[i].outgoingVertex -= INDEXING_SHIFT;
        graphParameters.edges[i].incomingVertex -= INDEXING_SHIFT;
        if (graphParameters.edges[i].outgoingVertex < 0 || graphParameters.edges[i].incomingVertex < 0) {
            throw std::invalid_argument("Vertex can't be negative!!!");
        }
    }
    Matrix matrix = ConvertEdgesToAdjacencyMatrix(graphParameters.edges, graphParameters.numberVertices);
    matrix = RaiseMatrixToPower(matrix, graphParameters.pathLength);
    int64_t numberPaths = 0;
    for (int i = 0; i < matrix[startVertex].size(); ++i) {
        numberPaths = (numberPaths + matrix[startVertex][i]) % MODULUS;
    }
    return numberPaths;
}

void WriteResult(const int result, std::ostream& outputStream = std::cout) {
    outputStream << result << "\n";
}

int main() {
    try {
        const GraphParameters graphParameters = ReadInput();
        const int numberPathsFromFirstVertex = CountNumberPaths(graphParameters, 0);
        WriteResult(numberPathsFromFirstVertex);
    }
    catch (const std::exception& e) {
        std::cerr << "Caught:" << e.what() << std::endl;
        return -1;
    }
    return 0;
}