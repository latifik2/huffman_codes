#pragma once

#include "TreeNode.h"
#include "Compare.h"

class Huffman {
public:
    PQ* CreateTreeNodes();

    void CreateHuffmanTree();

    void GenHuffmanCodes(const TreeNode *node, std::vector<uint8_t> code, std::map<char, std::vector<uint8_t>> &code_map);

    void CountFrequency(std::string text);

    int GetEncodedTextSize();

private:
    std::map<char, int> charFreq;
    std::vector<uint8_t> code;
    std::map<char, std::vector<uint8_t>> codeMap;
    PQ *pq;
};