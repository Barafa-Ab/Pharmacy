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

void bersihkanMemori()
{
    while (awal != NULL)
    {
        Obat *hapus = awal;
        awal = awal->next;
        delete hapus;
    }
    akhir = NULL;
}

void simpanKeFile()
{
    FILE *file = fopen("data_obat.txt", "w");
    if (file == NULL)
    {
        cout << "Error: Tidak dapat membuka file untuk menulis!\n";
        return;
    }

    Obat *current = awal;
    int count = 0;
    while (current != NULL)
    {
        fprintf(file, "%s,%s,%s,%.2f,%d\n",
                current->kode.c_str(),
                current->nama.c_str(),
                current->jenis.c_str(),
                current->harga,
                current->stok);
        current = current->next;
        count++;
    }
    fclose(file);
    cout << "Data berhasil disimpan ke file! (" << count << " obat)\n";
}
void muatDariFile()
{
    FILE *file = fopen("data_obat.txt", "r");
    if (file == NULL)
    {
        cout << "File masih kosong, masukkan data terlebih dahulu\n";
        return;
    }

    bersihkanMemori();

    char line[1000];
    while (fgets(line, sizeof(line), file))
    {
        line[strcspn(line, "\n")] = 0;

        stringstream ss(line);
        string kode, nama, jenis;
        double harga;
        int stok;

        getline(ss, kode, ',');
        getline(ss, nama, ',');
        getline(ss, jenis, ',');
        ss >> harga;
        ss.ignore();
        ss >> stok;

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
    }
    fclose(file);
}

int main()
{
    char pilihan, lagi;
    string kode, nama, jenis;
    double harga;
    int stok;
    muatDariFile();

    do
    {
        system("cls");
        cout << "\nSISTEM MANAJEMEN OBAT APOTEK\n";
        cout << "=====================================\n";
        cout << "1. Tambah Obat\n2. Tampilkan Semua Obat\n3. Cari Obat\n4. Hapus Obat\n5. Simpan ke File\n6. Keluar\n";
        cout << "=====================================\n";
        cout << "Pilih menu : ";
        cin >> pilihan;
        cin.ignore();

        switch (pilihan)
        {
        case '1':
        {
            system("cls");
            int n;
            cout << "Masukkan jumlah obat : ";
            cin >> n;
            cin.ignore();

            if (n <= 0)
            {
                cout << "Jumlah input tidak boleh <= 0\n";
                break;
            }

            for (int i = 0; i < n; i++)
            {
                cout << "\nObat ke-" << i + 1 << endl;
                while (true)
                {
                    cout << "Kode Obat  : ";
                    getline(cin, kode);
                    if (!cekKodeUnik(kode))
                    {
                        cout << "Error: Kode obat sudah digunakan. Masukkan kode lain.\n";
                    }
                    else
                        break;
                }
                cout << "Nama Obat  : ";
                getline(cin, nama);
                cout << "Jenis Obat : ";
                getline(cin, jenis);

                while (true)
                {
                    cout << "Harga : ";
                    cin >> harga;
                    cin.ignore();
                    if (harga <= 0)
                    {
                        cout << "Harga tidak boleh <= 0\n";
                        continue;
                    }
                    cout << "Stok  : ";
                    cin >> stok;
                    cin.ignore();
                    if (stok < 0)
                    {
                        cout << "Stok tidak boleh < 0\n";
                        continue;
                    }
                    break;
                }
                tambahObat(kode, nama, jenis, harga, stok);
            }
            break;
        }
        case '2':
            system("cls");
            sortObat();
            tampilMaju();
            break;
        case '3':
            system("cls");
            cariObat();
            break;
        case '4':
            system("cls");
            cout << "Masukkan kode obat yang akan dihapus: ";
            getline(cin, kode);
            hapusObat(kode);
            break;
        case '5':
            system("cls");
            simpanKeFile();
            break;
        case '6':
            system("cls");
            cout << "Menyimpan data sebelum keluar...\n";
            simpanKeFile();
            bersihkanMemori();
            cout << "Terima kasih telah menggunakan Sistem Manajemen Apotek!\n";
            break;
        default:
            system("cls");
            cout << "Pilihan tidak valid!\n";
        }
        cout << "Ingin pilih menu lagi?(y/n) : ";
        cin >> lagi;
        cin.ignore();
    } while (lagi == 'y' || lagi == 'Y');

    return 0;
}
