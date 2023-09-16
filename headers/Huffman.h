#pragma once

#include "TreeNode.h"
#include "Compare.h"

class Huffman {
public:
    Huffman();

    void CountFrequency(std::string text);
    void CountNodes();
    void CreateTreeNodes();
    void CreateHuffmanTree();
    void GenHuffmanCodes(const TreeNode *node, std::vector<uint8_t> code);
    int GetEncodedTextSize();

    friend class App;

private:
    std::map<char, int> charFreq;
    std::map<char, std::vector<uint8_t>> codeMap;
    PQ *pq;
    int nodesCount;
};