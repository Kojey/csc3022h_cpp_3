/**
 * huffmanNode library
 * author : othniel konan
 * date : march 2016
 */

#ifndef _HUFFMANTREE_H
#define _HUFFMANNTREE_H
#include <unordered_map>
#include <queue>
#include <memory>
//#include <bits/unique_ptr.h>

class HuffmanTree {

public:
    class HuffmanNode {
    private:
        char data;
        unsigned int frequency;
    public:
        std::shared_ptr<HuffmanNode> left;
        std::shared_ptr<HuffmanNode> right;
        // Constructor
        HuffmanNode() = delete;
        HuffmanNode(char ch , unsigned int fr) : data(ch), frequency(fr) {
            left = nullptr;
            right = nullptr;
        }
        char get_data(void) const {
            return this->data;
        }
        unsigned int get_frequency(void) const {
            return this->frequency;
        }
    };
    class Compare {
    public:
        bool operator()(const HuffmanNode a, const HuffmanNode b);
    };
    typedef std::unordered_map<char, unsigned int> & map_type;
    typedef std::priority_queue<HuffmanTree::HuffmanNode,std::vector<HuffmanTree::HuffmanNode>, HuffmanTree::Compare> &  queue_type;
    // return a map of char and its frequency in the file named inputFile
    void create_map(map_type  map,std::string inputFile);
    // read <key, value> from map, create a HuffmanNode with those parameters and add it to the queue
    void fill_queue(queue_type  prior_q, map_type  map );
    // build huffman tree
    std::unique_ptr<HuffmanNode> build_tree(std::priority_queue<HuffmanNode> & prior_q);

};

#endif