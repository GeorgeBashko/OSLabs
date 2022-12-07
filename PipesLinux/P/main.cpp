#include <iostream>
#include <sstream>
#include <cmath>

int main() {
    std::string str;
    getline(std::cin, str);
    std::stringstream ss(str);
    int value;
    std::string result;
    while (ss >> value) {
        result.append(std::to_string(std::pow(value,3))+" ");
    }
    std::cout << result<<"\n";
    return 0;
}
