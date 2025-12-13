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
    string kelas;

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
    StationNode* findStasiun(const string& kode_stasiun);
    KeretaApiNode* findKereta(int no_ka);

    // Insert
    void insertParent(int petak, const string& kode, const string& nama,
                      const string& kota, int tipe, unsigned int tinggi);

    void insertChild(int no_ka, const string& nama, const string& kelas);

    void insertRelation(const string& kode_stasiun, int no_ka,
                        const string& tiba, const string& berangkat,
                        const string& info);

    // Delete
    void deleteParent(const string& kode_stasiun);
    void deleteChild(int no_ka);
    void deleteRelation(const string& kode_stasiun, int no_ka);

    // Display
    void showAllParent();
    void showAllChild();
    void showAllRelations();
    void showChildFromParent(const string& kode_stasiun);
    void showRelasiFromKereta(int no_ka);
    void countChildOfParent(const string& kode_stasiun);
};

#endif
