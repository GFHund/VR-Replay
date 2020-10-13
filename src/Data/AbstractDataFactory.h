#ifndef __ABSTRACT_DATA_FACTORY__
#define __ABSTRACT_DATA_FACTORY__
class AbstractDataFactory{
    virtual Data* buildData(char* blob) = 0;
};
#endif