#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <cstdio>
using namespace std;

struct Obat
{
    string kode, nama, jenis;
    double harga;
    int stok;
    Obat *next;
    Obat *prev;
};

Obat *awal = NULL, *akhir = NULL;

bool cekKodeUnik(const string &kode)
{
    Obat *current = awal;
    while (current != NULL)
    {
        if (current->kode == kode)
            return false;
        current = current->next;
    }
    return true;
}
void buatListBaru()
{
    awal = akhir = NULL;
}

bool listKosong()
{
    return awal == NULL;
}

void tambahObat(const string &kode, const string &nama, const string &jenis, double harga, int stok)
{
    if (!cekKodeUnik(kode))
    {
        cout << "Error: Kode obat '" << kode << "' sudah ada!\n";
        return;
    }

    Obat *baru = new Obat{kode, nama, jenis, harga, stok, NULL, NULL};

    if (listKosong())
    {
        awal = akhir = baru;
    }
    else
    {
        akhir->next = baru;
        baru->prev = akhir;
        akhir = baru;
    }

    cout << "Obat " << nama << "' berhasil ditambahkan.\n";
}
void tampilMaju() {
    if (listKosong()) {
        cout << "List kosong!\n";
        return;
    }

    Obat *bantu = awal;
    cout << "\n======== DATA OBAT ========\n";
    while (bantu != NULL) {
        cout << "Kode    : " << bantu->kode << endl
             << "Nama    : " << bantu->nama << endl
             << "Jenis   : " << bantu->jenis << endl
             << "Harga   : Rp " << bantu->harga << endl
             << "Stok    : " << bantu->stok << endl
             << "--------------------------\n";
        bantu = bantu->next;
    }
}

int main()
{
    char pilihan, lagi;
    string kode, nama, jenis;
    double harga;
    int stok;

    do
    {
        system("cls");
        cout << "\nSISTEM MANAJEMEN OBAT APOTEK" << endl;
        cout << "=====================================" << endl;
        cout << "1. Tambah Obat\n2. Tampilkan Semua Obat\n3. Cari Obat\n4. Hapus Obat\n5. Simpan ke File\n6. Keluar" << endl;
        cout << "=====================================" << endl;

        cout << "Pilih menu : ";
        cin >> pilihan;
        cin.ignore();

        switch (pilihan)
        {
        case '1':
            break;
        case '2':
            break;
        case '3':
            break;
        case '4':
            break;
        case '5':
            break;
        case '6':
            break;
        default:
            system("cls");
            cout << "Pilihan tidak valid! Silakan pilih 1-8.\n";
            break;
        }

        cout << "Ingin pilih menu lagi?(y/n) : ";
        cin >> lagi;
        cin.ignore();

    } while (lagi == 'y' || lagi == 'Y');

    return 0;
}