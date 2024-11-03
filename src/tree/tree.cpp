#include "tree.h"
#include "../utils/utils.h"
#include "../file/file_utils.h"
#include <iostream>
#include <filesystem>
#include <algorithm>
#include <iomanip>

using namespace std;
namespace fs = std::filesystem;

// Construtor
// Cria um nó a partir do diretorio atual (./) e a partir dele cria uma arvore, setando esse nó como raiz
Tree::Tree()
{
    root = new TreeNode("root", fs::current_path(), false);
    currentNode = root;

    buildTree(currentNode, fs::current_path());
}

// Destrutor
// Destroi a arvoré e libera o espaço de memória dos nós
Tree::~Tree()
{
    deleteTree(root);
}

// Metodo responsável por criar a arvore de nós
void Tree::buildTree(TreeNode *node, const fs::path &currentPath)
{
    // para cada arquivo do diretório, cria um nó e seta como filho do nó atual
    // para cada subdiretorio do diretorio, chama a função recursivamente
    for (const auto &entry : fs::directory_iterator(currentPath))
    {
        string name = entry.path().filename().string();
        fs::path path = entry.path();
        TreeNode *newNode = new TreeNode(name, path, fs::is_regular_file(entry.status()));

        node->addChild(newNode); // seta como filho do nó atual

        if (!newNode->getIsFile()) // se nao for arquivo, chama recursivamente
        {
            Tree::buildTree(newNode, path);
        }
    }
}

// Metodo responsável por deletar a árvore (usar quando o programa for encerrado)
void Tree::deleteTree(TreeNode *node)
{
    if (node == nullptr)
        return;
    // chama recursivamenete a função para cada nó para garantir que nenhum filho vai se perder
    for (TreeNode *child : node->getChildren())
    {
        Tree::deleteTree(child);
    }

    delete node;
}

// Metodo responsável por adicionar um arquivo ou pasta na arvore
void Tree::addFile()
{
    cout << endl
         << "Digite o nome do arquivo a ser criado: " << endl;
    string fileName = Utils::validaInputFileName();

    cout << endl
         << "Qual o tipo do arquivo?" << endl
         << "1. Pasta." << endl
         << "2. Arquivo de texto." << endl;
    int tipo = Utils::validaInputOperacao12();
    bool isFile = false;

    if (tipo == 2)
    {
        fileName += ".txt";
        isFile = true;
    }

    // busca o arquivo na arvore
    TreeNode *fileExist = currentNode->findChild(fileName);
    if (fileExist != nullptr)
    {
        cout << endl
             << "Erro: Ja existe um arquivo com esse nome nesse diretorio!";
        return;
    }

    fs::path currentPath = currentNode->getPath();
    fs::path newPath = currentPath / fileName; // concatena o path atual com o nome do novo arquivo

    if (isFile)
    {
        if (FileUtils::criarArquivoNoDisco(newPath))
        {
            currentNode->addChild(new TreeNode(fileName, newPath, isFile));
        }
    }
    else
    {
        if (FileUtils::criarPastaNoDisco(newPath))
        {
            currentNode->addChild(new TreeNode(fileName, newPath, isFile));
        }
    }
}

// Metodo responsável por deletar um arquivo ou pasta da arvore
void Tree::deleteFile()
{
    cout << endl
         << "Digite o nome do arquivo a ser deletado: " << endl;
    string fileName = Utils::validaInputFileName();

    cout << endl
         << "Qual o tipo do arquivo?" << endl
         << "1. Pasta." << endl
         << "2. Arquivo de texto." << endl;
    int tipo = Utils::validaInputOperacao12();

    if (tipo == 2)
    {
        fileName += ".txt";
    }

    TreeNode *fileExist = currentNode->findChild(fileName);
    if (fileExist != nullptr)
    {
        if (tipo == 1)
        {
            // tratamento para impedir remoção das pastas da biblioteca 'src'
            if ((fileName == "src" && fileExist->getParent()->getName() == "root") ||
                (fileName == "file" && fileExist->getParent()->getName() == "src") ||
                (fileName == "tree" && fileExist->getParent()->getName() == "src") ||
                (fileName == "utils" && fileExist->getParent()->getName() == "src"))
            {
                cout << endl
                     << "Erro: Impossivel excluir esse recurso" << endl;
                return;
            }
        }
        // verifica se é arquivo ou subdiretorio
        if (!fileExist->getIsFile())
        {
            // se nao for arquivo, verifica se o subdiretorio tem filhos
            if (fileExist->getChildren().size() > 0)
            {
                cout << endl
                     << "Essa pasta contem arquivos." << endl
                     << "Tem certeza que deseja excluir ela? [s/n]" << endl;
                char confirmacao = Utils::validaConfirmacao();

                // chama a funcao de deletar a arvore do subdiretorio
                if (confirmacao == 's')
                {
                    Tree::deleteDirectoryTree(fileExist);
                }
            }
            else
            {
                // deleta o proprio subdiretorio e remove o nó da arvore
                if (FileUtils::excluirArquivo(fileExist->getPath()))
                {
                    Tree::removeNodeFromTree(fileExist);
                }
            }
        }
        // se for arquivo, deleta o proprio arquivo e remove o nó da arvore
        else
        {
            if (FileUtils::excluirArquivo(fileExist->getPath()))
            {
                Tree::removeNodeFromTree(fileExist);
            }
        }
    }
    else
    {
        cout << endl
             << "Erro: Pasta ou arquivo nao encontrado." << endl;
        return;
    }
}

