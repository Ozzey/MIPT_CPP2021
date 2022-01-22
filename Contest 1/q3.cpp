#include <iostream>
#include <vector>


struct coordinates {
public:
    int x, y;

    coordinates(int x, int y) {
        this->x = x;
        this->y = y;
    }

    coordinates(coordinates const &other) {
        this->x = other.x;
        this->y = other.y;
    }

    coordinates& operator=(const coordinates& other) {
        this->x = other.x;
        this->y = other.y;
        return *this;
    }

    ~coordinates() {}
private:
    coordinates() = default;

};

class robot {
public:
    enum direction {
        e_up,
        e_right,
        e_down,
        e_left
    };


    robot(int n, const std::vector<coordinates>& coord) {
        this->coord = coord;
        this->n = n;
    }

    void try_move () {
        if(dir == e_up) {
            for(const auto& i: coord) {
                if(((i.x == current.x) && (i.y == current.y+1)) || ((current.y+1 < 0) || (current.y+1 >= n))) {
                    return;
                }
            }
            current.y = current.y+1;
        }

        if(dir == e_down) {
            for(const auto& i: coord) {
                if(((i.x == current.x) && (i.y == current.y-1)) || ((current.y-1 < 0) || (current.y-1 >= n))) {
                    return;
                }
            }
            current.y = current.y-1;
        }

        if(dir == e_left) {
            for(const auto& i: coord) {
                if(((i.x == current.x-1) && (i.y == current.y)) || ((current.x-1 < 0) || (current.x-1 >= n))) {
                    return;
                }
            }
            current.x = current.x-1;
        }

        if(dir == e_right) {
            for(const auto& i: coord) {
                if(((i.x == current.x+1) && (i.y == current.y)) || ((current.x+1 < 0) || (current.x+1 >= n))) {
                    return;
                }
            }
            current.x = current.x+1;
        }
    }

    void set_direction(direction dirr) {
        this->dir = dirr;
    }

    const coordinates& get_coordinates () const {
        return current;
    }

    direction get_direction () const {
        return dir;
    }

    ~robot() = default;

private:
    int n;
    direction dir = e_up;
    std::vector<coordinates> coord;
    coordinates current = {0, 0};
    robot() = default;
};

int main() {
    robot r1(7, {{3,6}, {4,5}, {1,4},{2,3},{5,2},{0,1},{6,0},{3,4},{6,6}});

    r1.set_direction(robot::direction::e_right);
    r1.try_move();
    r1.try_move();
    r1.set_direction(robot::direction::e_up);
    r1.try_move();
    r1.try_move();
    r1.try_move();
    r1.set_direction(robot::direction::e_left);
    r1.try_move();
    r1.try_move();
    r1.set_direction(robot::direction::e_up);
    r1.try_move();
    r1.try_move();
    r1.set_direction(robot::direction::e_right);
    r1.try_move();
    r1.set_direction(robot::direction::e_up);
    r1.try_move();
    r1.set_direction(robot::direction::e_right);
    r1.try_move();
    r1.try_move();
    r1.set_direction(robot::direction::e_up);
    r1.try_move();
    r1.try_move();
    r1.try_move();

    coordinates coords = r1.get_coordinates();

    std::cout<< "(" << coords.x <<","<< coords.y<<")" << std::endl;
    /*
    robot r1(2, {});
    std::cout << r1.get_coordinates().print() << std::endl;
    r1.set_direction(robot::e_down);
    r1.try_move();
    std::cout << r1.get_coordinates().print() << std::endl;
    r1.set_direction(robot::e_right);
    r1.try_move();
    std::cout << r1.get_coordinates().print() << std::endl;
    r1.set_direction(robot::e_up);
    r1.try_move();
    std::cout << r1.get_coordinates().print() << std::endl;
    r1.try_move();
    std::cout << r1.get_coordinates().print() << std::endl;
    r1.set_direction(robot::e_left);
    r1.try_move();
    std::cout << r1.get_coordinates().print() << std::endl;*/

    // robot r1(7, {3,6}, {4,5}, {1,4},{2,3},{5,2},{0,1},{6,0},{3,4},{6,6}});
    return 0;
}
