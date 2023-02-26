#include "Kurye.h"
#include "Kurye.cpp"

/*
    Projede ilk once MahalleBilgis.txt ve o dosyada ki konutlar graph yapisina ekleniyor ve
    o konutlar arasindaki dijakstra yaklasimi ile en kisa yollar bulunuyor ardidan Paket.txt
    dosyasi okunup graph ile birlikte kurye sinifina aktarilip kurye olusturuluyor ondan sonra
    okunulan o paketler knapsak yaklasimi ile kurye tarafindan dagtiliyor.
*/


int countLinesInFile(string fileName); // dosyada bulunan satir sayisi (konut adedi ogrenmek icin)
int buildGraph(Graph &graph); // Mahalle.txt dosyasina gore Graphi olustruran fonksiyon
void printShortestPathByDijkstra(Graph &graph,int &V); // konutular arasi en kisa yollari yazdiran fonksiyon
int readPakets(List<Paket> &pakets); // paket.txt dosyasini okuyan fonksiyon

int main()
{

    int V = countLinesInFile("MahalleBilgisi.txt");
    if(V == -1){
        cout << "MahalleBilgisi.txt dosyasi acilamadi" << endl;
    }
    Graph graph(V);
    buildGraph(graph);
    printShortestPathByDijkstra(graph,V);
    int P = countLinesInFile("PaketBilgisi.txt");
    cout << "paket sayisi : " << P << endl;
    List<Paket> pakets;
    readPakets(pakets);
    Kurye kurye(pakets, graph, V, 0, 200, 60*60, 10);
    kurye.startKurye();

	return 0;
}


int countLinesInFile(string fileName){
    int count = 0;
    ifstream file(fileName);
    if(!file.is_open()){
        return -1;
    }
    string line;
    while(getline(file, line))
    count++;
    file.close();
    return count;
}

int buildGraph(Graph &graph){
    ifstream MahalleFile("MahalleBilgisi.txt");
    if(!MahalleFile.is_open()){
        return -1;
    }
    string line;
    int i = 0;
    int j = 0;
    while (getline(MahalleFile, line)) {
        stringstream ss(line);
        string word;
        j = 0;
        while(getline(ss, word, ',')) {
            if(word != "-" && word != "0"){
                graph.addEdge(i, j, stoi(word));
                //cout << i << " " << j << " " << stoi(word) << endl;
            }
            j++;
        }
        i++;
    }
    MahalleFile.close();
    return 0;
}

void printShortestPathByDijkstra(Graph &graph,int &V){
    for(int i = 0; i < V; i++){
        if(i == 0){
            cout << "      ";
            cout << setw(6) << "giris" << "    ";
            for(int k = 1; k < V-1; k++)
                cout << "K" << k << setw(5);
            cout << setw(5) << "  cikis" << endl;
            cout << setw(6) << "giris" << " ";
        }
        else if(i == V-1)
            cout << setw(6) << "cikis" << " ";
        else
            cout << "K" << i << setw(5) << " ";
        for(int j = 0; j < V; j++){
            cout << setw(5) << graph.dijkstra(i,j) << " ";
        }
        cout << endl;
    }
}

int readPakets(List<Paket> &pakets){
    ifstream PaketFile("PaketBilgisi.txt");
    if(!PaketFile.is_open()){
        return -1;
    }
    string line;
    while (getline(PaketFile, line)) {
        stringstream ss(line);
        string word;
        int k;
        string name;
        int volume;
        int value;
        getline(ss, word, ',');
        word.erase(0,1);
        k = stoi(word);
        getline(ss, word, ',');
        name = word;
        getline(ss, word, ',');
        volume = stoi(word);
        getline(ss, word, ',');
        value = stoi(word);
        Paket p;
        p.setParameters(k, name, volume, value);
        pakets.push_back(p);
    }
    PaketFile.close();
    return 0;
}

