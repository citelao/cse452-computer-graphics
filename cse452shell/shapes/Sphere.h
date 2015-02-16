//
//  Sphere.h
//  cse452shellXC
//
//  Created by Ben Stolovitz on 2/16/15.
//  Copyright (c) 2015 bstolovitz. All rights reserved.
//

#ifndef __cse452shellXC__Sphere__
#define __cse452shellXC__Sphere__

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

class Sphere : public Shape {
public:
    Sphere(int topdiv, int sidediv);
    void draw();
    
private:
    std::vector<std::vector<Vector3> > pts;
};

#endif /* defined(__cse452shellXC__Sphere__) */
