//
//  Cone.h
//  cse452shellXC
//
//  Created by Ben Stolovitz on 2/15/15.
//  Copyright (c) 2015 bstolovitz. All rights reserved.
//

#ifndef __cse452shellXC__Cone__
#define __cse452shellXC__Cone__

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

class Cone : public Shape {
public:
    Cone(int topdiv = 10, int sidediv = 2);
    void draw() const;
    
private:
    std::vector<std::vector<Vector3> > pts;
    
    int sidediv;
};

#endif /* defined(__cse452shellXC__Cone__) */
