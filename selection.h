#ifndef FENTABLE_H
#define FENTABLE_H

#include <QWidget>
#include <QTableWidget>

namespace Ui {
class Selection;
}

class FenTable : public QWidget
{
    Q_OBJECT

public:
    explicit FenTable(int num,bool oriented, QWidget *parent = 0);
    ~FenTable();

public slots:
    void on_Go_clicked();

private:
    Ui::Selection *ui;
    int nodes;
    QTableWidget *tab;
};

#endif
