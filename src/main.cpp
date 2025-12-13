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
    int pilih, petak, tipe;
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
                cout << "Petak: "; cin >>petak;
                cout << "Kode Stasiun: "; cin >> kode;
                cout << "Nama Stasiun: "; cin >> nama;
                cout << "Kota: "; cin >> kota;
                cout << "Tipe Kelas: "; cin >> tipe;
                cout << "Tinggi Mdpl: "; cin >> tinggi;
                rail.insertParent(petak, kode, nama, kota, tipe, tinggi);
                pause();
                break;

            case 2:
                cout << "Kode Stasiun: "; cin >>kode;
                rail.deleteParent(kode);
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
    int pilih, no_ka;
    string nama, kelas;

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
                cout << "No Kereta: "; cin >> no_ka;
                cout << "Nama Kereta: "; cin >> nama;
                cout << "kelas: "; cin >> kelas;
                rail.insertChild(no_ka, nama, kelas);
                pause();
                break;

            case 2:
                cout << "No Kereta: "; cin >> no_ka;
                rail.deleteChild(no_ka);
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
    int pilih, ka;
    string tiba, berangkat, info, kode;

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
                cout << "Kode Stasiun: "; cin >> kode;
                cout << "No Kereta: "; cin >> ka;
                cout << "Waktu Tiba: "; cin >> tiba;
                cout << "Waktu Berangkat: "; cin >> berangkat;
                cout << "Info Relasi: "; cin >> info;
                rail.insertRelation(kode, ka, tiba, berangkat, info);
                pause();
                break;

            case 2:
                cout << "Kode Stasiun: "; cin >> kode;
                cout << "No Kereta: "; cin >> ka;
                rail.deleteRelation(kode, ka);
                pause();
                break;

            case 3:
                cout << "No Kereta: "; cin >> ka;
                rail.showRelasiFromKereta(ka);
                pause();
                break;

            case 4:
                cout << "Kode Stasiun: "; cin >> kode;
                rail.showChildFromParent(kode);
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
        cout << "  MENU RAILWAY MLL\n";
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
