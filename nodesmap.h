#ifndef NODESMAP_H
#define NODESMAP_H

#include <namespace.h>
#include <node.h>

class NodesMap : public vector<Node>
{
public:
    id getPos(const id id_);
    id newIndex();
    NodesMap::iterator findToInsert(const id id_);
};

#endif // NODESMAP_H
