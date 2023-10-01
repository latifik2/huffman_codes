#pragma once

#include <string>
#include "../lib/BitArray.h"

class App {
public:
    enum Mode {
        ENCODE,
        DECODE
    };

    App(Mode mode, std::string filePath);
    ~App();

    void Init();
    void Run();
    void Encode();
    void Decode();
    void ReadTextFile(const std::string path);
    void ReadBinFile(const std::string path);
    void WriteBinFile(int treeSize, int newSzie, int charsNum, BitArray &BitArray);
    void AppendChar(BitArray &bitArray, char chr);
    void SetBufferTree(BitArray &BitArray, TreeNode *node);
    void SetBuffer(BitArray &bitArray, std::map<char, std::vector<uint8_t>> &codeMap);
    void AllocateMem(int size);
    void RunDecodingLoop(TreeNode* node, BitArray &bitArray, int size, Huffman &huffman);


    template <class T>
    void CheckFile(T &file);

private:
    std::string filePath;
    std::string text;
    Mode mode;
    uint8_t *encodedData;
};