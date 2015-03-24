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
    
    // Top & Bot
    gTop = _corner + Vector3(0, _dimensions[1], 0);
    nTop = (gTop - _corner).unit();
    
    gBot = _corner;
    nBot = -nTop;
    
    // Left & Right
    gRight = _corner + Vector3(_dimensions[0], 0, 0);
    nRight = (gRight - _corner).unit();
    
    gLeft = _corner;
    nLeft = -nRight;
    
    // Front & Back
    gFront = _corner + Vector3(0, 0, _dimensions[2]);
    nFront = (gFront - _corner).unit();
    
    gBack = _corner;
    nBack = -nFront;
};

HitRecord RayCube::intersect(Point3 p, Vector3 dir) const {
    HitRecord hr = HitRecord();
    
    // Take a planar approach
    
    // Top plane
    double ttop = (gTop - p) * nTop / (dir * nTop);
    // Bot plane
    double tbot = (gBot - p) * nBot / (dir * nBot);
    // Right plane
    double trgt = (gRight - p) * nRight / (dir * nRight);
    // Left plane
    double tlft = (gLeft - p) * nLeft / (dir * nLeft);
    // Front plane
    double tfrt = (gFront - p) * nFront / (dir * nFront);
    // Back plane
    double tbck = (gBack - p) * nBack / (dir * nBack);
    
    Point3 ptop = p + ttop * dir;
    bool ptopValid = (leftConstraint(ptop) < 0 &&
                      rightConstraint(ptop) < 0 &&
                      backConstraint(ptop) < 0 &&
                      frontConstraint(ptop) < 0);
    
    Point3 pbot = p + tbot * dir;
    bool pbotValid = (leftConstraint(pbot) < 0 &&
                      rightConstraint(pbot) < 0 &&
                      backConstraint(pbot) < 0 &&
                      frontConstraint(pbot) < 0);
    
    Point3 prgt = p + trgt * dir;
    bool prgtValid = (topConstraint(prgt) < 0 &&
                      botConstraint(prgt) < 0 &&
                      backConstraint(prgt) < 0 &&
                      frontConstraint(prgt) < 0);
    
    Point3 plft = p + tlft * dir;
    bool plftValid = (topConstraint(plft) < 0 &&
                      botConstraint(plft) < 0 &&
                      backConstraint(plft) < 0 &&
                      frontConstraint(plft) < 0);
    
    Point3 pfrt = p + tfrt * dir;
    bool pfrtValid = (topConstraint(pfrt) < 0 &&
                      botConstraint(pfrt) < 0 &&
                      leftConstraint(pfrt) < 0 &&
                      rightConstraint(pfrt) < 0);
    
    Point3 pbck = p + tbck * dir;
    bool pbckValid = (topConstraint(pbck) < 0 &&
                      botConstraint(pbck) < 0 &&
                      leftConstraint(pbck) < 0 &&
                      rightConstraint(pbck) < 0);
    
    
    if (ptopValid) {
        hr.addHit(ttop, 0, 0, ptop, nTop);
    }
    if (pbotValid) {
        hr.addHit(tbot, 0, 0, pbot, nBot);
    }
    
    if (prgtValid) {
        hr.addHit(trgt, 0, 0, prgt, nRight);
    }
    if (plftValid) {
        hr.addHit(tlft, 0, 0, plft, nLeft);
    }
    
    if (pfrtValid) {
        hr.addHit(tfrt, 0, 0, pfrt, nFront);
    }
    if (pbckValid) {
        hr.addHit(tbck, 0, 0, pbck, nBack);
    }
    
    return hr;
};

double RayCube::topConstraint(Point3 p) const {
    return (p - gTop) * nTop;
};

double RayCube::botConstraint(Point3 p) const {
    return (p - gBot) * nBot;
};

double RayCube::rightConstraint(Point3 p) const {
    return (p - gRight) * nRight;
};

double RayCube::leftConstraint(Point3 p) const {
    return (p - gLeft) * nLeft;
};

double RayCube::frontConstraint(Point3 p) const {
    return (p - gFront) * nFront;
};

double RayCube::backConstraint(Point3 p) const {
    return (p - gBack) * nBack;
};