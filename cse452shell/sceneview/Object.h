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
    
    private:
        bool _valid = false;
        const Shape* _shape;
};

#endif /* defined(__cse452shellXC__Object__) */
