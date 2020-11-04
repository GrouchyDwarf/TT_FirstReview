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

GraphParameters ReadInput(std::istream& inputStream = std::cin) {
    int numberEdges;
    GraphParameters graphParameters;
    inputStream >> graphParameters.numberVertices;
    inputStream >> numberEdges;
    inputStream >> graphParameters.pathLength;
    inputStream.ignore();
    try {
        if (numberEdges < 0) {
            throw -1;
        }
    }
    catch (int a) {
        std::cerr << "Number of edges can't be negative!!!\n";
        exit(-1);
    }
    graphParameters.edges.resize(numberEdges);
    for (int i = 0; i < numberEdges; ++i) {
        inputStream >> graphParameters.edges[i].outgoingVertex;
        inputStream >> graphParameters.edges[i].incomingVertex;
        
        try {
            if (--graphParameters.edges[i].outgoingVertex < 0 || --graphParameters.edges[i].incomingVertex < 0) {
                throw - 1;
            }
        }
        catch (int a) {
            std::cerr << "Vertex can't be less than one!!!\n";
            exit(-1);
        }
        inputStream.ignore();
    }
    return graphParameters;
}

Matrix ConvertEdgesToAdjacencyMatrix(const std::vector<Edge>& edges, const int numberVertices) {
    Matrix matrix(numberVertices, std::vector<int>(numberVertices, 0));
    for (int i = 0; i < edges.size(); ++i) {
        matrix[edges[i].outgoingVertex][edges[i].incomingVertex] += 1;
    }
    return matrix;
}

Matrix MultiplyMatrices(const Matrix& firstMatrix, const Matrix& secondMatrix) {
    try {
        if (firstMatrix[0].size() != secondMatrix.size()) {
            throw -1;
        }
    } catch (int a) {
        std::cerr << "Incompatible matrix sizes!!!\n";
        exit(-1);
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
        Matrix E(matrix.size());
        for (int i = 0; i < matrix.size(); ++i) {
            E[i].resize(matrix[i].size());
            for (int j = 0; j < matrix[i].size(); ++j) {
                if (i == j) {
                    E[i][j] = 1;
                } else {
                    E[i][j] = 0;
                }
            }
        }
        return E;
    }
    if (power % 2 == 0) {
        return RaiseMatrixToPower(MultiplyMatrices(matrix, matrix), power / 2);
    } else {
        return MultiplyMatrices(RaiseMatrixToPower(matrix, power - 1), matrix);
    }
}

int CountNumberPaths(const GraphParameters& graphParameters, const int startVertex) {
    try {
        if (graphParameters.numberVertices < 1) {
            throw -1;
        }
        if (graphParameters.pathLength < 0) {
            throw -2;
        }
    }
    catch(int a) {
        if (a == -1) {
            std::cerr << "Number of vertices can't be less than one - labyrinth does not exist!!!";
            exit(-1);
        }
        else if (a == -2) {
            std::cerr << "Path length can't be negative!!!";
            exit(-1);
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
    const GraphParameters graphParameters = ReadInput();
    const int numberPathsFromFirstVertex = CountNumberPaths(graphParameters, 0);
    WriteResult(numberPathsFromFirstVertex);
    return 0;
}