/*
 * test case for compressor
 * author : othiel konan
 * date : april 2016
 */

#define CATCH_CONFIG_MAIN

#include <fstream>
#include "libs/catch.hpp"
#include "libs/huffmanTree.h"


TEST_CASE("Testing compression"){
    HuffmanTree tree;
    typedef HuffmanTree::HuffmanNode node_type;
    std::unordered_map<char, unsigned int> map;
    std::unordered_map<char, std::string> code_table;
    std::priority_queue<node_type,std::vector<node_type>, HuffmanTree::Compare> prior_q;
    std::string file = "test_files/test1";

    SECTION("Testing <create_map>") {
        tree.create_map(map, file);
        SECTION("character presence"){
            REQUIRE(map.find(' ') != map.end());
            REQUIRE(map.find('s') != map.end());
            REQUIRE(map.find('a') == map.end());
        }
        SECTION("character frequency is updated"){
            REQUIRE(map['s']==4);
            REQUIRE(map[' ']==1);
        }
        SECTION("map has correct size after reading file"){
            REQUIRE(map.size()==8);
        }
    }
    SECTION("Testing <fill_queue>") {
        SECTION("map and queue should have the same size"){
            tree.fill_queue(prior_q, map);
            REQUIRE(map.size()==prior_q.size());
        }
    }
    SECTION("Testing <build_tree>, root frequency should be the number of character in file"){
        tree.create_map(map, file);
        tree.fill_queue(prior_q, map);
        HuffmanTree::HuffmanNode node(tree.build_tree(prior_q));
        unsigned int sum=0;
        for(const auto &n:map) sum += n.second;
        REQUIRE(node.get_frequency()==sum);
    }
}

TEST_CASE("Testing decompression"){
    SECTION("uncompressed file should be the same as initial file: test1"){
        HuffmanTree tree;
        std::string inp, out, file1, s, file2;
        inp = "test_files/inp1";
        out = "test_files/out1";
        tree.compress_file(inp,out);
        tree.decompress_file(out, inp+"_");

        std::ifstream inpFile(inp.c_str());
        while(!inpFile.eof()){
            inpFile >> s;
            file1+=s;
        }
        inpFile.close();

        std::ifstream decFile((inp+"_").c_str());
        while(!decFile.eof()){
            decFile >> s;
            file2+=s;
        }
        decFile.close();
        REQUIRE(file1==file2);
    }
    SECTION("uncompressed file should be the same as initial file: test2"){
        HuffmanTree tree;
        std::string inp, out, file1, s, file2;
        inp = "test_files/inp2";
        out = "test_files/out2";
        tree.compress_file(inp,out);
        tree.decompress_file(out, inp+"_");

        std::ifstream inpFile(inp.c_str());
        while(!inpFile.eof()){
            inpFile >> s;
            file1+=s;
        }
        inpFile.close();

        std::ifstream decFile((inp+"_").c_str());
        while(!decFile.eof()){
            decFile >> s;
            file2+=s;
        }
        decFile.close();
        REQUIRE(file1==file2);
    }
    SECTION("uncompressed file should be the same as initial file: test3"){
        HuffmanTree tree;
        std::string inp, out, file1, s, file2;
        inp = "test_files/inp3";
        out = "test_files/out3";
        tree.compress_file(inp,out);
        tree.decompress_file(out, inp+"_");

        std::ifstream inpFile(inp.c_str());
        while(!inpFile.eof()){
            inpFile >> s;
            file1+=s;
        }
        inpFile.close();

        std::ifstream decFile((inp+"_").c_str());
        while(!decFile.eof()){
            decFile >> s;
            file2+=s;
        }
        decFile.close();
        REQUIRE(file1==file2);
    }
    SECTION("uncompressed file should be the same as initial file: test4"){
        HuffmanTree tree;
        std::string inp, out, file1, s, file2;
        inp = "test_files/inp4";
        out = "test_files/out4";
        tree.compress_file(inp,out);
        tree.decompress_file(out, inp+"_");

        std::ifstream inpFile(inp.c_str());
        while(!inpFile.eof()){
            inpFile >> s;
            file1+=s;
        }
        inpFile.close();

        std::ifstream decFile((inp+"_").c_str());
        while(!decFile.eof()){
            decFile >> s;
            file2+=s;
        }
        decFile.close();
        REQUIRE(file1==file2);
    }
}