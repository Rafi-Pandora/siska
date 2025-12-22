#ifndef DATABASE_MANAGER_H
#define DATABASE_MANAGER_H

#include <sqlite3.h>
#include <string>
#include <vector>
#include "../core/railwayMLL.h" 

class DatabaseManager {
private:
    sqlite3* DB;
    
public:
    DatabaseManager(const char* file);
    ~DatabaseManager();

    // Fungsi Utama: Memuat semua data dari DB ke struktur MLL saat startup
    void loadDataToMLL(RailwayMLL &rail);

    // Fungsi Sinkronisasi (C dalam CRUD)
    void addStationDB(StationNode* s);
    void addKeretaDB(KeretaApiNode* k);
    void addRelasiDB(RelationNode* r);

    // Fungsi Penghapusan (D dalam CRUD)
    void deleteStationDB(std::string kode);
    void deleteKeretaDB(int no_ka);
    void deleteRelasiDB(std::string kode, int no_ka);

    // Fungsi Update (U dalam CRUD)
    void updateRelasiData(const string& kode_stasiun, int no_ka, const string& tiba, const string& berangkat);
    void updateRelasiChild(const string& kode_stasiun, int old_no_ka, int new_no_ka);
    void updateRelasiParent(const string& old_kode, const string& new_kode, int no_ka);
};

#endif