#include "railwayMLL.h"
#include <iostream>

using namespace std;

//<---HELPER DELETE DLL--->
void deleteDLLNode(RelationNode*& head, RelationNode*& tail, RelationNode* target) {
    if (!target) return;

    if (target->prev) target->prev->next = target->next;
    else head = target->next;

    if (target->next) target->next->prev = target->prev;
    else tail = target->prev;

    delete target;
}

//<---CONSTRUCTOR & DESTRUCTOR--->
RailwayMLL::RailwayMLL() {
    head_stasiun = tail_stasiun = nullptr;
    head_kereta = tail_kereta = nullptr;
    head_relasi = tail_relasi = nullptr;
}

RailwayMLL::~RailwayMLL() {
    // delete all relations
    RelationNode* r = head_relasi;
    while (r) {
        RelationNode* next = r->next;
        delete r;
        r = next;
    }

    // delete all kereta
    KeretaApiNode* k = head_kereta;
    while (k) {
        KeretaApiNode* next = k->next;
        delete k;
        k = next;
    }

    // delete all stasiun
    StationNode* s = head_stasiun;
    while (s) {
        StationNode* next = s->next;
        delete s;
        s = next;
    }
}

//<---FIND--->
StationNode* RailwayMLL::findStasiun(int petak_id) {
    StationNode* cur = head_stasiun;
    while (cur) {
        if (cur->petak_stasiun == petak_id) return cur;
        cur = cur->next;
    }
    return nullptr;
}

KeretaApiNode* RailwayMLL::findKereta(int ka_id) {
    KeretaApiNode* cur = head_kereta;
    while (cur) {
        if (cur->no_ka == ka_id) return cur;
        cur = cur->next;
    }
    return nullptr;
}

RelationNode* RailwayMLL::findRelasi(int petak_id, int ka_id) {
    RelationNode* cur = head_relasi;
    while (cur) {
        if (cur->petak_stasiun == petak_id && cur->no_ka == ka_id) return cur;
        cur = cur->next;
    }
    return nullptr;
}

//<---INSERT--->
void RailwayMLL::insertParent(int id, const string& kode, const string& nama, const string& kota, int tipe, unsigned int tinggi) {
    if (findStasiun(id)) {
        cout << "Error: Stasiun dengan ID tersebut sudah ada.\n";
        return;
    }
    StationNode* node = new StationNode{id, kode, nama, kota, tipe, tinggi, nullptr};
    if (!head_stasiun) head_stasiun = tail_stasiun = node;
    else { tail_stasiun->next = node; tail_stasiun = node; }
    cout << "Stasiun berhasil ditambahkan.\n";
}

void RailwayMLL::insertChild(int id, const string& nama, const string& jenis) {
    if (findKereta(id)) {
        cout << "Error: Kereta sudah ada.\n";
        return;
    }
    KeretaApiNode* node = new KeretaApiNode{id, nama, jenis, nullptr, nullptr};
    if (!head_kereta) head_kereta = tail_kereta = node;
    else {
        node->prev = tail_kereta;
        tail_kereta->next = node;
        tail_kereta = node;
    }
    cout << "Kereta berhasil ditambahkan.\n";
}

void RailwayMLL::insertRelation(int petak_id, int ka_id, const string& tiba, const string& berangkat, const string& info) {
    if (!findStasiun(petak_id) || !findKereta(ka_id)) {
        cout << "Error: Stasiun atau Kereta tidak ditemukan.\n";
        return;
    }
    if (findRelasi(petak_id, ka_id)) {
        cout << "Relasi sudah ada.\n";
        return;
    }

    RelationNode* node = new RelationNode{petak_id, ka_id, tiba, berangkat, info, nullptr, nullptr};
    if (!head_relasi) head_relasi = tail_relasi = node;
    else {
        node->prev = tail_relasi;
        tail_relasi->next = node;
        tail_relasi = node;
    }

    cout << "Relasi berhasil ditambahkan.\n";
}

//<---DELETE--->
void RailwayMLL::deleteRelation(int petak_id, int ka_id) {
    RelationNode* target = findRelasi(petak_id, ka_id);
    if (!target) { cout << "Relasi tidak ditemukan.\n"; return; }

    deleteDLLNode(head_relasi, tail_relasi, target);
    cout << "Relasi dihapus.\n";
}

