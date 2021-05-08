#ifndef FIRST_TRY_H
#define FIRST_TRY_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class first_try; }
QT_END_NAMESPACE

class first_try : public QMainWindow
{
    Q_OBJECT

public:
    first_try(QWidget *parent = nullptr);
    ~first_try();

private slots:
    void decrypt();
    void save_image();
    void open_image();

private:
    Ui::first_try *ui;
    QImage da_file;
    std::string str;
};
#endif // FIRST_TRY_H
