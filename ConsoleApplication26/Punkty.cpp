#include "Punkty.h"

#define f 5
using namespace std;


void writePointsToFile(const vector<point>& points, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (const auto& p : points) {
            file << "Name: " << p.name << ", Coordinates: (" << p.x << ", " << p.y << "), Connections: ";
            for (const auto& conn : p.connections) {
                file << conn.name << " ";
            }
            file << "\n";
        }
        file.close();
        cout << "Punkty zapisane do " << filename << endl;
    }
    else {
        cout << "Blad przy otwarciu pliku " << filename << endl;
    }
}

vector<point> readPointsFromFile(const string& filename, int n) {
    vector<point> points;
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        int i = 0;
        while (getline(file, line) and i++ < n) {
            char name;
            int x, y;
            vector<char> connections;
            if (sscanf(line.c_str(), "Name: %c, Coordinates: (%d, %d), Connections:", &name, &x, &y) == 3) {
                point p;
                p.name = name;
                p.x = x;
                p.y = y;
                string connectionsStr = line.substr(line.find("Connections: ") + 13);
                for (char c : connectionsStr) {
                    if (isalpha(c)) {
                        connections.push_back(c);
                    }
                }
                for (char c : connections) {
                    point conn;
                    conn.name = c;
                    p.connections.push_back(conn);
                }
                points.push_back(p);
            }
        }
        file.close();
    }
    else {
        cout << "Unable to open file " << filename << endl;
    }
    return points;
}

bool PointInVec(point p, vector<point> vec) {
    for (auto& t : vec) {
        if (t == p) {
            return true;
        }
    }
    return false;
}

double distance(point p1, point p2) {
    return sqrt(pow((p1.x - p2.x), 2) + pow((p1.y - p2.y), 2));
}

void findConnections(point* p, vector<point> tab) {
    for (auto& ptr : tab) {
        if (distance(*p, ptr) <= f && p->name != ptr.name) {
            p->connections.push_back(ptr);
        }
    }
}

point generatePoint(int start, vector<point> used, int radius, point p, int dir, int xmin, int xmax, int ymin, int ymax) {
    point res;
    if (start > 90) {
        res.name = char(start + 6);
    }
    else {
        res.name = char(start);
    }
    if (radius == 0) {
        res.x = rand() % (xmax - xmin + 1) + xmin;
        res.y = rand() % (ymax - ymin + 1) + ymin;
    }
    else {
        bool con = true;
        int i = 0;
        while (con) {
            if (i++ < 7) {
                con = false;
                if (dir == 1 || dir == 4) {
                    res.x = rand() % (radius + 1) + p.x;
                }
                else {
                    res.x = rand() % (radius + 1) + p.x - radius;
                }
                if (dir < 3) {
                    for (res.y = p.y; distance(p, res) <= f; res.y++) {}
                    res.y = rand() % (res.y - p.y) + p.y;
                }
                else {
                    for (res.y = p.y; distance(p, res) <= f; res.y--) {}
                    res.y = rand() % (res.y - p.y) + p.y;
                }
                if (PointInVec(res, used))
                    con = true;
            }
            else {
                return p;
            }
        }
    }
    return res;
}

void printPoint(point p) {
    cout << "Nazwa = \"" << p.name << "\" x = " << p.x << " y = " << p.y << " Polaczenia z: ";
    for (auto& t : p.connections)
        cout << t.name << " ";
    cout << endl;
}

void generateGroup(int start, int number, point p, int* dir, vector<point>* used, int xmin, int xmax, int ymin, int ymax) {
    for (int j = 0; j < number; j++) {
        point po = generatePoint(start + j, *used, f, p, *dir);
        if (po == p) {
            for (auto& idx : *used) {
                if (!(po == p)) break;
                po = generatePoint(start + j, *used, f, idx, *dir);
            }
        }
        used->push_back(po);
    }
}

vector<point> vecOfPoints(int quantity, int xmin, int xmax, int ymin, int ymax) {
    vector<point> res;
    int number, dir;
    point previous;
    for (int i = 0; i < quantity; i++) {
        point p;
        if (i == 0) {
            dir = rand()%4 + 1;
            p = generatePoint(65, res, 0, {}, dir, xmin, xmax, ymin, ymax);
        }
        else {
            p = generatePoint(i + 65, res, f, previous, dir);
        }
        res.push_back(p);
        previous = p;
        number = rand() % 3 + 1;
        while (i + number >= quantity && number > 0)
            number--;
        generateGroup(i + 66, number, p, &dir, &res);
        i += number;
    }
    for (auto& i : res) {
        findConnections(&i, res);
    }
    return res;
}

dpoint* finddPoint(char name, vector<dpoint>& board) {
    for (auto& it : board) {
        if (it.p.name == name) {
            return &it;
        }
    }
    return nullptr;
}

void printdji(vector<dpoint> tab) {
    for (auto& i : tab) {
        printPoint(i.p);
        cout << "Odleglosc od punktu startowego: " << i.dlugosc << endl;
        cout << "Sciezka: ";
        char prev = i.prev;
        vector<char> path;
        while (prev != '\0') {
            path.push_back(prev);
            for (auto& j : tab) {
                if (j.p.name == prev) {
                    prev = j.prev;
                    break;
                }
            }
        }
        for (auto it = path.rbegin(); it != path.rend(); ++it) {
            cout << *it << " ";
        }
        cout << i.p.name << endl;
    }
}

void djikstra(vector<point> points, vector<dpoint>* path) {
    if (points.empty()) return;

    // Initialize the path vector
    for (const auto& pt : points) {
        if (pt.name == points.front().name) {
            path->push_back({ pt, 0, {} });
        }
        else {
            path->push_back({ pt, INT_MAX, {} });
        }
    }

    vector<bool> visited(points.size(), false);

    while (true) {
        // Find the unvisited node with the smallest distance
        int minDistance = INT_MAX;
        dpoint* current = nullptr;
        for (auto& dp : *path) {
            if (!visited[&dp - &(*path)[0]] && dp.dlugosc < minDistance) {
                minDistance = dp.dlugosc;
                current = &dp;
            }
        }

        if (current == nullptr) break; // All reachable nodes have been visited

        visited[current - &(*path)[0]] = true;

        // Update distances for neighbors
        for (const auto& conn_name : current->p.connections) {
            dpoint* neighbor = finddPoint(conn_name.name, *path);
            if (neighbor && !visited[neighbor - &(*path)[0]]) {
                int new_distance = current->dlugosc + distance(current->p, neighbor->p);
                if (new_distance < neighbor->dlugosc) {
                    neighbor->dlugosc = new_distance;
                    neighbor->prev = current->p.name;
                }
            }
        }
    }
}
