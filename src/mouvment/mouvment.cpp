#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

template <class T>
class vec2 {
public:
    T x, y;
    
    vec2() :x(0), y(0) {}
    vec2(T x, T y) : x(x), y(y) {}
    vec2(const vec2& v) : x(v.x), y(v.y) {}
    
    vec2& operator=(const vec2& v) {
        x = v.x;
        y = v.y;
        return *this;
    }
    
    vec2 operator+(vec2& v) {
        return vec2(x + v.x, y + v.y);
    }
    vec2 operator-(vec2& v) {
        return vec2(x - v.x, y - v.y);
    }
    
    vec2& operator+=(vec2& v) {
        x += v.x;
        y += v.y;
        return *this;
    }
    vec2& operator-=(vec2& v) {
        x -= v.x;
        y -= v.y;
        return *this;
    }
    
    vec2 operator+(double s) {
        return vec2(x + s, y + s);
    }
    vec2 operator-(double s) {
        return vec2(x - s, y - s);
    }
    vec2 operator*(double s) {
        return vec2(x * s, y * s);
    }
    vec2 operator/(double s) {
        return vec2(x / s, y / s);
    }
    
    vec2& operator+=(double s) {
        x += s;
        y += s;
        return *this;
    }
    vec2& operator-=(double s) {
        x -= s;
        y -= s;
        return *this;
    }
    vec2& operator*=(double s) {
        x *= s;
        y *= s;
        return *this;
    }
    vec2& operator/=(double s) {
        x /= s;
        y /= s;
        return *this;
    }

    bool operator == ( const vec2& v ) const {
        return ( x == v.x ) && ( y == v.y );
    }

    bool operator != ( const vec2& v ) const {
        return ( x != v.x ) || ( y != v.y );
    }
    
    void set(T x, T y) {
        this->x = x;
        this->y = y;
    }
    
    void rotate(double deg) {
        double theta = deg / 180.0 * M_PI;
        double c = cos(theta);
        double s = sin(theta);
        double tx = x * c - y * s;
        double ty = x * s + y * c;
        x = tx;
        y = ty;
    }
    
    vec2& normalize() {
        if (length() == 0) return *this;
        *this *= (1.0 / length());
        return *this;
    }
    
    float dist(vec2 v) const {
        vec2 d(v.x - x, v.y - y);
        return d.length();
    }
    float length() const {
        return std::sqrt(x * x + y * y);
    }
    void truncate(double length) {
        double angle = atan2f(y, x);
        x = length * cos(angle);
        y = length * sin(angle);
    }
    
    vec2 ortho() const {
        return vec2(y, -x);
    }
    
    static float dot(vec2 v1, vec2 v2) {
        return v1.x * v2.x + v1.y * v2.y;
    }
    static float cross(vec2 v1, vec2 v2) {
        return (v1.x * v2.y) - (v1.y * v2.x);
    }
};

typedef vec2<float> vec2f;
typedef vec2<double> vec2d;
typedef vec2<int> vec2i;

constexpr int epsilon = 3000;

class Pod
{
public:
    Pod() :
    position{},
    target{},
    boostAvailable{true},
    allCheckpointFound{false},
    maxDistance{}
    {}

bool UseBoost(bool boostAsked, int currentDistance)
{
    if(!boostAvailable)
    {
        return false;
    }

    if(boostAsked && currentDistance + epsilon > maxDistance)
    {
        boostAvailable = false;
        cerr << "USE BOOST" << endl;
        return true;
    }

    return false;
}

void AddCheckpoint(vec2i position, int distance)
{
    if(allCheckpointFound)
    {
        return;
    }
    
    const vec2 newCheckpoint(position);
    
    if(checkpoints.empty())
    {
        checkpoints.push_back(newCheckpoint);
    }
    else if(checkpoints.back() != newCheckpoint)
    {
        checkpoints.push_back(newCheckpoint);

        if(checkpoints.front() == newCheckpoint)
        {
            allCheckpointFound = true;  
        }

        if(maxDistance < distance)
        {
            maxDistance = distance;
        }
    }
}

void Out(vec2i position, int thrust, bool boostAsked = false)
{
    bool useBoost = UseBoost(boostAsked, currentDistance);
    cout << position.x << " " << position.y << " ";
    cerr << "BOOST AVALAIBLE : " << boostAvailable << endl;
    if(useBoost)
    {
        cout << "BOOST";
    }
    else 
    {
        cout << thrust;
    }
    cout << endl;
}

void Update()
{
    cin >> position.x >> position.y >> target.x >> target.y >> currentDistance >> targetAngle; cin.ignore();
    int opponentX;
    int opponentY;
    cin >> opponentX >> opponentY; cin.ignore();

    AddCheckpoint(target, currentDistance);

    if(targetAngle > 90 || targetAngle < -90)
    {
        Out(target, 0);
    }
    else
    {
        if(allCheckpointFound && currentDistance + epsilon > maxDistance)
        {
            Out(target, 100, true);
        }
        else
        {
            Out(target, 100);
        }
    }

}

private:
    vector<vec2i> checkpoints;
    vec2i position;
    vec2i target;
    int maxDistance;
    int currentDistance;
    int targetAngle;
    bool boostAvailable : 1;
    bool allCheckpointFound : 1;
};

int main()
{
    Pod pod;

    // game loop
    while (1)
    {
        pod.Update();
    }
}