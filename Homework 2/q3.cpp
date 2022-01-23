#include <bits/stdc++.h>

using namespace std;

#ifndef RUBIKS_CUBE_SRC_RUBIKS_CUBE_H
#define RUBIKS_CUBE_SRC_RUBIKS_CUBE_H



class rubiks_cube {

public:
    enum color { e_white, e_red, e_green, e_orange, e_blue, e_yellow };
    enum side { e_top, e_front, e_left, e_back, e_right, e_bottom };
    enum direction { e_middle, e_equator, e_standing };


public:
    rubiks_cube() {
        for (int i = 0; i < 6; i++) {
            rubicsCube[i][0] = color(i);
            rubicsCube[i][1] = color(i);
            rubicsCube[i][2] = color(i);
            rubicsCube[i][3] = color(i);
        }
    }

    rubiks_cube& operator= (const rubiks_cube& other) = default;
    rubiks_cube(const rubiks_cube& other) = default;
    ~rubiks_cube() = default;

    array <side, 4> adj_side(side _side) const {
        array <side, 4> result;
        if (_side == e_back) {
            result = { e_top, e_left, e_bottom, e_right };
        }

        else if (_side == e_right) {
            result = { e_top, e_back, e_bottom, e_front };
        }

        else if (_side == e_front) {
            result = {e_top,e_right,e_bottom,e_left};
        }

        else if (_side == e_left) {
            result = { e_top, e_front, e_bottom, e_back };
        }

        else if (_side == e_top) {
            result = {e_back,e_right,e_front,e_left};
        }

        else {
            result = { e_front, e_right, e_back, e_left };
        }
        return result;
    }

    const array<color, 4>& get_side(side side_to_get) const{
        return rubicsCube[side_to_get];
    }

    void rotate_cube(direction direction_to_rotate, int count) {
        color temp;
        count = count % 4;
        if (count < 0) {
            count += 4;
        }
        for (int i = 0; i < (count); i++) {
            if (direction_to_rotate == e_middle) {
                color temp_side[4] = { rubicsCube[0][0], rubicsCube[0][1], rubicsCube[0][2], rubicsCube[0][3] };
                rubicsCube[0][0] = rubicsCube[1][0];
                rubicsCube[0][1] = rubicsCube[1][1];
                rubicsCube[0][2] = rubicsCube[1][2];
                rubicsCube[0][3] = rubicsCube[1][3];

                rubicsCube[1][0] = rubicsCube[5][0];
                rubicsCube[1][1] = rubicsCube[5][1];
                rubicsCube[1][2] = rubicsCube[5][2];
                rubicsCube[1][3] = rubicsCube[5][3];

                rubicsCube[5][0] = rubicsCube[3][3];
                rubicsCube[5][1] = rubicsCube[3][2];
                rubicsCube[5][2] = rubicsCube[3][1];
                rubicsCube[5][3] = rubicsCube[3][0];

                rubicsCube[3][0] = temp_side[3];
                rubicsCube[3][1] = temp_side[2];
                rubicsCube[3][2] = temp_side[1];
                rubicsCube[3][3] = temp_side[0];

                temp = rubicsCube[2][0];
                rubicsCube[2][0] = rubicsCube[2][1];
                rubicsCube[2][1] = rubicsCube[2][3];
                rubicsCube[2][3] = rubicsCube[2][2];
                rubicsCube[2][2] = temp;

                temp = rubicsCube[4][1];
                rubicsCube[4][1] = rubicsCube[4][0];
                rubicsCube[4][0] = rubicsCube[4][2];
                rubicsCube[4][2] = rubicsCube[4][3];
                rubicsCube[4][3] = temp;
            }
            else if (direction_to_rotate == e_equator) {
                color temp_side[4] = { rubicsCube[1][0], rubicsCube[1][1], rubicsCube[1][2], rubicsCube[1][3] };
                rubicsCube[1][0] = rubicsCube[4][0];
                rubicsCube[1][1] = rubicsCube[4][1];
                rubicsCube[1][2] = rubicsCube[4][2];
                rubicsCube[1][3] = rubicsCube[4][3];

                rubicsCube[4][0] = rubicsCube[3][0];
                rubicsCube[4][1] = rubicsCube[3][1];
                rubicsCube[4][2] = rubicsCube[3][2];
                rubicsCube[4][3] = rubicsCube[3][3];

                rubicsCube[3][0] = rubicsCube[2][0];
                rubicsCube[3][1] = rubicsCube[2][1];
                rubicsCube[3][2] = rubicsCube[2][2];
                rubicsCube[3][3] = rubicsCube[2][3];

                rubicsCube[2][0] = temp_side[0];
                rubicsCube[2][1] = temp_side[1];
                rubicsCube[2][2] = temp_side[2];
                rubicsCube[2][3] = temp_side[3];

                temp = rubicsCube[0][0];
                rubicsCube[0][0] = rubicsCube[0][2];
                rubicsCube[0][2] = rubicsCube[0][3];
                rubicsCube[0][3] = rubicsCube[0][1];
                rubicsCube[0][1] = temp;

                temp = rubicsCube[5][0];
                rubicsCube[5][0] = rubicsCube[5][1];
                rubicsCube[5][1] = rubicsCube[5][3];
                rubicsCube[5][3] = rubicsCube[5][2];
                rubicsCube[5][2] = temp;
            }
            else if (direction_to_rotate == e_standing) {
                color temp_side[4] = { rubicsCube[0][0], rubicsCube[0][1], rubicsCube[0][2], rubicsCube[0][3] };

                rubicsCube[0][0] = rubicsCube[2][2];
                rubicsCube[0][1] = rubicsCube[2][0];
                rubicsCube[0][2] = rubicsCube[2][3];
                rubicsCube[0][3] = rubicsCube[2][1];

                rubicsCube[2][0] = rubicsCube[5][2];
                rubicsCube[2][1] = rubicsCube[5][0];
                rubicsCube[2][2] = rubicsCube[5][3];
                rubicsCube[2][3] = rubicsCube[5][1];

                rubicsCube[5][0] = rubicsCube[4][2];
                rubicsCube[5][1] = rubicsCube[4][0];
                rubicsCube[5][2] = rubicsCube[4][3];
                rubicsCube[5][3] = rubicsCube[4][1];

                rubicsCube[4][1] = temp_side[0];
                rubicsCube[4][3] = temp_side[1];
                rubicsCube[4][0] = temp_side[2];
                rubicsCube[4][2] = temp_side[3];

                temp = rubicsCube[1][0];
                rubicsCube[1][0] = rubicsCube[1][2];
                rubicsCube[1][2] = rubicsCube[1][3];
                rubicsCube[1][3] = rubicsCube[1][1];
                rubicsCube[1][1] = temp;

                temp = rubicsCube[3][1];
                rubicsCube[3][1] = rubicsCube[3][3];
                rubicsCube[3][3] = rubicsCube[3][2];
                rubicsCube[3][2] = rubicsCube[3][0];
                rubicsCube[3][0] = temp;
            }
        }
    }