// Metodo responsavel por deletar toda a hierarquia de um diretorio incluindo arquivos e pastas
void Tree::deleteDirectoryTree(TreeNode *node)
{
    // para cada nó filho do nó atual
    for (TreeNode *child : node->getChildren())
    {
        // se for arquivo, deleta o arquivo e remove o nó da lista de filhos
        if (child->getIsFile())
        {
            if (FileUtils::excluirArquivo(child->getPath()))
            {
                Tree::removeNodeFromTree(child);
            }
        }
        // se nao, chama a funcao recursivamente
        else
        {
            Tree::deleteDirectoryTree(child);

            // após deletar todos os arquivos recursivamente, deleta o próprio nó
            if (FileUtils::excluirArquivo(child->getPath()))
            {
                Tree::removeNodeFromTree(child);
            }
        }
    }

    // após deletar todos os nós filhos e filhos dos filhos, deleta o primeiro nó que chamou a funcao
    if (node->getChildren().empty() && FileUtils::excluirArquivo(node->getPath()))
    {
        Tree::removeNodeFromTree(node);
    }

    delete node;
}

// Remove nó da arvore
void Tree::removeNodeFromTree(TreeNode *node)
{
    // verifica se o nó é de fato filho
    if (node->isChild(node))
    {
        // se o ponteiro do nó atual estiver apontando para o nó que sera removido, move o ponteiro para o pai
        if (node == currentNode)
        {
            currentNode = currentNode->getParent();
            currentNode->removeChild(node);
        }
        else
        {
            node->getParent()->removeChild(node);
        }
    }
}

// Função para mover o ponteiro do nó atual para dentro de um novo diretório
void Tree::enterDirectory()
{
    cout << endl
         << "Digite o nome do diretorio que voce quer acessar: " << endl;
    string name = Utils::validaInputFileName();

    // busca o nó
    TreeNode *fileExist = currentNode->findChild(name);
    if (fileExist != nullptr)
    {
        // tratamento para impedir acessar a biblioteca 'src'
        if (fileExist->getName() == "src" && fileExist->getParent()->getName() == "root")
        {
            cout << endl
                 << "Erro: Impossivel acessar esse recurso." << endl;
        }

        // ponteiro do nó atual recebe o novo nó
        currentNode = fileExist;
        cout << endl
             << "Diretorio atual: " << currentNode->getPath().string() << endl;
        return;
    }
    else
    {
        cout << endl
             << "Erro: Diretorio nao encontrado." << endl;
    }
}

// Função para mover o ponteiro do nó atual para o nó pai
void Tree::goBack()
{
    // tratamento para quando for o nó raiz
    if (currentNode->getParent() != nullptr)
    {
        // aponta o ponteiro para o pai do nó atual
        currentNode = currentNode->getParent();
        cout << endl
             << "Diretorio atual: " << currentNode->getPath().string() << endl;
    }
    else
    {
        cout << endl
             << "Voce ja esta na raiz da arvore" << endl;
    }
}

// Lista o diretorio atual usando o modelo de interface gráfica do dir do Windows
void Tree::listDirectory()
{
    cout << endl
         << setw(30) << left << "Name" << setw(10) << "Type" << setw(10) << "Size (Bytes)" << endl
         << string(60, '-') << endl;

    // itera sobre os arquivos do diretorio atual apresentando nome, tipo e quantidade de bytes
    for (const auto &entry : fs::directory_iterator(currentNode->getPath()))
    {
        cout << setw(30) << left << entry.path().filename().string();
        string type = entry.is_directory() ? "Dir" : "File";
        cout << setw(10) << type;

        if (entry.is_regular_file())
        {
            auto size = fs::file_size(entry);
            cout << setw(10) << size;
        }
        else
        {
            cout << setw(10) << "-";
        }

        cout << endl;
    }
}

