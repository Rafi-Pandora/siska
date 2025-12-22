#ifndef RAILWAY_MLL_H
#define RAILWAY_MLL_H

#include <string>
#include <vector>
#include <utility>
using namespace std;


//   NODE DEFINITIONS


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

class DatabaseManager;

//       CLASS MLL

class RailwayMLL {
public:

    StationNode* head_stasiun; 
    KeretaApiNode* head_kereta;
    DatabaseManager* db;

    /// @brief Constructor
    RailwayMLL();
    /// @brief Destructor, menghapus semua node (Parent, Child, dan Relasi).
    ~RailwayMLL();

    void setDatabase(DatabaseManager* dbMgr) { db = dbMgr; }

    // Pencegahan Copy Constructor dan Assignment Operator
    RailwayMLL(const RailwayMLL&) = delete;
    RailwayMLL& operator=(const RailwayMLL&) = delete;

    // ---------------------------------------------
    // FIND FUNCTIONS (Poin g, h, i)
    // ---------------------------------------------
    /**
     * @brief Mencari StationNode berdasarkan kode stasiun.
     * @param kode_stasiun Kode stasiun yang dicari.
     * @return StationNode* Pointer ke node jika ditemukan, nullptr jika tidak.
     */
    StationNode* findStasiun(const string& kode_stasiun);

    /**
     * @brief Mencari KeretaApiNode berdasarkan nomor KA.
     * @param no_ka Nomor KA yang dicari.
     * @return KeretaApiNode* Pointer ke node jika ditemukan, nullptr jika tidak.
     */
    KeretaApiNode* findKereta(int no_ka);

    /**
     * @brief Mencari RelationNode spesifik antara stasiun dan KA tertentu. (Poin i)
     * @param kode_stasiun Kode stasiun.
     * @param no_ka Nomor KA.
     * @return RelationNode* Pointer ke node relasi jika ditemukan, nullptr jika tidak.
     */
    RelationNode* findRelasi(const string& kode_stasiun, int no_ka);

    // ---------------------------------------------
    // INSERT FUNCTIONS (Poin a, b, c)
    // ---------------------------------------------
    /**
     * @brief Menambahkan StationNode baru ke List Parent. (Poin a)
     * @param petak Nomor petak stasiun.
     * @param kode Kode stasiun.
     * @param nama Nama stasiun.
     * @param kota Kota stasiun.
     * @param tipe Tipe kelas stasiun.
     * @param tinggi Tinggi stasiun MDPL.
     */
    void insertParent(int petak, const string& kode, const string& nama,
                      const string& kota, int tipe, unsigned int tinggi);

    /**
     * @brief Menambahkan KeretaApiNode baru ke List Child. (Poin b)
     * @param no_ka Nomor KA.
     * @param nama Nama KA.
     * @param kelas Kelas layanan KA.
     */
    void insertChild(int no_ka, const string& nama, const string& kelas);

    /**
     * @brief Menghubungkan Stasiun dan KA dengan RelationNode baru. (Poin c)
     * @param kode_stasiun Kode stasiun Parent.
     * @param no_ka Nomor KA Child.
     * @param tiba Waktu kedatangan.
     * @param berangkat Waktu keberangkatan.
     * @param info Info relasi tambahan.
     */
    void insertRelation(const string& kode_stasiun, int no_ka,
                        const string& tiba, 
                        const string& berangkat,
                        const string& info);
    
    // ---------------------------------------------
    // EDIT FUNCTION (Poin t)
    // ---------------------------------------------
    /**
     * @brief Mengedit waktu kedatangan dan keberangkatan pada RelationNode. (Poin t)
     * @param kode_stasiun Kode stasiun.
     * @param no_ka Nomor KA.
     * @param new_tiba Waktu kedatangan baru.
     * @param new_berangkat Waktu keberangkatan baru.
     */
    void editRelation(const string& kode_stasiun, int no_ka, 
                      const string& new_tiba, 
                      const string& new_berangkat);

    // ---------------------------------------------
    // DELETE FUNCTIONS (Poin d, e, f)
    // ---------------------------------------------
    /**
     * @brief Menghapus StationNode dan semua RelationNode yang terhubung. (Poin d)
     * @param kode_stasiun Kode stasiun yang akan dihapus.
     */
    void deleteParent(const string& kode_stasiun);

    /**
     * @brief Menghapus KeretaApiNode dan semua RelationNode yang terhubung. (Poin e)
     * @param no_ka Nomor KA yang akan dihapus.
     */
    void deleteChild(int no_ka);

    /**
     * @brief Menghapus RelationNode spesifik antara stasiun dan KA. (Poin f)
     * @param kode_stasiun Kode stasiun.
     * @param no_ka Nomor KA.
     */
    void deleteRelation(const string& kode_stasiun, int no_ka);

    // ---------------------------------------------
    // DISPLAY FUNCTIONS (Poin j, k, l, m, n, o)
    // ---------------------------------------------
    /// @brief Menampilkan semua data di List Parent (Stasiun). (Poin j)
    vector<string> showAllParent();

    /// @brief Menampilkan semua data di List Child (Kereta Api). (Poin k)
    vector<string> showAllChild();

    /// @brief Menampilkan semua data relasi yang ada (Per Stasiun).
    vector<string> showAllRelations();
    
    /**
     * @brief Menampilkan semua Stasiun yang dilayani oleh KA tertentu (Parent dari Child). (Poin m, n, o)
     * @param no_ka Nomor KA.
     */
    vector<string> showParentFromChild(int no_ka);

    /**
     * @brief Menampilkan semua KA yang singgah di Stasiun tertentu (Child dari Parent). (Poin l, n, o)
     * @param kode_stasiun Kode stasiun.
     */
    vector<string> showChildFromParent(const string& kode_stasiun);

    /**
     * @brief Menampilkan semua relasi (Stasiun) yang terhubung ke KA tertentu.
     * @param no_ka Nomor KA.
     */
    vector<string> showRelasiFromKereta(int no_ka);

    // ---------------------------------------------
    // COUNT FUNCTIONS (Poin p, q, r, s)
    // ---------------------------------------------
    /**
     * @brief Menghitung jumlah Stasiun (Parent) yang melayani KA (Child) tertentu. (Poin q)
     * @param no_ka Nomor KA.
     */
    int countParentOfChild(int no_ka);

    /**
     * @brief Menghitung jumlah KA (Child) yang dilayani oleh Stasiun (Parent) tertentu. (Poin p)
     * @param kode_stasiun Kode stasiun.
     */
    int countChildOfParent(const string& kode_stasiun);

    /// @brief Menghitung jumlah Stasiun (Parent) yang tidak melayani KA mana pun. (Poin s)
    pair<int, vector<string>> countParentTanpaChild();

    /// @brief Menghitung jumlah KA (Child) yang tidak terhubung ke Stasiun mana pun. (Poin r)
    pair<int, vector<string>> countChildTanpaParent();

    vector<string> showAllRelationsFromChild();

    void editRelationChangeChild(
        const string& kode_stasiun,
        int old_no_ka,
        int new_no_ka
    );

    void editRelationChangeParent(
        const string& old_kode_stasiun,
        const string& new_kode_stasiun,
        int no_ka
    );

};

#endif
