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
    id getId() const { return id_; }
    coordinate getX() const { return x; }
    coordinate getY() const { return y; }

    void setId(id id_) { this->id_ = id_; }
    void setX(coordinate x) { this->x = x; }
    void setY(coordinate y) { this->y = y; }
};

#endif // NODE_H
