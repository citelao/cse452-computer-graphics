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
    pts = {
        Vector3(0.5, 0.5, 0.5),
        Vector3(0.5, -0.5, 0.5),
        Vector3(-0.5, 0.5, 0.5),
        Vector3(-0.5, -0.5, 0.5),
        
        Vector3(0.5, 0.5, -0.5),
        Vector3(0.5, -0.5, -0.5),
        Vector3(-0.5, 0.5, -0.5),
        Vector3(-0.5, -0.5, -0.5)
    };
    
    indeces = {
        // top face
        2, 0, 4,
        6, 2, 4,
        
        // bottom face
        5, 1, 7,
        1, 3, 7,
        
        0, 1, 5,
        0, 5, 4,
        
        3, 1, 0,
        2, 3, 0,
        
        6, 3, 2,
        3, 6, 7,
        
        4, 5, 6,
        7, 6, 5
    };
}

void Cube::draw() {
    glBegin(GL_TRIANGLES);
        for(int i : indeces) {
            auto pt = pts[i];
            glVertex3f(pt[0], pt[1], pt[2]);
        }
    glEnd();
}