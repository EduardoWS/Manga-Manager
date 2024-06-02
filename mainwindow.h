#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include "addmangadialog.h"
#include "mangamanager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onAddMangaButtonClicked();
    void onEditMangaButtonClicked();
    void onRemoveMangaButtonClicked();
    void onMangaTableViewSelectionChanged();

private:
    Ui::MainWindow *ui;
    AddMangaDialog *addMangaDialog;
    MangaManager *mangaManager;
    QStandardItemModel *model;

    void updateMangaView();
    void updateMangaCount();
};
#endif // MAINWINDOW_H
