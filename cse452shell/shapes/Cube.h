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
#include <Windows.h>
#include <GL/glu.h>
#endif

#include <stdio.h>
#include <vector>
#include <cmath>
#include "Shape.h"
#include "../vecmath/Vector3.h"

class Cube : public Shape {
public:
    Cube(int topdiv = 2, int sidediv = 0);
    void draw();
    
private:
    void subdivide(Vector3 tl, Vector3 tr, Vector3 bl, Vector3 br, Vector3 norm, int depth);
    
    std::vector<Vector3> basis;
    std::vector<Vector3> pts;
    std::vector<Vector3> normals;
    std::vector<int> indeces;
    
    int topdiv;
    int sidediv;
};

#endif /* defined(__cse452shellXC__Cube__) */
