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

    // create tree and do other stuff
    return 0;
}