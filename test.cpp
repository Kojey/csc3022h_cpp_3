/*
 * test case for compressor
 * author : othiel konan
 * date : april 2016
 */

#define CATCH_CONFIG_MAIN

#include "libs/catch.hpp"
#include "libs/huffmanTree.h"


TEST_CASE("trying", "[AS]"){
    HuffmanTree tree;
    std::unordered_map<char, unsigned int> map;
    std::string s = "test_files/test1";
    tree.create_map(map,s);
    REQUIRE(map.find('a') != map.end());
}
