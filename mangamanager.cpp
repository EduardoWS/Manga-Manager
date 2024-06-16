#include "mangamanager.h"
#include <QFile>
#include <QTextStream>
#include <QIODevice>
#include <QDebug>
#include <QDataStream>
#include <iostream>

MangaManager::MangaManager(const QString &basePath) : nextId(0) {
    dataFileName = basePath + "/manga_data.csv";
    indexFileName = basePath + "/manga_index.csv";
    secondaryIndexFileName = basePath + "/manga_secondary_index.csv";
    nextIdFileName = basePath + "/next_id.txt";
    loadIndices();
    loadNextId();
    updateSecondaryIndex();
}

void MangaManager::loadNextId() {
    // Esse método carrega o próximo ID a partir de um arquivo de texto
    QFile file(nextIdFileName);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        in >> nextId;
        file.close();
    } else {
        nextId = 0;
    }
}

void MangaManager::saveNextId() {
    // Esse método atualiza o arquivo de texto que armazena o próximo ID
    QFile file(nextIdFileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << nextId;
        file.close();
    }
}


void MangaManager::addManga(const Manga &manga) {
    // Esse método é chamado quando um novo mangá é adicionado ao sistema
    // O ID do mangá é incrementado e salvo no arquivo de índices primários
    // O mangá é salvo no arquivo de dados e a posição do mangá é salva no arquivo de índices primários
    Manga mangaToAdd = manga;
    mangaToAdd.id = nextId++;
    QFile dataFile(dataFileName);
    if (dataFile.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&dataFile);
        out.setCodec("UTF-8");
        qint64 position = out.pos();
        mangaToAdd.saveToStream(out);
        qDebug() << "Adding manga at position:" << position; // Debug statement
        primaryIndices.append(position);
        qDebug() << "primaryIndices in addManga: " << primaryIndices;
        dataFile.close();
        updateSecondaryIndex();
        saveIndices();
        saveNextId();  // Salvar o próximo ID após adicionar um novo mangá
    } else {
        qDebug() << "Failed to open data file for appending";
    }
}


Manga MangaManager::getMangaByIndex(int index) {
    // Esse método é chamado quando um mangá é selecionado para visualização
    // O método carrega o mangá a partir do arquivo de dados na posição indicada pelo índice primário
    // O índice primário é um vetor de posições no arquivo de dados
    if (index < 0 || index >= primaryIndices.size()) {
        qDebug() << "Invalid index";
        return Manga();
    }
    Manga manga;
    qDebug() << "primaryIndices in getMangaByIndex: " << primaryIndices;
    
    QFile dataFile(dataFileName);
    if (dataFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&dataFile);
        in.setCodec("UTF-8");
        qDebug() << "Seeking position:" << primaryIndices[index]; // Debug statement
        in.seek(primaryIndices[index]);
        manga.loadFromStream(in);
        dataFile.close();
    }
    return manga;
}

void MangaManager::updateSecondaryIndex() {
    // Esse método atualiza o índice secundário para títulos
    // O índice secundário é um mapa de títulos para listas de IDs de mangás
    // O método é chamado após adicionar ou remover um mangá
    if (primaryIndices.isEmpty()) {
        return;
    }
    secondaryIndices.clear();
    QFile dataFile(dataFileName);
    if (dataFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&dataFile);
        in.setCodec("UTF-8");
        while (!in.atEnd()) {
            Manga manga;
            manga.loadFromStream(in);
            if (!secondaryIndices.contains(manga.title)) {
                secondaryIndices[manga.title] = QList<int>();
            }
            secondaryIndices[manga.title].append(manga.id);
        }
        dataFile.close();
    }
}


void MangaManager::updateManga(int index, const Manga &manga) {
    // Esse método é chamado quando um mangá é editado
    // O método carrega todos os mangás do arquivo de dados
    // O mangá editado é substituído pelo mangá original na lista de mangás
    if (index < 0 || index >= primaryIndices.size()) {
        qDebug() << "Invalid index";
        return;
    }

    QVector<Manga> allMangas;
    QFile dataFile(dataFileName);
    if (dataFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&dataFile);
        in.setCodec("UTF-8");
        while (!in.atEnd()) {
            Manga m;
            m.loadFromStream(in);
            allMangas.append(m);
        }
        dataFile.close();
    }

    allMangas[index] = manga;
    saveAllMangas(allMangas);
}


