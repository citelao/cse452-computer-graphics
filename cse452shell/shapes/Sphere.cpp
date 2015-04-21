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
    trueradius = 0.5;
    
    const double radius = 1;
    const double gr = (1.0 + sqrt(5)) / 2.0;
    
    // (0, ±1, ±φ)
    // (±1, ±φ, 0)
    // (±φ, 0, ±1)
    std::vector<Vector3> basis = {
        Vector3(0, radius, radius * gr),   // 0
        Vector3(0, radius, -radius * gr),  // 1
        Vector3(0, -radius, radius * gr),  // 2
        Vector3(0, -radius, -radius * gr), // 3
        
        Vector3(radius, radius * gr, 0),   // 4
        Vector3(radius, -radius * gr, 0),  // 5
        Vector3(-radius, radius * gr, 0),  // 6
        Vector3(-radius, -radius * gr, 0), // 7
        
        Vector3(radius * gr, 0, radius),   // 8
        Vector3(radius * gr, 0, -radius),  // 9
        Vector3(-radius * gr, 0, radius),  // 10
        Vector3(-radius * gr, 0, -radius)  // 11
    };
    
    for (auto &pt : basis) {
        pt.normalize();
        
        pt = pt * trueradius;
    }
    
    auto depth = sidediv;
    
    // front
    
    subdiv(basis[8], basis[9], basis[4], depth);
    subdiv(basis[8], basis[5], basis[9], depth);
    
    // left front
    subdiv(basis[8], basis[4], basis[0], depth);
    subdiv(basis[8], basis[2], basis[5], depth);
    subdiv(basis[2], basis[8], basis[0], depth);

    // right front
    subdiv(basis[4], basis[9], basis[1], depth);
    subdiv(basis[9], basis[5], basis[3], depth);
    subdiv(basis[3], basis[1], basis[9], depth);
    
    // back
    
    subdiv(basis[11], basis[10], basis[6], depth);
    subdiv(basis[11], basis[7], basis[10], depth);

    // left back
    subdiv(basis[11], basis[6], basis[1], depth);
    subdiv(basis[11], basis[3], basis[7], depth);
    subdiv(basis[3], basis[11], basis[1], depth);
    
    // right back
    subdiv(basis[6], basis[10], basis[0], depth);
    subdiv(basis[10], basis[7], basis[2], depth);
    subdiv(basis[2], basis[0], basis[10], depth);

    // top
    subdiv(basis[1], basis[6], basis[4], depth);
    subdiv(basis[4], basis[6], basis[0], depth);
    
    // bottom
    subdiv(basis[5], basis[2], basis[7], depth);
    subdiv(basis[5], basis[7], basis[3], depth);

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

    abprime = abprime * trueradius;
    bcprime = bcprime * trueradius;
    acprime = acprime * trueradius;
    
    subdiv(abprime, bcprime, acprime, d - 1);
    subdiv(bcprime, abprime, b, d - 1);
    subdiv(c, acprime, bcprime, d - 1);
    subdiv(a, abprime, acprime, d - 1);
};

void Sphere::draw() const {
    glBegin(GL_TRIANGLES);
        for (auto pt : pts) {
            glNormal3d(pt[0],pt[1],pt[2]);
            glVertex3d(pt[0],pt[1],pt[2]);
        }
    glEnd();
}

HitRecord Sphere::intersect(Point3 p, Vector3 dir) const {
    HitRecord hr = HitRecord();
    
    // Use the quadratic equation to solve for sphere intersection.
    double a = dir * dir;
    double b = 2 * ((p - _center) * dir);
    double c = (p - _center) * (p - _center) - pow(trueradius, 2);
    
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