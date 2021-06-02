#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    QIcon iconka;
//    iconka.addFile("icon.ico");
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(get_gen_msg()));
    connect(ui->textEdit, SIGNAL(textChanged()), this, SLOT(count_symb()));
    connect(ui->textEdit, SIGNAL(textChanged()), this, SLOT(count_word()));
    connect(ui->textEdit, SIGNAL(textChanged()), this, SLOT(count_sent()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(get_vars()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(clear_text_1()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(get_gen_image()));
    connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(clear_text_2()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(save_img()));
    this->setWindowTitle("Text King v1.0.0a");
//    this->setWindowIcon(iconka);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onfinish_post_text(QNetworkReply *reply){
    get_res = reply->readAll();
    ui->label_4->setText("");

    json_f_post = QJsonDocument::fromJson(get_res);

    QString user_text_fromrep_temp = json_f_post.object().value("result_list").toString();

    qDebug() << user_text_fromrep_temp;
    qDebug() << user_text;

    if (user_text_fromrep_temp == ""){
        ui->label_4->setText("Повторите попытку");
    }
    //exit(-1234);

    previous_ut = user_text;
    user_text_fromrep_temp = user_text_fromrep_temp.left(user_text_fromrep_temp.size() - 1);
    user_text_fromrep_temp = user_text_fromrep_temp.right(user_text_fromrep_temp.size() - 1);

    user_text += user_text_fromrep_temp;
    ui->textEdit->setPlainText(user_text);

    reply->deleteLater();
}

void MainWindow::get_gen_msg(){
    user_text = ui->textEdit->toPlainText();
    std::string user_text_str = user_text.toLocal8Bit().constData();

    QNetworkAccessManager* manager_poster = new QNetworkAccessManager(this);
    QUrl send_gen("http://localhost:5000");

    connect(manager_poster, &QNetworkAccessManager::finished, this, &MainWindow::onfinish_post_text);

    QNetworkRequest post_request(send_gen);
    post_request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json;charset=utf-8");

    qDebug() << user_text;

    auto temp_len{ std::to_string(ui->spinBox->value()) };
    QString QTemp_len = QString(temp_len.c_str());

    auto user_text_req = "{\"user_text\":\"" + user_text + "\", \"len\":" + QTemp_len + "}"; // "{\"user_text\":\"" + user_text + "\"}"
    QByteArray temp{ user_text_req.toUtf8() };
    manager_poster->post(post_request, temp);

}

void MainWindow::count_symb(){
    QString s = ui->textEdit->toPlainText();
    s = s.toLocal8Bit().constData();
    auto t = std::to_string(s.size());

    s = t.c_str();
    //qDebug() << s;
    ui->label_Symb->setText(s);
}

void MainWindow::count_word(){
    QString s = ui->textEdit->toPlainText();
    auto r{ s.split(" ") };
    int t{ 0 };

    for (auto i : r){
        if (i != ""){
            t++;
        }
    }

    auto st = std::to_string(t);
    s = st.c_str();
    //qDebug() << s;
    ui->label_Word->setText(s);
}

void MainWindow::count_sent(){
    QString s = ui->textEdit->toPlainText();
    auto r1{ s.split(".") };
    int t{ 0 };

    for (auto i : r1){
        for (auto j : i.split("!")){
            for (auto k : j.split("?")){
                if (k != ""){
                    t++;
                }
            }
        }
    }

//    auto r3{ s.split("?") };
//    int t{ 0 };

//    for (auto i : r1){
//        if (i != ""){
//            t++;
//        }
//    }

//    for (auto i : r2){
//        if (i != ""){
//            t++;
//        }
//    }

//    for (auto i : r3){
//        if (i != ""){
//            t++;
//        }
//    }

    auto st = std::to_string(t);
    s = st.c_str();
    //qDebug() << s;
    ui->label_Sent->setText(s);
}

void MainWindow::onfinish_get_text(QNetworkReply* reply){
    get_res = reply->readAll();
    ui->label_4->setText("");
    //user_text_fromrep = QString(get_res);

    QString user_text_fromrep_temp = QString(get_res);

    qDebug() << user_text_fromrep_temp;
    qDebug() << user_text;

    if (user_text_fromrep_temp == "" || user_text_fromrep_temp == "0"){
        ui->label_4->setText("Варианты кончились");
        return;
    }
    //exit(-1234);

    user_text = previous_ut + user_text_fromrep_temp;
    ui->textEdit->setPlainText(user_text);

    reply->deleteLater();
}

void MainWindow::get_vars(){
    QNetworkAccessManager* manager_getter = new QNetworkAccessManager(this);
    QUrl send_gen("http://localhost:5000/vars");

    connect(manager_getter, &QNetworkAccessManager::finished, this, &MainWindow::onfinish_get_text);

    QNetworkRequest get_request(send_gen);
    get_request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json;charset=utf-8");

    manager_getter->get(get_request);
}

void MainWindow::clear_text_1(){
    ui->textEdit->setText("");
}

//----------------------------------------------------images-------------------------------------------------

void MainWindow::clear_text_2(){
    ui->textEdit_2->setText("");
}

void MainWindow::onfinish_get_image(QNetworkReply* reply){
    get_res = reply->readAll();

    if (get_res == ""){
        ui->label_4->setText("Повторите попытку");
        return;
    }

    ui->label_4->setText("");
    user_pic.loadFromData(get_res, "PNG");

    qDebug() << user_pic.size();

    QPixmap pixmap = QPixmap::fromImage(user_pic);
    ui->label_image->setPixmap(pixmap);

    reply->deleteLater();
}

void MainWindow::get_gen_image(){
    QNetworkAccessManager* manager_poster = new QNetworkAccessManager(this);
    QUrl send_gen("http://localhost:5000/get_handwrite");

    connect(manager_poster, &QNetworkAccessManager::finished, this, &MainWindow::onfinish_get_image);

    QNetworkRequest post_request(send_gen);
    post_request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json;charset=utf-8");

    qDebug() << ui->textEdit_2->toPlainText();

    auto temp_fsize{ std::to_string(ui->spinBox_2->value()) };
    QString QTemp_fsize = QString(temp_fsize.c_str());

    auto user_text_req = "{\"to_handwrite\":\"" + ui->textEdit_2->toPlainText() + "\", \"f_size\" : " + QTemp_fsize + "}"; // "{\"user_text\":\"" + user_text + "\"}"
    QByteArray temp{ user_text_req.toUtf8() };
    manager_poster->post(post_request, temp);
    ui->label_4->setText("Ошибка. Попробуйте позже.");
}

void MainWindow::save_img(){
    QString fileName = QFileDialog::getSaveFileName(this, "Save Image", "", "Допустимые форматы (*.png)");
    if (fileName.size()){
        user_pic.save(fileName);
    }

    else{
        ui->label_4->setText("Страница не сохранена");
    }
}
