#ifndef CONFIG1_H
#define CONFIG1_H

#include <QDialog>
#include "xml.h"
namespace Ui {
class Config1;
}

class Config1 : public QDialog
{
    Q_OBJECT

public:
    void saveData();
    void dispData();
    explicit Config1(QWidget *parent = 0);
    ~Config1();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_checkBox_clicked(bool checked);

private:
    Ui::Config1 *ui;
};

#endif // CONFIG1_H
