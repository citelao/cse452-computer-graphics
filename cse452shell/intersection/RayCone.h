//
//  RayCone.h
//  cse452shellXC
//
//  Created by Ben Stolovitz on 3/22/15.
//  Copyright (c) 2015 bstolovitz. All rights reserved.
//

#ifndef __cse452shellXC__RayCone__
#define __cse452shellXC__RayCone__

#include <stdio.h>

#include "RayShape.h"

class RayCone : public RayShape {
public:
    RayCone(Point3 tip = Point3(0,0.5,0), Vector3 n = Vector3(0, 1.0, 0), double radius = 0.5);
    
    HitRecord intersect(Point3 p, Vector3 dir) const;
    
private:
    Point3 _tip;
    Vector3 _n;
    double _radius;
    double _height;

    double topConstraint(Point3 p) const;
    double botConstraint(Point3 p) const;
    double sideConstraint(Point3 p) const;
};

#endif /* defined(__cse452shellXC__RayCone__) */
