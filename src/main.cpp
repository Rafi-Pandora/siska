#include <iostream>
#include <limits>
#include "core/railwayMLL.h"
using namespace std;

void pause() {
    cout << "\nTekan ENTER untuk lanjut...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void menuParent(RailwayMLL &rail) {
    int pilih, id, tipe;
    unsigned int tinggi;
    string kode, nama, kota;

    do {
        cout << "\n===== MENU STASIUN (PARENT) =====\n";
        cout << "1. Tambah Stasiun\n";
        cout << "2. Hapus Stasiun\n";
        cout << "3. Lihat Semua Stasiun\n";
        cout << "0. Kembali\n";
        cout << "Pilih: ";
        cin >> pilih;

        switch(pilih) {
            case 1:
                cout << "Petak ID: "; cin >> id;
                cout << "Kode Stasiun: "; cin >> kode;
                cout << "Nama Stasiun: "; cin >> nama;
                cout << "Kota: "; cin >> kota;
                cout << "Tipe Kelas: "; cin >> tipe;
                cout << "Tinggi Mdpl: "; cin >> tinggi;
                rail.insertParent(id, kode, nama, kota, tipe, tinggi);
                pause();
                break;

            case 2:
                cout << "Petak ID: "; cin >> id;
                rail.deleteParent(id);
                pause();
                break;

            case 3:
                rail.showAllParent();
                pause();
                break;
        }

    } while(pilih != 0);
}

void menuChild(RailwayMLL &rail) {
    int pilih, id;
    string nama, jenis;

    do {
        cout << "\n===== MENU KERETA (CHILD) =====\n";
        cout << "1. Tambah Kereta\n";
        cout << "2. Hapus Kereta\n";
        cout << "3. Lihat Semua Kereta\n";
        cout << "0. Kembali\n";
        cout << "Pilih: ";
        cin >> pilih;

        switch(pilih) {
            case 1:
                cout << "ID Kereta: "; cin >> id;
                cout << "Nama Kereta: "; cin >> nama;
                cout << "Jenis Layanan: "; cin >> jenis;
                rail.insertChild(id, nama, jenis);
                pause();
                break;

            case 2:
                cout << "ID Kereta: "; cin >> id;
                rail.deleteChild(id);
                pause();
                break;

            case 3:
                rail.showAllChild();
                pause();
                break;
        }

    } while (pilih != 0);
}

void menuRelasi(RailwayMLL &rail) {
    int pilih, petak, ka;
    string tiba, berangkat, info;

    do {
        cout << "\n===== MENU RELASI (PARENT <-> CHILD) =====\n";
        cout << "1. Tambah Relasi\n";
        cout << "2. Hapus Relasi\n";
        cout << "3. Lihat Semua Relasi KA\n";
        cout << "4. Lihat Semua KA di Stasiun\n";
        cout << "0. Kembali\n";
        cout << "Pilih: ";
        cin >> pilih;

        switch(pilih) {
            case 1:
                cout << "Petak Stasiun: "; cin >> petak;
                cout << "ID Kereta: "; cin >> ka;
                cout << "Waktu Tiba: "; cin >> tiba;
                cout << "Waktu Berangkat: "; cin >> berangkat;
                cout << "Info Relasi: "; cin >> info;
                rail.insertRelation(petak, ka, tiba, berangkat, info);
                pause();
                break;

            case 2:
                cout << "Petak Stasiun: "; cin >> petak;
                cout << "ID Kereta: "; cin >> ka;
                rail.deleteRelation(petak, ka);
                pause();
                break;

            case 3:
                cout << "ID Kereta: "; cin >> ka;
                rail.showRelasiFromKereta(ka);
                pause();
                break;

            case 4:
                cout << "Petak Stasiun: "; cin >> petak;
                rail.showChildFromParent(petak);
                pause();
                break;
        }

    } while (pilih != 0);
}

int main() {
    RailwayMLL rail;
    int pilih;

    do {
        cout << "\n=========================\n";
        cout << "  GUI MENU RAILWAY MLL\n";
        cout << "=========================\n";
        cout << "1. Menu Stasiun (Parent)\n";
        cout << "2. Menu Kereta (Child)\n";
        cout << "3. Menu Relasi\n";
        cout << "0. Exit\n";
        cout << "Pilih menu: ";
        cin >> pilih;

        switch(pilih) {
            case 1: menuParent(rail); break;
            case 2: menuChild(rail); break;
            case 3: menuRelasi(rail); break;
            case 0: cout << "Keluar...\n"; break;
            default: cout << "Pilihan tidak valid.\n"; pause();
        }

    } while(pilih != 0);

    return 0;
}
