#ifndef TREE_NODE_H
#define TREE_NODE_H

#include <vector>
#include <string>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

// Classe que define o nó da arvore
class TreeNode
{
private:
    string name;
    fs::path path;
    vector<TreeNode *> children;
    TreeNode *parent;
    bool isFile;

public:
    // Construtor e Destrutor da classe
    TreeNode(const string &val, const fs::path &path, bool file, TreeNode *parent = nullptr);

    // Prototipos das funções para Nós de Arvore
    void addChild(TreeNode *node);
    string getName() const;
    fs::path getPath() const;
    TreeNode *getParent() const;
    bool getIsFile() const;
    void removeChild(TreeNode *node);
    vector<TreeNode *> &getChildren();
    TreeNode *findChild(string &name);
    bool isChild(TreeNode *node);
    void updateName(const string &newName);
    void updatePath(const fs::path &newPath);
};

#endif // TREE_NODE_H