void RailwayMLL::deleteChild(int ka_id) {
    KeretaApiNode* target = findKereta(ka_id);
    if (!target) { cout << "Kereta tidak ditemukan.\n"; return; }

    // delete all relations
    RelationNode* cur = head_relasi;
    while (cur) {
        RelationNode* next = cur->next;
        if (cur->no_ka == ka_id) deleteDLLNode(head_relasi, tail_relasi, cur);
        cur = next;
    }

    // delete kereta node
    if (target->prev) target->prev->next = target->next;
    else head_kereta = target->next;

    if (target->next) target->next->prev = target->prev;
    else tail_kereta = target->prev;

    delete target;
    cout << "Kereta dan semua relasinya dihapus.\n";
}

void RailwayMLL::deleteParent(int petak_id) {
    StationNode* cur = head_stasiun;
    StationNode* prev = nullptr;

    while (cur && cur->petak_stasiun != petak_id) {
        prev = cur;
        cur = cur->next;
    }

    if (!cur) { cout << "Stasiun tidak ditemukan.\n"; return; }

    // delete relation linked to station
    RelationNode* r = head_relasi;
    while (r) {
        RelationNode* next = r->next;
        if (r->petak_stasiun == petak_id) deleteDLLNode(head_relasi, tail_relasi, r);
        r = next;
    }

    // delete station
    if (prev) prev->next = cur->next;
    else head_stasiun = cur->next;

    if (cur == tail_stasiun) tail_stasiun = prev;

    delete cur;
    cout << "Stasiun dan relasinya dihapus.\n";
}

//<---DISPLAY--->
void RailwayMLL::showAllParent() {
    cout << "\n=== LIST STASIUN ===\n";
    StationNode* s = head_stasiun;
    if (!s) { cout << "Kosong.\n"; return; }
    while (s) {
        cout << s->petak_stasiun << " | " << s->nama_stasiun << " | Kode: " << s->kode_stasiun << endl;
        s = s->next;
    }
}

void RailwayMLL::showAllChild() {
    cout << "\n=== LIST KERETA API ===\n";
    KeretaApiNode* k = head_kereta;
    if (!k) { cout << "Kosong.\n"; return; }
    while (k) {
        cout << k->no_ka << " | " << k->nama_kereta << " | " << k->jenis_layanan << endl;
        k = k->next;
    }
}

void RailwayMLL::showAllRelations() {
    cout << "\n=== LIST RELASI ===\n";
    RelationNode* r = head_relasi;
    if (!r) { cout << "Kosong.\n"; return; }

    while (r) {
        cout << "Stasiun: " << r->petak_stasiun
             << " <--> KA " << r->no_ka
             << " | Tiba: " << r->waktu_kedatangan
             << " | Brkt: " << r->waktu_keberangkatan
             << endl;
        r = r->next;
    }
}

void RailwayMLL::showChildFromParent(int petak_id) {
    StationNode* st = findStasiun(petak_id);
    if (!st) { cout << "Stasiun tidak ditemukan.\n"; return; }

    cout << "\n=== Kereta yang singgah di " << st->nama_stasiun << " ===\n";

    RelationNode* r = head_relasi;
    bool found = false;

    while (r) {
        if (r->petak_stasiun == petak_id) {
            KeretaApiNode* k = findKereta(r->no_ka);
            if (k) {
                cout << k->no_ka << " - " << k->nama_kereta
                     << " | Tiba: " << r->waktu_kedatangan
                     << " | Brkt: " << r->waktu_keberangkatan << endl;
                found = true;
            }
        }
        r = r->next;
    }
}

void RailwayMLL::showRelasiFromKereta(int ka_id) {
    KeretaApiNode* ka = findKereta(ka_id);
    if (!ka) {
        cout << "Kereta tidak ditemukan.\n";
        return;
    }

    cout << "\n=== Relasi untuk Kereta " << ka->nama_kereta << " (KA " << ka->no_ka << ") ===\n";

    RelationNode* r = head_relasi;
    bool found = false;

    while (r) {
        if (r->no_ka == ka_id) {
            StationNode* s = findStasiun(r->petak_stasiun);
            if (s) {
                cout << "Stasiun " << s->nama_stasiun
                     << " | Tiba: " << r->waktu_kedatangan
                     << " | Brkt: " << r->waktu_keberangkatan
                     << " | Info: " << r->info_relasi
                     << endl;
                found = true;
            }
        }
        r = r->next;
    }

    if (!found) {
        cout << "Tidak ada relasi untuk kereta ini.\n";
    }
}

void RailwayMLL::countChildOfParent(int petak_id) {
    StationNode* s = findStasiun(petak_id);
    if (!s) {
        cout << "Stasiun tidak ditemukan.\n";
        return;
    }

    int count = 0;
    RelationNode* r = head_relasi;

    while (r) {
        if (r->petak_stasiun == petak_id) {
            count++;
        }
        r = r->next;
    }

    cout << "Total kereta yang singgah di " << s->nama_stasiun << ": " << count << endl;
}