#include "railwayMLL.h"
#include <iostream>
#include <sstream> 
#include <iomanip> 
#include <vector>
#include <utility>
using namespace std;

// =============================================================
// Helper delete DLL (dipakai untuk hapus relasi KA atau Stasiun)
// =============================================================
void deleteRelationFromList(RelationNode*& head, RelationNode*& target) {
    if (!target) return;

    if (target->prev) target->prev->next = target->next;
    else head = target->next;

    if (target->next) target->next->prev = target->prev;

    delete target;
}

// =============================================================
// CONSTRUCTOR / DESTRUCTOR
// =============================================================
RailwayMLL::RailwayMLL() {
    head_stasiun = nullptr;
    head_kereta  = nullptr;
}

RailwayMLL::~RailwayMLL() {

    // DELETE ALL RELATIONS under each station
    StationNode* s = head_stasiun;
    while (s) {
        RelationNode* r = s->relasi;
        while (r) {
            RelationNode* next = r->next;
            delete r;
            r = next;
        }
        s = s->next;
    }

    // DELETE ALL CHILD
    KeretaApiNode* k = head_kereta;
    while (k) {
        KeretaApiNode* next = k->next;
        delete k;
        k = next;
    }

    // DELETE ALL PARENTS
    while (head_stasiun) {
        StationNode* next = head_stasiun->next;
        delete head_stasiun;
        head_stasiun = next;
    }
}

// =============================================================
// FIND FUNCTIONS
// =============================================================
StationNode* RailwayMLL::findStasiun(const string& kode_stasiun) {
    StationNode* cur = head_stasiun;
    while (cur) {
        if (cur->kode_stasiun == kode_stasiun)
            return cur;
        cur = cur->next;
    }
    return nullptr;
}

KeretaApiNode* RailwayMLL::findKereta(int no_ka) {
    KeretaApiNode* cur = head_kereta;
    while (cur) {
        if (cur->no_ka == no_ka)
            return cur;
        cur = cur->next;
    }
    return nullptr;
}

RelationNode* RailwayMLL::findRelasi(const string& kode_stasiun, int no_ka) {
    StationNode* st = findStasiun(kode_stasiun);
    KeretaApiNode* ka = findKereta(no_ka);

    if (!st || !ka) return nullptr;

    RelationNode* r = st->relasi;

    while (r) {
        if (r->parentStation == st && r->childKereta == ka) {
            cout << "Relasi Stasiun " << st->nama_stasiun 
                 << " dan KA " << ka->nama_kereta << " DITEMUKAN.\n";
            return r;
        }
        r = r->next;
    }

    return nullptr;
}

// =============================================================
// INSERT PARENT
// =============================================================
void RailwayMLL::insertParent(int petak, const string& kode,
        const string& nama, const string& kota, int tipe, unsigned int tinggi) {

    if (findStasiun(kode)) {
        cout << "Stasiun sudah ada!\n";
        return;
    }

    StationNode* node = new StationNode{
        petak, kode, nama, kota, tipe, tinggi,
        nullptr,
        nullptr   // <--- pointer relasi
    };

    if (!head_stasiun) head_stasiun = node;
    else {
        StationNode* last = head_stasiun;
        while (last->next) last = last->next;
        last->next = node;
    }

    cout << "Stasiun ditambahkan.\n";
}

// =============================================================
// INSERT CHILD
// =============================================================
void RailwayMLL::insertChild(int no_ka, const string& nama, const string& kelas) {
    if (findKereta(no_ka)) {
        cout << "Kereta sudah ada!\n";
        return;
    }

    KeretaApiNode* node = new KeretaApiNode{
        no_ka, nama, kelas,
        nullptr, nullptr,
        nullptr // <--- child relasi list
    };

    if (!head_kereta) {
        head_kereta = node;
    } else {
        KeretaApiNode* tail = head_kereta;
        while (tail->next) tail = tail->next;
        tail->next = node;
        node->prev = tail;
    }

    cout << "Kereta ditambahkan.\n";
}

// =============================================================
// INSERT RELATION (Parent ↔ Child connection)
// =============================================================
void RailwayMLL::insertRelation(const string& kode_stasiun, int no_ka,
        const string& tiba, const string& berangkat, const string& info) {

    StationNode* st = findStasiun(kode_stasiun);
    KeretaApiNode* ka = findKereta(no_ka);

    if (!st || !ka) {
        cout << "Error: stasiun atau KA tidak ditemukan.\n";
        return;
    }

    // Membuat node relasi
    RelationNode* node = new RelationNode{
        tiba, berangkat, info,
        st->relasi, nullptr, // next, prev
        st, ka               // parent & child pointer
    };

    if (st->relasi)
        st->relasi->prev = node;

    st->relasi = node;

    // Tambahkan node ke list relasi milik KA
    node->next = ka->relasi;
    if (ka->relasi) ka->relasi->prev = node;
    ka->relasi = node;

    cout << "Relasi berhasil ditambahkan.\n";
}

