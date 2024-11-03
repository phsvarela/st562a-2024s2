#include "tree_node.h"
#include <vector>
#include <string>
#include <algorithm>
#include <filesystem>

#include <iostream>
using namespace std;
namespace fs = std::filesystem;

// Cria um nó definindo se é um arquivo ou não
TreeNode::TreeNode(const string &val, const fs::path &path, bool file, TreeNode *parent)
    : name(val), path(path), isFile(file), parent(parent)
{
}

// Adiciona um filho no nó
void TreeNode::addChild(TreeNode *node)
{
    node->parent = this;
    children.push_back(node);
}

// Retira um nó da lista de filhos
void TreeNode::removeChild(TreeNode *node)
{
    vector<TreeNode *> &siblings = node->getParent()->getChildren();
    auto it = std::remove(siblings.begin(), siblings.end(), node);
    siblings.erase(it, siblings.end());
}

// Pega o nome do nó (importante para interação com usuário)
string TreeNode::getName() const
{
    return name;
}

// Pega o path do nó
fs::path TreeNode::getPath() const
{
    return path;
}

// Pega o nó pai
TreeNode *TreeNode::getParent() const
{
    return parent;
}

// Verifica se é arquivo ou não (importante para a construção da hierarquia da arvore)
bool TreeNode::getIsFile() const
{
    return isFile;
}

// Pega lista de filhos do nó
vector<TreeNode *> &TreeNode::getChildren()
{
    return children;
}

// Busca um filho pelo nome
TreeNode *TreeNode::findChild(string &name)
{
    for (TreeNode *child : this->getChildren())
    {
        if (child->getName() == name)
        {
            return child;
        }
    }

    return nullptr;
}

// Verifica se esse nó é realmente filho do pai
bool TreeNode::isChild(TreeNode *node)
{
    vector<TreeNode *> &siblings = node->getParent()->getChildren();
    return find(siblings.begin(), siblings.end(), node) != siblings.end();
}

// Editar o nome do nó atual
void TreeNode::updateName(const string &newName)
{
    this->name = newName;
}

// Editar o path do nó atual
void TreeNode::updatePath(const fs::path &newPath)
{
    this->path = newPath;
}
