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
: mode(mode), filePath(filePath), fileSize(0) {

    ReadBinFile(this->filePath);
}

App::~App() {
    if (mode == ENCODE)
        delete[] sourceData;
    else
        delete[] encodedData;
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
    // TreeNode *root;
    std::vector<uint8_t> code;

    huffman.CountFrequency(sourceData, fileSize);
    huffman.CreateTreeNodes();
    huffman.CreateHuffmanTree();

    huffman.root = huffman.pq->top();
    huffman.GenHuffmanCodes(huffman.root, code);
   
    Debug::printBT(huffman.root);
    int newSize = huffman.GetEncodedTextSize();
    Debug::DebugPrint<int>(newSize);

    int charsNum = huffman.GetCharsNum();
    int nodesNum = huffman.GetNodesNum();
    BitArray bitArray(8 * charsNum + newSize + nodesNum);

    SetBufferTree(bitArray, huffman.root);
    //bitArray.AlignIndex();
    int treeSize = bitArray.GetOperations();

    SetBuffer(bitArray, huffman.codeMap);

    WriteBinFile(treeSize, newSize, charsNum, nodesNum, bitArray);

    
}

void App::Decode() {
    int treeSize = *reinterpret_cast<int*>(&encodedData[0]);
    int encodedDataSize = *reinterpret_cast<int*>(&encodedData[4]);
    int charsNum = *reinterpret_cast<int*>(&encodedData[8]);
    int nodesNum = *reinterpret_cast<int*>(&encodedData[12]);
    BitArray bitArray(&encodedData[16], encodedDataSize + charsNum * 8 + nodesNum);

    Huffman huffman;
    //TreeNode *root = new TreeNode(0);
    huffman.root = new TreeNode(0);
    uint8_t test = bitArray.PopBit();

    huffman.root->left = huffman.RestoreHuffmanTree(huffman.root->left, bitArray, true);
    huffman.root->right = huffman.RestoreHuffmanTree(huffman.root->right, bitArray, false);
    
    RunDecodingLoop(huffman.root, bitArray, encodedDataSize, huffman);

    Debug::DebugPrint(text);
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
    fileSize = file.tellg();
    file.seekg(0, std::ios::beg);
    AllocateMem(fileSize);

    uint8_t* pTmp;
    if (mode == ENCODE)
        pTmp = sourceData;
    else
        pTmp = encodedData;

    file.read(reinterpret_cast<char *>(pTmp), fileSize);


    file.close();
}

void App::WriteBinFile(int treeSize, int newSize, int charsNum, int nodesNum, BitArray &bitArray) {
    std::ofstream file;
    uint8_t *data = bitArray.GetBitArray();

    file.open("EncodedData", std::ios::out | std::ios::binary);

    CheckFile<std::ofstream>(file);
    //int size = charsNum * 8 + newSize;

    file.write(reinterpret_cast<const char*>(&treeSize), sizeof(int));
    file.write(reinterpret_cast<const char*>(&newSize), sizeof(int));
    file.write(reinterpret_cast<const char*>(&charsNum), sizeof(int));
    file.write(reinterpret_cast<const char*>(&nodesNum), sizeof(int));
    file.write(reinterpret_cast<const char*>(data), bitArray.GetSize());

    file.close();
}

void App::AppendChar(BitArray &bitArray, char chr) {
    for (uint8_t i = 0; i < 8; i++) {
        bitArray.AppendBit(BitArray::BitState((chr & 0x80) >> 7));
        chr <<= 1;
    }
}

void App::SetBufferTree(BitArray &bitArray, TreeNode *node) {
    bitArray.CountOperations();
    if (node->character != 0) {
        bitArray.AppendBit(BitArray::OFF);
        AppendChar(bitArray, node->character);
        return;
    }
    bitArray.AppendBit(BitArray::ON);
    SetBufferTree(bitArray, node->left);
    SetBufferTree(bitArray, node->right);
}

void App::SetBuffer(BitArray &bitArray, std::map<char, std::vector<uint8_t>> &codeMap) {
    for (const auto &chr : text) {
        auto code = codeMap[chr];

        for (auto it = code.begin(); it != code.end(); it++)
            bitArray.AppendBit(BitArray::BitState(*it));
    }
}

void App::AllocateMem(int size) {
    if (mode == ENCODE)
        sourceData = new uint8_t[size];
    else
        encodedData = new uint8_t[size];
}


template <class T>
void App::CheckFile(T &file) {
    if (!file.is_open()) {
        Debug::DebugPrint("Unable to open file.");
        exit(-1);
    }   
}

void App::RunDecodingLoop(TreeNode* node, BitArray &bitArray, int size, Huffman &huffman) {

    while (bitArray.GetOperations() != size) {
        text += huffman.DecodeCodes(node, bitArray);
        //bitArray.CountOperations();
    }
}


int main(int argc, char *argv[]) {

    if (argc < 3) {
        Debug::DebugPrint("Not enough args.\nUsage: ./App e/d {filepath}");
        return -1;
    }
    App::Mode mode = App::BAD_VALUE;
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

    if (mode == App::BAD_VALUE) {
        Debug::DebugPrint("Bad argument.\nUsage: ./App e/d {filepath}");
        return -1;
    }

    std::string filePath(argv[2]);

    App app(mode, filePath);
    app.Run();

    return 0;
}