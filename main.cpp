#include <iostream>
#include "railwayMLL.h"
using namespace std;

int main() {
    RailwayMLL mll;

    // ---------------------------------------------------------
    //  INSERT DATA STASIUN (Parent)
    // ---------------------------------------------------------
    mll.insertParent(101, "BD", "Bandung", "Bandung", 1, 700);
    mll.insertParent(102, "YK", "Yogyakarta", "Yogyakarta", 1, 113);
    mll.insertParent(103, "SMT", "Semarang Tawang", "Semarang", 1, 4);

    // ---------------------------------------------------------
    //  INSERT DATA KERETA (Child)
    // ---------------------------------------------------------
    mll.insertChild(1, "Argo Parahyangan", "Eksekutif");
    mll.insertChild(2, "Taksaka", "Eksekutif");
    mll.insertChild(3, "Bogowonto", "Ekonomi");

    // ---------------------------------------------------------
    //  INSERT RELATION (Parent ↔ Child)
    // ---------------------------------------------------------
    mll.insertRelation(101, 1, "10:00", "10:05", "Transit Bandung");
    mll.insertRelation(102, 2, "12:30", "12:35", "Transit Yogyakarta");
    mll.insertRelation(103, 3, "14:00", "14:10", "Transit Semarang");

    // ---------------------------------------------------------
    //  DISPLAY DATA
    // ---------------------------------------------------------
    cout << "\n==== LIST STASIUN ====\n";
    mll.showAllParent();

    cout << "\n==== LIST KERETA API ====\n";
    mll.showAllChild();

    cout << "\n==== LIST RELATIONS ====\n";
    mll.showAllRelations();

    // ---------------------------------------------------------
    //  MENAMPILKAN RELASI PER STASIUN
    // ---------------------------------------------------------
    cout << "\n==== CHILD DARI PARENT (Stasiun 101) ====\n";
    mll.showChildFromParent(101);

    // ---------------------------------------------------------
    //  MENAMPILKAN RELASI PER KERETA
    // ---------------------------------------------------------
    cout << "\n==== RELASI DARI KERETA (KA 2) ====\n";
    mll.showRelasiFromKereta(2);

    // ---------------------------------------------------------
    //  HITUNG JUMLAH RELASI DARI STASIUN
    // ---------------------------------------------------------
    cout << "\n==== TOTAL RELASI STASIUN 101 ====\n";
    mll.countChildOfParent(101);

    // ---------------------------------------------------------
    //  DELETE EXAMPLE
    // ---------------------------------------------------------
    cout << "\n=== DELETE KERETA 3 ===\n";
    mll.deleteChild(3);

    cout << "\n=== AFTER DELETE CHILD ===\n";
    mll.showAllChild();

    cout << "\n=== DELETE RELATION (101,1) ===\n";
    mll.deleteRelation(101, 1);

    cout << "\n=== AFTER DELETE RELATION ===\n";
    mll.showAllRelations();

    cout << "\n=== DELETE PARENT (103) ===\n";
    mll.deleteParent(103);

    cout << "\n=== AFTER DELETE PARENT ===\n";
    mll.showAllParent();

    return 0;
}
