#ifndef FIELD_HPP
#define FIELD_HPP

#include "Configs.hpp"


//-- Field Class
class Field {
    private:
        Mat Ground;
    public:
        Field();
        void fieldCreate();
        Mat Access();
};

#endif // FIELD_HPP