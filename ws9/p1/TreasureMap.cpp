#include <iostream>
#include <fstream>
#include <string>
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
        std::ofstream fout(filename/*, std::ios::binary*/); // Open the binary file for writing
        if (!fout.is_open()) { // Check if the file is opened successfully
            throw std::string("Unable to open file for writing: ") + filename;
        }

        // Write the number of rows and colSize to the binary file
        fout.write(reinterpret_cast<const char*>(&rows), sizeof(size_t));
        fout.write(reinterpret_cast<const char*>(&colSize), sizeof(size_t));

        // Write each row of the map to the binary file
        for (size_t i = 0; i < rows; ++i) {
            fout.write(map[i].c_str(), colSize); // Write the entire row
        }

        fout.close(); // Close the file
    }

    void TreasureMap::recall(const char* filename) {
        std::ifstream fin(filename, std::ios::binary); // Open the binary file for reading
        if (!fin.is_open()) { // Check if the file is opened successfully
            throw std::string("Unable to open file for reading: ") + filename;
        }

        // Read the number of rows and colSize from the binary file
        fin.read(reinterpret_cast<char*>(&rows), sizeof(size_t));
        fin.read(reinterpret_cast<char*>(&colSize), sizeof(size_t));

        // Allocate memory for the map
        map = new std::string[rows];

        // Read each row of the map from the binary file
        for (size_t i = 0; i < rows; ++i) {
            char* buffer = new char[colSize + 1]; // Allocate buffer to read the row
            fin.read(buffer, colSize); // Read the row
            buffer[colSize] = '\0'; // Null-terminate the string
            map[i] = buffer; // Store the row in the map
            delete[] buffer; // Delete the buffer
        }

        fin.close(); // Close the file
    }




    void TreasureMap::clear(){
        delete [] map;
        map = nullptr;
        rows = 0;
        colSize = 0;
    }


    size_t processPartition(const std::string* partition, size_t size, char mark) {
        size_t count = 0;
        for (size_t i = 0; i < size; ++i) {
            count += digForTreasure(partition[i], mark);
        }
        return count;
    }


 size_t TreasureMap::findTreasure(char mark) {
        const size_t numThreads = 4;
        std::vector<std::thread> threads;
        std::vector<std::packaged_task<size_t()>> tasks(numThreads);
        std::vector<std::future<size_t>> futures;

        size_t partitionSize = rows / numThreads;
        size_t lastPartitionSize = rows % numThreads;

        size_t startIndex = 0;
        size_t endIndex = 0;

        for (size_t i = 0; i < numThreads; ++i) {
            endIndex += (i < lastPartitionSize) ? partitionSize + 1 : partitionSize;
            std::string* partition = map + startIndex;
            tasks[i] = std::packaged_task<size_t()>(
                std::bind(processPartition, partition, endIndex - startIndex, mark)
            );
            futures.emplace_back(tasks[i].get_future());
            threads.emplace_back(std::thread(std::move(tasks[i])));
            startIndex = endIndex;
        }

        size_t totalCount = 0;
        for (auto& future : futures) {
            totalCount += future.get();
        }

        for (auto& thread : threads) {
            thread.join();
        }

        return totalCount;
    }
}


/* output: 
Command Line: ws map.txt map.bin

***Displaying original Map***
W|<|>...---....|AHAHAHAHAHA---
|<|>...---|^|...X|BBBBBB|....|
|^|-|^|-.00....0..|.00....0..|
||^CCC4567.....|^||..00|.0.0.|
|^||...|^|...X|BBBBBB|.|X....|
|^|------|^|-.00....0..|0----|
|^|...X|BBB|^|-.00....0..|BBB|
||^|-.00....0..|^CCCCCC......|
|..12340000...|......1182APPLE
|??-----X..|^|-.00....0..|...|
---SEC|^|-.00....0..|RETS-----
|^|------|^|-.00....0..|0----|

***Enscribing Map and displaying cleared current Map***
The map is empty!

***Recalling Map and displaying current Map***
W|<|>...---....|AHAHAHAHAHA---
|<|>...---|^|...X|BBBBBB|....|
|^|-|^|-.00....0..|.00....0..|
||^CCC4567.....|^||..00|.0.0.|
|^||...|^|...X|BBBBBB|.|X....|
|^|------|^|-.00....0..|0----|
|^|...X|BBB|^|-.00....0..|BBB|
||^|-.00....0..|^CCCCCC......|
|..12340000...|......1182APPLE
|??-----X..|^|-.00....0..|...|
---SEC|^|-.00....0..|RETS-----
|^|------|^|-.00....0..|0----|

***Finding treasure on current Map***
***Found 5 treasure on current Map***

The content of the binary file
------------------------------
File size in bytes: [376]
01: [ 0c 00 00 00 00 00 00 00 1e 00 00 00 00 00 00 00 57 7c 3c 7c]
02: [ 3e 2e 2e 2e 2d 2d 2d 2e 2e 2e 2e 7c 41 48 41 48 41 48 41 48]
03: [ 41 48 41 2d 2d 2d 7c 3c 7c 3e 2e 2e 2e 2d 2d 2d 7c 5e 7c 2e]
04: [ 2e 2e 58 7c 42 42 42 42 42 42 7c 2e 2e 2e 2e 7c 7c 5e 7c 2d]
05: [ 7c 5e 7c 2d 2e 30 30 2e 2e 2e 2e 30 2e 2e 7c 2e 30 30 2e 2e]
06: [ 2e 2e 30 2e 2e 7c 7c 7c 5e 43 43 43 34 35 36 37 2e 2e 2e 2e]
07: [ 2e 7c 5e 7c 7c 2e 2e 30 30 7c 2e 30 2e 30 2e 7c 7c 5e 7c 7c]
08: [ 2e 2e 2e 7c 5e 7c 2e 2e 2e 58 7c 42 42 42 42 42 42 7c 2e 7c]
09: [ 58 2e 2e 2e 2e 7c 7c 5e 7c 2d 2d 2d 2d 2d 2d 7c 5e 7c 2d 2e]
0a: [ 30 30 2e 2e 2e 2e 30 2e 2e 7c 30 2d 2d 2d 2d 7c 7c 5e 7c 2e]
0b: [ 2e 2e 58 7c 42 42 42 7c 5e 7c 2d 2e 30 30 2e 2e 2e 2e 30 2e]
0c: [ 2e 7c 42 42 42 7c 7c 7c 5e 7c 2d 2e 30 30 2e 2e 2e 2e 30 2e]
0d: [ 2e 7c 5e 43 43 43 43 43 43 2e 2e 2e 2e 2e 2e 7c 7c 2e 2e 31]
0e: [ 32 33 34 30 30 30 30 2e 2e 2e 7c 2e 2e 2e 2e 2e 2e 31 31 38]
0f: [ 32 41 50 50 4c 45 7c 3f 3f 2d 2d 2d 2d 2d 58 2e 2e 7c 5e 7c]
10: [ 2d 2e 30 30 2e 2e 2e 2e 30 2e 2e 7c 2e 2e 2e 7c 2d 2d 2d 53]
11: [ 45 43 7c 5e 7c 2d 2e 30 30 2e 2e 2e 2e 30 2e 2e 7c 52 45 54]
12: [ 53 2d 2d 2d 2d 2d 7c 5e 7c 2d 2d 2d 2d 2d 2d 7c 5e 7c 2d 2e]
13: [ 30 30 2e 2e 2e 2e 30 2e 2e 7c 30 2d 2d 2d 2d 7c]
------------------------------
*/