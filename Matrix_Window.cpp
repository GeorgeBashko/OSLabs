#include <iostream>
#include <vector>
#include <windows.h>
#include <mutex>
#include <ctime>
#include <map>


struct ThreadParams {
    std::vector<std::vector<int>>& M1;
    std::vector<std::vector<int>>& M2;
    std::vector<std::vector<int>>& M3;
    int start1, start2, mul_st, count;
    ThreadParams(std::vector<std::vector<int>>& m1,
        std::vector<std::vector<int>>& m2,
        std::vector<std::vector<int>>& m3,
        int i, int j, int k, int count) :
        M1(m1), M2(m2), M3(m3), start1(i), start2(j), mul_st(k), count(count) {}
};

std::vector<std::vector<int>> createMatrix(int size) {
    std::vector<std::vector<int>> res(size);
    for (auto& x : res) {
        for (size_t i = 0; i < size; ++i) {
            int num = (rand() % 20);
            x.push_back(num);
        }
    }
    return res;
}

DWORD WINAPI multiplyBlocks(LPVOID params) {
    ThreadParams p = *(ThreadParams*)params;
    for (size_t i = p.start1; i < p.start1 + p.count; i++) {
        for (size_t j = p.start2; j < p.start2 + p.count; j++) {
            int sum = 0;
            for (size_t k = 0; k < p.count; k++)
                sum += p.M1[i][p.mul_st + k] * p.M2[p.mul_st + k][j];
            HANDLE mutex = CreateMutex(NULL, TRUE, NULL);
            p.M3[i][j] += sum;
            ReleaseMutex(mutex);
        }
    }
    return 0;
}

unsigned int multiply_matrix_with_threads(std::vector<std::vector<int>>& A,
    std::vector<std::vector<int>>& B,
    std::vector<std::vector<int>>& D,
    unsigned int blocks) {
    size_t size = A.size();
    size_t count = size / blocks;
    short thread_count = 0;
    std::vector<HANDLE> threads;;
    for (size_t i = 0; i < size; i += count) {
        for (size_t j = 0; j < size; j += count) {
            for (size_t k = 0; k < size; k += count) {
                ThreadParams* p = new ThreadParams(A, B, D, i, j, k, count);
                HANDLE thread = CreateThread(nullptr, 0, multiplyBlocks, p, 0, nullptr);
                threads.push_back(thread);
                thread_count++;
            }
        }
    }
    WaitForMultipleObjects(threads.size(), threads.data(), TRUE, INFINITE);
    return thread_count;
}

std::map<unsigned int, std::pair<unsigned int, unsigned int>> experimentThreads(
    std::vector<std::vector<int>>& A,
    std::vector<std::vector<int>>& B,
    std::vector<std::vector<int>>& D) {
    std::map<unsigned int, std::pair<unsigned int, unsigned int>> res;
    size_t N = A.size();
    for (size_t i = 1; i <= N; i++) {
        if (N % i != 0) continue;
        std::vector<int> temp(N, 0);
        D = std::vector<std::vector<int>>(N, temp);
        unsigned int one = clock();
        auto threads = multiply_matrix_with_threads(A, B, D, i);
        unsigned int two = clock();
        res[i] = std::make_pair(threads, two - one);
    }
    return res;
}

unsigned int experiment_basic_multiplication(std::vector<std::vector<int>>& A,
    std::vector<std::vector<int>>& B,
    std::vector<std::vector<int>>& D) {
    unsigned int start = clock();
    ThreadParams* p = new ThreadParams(A, B, D, 0, 0, 0, A.size());
    multiplyBlocks(p);
    unsigned int end = clock();
    return end - start;
}

void print_map(std::map<unsigned int, std::pair<unsigned int, unsigned int>> map) {
    auto it = map.begin();
    while (it != map.end()) {
        std::cout << "Blocks: " << it->first << ", time: "
            << it->second.second << ", threads: " << it->second.first << '\n';
        it++;
    }
}

int main() {
    srand(time(nullptr));
    int n = 10;
    std::vector<int> temp(n, 0);
    std::vector<std::vector<int>> a = createMatrix(n), b = createMatrix(n), d(n, temp);
    std::cout << "Basic multiplication time: " << experiment_basic_multiplication(a, b, d) << '\n';
    std::vector<std::vector<int>> dest(n, temp);
    print_map(experimentThreads(a, b, dest));
    return 0;
}
