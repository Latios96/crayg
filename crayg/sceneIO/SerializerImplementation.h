//
// Created by Jan Honsbrok on 01.11.18.
//

#ifndef CRAYG_SERIALIZERIMPLEMENTATION_H
#define CRAYG_SERIALIZERIMPLEMENTATION_H

#include "Serializable.h"

class SerializerImplementation : public Serializer{
public:
    /*explicit SerializerImplementation(const std::string &path);*/
    virtual void init()=0;
    virtual void startObject()=0;
    virtual void endObject()=0;
    virtual void finish()=0;
};

/*SerializerImplementation::SerializerImplementation(const std::string &path) {

}*/

#endif //CRAYG_SERIALIZERIMPLEMENTATION_H
