#ifndef RAILWAY_MLL_H
#define RAILWAY_MLL_H

#include <string>
using namespace std;

// ===========================
//   NODE DEFINITIONS
// ===========================
struct StationNode {
    int petak_stasiun;
    string kode_stasiun;
    string nama_stasiun;
    string kota;
    int tipe_kelas_stasiun;
    unsigned int tinggi_stasiun_mdpl;
    StationNode* next;
};

struct KeretaApiNode {
    int no_ka;
    string nama_kereta;
    string jenis_layanan;
    KeretaApiNode* next;
    KeretaApiNode* prev;
};

struct RelationNode {
    int petak_stasiun;
    int no_ka;
    string waktu_kedatangan;
    string waktu_keberangkatan;
    string info_relasi;
    RelationNode* next;
    RelationNode* prev;
};

// ===========================
//       CLASS MLL
// ===========================
class RailwayMLL {
public:
    // Pointers
    StationNode* head_stasiun;
    StationNode* tail_stasiun;

    KeretaApiNode* head_kereta;
    KeretaApiNode* tail_kereta;

    RelationNode* head_relasi;
    RelationNode* tail_relasi;

    RailwayMLL();
    ~RailwayMLL();

    RailwayMLL(const RailwayMLL&) = delete;
    RailwayMLL& operator=(const RailwayMLL&) = delete;

    // Helper
    StationNode* findStasiun(int petak_id);
    KeretaApiNode* findKereta(int ka_id);
    RelationNode* findRelasi(int petak_id, int ka_id);

    // Insert
    void insertParent(int id, const string& kode, const string& nama, const string& kota, int tipe, unsigned int tinggi);
    void insertChild(int id, const string& nama, const string& jenis);
    void insertRelation(int petak_id, int ka_id, const string& tiba, const string& berangkat, const string& info);

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
