#pragma once

#include "TreeNode.h"
#include "Compare.h"
#include "../lib/BitArray.h"

class Huffman {
public:
    Huffman();

    void CountFrequency(std::string text);
    void CountNodes();
    void CreateTreeNodes();
    void CreateHuffmanTree();
    TreeNode* RestoreHuffmanTree(TreeNode *node, BitArray &birArray, bool isLeft);
    void GenHuffmanCodes(const TreeNode *node, std::vector<uint8_t> code);
    int GetEncodedTextSize();
    int GetCharsNum();
    int GetNodesNum();
    char DecodeCodes(TreeNode* node, BitArray &bitArray);

    friend class App;

private:
    std::map<char, int> charFreq;
    std::map<char, std::vector<uint8_t>> codeMap;
    PQ *pq;
    int nodesCount;
};