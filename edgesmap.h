#ifndef EDGESMAP_H
#define EDGESMAP_H

#include <namespace.h>
#include <edge.h>

class EdgesMap : public vector<Edge>
{
public:
    id getPos(const id id_);
    id newIndex();
    EdgesMap::iterator findToInsert(const id id_);
};

#endif // EDGESMAP_H
