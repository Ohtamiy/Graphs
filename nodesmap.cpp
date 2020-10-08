#include "nodesmap.h"

id NodesMap::getPos(const id id_){
    id counter = 0;
    for(auto i = begin(); i != end(); i++, counter++)
        if(i->getId() == id_)
            return counter;
    return 0;
}

id NodesMap::newIndex(){
    if(size() == 0) return 0;
    for(id i = 0; i < size() - 1; ++i)
        if(at(i).getId() + 1 < at(i+1).getId())
            return at(i).getId() + 1;
    return rbegin()->getId() + 1;
}

NodesMap::iterator NodesMap::findToInsert(const id id_){
    for(auto i = begin(); i != end(); i++)
        if(i->getId() + 1 == id_)
            return ++i;
    return begin();
}