// =============================================================
// DELETE RELATION
// =============================================================
void RailwayMLL::deleteRelation(const string& kode_stasiun, int no_ka) {
    StationNode* st = findStasiun(kode_stasiun);
    KeretaApiNode* ka = findKereta(no_ka);

    if (!st || !ka) {
        cout << "Stasiun/KA tidak ditemukan.\n";
        return;
    }

    RelationNode* r = st->relasi;

    while (r) {
        if (r->parentStation == st && r->childKereta == ka) {

            // Hapus dari parent
            if (r->prev) r->prev->next = r->next;
            else st->relasi = r->next;

            if (r->next) r->next->prev = r->prev;

            delete r;
            cout << "Relasi dihapus.\n";
            return;
        }
        r = r->next;
    }

    cout << "Relasi tidak ditemukan.\n";
}

// =============================================================
// DELETE CHILD
// =============================================================
void RailwayMLL::deleteChild(int ka_id) {
    KeretaApiNode* target = findKereta(ka_id);
    if (!target) {
        cout << "KA tidak ditemukan.\n";
        return;
    }

    // 1. Hapus semua RELATION yang terhubung ke KA ini
    RelationNode* r = target->relasi;
    while (r) {
        RelationNode* next = r->next;

        StationNode* st = r->parentStation;

        // Lepas node relasi dari parent station
        if (r->prev) r->prev->next = r->next;
        else st->relasi = r->next;

        if (r->next) r->next->prev = r->prev;

        // Lepas dari child list (KA)
        if (r->next && r->next->parentStation == st)
            r->next->prev = r->prev;

        delete r;

        r = next;
    }

    // 2. Hapus KA dari DLL child list
    if (target->prev)
        target->prev->next = target->next;
    else
        head_kereta = target->next;

    if (target->next)
        target->next->prev = target->prev;

    delete target;

    cout << "Kereta beserta seluruh relasinya telah dihapus.\n";
}

// =============================================================
// EDIT RELATION (Poin t)
// =============================================================
void RailwayMLL::editRelation(const string& kode_stasiun, int no_ka, 
                             const string& new_tiba, const string& new_berangkat) {
    
    RelationNode* r = findRelasi(kode_stasiun, no_ka);

    if (!r) {
        cout << "Error: Relasi tidak ditemukan. Gagal mengedit.\n";
        return;
    }

    // Lakukan perubahan data
    r->waktu_kedatangan = new_tiba;
    r->waktu_keberangkatan = new_berangkat;

    cout << "Relasi berhasil diubah:\n";
    cout << "  Stasiun: " << r->parentStation->nama_stasiun << endl;
    cout << "  KA: " << r->childKereta->nama_kereta << endl;
    cout << "  Waktu Tiba Baru: " << r->waktu_kedatangan << endl;
    cout << "  Waktu Berangkat Baru: " << r->waktu_keberangkatan << endl;
}

// =============================================================
// DELETE PARENT
// =============================================================
void RailwayMLL::deleteParent(const string& kode_stasiun) {
    StationNode* st = findStasiun(kode_stasiun);
    if (!st) { cout << "Stasiun tidak ditemukan.\n"; return; }

    // Hapus seluruh relasi station ini
    RelationNode* r = st->relasi;
    while (r) {
        RelationNode* next = r->next;
        delete r;
        r = next;
    }

    // Remove parent from list
    if (head_stasiun == st) {
        head_stasiun = st->next;
    } else {
        StationNode* cur = head_stasiun;
        while (cur->next != st) cur = cur->next;
        cur->next = st->next;
    }

    delete st;
    cout << "Stasiun dan semua relasinya dihapus.\n";
}

// =============================================================
// DISPLAY FUNCTIONS
// =============================================================
vector<string> RailwayMLL::showAllParent() {
    vector<string> result;
    StationNode* s = head_stasiun;
    
    // Tambahkan header
    stringstream header;
    header << "PETAK | KODE | NAMA STASIUN | KOTA";
    result.push_back(header.str());

    while (s) {
        stringstream ss;
        ss << s->petak_stasiun << " | " 
           << s->kode_stasiun << " | " 
           << s->nama_stasiun << " | " 
           << s->kota;
        result.push_back(ss.str());
        s = s->next;
    }
    return result;
}

