#include "addmangadialog.h"

AddMangaDialog::AddMangaDialog(QWidget *parent)
    : QDialog(parent) {
    setWindowTitle("Adicionar Mangá");

    isbnEdit = new QLineEdit(this);
    titleEdit = new QLineEdit(this);
    authorEdit = new QLineEdit(this);
    startYearEdit = new QLineEdit(this);
    endYearEdit = new QLineEdit(this);
    genreEdit = new QLineEdit(this);
    magazineEdit = new QLineEdit(this);
    publisherEdit = new QLineEdit(this);
    editionYearEdit = new QLineEdit(this);
    volumesCountEdit = new QLineEdit(this);
    acquiredVolumesCountEdit = new QLineEdit(this);
    acquiredVolumesListEdit = new QLineEdit(this);
    saveButton = new QPushButton("Salvar", this);

    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow("ISBN:", isbnEdit);
    formLayout->addRow("Título:", titleEdit);
    formLayout->addRow("Autor(es):", authorEdit);
    formLayout->addRow("Ano de Início:", startYearEdit);
    formLayout->addRow("Ano de Fim:", endYearEdit);
    formLayout->addRow("Gênero:", genreEdit);
    formLayout->addRow("Revista:", magazineEdit);
    formLayout->addRow("Editora:", publisherEdit);
    formLayout->addRow("Ano da Edição:", editionYearEdit);
    formLayout->addRow("Quantidade de Volumes:", volumesCountEdit);
    formLayout->addRow("Volumes Adquiridos:", acquiredVolumesCountEdit);
    formLayout->addRow("Lista de Volumes Adquiridos:", acquiredVolumesListEdit);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(saveButton);

    setLayout(mainLayout);

    connect(saveButton, &QPushButton::clicked, this, &AddMangaDialog::onSaveButtonClicked);
}

void AddMangaDialog::onSaveButtonClicked() {
    // Implementar funcionalidade de salvar mangá
    accept();
}
