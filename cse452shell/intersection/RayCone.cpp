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
    // v = p + td - tip
    // (v - (v*n)n)^2 - r^2(v*n)^2 = 0
    // => quadratic
    Vector3 alpha = dir - (dir * _n * _n);
    Vector3 beta = (p - _tip) - ((p - _tip) * _n * _n);
    double gamma = dir * _n;
    double delta = (p - _tip) * _n;
    
    double a = alpha * alpha - _radius * _radius * gamma * gamma;
    double b = 2 * alpha * beta - (2 * _radius * _radius * gamma * delta);
    double c = beta * beta - (_radius * _radius * delta * delta);
    
    double ts1 = (-b + sqrt(pow(b, 2) - 4 * a * c)) / (2 * a);
    double ts2 = (-b - sqrt(pow(b, 2) - 4 * a * c)) / (2 * a);
    
    Point3 pbot = p + tbot * dir;
    bool pbotFits = sideConstraint(pbot) < 0;
    
    Point3 ps1 = p - ts1 * dir;
    bool ps1Fits = botConstraint(ps1) > 0;
    
    Point3 ps2 = p - ts2 * dir;
    bool ps2Fits = botConstraint(ps2) > 0;
    
    if (pbotFits) {
        hr.addHit(tbot, 0, 0, pbot, -_n);
    }
    
//    if (ps1Fits) {
        hr.addHit(ts1, 0, 0, ps1, Vector3(1,0,0));
//    }
    
//    if (ps2Fits) {
        hr.addHit(ts2, 0, 0, ps2, Vector3(0,0,0));
//    }
    
    return hr;
};

double RayCone::botConstraint(Point3 p) const {
    return (p - _tip - _height * _n) * _n;
};

double RayCone::sideConstraint(Point3 p) const {
    auto v = p - _tip;
    auto a = v - (v * _n) * _n;
    auto b = v * _n;
    return a * a - _radius * _radius * b * b;
};