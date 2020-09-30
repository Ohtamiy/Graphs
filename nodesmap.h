#ifndef NODESMAP_H
#define NODESMAP_H

#include <namespace.h>
#include <node.h>

class NodesMap : public vector<Node>
{
public:
    id getPos(id id_);
};

#endif // NODESMAP_H
