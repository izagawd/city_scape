#pragma once
#include "GL/glew.h"


struct Color{

    GLubyte colorBytes[4];


    Color() : Color(0,0,0,255){

    }
    Color(GLubyte r, GLubyte g, GLubyte b, GLubyte opacity){
        colorBytes[0] = r;
        colorBytes[1] = g;
        colorBytes[2] = b;
        colorBytes[3] = opacity;
    }
};
