#ifndef CONFIG2_H
#define CONFIG2_H

#include <QDialog>
#include "xml.h"
namespace Ui {
class Config2;
}

class Config2 : public QDialog
{
    Q_OBJECT

public:
    void saveData();
    void dispData();
    explicit Config2(QWidget *parent = 0);
    ~Config2();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_checkBox_clicked(bool checked);

private:
    Ui::Config2 *ui;
};

#endif // CONFIG2_H
