//
//  RaySphere.h
//  cse452shellXC
//
//  Created by Ben Stolovitz on 3/22/15.
//  Copyright (c) 2015 bstolovitz. All rights reserved.
//

#ifndef __cse452shellXC__RaySphere__
#define __cse452shellXC__RaySphere__

#include <stdio.h>

#include "RayShape.h"

class RaySphere : public RayShape {
    public:
        RaySphere(Point3 center = Point3(0,0,0), double radius = 0.5) :
        _center(center), _radius(radius) {};
    
        HitRecord intersect(Point3 p, Vector3 dir) const;
    
    private:
        Point3 _center;
        double _radius;
};

#endif /* defined(__cse452shellXC__RaySphere__) */