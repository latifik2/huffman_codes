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
    if (this->mode == Mode::ENCODE)
        ReadTextFile(this->filePath);
    else
        ReadBinFile(this->filePath);
    
}

void App::Run() {
    switch (mode)
    {
    case ENCODE:
        Encode();
        break;

    case DECODE:
        Decode();
        break;

    default:
        break;
    }
}

void App::Encode() {
    Huffman huffman;
    TreeNode *root;
    std::vector<uint8_t> code;

    huffman.CountFrequency(this->text);
    huffman.CreateTreeNodes();
    huffman.CreateHuffmanTree();

    root = huffman.pq->top();
    huffman.GenHuffmanCodes(root, code);
   
    //Debug::printBT(root);
    int newSize = huffman.GetEncodedTextSize();
    Debug::DebugPrint<int>(newSize);
    
    BitArray bitArray(newSize);

    SetBufferTree(bitArray, root);
    bitArray.AlignIndex();
    int treeSize = bitArray.GetOperations();

    SetBuffer(bitArray, huffman.codeMap);

    WriteBinFile(treeSize, newSize, bitArray);
}

void App::Decode() {
    int treeSize = *reinterpret_cast<int*>(&encodedData[0]);
    int encodedDataSize = *reinterpret_cast<int*>(&encodedData[4]);
    BitArray bitArray(&encodedData[8], encodedDataSize);

    TreeNode *root = new TreeNode(0);
    uint8_t test = bitArray.PopBit();

}


void App::ReadTextFile(const std::string path) {
    std::ifstream file;
    std::stringstream buffer;

    file.open(path, std::ios::in);

    CheckFile<std::ifstream>(file);

    buffer << file.rdbuf();
    this->text = buffer.str();

    file.close();
}

void App::ReadBinFile(const std::string path) {
    std::ifstream file;

    file.open(filePath, std::ios::in | std::ios::binary);

    CheckFile<std::ifstream>(file);

    file.seekg(0, std::ios::end);
    int size = file.tellg();
    file.seekg(0, std::ios::beg);
    AllocateMem(size);

    file.read(reinterpret_cast<char *>(encodedData), size);


    file.close();
}

void App::WriteBinFile(int treeSize, int newSize, BitArray &bitArray) {
    std::ofstream file;
    encodedData = bitArray.GetBitArray();

    file.open("../EncodedData", std::ios::out | std::ios::binary);

    CheckFile<std::ofstream>(file); 

    file.write(reinterpret_cast<const char*>(&treeSize), sizeof(int));
    file.write(reinterpret_cast<const char*>(&newSize), sizeof(int));
    file.write(reinterpret_cast<const char*>(encodedData), bitArray.GetSize());

    file.close();
}

void App::AppendChar(BitArray &bitArray, char chr) {
    for (uint8_t i = 0; i < 8; i++) {
        bitArray.AppendBit(chr & 1);
        chr >>= 1;
    }
}

void App::SetBufferTree(BitArray &bitArray, TreeNode *node) {
    bitArray.CountOperations();
    if (node->character != 0) {
        bitArray.AppendBit(0);
        AppendChar(bitArray, node->character);
        return;
    }
    bitArray.AppendBit(1);
    SetBufferTree(bitArray, node->left);
    SetBufferTree(bitArray, node->right);
}

void App::SetBuffer(BitArray &bitArray, std::map<char, std::vector<uint8_t>> &codeMap) {
    for (const auto &chr : text) {
        auto code = codeMap[chr];

        for (auto it = code.begin(); it != code.end(); it++)
            bitArray.AppendBit(*it);
    }
}

void App::AllocateMem(int size) {
    encodedData = new uint8_t[size];
}


template <class T>
void App::CheckFile(T &file) {
    if (!file.is_open()) {
        Debug::DebugPrint<char const [21]>("Unable to open file.");
        exit(-1);
    }   
}


int main(int argc, char *argv[]) {

    if (argc < 3) {
        Debug::DebugPrint<char const[]>("Not enough args.\nUsage: ./App e/d {filepath}");
        return -1;
    }
    App::Mode mode;
    switch (*argv[1])
    {
    case 'e':
        mode = App::ENCODE;
        break;
    
    case 'd':
        mode = App::DECODE;
        break;

    default:
        break;
    }

    std::string filePath(argv[2]);


    App app(mode, filePath);
    app.Init();
    app.Run();

    return 0;
}