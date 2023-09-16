#pragma once

#include <string>

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

private:
    std::string filePath;
    std::string text;
    Mode mode;
    uint8_t *encodedData;
};