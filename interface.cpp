#include<iostream>
#include<string>
#include<vector>

typedef std::vector<std::vector<int>> Smegn;

Smegn convertInputToSmegn(const std::vector<std::string>& input, int matrSize);

Smegn multiplyMatrices(const Smegn& a, const Smegn& b, int mod);

Smegn binpowMatrices(const Smegn& a, int n, int mod);

int64_t countNumberPaths(const Smegn& matrix, int startVertex, int mod);

int main() {
    int matrSize, n, pathLength;
    std::cin >> matrSize;
    std::cin >> n;
    std::cin >> pathLength;
    std::cin.ignore(1, '\n');

    std::vector<std::string> input(n);
    for (int i = 0; i < n; ++i) {
        std::getline(std::cin, input[i]);
    }
    Smegn result = convertInputToSmegn(input, matrSize);

    const int mod = 1000000007;
    result = binpowMatrices(result, pathLength, mod);
    std::cout << countNumberPaths(result, 0, mod) << std::endl;
    return 0;
}