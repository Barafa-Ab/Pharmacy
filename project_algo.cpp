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
void tampilMaju()
{
    if (listKosong())
    {
        cout << "List kosong!\n";
        return;
    }

    Obat *bantu = awal;
    cout << "\n======== DATA OBAT ========\n";
    while (bantu != NULL)
    {
        cout << "Kode    : " << bantu->kode << endl
             << "Nama    : " << bantu->nama << endl
             << "Jenis   : " << bantu->jenis << endl
             << "Harga   : Rp " << bantu->harga << endl
             << "Stok    : " << bantu->stok << endl
             << "--------------------------\n";
        bantu = bantu->next;
    }
}

void cariObat()
{
    if (listKosong())
    {
        cout << "Daftar obat kosong!\n";
        return;
    }

    int pilihan;
    cout << "\nCari berdasarkan:\n1. Kode\n2. Nama\n3. Jenis\nPilihan: ";
    cin >> pilihan;
    cin.ignore();

    string keyword;
    cout << "Masukkan kata kunci: ";
    getline(cin, keyword);
    transform(keyword.begin(), keyword.end(), keyword.begin(), ::tolower);

    Obat *current = awal;
    bool found = false;
    int count = 0;

    cout << "\n======== HASIL PENCARIAN ========\n";
    while (current != NULL)
    {
        string compareValue;
        switch (pilihan)
        {
        case 1:
            compareValue = current->kode;
            break;
        case 2:
            compareValue = current->nama;
            break;
        case 3:
            compareValue = current->jenis;
            break;
        default:
            cout << "Pilihan tidak valid!\n";
            return;
        }

        transform(compareValue.begin(), compareValue.end(), compareValue.begin(), ::tolower);
        if (compareValue.find(keyword) != string::npos)
        {
            count++;
            cout << "Obat ke-" << count << ":\n"
                 << "Kode    : " << current->kode << endl
                 << "Nama    : " << current->nama << endl
                 << "Jenis   : " << current->jenis << endl
                 << "Harga   : Rp " << current->harga << endl
                 << "Stok    : " << current->stok << endl
                 << "--------------------------\n";
            found = true;
        }
        current = current->next;
    }

    if (!found)
        cout << "Obat tidak ditemukan!\n";
    else
        cout << "Total ditemukan: " << count << " obat";
}
void sortObat()
{
    if (listKosong() || awal == akhir)
    {
        cout << "Tidak ada data untuk diurutkan!\n";
        return;
    }

    bool swapped;
    Obat *ptr1;
    Obat *lptr = NULL;

    do
    {
        swapped = false;
        ptr1 = awal;

        while (ptr1->next != lptr)
        {
            if (ptr1->kode > ptr1->next->kode)
            {
                swap(ptr1->kode, ptr1->next->kode);
                swap(ptr1->nama, ptr1->next->nama);
                swap(ptr1->jenis, ptr1->next->jenis);
                swap(ptr1->harga, ptr1->next->harga);
                swap(ptr1->stok, ptr1->next->stok);
                swapped = true;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);

    cout << "Data berhasil diurutkan berdasarkan kode!\n";
}

void hapusObat(const string &kode)
{
    if (listKosong())
    {
        cout << "List kosong!\n";
        return;
    }

    Obat *hapus = awal;
    while (hapus != NULL && hapus->kode != kode)
    {
        hapus = hapus->next;
    }

    if (hapus == NULL)
    {
        cout << "Obat dengan kode '" << kode << "' tidak ditemukan!\n";
        return;
    }

    char confirm;
    cout << "Anda akan menghapus obat:\n"
         << "Nama: " << hapus->nama << "\nKode: " << hapus->kode
         << "\nYakin? (y/n): ";
    cin >> confirm;

    if (tolower(confirm) != 'y')
    {
        cout << "Penghapusan dibatalkan!\n";
        return;
    }

    if (hapus == awal && hapus == akhir)
    {
        awal = akhir = NULL;
    }
    else if (hapus == awal)
    {
        awal = hapus->next;
        awal->prev = NULL;
    }
    else if (hapus == akhir)
    {
        akhir = hapus->prev;
        akhir->next = NULL;
    }
    else
    {
        hapus->prev->next = hapus->next;
        hapus->next->prev = hapus->prev;
    }

    delete hapus;
    cout << "Obat berhasil dihapus!\n";
}
void bersihkanMemori() {
    while (awal != NULL) {
        Obat *hapus = awal;
        awal = awal->next;
        delete hapus;
    }
    akhir = NULL;
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