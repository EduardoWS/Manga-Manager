#include "manga.h"
#include <QTextCodec>
#include <QDebug>

void Manga::saveToStream(QTextStream &out) const {
    out.setCodec("UTF-8");
    out << id << '\n'
        << isbn << '\n'
        << title << '\n'
        << authors << '\n'
        << startYear << '\n'
        << endYear << '\n'
        << genre << '\n'
        << magazine << '\n'
        << publisher << '\n'
        << editionYear << '\n'
        << volumesCount << '\n'
        << acquiredVolumesCount << '\n';
    for (int i = 0; i < acquiredVolumesCount; ++i) {
        out << acquiredVolumes[i] << (i == acquiredVolumesCount - 1 ? '\n' : ' ');
    }
}

void Manga::loadFromStream(QTextStream &in) {
    in.setCodec("UTF-8");
    QString temp;

    // Ler a linha e copiar para o campo id
    in >> id;
    in.readLine();  // Mover o ponteiro para a próxima linha

    // Ler a linha e copiar para o campo isbn
    in.readLineInto(&temp);
    strncpy(isbn, temp.toUtf8().constData(), sizeof(isbn) - 1);
    isbn[sizeof(isbn) - 1] = '\0';  // Garantir que a string termine com '\0'

    // Ler a linha e copiar para o campo title
    in.readLineInto(&temp);
    strncpy(title, temp.toUtf8().constData(), sizeof(title) - 1);
    title[sizeof(title) - 1] = '\0';  // Garantir que a string termine com '\0'

    // Ler a linha e copiar para o campo authors
    in.readLineInto(&temp);
    strncpy(authors, temp.toUtf8().constData(), sizeof(authors) - 1);
    authors[sizeof(authors) - 1] = '\0';  // Garantir que a string termine com '\0'

    // Ler os campos numéricos
    in >> startYear;
    in >> endYear;
    in.readLine();  // Mover o ponteiro para a próxima linha

    // Ler a linha e copiar para o campo genre
    in.readLineInto(&temp);
    strncpy(genre, temp.toUtf8().constData(), sizeof(genre) - 1);
    genre[sizeof(genre) - 1] = '\0';  // Garantir que a string termine com '\0'

    // Ler a linha e copiar para o campo magazine
    in.readLineInto(&temp);
    strncpy(magazine, temp.toUtf8().constData(), sizeof(magazine) - 1);
    magazine[sizeof(magazine) - 1] = '\0';  // Garantir que a string termine com '\0'

    // Ler a linha e copiar para o campo publisher
    in.readLineInto(&temp);
    strncpy(publisher, temp.toUtf8().constData(), sizeof(publisher) - 1);
    publisher[sizeof(publisher) - 1] = '\0';  // Garantir que a string termine com '\0'

    // Ler os campos numéricos restantes
    in >> editionYear;
    in >> volumesCount;
    in >> acquiredVolumesCount;
    in.readLine();  // Mover o ponteiro para a próxima linha

    // Ler os volumes adquiridos
    for (int i = 0; i < acquiredVolumesCount; ++i) {
        in >> acquiredVolumes[i];
    }

    // Ler a linha para mover o ponteiro para a próxima linha
    in.readLine();
}