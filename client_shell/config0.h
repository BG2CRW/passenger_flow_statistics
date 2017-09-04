#ifndef CONFIG0_H
#define CONFIG0_H

#include <QDialog>
#include "xml.h"
namespace Ui {
class Config0;
}

class Config0 : public QDialog
{
    Q_OBJECT

public:
    void saveData();
    void dispData();
    explicit Config0(QWidget *parent = 0);
    ~Config0();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();


    void on_checkBox_clicked(bool checked);

private:
    Ui::Config0 *ui;
};

#endif // CONFIG0_H
