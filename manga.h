#ifndef MANGA_H
#define MANGA_H

#include <QString>
#include <QTextStream>
#include <QFile>

struct Manga {
    int id;
    char isbn[20];
    char title[100];
    char authors[100];
    int startYear;
    int endYear;
    char genre[50];
    char magazine[50];
    char publisher[50];
    int editionYear;
    int volumesCount;
    int acquiredVolumesCount;
    int acquiredVolumes[100];  // Tamanho fixo para simplificação

    void saveToStream(QTextStream &out) const;
    void loadFromStream(QTextStream &in);
};

#endif // MANGA_H
