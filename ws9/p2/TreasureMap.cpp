#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <vector>
#include <future>
#include <functional>
#include "TreasureMap.h"

namespace seneca{

    size_t digForTreasure(const std::string& str, char mark){
        size_t cnt = 0;
        for (auto& x : str){
            if (x == mark){
                cnt++;
            }
        }
        return cnt;
    }

    TreasureMap::TreasureMap(const char* filename){
        std::fstream fin(filename);
        if (fin){
            fin >> rows;
            fin.ignore();
            map = new std::string[rows];
            size_t idx = 0;
            while(fin){
                getline(fin, map[idx]);
                idx++;
            }
            colSize = map[0].length();
        }
        else {
            throw std::string(filename) + " cannot be opened";
        }
    }

    TreasureMap::~TreasureMap(){
        delete [] map;
    }

    std::ostream& TreasureMap::display(std::ostream& os) const{
        if (map){
            for (size_t i = 0; i < rows; ++i){
                os << map[i] << std::endl;
            }
        }
        else 
            os << "The map is empty!" << std::endl;
        return os;
    }

void TreasureMap::enscribe(const char* filename) {
        std::ofstream fout(filename, std::ios::binary); 
        if (!fout.is_open()) { 
            throw std::string("Unable to open file for writing: ") + filename;
        }

        // Write the number of rows and colSize to the binary file
        fout.write(reinterpret_cast<const char*>(&rows), sizeof(rows));
        fout.write(reinterpret_cast<const char*>(&colSize), sizeof(colSize));

        for (size_t i = 0; i < rows; ++i) {
            fout.write(map[i].c_str(), colSize); 
        }
        fout.close(); 
    }

    void TreasureMap::recall(const char* filename) {
        std::ifstream fin(filename, std::ios::binary); 
        if (!fin.is_open()) { 
            throw std::string("Unable to open file for reading: ") + filename;
        }

        // Read the number of rows and colSize from the binary file
        fin.read(reinterpret_cast<char*>(&rows), sizeof(rows));
        fin.read(reinterpret_cast<char*>(&colSize), sizeof(colSize));

        map = new std::string[rows];

        for (size_t i = 0; i < rows; ++i) {
            char* buffer = new char[colSize + 1]; 
            fin.read(buffer, colSize); 
            buffer[colSize] = '\0'; 
            map[i] = buffer; 
            delete[] buffer; 
        }

        fin.close(); 
    }

    void TreasureMap::clear(){
        delete [] map;
        map = nullptr;
        rows = 0;
        colSize = 0;
    }

    size_t TreasureMap::findTreasure(char mark) {
        size_t count = 0;
        const size_t numThreads = 4; // Manually specify the number of threads
        std::vector<std::packaged_task<size_t()>> tasks(numThreads);
        std::vector<std::future<size_t>> futures(numThreads);
        size_t rowsPerThread = rows / numThreads; // Rows per thread

        for (size_t i = 0; i < numThreads; ++i) {
            size_t startIdx = i * rowsPerThread;
            size_t endIdx = (i == numThreads - 1) ? rows : startIdx + rowsPerThread;

            // Create packaged_task with bound digForTreasure function
            tasks[i] = std::packaged_task<size_t()>([this, mark, startIdx, endIdx]() {
                size_t threadCount = 0;
                for (size_t j = startIdx; j < endIdx; ++j) {
                    threadCount += digForTreasure(map[j], mark);
                }
                return threadCount;
            });

            // Associate packaged_task with future
            futures[i] = tasks[i].get_future();

            // Create thread and provide packaged_task and partitioned data
            std::thread t(std::move(tasks[i]));

            // No need to join threads here, we can join them later
            t.detach();
        }

        // Wait for all threads to finish
        for (auto& f : futures) {
            count += f.get();
        }

        return count;

    }
}
