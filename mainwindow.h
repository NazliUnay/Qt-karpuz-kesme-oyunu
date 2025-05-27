// Şerife Nazlı Ünay

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>   // Qt'deki ana pencere sınıfı
#include <QDialog>       // Qt'deki dialog sınıfı (gereksiz olsa da eklenebilir)
#include <QLabel>        // QLabel, metin ve görsel içerik görüntülemek için
#include <QTimer>        // Zamanlayıcılar, oyunun zamanını ve karpuzları kontrol etmek için
#include <QFile>         // Dosya işlemleri için (skorları kaydetme ve yükleme)
#include <QTextStream>   // Dosya okuma/yazma işlemleri için (skorlar.txt'yi işlemek için)
#include <QDebug>        // Hata ayıklama mesajları için
#include <QMessageBox>   // Oyun bitiminde mesaj kutuları gösterme için
#include <QRandomGenerator> // Rastgele sayı üretmek için (karpuzların pozisyonlarını belirlemek için)
#include <QEvent>        // Etkinlikler için (tıklama gibi)

QT_BEGIN_NAMESPACE
namespace Ui {class MainWindow;} // Ana pencere UI sınıfını tanımlıyoruz
QT_END_NAMESPACE

// MainWindow sınıfı, QMainWindow sınıfından türetilmiş olup oyunun ana penceresini ve işlevselliğini yönetir.
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);  // Constructor: Başlangıçta pencereyi başlatır
    ~MainWindow(); // Destructor: Pencere kapandığında belleği temizler

private slots:
    void karpuzOlustur();
    void karpuzlariHareketEttir();
    void karpuzKes(QLabel *karpuz);
    void oyunuBitir();
    void sureGuncelle();

private:
    Ui::MainWindow *ui; // UI öğelerine erişim sağlar

    QTimer *bitir, *karpuzOlusturTimer, *karpuzDusurTimer, *sureTimer; // Zamanlayıcılar, oyunun işleyişini kontrol eder

    QList<QLabel*> karpuzlar; // QLabel ve Y koordinatı tutan vektör (karpuzlar burada saklanır)
    QStringList konumlar;

    int skor, kacirilanKarpuz, kalanSure, enBuyukSkor, index;
    QLabel *clickedLabel; // Tıklanan karpuz label'ını tutar

    void konumlariYukle(); // Karpuzların yerlerini yükler
    void skorlariYukle();
    void oyunuYenidenBaslat();
    QString Mesaj(); // Oyun bitiminde gösterilecek mesajı döndürür

protected:
    bool eventFilter(QObject *targetObjec, QEvent *event) override; // Event filtresi, fare tıklamaları gibi olayları kontrol eder
};

#endif // MAINWINDOW_H
