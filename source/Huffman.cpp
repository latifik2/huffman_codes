#include "../headers/Huffman.h"

//#include "../headers/TreeNode.h"
using PQ = std::priority_queue<TreeNode *, std::vector<TreeNode *>, Compare>;

Huffman::Huffman()
    : nodesCount(0) {
}

void Huffman::CountNodes() {
    this->nodesCount++;
}

void Huffman::CreateTreeNodes() {
    this->pq = new std::priority_queue<TreeNode *, std::vector<TreeNode *>, Compare>();

    for (auto it = this->charFreq.begin(); it != this->charFreq.end(); it++) {
        pq->push(new TreeNode(it->second, it->first));
        CountNodes();
    }
    
}


void Huffman::CreateHuffmanTree() {
    while (this->pq->size() > 1) {
        auto tmp1 = this->pq->top();
        this->pq->pop();
        auto tmp2 = this->pq->top();
        this->pq->pop();
        this->pq->push(new TreeNode(tmp1->weigth + tmp2->weigth, 0, tmp1, tmp2));
        CountNodes();
    }
}

TreeNode* Huffman::RestoreHuffmanTree(TreeNode *node, BitArray &bitArray, bool isLeft) {

    if (node != nullptr)
        return nullptr;
    
    uint8_t bit = bitArray.PopBit();

    if (bit == 0) {
        BitArray chr(8);
        for (int i = 0; i < 8; i++) {
            uint8_t chr_bit = bitArray.PopBit();
            chr.AppendBit(BitArray::BitState(chr_bit));
        }
        node = new TreeNode(0, char(chr.GetByte(0)));
        return node;
    }
    else {
        node = new TreeNode(0);
    }
    node->left = Huffman::RestoreHuffmanTree(node->left, bitArray, true);
    node ->right = Huffman::RestoreHuffmanTree(node->right, bitArray, false);
    return node;
}

void Huffman::GenHuffmanCodes(const TreeNode *node, std::vector<uint8_t> code) {
    if (node->character != 0) {
        codeMap[node->character] = code;
        code.clear(); //should probably replace this with code.pop() and pass code vector as reference
        return;
    }

    if (node->left != nullptr) {
        code.push_back(0);
        Huffman::GenHuffmanCodes(node->left, code);
        code.pop_back();
    }

    if (node->right != nullptr) {
        code.push_back(1);
        Huffman::GenHuffmanCodes(node->right, code);
        code.pop_back();
    }

}

void Huffman::CountFrequency(std::string text) {

    for (const auto &chr : text) {
        auto it = charFreq.find(chr);
        if (it != charFreq.end())
            it->second += 1;
        else
            charFreq[chr] = 1;
    }

}

int Huffman::GetEncodedTextSize() {
    int size = 0;

    auto it = charFreq.begin();
    auto it2 = codeMap.begin();

    while (it != charFreq.end()) {
        size += it->second * it2->second.size();
        it++;
        it2++;
    }
    return size;
}

int Huffman::GetCharsNum() {
    return charFreq.size();
}

char Huffman::DecodeCodes(TreeNode *node, BitArray &bitArray){
    if (node->character != 0)
        return node->character;

    uint8_t bit = bitArray.PopBit();
    bitArray.CountOperations();
    if (bit == 0)
        return DecodeCodes(node->left, bitArray);
    if (bit == 1)
        return DecodeCodes(node->right, bitArray);

    return '#';
}