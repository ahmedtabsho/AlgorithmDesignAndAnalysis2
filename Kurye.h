#ifndef KURYE_H_INCLUDED
#define KURYE_H_INCLUDED

#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>
#include "List.h"
#include "List.cpp"
#include "Graph.h"
#include "Graph.cpp"
#include "Paket.h"
#include "Paket.cpp"

class Kurye{
public:
    float prim = 0.0; // toplayacagi prim
    int nowPos; // bulundugu konum bilgisi
    int capacity; // motor kapasitesi
    int time; // calisma suresi
    int starttime; // baslangic saati
    int V; // konut sayisi arti giris cikis
    int shortestpath[100][100]; // dijkastraya gore bulunan en kisa yollar tutan array
    List<Paket> allPakets; // butun paketler
    List<Paket> paketsInBag; // motorda bulunan paketler
    Graph graph;
    Kurye(List<Paket> ap, Graph g, int v, int start, int cap = 200, int t = 60 * 60, int st = 10);
    int findRoutByKnapsak();  //  knapsak yaklasimi ile tum paketlerden dagitilacak paketleri bulan fonksiyon
    void printPaketsInBag(); // motorda bulunan paketleri yazdiran fonksiyon
    void startKurye(); // kuryeyi paketleri bitene kadar calistiran fonksiyon
    int runKurye(fstream &sonucfile); // kuryeyi calistirip sonuc.txt'e sonucu yazan fonksiyon
    void deleteDelivedPaketFromAllPakets(int k); // teslim edilen paketi silen fonksiyon
    void printAllPakets(); // teslim edilecek butun paketleri yazdiran fonsiyon
};


#endif // KURYE_H_INCLUDED
