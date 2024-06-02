#ifndef ADDMANGADIALOG_H
#define ADDMANGADIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QFormLayout>
#include <QVBoxLayout>

class AddMangaDialog : public QDialog {
    Q_OBJECT

public:
    AddMangaDialog(QWidget *parent = nullptr);

    QLineEdit* getIsbnEdit() const { return isbnEdit; }
    QLineEdit* getTitleEdit() const { return titleEdit; }
    QLineEdit* getAuthorEdit() const { return authorEdit; }
    QLineEdit* getStartYearEdit() const { return startYearEdit; }
    QLineEdit* getEndYearEdit() const { return endYearEdit; }
    QLineEdit* getGenreEdit() const { return genreEdit; }
    QLineEdit* getMagazineEdit() const { return magazineEdit; }
    QLineEdit* getPublisherEdit() const { return publisherEdit; }
    QLineEdit* getEditionYearEdit() const { return editionYearEdit; }
    QLineEdit* getVolumesCountEdit() const { return volumesCountEdit; }
    QLineEdit* getAcquiredVolumesCountEdit() const { return acquiredVolumesCountEdit; }
    QLineEdit* getAcquiredVolumesListEdit() const { return acquiredVolumesListEdit; }


private slots:
    void onSaveButtonClicked();

private:
    QLineEdit *isbnEdit;
    QLineEdit *titleEdit;
    QLineEdit *authorEdit;
    QLineEdit *startYearEdit;
    QLineEdit *endYearEdit;
    QLineEdit *genreEdit;
    QLineEdit *magazineEdit;
    QLineEdit *publisherEdit;
    QLineEdit *editionYearEdit;
    QLineEdit *volumesCountEdit;
    QLineEdit *acquiredVolumesCountEdit;
    QLineEdit *acquiredVolumesListEdit;
    QPushButton *saveButton;
};

#endif // ADDMANGADIALOG_H
