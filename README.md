# Manga Manager

Este é um programa de gerenciamento de mangás desenvolvido em C++ usando Qt para a interface gráfica. O programa permite adicionar, editar, remover, visualizar e pesquisar mangás.

![image](https://github.com/EduardoWS/Manga-Manager/assets/81593054/72be186b-6792-4a72-aabf-0636f5f70a9c)


## Estrutura do Projeto

- `main.cpp`: Ponto de entrada do programa. Inicializa a aplicação Qt e exibe a janela principal.
- `mainwindow.cpp`: Implementação da classe `MainWindow`, que gerencia a interface gráfica principal do programa, incluindo a tabela de mangás e os botões de adicionar, editar e remover.
- `mainwindow.h`: Declaração da classe `MainWindow`.
- `manga.cpp`: Implementação da classe `Manga`, que representa um mangá individual com todos os seus atributos.
- `manga.h`: Declaração da classe `Manga`.
- `mangamanager.cpp`: Implementação da classe `MangaManager`, que gerencia a adição, edição, remoção e carregamento de mangás, bem como a manutenção dos índices primários e secundários.
- `mangamanager.h`: Declaração da classe `MangaManager`.
- `addmangadialog.cpp`: Implementação da classe `AddMangaDialog`, que fornece uma interface gráfica para adicionar ou editar mangás.
- `addmangadialog.h`: Declaração da classe `AddMangaDialog`.
- `MangaManager.pro`: Arquivo de projeto do Qt Creator, que define as configurações de construção e os arquivos fontes do projeto.

## Como Compilar

### Pré-requisitos

- Qt 5.x ou superior
- Qt Creator (opcional, mas recomendado)

### Passos para Compilar

1. Abra o Qt Creator.
2. Clique em `File > Open File or Project...`.
3. Selecione o arquivo `MangaManager.pro`.
4. Clique em `Configure Project`.
5. Clique em `Build > Build Project` para compilar o projeto.
6. Clique em `Run` para executar o programa.

## Como Usar

1. **Adicionar Mangá**: Clique no botão "Adicionar" e preencha as informações.
2. **Editar Mangá**: Selecione um mangá na tabela e clique no botão "Editar".
3. **Remover Mangá**: Selecione um mangá na tabela e clique no botão "Excluir".
4. **Visualizar Mangás**: Os mangás adicionados são listados na tabela.
5. **Pesquisar Mangás**: Use o Entry Text para inserir o título de um Mangá e o botão Pesquisar para realizar a busca. O buscador irá mostrar todos os Mangás com o mesmo título.

