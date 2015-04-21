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
    void draw() const;
    HitRecord intersect(Point3 p, Vector3 dir) const;
    
private:
    void subdivide(Vector3 tl, Vector3 tr, Vector3 bl, Vector3 br, Vector3 norm, int depth);
    
    double topConstraint(Point3 p) const;
    double botConstraint(Point3 p) const;
    double rightConstraint(Point3 p) const;
    double leftConstraint(Point3 p) const;
    double frontConstraint(Point3 p) const;
    double backConstraint(Point3 p) const;
    
    // Vertices
    std::vector<Vector3> basis;
    std::vector<Vector3> pts;
    std::vector<Vector3> normals;
    std::vector<int> indeces;
    
    int topdiv;
    int sidediv;
    
    // Intersection
    Point3 _corner;
    Vector3 _dimensions;
    
    Point3 gTop;
    Point3 gBot;
    Point3 gLeft;
    Point3 gRight;
    Point3 gFront;
    Point3 gBack;
    
    Vector3 nTop;
    Vector3 nBot;
    Vector3 nLeft;
    Vector3 nRight;
    Vector3 nFront;
    Vector3 nBack;
};

#endif /* defined(__cse452shellXC__Cube__) */
