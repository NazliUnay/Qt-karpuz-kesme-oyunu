// Şerife Nazlı Ünay

#include "mainwindow.h"
#include "ui_mainwindow.h"

constexpr int KARPUZ_GENISLIK = 80;
constexpr int KARPUZ_YUKSEKLIK = 80;
constexpr int DUSME_HIZI = 5;
constexpr int OYUN_SURESI = 30;

MainWindow::MainWindow(QWidget *parent)
    :QMainWindow(parent), ui(new Ui::MainWindow), skor(0), kacirilanKarpuz(0), kalanSure(OYUN_SURESI)
{
    ui->setupUi(this);
    ui->background->lower(); // Arka planda olması için

    karpuzOlusturTimer = new QTimer(this);
    karpuzDusurTimer = new QTimer(this);
    bitir = new QTimer(this);
    sureTimer = new QTimer(this);

    connect(karpuzOlusturTimer,SIGNAL(timeout()),this,SLOT(karpuzOlustur()));
    connect(karpuzDusurTimer,SIGNAL(timeout()),this,SLOT(karpuzlariHareketEttir()));
    connect(bitir, SIGNAL(timeout()), this,SLOT(oyunuBitir()));
    connect(sureTimer,SIGNAL(timeout()), this,SLOT(sureGuncelle()));

    bitir->setSingleShot(true); // Oyun sonu yalnızca bir kez tetiklenmeli

    oyunuYenidenBaslat();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::konumlariYukle()
{
    QFile file(":/veri/konumlar.txt");
    if (!file.exists()) {
        qDebug() << "Dosya bulunamadı!";
        return;
    }
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Dosya açılamadı! " << file.errorString();
        return;
    }

    konumlar.clear(); // Yeniden başlatmalarda listenin büyümesini önler

    QTextStream stream(&file);
    while (!stream.atEnd()) {
        // Satır bir kez okunur; doğrulanan satırın kendisi listeye eklenir
        const QString satir = stream.readLine().trimmed();
        if (satir.isEmpty()) continue;

        const QStringList parcala = satir.split(" ");
        bool okX = false, okY = false;
        if (parcala.size() == 2) {
            parcala[0].toInt(&okX); // 0 koordinatı da geçerli kabul edilir
            parcala[1].toInt(&okY);
        }

        if (okX && okY) {
            konumlar.append(satir);
        } else {
            qDebug() << "Geçersiz konum satırı atlandı: " << satir;
        }
    }
    file.close();
}

void MainWindow::skorlariYukle()
{
    QFile file("skorlar.txt");
    if (!file.exists()) {
        qDebug() << "Skor dosyası bulunamadı, yeni dosya oluşturulacak.";
    }
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qDebug() << "Skor dosyası açılamadı!"; return;
    }

    QTextStream stream(&file);
    enBuyukSkor = 0;
    while (!stream.atEnd()) {
        skor = stream.readLine().toInt();
        if (skor > enBuyukSkor) {
            enBuyukSkor = skor;
        }
    }
    skor=0;
    ui->max->setText("😎 Max skor: "+QString::number(enBuyukSkor));
    file.close();
}

void MainWindow::karpuzOlustur()
{
    if (konumlar.isEmpty()) return;

    index = QRandomGenerator::global()->bounded(konumlar.size());
    QStringList konumParcalari = konumlar[index].split(" ");



    if (konumParcalari.size() == 2) {
        int x = konumParcalari[0].toInt();
        int y = konumParcalari[1].toInt();
        if (x < 0 || x > width() - KARPUZ_GENISLIK || y < 0 || y > height() - KARPUZ_YUKSEKLIK) { /// pencere dışında konumlar içeriyorsa
            qDebug() << "Koordinatlar pencere dışı: " << x << y;
            konumlar.removeAt(index);
            return;
        }
        QLabel *karpuz = new QLabel(this);
        karpuz->setStyleSheet("border-image: url(:/gorseller/images/1.png); border-radius: 35px;");
        karpuz->setGeometry(x, y, KARPUZ_GENISLIK, KARPUZ_YUKSEKLIK);
        karpuz->show();
        karpuz->installEventFilter(this);

        karpuzlar.push_back(karpuz);
    } else {
        qDebug() << "Hatalı format, konum siliniyor: " << konumlar[index];
        konumlar.removeAt(index); // Hatalı konumu listeden çıkar
        return;
    }
}
void MainWindow::karpuzlariHareketEttir()
{
    int i = 0;
    while (i < karpuzlar.length()) {
        QLabel *karpuz = karpuzlar[i];
        if (karpuz->y() >= this->height()) {
            kacirilanKarpuz++;
            ui->lbn_kacirilanKarpuzSayisi->setText("<font color='black'> 🥺Kaçırılan Karpuz: </font><font color='red'>" + QString::number(kacirilanKarpuz) + "</font>");
            delete karpuz; // Bellekten kaldır
            karpuzlar.removeAt(i); // Listeden çıkar
        } else {
            karpuz->move(karpuz->x(), karpuz->y() + DUSME_HIZI);
            i++; // Sadece taşınan karpuzlar için artırılır
        }
    }

}

