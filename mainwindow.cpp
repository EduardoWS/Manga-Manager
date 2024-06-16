#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "manga.h"
#include <QDebug>
#include <QMessageBox>
#include <QDir>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , mangaManager(new MangaManager(QDir::currentPath()))
    , model(new QStandardItemModel(this))
{
    ui->setupUi(this);

    setWindowTitle("Manga Manager");

    // Impedir o redimensionamento da janela
    this->setFixedSize(this->size());

    // Configurar o modelo do QTableView
    model->setColumnCount(5);
    model->setHeaderData(0, Qt::Horizontal, "ISBN");
    model->setHeaderData(1, Qt::Horizontal, "Título");
    model->setHeaderData(2, Qt::Horizontal, "Autor(es)");
    model->setHeaderData(3, Qt::Horizontal, "Revista");
    model->setHeaderData(4, Qt::Horizontal, "Ano da Edição");
    qDebug() << model->columnCount();

    ui->mangaTableView->setModel(model);
    ui->mangaTableView->horizontalHeader()->setStretchLastSection(true);
    ui->mangaTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Configurar a QTableView para selecionar a linha inteira
    ui->mangaTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->mangaTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);  // Desabilitar edição direta

    connect(ui->add_manga_button, &QPushButton::clicked, this, &MainWindow::onAddMangaButtonClicked);
    connect(ui->edit_manga_button, &QPushButton::clicked, this, &MainWindow::onEditMangaButtonClicked);
    connect(ui->remove_manga_button, &QPushButton::clicked, this, &MainWindow::onRemoveMangaButtonClicked);
    connect(ui->mangaTableView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &MainWindow::onMangaTableViewSelectionChanged);
    connect(ui->search_button, &QPushButton::clicked, this, &MainWindow::onSearchButtonClicked);

    updateMangaView();
    updateMangaCount();


}

MainWindow::~MainWindow() {
    delete ui;
    delete mangaManager;
}

void MainWindow::onAddMangaButtonClicked() {
    addMangaDialog = new AddMangaDialog(this);
    if (addMangaDialog->exec() == QDialog::Accepted) {
        Manga manga;
        strcpy(manga.isbn, addMangaDialog->getIsbnEdit()->text().toStdString().c_str());
        strcpy(manga.title, addMangaDialog->getTitleEdit()->text().toStdString().c_str());
        strcpy(manga.authors, addMangaDialog->getAuthorEdit()->text().toStdString().c_str());
        manga.startYear = addMangaDialog->getStartYearEdit()->text().toInt();
        manga.endYear = addMangaDialog->getEndYearEdit()->text().toInt();
        strcpy(manga.genre, addMangaDialog->getGenreEdit()->text().toStdString().c_str());
        strcpy(manga.magazine, addMangaDialog->getMagazineEdit()->text().toStdString().c_str());
        strcpy(manga.publisher, addMangaDialog->getPublisherEdit()->text().toStdString().c_str());
        manga.editionYear = addMangaDialog->getEditionYearEdit()->text().toInt();
        manga.volumesCount = addMangaDialog->getVolumesCountEdit()->text().toInt();
        manga.acquiredVolumesCount = addMangaDialog->getAcquiredVolumesCountEdit()->text().toInt();

        // verificar se a quantidade de volumes adquiridos é menor ou igual a quantidade de volumes
        if (manga.acquiredVolumesCount > manga.volumesCount) {
            QMessageBox::information(this, "Adicionar Mangá", "A quantidade de volumes adquiridos não pode ser maior que a quantidade de volumes!");
            return;
        }

        // verificar se a quantidade de volumes adquiridos é menor ou igual a 100
        if (manga.acquiredVolumesCount > 100) {
            QMessageBox::information(this, "Adicionar Mangá", "A quantidade de volumes adquiridos não pode ser maior que 100!");
            return;
        }

        
        qDebug() << "Teste A";
        QStringList volumesList = addMangaDialog->getAcquiredVolumesListEdit()->text().split(",");
        qDebug() << "Teste B";
        for (int i = 0; i < manga.acquiredVolumesCount && i < 100; ++i) {
            qDebug() << "Teste C";
            try {
                manga.acquiredVolumes[i] = volumesList[i].toInt();
            } catch (std::exception &e) {
                QMessageBox::information(this, "Adicionar Mangá", "A lista de volumes adquiridos contém valores inválidos!");
                return;
            } catch (...) {
                QMessageBox::information(this, "Adicionar Mangá", "Erro desconhecido ao adicionar mangá!");
                return;
            }
            //manga.acquiredVolumes[i] = volumesList[i].toInt();
        }
        // verificar se a lista de volumes é igual a quantidade de volumes adquiridos
        if (volumesList.size() != manga.acquiredVolumesCount) {
            QMessageBox::information(this, "Adicionar Mangá", "A quantidade de volumes adquiridos não corresponde a lista de volumes adquiridos!");
            return;
        }

        mangaManager->addManga(manga);
        updateMangaView();
        updateMangaCount();
    }
}

