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
};

#endif