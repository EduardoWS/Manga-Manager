#include "searchmangadialog.h"

SearchMangaDialog::SearchMangaDialog(QWidget *parent)
    : QDialog(parent) {
    setWindowTitle("Buscar Mangá");

    titleEdit = new QLineEdit(this);

    searchButton = new QPushButton("Buscar", this);

    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow("Título:", titleEdit);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(searchButton);

    setLayout(mainLayout);

    connect(searchButton, &QPushButton::clicked, this, &SearchMangaDialog::onSaveButtonClicked);
}

void SearchMangaDialog::onSaveButtonClicked() {
    // Implementar funcionalidade de salvar mangá
    accept();
}
