//
//  RayCylinder.cpp
//  cse452shellXC
//
//  Created by Ben Stolovitz on 3/22/15.
//  Copyright (c) 2015 bstolovitz. All rights reserved.
//

#include "RayCylinder.h"

RayCylinder::RayCylinder(Point3 center, Vector3 n, double radius) {
    _center = center;
    _n = n.unit();
    _radius = radius;
    _height = n.length();
};

HitRecord RayCylinder::intersect(Point3 p, Vector3 dir) const {
    HitRecord hr = HitRecord();
    
    // Possible planes:
    // Top
    // (p + td - center - height * n) * n = 0
    double ttop = ((_center + _height * _n - p) * _n) / (dir * _n);
    
    // Bottom
    // (p + td - center + height * n) * n = 0
    double tbot = ((_center - _height * _n - p) * _n) / (dir * _n);
    
    // Side
    // f = (p + t * d - center)
    // g = (f - (f * n) * n)
    // g * g - radius * radius = 0
    // => quadratic
    
    // A = alpha * alpha
    // B = 2 * alpha * beta
    // C = beta * beta - radius * radius
    // alpha = d - d * n * n
    // beta = p - center - (n * n)(p - center)
    Vector3 alpha = dir - (dir * _n * _n);
    Vector3 beta = p - _center - (p - _center) * _n * _n;
    double a = alpha * alpha;
    double b = 2 * alpha * beta;
    double c = beta * beta - _radius * _radius;
    
    double ts1 = (-b + sqrt(pow(b, 2) - 4 * a * c)) / (2 * a);
    double ts2 = (-b - sqrt(pow(b, 2) - 4 * a * c)) / (2 * a);
    
    // Does ptop fit on top plane?
    // Check side constraint <=
    Point3 ptop = p + ttop * dir;
    bool ptopFit = sideConstraint(ptop) <= 0;
    
    // Does pbot fit on bot plane?
    // Check side constraint <=
    Point3 pbot = p + tbot * dir;
    bool pbotFit = sideConstraint(pbot) <= 0;
    
    // Does ps1 fit on side plane?
    // Check top constraint <
    // Check bot constraint >
    Point3 ps1 = p + ts1 * dir;
    bool ps1Fit = topConstraint(ps1) < -tolerance && botConstraint(ps1) > tolerance;
    
    // Does ps1 fit on side plane?
    // Check top constraint <
    // Check bot constraint >
    Point3 ps2 = p + ts2 * dir;
    bool ps2Fit = topConstraint(ps2) < -tolerance && botConstraint(ps2) > tolerance;
    
    if (ptopFit) {
        hr.addHit(ttop, 0, 0, ptop, _n);
    }
    if (pbotFit) {
        hr.addHit(tbot, 0, 0, pbot, -_n);
    }
    if (ps1Fit) {
        auto norm = ps1 - (_center + ((ps1 - _center) * _n) * _n);
        hr.addHit(ts1, 0, 0, ps1, norm);
    }
    if (ps2Fit) {
        auto norm = ps2 - (_center + ((ps2 - _center) * _n) * _n);
        hr.addHit(ts2, 0, 0, ps2, norm);
    }
    
    return hr;
};

double RayCylinder::topConstraint(Point3 p) const {
    return (p - _center - _height * _n) * _n;
};

double RayCylinder::botConstraint(Point3 p) const {
    return (p - _center + _height * _n) * _n;
};

double RayCylinder::sideConstraint(Point3 p) const {
    auto f = p - _center;
    auto g = f - (f * _n) * _n;
    return g * g - _radius * _radius;
};