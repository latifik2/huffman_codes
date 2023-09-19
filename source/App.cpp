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

App::App(Mode mode, std::string filePath)
: mode(mode), filePath(filePath) {
}

App::~App() {
    delete[] this->encodedData;
}

void App::Init() {
    if (this->mode == Mode::encode)
        ReadTextFile(this->filePath);
    
}

void App::Run() {
    Huffman huffman;
    TreeNode *root;
    std::vector<uint8_t> code;

    huffman.CountFrequency(this->text);
    huffman.CreateTreeNodes();
    huffman.CreateHuffmanTree();

    root = huffman.pq->top();
    huffman.GenHuffmanCodes(root, code);
   
    Debug::printBT(root);
    int newSize = huffman.GetEncodedTextSize();
    
    BitArray bitArray(newSize);

    SetBufferTree(bitArray, root);
    bitArray.AlignIndex();
    int treeSize = bitArray.GetOperations();

    SetBuffer(bitArray, huffman.codeMap);

    WriteBinFile(treeSize, bitArray);
}


void App::ReadTextFile(const std::string path) {
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

void App::ReadBinFile(const std::string path) {}

void App::WriteBinFile(int treeSize, BitArray &bitArray) {
    std::ofstream file;
    encodedData = bitArray.get_bit_array();

    file.open("../EncodedData", std::ios::out | std::ios::binary);

    if (!file.is_open()) {
        Debug::DebugPrint("Unable to open file.");
        return;
    }   

    file.write(reinterpret_cast<const char*>(&treeSize), 4);
    file.write(reinterpret_cast<const char*>(encodedData), bitArray.GetSize());
}

void App::AppendChar(BitArray &bitArray, char chr) {
    for (uint8_t i = 0; i < 8; i++) {
        bitArray.append_bit(chr & 1);
        chr >>= 1;
    }
}

void App::SetBufferTree(BitArray &bitArray, TreeNode *node) {
    bitArray.CountOperations();
    if (node->character != 0) {
        bitArray.append_bit(0);
        AppendChar(bitArray, node->character);
        return;
    }
    bitArray.append_bit(1);
    SetBufferTree(bitArray, node->left);
    SetBufferTree(bitArray, node->right);
}

void App::SetBuffer(BitArray &bitArray, std::map<char, std::vector<uint8_t>> &codeMap) {
    for (const auto &chr : text) {
        auto code = codeMap[chr];
        for (auto it = code.begin(); it != code.end(); it++)
            bitArray.append_bit(*it);
    }
}


int main(int argc, char *argv[]) {

    if (argc < 2) {
        Debug::DebugPrint("Not enough args.\nUsage: ./App encode/decode");
        return -1;
    }

    std::string filePath(argv[1]);
    App app(App::Mode::encode, filePath);
    app.Init();
    app.Run();

    return 0;
}