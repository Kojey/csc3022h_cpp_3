/**
 *  driver for the huffmanTree
 *  author : othniel konan
 *  date : march 2016
 */

#include <iostream>
#include <string>
#include "libs/huffmanTree.h"

int main(int argc, char * argv []){
    // exception
    if (argc < 3){
        std::cout << "Missing arguments." << std::endl;
        return 0;
    }
    // create variables
    std::string inputFile = std::string(argv[1]); std::string output_file = std::string(argv[2]);
    HuffmanTree tree;
    std::unordered_map<char, unsigned int> m;
    std::unordered_map<char, unsigned int> & map = m;
    tree.create_map(map,inputFile);
    for( const auto& n : m ) {
        std::cout << "Key:[" << n.first << "] Value:[" << n.second << "]\n";
    }
    // create tree and do other stuff
    return 0;
}