#include "mangamanager.h"
#include <QFile>
#include <QTextStream>
#include <QIODevice>
#include <QDebug>

MangaManager::MangaManager(const QString &basePath) {
    dataFileName = basePath + "/manga_data.txt";
    indexFileName = basePath + "/manga_index.txt";
    secondaryIndexFileName = basePath + "/manga_secondary_index.txt";
    loadIndices();
    qDebug() << "MangaManager initialized with data file:" << dataFileName << "and index file:" << indexFileName;
}
void MangaManager::addManga(const Manga &manga) {
    QFile dataFile(dataFileName);
    if (dataFile.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&dataFile);
        out.setCodec("UTF-8");
        qint64 position = out.pos();
        manga.saveToStream(out);
        primaryIndices.append(position);
        qDebug() << "Added manga at position:" << position; // Debug statement
        dataFile.close();
        saveIndices();
        qDebug() << "Manga added and data saved";
    } else {
        qDebug() << "Failed to open data file for appending";
    }
}

Manga MangaManger::getMangaByTitle(const QString &mangaTitle){
    QFile secondaryIndexFile(secondaryIndexFileName);
    Manga manga;
    if (secondaryIndexFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&secondaryIndexFile);
        in.setCodec("UTF-8");
        /* se o arquivo contém uma linha com <título - índice>:
         * umIndice = leIndice();
         * manga = getMangaByIndex();
         * */
    }
    return manga;

}

Manga MangaManager::getMangaByIndex(int index) {
    Manga manga;
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

void MangaManager::updateManga(int index, const Manga &manga) {
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

    allMangas.removeAt(index);
    saveAllMangas(allMangas);
}

void MangaManager::saveAllMangas(const QVector<Manga> &allMangas) {
    QFile dataFile(dataFileName);
    if (dataFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&dataFile);
        out.setCodec("UTF-8");
        primaryIndices.clear();
        for (const Manga &manga : allMangas) {
            // Salvar a posição atual do arquivo antes de salvar o mangá
            qint64 position = out.pos();
            primaryIndices.append(position);
            qDebug() << "Saving manga at position:" << position; // Debug statement
            manga.saveToStream(out);
            // Avançar o ponteiro de arquivo para a próxima posição após salvar o mangá
            out.flush();
        }
        dataFile.close();
        saveIndices();
    } else {
        qDebug() << "Failed to open data file for writing";
    }
}

void MangaManager::loadIndices() {
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
        qDebug() << "Indices loaded";
    } else {
        qDebug() << "Failed to open index file for reading";
    }
}

void MangaManager::saveIndices() {
    QFile indexFile(indexFileName);
    if (indexFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&indexFile);
        out.setCodec("UTF-8");
        for (qint64 position : primaryIndices) {
            qDebug() << "Saving index position:" << position; // Debug statement
            out << position << '\n';
        }
        indexFile.close();
        qDebug() << "Indices saved";
    } else {
        qDebug() << "Failed to open index file for writing";
    }
}

int MangaManager::getPrimaryIndicesSize() const {
    return primaryIndices.size();
}
