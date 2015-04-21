//
//  Cube.cpp
//  cse452shellXC
//
//  Created by Ben Stolovitz on 2/15/15.
//  Copyright (c) 2015 bstolovitz. All rights reserved.
//

#include "Cube.h"

Cube::Cube(int topdiv, int sidediv)
: topdiv(topdiv), sidediv(sidediv) {
    basis = {
        Vector3(0.5, 0.5, 0.5),  // 0
        Vector3(0.5, -0.5, 0.5), // 1
        Vector3(-0.5, 0.5, 0.5), // 2
        Vector3(-0.5, -0.5, 0.5),// 3
        
        Vector3(0.5, 0.5, -0.5), // 4
        Vector3(0.5, -0.5, -0.5),// 5
        Vector3(-0.5, 0.5, -0.5),// 6
        Vector3(-0.5, -0.5, -0.5)// 7
    };
    
    // top & bot
    subdivide(basis[2], basis[0], basis[6], basis[4], Vector3(0, 1, 0), topdiv);
    subdivide(basis[7], basis[5], basis[3], basis[1], Vector3(0, -1, 0), topdiv);
    
    // sides
    subdivide(basis[0], basis[1], basis[4], basis[5], Vector3(1, 0, 0), topdiv);
    subdivide(basis[3], basis[1], basis[2], basis[0], Vector3(0, 0, 1), topdiv);
    subdivide(basis[6], basis[7], basis[2], basis[3], Vector3(-1, 0, 0), topdiv);
    subdivide(basis[7], basis[6], basis[5], basis[4], Vector3(0, 0, -1), topdiv);
    
    // Intersection
    _corner = Point3(-0.5,-0.5,-0.5);
    _dimensions = Vector3(1,1,1);
    
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
}

void Cube::subdivide(Vector3 tl, Vector3 tr, Vector3 bl, Vector3 br, Vector3 norm, int depth) {
    if(depth == 1) {
        pts.push_back(tl);
        pts.push_back(tr);
        pts.push_back(br);
        
        pts.push_back(tl);
        pts.push_back(br);
        pts.push_back(bl);
        
        normals.push_back(norm);
        normals.push_back(norm);
        
        return;
    }
    
    // gen pts
    auto tm = (tl + tr) / 2.0;
    auto cl = (bl + tl) / 2.0;
    auto cr = (br + tr) / 2.0;
    auto cm = (cl + cr) / 2.0;
    auto bm = (bl + br) / 2.0;
    
    // top left
    subdivide(tl, tm, cl, cm, norm, depth - 1);
    
    // top right
    subdivide(tm, tr, cm, cr, norm, depth - 1);
    
    // bot left
    subdivide(cl, cm, bl, bm, norm, depth - 1);
    
    // bot right
    subdivide(cm, cr, bm, br, norm, depth - 1);
};

HitRecord Cube::intersect(Point3 p, Vector3 dir) const {
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

double Cube::topConstraint(Point3 p) const {
    return (p - gTop) * nTop;
};

double Cube::botConstraint(Point3 p) const {
    return (p - gBot) * nBot;
};

double Cube::rightConstraint(Point3 p) const {
    return (p - gRight) * nRight;
};

double Cube::leftConstraint(Point3 p) const {
    return (p - gLeft) * nLeft;
};

double Cube::frontConstraint(Point3 p) const {
    return (p - gFront) * nFront;
};

double Cube::backConstraint(Point3 p) const {
    return (p - gBack) * nBack;
};

void Cube::draw() const {
    glBegin(GL_TRIANGLES);
        for(size_t i = 0; i < pts.size(); i++) {
            auto pt = pts[i];
            auto norm = normals[i / 3];
            glNormal3d(norm[0], norm[1], norm[2]);
            glVertex3d(pt[0], pt[1], pt[2]);
        }
    glEnd();
}