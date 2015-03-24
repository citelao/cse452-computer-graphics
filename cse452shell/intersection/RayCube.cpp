//
//  RayCube.cpp
//  cse452shellXC
//
//  Created by Ben Stolovitz on 3/22/15.
//  Copyright (c) 2015 bstolovitz. All rights reserved.
//

#include "RayCube.h"

RayCube::RayCube(Point3 corner, Vector3 dimensions) {
    _corner = corner;
    _dimensions = dimensions;
};

HitRecord RayCube::intersect(Point3 p, Vector3 dir) const {
    HitRecord hr = HitRecord();
    
    // Take a planar approach
    
    // Top plane
    Point3 topg = _corner + Vector3(0, _dimensions[1], 0);
    Vector3 topn = (topg - _corner).unit();
    double ttop = (topg - p) * topn / (dir * topn);
    
    Point3 ptop = p + ttop * dir;
//    bool ptopValid = (lftConstraint(ptop) > 0 &&
//                      rgtConstraint(ptop) < 0 &&
//                      bckConstraint(ptop) < 0 &&
//                      frtConstraint(ptop) > 0);
    
    // Bot plane
    Point3 botg = _corner;
    Vector3 botn = -topn;
    double tbot = (botg - p) * botn / (dir * botn);
    
    Point3 pbot = p + tbot * dir;
    
    // Right plane
    Point3 rgtg = _corner + Vector3(_dimensions[0], 0, 0);
    Vector3 rgtn = (rgtg - _corner).unit();
    double trgt = (rgtg - p) * rgtn / (dir * rgtn);
    
    Point3 prgt = p + trgt * dir;
    
    // Left plane
    Point3 lftg = _corner;
    Vector3 lftn = -rgtn;
    double tlft = (lftg - p) * lftn / (dir * lftn);
    
    Point3 plft = p + tlft * dir;
    
    // Front plane
    Point3 frtg = _corner + Vector3(0, 0, _dimensions[2]);
    Vector3 frtn = (frtg - _corner).unit();
    double tfrt = (frtg - p) * frtn / (dir * frtn);
    
    Point3 pfrt = p + tfrt * dir;
    
    // Back plane
    Point3 bckg = _corner;
    Vector3 bckn = -rgtn;
    double tbck = (bckg - p) * bckn / (dir * bckn);
    
    Point3 pbck = p + tbck * dir;
    
    
    hr.addHit(ttop, 0, 0, ptop, topn);
    hr.addHit(tbot, 0, 0, pbot, botn);
    
    hr.addHit(trgt, 0, 0, prgt, rgtn);
    hr.addHit(tlft, 0, 0, plft, lftn);
    
    hr.addHit(tfrt, 0, 0, pfrt, frtn);
    hr.addHit(tbck, 0, 0, pbck, bckn);
    
    return hr;
};

double topConstraint(Point3 p) const {
    
};

double botConstraint(Point3 p) const {
    
};

double rgtConstraint(Point3 p) const {
    return (p - g) * n;
};

double lftConstraint(Point3 p) const {
    
};

double frtConstraint(Point3 p) const {
    
};

double bckConstraint(Point3 p) const {
    
};