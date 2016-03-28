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
        HuffmanNode(char ch, unsigned int fr) : data(ch), frequency(fr) {
            left = nullptr;
            right = nullptr;
        }
//        HuffmanNode(const HuffmanNode & node) = default;
//        HuffmanNode(HuffmanNode && node) = default;
        char get_data(void) const {
            return this->data;
        }
        unsigned int get_frequency(void) const {
            return this->frequency;
        }
    };
    class Compare {
    public:
        bool operator()(const HuffmanNode a, const HuffmanNode b){
            /*
             * check if a is greater that b
             */
            return (a.get_frequency() > b.get_frequency() ? true:false);
        }
    };
    typedef std::unordered_map<char, unsigned int> & map_type;
    typedef std::unordered_map<char, std::string> & code_type;
    typedef HuffmanTree::HuffmanNode node_type;
    typedef std::priority_queue<node_type,std::vector<node_type>, HuffmanTree::Compare> &  queue_type;
    // return a map of char and its frequency in the file named inputFile
    void create_map(map_type, std::string);
    // read <key, value> from map, create a HuffmanNode with those parameters and add it to the queue
    void fill_queue(queue_type, map_type);
    // build huffman tree
    HuffmanTree::HuffmanNode build_tree(HuffmanTree::queue_type);
    void generate_code_table(node_type, code_type, std::string);
    std::string generate_bit_string(std::string, code_type);
    void generate_code_file(std::string, code_type);
    void generate_compressed_file(std::string, std::string);
    void compress_file(std::string, std::string);
    void decompress_file(std::string, std::string);
};

#endif