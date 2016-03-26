/**
 * huffmanNode library
 * author : othniel konan
 * date : march 2016
 */

#ifndef _HUFFMANTREE_H
#define _HUFFMANNTREE_H

#include <bits/shared_ptr.h>
#include <unordered_map>
#include <queue>
#include <bits/unique_ptr.h>

class HuffmanTree {
    typedef std::unordered_map<char, unsigned int> & map_type;
    typedef std::priority_queue<HuffmanNode, compare> & queue_type;
private:
    class HuffmanNode {
    private:
        char data;
        unsigned int frequency;
    public:
        std::shared_ptr<HuffmanNode> left;
        std::shared_ptr<HuffmanNode> right;

        HuffmanNode(char ch = ' ', unsigned int fr) : data(ch), frequency(fr) {
            left = nullptr;
            right = nullptr;
        }
    };
    class compare {
    public:
        bool operator()(HuffmanNode & nodeA, HuffmanNode & nodeB);
    };
public:
    // return a map of char and its frequency in the file named inputFile
    void create_map(map_type map,std::string inputFile);
    // read <key, value> from map, create a HuffmanNode with those parameters and add it to the queue
    void fill_queue(queue_type prior_q, map_type map );
    // build huffman tree
    std::unique_ptr<HuffmanNode> build_tree(queue_type prior_q);

};

#endif