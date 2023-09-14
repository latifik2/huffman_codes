#include "../headers/Huffman.h"
//#include "../headers/TreeNode.h"
using PQ = std::priority_queue<TreeNode *, std::vector<TreeNode *>, Compare>;


PQ* Huffman::CreateTreeNodes(const std::map<char, int> &charFreq) {
    PQ *pq = new std::priority_queue<TreeNode *, std::vector<TreeNode *>, Compare>();

    for (auto it = charFreq.begin(); it != charFreq.end(); it++)
        pq->push(new TreeNode(it->second, it->first));

    return pq;
}


PQ* Huffman::CreateHuffmanTree(PQ *pq) {
    while (pq->size() > 1) {
        auto tmp1 = pq->top();
        pq->pop();
        auto tmp2 = pq->top();
        pq->pop();
        pq->push(new TreeNode(tmp1->weigth + tmp2->weigth, 0, tmp1, tmp2));
    }

    return pq;
}

void Huffman::GenHuffmanCodes(const TreeNode *node, std::vector<uint8_t> code, std::map<char, std::vector<uint8_t>> &code_map) {
    if (node->character != 0) {
        code_map[node->character] = code;
        code.clear();
        return;
    }

    if (node->left != nullptr) {
        code.push_back(0);
        Huffman::GenHuffmanCodes(node->left, code, code_map);
        code.pop_back();
    }

    if (node->right != nullptr) {
        code.push_back(1);
        Huffman::GenHuffmanCodes(node->right, code, code_map);
        code.pop_back();
    }

}

void Huffman::CountFrequency(std::string text, std::map<char, int> &charFreq) {

    for (const auto &chr : text) {
        auto it = charFreq.find(chr);
        if (it != charFreq.end())
            it->second += 1;
        else
            charFreq[chr] = 1;
    }

}

int Huffman::GetEncodedTextSize(const std::map<char, int> &char_freq, const std::map<char, std::vector<uint8_t>> &code_map) {
    int size = 0;

    auto it = char_freq.begin();
    auto it2 = code_map.begin();

    while (it != char_freq.end()) {
        size += it->second * it2->second.size();
        it++;
        it2++;
    }
    return size;
}