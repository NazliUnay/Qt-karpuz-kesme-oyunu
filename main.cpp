// Şerife Nazlı Ünay
// 23100011009

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication> // Qt uygulama sınıfını içerir, uygulamanın çalışması için gereklidir
#include <QScreen> // Ekran bilgilerini almak için kullanılır

int main(int argc, char *argv[]) {
    QApplication app(argc, argv); // Uygulamayı başlatır, QApplication bir Qt uygulamasının temel yapı taşıdır
    MainWindow window; // MainWindow sınıfından bir nesne oluşturuluyor, bu ana pencereyi temsil eder

    QScreen *screen = QApplication::primaryScreen(); // Ana ekranı alır
    QSize screenSize = screen->size(); // Ekran çözünürlüğünü alır, ekranın boyutlarını verir
    window.resize(screenSize); // Uygulamanın penceresini ekran boyutlarına göre yeniden boyutlandırır

    window.show(); //ekranda göster

    return app.exec(); // Uygulamayıbaşlatır, uygulama çalışmaya devam eder
}
