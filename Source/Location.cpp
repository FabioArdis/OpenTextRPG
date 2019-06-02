#include "Location.h"

Location::Location() {
    for(int j = 0; j < 10; j++) {
        Dungeon1[j][0] = "X";
    }
    for(int i = 1; i < 10; i++) {
        Dungeon1[0][i] = "X";
    }
    for(int j = 1; j < 9; j++) {
        for(int i = 1; i < 9; i++) {
            Dungeon1[j][i] = " ";
        }
    }
    for(int j = 1; j < 10; j++) {
        Dungeon1[j][9] = "X";
    }
    for(int i = 1; i < 10; i++) {
        Dungeon1[9][i] = "X";
    }
    Dungeon1[6][5] = "X";
    Dungeon1[4][2] = "X";
}
