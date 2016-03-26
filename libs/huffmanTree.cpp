/**
 * implementation of huffmanTree class
 * author : othniel konan
 * date : march 2016
 */

#include <fstream>
#include <iostream>
#include "huffmanTree.h"

void HuffmanTree::create_map(std::unordered_map<char, unsigned int> &map, std::string inputFile) {
    std::ifstream file (inputFile.c_str());
    if(!file){
        std::cout << "Error : Unable to open file " << inputFile << std::endl;
        return;
    }
    char c;
    while(file.get(c)){
        // check if character is an ASCII letter
        if(int(c)<32 || int(c)>127){
            std::cout << "Error : " << inputFile <<" file contains non ASCII letters." << std::endl;
            return;
        }
        // check for new character
        // *new => add it to the map
        if(map.find(c)==map.end()) map.insert({c,1});
        // *old => update its count
        else map[c]+=1;
    }
    file.close();
}