void MangaManager::removeManga(int index) {
    // Esse método é chamado quando um mangá é removido
    // O método carrega todos os mangás do arquivo de dados
    // O mangá é removido da lista de mangás e os índices são atualizados

    if (index < 0 || index >= primaryIndices.size()) {
        qDebug() << "Invalid index";
        return;
    }

    QVector<Manga> allMangas;
    QFile dataFile(dataFileName);
    if (dataFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&dataFile);
        in.setCodec("UTF-8");
        while (!in.atEnd()) {
            Manga m;
            m.loadFromStream(in);
            allMangas.append(m);
        }
        dataFile.close();
    }

    // Remove manga e seus índices
    Manga mangaToRemove = allMangas[index];
    allMangas.removeAt(index);
    primaryIndices.removeAt(index);
    secondaryIndices.remove(mangaToRemove.title);

    // Salva novamente todos os mangás e atualiza os índices
    saveAllMangas(allMangas);
    saveIndices();
}

void MangaManager::saveAllMangas(const QVector<Manga> &allMangas) {
    // Esse método salva todos os mangás no arquivo de dados
    // O método é chamado após adicionar, editar ou remover um mangá

    QFile dataFile(dataFileName);
    if (dataFile.open(QIODevice::WriteOnly)) {
        QTextStream out(&dataFile);
        out.setCodec("UTF-8");
        primaryIndices.clear();
        qDebug() << "primaryIndices in saveAllMangas: " << primaryIndices;
        for (const Manga &manga : allMangas) {
            // Salvar a posição atual do arquivo antes de salvar o mangá
            qint64 position = dataFile.pos();
            primaryIndices.append(position);
            qDebug() << "Saving manga at position:" << position; // Debug statement
            manga.saveToStream(out);
            // Avançar o ponteiro de arquivo para a próxima posição após salvar o mangá
            out.flush();
        }
        dataFile.close();
        updateSecondaryIndex();
        saveIndices();
    } else {
        qDebug() << "Failed to open data file for writing";
    }
}


void MangaManager::loadIndices() {
    // Esse método carrega os índices primários e secundários de arquivos
    // Os índices primários são posições no arquivo de dados
    // Os índices secundários são títulos de mangás mapeados para listas de IDs de mangás

    QFile indexFile(indexFileName);
    if (indexFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&indexFile);
        in.setCodec("UTF-8");
        QString line;
        while (in.readLineInto(&line)) {
            qint64 pos = line.toLongLong();
            primaryIndices.append(pos);
            qDebug() << "Loaded index position:" << pos; // Debug statement
        }
        indexFile.close();
    }

    QFile secondaryIndexFile(secondaryIndexFileName);
    if (secondaryIndexFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&secondaryIndexFile);
        in.setCodec("UTF-8");
        QString line;
        while (in.readLineInto(&line)) {
            QStringList parts = line.split(","); // Separar a linha em partes
            if (parts.size() > 1) {
                QString title = parts[0]; // O título é a primeira parte
                QList<int> ids;
                for (int i = 1; i < parts.size(); ++i) {
                    ids.append(parts[i].toInt());
                }
                secondaryIndices.insert(title, ids);
                qDebug() << "Loaded sec index position:" << title << "," << ids;
            }
        }
        secondaryIndexFile.close();
    }
}

void MangaManager::saveIndices() {
    // Esse método é chamado após adicionar ou remover um mangá
    // Ele salva os índices primários e secundários em arquivos

    // Salvar índices primários
    QFile indexFile(indexFileName);
    if (indexFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&indexFile);
        out.setCodec("UTF-8");
        for (qint64 position : primaryIndices) {
            out << position << "\n";
        }
        indexFile.close();
    }

   // Salvar índices secundários
    QFile secondaryIndexFile(secondaryIndexFileName);
    if (secondaryIndexFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&secondaryIndexFile);
        out.setCodec("UTF-8");
        qDebug() << "Saving secondary indices to file:" << secondaryIndexFileName;
        for (const QString &title : secondaryIndices.keys()) {
            QList<int> ids = secondaryIndices.value(title);
            QStringList idsStringList;
            for (int id : ids) {
                idsStringList.append(QString::number(id));                  // Converter int para string
            }
            QString idsString = idsStringList.join(",");                    // Juntar a lista de IDs em uma string
            out << title << "," << idsString << "\n";                       // Salvar a linha no arquivo
            qDebug() << "Saved secondary index:" << title << idsString;
        }
        secondaryIndexFile.close();
    } else {
        qDebug() << "Failed to open secondary index file for writing";
    }
}

int MangaManager::getPrimaryIndicesSize() const {
    return primaryIndices.size();
}

QMap<QString, QList<int>> MangaManager::getSecondaryIndices() const {
    return secondaryIndices;
}
