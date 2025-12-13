#include "railwayMLL.h"
#include <iostream>
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
void RailwayMLL::showAllParent() {
    cout << "\n=== DAFTAR STASIUN ===\n";

    StationNode* s = head_stasiun;
    while (s) {
        cout << s->petak_stasiun << " | " << s->nama_stasiun
             << " (" << s->kode_stasiun << ")\n";
        s = s->next;
    }
}

void RailwayMLL::showAllChild() {
    cout << "\n=== DAFTAR KERETA API ===\n";

    KeretaApiNode* k = head_kereta;
    while (k) {
        cout << k->no_ka << " | " << k->nama_kereta
             << " | " << k->kelas << endl;
        k = k->next;
    }
}

void RailwayMLL::showRelasiFromKereta(int ka_id) {
    KeretaApiNode* ka = findKereta(ka_id);
    if (!ka) { cout << "KA tidak ditemukan.\n"; return; }

    cout << "\n=== RELASI KA " << ka->nama_kereta << " ===\n";

    RelationNode* r = ka->relasi;
    while (r) {
        cout << "Stasiun: " << r->parentStation->nama_stasiun
             << " | Tiba: " << r->waktu_kedatangan
             << " | Brkt: " << r->waktu_keberangkatan
             << endl;
        r = r->next;
    }
}

void RailwayMLL::showChildFromParent(const string& kode_stasiun) {
    StationNode* st = findStasiun(kode_stasiun);
    if (!st) { cout << "Stasiun tidak ditemukan.\n"; return; }

    cout << "\n=== KA di stasiun " << st->nama_stasiun << " ===\n";

    RelationNode* r = st->relasi;
    while (r) {
        cout << "KA: " << r->childKereta->nama_kereta
             << " | Tiba: " << r->waktu_kedatangan
             << " | Brkt: " << r->waktu_keberangkatan
             << endl;
        r = r->next;
    }
}
