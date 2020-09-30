#include "nodesmap.h"

id NodesMap::getPos(id id_){
    id counter = 0;
    for(auto i = begin(); i != end(); i++, counter++)
        if(i->getId() == id_)
            return counter;
    return 0;
}
