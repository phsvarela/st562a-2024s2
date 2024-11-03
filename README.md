# st562a-2024s2

Esse programa foi desenvolvido para a matéria de Estrutura de Arquivos ST562A do 2º Semestre de 2024 da Faculdade de Tecnologia(FT) da Unicamp.

O objetivo desse programa é gerenciar arquivos de uma forma dinâmica e automática mantendo os critérios de inserção, remoção, edição e visuliazação de dados de um arquivo.

Para o critério de edição de arquivos, ao inserir ou remover dados de um arquivo, é possível perceber que o tamanho do mesmo também altera, mantendo o critério de tamanho de arquivo.

Esse gerenciador de arquivos conta com a criação de uma árvore simples a partir do diretório atual, sendo o próprio diretório a raiz da árvore. Assim sendo, a manipulação de arquivos acontece dentro e a partir desse diretório.

Para compilar o programa, é necessário ter C++ 17 instalado e um compilador capaz de suportar essa versão

Comando para compilação: g++ main.cpp src/utils/utils.cpp src/file/file_utils.cpp src/tree/tree.cpp src/tree/tree_node.cpp -o main

Comando para rodar o programa: ./main