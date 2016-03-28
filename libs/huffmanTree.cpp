/**
 * implementation of huffmanTree class
 * author : othniel konan
 * date : march 2016
 */

#include <fstream>
#include <iostream>
#include <vector>
#include <bitset>
#include "huffmanTree.h"

void HuffmanTree::create_map(HuffmanTree::map_type map, std::string inputFile) {
    /*
     * Read characters from text file and create a map of the characters and
     * their respective frequency
     */
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

void HuffmanTree::fill_queue( HuffmanTree::queue_type prior_q, HuffmanTree::map_type map) {
    /*
     * Create a priority queue of HuffmanNode where node A is of higher order than node B if
     * the frequency of A is greater than the frequency of B
     */
    // for each element in the map
    for( const auto& n : map ) {
        // create a HuffmanNode with data = map[key] and frequency = value
        // add it to the queue
        prior_q.push(HuffmanTree::HuffmanNode(n.first,n.second));
    }
}

HuffmanTree::HuffmanNode HuffmanTree::build_tree(HuffmanTree::queue_type prior_q) {
    while (prior_q.size()>1){
        std::shared_ptr<HuffmanTree::HuffmanNode> left(new HuffmanTree::HuffmanNode(prior_q.top()));
        prior_q.pop();
        std::shared_ptr<HuffmanTree::HuffmanNode> right(new HuffmanTree::HuffmanNode(prior_q.top()));
        prior_q.pop();
        unsigned int fr = left->get_frequency()+right->get_frequency();
        HuffmanTree::HuffmanNode head = HuffmanTree::HuffmanNode('\0',fr);
        head.left = std::move(left);
        head.right = std::move(right);
        prior_q.push(head);
    }
    HuffmanTree::HuffmanNode node(prior_q.top());
    return node;
}

void HuffmanTree::generate_code_table(node_type node, code_type map, std::string code) {
    if(node.left == nullptr){ // leaf node
        map.insert({node.get_data(), code}); // add leadf to code table
        return;
    }
    else{ // not a leaf so has left and right child
        std::string left = code + "0";
        std::string right = code + "1";
        HuffmanTree::generate_code_table(*(node.left), map, left );
        HuffmanTree::generate_code_table(*(node.right), map, right);
    }
}

std::string HuffmanTree::generate_bit_string(std::string inputFile, code_type map) {
    std::ifstream file(inputFile.c_str());
    if(!file){
        std::cout << "Error : Unable to open file " << inputFile << std::endl;
        return NULL;
    }
    char c;
    std::string bit_string;
    while(file.get(c)) bit_string+=map[c];
    file.close();
    return bit_string;
}

void HuffmanTree::generate_code_file(std::string outputFile, code_type map) {
    std::ofstream file((outputFile+".hdr").c_str());
    if(!file){
        std::cout << "Error : Unable to open file " << outputFile << ".hdr" << std::endl;
        return;
    }
    for(const auto& n : map) file << n.first << " " << n.second << "\n";
    file.close();
}

void HuffmanTree::generate_compressed_file(std::string outputFile, std::string bit_string) {
    std::ofstream file(outputFile.c_str(), std::ios::binary);
    const unsigned char * c = (const unsigned char *) bit_string.c_str();
    if(!file){
        std::cout << "Error : Unable to open file " << outputFile << std::endl;
        return;
    }
    typedef std::bitset<1> bit;
    typedef std::bitset<8> byte;
    for(int i=0; i<bit_string.size(); i+=8) {
        byte buf=0;
        for(int j=i; j<i+8; j++){
            bool x = (*(c+j)=='1'? true:false);
            byte b = (x?1:0) << 7-(j-i);
//            std::cout << i << " " << j << " " << *(c+j) << " " << x << " " << j-i << " " << b << std::endl;
            buf|= b;
        }
        std::cout << buf ;//<< std::endl;
        const char * p = (const char *) & buf;
        file.write(p,1);
    }
    file.close();
}
