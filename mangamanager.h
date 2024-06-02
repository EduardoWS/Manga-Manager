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

private:
    QString dataFileName;
    QString indexFileName;
    QVector<int> primaryIndices;  // Vetor para armazenar os índices primários

    void loadIndices();
    void saveIndices();
    void saveAllMangas(const QVector<Manga> &allMangas);
};

#endif // MANGAMANAGER_H
