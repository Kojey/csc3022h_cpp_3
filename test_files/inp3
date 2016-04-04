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
    if(file.is_open()) {
        for (const auto &n : map) {
            file << n.first << std::endl;
            file << n.second << std::endl;
        }
        file.close();
    }
}

void HuffmanTree::generate_compressed_file(std::string outputFile, std::string bit_string) {
    std::ofstream file(outputFile.c_str());
    if(file.is_open()) {
        file << bit_string.size();
        file << "\n";
        file << bit_string;
        file.close();
    }
}

void HuffmanTree::generate_binary_compressed_file(std::string outputFile, std::string bit_string) {
    std::ofstream file((outputFile+".bin").c_str(), std::ios::binary);
    const unsigned char * c = (const unsigned char *) bit_string.c_str();
    if(file.is_open()) {
        int n = bit_string.size();
        char end = '\n';
        file.write(reinterpret_cast<const char *>(&n), sizeof(int));
        file.write(&end, 1);
        for (int i = 0; i < n; i += 8) {
            std::bitset<8> buf = 0;
            for (int j = i; j < i + 8; j++) {
                bool x = (*(c + j) == '1' ? true : false);
                buf |= (x ? 1 : 0) << 7 - (j - i);
            }
            file.write((const char *) &buf, 1);
        }
        file.close();
    }
}

void  HuffmanTree::compress_file(std::string inputFile, std::string outputFile) {
    // variables and typedef
    typedef HuffmanTree::HuffmanNode node_type;
    HuffmanTree tree;
    std::unordered_map<char, unsigned int> map;
    std::unordered_map<char, std::string> code_table;
    std::priority_queue<node_type,std::vector<node_type>, HuffmanTree::Compare> prior_q;
    // calling methods
    tree.create_map(map,inputFile);
    tree.fill_queue(prior_q,map);
    HuffmanTree::HuffmanNode node(tree.build_tree(prior_q));
    tree.generate_code_table(node,code_table,"");
    tree.generate_code_file(outputFile, code_table);
    std::string bit_string = tree.generate_bit_string(inputFile,code_table);
    tree.generate_binary_compressed_file(outputFile, bit_string);
    tree.generate_compressed_file(outputFile, bit_string);
}

void HuffmanTree::decompress_file(std::string inputBinFile, std::string code_file){
    // create inverse of map
    std::unordered_map<std::string, std::string> code_table;
    std::ifstream file((inputBinFile+".hdr").c_str());
    if(!file){
        std::cout << "Error : Unable to open file " << inputBinFile+"hdr" << std::endl;
        return;
    }
    while(!file.eof()){
        std::string s,c;
        std::getline(file,c,'\n');
        std::getline(file,s,'\n');
        if(s=="") {
            std::getline(file, s, '\n');
            code_table.insert({s, "\n"});
        }
        else code_table.insert({s,c});

    }
    file.close();// read inputBinFile and convert it to a bit_stream
    file.open((inputBinFile+".bin").c_str(), std::ios::binary);
    if(!file){
        std::cout << "Error : Unable to open file " << inputBinFile << std::endl;
        return;
    }
    char c;
    int Nbits ;
    file.read(reinterpret_cast<char *>(&Nbits), sizeof(int)); // read the int
    int Nbytes = Nbits/8 + (Nbits%8?1:0);
    file.read(&c, 1); // read the '\n' character
    std::bitset<8> * byte = new std::bitset<8> [Nbytes];
    for(int j=0; j<Nbytes; j++){
        file.read((char *) & byte[j],1);
    }
    file.close();
    // convert bit_stream to bit_string
    std::string bit_string;
    std::string bit;
    for(int k=0; k<Nbytes; k++){
        for(int i=7; i>-1; i--) {
            std::bitset<8> buf;
            std::bitset<1> bit_result;
            // extract bit at position i
            buf = byte[k] & (std::bitset<8>) 1 << i;
            buf = buf >> i;
            bit = (buf == 1 ? '1' : '0');
            bit_string += bit;
        }
    }
    delete [] byte;
    // decode bit_string
    std::string decoded_string,code;
    for (int i=0; i<bit_string.size(); i++){
        std::string ch = bit_string.substr(i,1);
        code+=ch;
        if(code_table.find(code)!=code_table.end()){
            decoded_string+=code_table[code];
            code = "";
        }
        if(i==Nbits)break;
    }
    // write letters to outputFile
    std::ofstream ofile(code_file.c_str());
    while(ofile.is_open()) {
        ofile << decoded_string;
        ofile.close();
    }
}