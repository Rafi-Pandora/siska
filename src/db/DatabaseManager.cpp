#include "DatabaseManager.h"
#include <iostream>

DatabaseManager::DatabaseManager(const char* file) {
    int exit = sqlite3_open(file, &DB);
    if (exit != SQLITE_OK) {
        std::cerr << "Error open DB: " << sqlite3_errmsg(DB) << std::endl;
    } else {
        std::cout << "[DB] Koneksi database berhasil dibuka." << std::endl;
    }
}

DatabaseManager::~DatabaseManager() {
    sqlite3_close(DB);
    std::cout << "[DB] Koneksi database ditutup." << std::endl;
}

// =============================================================
// FUNGSI LOAD (Membangun Ulang MLL dari Database)
// =============================================================
void DatabaseManager::loadDataToMLL(RailwayMLL &rail) {
    sqlite3_stmt* stmt;

    // Load Stasiun (Parent)
    std::string sqlS = "SELECT * FROM stasiun;";
    if (sqlite3_prepare_v2(DB, sqlS.c_str(), -1, &stmt, NULL) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            rail.insertParent(
                sqlite3_column_int(stmt, 1),        // petak
                (const char*)sqlite3_column_text(stmt, 0), // kode
                (const char*)sqlite3_column_text(stmt, 2), // nama
                (const char*)sqlite3_column_text(stmt, 3), // kota
                sqlite3_column_int(stmt, 4),        // tipe
                sqlite3_column_int(stmt, 5)         // tinggi
            );
        }
    }
    sqlite3_finalize(stmt);

    // Load Kereta Api (Child)
    std::string sqlK = "SELECT * FROM kereta_api;";
    if (sqlite3_prepare_v2(DB, sqlK.c_str(), -1, &stmt, NULL) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            rail.insertChild(
                sqlite3_column_int(stmt, 0),        // no_ka
                (const char*)sqlite3_column_text(stmt, 1), // nama
                (const char*)sqlite3_column_text(stmt, 2)  // kelas
            );
        }
    }
    sqlite3_finalize(stmt);

    // Load Relasi (Menghubungkan Parent & Child)
    std::string sqlR = "SELECT * FROM relasi;";
    if (sqlite3_prepare_v2(DB, sqlR.c_str(), -1, &stmt, NULL) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            rail.insertRelation(
                (const char*)sqlite3_column_text(stmt, 0), // kode_stasiun
                sqlite3_column_int(stmt, 1),               // no_ka
                (const char*)sqlite3_column_text(stmt, 2), // waktu_tiba
                (const char*)sqlite3_column_text(stmt, 3), // waktu_berangkat
                (const char*)sqlite3_column_text(stmt, 4)  // info
            );
        }
    }
    sqlite3_finalize(stmt);
    std::cout << "[DB] Data MLL berhasil dipulihkan dari database." << std::endl;
}

// =============================================================
// FUNGSI INSERT (SINKRONISASI KE DB)
// =============================================================
void DatabaseManager::addStationDB(StationNode* s) {
    std::string sql = "INSERT OR IGNORE INTO stasiun VALUES (?, ?, ?, ?, ?, ?);";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, NULL);
    
    sqlite3_bind_text(stmt, 1, s->kode_stasiun.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 2, s->petak_stasiun);
    sqlite3_bind_text(stmt, 3, s->nama_stasiun.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 4, s->kota.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 5, s->tipe_kelas_stasiun);
    sqlite3_bind_int(stmt, 6, s->tinggi_stasiun_mdpl);

    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}

void DatabaseManager::addKeretaDB(KeretaApiNode* k) {
    std::string sql = "INSERT OR IGNORE INTO kereta_api VALUES (?, ?, ?);";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, NULL);
    
    sqlite3_bind_int(stmt, 1, k->no_ka);
    sqlite3_bind_text(stmt, 2, k->nama_kereta.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, k->kelas.c_str(), -1, SQLITE_TRANSIENT);

    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}

void DatabaseManager::addRelasiDB(RelationNode* r) {
    std::string sql = "INSERT OR IGNORE INTO relasi VALUES (?, ?, ?, ?, ?);";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, NULL);
    
    sqlite3_bind_text(stmt, 1, r->parentStation->kode_stasiun.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 2, r->childKereta->no_ka);
    sqlite3_bind_text(stmt, 3, r->waktu_kedatangan.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 4, r->waktu_keberangkatan.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 5, r->info_relasi.c_str(), -1, SQLITE_TRANSIENT);

    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}

// =============================================================
// FUNGSI DELETE (SINKRONISASI KE DB)
// =============================================================
void DatabaseManager::deleteStationDB(std::string kode) {
    std::string sql = "DELETE FROM stasiun WHERE kode_stasiun = ?;";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, kode.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}

void DatabaseManager::deleteKeretaDB(int no_ka) {
    std::string sql = "DELETE FROM kereta_api WHERE no_ka = ?;";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, no_ka);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}

void DatabaseManager::deleteRelasiDB(std::string kode, int no_ka) {
    std::string sql = "DELETE FROM relasi WHERE kode_stasiun = ? AND no_ka = ?;";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, kode.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 2, no_ka);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}

// =============================================================
// FUNGSI UPDATE / EDIT (SINKRONISASI KE DB)
// =============================================================

void DatabaseManager::updateRelasiData(const std::string& kode_stasiun, int no_ka, 
                                      const std::string& tiba, const std::string& berangkat) {
    std::string sql = "UPDATE relasi SET waktu_tiba = ?, waktu_berangkat = ? "
                      "WHERE kode_stasiun = ? AND no_ka = ?;";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, NULL);

    sqlite3_bind_text(stmt, 1, tiba.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, berangkat.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, kode_stasiun.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 4, no_ka);

    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}

void DatabaseManager::updateRelasiChild(const std::string& kode_stasiun, int old_no_ka, int new_no_ka) {
    std::string sql = "UPDATE relasi SET no_ka = ? WHERE kode_stasiun = ? AND no_ka = ?;";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, NULL);

    sqlite3_bind_int(stmt, 1, new_no_ka);
    sqlite3_bind_text(stmt, 2, kode_stasiun.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 3, old_no_ka);

    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}

void DatabaseManager::updateRelasiParent(const std::string& old_kode, const std::string& new_kode, int no_ka) {
    std::string sql = "UPDATE relasi SET kode_stasiun = ? WHERE kode_stasiun = ? AND no_ka = ?;";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, NULL);

    sqlite3_bind_text(stmt, 1, new_kode.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, old_kode.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 3, no_ka);

    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}