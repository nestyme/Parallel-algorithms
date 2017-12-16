#include <iostream>
#include <omp.h>
#include <unistd.h>
#define MAX_NUMBER 25
using namespace std;
typedef bool ** bool_prt;
void operate(int a, int b, bool **source, bool_prt stock);
void compute(int r, bool **source, bool_prt stock);

int main() {
    bool_prt l;
    bool_prt buffer;
    unsigned int k;
    bool alive;
    k = 0;
    alive = 1;
    l = new bool *[MAX_NUMBER];
    buffer = new bool *[MAX_NUMBER];
    for (int i = 0; i < MAX_NUMBER; i++) {
        l[i] = new bool[MAX_NUMBER];
        buffer[i] = new bool[MAX_NUMBER];
    }

    srand(time(NULL));

    for (int i = 0; i < MAX_NUMBER; i++)
        for (int j = 0; j < MAX_NUMBER; j++) {
            l[i][j] = static_cast<bool>(rand() % 2);
            buffer[i][j] = 0;
        }

    bool_prt bool_prt1 = l;
    bool_prt bool_prt2 = buffer;

    while (alive) {
        int i;
        for (i = 0; i < MAX_NUMBER; i++) {
            compute(i, bool_prt1, bool_prt2);
        }



        for (int i = 0; i < 16; i++) {
            cout << endl;
        }
        ++k;
        cout<<"==================="<<k<<"==================="<<endl;
        for (int i = 0; i < MAX_NUMBER; i++) {
            for (int j = 0; j < MAX_NUMBER; j++) {
                if (bool_prt2[i][j])
                    cout << "o";
                else
                    cout << " ";
            }
            cout << endl;
        }

        usleep(2000000);
        swap(bool_prt1, bool_prt2);
    }

    return 0;
}

void operate(int a, int b, bool_prt source, bool_prt stock) {
    int operateSet[] = {-1, 0, 1};
    int cnt = 0, tx, ty;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            tx = a + operateSet[i];
            if (tx >= MAX_NUMBER)
                tx = 0;
            else if (tx < 0)
                tx = MAX_NUMBER - 1;

            ty = b + operateSet[j];
            if (ty >= MAX_NUMBER)
                ty = 0;
            else if (ty < 0)
                ty = MAX_NUMBER - 1;

            if (tx == a && ty == b)
                continue;

            if (source[tx][ty])
                cnt++;
        }
    }

    if (source[a][b]) {
        stock[a][b] = (cnt == 2 || cnt == 3);
    } else {
        stock[a][b] = (cnt == 3);
    }
}

void compute(int r, bool **source, bool **stock) {
    for (int j = 0; j < MAX_NUMBER; j++) {
        operate(r, j, source, stock);
    }
}



