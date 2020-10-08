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

    inline id getId() const { return id_; }
    inline id getIn() const { return in; }
    inline id getOut() const { return out; }

    inline void setIn(id in) { this->in = in; }
    inline void setOut(id out) { this->out = out; }
};

#endif // EDGE_H
