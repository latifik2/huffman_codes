#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <queue>

#include "../headers/Huffman.h"
#include "../headers/Debug.h"
#include "../headers/App.h"
#include "../lib/BitArray.h"

App::App(Mode mode, std::string filePath) {
    this->mode = mode;
    this->filePath = filePath;
}

App::~App() {
    delete[] this->encodedData;
}

void App::Init() {
    if (this->mode == Mode::encode)
        ReadFile(this->filePath);
    
}

void App::ReadFile(const std::string path) {
    std::ifstream file;
    std::stringstream buffer;

    file.open(path, std::ios::in);

    if (!file.is_open()) {
        Debug::DebugPrint("Unable to open file.");
        return;
    }   

    buffer << file.rdbuf();
    this->text = buffer.str();
}

int main(int argc, char *argv[]) {

    if (argc < 2) {
        Debug::DebugPrint("Not enough args.\nUsage: ./App encode/decode");\
        return -1;
    }


    

    
    // Huffman huffman;

    // huffman.CountFrequency(text);
    // pq = huffman.CreateTreeNodes();
    // huffman.CreateHuffmanTree(pq);
    // //DebugPQPrint(pq);

    // TreeNode *root  = pq->top();
    

    // Debug::printBT(root);

    // huffman.GenHuffmanCodes(root, code, code_map);

    // int new_size = huffman.GetEncodedTextSize(char_freq, code_map);

    return 0;
}