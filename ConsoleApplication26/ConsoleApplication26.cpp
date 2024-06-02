#include "Punkty.h"

#define PointsFromFile

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


    vector <dpoint> rozw;

    djikstra(plansza, &rozw);

    printdji(rozw);



    
    return 0;
}

#else

int main() {
    
    vector<point> plansza = readPointsFromFile("points.txt", 52);

    vector <dpoint> rozw;

    

    djikstra(plansza, &rozw);
    

    printdji(rozw);


    return 0;
}

#endif

