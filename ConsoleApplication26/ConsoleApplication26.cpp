#include <iostream>
#include <math.h>
#include <vector>
#include <string>
#include <ctime> 

#define f 5
using namespace std;

struct point {
    char name;
    int x, y;
    vector <point> connections;
    bool operator == (const point& p) {
        if (p.x == x and p.y == y)
            return true;
        else
            return false;
    }
};

double distance(point p1, point p2) {
    return sqrt(pow((p1.x - p2.x), 2) + pow((p1.y - p2.y), 2));
}

void findConnections(point* p, vector<point> tab) {
    vector<point>::iterator ptr;
    for (ptr = tab.begin(); ptr < tab.end(); ptr++) {
        if (distance(*p, *ptr) <= f and p->name != ptr->name) {
            p->connections.push_back(*ptr);
            /*ptr->connections.push_back(*p);*/
        }

    }
}

point generatePoint(int start = 65, vector <point> used = {}, int radius = 0, point p = {}, int xmin = -100, int xmax = 100, int ymin = -100, int ymax = 100) {
    point res;
    if (start > 90) {
        res.name = char(start + 6);
    }
    else
    {
        res.name = char(start);
    }
    if (radius == 0) {
        res.x = rand() % (xmax - xmin) + xmin;
        res.y = rand() % (ymax - ymin) + ymin;
    }

    else
    {

        bool con = true;
        while (con) {
            con = false;
            res.x = rand() % (2 * radius + 1) + p.x - radius;
            res.y = rand() % (2 * radius + 1) + p.y - radius;
            while (distance(p, res) > f)
                res.y = rand() % (2 * radius + 1) + p.y - radius;
            if (res.x < xmin or res.x > xmax or res.y < ymin or res.y > ymax)
                con = false;
        }
    }
    for (auto o = (used).begin(); o < (used).end(); o++) {
        if (*o == res) {
            res = generatePoint(start, used, radius, p);
        }
    }
    return res;
}

void printPoint(point p) {
    cout << "Nazwa = \"" << p.name << "\" x = " << p.x << " y = " << p.y << " Polaczenia z: ";
    for (auto t = p.connections.begin(); t < p.connections.end(); t++)
        cout << (*t).name << " ";
    cout << endl;
}

void generateGroup(int start, int number, point p, vector <point>* used, int xmin = -100, int xmax = 100, int ymin = -100, int ymax = 100) {
    for (int j = 0; j < number; j++) {
        point po;
        po = generatePoint(start + j, *used, f, p);
        /*findConnections(&po, *used);*/
        used->push_back(po);
    }
}

vector <point> vecOfPoints(int quantity = 20, int xmin = -100, int xmax = 100, int ymin = -100, int ymax = 100) {
    vector <point> res;
    int number;
    point previous;
    for (int i = 0; i < quantity; i++) {
        point p;
        if (i == 0) {
            p = generatePoint(65, res, 0, {}, xmin, xmax, ymin, ymax);
        }
        else {
            p = generatePoint(i + 65, res, f, previous);
        }
        /*findConnections(&p, res);*/
        res.push_back(p);
        previous = p;
        number = rand() % 3 + 1;
        while (i + number >= quantity and number > 0)
            number--;
        generateGroup(i + 66, number, p, &res);
        i += number;
    }
    for (auto i = res.begin(); i < res.end(); i++) {
        findConnections(&(*i), res);
    }
    return res;
}

struct dpoint {
    point p;
    double dlugosc;
    char prev;
};


//point* findPoint(char name, vector<dpoint> board) {
//    for (auto a = board.begin(); a < board.end(); a++) {
//        if (a->p.name == name)
//            return &a->p;
//    }
//    return NULL;
//}

dpoint* finddPoint(char name, vector<dpoint>& board) {
    for (auto it = board.begin(); it != board.end(); ++it) {
        if (it->p.name == name) {
            return &(*it);
        }
    }
    return nullptr;
}

void printdji(vector<dpoint> tab) {
    for (auto i = tab.begin(); i < tab.end(); i++) {
        printPoint(i->p);
        cout << "Odleglosc od punktu startowego: " << i->dlugosc << endl;
        // Wydrukuj œcie¿kê
        cout << "Sciezka: ";
        char prev = i->prev;
        vector<char> path;
        while (prev != '\0') {
            path.push_back(prev);
            for (auto j = tab.begin(); j < tab.end(); j++) {
                if (j->p.name == prev) {
                    prev = j->prev;
                    break;
                }
            }
        }
        for (auto it = path.rbegin(); it != path.rend(); ++it) {
            cout << *it << " ";
        }
        cout << i->p.name << endl;
    }
}

void djikstra(vector <point> points = {}, vector <dpoint>* path = {}) {
    for (auto i = points.begin(); i < points.end(); i++) {
        if (i == points.begin()) {
            path->push_back({ *i, 0 ,'\0' });
        }
        else
        {
            path->push_back({ *i, INT_MAX,'\0' });
        }
    }


    for (auto i = path->begin(); i < path->end(); i++) {
        for (auto j = i->p.connections.begin(); j < i->p.connections.end(); j++) {
            dpoint* d = finddPoint(j->name, *path);
            if (i->dlugosc + distance(*j, i->p) < d->dlugosc) {
                d->dlugosc = i->dlugosc + distance(*j, i->p);
                d->prev = i->p.name;

            }
        }
    }
}

int main()
{
    srand(time(0)); // Inicjalizacja ziarna generatora liczb losowych
    int n;
    //cout << "Podaj ilosc punktow(zaleca sie < 26)" << endl;
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

    djikstra(plansza, &rozw);
    printdji(rozw);
    return 0;
}

