#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <utility>
# define PI 3.14159265358979323846

const double EPS = 1e-6;

bool equal(double a, double b){return std::fabs(a - b) < EPS;}


//------------------VECTOR------------//

struct vector{
    double x, y;

    vector(double x, double y):x(x), y(y){}
    vector(): x(0.0), y(0.0){}
    vector(const vector& other){
        x = other.x;
        y = other.y;
    }

    double length() { return sqrt(pow(x, 2) + pow(y, 2)); }
    double length() const { return sqrt(pow(x, 2) + pow(y, 2)); }

    vector& operator+= (const vector& other){
        x += other.x;
        y += other.y;
        return *this;
    }
    vector& operator-= (const vector& other){
        x -= other.x;
        y -= other.y;
        return *this;
    }
    vector& operator*= (const vector& other){
        x *= other.x;
        y *= other.y;
        return *this;
    }
    vector& operator+= (double scalar){
        x += scalar;
        y += scalar;
        return *this;
    }
    vector& operator-= (double scalar){
        x -= scalar;
        y -= scalar;
        return *this;
    }
    vector& operator*= (double scalar){
        x *= scalar;
        y *= scalar;
        return *this;
    }
    vector& operator/= (double scalar){
        x /= scalar;
        y /= scalar;
        return *this;
    }
    vector operator+ ()const{
        return *this;
    }
    vector operator- ()const{
        vector temp(*this);
        temp.x = -temp.x;
        temp.y = -temp.y;
        return temp;
    }

};

vector operator+ (const vector& first, double scalar) {
    return vector(first) += scalar;
}
vector operator- (const vector& first, double scalar) {
    return vector(first) -= scalar;
}
vector operator* (const vector& first, const double scalar) {
    return vector(first) *= scalar;
}
vector operator* (double scalar, const vector& first) {
    return vector(first) *= scalar;
}
vector operator/ (const vector& first, double scalar) {
    return vector(first) /= scalar;
}
vector operator+ (const vector& first, const vector& second) {
    return vector(first) += second;
}
vector operator- (const vector& first, const vector& second) {
    return vector(first) -= second;
}
vector operator* (const vector& first, const vector& second) {
    return vector(first) *= second;
}

bool operator == (const vector& first, const vector& second) {
    return equal(first.x, second.x) &&
           equal(first.y, second.y);
}
bool operator == (const vector& first, vector& second) {
    return equal(first.x, second.x) &&
           equal(first.y, second.y);
}
bool operator != (const vector& first, const vector& second) {
    return !(first == second);
}

double dot_product(const vector& lhs, const vector& rhs) {
    return (lhs.x * rhs.x) + (lhs.y * rhs.y);
}
double cross_product(const vector& lhs, const vector& rhs){
    double det = (lhs.x * rhs.y) - (lhs.y * rhs.x);
    return det;
}
bool collinear(const vector& lhs, const vector& rhs){
    return equal((lhs.y * rhs.x), (rhs.y * lhs.x));
}
double distance(const vector& first, const vector& second){
    return std::sqrt(std::pow(first.x-second.x,2)+
                     std::pow(first.y-second.y,2));
}

//------------------SHApe-------------//
class shape{

public:

    //const methods
    virtual vector center() const = 0;
    virtual double perimeter() const = 0;
    virtual double area() const = 0;

    virtual bool operator==(const shape& another) const = 0;
    virtual bool operator!=(const shape& another) const = 0;

    virtual bool congruent_to(const shape &another) const = 0;

    //non const methods
    virtual void rotate(double angle) = 0;
    virtual void scale(double coefficient) = 0;
    virtual void translate(vector transform) = 0;
};

//------------------CIRCLE------------//

class circle : virtual public shape{

public:

    circle():centre_(),radius_(){};
    circle(const vector& cent, double rad):centre_(cent),radius_(rad){};

