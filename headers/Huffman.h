#pragma once

#include "TreeNode.h"
#include "Compare.h"
#include "../lib/BitArray.h"

#include <vector>

class Huffman {
public:
    Huffman();
    ~Huffman();

    void FreeNodes(TreeNode *node);
    void CountFrequency(uint8_t* sourceData, int size);
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
    TreeNode *root;
    int nodesCount;
};