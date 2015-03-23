//
//  RaySphere.cpp
//  cse452shellXC
//
//  Created by Ben Stolovitz on 3/22/15.
//  Copyright (c) 2015 bstolovitz. All rights reserved.
//

#include "RaySphere.h"

HitRecord RaySphere::intersect(Point3 p, Vector3 dir) const {
    HitRecord hr = HitRecord();
    
    // Use the quadratic equation to solve for sphere intersection.
    double a = dir * dir;
    double b = 2 * ((p - _center) * dir);
    double c = (p - _center) * (p - _center) - pow(_radius, 2);
    
    if (b * b < 4 * a * c) {
        return hr;
    }
    
    double t1 = (-b + sqrt(pow(b, 2) - 4 * a * c)) / (2 * a);
    double t2 = (-b - sqrt(pow(b, 2) - 4 * a * c)) / (2 * a);

    if (t2 < 0) {
        return hr;
    }
    
    Point3 p1 = p + t1 * dir;
    Point3 p2 = p + t2 * dir;
    
    hr.addHit(t1, 0, 0, p1, (p1 - _center).unit());
    hr.addHit(t2, 0, 0, p2, (p2 - _center).unit());
    
    return hr;
}