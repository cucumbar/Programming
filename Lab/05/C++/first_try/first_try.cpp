#include "first_try.h"
#include "ui_first_try.h"
#include <iostream>
#include <string>
#include <vector>
#include <bitset>
#include <sstream>
#include <QFileDialog>



first_try::first_try(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::first_try)
{
    ui->setupUi(this);
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(save_image()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(open_image()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(decrypt()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(open_image()));
}

first_try::~first_try()
{
    delete ui;
}


//!!
std::vector<char> hex_to_bytes(const std::string& hex) {
  std::vector<char> bytes;

  for (unsigned int i = 0; i < hex.length(); i += 2) {
    std::string byteString = hex.substr(i, 2);
    char byte = (char) strtol(byteString.c_str(), NULL, 16);
    bytes.push_back(byte);
  }

  return bytes;
}
//HEHE IMA EVIL
void vec_to_qba(const std::vector<char> &vec, QByteArray &qba){
    unsigned int size=vec.size();
    qba.resize(size);

    for(unsigned int i=0; i<size; i++){
        qba[i]=(char)vec[i];
    }
}


QColor roll_pixel(QColor pixel, std::string msg_part){
    int int_msg_part{ std::stoi(msg_part) };

    if (int_msg_part / 100){
        if (!(pixel.red() % 2)){
            pixel.setRed(pixel.red() + 1);
        }
    }

    else{
        if (pixel.red() % 2){
            pixel.setRed(pixel.red() - 1);
        }
    }

    if ((int_msg_part % 100) / 10){
        if (!(pixel.green() % 2)){
            pixel.setGreen(pixel.green() + 1);
        }
    }

    else{
        if (pixel.green() % 2){
            pixel.setGreen(pixel.green() - 1);
        }
    }

    if (int_msg_part % 10){
        if (!(pixel.blue() % 2)){
            pixel.setBlue(pixel.blue() + 1);
        }
    }

    else{
        if (pixel.blue() % 2){
            pixel.setBlue(pixel.blue() - 1);
        }
    }

    return pixel;
}

std::string reroll_pixel(QColor const& pixel){
    std::string str{ "" };
    str += std::to_string(pixel.red()) + std::to_string(pixel.green()) + std::to_string(pixel.blue());
    return str;
}

void first_try::decrypt(){
    unsigned int len_control { 57 }, counter{ 0 };
    std::string user_text{ "" }, test{ "" };
    std::stringstream result{ "" };
    bool flag{ false };

    for (int i{ 0 }; i<this->da_file.size().height(); i++){
        for (int j{ 0 }; j<this->da_file.size().width(); j++){

            auto temp_color{ this->da_file.pixelColor(j, i) };
            test += reroll_pixel(temp_color);
            counter += 3;

            if (counter == 24){
                if (test != "111000101001110110100100"){
                    ui->label_3->setText("Сообщения в картинке нет");
                    ui->label_3->setGeometry(QRect(400, 620, 400, 50));
                    return;
                }
            }

            if (counter == len_control){
                if (len_control == 57){
                    len_control += std::bitset<32>(test).to_ulong();
                }

                else{
                    std::cout << test.size();
                    user_text = test.substr(56);
                    flag = true;
                    break;
                }
            }

            if (counter > len_control){
                flag = true;
                break;
            }
        }

        if (flag){
            break;
        }
    }

    user_text = test.substr(56, len_control-1);
    result << std::hex << std::bitset<32>(user_text).to_ulong();

    std::string res = result.str();
    std::vector<char> result_v = hex_to_bytes(res);
    QByteArray tempo;

    vec_to_qba(result_v, tempo);

    QString RESULTED_RESULT = QString::fromUtf8(tempo);

    ui->plainTextEdit_2->setPlainText(RESULTED_RESULT);
    ui->label_3->setText(QString("Присутствует сообщение длиной %1 байт").arg(len_control/8));
}

void first_try::open_image(){
    auto fileContentReady = [this](const QString &fileName, const QByteArray &fileContent) {
        if (fileName.isEmpty()) {
            std::exit(1234);
        } else {
            this->da_file.load(fileContent);
    };


    QString fileName = QFileDialog::getOpenFileName(
                this,
                "Открыть изображение",
                "C://",
                "Изображения (*.png)");

    this->da_file.convertTo(QImage::Format_ARGB32);
    ui->plainTextEdit_2->setPlainText("Izobrajenie uspeshno otkrito");
};


/*
# This Python file uses the following encoding: utf-8
import sys
from bitstring import BitArray

# -*- coding: utf-8 -*-

from PySide2.QtCore import *
from PySide2.QtGui import *
from PySide2.QtWidgets import *

class Ui_first_try(object):
    def __init__(self):
        self.da_file = ""

    def encrypt(self):
        #"11100010 10011101 10100100" + f"{size}" - впереди каждого

        def reroll_pixel(pixel):
            return "".join([str(pixel.red() % 2), str(pixel.green() % 2), str(pixel.blue() % 2)])

        def roll_pixel(pixel, msg_part):
            msg_part = int(msg_part)

            if msg_part // 100:
                if not pixel.red() % 2:
                    pixel.setRed(pixel.red() + 1)

            else:
                if pixel.red() % 2:
                    pixel.setRed(pixel.red() - 1)

            if (msg_part % 100) // 10:
                if not pixel.green() % 2:
                    pixel.setGreen(pixel.green() + 1)

            else:
                if pixel.green() % 2:
                    pixel.setGreen(pixel.green() - 1)

            if msg_part % 10:
                if not pixel.blue() % 2:
                    pixel.setBlue(pixel.blue() + 1)

            else:
                if pixel.blue() % 2:
                    pixel.setBlue(pixel.blue() - 1)

            return qRgb(pixel.red(), pixel.green(), pixel.blue())

        if (((self.da_file.size().width() * self.da_file.size().height()) * 3) + 56) < len(self.string):
            self.label_3.setText("Файл слишком мал для записи.")
            self.label_3.setGeometry(QRect(400, 620, 200, 50))
            return 0

        else:
#            res_pix = roll_pixel(self.da_file.pixelColor(0, 0), "101")
#            print(self.string)

            temp_s = "".join([f'{i:08b}' for i in self.string.encode()]) #BitArray(hex=self.string.encode('utf-8').hex()).bin
#            print(temp_s)
#            print("vhod:", len(temp_s))
            temp_s_l = str(bin(len(temp_s)))[2:]

#            print(temp_s, '\n')
#            print(temp_s_l)

            self.string = "111000101001110110100100" + "".join(['0' for i in range(32-len(temp_s_l))]) + temp_s_l + temp_s
#            print(self.string, '\n')

#            if len(self.string) % 3:    # т.к. мы всегда добавляем октеты(восьмерки битов), мы не можем получить остаток 1 (ТЧ в действии),
#                self.string += '0'      # значит это либо 2 либо 0. если 1 - добавим в конец строки ноль, который не будет влиять на перевод
#                                        # строки обратно из пикселей, т.к. мы будем считывать для декода определенное размером(temp_s_l) число бит.

#            test = ""
            for i in range(self.da_file.size().height()):
                for j in range(self.da_file.size().width()):
                    temp_color = self.da_file.pixelColor(j, i)

                    try:
                        if self.string == '':
                            continue

                        temp_s = self.string[0:3]
                        res_pix = roll_pixel(temp_color, temp_s)
#                        test += reroll_pixel(temp_color)
                        self.da_file.setPixel(j, i, res_pix)
                        self.string = self.string[3:]

                    except IndexError:
                        break

#            print(test)
            self.string.encode("utf-8")
            sTemp = QByteArray(bytes(self.string, 'utf-8'))
            self.label_3.setText("Закодировано")
            self.label_3.setGeometry(QRect(400, 620, 400, 50))
            return 1


    def decrypt(self):
        def reroll_pixel(pixel):
            return "".join([str(pixel.red() % 2), str(pixel.green() % 2), str(pixel.blue() % 2)])

        counter = 0
        user_text = ""
        len_control = 57
        test = ""
        flag = False

        for i in range(self.da_file.size().height()):
            for j in range(self.da_file.size().width()):
                temp_color = self.da_file.pixelColor(j, i)
                test += reroll_pixel(temp_color)
                counter += 3

                if counter == 24: #проверяем кокоро символ
                    if test != "111000101001110110100100":
                        self.label_3.setText("Сообщения в картинке нет.")
                        self.label_3.setGeometry(QRect(400, 620, 600, 50))
                        return

                if counter == len_control:
                    if len_control == 57:
                        len_control += int(test[24:56], 2)
                        print(len(test), len_control)

                    else:
                        print(len(test))
                        user_text = test[56:]
                        flag = True
                        break

                if counter > len_control:
                    flag = True
                    break

            if flag:
                break


        user_text = test[56:len_control-1] #если че тут ошибка может быть
        print(len(test))

        try:
            user_text = int(user_text, 2)
            user_text = hex(user_text)[2:]
            user_text = bytes.fromhex(user_text)

        except ValueError:
            user_text = b''

        user_text = user_text.decode("utf-8")

#        for i in range(self.da_file.size().height()):
#            if counter == 57:
#                break

#            for j in range(self.da_file.size().width()):
#                counter += 3
#                res_str += reroll_pixel(self.da_file.pixelColor(j, i))

#                if counter == 24: #проверяем кокоро символ
#                    if res_str != "111000101001110110100100":
#                        self.label_3.setText("Сообщения в картинке нет.")
#                        self.label_3.setGeometry(QRect(400, 620, 600, 50))
#                        return

#                if counter == 57: #проверяем размер чтоб не по всей картинке шастать
#                    msg_length = int(res_str[24:56], base=2)
#                    print("vyhod:", msg_length)
#                    len_control = 57 + msg_length
#                    save_i = i
#                    save_j = j
#                    break

#        counter = 0
#        res_str_wt = "" #result string with text

#        for i in range(save_i, self.da_file.size().height()):
#            if counter == msg_length:
#                break

#            for j in range(save_j, self.da_file.size().width()):
#                counter += 3
#                res_str_wt += reroll_pixel(self.da_file.pixelColor(j, i))

#                if counter == msg_length:
#                    break


#        print(res_str_wt[0:msg_length+2].lstrip('0'))
#        user_text = int(res_str_wt[0:msg_length+2].lstrip('0'), 2) #хз почему до мсг +2, но работает если делать так. видать концы где то не обстрогал
#        print(str(user_text)[:msg_length])
#        user_text = hex(user_text)[2:]
#        print(user_text)
#        user_text = bytes.fromhex(user_text)
#        print(user_text)
#        user_text = user_text.decode("utf-8")


        self.label_3.setText(f"Обнаружено сообщение длиной {len_control-57}")
        self.label_3.setGeometry(QRect(300, 620, 800, 50))

        self.plainTextEdit_2.setPlainText(user_text)

#        print(res_str)


    def openImage(self):
        fileName, _ = QFileDialog.getOpenFileName(None, "Открыть изображение", "./", "Изображения(*.png)")

        if fileName:
            self.da_file = QImage(fileName)
            self.da_file.convertTo(QImage.Format_ARGB32)

            self.label_3.setText("Файл загружен успешно.")
            self.label_3.setGeometry(QRect(365, 620, 400, 50))

        else:
            self.label_3.setText("Файл не загружен.")
            self.label_3.setGeometry(QRect(400, 620, 400, 50))


    def saveImage(self): #encrypt and save
        self.string = self.plainTextEdit.toPlainText()

        res = self.encrypt()

        if not res:
            self.label_3.setText("Файл слишком мал.")
            self.label_3.setGeometry(QRect(400, 620, 400, 50))
            return 1

        fileName, _ = QFileDialog.getSaveFileName(None, "Сохранить изображение", "./", "Изображения(*.png)")

        if fileName:
            with open(fileName, 'wb') as f:
                temp = QPixmap(self.da_file)

                ba = QByteArray()
                buff = QBuffer(ba)
                buff.open(QIODevice.WriteOnly)
                temp.save(buff, "PNG")
                self.pixmap_bytes = ba.data()

                f.write(self.pixmap_bytes)

            print(fileName)
            self.label_3.setText("Файл зашифрован и сохранен успешно.")
            self.label_3.setGeometry(QRect(365, 620, 600, 50))

        else:
            self.label_3.setText("Файл не сохранен.")
            self.label_3.setGeometry(QRect(365, 620, 400, 50))

    def setupUi(self, first_try):
        if not first_try.objectName():
            first_try.setObjectName(u"first_try")
        first_try.resize(1030, 680)
        sizePolicy = QSizePolicy(QSizePolicy.Fixed, QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(first_try.sizePolicy().hasHeightForWidth())
        first_try.setSizePolicy(sizePolicy)
        first_try.setMinimumSize(QSize(1030, 680))
        first_try.setMaximumSize(QSize(1030, 680))
        first_try.setStyleSheet(u"background-color:rgb(60, 197, 255)")
        self.centralwidget = QWidget(first_try)
        self.centralwidget.setObjectName(u"centralwidget")
        self.pushButton = QPushButton(self.centralwidget)
        self.pushButton.setObjectName(u"pushButton")
        self.pushButton.setGeometry(QRect(40, 550, 145, 65))
        font = QFont()
        font.setFamily(u"Roboto")
        font.setPointSize(11)
        self.pushButton.setFont(font)
        self.pushButton.setCursor(QCursor(Qt.PointingHandCursor))
        self.pushButton.setStyleSheet(u"background-color: blue;\n"
"color: white;\n"
"border-radius: 15px;\n"
"\n"
"font-family: Roboto;\n"
"\n"
"QPushButton#pushButton:hover{\n"
"background-color: black;\n"
"}\n"
"")
        self.plainTextEdit = QPlainTextEdit(self.centralwidget)
        self.plainTextEdit.setObjectName(u"plainTextEdit")
        self.plainTextEdit.setGeometry(QRect(40, 230, 441, 291))
        self.plainTextEdit.viewport().setProperty("cursor", QCursor(Qt.IBeamCursor))
        self.plainTextEdit.setStyleSheet(u"font-size: 18px;\n"
"background-color:rgb(193, 244, 255)\n"
"\n"
"")
        self.pushButton_2 = QPushButton(self.centralwidget)
        self.pushButton_2.setObjectName(u"pushButton_2")
        self.pushButton_2.setGeometry(QRect(40, 180, 161, 31))
        font1 = QFont()
        font1.setPointSize(11)
        self.pushButton_2.setFont(font1)
        self.pushButton_2.setCursor(QCursor(Qt.PointingHandCursor))
        self.pushButton_2.setStyleSheet(u"background-color: blue;\n"
"color: white;\n"
"border-radius: 15px;\n"
"alternate-background-color: rgb(170, 85, 255);")
        self.label = QLabel(self.centralwidget)
        self.label.setObjectName(u"label")
        self.label.setGeometry(QRect(70, 30, 411, 81))
        font2 = QFont()
        font2.setFamily(u"Verdana")
        font2.setPointSize(18)
        font2.setBold(True)
        font2.setItalic(True)
        font2.setUnderline(False)
        font2.setWeight(75)
        self.label.setFont(font2)
        self.label.setCursor(QCursor(Qt.ArrowCursor))
        self.label.setAutoFillBackground(False)
        self.label.setStyleSheet(u"border-color: rgb(255, 0, 4);")
        self.label_2 = QLabel(self.centralwidget)
        self.label_2.setObjectName(u"label_2")
        self.label_2.setGeometry(QRect(570, 30, 421, 81))
        self.label_2.setFont(font2)
        self.label_2.setCursor(QCursor(Qt.ArrowCursor))
        self.label_2.setAutoFillBackground(False)
        self.label_2.setStyleSheet(u"border-color: rgb(255, 0, 4);")

        font3 = QFont()
        font3.setFamily(u"Verdana")
        font3.setPointSize(13)
        font3.setBold(True)
        font3.setItalic(False)
        font3.setUnderline(False)
        font3.setWeight(75)
        self.label_3 = QLabel(self.centralwidget)
        self.label_3.setObjectName(u"label")
        self.label_3.setGeometry(QRect(400, 620, 400, 50))
        self.label_3.setFont(font3)
        self.label_3.setCursor(QCursor(Qt.ArrowCursor))
        self.label_3.setAutoFillBackground(False)

        self.plainTextEdit_2 = QPlainTextEdit(self.centralwidget)
        self.plainTextEdit_2.setObjectName(u"plainTextEdit_2")
        self.plainTextEdit_2.setGeometry(QRect(550, 230, 441, 291))
        self.plainTextEdit_2.viewport().setProperty("cursor", QCursor(Qt.IBeamCursor))
        self.plainTextEdit_2.setStyleSheet(u"font-size: 18px;\n"
"background-color:rgb(193, 244, 255)\n"
"\n"
"")
        self.plainTextEdit_2.setReadOnly(True)
        self.pushButton_3 = QPushButton(self.centralwidget)
        self.pushButton_3.setObjectName(u"pushButton_3")
        self.pushButton_3.setGeometry(QRect(550, 550, 141, 41))
        self.pushButton_3.setFont(font)
        self.pushButton_3.setCursor(QCursor(Qt.PointingHandCursor))
        self.pushButton_3.setStyleSheet(u"background-color: blue;\n"
"color: white;\n"
"border-radius: 15px;\n"
"\n"
"font-family: Roboto;\n"
"\n"
"")
        self.pushButton_4 = QPushButton(self.centralwidget)
        self.pushButton_4.setObjectName(u"pushButton_4")
        self.pushButton_4.setGeometry(QRect(550, 180, 161, 31))
        self.pushButton_4.setFont(font1)
        self.pushButton_4.setCursor(QCursor(Qt.PointingHandCursor))
        self.pushButton_4.setStyleSheet(u"background-color: blue;\n"
"color: white;\n"
"border-radius: 15px;")
        first_try.setCentralWidget(self.centralwidget)
        self.menubar = QMenuBar(first_try)
        self.menubar.setObjectName(u"menubar")
        self.menubar.setGeometry(QRect(0, 0, 1030, 26))
        first_try.setMenuBar(self.menubar)
        self.statusbar = QStatusBar(first_try)
        self.statusbar.setObjectName(u"statusbar")
        first_try.setStatusBar(self.statusbar)
#        self.get_files_enc = OPENER()
#        self.get_files_dec = OPENER()

        self.retranslateUi(first_try)
        self.pushButton_2.clicked.connect(self.openImage) ##@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        self.pushButton_4.clicked.connect(self.openImage) ##@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        self.pushButton.clicked.connect(self.saveImage) ##@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        self.pushButton_3.clicked.connect(self.decrypt)

        QMetaObject.connectSlotsByName(first_try)
    # setupUi

    def retranslateUi(self, first_try):
            first_try.setWindowTitle(QCoreApplication.translate("first_try", u"first_try", None))
            self.pushButton.setText(QCoreApplication.translate("first_try", u"\u0417\u0430\u0448\u0438\u0444\u0440\u043e\u0432\u0430\u0442\u044c\n"
    "\u0438 \u0441\u043e\u0445\u0440\u0430\u043d\u0438\u0442\u044c", None))
    #if QT_CONFIG(tooltip)
            self.plainTextEdit.setToolTip(QCoreApplication.translate("first_try", u"<html><head/><body><p>\u041d\u0435 \u0445\u043e\u0442\u0438\u0442\u0435 - \u043d\u0435 \u0432\u0432\u043e\u0434\u0438\u0442\u0435</p></body></html>", None))
    #endif // QT_CONFIG(tooltip)
            self.plainTextEdit.setPlainText("")
            self.plainTextEdit.setPlaceholderText(QCoreApplication.translate("first_try", u"\u0412\u0432\u0435\u0434\u0438\u0442\u0435 \u0442\u0435\u043a\u0441\u0442...", None))
            self.pushButton_2.setText(QCoreApplication.translate("first_try", u"\u0412\u044b\u0431\u0440\u0430\u0442\u044c \u0444\u0430\u0439\u043b...", None))
            self.label.setText(QCoreApplication.translate("first_try", u"\u0417\u0430\u043a\u043e\u0434\u0438\u0440\u0443\u0439\u0442\u0435 \u043f\u043e\u0441\u043b\u0430\u043d\u0438\u0435\n"
    "         \u0432 \u043a\u0430\u0440\u0442\u0438\u043d\u043a\u0443!!!", None))
            self.label_2.setText(QCoreApplication.translate("first_try", u"\u0420\u0430\u0441\u043a\u043e\u0434\u0438\u0440\u0443\u0439\u0442\u0435 \u043f\u043e\u0441\u043b\u0430\u043d\u0438\u0435\n"
    "         \u0438\u0437 \u043a\u0430\u0440\u0442\u0438\u043d\u043a\u0438!!!", None))
    #if QT_CONFIG(tooltip)
            self.plainTextEdit_2.setToolTip(QCoreApplication.translate("first_try", u"<html><head/><body><p>\u041d\u0435 \u0445\u043e\u0442\u0438\u0442\u0435 - \u043d\u0435 \u043a\u043e\u043f\u0438\u0440\u0443\u0439\u0442\u0435</p></body></html>", None))
    #endif // QT_CONFIG(tooltip)
            self.plainTextEdit_2.setPlainText("")
            self.plainTextEdit_2.setPlaceholderText(QCoreApplication.translate("first_try", u"\u0417\u0434\u0435\u0441\u044c \u0431\u0443\u0434\u0435\u0442 \u0440\u0435\u0437\u0443\u043b\u044c\u0442\u0430\u0442...", None))
            self.pushButton_3.setText(QCoreApplication.translate("first_try", u"\u0420\u0430\u0441\u0448\u0438\u0444\u0440\u043e\u0432\u0430\u0442\u044c", None))
            self.pushButton_4.setText(QCoreApplication.translate("first_try", u"\u0412\u044b\u0431\u0440\u0430\u0442\u044c \u0444\u0430\u0439\u043b...", None))


if __name__ == '__main__':
    app = QApplication(sys.argv)
    Form = QMainWindow()
    ui = Ui_first_try()
    ui.setupUi(Form)
    Form.show()
    sys.exit(app.exec_())

*/

}
