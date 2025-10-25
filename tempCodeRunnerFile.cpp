#include <iostream>
#include <string>
#include <fstream>
using namespace std;

const int MAX_KITAP = 100;

struct Kitap {
    string kitapAdi, yazarAdi, isbn;
    int yayinYili;
};

void kitapEkle(Kitap kitaplar[], int &kitapSayisi) {
    if (kitapSayisi >= MAX_KITAP) {
        cout << "Kitap eklenemiyor, maksimum kapasiteye ulaşıldı." << endl;
        return;
    }
    cout << "Kitap adi: "; getline(cin, kitaplar[kitapSayisi].kitapAdi);
    cout << "Yazar adi: "; getline(cin, kitaplar[kitapSayisi].yazarAdi);
    cout << "Yayin yili: "; cin >> kitaplar[kitapSayisi].yayinYili; cin.ignore();
    cout << "ISBN numarasi: "; getline(cin, kitaplar[kitapSayisi].isbn);
    kitapSayisi++;
    cout << "Kitap başariyla eklendi!" << endl;
}

void kitapListele(const Kitap kitaplar[], int kitapSayisi) {
    if (kitapSayisi == 0) {
        cout << "Listelenecek kitap bulunamadi." << endl;
        return;
    }
    cout << "\nKayitli Kitaplar:" << endl;
    for (int i = 0; i < kitapSayisi; i++)
        cout << i + 1 << ". " << kitaplar[i].kitapAdi << ", " << kitaplar[i].yazarAdi
             << ", " << kitaplar[i].yayinYili << ", " << kitaplar[i].isbn << endl;
}

void kitapAra(const Kitap kitaplar[], int kitapSayisi) {
    string aramaKriteri; cout << "Kitap adı veya yazar adı girin: "; getline(cin, aramaKriteri);
    bool bulundu = false;
    for (int i = 0; i < kitapSayisi; i++) {
        if (kitaplar[i].kitapAdi.find(aramaKriteri) != string::npos ||
            kitaplar[i].yazarAdi.find(aramaKriteri) != string::npos) {
            cout << kitaplar[i].kitapAdi << ", " << kitaplar[i].yazarAdi << ", "
                 << kitaplar[i].yayinYili << ", " << kitaplar[i].isbn << endl;
            bulundu = true;
        }
    }
    if (!bulundu) cout << "Kitap bulunamadi." << endl;
}

void kitapSil(Kitap kitaplar[], int &kitapSayisi) {
    string silinecek; cout << "Silmek istediğiniz kitabin adi veya ISBN numarasini girin: ";
    getline(cin, silinecek);
    for (int i = 0; i < kitapSayisi; i++) {
        if (kitaplar[i].kitapAdi == silinecek || kitaplar[i].isbn == silinecek) {
            for (int j = i; j < kitapSayisi - 1; j++)
                kitaplar[j] = kitaplar[j + 1];
            kitapSayisi--;
            cout << "Kitap başariyla silindi!" << endl;
            return;
        }
    }
    cout << "Kitap bulunamadı." << endl;
}

void kitapGuncelle(Kitap kitaplar[], int kitapSayisi) {
    string guncellenecek; cout << "Güncellemek istediğiniz kitabın adını veya ISBN numarasını girin: ";
    getline(cin, guncellenecek);
    for (int i = 0; i < kitapSayisi; i++) {
        if (kitaplar[i].kitapAdi == guncellenecek || kitaplar[i].isbn == guncellenecek) {
            cout << "Yeni kitap adı (boş bırakılırsa değişmez): "; string yeniAdi; getline(cin, yeniAdi);
            if (!yeniAdi.empty()) kitaplar[i].kitapAdi = yeniAdi;
            cout << "Yeni yazar adı (boş bırakılırsa değişmez): "; string yeniYazar; getline(cin, yeniYazar);
            if (!yeniYazar.empty()) kitaplar[i].yazarAdi = yeniYazar;
            cout << "Yeni yayın yılı (0 girilirse değişmez): "; int yeniYil; cin >> yeniYil; cin.ignore();
            if (yeniYil != 0) kitaplar[i].yayinYili = yeniYil;
            cout << "Yeni ISBN numarası (boş bırakılırsa değişmez): "; string yeniIsbn; getline(cin, yeniIsbn);
            if (!yeniIsbn.empty()) kitaplar[i].isbn = yeniIsbn;
            cout << "Kitap bilgileri başarıyla güncellendi!" << endl;
            return;
        }
    }
    cout << "Kitap bulunamadı." << endl;
}

void dosyadanOku(Kitap kitaplar[], int &kitapSayisi) {
    ifstream dosya("kitaplar.txt");
    if (!dosya) { cout << "Dosya okunamadı, yeni bir dosya oluşturulacak." << endl; return; }
    while (!dosya.eof() && kitapSayisi < MAX_KITAP) {
        getline(dosya, kitaplar[kitapSayisi].kitapAdi);
        getline(dosya, kitaplar[kitapSayisi].yazarAdi);
        dosya >> kitaplar[kitapSayisi].yayinYili;
        dosya.ignore(); getline(dosya, kitaplar[kitapSayisi].isbn);
        dosya.ignore();
        if (!kitaplar[kitapSayisi].kitapAdi.empty()) kitapSayisi++;
    }
    dosya.close();
}

void dosyayaYaz(const Kitap kitaplar[], int kitapSayisi) {
    ofstream dosya("kitaplar.txt");
    if (!dosya) { cout << "Dosya yazılamadı." << endl; return; }
    for (int i = 0; i < kitapSayisi; i++) {
        dosya << kitaplar[i].kitapAdi << endl;
        dosya << kitaplar[i].yazarAdi << endl;
        dosya << kitaplar[i].yayinYili << endl;
        dosya << kitaplar[i].isbn << endl;
        dosya << endl;
    }
    dosya.close();
}

int main() {
    Kitap kitaplar[MAX_KITAP];
    int kitapSayisi = 0, secim;
    dosyadanOku(kitaplar, kitapSayisi);
    do {
        cout << "\nKitap Kayıt Sistemi\n1. Kitap Ekle\n2. Kitap Listele\n3. Kitap Ara\n4. Kitap Sil\n5. Kitap Güncelle\n6. Çıkış\nSeçiminizi yapın: ";
        cin >> secim; cin.ignore();
        switch (secim) {
            case 1: kitapEkle(kitaplar, kitapSayisi); break;
            case 2: kitapListele(kitaplar, kitapSayisi); break;
            case 3: kitapAra(kitaplar, kitapSayisi); break;
            case 4: kitapSil(kitaplar, kitapSayisi); break;
            case 5: kitapGuncelle(kitaplar, kitapSayisi); break;
            case 6: dosyayaYaz(kitaplar, kitapSayisi); cout << "Programdan çikiliyor..." << endl; break;
            default: cout << "Geçersiz seçim, tekrar deneyin." << endl;
        }
    } while (secim != 6);
    return 0;
}
