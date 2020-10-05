#ifndef EDGESMAP_H
#define EDGESMAP_H

#include <namespace.h>
#include <edge.h>

class EdgesMap : public vector<Edge>
{
public:
    id getPos(id id_);
};

#endif // EDGESMAP_H
