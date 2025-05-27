// Şerife Nazlı Ünay

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

// proje Qt Widgets tabanlı olduğu için!
#include <QtWidgets/QApplication>
// Qt uygulamasının çalışmasını başlatan sınıf. QApplication, Qt uygulamasının tüm yaşam döngüsünü yönetir ve bu sınıf olmadan uygulama başlatılamaz.

#include <QtWidgets/QMainWindow>
// Qt'deki ana pencereyi oluşturmak için kullanılan sınıf. Uygulamanın ana penceresini yönetmek ve içeriğini düzenlemek için kullanılır.

#include <QtWidgets/QLabel>
// QLabel, bir metin veya resim göstermek için kullanılır. Bu sınıf, kullanıcı arayüzündeki etiketleri (örneğin, bir açıklama veya gösterge) oluşturur.

#include <QtWidgets/QWidget>
/*QWidget, Qt'nin temel kullanıcı arayüzü (UI) öğelerinin temel sınıfıdır ve
genellikle pencere, düğme, etiket gibi görsel bileşenleri oluşturmak için kullanılır.
QWidget, arayüz elemanlarının (butonlar, metin kutuları, vb.) temel özelliklerini ve fonksiyonlarını içerir.
Bu sınıf, tüm görsel bileşenlerin üst sınıfıdır ve QWidget sınıfından türetilmiş diğer bileşenler bu sınıfın özelliklerine sahip olur.
*/
#include <QTimer>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget; // Merkezi içerik alanı
     // Ekranda gösterilecek olan metin etiketleri
    QLabel *lbn_sure, *lbn_kesilenKarpuzSayisi, *lbn_kacirilanKarpuzSayisi, *background, *max,*lbn_mesaj;

    void setupUi(QMainWindow *MainWindow) // Kullanıcı arayüzünü
    {
        if (MainWindow->objectName().isEmpty())//adı boşsa ana pencereyi adlandır
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));

        centralWidget = new QWidget(MainWindow);//ana pencere için içerik alanı
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));

        lbn_sure = new QLabel(centralWidget);
        lbn_sure->setObjectName(QString::fromUtf8("lbn_sure"));
        lbn_sure->setGeometry(QRect(20, 50, 200, 30));
        lbn_sure->setStyleSheet("color: black; font: bold 20px;");
        lbn_sure->setText("⏳ Süre: <font color='blue'>30</font>");


        lbn_kesilenKarpuzSayisi = new QLabel(centralWidget);
        lbn_kesilenKarpuzSayisi->setObjectName(QString::fromUtf8("lbn_kesilenKarpuzSayisi"));
        lbn_kesilenKarpuzSayisi->setGeometry(QRect(1250, 10, 250, 40));
        lbn_kesilenKarpuzSayisi->setStyleSheet("color: black; font: bold 20px;");
        lbn_kesilenKarpuzSayisi->setText("Kesilen Karpuz: <font color='green'>0</font>");


        lbn_kacirilanKarpuzSayisi = new QLabel(centralWidget);
        lbn_kacirilanKarpuzSayisi->setObjectName(QString::fromUtf8("lbn_kacirilanKarpuzSayisi"));
        lbn_kacirilanKarpuzSayisi->setGeometry(QRect(1250, 50, 250, 40));
        lbn_kacirilanKarpuzSayisi->setStyleSheet("color: black; font: bold 20px;");
        lbn_kacirilanKarpuzSayisi->setText("🥺Kaçırılan Karpuz: <font color='red'>0</font>");

        max = new QLabel(centralWidget);
        max->setObjectName(QString::fromUtf8("lbn_kesilenKarpuzSayisi"));
        max->setGeometry(QRect(20, 10, 200, 30));
        max->setStyleSheet("color: black; font: bold 20px;");
        max->setText("😎 Max skor: ");

        background= new QLabel(centralWidget);
        background->setObjectName(QString::fromUtf8("background"));
        background->setStyleSheet("border-image: url(:/gorseller/images/back.jpg)");
        background->setGeometry(0, 100,1600, 1200);


        lbn_mesaj= new QLabel(centralWidget);
        lbn_mesaj->setObjectName(QString::fromUtf8("lbn_mesaj"));
        lbn_mesaj->setStyleSheet("color: black; font: bold 20px;");
        lbn_mesaj->setGeometry(QRect(600, 10, 300, 30));


        MainWindow->setCentralWidget(centralWidget);
        // Ana pencereyi içerik widget'ı olarak ayarlıyoruz
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Karpuz Kesme Oyunu", nullptr));

    }

};

namespace Ui {
class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
