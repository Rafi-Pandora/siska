#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include "core/railwayMLL.h"
#include "db/DatabaseManager.h"

using namespace std;

// ============================================================
// PRINT HELPER
// ============================================================

void printHelpStasiun() {
    cout << "\n=== HELP INPUT STASIUN ===\n";
    cout << "Petak        : 14\n";
    cout << "Kode Stasiun : CNP\n";
    cout << "Nama Stasiun : Cirebon Prujakan\n";
    cout << "Kota         : Cirebon\n";
    cout << "Tipe Kelas   : 1   (1=Besar, 2=Sedang, 3=Kecil)\n";
    cout << "Tinggi MDPL  : 31\n";
    cout << "--------------------------\n";
    cout << "Catatan:\n";
    cout << "- Kode Stasiun harus unik\n";
    cout << "- Nama & Kota boleh mengandung spasi\n";
}

void printHelpKereta() {
    cout << "\n=== HELP INPUT KERETA ===\n";
    cout << "No Kereta   : 21\n";
    cout << "Nama Kereta : KA Jakalana\n";
    cout << "Kelas       : ekonomi | bisnis | eksekutif\n";
    cout << "--------------------------\n";
    cout << "Catatan:\n";
    cout << "- No Kereta harus unik\n";
    cout << "- Penulisan kelas bebas (string)\n";
}

void printHelpRelasi() {
    cout << "\n=== HELP INPUT RELASI ===\n";
    cout << "Kode Stasiun    : JNG\n";
    cout << "No Kereta       : 103\n";
    cout << "Waktu Tiba      : 10:30\n";
    cout << "Waktu Berangkat : 10:45\n";
    cout << "Info            : Terminus | Berhenti | Susul\n";
    cout << "--------------------------\n";
    cout << "Catatan:\n";
    cout << "- Stasiun & Kereta harus sudah terdaftar\n";
    cout << "- Format waktu bebas (disarankan HH:MM)\n";
}


// =============================================================
// INPUT HELPERS 
// =============================================================
string inputString(const string& prompt) {
    string s;
    cout << prompt;
    getline(cin, s);
    return s;
}

int inputInt(const string& prompt) {
    string s;
    int value;
    while (true) {
        cout << prompt;
        getline(cin, s);
        try {
            value = stoi(s);
            return value;
        } catch (...) {
            cout << "Input harus berupa angka!\n";
        }
    }
}

void pause() {
    cout << "\nTekan ENTER untuk lanjut...";
    cin.get();
}

// =============================================================
// DISPLAY HELPER
// =============================================================
void displayVector(const vector<string>& data) {
    if (data.empty()) {
        cout << "Tidak ada data.\n";
        return;
    }
    for (const auto& s : data)
        cout << s << endl;
}

void persistentStorage(DatabaseManager* &db, RailwayMLL &rail) {
    int input;
    do
    {
        cout << "dengan menggunakan Persistent Storage kamu mengizinkan segala perubahan akan disimpan secara lokal dan akan memuat data dari penyimpanan lokal kamu\n1.setuju\n0.kembali" << endl;
        inputInt("");
        if (input == 1)
        {
            db = new DatabaseManager(string(DB_PATH));
            rail.setDatabase(db);
        }
    } while (input != 0);
    
    
}

// =============================================================
// SUB-MENU RELASI DISPLAY
// =============================================================
void menuRelasiDisplay(RailwayMLL &rail) {
    int pilih;
    do {
        cout << "\n===== SUB-MENU RELASI: TAMPILKAN =====\n";
        cout << "1. Tampilkan Semua Relasi\n";
        cout << "2. Tampilkan KA di Stasiun\n";
        cout << "3. Tampilkan Stasiun KA\n";
        cout << "0. Kembali\n";

        pilih = inputInt("Pilih: ");

        switch (pilih) {
            case 1:
                displayVector(rail.showAllRelations());
                pause();
                break;
            case 2: {
                string kode = inputString("Kode Stasiun: ");
                displayVector(rail.showChildFromParent(kode));
                pause();
                break;
            }
            case 3: {
                int ka = inputInt("No Kereta: ");
                displayVector(rail.showRelasiFromKereta(ka));
                pause();
                break;
            }
        }
    } while (pilih != 0);
}

// =============================================================
// SUB-MENU RELASI COUNT
// =============================================================
void menuRelasiCount(RailwayMLL &rail) {
    int pilih;
    do {
        cout << "\n===== SUB-MENU RELASI: HITUNG =====\n";
        cout << "1. Hitung KA di Stasiun\n";
        cout << "2. Hitung Stasiun KA\n";
        cout << "3. Stasiun tanpa Relasi\n";
        cout << "4. KA tanpa Relasi\n";
        cout << "0. Kembali\n";

        pilih = inputInt("Pilih: ");

        switch (pilih) {
            case 1: {
                string kode = inputString("Kode Stasiun (int): ");
                cout << rail.countChildOfParent(kode) << endl;
                pause();
                break;
            }
            case 2: {
                int ka = inputInt("No Kereta (int): ");
                cout << rail.countParentOfChild(ka) << endl;
                pause();
                break;
            }
            case 3: {
                auto r = rail.countParentTanpaChild();
                cout << "Total: " << r.first << endl;
                displayVector(r.second);
                pause();
                break;
            }
            case 4: {
                auto r = rail.countChildTanpaParent();
                cout << "Total: " << r.first << endl;
                displayVector(r.second);
                pause();
                break;
            }
        }
    } while (pilih != 0);
}

