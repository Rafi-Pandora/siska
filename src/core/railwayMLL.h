#ifndef RAILWAY_MLL_H
#define RAILWAY_MLL_H

#include <string>
using namespace std;

// ===========================
//   NODE DEFINITIONS
// ===========================

// ---------- PARENT (LEVEL 1) : STATION (SLL) ----------
struct StationNode {
    int petak_stasiun;
    string kode_stasiun;
    string nama_stasiun;
    string kota;
    int tipe_kelas_stasiun;
    unsigned int tinggi_stasiun_mdpl;

    StationNode* next;            // SLL
    struct RelationNode* relasi;  // pointer ke list relasi (LEVEL 2)
};


// ---------- CHILD (LEVEL 3) : KERETA API (DLL) ----------
struct KeretaApiNode {
    int no_ka;
    string nama_kereta;
    string jenis_layanan;

    KeretaApiNode* next;          // DLL
    KeretaApiNode* prev;          // DLL
    struct RelationNode* relasi;  // pointer ke list relasi KA ini (LEVEL 2)
};


// ---------- RELATION (LEVEL 2) : LINK STATION ↔ KERETA ----------
struct RelationNode {
    string waktu_kedatangan;
    string waktu_keberangkatan;
    string info_relasi;

    RelationNode* next;           // DLL
    RelationNode* prev;           // DLL

    StationNode* parentStation;   // pointer ke Parent
    KeretaApiNode* childKereta;   // pointer ke Child
};


// ===========================
//       CLASS MLL
// ===========================
class RailwayMLL {
public:

    // Head pointers for 3 lists
    StationNode* head_stasiun;  
    KeretaApiNode* head_kereta;

    RailwayMLL();
    ~RailwayMLL();

    RailwayMLL(const RailwayMLL&) = delete;
    RailwayMLL& operator=(const RailwayMLL&) = delete;

    // Find
    StationNode* findStasiun(int petak_id);
    KeretaApiNode* findKereta(int ka_id);

    // Insert
    void insertParent(int petak, const string& kode, const string& nama,
                      const string& kota, int tipe, unsigned int tinggi);

    void insertChild(int ka_id, const string& nama, const string& jenis);

    void insertRelation(int petak_id, int ka_id,
                        const string& tiba, const string& berangkat,
                        const string& info);

    // Delete
    void deleteParent(int petak_id);
    void deleteChild(int ka_id);
    void deleteRelation(int petak_id, int ka_id);

    // Display
    void showAllParent();
    void showAllChild();
    void showAllRelations();
    void showChildFromParent(int petak_id);
    void showRelasiFromKereta(int ka_id);
    void countChildOfParent(int petak_id);
};

#endif
