//
//  RayCylinder.h
//  cse452shellXC
//
//  Created by Ben Stolovitz on 3/22/15.
//  Copyright (c) 2015 bstolovitz. All rights reserved.
//

#ifndef __cse452shellXC__RayCylinder__
#define __cse452shellXC__RayCylinder__

#include <stdio.h>

#include "RayShape.h"

class RayCylinder : public RayShape {
public:
    RayCylinder(Point3 center = Point3(0,0,0), Vector3 n = Vector3(0, 0.5, 0), double radius = 0.5);
    
    HitRecord intersect(Point3 p, Vector3 dir) const;
    
private:
    const double tolerance = 0.000001;
    
    Point3 _center;
    Vector3 _n;
    double _radius;
    double _height;
    
    double topConstraint(Point3 p) const;
    double botConstraint(Point3 p) const;
    double sideConstraint(Point3 p) const;
};

#endif /* defined(__cse452shellXC__RayCylinder__) */
