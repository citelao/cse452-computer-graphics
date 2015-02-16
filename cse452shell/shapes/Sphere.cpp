//
//  Sphere.cpp
//  cse452shellXC
//
//  Created by Ben Stolovitz on 2/16/15.
//  Copyright (c) 2015 bstolovitz. All rights reserved.
//

#include "Sphere.h"

Sphere::Sphere(int topdiv, int sidediv) {
    // Geodesic model!
    // start with three points, subdivide however many times.
    const auto radius = 1.0;
    const std::vector<double> angles = {0, 2 * 3.14159 / 3, 2 * 2 * 3.14159 / 3};
    
    auto a = Vector3(radius * cos(angles[0]),
                     0,
                     radius * sin(angles[0]));
    auto b = Vector3(radius * cos(angles[1]),
                     0,
                     radius * sin(angles[1]));
    auto c = Vector3(radius * cos(angles[2]),
                     0,
                     radius * sin(angles[2]));
    
    auto d = Vector3(0, radius, 0);
    
    
    auto depth = sidediv;
//    auto depth = 1;
    subdiv(a, b, c, depth);
    subdiv(d, c, b, depth);
    subdiv(d, b, a, depth);
    subdiv(d, a, c, depth);
};

void Sphere::subdiv(Vector3 a, Vector3 b, Vector3 c, int d) {
    if(d == 1) {
        pts.push_back(a);
        pts.push_back(b);
        pts.push_back(c);
        return;
    }
    
    auto abprime = (a + b) / 2;
    auto bcprime = (b + c) / 2;
    auto acprime = (c + a) / 2;
    
    abprime.normalize();
    bcprime.normalize();
    acprime.normalize();
    
    subdiv(abprime, bcprime, acprime, d - 1);
    subdiv(bcprime, abprime, b, d - 1);
    subdiv(c, acprime, bcprime, d - 1);
    subdiv(a, abprime, acprime, d - 1);
};

void Sphere::draw() {
    glBegin(GL_TRIANGLES);
        for (auto pt : pts) {
            glNormal3d(pt[0],pt[1],pt[2]);
            glVertex3d(pt[0],pt[1],pt[2]);
        }
    glEnd();
};