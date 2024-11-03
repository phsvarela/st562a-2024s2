#ifndef TREE_H
#define TREE_H

#include "tree_node.h"
#include <string>

using namespace std;

// Classe que define a arvore
// Estrutura hierarquica básica de nós que contém lista de nós
class Tree
{
private:
    // Uma arvore que contém um nó principal, o qual tem sua lista de nós filhos
    // que contém seus nós filhos, e o nó do diretório atual
    TreeNode *root;
    TreeNode *currentNode;

    void deleteTree(TreeNode *node);
    void buildTree(TreeNode *node, const fs::path &currentPath);
    void removeNodeFromTree(TreeNode *node);

public:
    Tree();
    ~Tree();

    void addFile();
    void deleteFile();
    void deleteDirectoryTree(TreeNode *node);
    void enterDirectory();
    void goBack();
    void listDirectory();
    void selectAndEditFile();
    void editDirectory(TreeNode *node);
    void editFile(TreeNode *node);
};

#endif // TREE_H