    //CONST METHODS
    const double radius() const {return radius_;}
    //for more precision while checking for equality
    static bool equal_center(const vector& circle_a, const vector& circle_b) {
        bool x_equal = std::fabs(circle_a.y - circle_b.y) < EPS;
        bool y_equal = std::fabs(circle_a.x - circle_b.x) < EPS;
        return x_equal && y_equal;
    }
    double perimeter() const override {
        return 2*PI*radius_;
    }
    double area() const override {
        return PI*pow(radius_,2);
    }
    vector center() const override {
        return centre_;
    }
    bool congruent_to(const shape& another) const override {
        if (typeid(another) == typeid(*this)) {
            const auto &other = dynamic_cast<const circle &>(another);
            return std::fabs(radius_ - other.radius_) < EPS;
        }
        return false;
    }

    //NON CONST METHODS
    void rotate(double angle) override {}
    void scale(double coefficient )override {
        radius_*= fabs(coefficient);
    }
    void translate(vector transform) override {
        centre_.x+=transform.x; centre_.y+=transform.y;
    }

    //BOOL OPERATORS
    bool operator== (const shape& another) const override {
        if(typeid(another)== typeid(*this)){
            const auto& other = dynamic_cast<const circle&>(another);
            return centre_==other.centre_ && std::fabs(radius_ - other.radius_) < EPS;
        }
        return false;
    }
    bool operator!= (const shape& another) const override {
        return !(*this == another);
    }

private:
    vector centre_;
    double radius_;
};

//----------------POLYGON--------------//
class polygon: virtual public shape{

public:
    polygon() = default;
    ~polygon() = default;
    explicit polygon(std::vector<vector> vectors){
        if(signed_area(vectors)<0){
            for(size_t s = 0; s < vectors.size(); s++)
                vertices_.push_back(vectors[vectors.size()-s-1]);
        } else {
            for(const auto& element: vectors)
                vertices_.push_back(element);
        }
    }

    //CONST METHODS
    const size_t vertices_count() const {return vertices_.size();}
    const std::vector<vector>& get_vertices() const {return vertices_;}
    vector center() const override{
        vector center;
        for (size_t s = 0;  s < vertices_.size() ; s++){
            center.x+=(vertices_[s].x + vertices_[(s+1)%vertices_.size()].x)*
                      (vertices_[s].x*vertices_[(s+1)%vertices_.size()].y
                       -vertices_[s].y*vertices_[(s+1)%vertices_.size()].x);

            center.y+=(vertices_[s].y + vertices_[(s+1)%vertices_.size()].y)*
                      (vertices_[s].x*vertices_[(s+1)%vertices_.size()].y-
                       vertices_[s].y*vertices_[(s+1)%vertices_.size()].x);
        }
        center*=(1/(6*signed_area(vertices_)));
        return center;
    }
    double perimeter() const override {
        double dist;
        double perimeter = 0.0;
        for (int i = 0; i < vertices_.size()-1; i++) {
            dist = sqrt(pow(vertices_[i + 1].x - vertices_[i].x, 2) +
                        pow(vertices_[i + 1].y - vertices_[i].y, 2));
            perimeter += dist;
        }
        dist = sqrt(pow(vertices_[0].x - vertices_[vertices_.size()-1].x, 2) +
                    pow(vertices_[0].y - vertices_[vertices_.size()-1].y, 2));
        perimeter += dist;
        return perimeter;
    }
    double area() const override {
        double area=0.0;
        for (size_t i = 0; i < vertices_.size() ; ++i) {
            area+= cross_product(vertices_[i], (vertices_[(i+1)%vertices_.size()]));
        }
        return fabs(area/2);
    }
    bool congruent_to(const shape & other) const override {
        const auto* another = dynamic_cast<const polygon*>(&other);
        std::vector<vector> vec_a(vertices_.size()), vec_b(vertices_.size());
        for (int i = 0; i < vertices_.size(); i++){
            vec_a[i] = vector(vertices_[i] - vertices_[(i + 1) % vertices_.size()]);

            vec_b[i] = vector(another->vertices_[i] - another->vertices_[(i + 1) % vertices_.size()]);
        }

        for (int j = 0; j < vertices_.size(); j++)
            if (equal(vec_a[0].length(), vec_b[j].length())) {
                for (int i = 0; i < vertices_.size(); i++) {
                    if (similarUp(vec_a, vec_b, i, j)) { break; }
                    if (i + 1 == vertices_.size()) { return true; }
                }

                for (int i = 0; i < vertices_.size(); i++) {

                    if (similarDown(vec_a, vec_b, i, j)) { break; }

                    if (i + 1 == vertices_.size()) { return true; }
                }
            }
        return false;
    }