// Metodo que busca um arquivo e abre as opcoes para edicao
void Tree::selectAndEditFile()
{
    cout << endl
         << "Digite o nome do arquivo a ser editado: " << endl;
    string fileName = Utils::validaInputFileName();

    cout << endl
         << "Qual o tipo do arquivo?" << endl
         << "1. Pasta." << endl
         << "2. Arquivo de texto." << endl;
    int tipo = Utils::validaInputOperacao12();

    if (tipo == 2)
    {
        fileName += ".txt";
    }

    TreeNode *fileExist = currentNode->findChild(fileName);
    if (fileExist != nullptr)
    {
        cout << endl
             << setw(30) << left << "Name" << setw(10) << "Type" << setw(10) << "Size (Bytes)" << endl
             << string(60, '-') << endl;

        cout << setw(30) << left << fileExist->getName();
        string type = tipo == 1 ? "Dir" : "File";
        cout << setw(10) << type;

        if (tipo == 2)
        {
            auto size = fs::file_size(fileExist->getPath());
            cout << setw(10) << size;
        }
        else
        {
            cout << setw(10) << "-";
        }

        cout << endl;

        if (tipo == 1)
        {
            Tree::editDirectory(fileExist);
            return;
        }
        else
        {
            Tree::editFile(fileExist);
            return;
        }
    }
    else
    {
        cout << endl
             << "Erro: Arquivo nao encontrado." << endl;
        return;
    }
}

// Metodo que abre as opcoes de editar diretorio
void Tree::editDirectory(TreeNode *node)
{
    cout << endl
         << "O que deseja realizar?" << endl
         << "1. Renomear diretorio" << endl
         << "0. Voltar" << endl;
    int escolha = Utils::validaInputOperacao12();

    if (escolha == 1)
    {
        cout << endl
             << "Digite o novo nome para o diretorio: " << endl;
        string fileName = Utils::validaInputFileName();

        fs::path oldPath = node->getPath();
        fs::path parentPath = node->getParent()->getPath();
        fs::path newPath = parentPath / fileName;

        if (FileUtils::renameFile(oldPath, newPath))
        {
            node->updateName(fileName);
            node->updatePath(newPath);
            return;
        }
    }
    cout << endl
         << "Nenhuma informacao foi editada" << endl;
    return;
}

// Metodo que abre as opcoes de editar arquivo
void Tree::editFile(TreeNode *node)
{
    cout << endl
         << "O que deseja realizar?" << endl
         << "1. Renomear arquivo." << endl
         << "2. Inserir texto." << endl
         << "3. Remover texto." << endl
         << "4. Ver conteudo do arquivo." << endl
         << "5. Apagar conteudo do arquivo." << endl
         << "0. Voltar" << endl;
    string texto;
    string fileName;
    fs::path oldPath;
    fs::path parentPath;
    fs::path newPath;
    fs::path path;
    int index = -1;
    int escolha = Utils::validaInputOperacao012345();

    switch (escolha)
    {
    case 1:
        cout << endl
             << "Opcao selecionada: Renomear arquivo." << endl
             << endl
             << "Digite o novo nome para o arquivo: " << endl;

        fileName = Utils::validaInputFileName();
        fileName += ".txt";

        oldPath = node->getPath();
        parentPath = node->getParent()->getPath();
        newPath = parentPath / fileName;

        // se o arquivo foi renomeado corretamente, muda o nome e path dele no nó da arvore
        if (FileUtils::renameFile(oldPath, newPath))
        {
            node->updateName(fileName);
            node->updatePath(newPath);
            return;
        }
    case 2:
        cout << endl
             << "Opcao selecionada: Inserir texto." << endl
             << endl;

        getline(cin, texto);

        path = node->getPath();
        FileUtils::inserirTexto(path, texto);
        return;
    case 3:
        cout << endl
             << "Opcao selecionada: Remover texto." << endl
             << endl
             << "Digite o ID do texto que sera removido: " << endl;

        index = Utils::validaInputNumero();

        path = node->getPath();
        FileUtils::removerTexto(path, index);
        return;
    case 4:
        cout << endl
             << "Opcao selecionada: Ver conteudo do arquivo." << endl
             << endl;

        path = node->getPath();
        FileUtils::imprimirTexto(path);
        return;
    case 5:
        cout << endl
             << "Opcao selecionada: Apagar conteudo do arquivo." << endl
             << endl;

        path = node->getPath();
        FileUtils::apagarConteudoArquivo(path);
        return;
    default:
        cout << endl
             << "Nenhuma informacao foi editada" << endl;
        return;
    }
}
