#include <iostream>
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