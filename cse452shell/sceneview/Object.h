//
//  Object.h
//  cse452shellXC
//
//  Created by Ben Stolovitz on 4/1/15.
//  Copyright (c) 2015 bstolovitz. All rights reserved.
//

#ifndef __cse452shellXC__Object__
#define __cse452shellXC__Object__

#include <stdio.h>
#ifdef __APPLE__
// because Apple is stupid and I hate everyone
#include <OpenGL/glu.h>
#else
#include <Windows.h>
#include <GL/glu.h>
#endif

#include "Color.h"

#include "IDrawable.h"
#include "../shapes/Shape.h"

class Object : public IDrawable {
    public:
        Object()
        : _valid(false) {};
        Object(Shape* shape)
        : _shape(shape), _valid(true) {};
    
        ~Object();
    
        bool isValid() const;
        Object* setShape(Shape* shape);
    
        void draw() const;
    
        Color ambient = Color(0.2, 0.2, 0.2);
        Color diffuse = Color(0.8, 0.8, 0.8);
        Color specular = Color(0, 0, 0);
        Color emission = Color(0, 0, 0);
        Color reflect = Color(0, 0, 0);
        Color transparent = Color(0, 0, 0);
        GLfloat ior = 0.0;
        GLfloat shininess = 0.0;
    
        std::string textureFile;
        double textureU;
        double textureV;
    
    private:
        bool _valid = false;
        const Shape* _shape;
};

#endif /* defined(__cse452shellXC__Object__) */