vector<string> RailwayMLL::showAllChild() {
    vector<string> result;
    KeretaApiNode* k = head_kereta;
    
    stringstream header;
    header << "NO KA | NAMA KERETA | KELAS";
    result.push_back(header.str());

    while (k) {
        stringstream ss;
        ss << k->no_ka << " | " 
           << k->nama_kereta << " | " 
           << k->kelas;
        result.push_back(ss.str());
        k = k->next;
    }
    return result;
}

vector<string> RailwayMLL::showAllRelations() {
    vector<string> result;
    StationNode* s = head_stasiun;
    
    result.push_back("--- DAFTAR SEMUA RELASI JALAN (Per Stasiun) ---");

    while (s) {
        RelationNode* r = s->relasi;
        if (r) {
            result.push_back("--- Stasiun: " + s->nama_stasiun + " (" + s->kode_stasiun + ") ---");
            while (r) {
                stringstream ss;
                ss << "  KA " << r->childKereta->nama_kereta 
                   << " | Tiba: " << r->waktu_kedatangan
                   << " | Brkt: " << r->waktu_keberangkatan
                   << " | Info: " << r->info_relasi;
                result.push_back(ss.str());
                r = r->next;
            }
        }
        s = s->next;
    }
    if (result.size() == 1) { // Hanya ada header awal
        result.push_back("Tidak ada relasi yang tercatat.");
    }
    return result;
}

vector<string> RailwayMLL::showChildFromParent(const string& kode_stasiun) {
    vector<string> result;
    StationNode* st = findStasiun(kode_stasiun);
    if (!st) { 
        result.push_back("Stasiun tidak ditemukan."); 
        return result; 
    }

    result.push_back("=== KA di stasiun " + st->nama_stasiun + " ===");

    RelationNode* r = st->relasi;
    while (r) {
        stringstream ss;
        ss << "KA: " << r->childKereta->nama_kereta
           << " | Tiba: " << r->waktu_kedatangan
           << " | Brkt: " << r->waktu_keberangkatan;
        result.push_back(ss.str());
        r = r->next;
    }
    if (r == st->relasi) { // List is empty
        result.push_back("Stasiun ini tidak melayani KA.");
    }
    return result;
}

vector<string> RailwayMLL::showParentFromChild(int no_ka) {
    // Logika sama dengan showRelasiFromKereta
    return showRelasiFromKereta(no_ka);
}

vector<string> RailwayMLL::showRelasiFromKereta(int no_ka) {
    vector<string> result;
    KeretaApiNode* ka = findKereta(no_ka);
    if (!ka) { 
        result.push_back("KA tidak ditemukan."); 
        return result; 
    }

    result.push_back("=== Stasiun yang dilayani KA " + ka->nama_kereta + " ===");

    RelationNode* r = ka->relasi;
    if (!r) {
        result.push_back("KA ini belum melayani stasiun manapun.");
        return result;
    }

    while (r) {
        stringstream ss;
        ss << "Stasiun: " << r->parentStation->nama_stasiun
           << " | Tiba: " << r->waktu_kedatangan
           << " | Brkt: " << r->waktu_keberangkatan
           << " | Info: " << r->info_relasi;
        result.push_back(ss.str());
        r = r->next;
    }
    return result;
}

// =============================================================
// COUNT
// =============================================================
int RailwayMLL::countChildOfParent(const string& kode_stasiun) {
    StationNode* st = findStasiun(kode_stasiun);
    if (!st) return -1; // Mengembalikan -1 jika stasiun tidak ditemukan

    int count = 0;
    RelationNode* r = st->relasi;
    while (r) {
        count++;
        r = r->next;
    }
    return count;
}

int RailwayMLL::countParentOfChild(int no_ka) {
    KeretaApiNode* ka = findKereta(no_ka);
    if (!ka) return -1; // Mengembalikan -1 jika KA tidak ditemukan

    int count = 0;
    RelationNode* r = ka->relasi;
    while (r) {
        count++;
        r = r->next;
    }
    return count;
}

pair<int, vector<string>> RailwayMLL::countChildTanpaParent() {
    int count = 0;
    vector<string> list_ka;
    KeretaApiNode* k = head_kereta;

    while (k) {
        if (!k->relasi) {
            stringstream ss;
            ss << k->no_ka << " | " << k->nama_kereta;
            list_ka.push_back(ss.str());
            count++;
        }
        k = k->next;
    }
    return make_pair(count, list_ka);
}

pair<int, vector<string>> RailwayMLL::countParentTanpaChild() {
    int count = 0;
    vector<string> list_stasiun;
    StationNode* s = head_stasiun;

    while (s) {
        if (!s->relasi) {
            stringstream ss;
            ss << s->petak_stasiun << " | " << s->nama_stasiun;
            list_stasiun.push_back(ss.str());
            count++;
        }
        s = s->next;
    }
    return make_pair(count, list_stasiun);
}