// =============================================================
// MENU STASIUN (PARENT)
// =============================================================
void menuParent(RailwayMLL &rail) {
    int pilih, petak, kelas, tinggi;
    string kode_stasiun, nama_stasiun, kota;
    do {
        cout << "\n===== MENU STASIUN =====\n";
        cout << "1. Tambah Stasiun\n";
        cout << "2. Hapus Stasiun\n";
        cout << "3. Lihat Semua Stasiun\n";
        cout << "4. Lihat Contoh Input Stasiun\n";
        cout << "0. Kembali\n";

        pilih = inputInt("Pilih: ");

        switch (pilih) {
            case 1: {
                nama_stasiun = inputString("Nama Stasiun (str): ");
                kode_stasiun = inputString("Kode Stasiun (str): ");
                kota = inputString("Kota (str): ");
                petak = inputInt("Petak (int): ");
                kelas = inputInt("Tipe Kelas (int): ");
                tinggi = inputInt("Tinggi MDPL (int): ");
                rail.insertParent(petak, kode_stasiun, nama_stasiun, kota, kelas, tinggi);
                pause();
                break;
            }
            case 2:
                rail.deleteParent(inputString("Kode Stasiun (str): "));
                pause();
                break;
            case 3:
                displayVector(rail.showAllParent());
                pause();
                break;
            case 4:
                printHelpStasiun();
                pause();
                break;
        }
    } while (pilih != 0);
}

// =============================================================
// MENU KERETA (CHILD)
// =============================================================
void menuChild(RailwayMLL &rail) {
    int pilih, no_kereta;
    string nama_kereta, kelas;
    do {
        cout << "\n===== MENU KERETA =====\n";
        cout << "1. Tambah Kereta\n";
        cout << "2. Hapus Kereta\n";
        cout << "3. Lihat Semua Kereta\n";
        cout << "3. Lihat Contoh Input Kereta\n";
        cout << "0. Kembali\n";

        pilih = inputInt("Pilih: ");

        switch (pilih) {
            case 1:
                no_kereta = inputInt("No Kereta (int): ");
                nama_kereta = inputString("Nama Kereta (str): ");
                kelas = inputString("Kelas (str): ");
                rail.insertChild(no_kereta, nama_kereta, kelas);
                pause();
                break;
            case 2:
                rail.deleteChild(inputInt("No Kereta (int): "));
                pause();
                break;
            case 3:
                displayVector(rail.showAllChild());
                pause();
                break;
            case 4:
                printHelpKereta();
                pause();
                break;
        }
    } while (pilih != 0);
}

// =============================================================
// MENU RELASI
// =============================================================
void menuRelasi(RailwayMLL &rail) {
    int pilih, no_kereta;
    string kode_stasiun, waktu_tiba, waktu_berangkat, info;
    do {
        cout << "\n===== MENU RELASI =====\n";
        cout << "1. Tambah Relasi\n";
        cout << "2. Hapus Relasi\n";
        cout << "3. Edit Relasi\n";
        cout << "4. Tampilkan Relasi\n";
        cout << "5. Hitung Relasi\n";
        cout << "6. Tampilkan Contoh Input Relasi\n";
        cout << "0. Kembali\n";

        pilih = inputInt("Pilih: ");

        switch (pilih) {
            case 1:
                kode_stasiun = inputString("Kode Stasiun (str): ");
                no_kereta = inputInt("No Kereta (int): ");
                waktu_tiba = inputString("Waktu Tiba (str): ");
                waktu_berangkat = inputString("Waktu Berangkat (str): ");
                info = inputString("Info (str): ");
                rail.insertRelation(kode_stasiun, no_kereta, waktu_tiba, waktu_berangkat, info);
                pause();
                break;
            case 2:
                rail.deleteRelation(
                    inputString("Kode Stasiun (str): "),
                    inputInt("No Kereta (int): ")
                );
                pause();
                break;
            case 3:
                kode_stasiun = inputString("Kode Stasiun (str): ");
                no_kereta = inputInt("No Kereta (int): ");
                waktu_tiba = inputString("Waktu Tiba Baru (str): ");
                waktu_berangkat = inputString("Waktu Berangkat Baru (str): ");
                rail.editRelation(kode_stasiun, no_kereta, waktu_tiba, waktu_berangkat);
                pause();
                break;
            case 4:
                menuRelasiDisplay(rail);
                break;
            case 5:
                menuRelasiCount(rail);
                break;
            case 6:
                printHelpRelasi();
                break;
        }
    } while (pilih != 0);
}

// =============================================================
// MAIN
// =============================================================
int main() {
    RailwayMLL rail;
    DatabaseManager db = nullptr;
    int pilih;

    do {
        cout << "\n===== MENU UTAMA =====\n";
        cout << "1. Menu Stasiun\n";
        cout << "2. Menu Kereta\n";
        cout << "3. Menu Relasi\n";
        cout << "4. Persistent Storage\n";
        cout << "0. Exit\n";

        pilih = inputInt("Pilih: ");

        switch (pilih) {
            case 1: menuParent(rail); break;
            case 2: menuChild(rail); break;
            case 3: menuRelasi(rail); break;
        }
    } while (pilih != 0);

    cout << "Keluar...\n";
    return 0;
}
