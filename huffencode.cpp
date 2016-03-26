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
    std::unordered_map<char, unsigned int> map;
    std::unordered_map<char, std::string> code_table;
    tree.create_map(map,inputFile);
    typedef HuffmanTree::HuffmanNode node_type;
    std::priority_queue<node_type,std::vector<node_type>, HuffmanTree::Compare> prior_q;
    tree.fill_queue(prior_q,map);
    // create tree and do other stuff
    for( const auto& n : map ) {
        std::cout << "key[" << n.first << "] = " << n.second << std::endl;
    }
    HuffmanTree::HuffmanNode node(tree.build_tree(prior_q));
    tree.generate_code_table(node,code_table,"");
    std::cout << std::endl;
    for( const auto& n : code_table ) {
        std::cout << "key[" << n.first << "] = " << n.second << std::endl;
    }
    return 0;
}