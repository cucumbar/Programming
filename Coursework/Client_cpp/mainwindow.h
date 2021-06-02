#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork/QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QFileDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include <QByteArray>
#include <string>
#include <QImage>
#include <QIcon>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public slots:
    void get_gen_msg();
    void get_vars();
    void get_gen_image(); //!

    void onfinish_post_text(QNetworkReply*);
    void onfinish_get_text(QNetworkReply*);
    void onfinish_get_image(QNetworkReply*); //!

    void count_symb();
    void count_word();
    void count_sent();

    void clear_text_1();
    void clear_text_2();

    void save_img();

public:
    MainWindow(QWidget *parent = nullptr);
    QJsonDocument json_f_post;
    QString user_text{ "" }, previous_ut{ "" };
    QByteArray get_res;
    QImage user_pic;
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
