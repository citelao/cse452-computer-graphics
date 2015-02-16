//
//  Cube.h
//  cse452shellXC
//
//  Created by Ben Stolovitz on 2/15/15.
//  Copyright (c) 2015 bstolovitz. All rights reserved.
//

#ifndef __cse452shellXC__Cube__
#define __cse452shellXC__Cube__

#ifdef __APPLE__
// because Apple is stupid and I hate everyone
#include <OpenGL/glu.h>
#else
#include <GL/glu.h>
#endif

#include <stdio.h>
#include <vector>
#include <cmath>
#include "Shape.h"
#include "../vecmath/Vector3.h"

class Cube : public Shape {
public:
    Cube(int topdiv, int sidediv);
    void draw();
    
private:
    std::vector<Vector3> pts;
    std::vector<int> indeces;
    
    int topdiv;
    int sidediv;
};

#endif /* defined(__cse452shellXC__Cube__) */