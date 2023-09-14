#include <iostream>
#include <map>
#include <queue>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>


class Compare;
class TreeNode;

using PQ = std::priority_queue<TreeNode *, std::vector<TreeNode *>, Compare>;


class TreeNode {
private:
    char character;
    int weigth;
    TreeNode *left;
    TreeNode *right;

public:
    TreeNode(int weigth, char character = 0, TreeNode *left = nullptr, TreeNode *right = nullptr) {
        this->weigth = weigth;
        this->left = left;
        this->right = right;
        this->character = character;
    }

    // bool operator()(const TreeNode *&a, const TreeNode *&b) {
    //     return a->weigth > b->weigth;
    // }

    
    friend class Compare;
    friend PQ* _CreateTreeNodes(const std::map<char, int> &charFreq);
    friend PQ* CreateHuffmanTree(PQ *pq);
    friend void GenHuffmanCodes(const TreeNode *node, std::vector<uint8_t> code, std::map<char, std::vector<uint8_t>> &code_map);
    friend void DebugPQPrint(PQ *pq);
    friend void printBT(const std::string& prefix, const TreeNode* node, bool isLeft);

    
};

class Compare {
public:
    bool operator()(const TreeNode *a, const TreeNode *b) {
        return a->weigth > b->weigth;
    }
};

//using PQ = std::priority_queue<TreeNode *, std::vector<TreeNode *>, Compare>;



void DebugPrint(std::string text) {
    std::cout << text << std::endl;
}

void DebugPQPrint(PQ *pq) {
    while (!pq->empty()) {
        std::cout << pq->top()->weigth << std::endl;
        pq->pop();
    }
}

PQ* _CreateTreeNodes(const std::map<char, int> &charFreq) {

    PQ *pq = new std::priority_queue<TreeNode *, std::vector<TreeNode *>, Compare>();

    for (auto it = charFreq.begin(); it != charFreq.end(); it++)
        pq->push(new TreeNode(it->second, it->first));

    return pq;
}

PQ* CreateHuffmanTree(PQ *pq) {
    while (pq->size() > 1) {
        auto tmp1 = pq->top();
        pq->pop();
        auto tmp2 = pq->top();
        pq->pop();
        pq->push(new TreeNode(tmp1->weigth + tmp2->weigth, 0, tmp1, tmp2));
    }

    return pq;
}

void GenHuffmanCodes(const TreeNode *node, std::vector<uint8_t> code, std::map<char, std::vector<uint8_t>> &code_map) {
    if (node->character != 0) {
        code_map[node->character] = code;
        code.clear();
        return;
    }

    if (node->left != nullptr) {
        code.push_back(0);
        GenHuffmanCodes(node->left, code, code_map);
        code.pop_back();
    }

    if (node->right != nullptr) {
        code.push_back(1);
        GenHuffmanCodes(node->right, code, code_map);
        code.pop_back();
    }

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

int GetEncodedTextSize(const std::map<char, int> &char_freq, const std::map<char, std::vector<uint8_t>> &code_map) {
    int size = 0;

    auto it = char_freq.begin();
    auto it2 = code_map.begin();

    while (it != char_freq.end()) {
        size += it->second * it2->second.size();
        it++;
        it2++;
    }
    return size;
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


void printBT(const std::string& prefix, const TreeNode* node, bool isLeft)
{
    if( node != nullptr )
    {
        std::cout << prefix;

        std::cout << (isLeft ? "├──" : "└──" );

        // print the value of the node
        std::cout << node->weigth << std::endl;

        // enter the next tree level - left and right branch
        printBT( prefix + (isLeft ? "│   " : "    "), node->left, true);
        printBT( prefix + (isLeft ? "│   " : "    "), node->right, false);
    }
}

void printBT(const TreeNode* node)
{
    printBT("", node, false);    
}

// pass the root node of your binary tree


int main() {
    std::string text = ReadFile("text2.txt");
    //DebugPrint(text);
    std::map<char, int> char_freq;
    PQ *pq;


    CountFrequency(text, char_freq);
    pq = _CreateTreeNodes(char_freq);
    CreateHuffmanTree(pq);
    //DebugPQPrint(pq);

    TreeNode *root  = pq->top();
    std::vector<uint8_t> code;
    std::map<char, std::vector<uint8_t>> code_map;

    printBT(root);

    GenHuffmanCodes(root, code, code_map);

    int new_size = GetEncodedTextSize(char_freq, code_map);

    return 0;
}
