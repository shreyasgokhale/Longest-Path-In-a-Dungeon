#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include<string>

uint8_t map_size = 0;
uint8_t row_size = 0;
uint8_t max_count = 0;

// 2D Vector defining our map
static std::vector<std::vector<char>> map_vector;


void printMap() {
    for (auto &i : map_vector) {
        for (const auto &j : i) {
            std::cout << j << " ";
        }
        std::cout << std::endl;
    }
}

bool readFile() {
    std::ifstream map_file("map.txt");
    std::string string;
    while(std::getline(map_file, string)){
        map_vector.emplace_back();
        std::copy(string.begin(), string.end(), std::back_inserter(map_vector.back()));
    }
    printMap();
    map_file.close();
    return true;
}

void findStartingPositions(std::vector<char> first_row, std::vector<std::pair<int, int>> *pVector) {
    for (int i=0; i<row_size;i++)
        if (first_row.at(i) == *".")
            pVector->emplace_back(std::make_pair(0, i));
}

bool tracePath( std::pair<int, int> pair, int counter) {

    // Sanity check
    if(pair.first > map_size || pair.second >= row_size || pair.first < 0 || pair.second < 0)
        return false;

    unsigned char count_char = '0' + counter;

    // Update Visited node
    map_vector.at(pair.first).at(pair.second) = (count_char);
    counter ++;

    // Check left

    if(map_vector.at(pair.first).at(pair.second - 1) ==*".")
        tracePath(std::make_pair(pair.first,pair.second - 1),counter);

    // Check right
    if(map_vector.at(pair.first).at(pair.second + 1 ) ==*".")
        tracePath(std::make_pair(pair.first,pair.second + 1),counter);

    // Sanity check 2
    if(pair.first ==  map_size)
        return true;

    // Check front
    if(map_vector.at(pair.first+1).at(pair.second) ==*".")
        tracePath(std::make_pair(pair.first+1,pair.second),counter);

    // Reached End
    if(map_vector.at(pair.first+1).at(pair.second) ==*"#" || map_vector.at(pair.first+1).at(pair.second) !=*".")
        if(counter > max_count) max_count = counter;

    return true;
}

void findPath() {
    std::vector<std::queue<std::pair<int,int>>> paths;
    std::vector<std::pair<int,int>> starts;

    findStartingPositions(map_vector.at(0), &starts);

    // Iterate through all paths
    for (auto & itr : starts) {
        tracePath(itr, 0);
    }
}

int main() {
    //  Get Map data from file
    if(!readFile()) std::cout << "File Read Failed";
    map_size = map_vector.size();
    row_size = map_vector.at(1).size();
    findPath();
    char count_char = '0' + max_count;
    std::cout<<count_char<<std::endl;
    printMap();
    return 0;
}