#ifndef SEARCHMANGADIALOG_H
#define SEARCHMANGADIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QFormLayout>
#include <QVBoxLayout>

class SearchMangaDialog : public QDialog {
    Q_OBJECT

public:
    SearchMangaDialog(QWidget *parent = nullptr);
    QLineEdit* getTitleEdit() const { return titleEdit; }
private slots:
    void onSaveButtonClicked();
private:
     QLineEdit *titleEdit;
#endif // SEARCHMANGADIALOG_H

