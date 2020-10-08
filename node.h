#ifndef NODE_H
#define NODE_H

#include <namespace.h>

class Node
{
    id id_;
    coordinate x, y;

public:
    Node(id id_, coordinate x, coordinate y){
        this->id_ = id_;
        this->x = x;
        this->y = y;
    }

    // const isn't required but it shows that the method isn't changing class objects
    inline id getId() const { return id_; }
    inline coordinate getX() const { return x; }
    inline coordinate getY() const { return y; }

    inline void setX(const coordinate x) { this->x = x; }
    inline void setY(const coordinate y) { this->y = y; }
};

#endif // NODE_H
