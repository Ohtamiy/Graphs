#ifndef EDGE_H
#define EDGE_H

#include <namespace.h>

class Edge
{
    id id_, in, out;

public:
    Edge(id id_, id in, id out){
        this->id_ = id_;
        this->in = in;
        this->out = out;
    }

    id getId() const { return id_; }
    id getIn() const { return in; }
    id getOut() const { return out; }

    void setId(id id_) { this->id_ = id_; }
    void setIn(id in) { this->in = in; }
    void setOut(id out) { this->out = out;}
};

#endif // EDGE_H