void MainWindow::onEditMangaButtonClicked() {
    QItemSelectionModel *selectionModel = ui->mangaTableView->selectionModel();
    if (selectionModel->hasSelection()) {
        int selectedRow = selectionModel->selectedRows().first().row();
        Manga manga = mangaManager->getMangaByIndex(selectedRow);

        addMangaDialog = new AddMangaDialog(this);
        addMangaDialog->getIsbnEdit()->setText(manga.isbn);
        addMangaDialog->getTitleEdit()->setText(manga.title);
        addMangaDialog->getAuthorEdit()->setText(manga.authors);
        addMangaDialog->getStartYearEdit()->setText(QString::number(manga.startYear));
        addMangaDialog->getEndYearEdit()->setText(QString::number(manga.endYear));
        addMangaDialog->getGenreEdit()->setText(manga.genre);
        addMangaDialog->getMagazineEdit()->setText(manga.magazine);
        addMangaDialog->getPublisherEdit()->setText(manga.publisher);
        addMangaDialog->getEditionYearEdit()->setText(QString::number(manga.editionYear));
        addMangaDialog->getVolumesCountEdit()->setText(QString::number(manga.volumesCount));
        addMangaDialog->getAcquiredVolumesCountEdit()->setText(QString::number(manga.acquiredVolumesCount));

        QStringList volumesList;
        for (int i = 0; i < manga.acquiredVolumesCount; ++i) {
            volumesList.append(QString::number(manga.acquiredVolumes[i]));
        }
        addMangaDialog->getAcquiredVolumesListEdit()->setText(volumesList.join(","));

        if (addMangaDialog->exec() == QDialog::Accepted) {
            strcpy(manga.isbn, addMangaDialog->getIsbnEdit()->text().toStdString().c_str());
            strcpy(manga.title, addMangaDialog->getTitleEdit()->text().toStdString().c_str());
            strcpy(manga.authors, addMangaDialog->getAuthorEdit()->text().toStdString().c_str());
            manga.startYear = addMangaDialog->getStartYearEdit()->text().toInt();
            manga.endYear = addMangaDialog->getEndYearEdit()->text().toInt();
            strcpy(manga.genre, addMangaDialog->getGenreEdit()->text().toStdString().c_str());
            strcpy(manga.magazine, addMangaDialog->getMagazineEdit()->text().toStdString().c_str());
            strcpy(manga.publisher, addMangaDialog->getPublisherEdit()->text().toStdString().c_str());
            manga.editionYear = addMangaDialog->getEditionYearEdit()->text().toInt();
            manga.volumesCount = addMangaDialog->getVolumesCountEdit()->text().toInt();
            manga.acquiredVolumesCount = addMangaDialog->getAcquiredVolumesCountEdit()->text().toInt();

            volumesList = addMangaDialog->getAcquiredVolumesListEdit()->text().split(",");
            for (int i = 0; i < manga.acquiredVolumesCount && i < 100; ++i) {
                manga.acquiredVolumes[i] = volumesList[i].toInt();
            }

            mangaManager->updateManga(selectedRow, manga);
            updateMangaView();
            updateMangaCount();
        }
    }
}

void MainWindow::onRemoveMangaButtonClicked() {
    QItemSelectionModel *selectionModel = ui->mangaTableView->selectionModel();
    if (selectionModel->hasSelection()) {
        int selectedRow = selectionModel->selectedRows().first().row();
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Remover Mangá", "Tem certeza que deseja remover este mangá?", QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            mangaManager->removeManga(selectedRow);
            updateMangaView();
            updateMangaCount();
        }
    }
}

void MainWindow::onMangaTableViewSelectionChanged() {
    QItemSelectionModel *selectionModel = ui->mangaTableView->selectionModel();
    bool hasSelection = selectionModel->hasSelection();
    ui->edit_manga_button->setEnabled(hasSelection);
    ui->remove_manga_button->setEnabled(hasSelection);
}

void MainWindow::updateMangaView() {
    model->removeRows(0, model->rowCount());

    for (int i = 0; i < mangaManager->getPrimaryIndicesSize(); ++i) {
        Manga manga = mangaManager->getMangaByIndex(i);

        QList<QStandardItem *> items;
        items.append(new QStandardItem(manga.isbn));
        items.append(new QStandardItem(manga.title));
        items.append(new QStandardItem(manga.authors));
        items.append(new QStandardItem(manga.magazine));
        items.append(new QStandardItem(QString::number(manga.editionYear)));

        model->appendRow(items);
    }
}

void MainWindow::updateMangaCount() {
    int count = mangaManager->getPrimaryIndicesSize();
    ui->label->setText(QString("Total de mangás catalogados: %1").arg(count));
}


void MainWindow::onSearchButtonClicked() {
    QString title = ui->entry_text->text();
    if (title == ""){
        updateMangaView();
        return;
    }

    model->removeRows(0, model->rowCount()); // limpar linhas

    QList<int> ids = mangaManager->getSecondaryIndices().value(title, QList<int>());
    if (ids.isEmpty()) {
        //updateMangaView();
        QMessageBox::information(this, "Buscar Mangá", "Mangá não encontrado!");
        return;
    }

    for (int i = 0; i < mangaManager->getPrimaryIndicesSize(); ++i) {
        Manga manga = mangaManager->getMangaByIndex(i);
        
        if (ids.contains(manga.id)) {
            QList<QStandardItem *> items;
            items.append(new QStandardItem(manga.isbn));
            items.append(new QStandardItem(manga.title));
            items.append(new QStandardItem(manga.authors));
            items.append(new QStandardItem(manga.magazine));
            items.append(new QStandardItem(QString::number(manga.editionYear)));

            model->appendRow(items);
        }
    }
}

