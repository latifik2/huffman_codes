#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <queue>

#include "../headers/Huffman.h"
#include "../headers/Debug.h"

std::string ReadFile(const std::string path) {
    std::ifstream file;
    std::stringstream buffer;
    std::string text;

    file.open(path, std::ios::in);

    if (!file.is_open()) {
        Debug::DebugPrint("Unable to open file.");
        return nullptr;
    }   
    // file >> text;
    // file.close();

    buffer << file.rdbuf();
    return buffer.str();
}

int main() {
    std::string text = ReadFile("text2.txt");

    std::map<char, int> char_freq;
    PQ *pq;
    Huffman huffman;

    huffman.CountFrequency(text, char_freq);
    pq = huffman.CreateTreeNodes(char_freq);
    huffman.CreateHuffmanTree(pq);
    //DebugPQPrint(pq);

    TreeNode *root  = pq->top();
    std::vector<uint8_t> code;
    std::map<char, std::vector<uint8_t>> code_map;

    Debug::printBT(root);

    huffman.GenHuffmanCodes(root, code, code_map);

    int new_size = huffman.GetEncodedTextSize(char_freq, code_map);

    return 0;
}