    void rotate_side(side side_to_rotate, int count) {
        color temp;
        count = count % 4;
        if (count < 0) {
            count += 4;
        }
        for (int i = 0; i < (count); i++) {
            temp = rubicsCube[side_to_rotate][0];
            rubicsCube[side_to_rotate][0] = rubicsCube[side_to_rotate][2];
            rubicsCube[side_to_rotate][2] = rubicsCube[side_to_rotate][3];
            rubicsCube[side_to_rotate][3] = rubicsCube[side_to_rotate][1];
            rubicsCube[side_to_rotate][1] = temp;
            array <side, 4> t_side = adj_side(side_to_rotate);
            if(side_to_rotate == e_top){
                temp = rubicsCube[t_side[0]][1];
                rubicsCube[t_side[0]][1] = rubicsCube[t_side[3]][1];
                rubicsCube[t_side[3]][1] = rubicsCube[t_side[2]][1];
                rubicsCube[t_side[2]][1] = rubicsCube[t_side[1]][1];
                rubicsCube[t_side[1]][1] = temp;
                temp = rubicsCube[t_side[0]][0];
                rubicsCube[t_side[0]][0] = rubicsCube[t_side[3]][0];
                rubicsCube[t_side[3]][0] = rubicsCube[t_side[2]][0];
                rubicsCube[t_side[2]][0] = rubicsCube[t_side[1]][0];
                rubicsCube[t_side[1]][0] = temp;
            }
            else if (side_to_rotate == e_bottom) {
                temp = rubicsCube[t_side[0]][3];
                rubicsCube[t_side[0]][3] = rubicsCube[t_side[3]][3];
                rubicsCube[t_side[3]][3] = rubicsCube[t_side[2]][3];
                rubicsCube[t_side[2]][3] = rubicsCube[t_side[1]][3];
                rubicsCube[t_side[1]][3] = temp;
                temp = rubicsCube[t_side[0]][2];
                rubicsCube[t_side[0]][2] = rubicsCube[t_side[3]][2];
                rubicsCube[t_side[3]][2] = rubicsCube[t_side[2]][2];
                rubicsCube[t_side[2]][2] = rubicsCube[t_side[1]][2];
                rubicsCube[t_side[1]][2] = temp;
            }
            else if (side_to_rotate == e_front)
            {
                temp = rubicsCube[t_side[0]][2];
                rubicsCube[t_side[0]][2] = rubicsCube[t_side[3]][3];
                rubicsCube[t_side[3]][3] = rubicsCube[t_side[2]][1];
                rubicsCube[t_side[2]][1] = rubicsCube[t_side[1]][0];
                rubicsCube[t_side[1]][0] = temp;
                temp = rubicsCube[t_side[0]][3];
                rubicsCube[t_side[0]][3] = rubicsCube[t_side[3]][1];
                rubicsCube[t_side[3]][1] = rubicsCube[t_side[2]][0];
                rubicsCube[t_side[2]][0] = rubicsCube[t_side[1]][2];
                rubicsCube[t_side[1]][2] = temp;
            }
            else if (side_to_rotate == e_back)
            {
                temp = rubicsCube[t_side[0]][1];
                rubicsCube[t_side[0]][1] = rubicsCube[t_side[3]][3];
                rubicsCube[t_side[3]][3] = rubicsCube[t_side[2]][2];
                rubicsCube[t_side[2]][2] = rubicsCube[t_side[1]][0];
                rubicsCube[t_side[1]][0] = temp;

                temp = rubicsCube[t_side[0]][0];
                rubicsCube[t_side[0]][0] = rubicsCube[t_side[3]][1];
                rubicsCube[t_side[3]][1] = rubicsCube[t_side[2]][3];
                rubicsCube[t_side[2]][3] = rubicsCube[t_side[1]][2];
                rubicsCube[t_side[1]][2] = temp;
            }
            else if (side_to_rotate == e_right)
            {
                temp = rubicsCube[t_side[0]][3];
                rubicsCube[t_side[0]][3] = rubicsCube[t_side[3]][3];
                rubicsCube[t_side[3]][3] = rubicsCube[t_side[2]][3];
                rubicsCube[t_side[2]][3] = rubicsCube[t_side[1]][0];
                rubicsCube[t_side[1]][0] = temp;
                temp = rubicsCube[t_side[0]][1];
                rubicsCube[t_side[0]][1] = rubicsCube[t_side[3]][1];
                rubicsCube[t_side[3]][1] = rubicsCube[t_side[2]][1];
                rubicsCube[t_side[2]][1] = rubicsCube[t_side[1]][2];
                rubicsCube[t_side[1]][2] = temp;
            }
            else if (side_to_rotate == e_left)
            {
                temp = rubicsCube[t_side[0]][0];
                rubicsCube[t_side[0]][0] = rubicsCube[t_side[3]][3];
                rubicsCube[t_side[3]][3] = rubicsCube[t_side[2]][0];
                rubicsCube[t_side[2]][0] = rubicsCube[t_side[1]][0];
                rubicsCube[t_side[1]][0] = temp;
                temp = rubicsCube[t_side[0]][2];
                rubicsCube[t_side[0]][2] = rubicsCube[t_side[3]][1];
                rubicsCube[t_side[3]][1] = rubicsCube[t_side[2]][2];
                rubicsCube[t_side[2]][2] = rubicsCube[t_side[1]][2];
                rubicsCube[t_side[1]][2] = temp;
            }
        }
    }

private:
    array<color,4> rubicsCube[6];
};

#endif /// RUBIKS_CUBE_SRC_RUBIKS_CUBE_H.



int main(){
    rubiks_cube obj;
    std::array<rubiks_cube::color,4> abc;
    obj.rotate_side(rubiks_cube::side::e_top,1);
    for (int i=0;i<4;++i) {
        if (i == 0) {
            abc = obj.get_side(rubiks_cube::side::e_front);
        } else if (i == 1) {
            abc = obj.get_side(rubiks_cube::side::e_left);
        } else if (i == 2) {
            abc = obj.get_side(rubiks_cube::side::e_back);;
        } else if (i == 3) {
            abc = obj.get_side(rubiks_cube::side::e_right);
        }
        for (int f = 0; f < 4; ++f) {
            if (abc[f] == 0) {
                std::cout << "w ";
            } else if (abc[f] == 1) {
                std::cout << "r ";
            } else if (abc[f] == 2) {
                std::cout << "g ";
            } else if (abc[f] == 3) {
                std::cout << "o ";
            } else if (abc[f] == 4) {
                std::cout << "b ";
            } else if (abc[f] == 5) {
                std::cout << "y ";
            }
        }
        std::cout << std::endl;
    }
}

