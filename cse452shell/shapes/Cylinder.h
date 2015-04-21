//
//  Cylinder.h
//  cse452shellXC
//
//  Created by Ben Stolovitz on 2/15/15.
//  Copyright (c) 2015 bstolovitz. All rights reserved.
//

#ifndef __cse452shellXC__Cylinder__
#define __cse452shellXC__Cylinder__

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
#include "../intersection/HitRecord.h"
#include "../vecmath/Vector3.h"

class Cylinder : public Shape {
    public:
        Cylinder(int topdiv = 10, int sidediv = 2);
        void draw() const;
        HitRecord intersect(Point3 p, Vector3 dir) const;
    
    private:
        // Vertices
        std::vector<Vector3> top;
        std::vector<Vector3> bot;
        int sidediv;
    
        // Shape properties
        const double tolerance = 0.000001;
        
        Point3 _center = Point3(0,0,0);
        Vector3 _n = Vector3(0, 1, 0);
        double _radius = 0.5;
        double _height = 0.5;
        
        double topConstraint(Point3 p) const;
        double botConstraint(Point3 p) const;
        double sideConstraint(Point3 p) const;
};

#endif /* defined(__cse452shellXC__Cylinder__) */
