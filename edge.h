#ifndef EDGE_H
#define EDGE_H

#include <namespace.h>

class Edge
{
    id id_, in, out;
    bool colour;

public:
    Edge(id id_, id in, id out, bool colour){
        this->id_ = id_;
        this->in = in;
        this->out = out;
        this->colour = colour;
    }

    inline id getId() const { return id_; }
    inline id getIn() const { return in; }
    inline id getOut() const { return out; }
    inline bool getColour() const { return colour; }

    inline void setIn(id in) { this->in = in; }
    inline void setOut(id out) { this->out = out; }
    inline void setId(id id_) { this->id_ = id_; }
    inline void setColour(bool colour) { this->colour = colour; }
};

#endif // EDGE_H
