#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <sstream>

class TreeNode {
public:
    
    int weigth;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int weigth, TreeNode *left = nullptr, TreeNode *right = nullptr) {
        this->weigth = weigth;
        this->left = left;
        this->right = right;
    }
};

void DebugPrint(std::string text) {
    std::cout << text << std::endl;
}

void CountFrequency(std::string text, std::map<char, int> &charFreq) {
    

    for (const auto &chr : text) {
        auto it = charFreq.find(chr);
        if (it != charFreq.end())
            it->second += 1;
        else
            charFreq[chr] = 1;
    }

}

std::string ReadFile(const std::string path) {
    std::ifstream file;
    std::stringstream buffer;
    std::string text;

    file.open(path, std::ios::in);

    if (!file.is_open()) {
        DebugPrint("Unable to open file.");
        return nullptr;
    }   
    // file >> text;
    // file.close();

    buffer << file.rdbuf();
    return buffer.str();
}

int main() {
    std::string text = ReadFile("text.txt");
    DebugPrint(text);
    std::map<char, int> charFreq;
    CountFrequency(text, charFreq);

    return 0;
}
