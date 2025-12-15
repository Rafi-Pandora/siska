#include <iostream>
#include <limits>
#include <string> 
#include "core/railwayMLL.h" 
using namespace std;

// =============================================================
// HELPER FUNCTIONS
// =============================================================
void pause() {
    cout << "\nTekan ENTER untuk lanjut...";
    // Membersihkan buffer sebelum menerima input baru
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void cleanInput() {
    // Fungsi untuk membersihkan buffer cin setelah cin >> variabel
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    } else {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void displayVector(const vector<string>& data) {
    if (data.empty()) {
        cout << "Tidak ada data untuk ditampilkan.\n";
        return;
    }
    for (const string& line : data) {
        cout << line << endl;
    }
}

// =============================================================
// SUB-MENU RELASI DISPLAY
// =============================================================
void menuRelasiDisplay(RailwayMLL &rail) {
    int pilih, ka;
    string kode;
    vector<string> result;

    do {
        // ... (Menu item sama) ...
        cout << "\n===== SUB-MENU RELASI: TAMPILKAN =====\n";
        cout << "1. Tampilkan Semua Relasi (Global)\n"; 
        cout << "2. Tampilkan KA di Stasiun Tertentu\n"; 
        cout << "3. Tampilkan Stasiun KA Tertentu\n"; 
        cout << "0. Kembali\n";
        cout << "Pilih: ";
        cin >> pilih;
        cleanInput();

        switch(pilih) {
            case 1:
                result = rail.showAllRelations();
                displayVector(result);
                pause();
                break;
            case 2:
                cout << "Kode Stasiun: "; cin >> kode;
                cleanInput();
                result = rail.showChildFromParent(kode);
                displayVector(result);
                pause();
                break;
            case 3:
                cout << "No Kereta: "; cin >> ka;
                cleanInput();
                result = rail.showRelasiFromKereta(ka);
                displayVector(result);
                pause();
                break;
        }
    } while (pilih != 0);
}

// =============================================================
// SUB-MENU RELASI COUNT
// =============================================================
void menuRelasiCount(RailwayMLL &rail) {
    int pilih, ka, count;
    string kode;
    pair<int, vector<string>> list_data;

    do {
        // ... (Menu item sama) ...
        cout << "\n===== SUB-MENU RELASI: HITUNG =====\n";
        cout << "1. Hitung KA di Stasiun Tertentu\n"; 
        cout << "2. Hitung Stasiun KA Tertentu\n"; 
        cout << "3. Hitung Stasiun Tanpa Relasi\n"; 
        cout << "4. Hitung KA Tanpa Relasi\n"; 
        cout << "0. Kembali\n";
        cout << "Pilih: ";
        cin >> pilih;
        cleanInput();

        switch(pilih) {
            case 1:
                cout << "Kode Stasiun: "; cin >> kode;
                cleanInput();
                count = rail.countChildOfParent(kode);
                if (count >= 0) {
                    cout << "Stasiun " << kode << " melayani " << count << " Kereta Api.\n";
                } else {
                    cout << "Stasiun tidak ditemukan.\n";
                }
                pause();
                break;
            case 2:
                cout << "No Kereta: "; cin >> ka;
                cleanInput();
                count = rail.countParentOfChild(ka);
                if (count >= 0) {
                    cout << "KA " << ka << " dilayani oleh " << count << " Stasiun.\n";
                } else {
                    cout << "KA tidak ditemukan.\n";
                }
                pause();
                break;
            case 3:
                list_data = rail.countParentTanpaChild();
                cout << "Total Stasiun tanpa relasi: " << list_data.first << endl;
                displayVector(list_data.second);
                pause();
                break;
            case 4:
                list_data = rail.countChildTanpaParent();
                cout << "Total Kereta Api tanpa relasi: " << list_data.first << endl;
                displayVector(list_data.second);
                pause();
                break;
        }
    } while (pilih != 0);
}

// =============================================================
// MAIN MENU PARENT (STASIUN)
// =============================================================
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
        cleanInput();

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
                displayVector(rail.showAllParent()); // MODIFIED
                pause();
                break;
        }

    } while(pilih != 0);
}

// =============================================================
// MAIN MENU CHILD (KERETA)
// =============================================================
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
        cleanInput();

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
                displayVector(rail.showAllChild()); // MODIFIED
                pause();
                break;
        }

    } while (pilih != 0);
}

// =============================================================
// MAIN MENU RELASI
// =============================================================
void menuRelasi(RailwayMLL &rail) {
    int pilih, ka;
    string tiba, berangkat, info, kode;
    RelationNode *r;

    do {
        cout << "\n===== MENU RELASI (PARENT <-> CHILD) =====\n";
        cout << "1. Tambah Relasi\n";
        cout << "2. Hapus Relasi\n";
        cout << "3. Edit Relasi\n";
        cout << "4. Cek Relasi (Find)\n";
        cout << "5. Menu Tampilkan Relasi\n"; 
        cout << "6. Menu Hitung Relasi\n";    
        cout << "0. Kembali\n";
        cout << "Pilih: ";
        cin >> pilih;
        cleanInput();

        switch(pilih) {
            case 1: // Insert Relation
                cout << "Kode Stasiun: "; cin >> kode;
                cout << "No Kereta: "; cin >> ka;
                cout << "Waktu Tiba: "; cin >> tiba;
                cout << "Waktu Berangkat: "; cin >> berangkat;
                cout << "Info Relasi: "; cin >> info;
                rail.insertRelation(kode, ka, tiba, berangkat, info);
                pause();
                break;

            case 2: // Delete Relation
                cout << "Kode Stasiun: "; cin >> kode;
                cout << "No Kereta: "; cin >> ka;
                rail.deleteRelation(kode, ka);
                pause();
                break;

            case 3: // Edit Relation
                cout << "Kode Stasiun: "; cin >> kode;
                cout << "No Kereta: "; cin >> ka;
                cout << "Waktu Tiba Baru: "; cin >> tiba;
                cout << "Waktu Berangkat Baru: "; cin >> berangkat;
                rail.editRelation(kode, ka, tiba, berangkat);
                pause();
                break;

            case 4: // Find Relasi
                cout << "Kode Stasiun: "; cin >> kode;
                cout << "No Kereta: "; cin >> ka;
                r = rail.findRelasi(kode, ka);
                if (!r) cout << "Relasi tidak ditemukan.\n";
                pause();
                break;

            case 5: // Display Sub-menu
                menuRelasiDisplay(rail);
                break;

            case 6: // Count Sub-menu
                menuRelasiCount(rail);
                break;
        }

    } while (pilih != 0);
}

// =============================================================
// MAIN PROGRAM
// =============================================================
int main() {
    RailwayMLL rail;
    int pilih;

    // Call cleanInput once here in case there's leftover input from environment
    cleanInput(); 

    do {
        cout << "\n=========================\n";
        cout << "   MENU RAILWAY MLL\n";
        cout << "=========================\n";
        cout << "1. Menu Stasiun (Parent)\n";
        cout << "2. Menu Kereta (Child)\n";
        cout << "3. Menu Relasi\n";
        cout << "0. Exit\n";
        cout << "Pilih menu: ";
        cin >> pilih;
        cleanInput();

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