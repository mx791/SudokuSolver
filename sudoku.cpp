#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>

int SIZE = 2;
int SIZE_2 = SIZE*SIZE;
int FULL_SIZE = SIZE_2*SIZE_2;

int* createWithSize(int size) {
    int* arr = new int[size];
    for (int i=0; i<size; i++) {
        arr[i] = 0;
    }
    return arr;
}

bool isGridFool(int* grid) {
    for (int i=0; i<FULL_SIZE; i++) {
        if (grid[i] == 0) {
            return false;
        }
    }
    return true;
}

bool isGridValid(int* grid) {
    for (int i=0; i<SIZE*SIZE; i++) {
        int* seensH = createWithSize(SIZE_2+1);
        int* seensV = createWithSize(SIZE_2+1);
        for (int e=0; e<SIZE*SIZE; e++) {
            // horizontal
            int value = grid[i*SIZE_2+e];
            if (seensH[value] == 1 && value != 0) {
                return false;
            }
            seensH[value] = 1;
            // vertical
            int value2 = grid[e*SIZE_2 + i];
            if (seensV[value2] == 1 && value2 != 0) {
                return false;
            }
            seensV[value2] = 1;
        }
        free(seensV);
        free(seensH);

    }
    for (int x=0; x<SIZE; x++) {
        for (int y=0; y<SIZE; y++) {
            int* seens = createWithSize(SIZE_2+1);
            for (int x1=0; x1<SIZE; x1++) {
                for (int y1=0; y1<SIZE; y1++) {
                    int index = x*SIZE + y*SIZE*SIZE*SIZE + y1*SIZE_2 + x1;
                    int value = grid[index];
                    if (seens[value] == 1 && value != 0) {
                        return false;
                    }
                    seens[value] = 1;
                }
            }
            free(seens);
        }
    }
    return true;
}

void printGrid(int* grid) {
    for (int i=0; i<SIZE*SIZE; i++) {
        for (int e=0; e<SIZE*SIZE; e++) {
            std::cout << grid[i*SIZE_2+e] << " ";
        }
        std::cout << std::endl;
    }
}

void solveGrid(int* grid) {
    int* mask = createWithSize(FULL_SIZE);
    for (int i=0; i<FULL_SIZE; i++) {
        mask[i] = grid[i];
    }
    int cursor = 0;
    bool continuer = true;
    bool goBackFlag = false;
    int loopIters = 0;
    while (continuer) {
        loopIters++;
        bool valid = isGridValid(grid);
        if (isGridFool(grid) && valid) {
            return;
        }
        if (valid && (grid[cursor] == 0 || goBackFlag)) {
            grid[cursor]++;
            goBackFlag = false;
        } else if (grid[cursor] < SIZE_2) {
            grid[cursor]++;
        } else {
            grid[cursor] = 0;
            cursor--;
            while (mask[cursor] != 0) {
                cursor--;
            }
            goBackFlag = true;
        }
        if (isGridValid(grid) && grid[cursor] != 0 && !goBackFlag) {
            cursor++;
            while (mask[cursor] != 0) {
                cursor++;
            }
        }
        continuer = cursor < FULL_SIZE && cursor >= 0;
    }
    free(mask);
    std::cout << "Iters performed: " << loopIters << "\n";
    if (!isGridFool(grid)) {
        std::cout << "Grid cannot be resolved" << "\n";
    }
}

int* loadGrid() {
    std::string path = "grid.txt";
    std::ifstream myfile(path);
    std::string line;
    std::vector<int> data;
    int i = 0;
    while (getline(myfile, line)) {
        for (int e=0; e<line.size(); e++) {
            if (line[e] != ' ') {
                data.push_back(std::stoi(line.substr(e, 1)));
            }
        }
        i++;
    }
    if (sqrt(data.size()) != i) {
        std::cout << "Wrong size : got " << data.size() << " while expecting " << i*i << "\n";
    }
    SIZE = sqrt(i);
    SIZE_2 = SIZE*SIZE;
    FULL_SIZE = SIZE_2*SIZE_2;
    int* grid = new int[data.size()];
    for (int id=0; id<data.size(); id++) {
        grid[id] = data[id];
    }
    return grid;
}

int main() {
    int* grid = loadGrid();
    solveGrid(grid);
    printGrid(grid);
    return 0;
}