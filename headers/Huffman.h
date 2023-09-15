#pragma once

#include "TreeNode.h"
#include "Compare.h"

class Huffman {
public:
    PQ* CreateTreeNodes(const std::map<char, int> &charFreq);

    PQ* CreateHuffmanTree(PQ *pq);

    void GenHuffmanCodes(const TreeNode *node, std::vector<uint8_t> code, std::map<char, std::vector<uint8_t>> &code_map);

    void CountFrequency(std::string text, std::map<char, int> &charFreq);

    int GetEncodedTextSize(const std::map<char, int> &char_freq, const std::map<char, std::vector<uint8_t>> &code_map);
};