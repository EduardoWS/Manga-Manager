#ifndef MANGAMANAGER_H
#define MANGAMANAGER_H

#include "manga.h"
#include <QString>
#include <QVector>

class MangaManager {
public:
    MangaManager(const QString &basePath);

    void addManga(const Manga &manga);
    Manga getMangaByIndex(int index);
    void updateManga(int index, const Manga &manga);
    void removeManga(int index);
    int getPrimaryIndicesSize() const;
    QMap<QString, QList<int>> getSecondaryIndices() const;

private:
    QString dataFileName;
    QString indexFileName;
    QString secondaryIndexFileName;
    QVector<qint64> primaryIndices;
    QMap<QString, QList<int>> secondaryIndices; // Índice secundário para títulos
    QString nextIdFileName;
    int nextId; // ID único para mangás

    void loadIndices();
    void saveIndices();
    void loadNextId();
    void saveNextId();
    void saveAllMangas(const QVector<Manga> &allMangas);
    void updateSecondaryIndex();
};

#endif // MANGAMANAGER_H