    //NON CONST METHODS
    void rotate(double angle) override {
        double center_x= center().x, new_x;
        double center_y= center().y, new_y;
        for (auto & vertice : vertices_){
            new_x=center_x+ (((vertice.x -center_x) * cos(angle)) -
                             ((vertice.y - center_y) * sin(angle)));
            new_y =center_y+(((vertice.x - center_x) * sin(angle)) +
                             ((vertice.y - center_y) * cos(angle)));

            vertice.x = new_x;
            vertice.y = new_y;
        }
    }
    void scale(double coefficient) override {
        double center_x= center().x;
        double center_y= center().y;
        for (auto & vertice : vertices_){
            vertice.x = center_x + coefficient*(vertice.x - center_x);
            vertice.y = center_y + coefficient*(vertice.y - center_y);
        }
    }
    void translate(vector transform) override {
        for(vector& vert: vertices_){
            vert.x += transform.x;
            vert.y += transform.y;
        }
    }

    //BOOL FUNCTIONS//
    bool operator==(const shape& another) const override {
        const auto* cpy = dynamic_cast<const polygon*>(&another);
        if(cpy== nullptr)
            return false;
        if (vertices_count()!=cpy->vertices_count())
            return false;

        for(size_t s = 0; s < vertices_count();s++){
            for(size_t t = 0; t < vertices_count(); t++)
                if (vertices_[s]==cpy->vertices_[t])
                    break ;
                else if (vertices_[s] != cpy->vertices_[t] && t == vertices_count()-1)
                    return false;
        }

        return true ;
    }
    bool operator!=(const shape& another) const override {
        return !(*this == another);
    }

    //USEFUL METHODS
    bool similarUp(std::vector<vector> vec_a,std::vector<vector> vec_b, int i, int j) const {
        int ind= j - i;
        bool condition =
                (std::fabs(vec_a[i].length()-
                           vec_b[(ind + vertices_.size()) % vertices_.size()].length()) > EPS) or

                (std::fabs(vec_a[(i + 1) % vertices_.size()].length()-
                           vec_b[(ind - 1 + vertices_.size()) % vertices_.size()].length()) > EPS) or

                (std::fabs(std::fabs(cross_product(vec_a[i], vec_a[(i + 1) % vertices_.size()])) -
                           std::fabs(cross_product(vec_b[(ind + vertices_.size()) % vertices_.size()],
                                                   vec_b[(ind - 1 + vertices_.size()) % vertices_.size()]))) > EPS) ;

        return condition;
    }
    bool similarDown(std::vector<vector> vec1, std::vector<vector> vec2, int i, int j) const {
        int ind = i + j;
        bool condition =
                (std::fabs(vec1[i].length() - vec2[(i + j) % vertices_.size()].length()) > EPS ) or

                (std::fabs(vec1[(i + 1) % vertices_.size()].length() -
                           vec2[(ind + 1) % vertices_.size()].length()) > EPS ) or

                (std::fabs(std::fabs(cross_product(vec1[i], vec1[(i + 1) % vertices_.size()])) -
                           std::fabs(cross_product(vec2[(ind) % vertices_.size()],
                                                   vec2[(ind + 1) % vertices_.size()]))) > EPS ) ;

        return condition;
    }

protected:
    std::vector<vector> vertices_;

private:
    double signed_area(const std::vector<vector> &vectors) const {
        double sum_cross_product=0.;
        for (size_t t = 0;  t < vectors.size(); t++)
            sum_cross_product+=cross_product(
                    vectors[t],vectors[(t+1)%vectors.size()]);
        return sum_cross_product/2;
    }

};
//-----------------------RECTANGLE---------------------------//

