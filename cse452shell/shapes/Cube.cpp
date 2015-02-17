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

void Cube::draw() {
    glBegin(GL_TRIANGLES);
        for(size_t i = 0; i < pts.size(); i++) {
            auto pt = pts[i];
            auto norm = normals[i / 3];
            glNormal3d(norm[0], norm[1], norm[2]);
            glVertex3d(pt[0], pt[1], pt[2]);
        }
    glEnd();
}