bool MainWindow::eventFilter(QObject *targetObjec, QEvent *event)
{
    if (event->type() != QEvent::MouseButtonPress) {
        bool sonuc= QMainWindow::eventFilter(targetObjec, event);
        return sonuc;
    }
    else{
        if (QLabel *clickedLabel = qobject_cast<QLabel *>(targetObjec)) {
            karpuzKes(clickedLabel);
            return true;
        }
        return false;
    }

}

void MainWindow::karpuzKes(QLabel *karpuz)
{
    // Zaten kesilmiş (listeden çıkarılmış) karpuza tekrar tıklanırsa puan verilmez
    index = karpuzlar.indexOf(karpuz);
    if (index == -1) return;
    karpuzlar.removeAt(index);
    karpuz->removeEventFilter(this);

    skor++;
    // Skor maksimumu geçtiyse mesaj göster
    if (skor > enBuyukSkor) {
        ui->lbn_mesaj->setText("<font color='darkgreen'><b>🏆 Yeni Rekor Kırdınız! 🏆</b></font>");

        // 3 saniye sonra mesajı temizle
        QTimer::singleShot(3000, this, [=]() {
            ui->lbn_mesaj->clear();
        });
    }
    karpuz->setStyleSheet("border-image: url(:/gorseller/images/2.png); border-radius: 35px;");
    QTimer::singleShot(1000, karpuz, &QLabel::deleteLater);

    ui->lbn_kesilenKarpuzSayisi->setText("<font color='black'> 😆Kesilen Karpuz: </font><font color='green'>" + QString::number(skor) + "</font>");
}
void MainWindow::oyunuBitir()
{
    bitir->stop();
    sureTimer->stop();
    karpuzDusurTimer->stop();
    karpuzOlusturTimer->stop();

    QFile file("skorlar.txt");
    if (file.open(QIODevice::Append| QIODevice::Text)) {
        QTextStream stream(&file);
        stream << QString::number(skor) << "\n";
        file.close();
    }
    // Tüm QLabel nesnelerini güvenli bir şekilde sil
    for (QLabel* karpuz : karpuzlar) {
        delete karpuz;
    }
    karpuzlar.clear();
    QMessageBox::information(this, "Bilgi", Mesaj());
    if (QMessageBox::question(this, "Oyun Bitti","\nTekrar oynamak ister misiniz?") == QMessageBox::Yes) {
        oyunuYenidenBaslat();
    } else {
        close();
    }
}

void MainWindow::sureGuncelle()
{
    ui->lbn_sure->setText("<font color='black'> ⏳Süre: </font><font color='blue'>" +  QString::number(--kalanSure)+"</font>" );
    if (kalanSure <= 0) {
        sureTimer->stop();
        return;
    }
}

QString MainWindow::Mesaj()
{
    if (skor <= enBuyukSkor) {
        return "Oyun Bitti! \n😭 Maksimum Skoru Geçemediniz! 😭\n😆Kesilen Karpuz: " + QString::number(skor)
               + "\n🥺Kaçırılan Karpuz: " + QString::number(kacirilanKarpuz)
               + "\n😎Maksimum Skor: " + QString::number(enBuyukSkor);

    } else {
        return "Oyun Bitti! \n🏆 Tebrikler, Maksimum Skor Sizde! 🏆\n😆Kesilen Karpuz: " + QString::number(skor)
        + "\n🥺Kaçırılan Karpuz: " + QString::number(kacirilanKarpuz)
            + "\n😎Maksimum Skor: " + QString::number(enBuyukSkor);
    }
}
void MainWindow::oyunuYenidenBaslat()
{
    konumlariYukle(); //konumlari yükle
    skorlariYukle(); // Mevcut skorları yükle

    // Etiketleri sıfırla
    ui->lbn_kesilenKarpuzSayisi->setText("<font color='black'>😆Kesilen Karpuz: </font><font color='green'>0</font>");
    ui->lbn_kacirilanKarpuzSayisi->setText("<font color='black'> 🥺Kaçırılan Karpuz: </font><font color='red'>0</font>");
    ui->lbn_sure->setText("<font color='black'> ⏳Süre: </font><font color='blue'>30</font>");
    ui->max->setText("😎 Max skor: "+QString::number(enBuyukSkor));
    // Skor ve sayacı sıfırla
    skor = 0;kacirilanKarpuz = 0;kalanSure = OYUN_SURESI;


    ui->lbn_mesaj->setText("<font color='darkgreen'><b>🍉 !!! OYUN BAŞLADI !!! 🍉</b></font>");
    QTimer::singleShot(3000, this, [=]() {
        ui->lbn_mesaj->clear();
    });

    // Varsa ekranda kalan karpuzları sil
    for (QLabel* karpuz : karpuzlar) {
        delete karpuz;
    }
    karpuzlar.clear();

    // Zamanlayıcıları yeniden başlat
    karpuzOlusturTimer->start(500);
    karpuzDusurTimer->start(60);
    bitir->start(OYUN_SURESI*1000);
    sureTimer->start(1000);
}