class rectangle:public polygon{

public:
    rectangle()=default;
    rectangle(vector const& center,double const height,double width):
            center_(center),width_(width),height_(height){
        vertices_.emplace_back(center.x-(width_/2),center.y+(height_/2));
        vertices_.emplace_back(center.x+(width_/2),center.y+(height_/2));
        vertices_.emplace_back(center.x+(width_/2),center.y-(height_/2));
        vertices_.emplace_back(center.x-(width_/2),center.y-(height_/2));
    }
    rectangle(const rectangle& other)= default;
    ~rectangle()= default;
    rectangle& operator= (const rectangle& other)= default;

    //CONST METHODS
    const double height() const {
        return height_;
    }
    const double width() const {
        return width_;
    }

protected:
    double width_;
    vector center_;

private:
    double height_;
};

//----------------------------SQUARE-------------------------//

class square:public rectangle{

public:
    square(const vector& center,double side):rectangle(center,side,side){}
    square(const square& other)= default;
    ~square()= default;
    square& operator= (const square& other)= default;

    //CONST METHODS
    circle circumscribed_circle() const {
        return circle(center_,width_/std::sqrt(2));
    }
    circle inscribed_circle() const {
        return circle(center_,width_/2);
    }
    const double side() const {
        return width();
    }
};

//----------------------------TRIANGLE-------------------------//
class triangle :public polygon{

public:
    triangle() = default;
    triangle(const vector& _from,const vector& _to,const vector& _then_to){
        vertices_.push_back(_from);
        vertices_.push_back(_to);
        vertices_.push_back(_then_to);
    }
    triangle(const triangle& other)= default;
    ~triangle()= default;
    triangle& operator=(const triangle& other)= default;

    //CONST METHODS: inscribed and circumscribed circles
    circle circumscribed_circle() const {
        vector center_circumscribed;
        double Diameter(0);
        for (size_t t = 0;  t < vertices_.size() ; t++) {
            Diameter+=2*vertices_[t].x*(vertices_[(t+1)%vertices_.size()].y
                                        -vertices_[(t+2)%vertices_.size()].y);

            center_circumscribed.x+=(std::pow(vertices_[t].x,2)
                                     +std::pow(vertices_[t].y,2))
                                    *(vertices_[(t+1)%vertices_.size()].y
                                      -vertices_[(t+2)%vertices_.size()].y);

            center_circumscribed.y+=(std::pow(vertices_[t].x,2)
                                     +std::pow(vertices_[t].y,2))
                                    *(vertices_[(t+2)%vertices_.size()].x
                                      -vertices_[(t+1)%vertices_.size()].x);
        }
        center_circumscribed*=(1/Diameter);
        double radius_circumscribed(1/(4*area()));

        for (size_t t = 0;  t < vertices_.size() ; t++)
            radius_circumscribed *= distance(vertices_[t],
                                             vertices_[(t + 1) % vertices_.size()]);

        circle circumscribed(center_circumscribed,radius_circumscribed);
        return circumscribed;
    }
    circle inscribed_circle() const {
        vector center_inscribed;
        double distances_sum=0;
        for (size_t t = 0;  t < vertices_.size(); t++) {

            center_inscribed+= vertices_[t]
                               *distance(vertices_[(t + 1) % vertices_.size()],
                                         vertices_[(t + 2) % vertices_.size()]);

            distances_sum+=distance(vertices_[t],
                                    vertices_[(t+1)%vertices_.size()]);
        }
        center_inscribed/=distances_sum;
        circle inscribed(center_inscribed, 2*area()/perimeter());
        return inscribed;
    }

};

//-----------------------------------------------------//

