#pragma once

#include <string>
#include "../lib/BitArray.h"

class App {
public:
    enum Mode {
        encode,
        decode
    };

    App(Mode mode, std::string filePath);
    ~App();

    void Init();
    void Run();
    void ReadTextFile(const std::string path);
    void ReadBinFile(const std::string path);
    void WriteBinaryFile();
    void AppendChar(BitArray &bitArray, char chr);
    void SetBufferTree(BitArray &BitArray, TreeNode *node);
    void SetBuffer(BitArray &bitArray, std::map<char, std::vector<uint8_t>> &codeMap);

private:
    std::string filePath;
    std::string text;
    Mode mode;
    uint8_t *encodedData;
};