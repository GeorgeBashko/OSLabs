#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <thread>
#include <mutex>
#include <valarray>
#include "Matrix_buffered_channel.h"

std::mutex g_lock;

void readMatrixFromFile(std::vector< std::vector<int>> &m1, std::string file)
{
    std::ifstream input(file);
    std::string row;
    int k = 0;
    while (getline(input,row))
    {
        std::stringstream ss;
        ss.str(row);
        std::string value;

        while (ss >> value)
        {
            m1[k].push_back(std::stoi(value));
        }
        ++k;
    }
}
void multiplyBlocksWithChannel(const std::vector <std::vector <int>>& m1, const std::vector <std::vector <int>>& m2, std::vector < std::vector <int>>& resM, std::pair<int, int>& pair, int matrixSize, int blockSize)
{
    for (int i = pair.first; i < std::min(pair.first + blockSize, matrixSize); ++i)
        for (int j = pair.second; j < std::min(pair.second + blockSize, matrixSize); ++j)
            for (int k = 0; k < matrixSize; ++k)
            {
                g_lock.lock();
                resM[i][j] += m1[i][k] * m2[k][j];
                g_lock.unlock();
            }
}

void multiplyWithChannel(const std::vector <std::vector <int>>& m1, const std::vector <std::vector <int>>& m2, std::vector < std::vector <int>>& resM, int matrixSize, int blockSize, BufferedChannel < std::pair<int, int>>& channel)
{
    std::pair<std::pair<int, int>, bool> pair = channel.recv();
    while (pair.second)
    {
        multiplyBlocksWithChannel(m1, m2, resM, pair.first, matrixSize, blockSize);
        pair = channel.recv();
    }
}

void multiply(const std::vector <std::vector <int>>& m1, const std::vector <std::vector <int>>& m2, std::vector < std::vector <int>>& resM, int matrixSize, int blockSize, int countThreads)
{
    std::vector<std::thread> threads;
    int size = std::pow(matrixSize % blockSize == 0 ? matrixSize / blockSize : matrixSize / blockSize + 1, 2);
    BufferedChannel<std::pair<int,int>> channel(size);
    for (int blockI = 0; blockI < matrixSize; blockI += blockSize)
        for (int blockJ = 0; blockJ < matrixSize; blockJ += blockSize)
        {
            std::pair<int, int> blockPair = { blockI,blockJ };
            channel.send(std::move(blockPair));
        }

    channel.close();
    for (int i = 0; i < countThreads; ++i)
        threads.emplace_back(multiplyWithChannel, std::ref(m1), std::ref(m2), std::ref(resM), matrixSize, blockSize,
                             std::ref(channel));

    for (auto& thread: threads)
        thread.join();
}

void calculateTime(std::vector< std::vector<int>>& m1, std::vector< std::vector<int>>& m2, std::vector< std::vector<int>>& m3, int matrixSize,int blockSize, int count)
{
    std::vector<double> calculationTime;
    auto Time = std::chrono::high_resolution_clock::now();
    for (int i = 1; i <= count; ++i)
    {
        multiply(m1, m2, m3, matrixSize, blockSize, i);
        auto Time1 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> current = Time1 - Time;
        calculationTime.push_back(current.count());
        m3 = std::vector<std::vector<int>>(matrixSize, std::vector<int>(matrixSize));
    }
    for (int i = 0; i < calculationTime.size() - 1; ++i)
    {
        std::cout<<"Time with " << i + 1 << " threads is " << calculationTime[i + 1] - calculationTime[i] << std::endl;
    }
}

int main()
{
    int size = 100;
    std::vector< std::vector<int>> matrix(size);
    std::vector< std::vector<int>> matrix1(size);
    std::vector< std::vector<int>> matrix2(size,std::vector<int>(size));
    readMatrixFromFile(matrix, "matrix1.txt");
    readMatrixFromFile(matrix1, "matrix2.txt");
    calculateTime(matrix, matrix1, matrix2, size, 8,35);
}
