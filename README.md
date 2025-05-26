
# 🎮 Karpuz Kesme Oyunu (Görsel Programlama Ödevi)

## 👤 Öğrenci Bilgileri

- **Ad Soyad:** [Adınız Soyadınız]
- **Öğrenci No:** 23100011009
- **Ders:** 2024-2025 Bahar Yarıyılı - Görsel Programlama
- **Ödev:** 1. Laboratuvar Uygulaması

---

## 📌 Oyun Açıklaması

Bu proje, *Fruit Ninja* oyunundan esinlenilerek oluşturulmuş bir **karpuz kesme oyunudur**. Amaç, 30 saniyelik süre içerisinde mümkün olduğunca çok karpuzu keserek yüksek skor elde etmektir.

---

## 🚀 Özellikler

- ✅ Qt 5/6 ile GUI geliştirme
- ✅ `QMainWindow` tabanlı tam ekran arayüz
- ✅ `konumlar.txt` dosyasından konum okuma
- ✅ `QTimer` ile zamanlama ve süre takibi
- ✅ `QPixmap` ve `QLabel` ile karpuz görselleri
- ✅ Mouse ile tıklama ile kesme animasyonu
- ✅ Kesilen/kaçırılan karpuz sayısı ve kalan süre üst panelde
- ✅ `skorlar.txt` dosyasına skor kaydı
- ✅ Maksimum skor kontrolü ve kullanıcıya gösterimi
- ✅ Qt kaynak sistemi (`kaynaklarim.qrc`) üzerinden görsel yönetimi

---

## 📂 Proje Yapısı

```
23100011009_Odev1/
├── main.cpp
├── mainwindow.cpp
├── mainwindow.h
├── mainwindow.ui
├── ui_mainwindow.h
├── kaynaklarim.qrc
├── konumlar.txt
├── skorlar.txt
├── images/               # Karpuz ve kesilmiş karpuz resimleri
└── README.md             
```

---

## 🛠 Kurulum & Çalıştırma

1. **Qt Creator** ile `23100011009_Odev1.pro` dosyasını açın.
2. Gerekli kaynakların (resimler, `konumlar.txt`) proje dizininde olduğundan emin olun.
3. Projeyi derleyin ve çalıştırın.
4. Oyun başladığında 30 saniye süresince karpuzlara tıklayarak en yüksek skoru yapmaya çalışın.

---

## ⏳ Oyun Süreci

- Oyun başladığında 30 saniyelik sayaç devreye girer.
- `konumlar.txt`'den alınan konumlara göre karpuzlar belirir.
- Tıklanan karpuzlar kesilmiş karpuza dönüşür ve kısa süre sonra kaybolur.
- Her kaçırılan karpuz istatistiklere yansır.
- Süre bittiğinde oyun sona erer ve skor `skorlar.txt` dosyasına kaydedilir.

---

## 📽️ Ekran Kaydı

Oyun içi deneyimi görmek için aşağıdaki videoyu izleyebilirsiniz:

🎥 [Karpuz Kesme Oyunu Tanıtım Videosu](https://www.youtube.com/watch?v=IJ7QwbOhyuI)
![Oyun Demo](https://s6.ezgif.com/tmp/ezgif-639ea8262b165a.gif) 
---

## 📝 Proje Hakkında Medium Yazısı

Bu proje hakkında yazdığım detaylı yazıya aşağıdaki bağlantıdan ulaşabilirsiniz:

👉 (Medium yazı linki buraya)

---
## 👩‍💻 Geliştirici Bilgileri

- **Ad Soyad**: Şerife Nazlı Ünay  
- **Üniversite**: Necmettin Erbakan Üniversitesi  
- **Bölüm**: Bilgisayar Mühendisliği  
- **LinkedIn**: [linkedin.com/in/serife-nazli-unay](https://www.linkedin.com/in/serife-nazli-unay/)  
- **Medium**: [medium.com/@nazli_unay](https://medium.com/@nazli_unay)
---

## ✉️ İletişim

Herhangi bir geri bildirim ya da geliştirme önerisi için iletişime geçebilirsiniz.  
📧 E-posta: [unay.nazli42@gmail.com]
