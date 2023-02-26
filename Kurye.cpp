#include "Kurye.h"

Kurye::Kurye(List<Paket> ap, Graph g, int v, int start, int cap, int t , int st) : allPakets(ap), time(t), starttime(st), capacity(cap), nowPos(start), graph(g), V(v) {
        starttime = st * 60 * 60;
		for(int i = 0; i < V; i++){
            for(int j = 0; j < V; j++){
                shortestpath[i][j] = graph.dijkstra(i,j);
            }
        }
    }

int Kurye::findRoutByKnapsak(){
        int size = allPakets.size();
        if(allPakets.isEmpty()){ return -1; }
        Paket tmpPakets[size];
        int s = 0;
        for(Node<Paket>* i = allPakets.begin(); i != allPakets.end(); i = i->next){
            tmpPakets[s] = i->data;
            s++;
        }
        int V[size+1][capacity+1];
        int keep[size+1][capacity+1];
        for(int i = 0; i <= capacity; i++){
            V[0][i] = 0;
        }
        for(int i = 1; i <= size; i++){
            for(int w = 0; w <= capacity; w++){
                if((tmpPakets[i-1].volume <= w) && ((tmpPakets[i-1].value + V[i-1][w - tmpPakets[i-1].volume]) > V[i-1][w])){
                    V[i][w] = tmpPakets[i-1].value + V[i-1][w - tmpPakets[i-1].volume];
                    keep[i-1][w] = 1;
                }
                else {
                    V[i][w] = V[i-1][w];
                    keep[i-1][w] = 0;
                }
            }
        }

        int k = capacity;
        for(int i = size-1; i >= 0; i--){
            if(keep[i][k] == 1){
                paketsInBag.push_back(tmpPakets[i]);
                k -= tmpPakets[i].volume;
            }
        }
        cout << endl;
        printPaketsInBag();
        return V[size][capacity];
    }

void Kurye::printPaketsInBag(){

        cout << "paket teslimi bu sekilde yapilacak.." << endl;
        cout << setw(10) << "Konutlar" << setw(20) << "Esya ismi" << setw(20) << "Hacim(cm3)"
        << setw(10) << "Degeri" << setw(30) << "Hacim/Deger Endeksi" << endl;
        for(Node<Paket>* i = paketsInBag.begin(); i != paketsInBag.end(); i = i->next){
            cout << setw(9) << "K" << i->data.k << setw(10) << setw(20) << i->data.name << setw(20) << i->data.volume
            << setw(10) << i->data.value << setw(30) << i->data.value/i->data.volume << endl;
        }
    }

void Kurye::startKurye(){
        printAllPakets();
        fstream sonucfile;
        string filename = "sonuc.txt";
        sonucfile.open(filename ,ios::out);
        while(true){
            if(findRoutByKnapsak() == -1) {
                cout << "\nButun paketler dagtildi ." << endl;
                cout << "Topladigi prim : " << prim << endl;
                sonucfile << "Butun paketler dagtildi ." << endl;
                sonucfile << "Topladigi prim : " << prim << endl;
                cout << "sonuc.txt dosyasi olusturuldu." << endl;
                return;
            }
            while(true){
                if(runKurye(sonucfile) == -1){
                    cout << "\nPaket teslim edilemedi zaman bitti." << endl;
                    cout << "Topladigi prim : " << prim << endl;
                    sonucfile << "Paket teslim edilemedi zaman bitti." << endl;
                    sonucfile << "Topladigi prim : " << prim << endl;
                    cout << "sonuc.txt dosyasi olusturuldu." << endl;
                    return;
                }
                if(runKurye(sonucfile) == -2){
                    cout << "\nmotor uzerindeki paketler bitti merkeze donuyor" << endl;
                    sonucfile << "motor uzerindeki paketler bitti merkeze donuyor" << endl;
                    nowPos=0;
                    break;
                }
            }

        }
        sonucfile.close();
    }

int Kurye::runKurye(fstream &sonucfile){


        if(paketsInBag.isEmpty()){ return -2; }
        Paket delivePaket;
        delivePaket = paketsInBag.front();
        int dis = shortestpath[nowPos][delivePaket.k];
        int tt;
        tt = (dis/5) + 120;
        time -= tt;
        if(time < 0){
            return -1;
        }
        paketsInBag.pop_front();
        deleteDelivedPaketFromAllPakets(delivePaket.k);
        starttime += tt;
        cout << "K" << delivePaket.k << " " << delivePaket.name << " " << delivePaket.volume << " " << delivePaket.value
        << " paketi teslim edildi saat : " << (starttime/(60*60)) << ":" << (starttime/60)%60 << ":" << starttime%60 << endl;
        sonucfile << "K" << delivePaket.k << " " << delivePaket.name << " " << delivePaket.volume << " " << delivePaket.value
        << " paketi teslim edildi saat : " << (starttime/(60*60)) << ":" << (starttime/60)%60 << ":" << starttime%60 << endl;
    	nowPos = delivePaket.k;
        prim += delivePaket.value / 100.0;
    }

void Kurye::deleteDelivedPaketFromAllPakets(int k){
        List<Paket> tmp;
        tmp = allPakets;
        allPakets.clear();
        for(Node<Paket>* i = tmp.begin(); i != tmp.end(); i = i->next){
            if(i->data.k != k){
                Paket tp;
                tp = i->data;
                allPakets.push_back(tp);
            }
        }
    }

void Kurye::printAllPakets(){

        cout << "butun paketler" << endl;
        cout << setw(10) << "Konutlar" << setw(20) << "Esya ismi" << setw(20) << "Hacim(cm3)"
        << setw(10) << "Degeri" << setw(30) << "Hacim/Deger Endeksi" << endl;
        for(Node<Paket>* i = allPakets.begin(); i != allPakets.end(); i = i->next){
            cout << setw(9) << "K" << i->data.k << setw(10) << setw(20) << i->data.name << setw(20) << i->data.volume
            << setw(10) << i->data.value << setw(30) << i->data.value/i->data.volume << endl;
        }
    }
