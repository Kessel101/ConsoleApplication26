#include "Punkty.h"

//#define PointsFromFile

#ifndef PointsFromFile


int main()
{
    srand(time(0));
    int n;
    cout << "Podaj ilosc punktow(zaleca sie < 24)" << endl;
    cin >> n;
    if (n > 52) {
        cout << "za duzo!" << endl;
        return 0;
    }
    vector <point> plansza = vecOfPoints(n);

    /*for (auto i = plansza.begin(); i < plansza.end(); i++) {
        printPoint(*i);
    }*/

    vector <dpoint> rozw;

    auto start = chrono::high_resolution_clock::now();
    djikstra(plansza, &rozw);
    auto end = chrono::high_resolution_clock::now();
    auto elapsed = end - start;

    printdji(rozw);

    auto duration_ms = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    cout << "Czas(ms): " << duration_ms << endl;


    
    return 0;
}

#else

int main() {
    int n = 52;
    /*cout << "Podaj ilosc punktow(zaleca sie < 24)" << endl;
    cin >> n;
    if (n > 52) {
        cout << "za duzo!" << endl;
        return 0;
    }*/
    vector<point> plansza = readPointsFromFile("points.txt", n);

    vector <dpoint> rozw;

    /*for (auto i = plansza.begin(); i < plansza.end(); i++) {
        printPoint(*i);
    }*/

    auto start = chrono::high_resolution_clock::now();
    djikstra(plansza, &rozw);
    auto end = chrono::high_resolution_clock::now();
    auto elapsed = end - start;

    printdji(rozw);

    auto duration_ms = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    cout << "Czas(ms): " << duration_ms << endl;

    return 0;
}

#endif // !PointsFromFile

