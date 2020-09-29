#ifndef EDGE_H
#define EDGE_H

#include <namespace.h>

class Edge
{
    id id_;
    coordinate in, out;

public:
    Edge();
    Edge(id id_, coordinate in, coordinate out){
        this->id_ = id_;
        this->in = in;
        this->out = out;
    }

    id getId() const { return id_; }
    coordinate getIn() const { return in; }
    coordinate getOut() const { return out; }

    void setId(id id_) { this->id_ = id_; }
    void setIn(coordinate in) { this->in = in; }
    void setOut(coordinate out) { this->out = out;}
};

#endif // EDGE_H
