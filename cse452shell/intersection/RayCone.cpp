//
//  RayCone.cpp
//  cse452shellXC
//
//  Created by Ben Stolovitz on 3/22/15.
//  Copyright (c) 2015 bstolovitz. All rights reserved.
//

#include "RayCone.h"

RayCone::RayCone(Point3 tip, Vector3 n, double radius) {
    _tip = tip;
    _n = n.unit();
    _radius = radius;
    _height = n.length();
}

HitRecord RayCone::intersect(Point3 p, Vector3 dir) const {
    HitRecord hr = HitRecord();
    
    // Bottom
    // (p + td - _tip - height * n) * n = 0
    double tbot = ((_tip - _height * _n - p) * _n) / (dir * _n);
    
    // Side
    // v = p + td - center
    // (v - (v*n)n)^2 - r^2(v*n)^2 = 0
    
    Point3 pbot = p + tbot * dir;
    
    hr.addHit(tbot, 0, 0, pbot, -_n);
    
    return hr;
};