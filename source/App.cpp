#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <queue>

#include "../headers/Huffman.h"
#include "../headers/Debug.h"
#include "../headers/App.h"
//#include "../lib/BitArray.h"

App::App(Mode mode, std::string filePath) {
    this->mode = mode;
    this->filePath = filePath;
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
    // //DebugPQPrint(pq);
    // TreeNode *root  = pq->top();
    Debug::printBT(root);
    // int new_size = huffman.GetEncodedTextSize(char_freq, code_map);
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

void App::ReadBinFile(const std::string path) {
}

int main(int argc, char *argv[]) {

    if (argc < 2) {
        Debug::DebugPrint("Not enough args.\nUsage: ./App encode/decode");\
        return -1;
    }

    std::string filePath(argv[1]);
    App app(App::Mode::encode, filePath);
    app.Init();
    app.Run();

    return 0;
}