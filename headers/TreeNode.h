#include <map>
#include <queue>
#include <vector>
#include <string>


class Compare;
class Huffman;
class TreeNode;
class Debug;

using PQ = std::priority_queue<TreeNode *, std::vector<TreeNode *>, Compare>;

class TreeNode {
public:
    TreeNode(int weigth, char character = 0, TreeNode *left = nullptr, TreeNode *right = nullptr);


    friend class Compare;
    friend class Huffman;
    friend class Debug;
    //friend PQ* CreateTreeNodes(const std::map<char, int> &charFreq);
    // friend PQ* CreateHuffmanTree(PQ *pq);
    // friend void GenHuffmanCodes(const TreeNode *node, std::vector<uint8_t> code, std::map<char, std::vector<uint8_t>> &code_map);
    // friend void DebugPQPrint(PQ *pq);
    // friend void printBT(const std::string& prefix, const TreeNode* node, bool isLeft);

private:
    char character;
    int weigth;
    TreeNode *left;
    TreeNode *right;
};