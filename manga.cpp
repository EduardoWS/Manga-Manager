#include "manga.h"
#include <QTextCodec>
#include <QDebug>

void Manga::saveToStream(QTextStream &out) const {
    out.setCodec("UTF-8");
    out << id << "," << isbn << "," << title << "," << authors << "," << startYear << ","
        << endYear << "," << genre << "," << magazine << "," << publisher << ","
        << editionYear << "," << volumesCount << "," << acquiredVolumesCount << ",'";
    for (int i = 0; i < acquiredVolumesCount; ++i) {
        if (i==acquiredVolumesCount-1) out << acquiredVolumes[i];
        else out << acquiredVolumes[i] << ",";
    }
    out << "'" << "\n";
}

void Manga::loadFromStream(QTextStream &in) {
    QString line = in.readLine();
    QStringList fields = line.split(",");
    qDebug() << "fields: " << fields;
    id = fields[0].toInt();
    strcpy(isbn, fields[1].toStdString().c_str());
    strcpy(title, fields[2].toStdString().c_str());
    strcpy(authors, fields[3].toStdString().c_str());
    startYear = fields[4].toInt();
    endYear = fields[5].toInt();
    strcpy(genre, fields[6].toStdString().c_str());
    strcpy(magazine, fields[7].toStdString().c_str());
    strcpy(publisher, fields[8].toStdString().c_str());
    editionYear = fields[9].toInt();
    volumesCount = fields[10].toInt();
    acquiredVolumesCount = fields[11].toInt();
    // tirar espaços em branco do ultimo campo
    fields[12] = fields[12].trimmed();
    qDebug() << "acquiredVolumesCount: " << acquiredVolumesCount;
    qDebug() << "fields[12]: " << fields[12];
    qDebug() << "fields[12]: " << fields[15];
    for (int i = 0; i < acquiredVolumesCount; ++i) {
        if (i == 0){ // tirar aspas simples do primeiro campo
            fields[12] = fields[12].remove(0, 1);
        }
        if (i == acquiredVolumesCount-1){ // tirar aspas simples do ultimo campo
            fields[12+i] = fields[12+i].remove(fields[12+i].size()-1, 1);
        }
        acquiredVolumes[i] = fields[12 + i].toInt();
        qDebug() << "acquiredVolumes[" << i << "]: " << acquiredVolumes[i];
    }
}
