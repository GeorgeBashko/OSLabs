#include <iostream>
#include <sstream>

int main() {
    std::string str;
    getline(std::cin, str);
    std::stringstream ss(str);
    int value;
    int sum=0;
    while (ss >> value) {
        sum+=value;
    }
    std::cout << sum << "\n";
    return 0;
}
