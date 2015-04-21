//
//  Cone.cpp
//  cse452shellXC
//
//  Created by Ben Stolovitz on 2/15/15.
//  Copyright (c) 2015 bstolovitz. All rights reserved.
//

#include "Cone.h"

Cone::Cone(int topdiv, int sidediv) {
    pts = std::vector<std::vector<Vector3> >(sidediv);

    for (int i = 0; i < sidediv; i++) {
        double h = -0.5 + (double)i / (double)sidediv;
        double r = 0.5 - (0.5 + h) / 2.0;
        
        for (int j = 0; j < topdiv; j++) {
            double radians = (double)j / (double)topdiv * 2 * 3.14159;
            
            auto botv = Vector3(r * sin(radians), h, r * cos(radians));
            
            pts[i].push_back(botv);
        }
    }
    
    _tip = Point3(0,0.5,0);
    _n = Vector3(0, 1.0, 0).unit();
    _radius = 0.5;
    _height = Vector3(0, 1.0, 0).length();
    
};

void Cone::draw() const {
    glBegin(GL_TRIANGLES);
    auto v = pts[pts.size() - 1];
    for (size_t i = 0; i < v.size(); i++) {
        Vector3 pt1;
        Vector3 pt2;
        if (i + 1 < v.size()) {
            pt1 = v[i];
            pt2 = v[i+1];
        } else {
            pt1 = v[i];
            pt2 = v[0];
        }
        
        glNormal3f(0, 1, 0);
        glVertex3f(0.0, 0.5, 0.0);
        glNormal3d(pt1[0], 0, pt1[2]);
        glVertex3f(pt1[0], pt1[1], pt1[2]);
        glNormal3d(pt2[0], 0, pt2[2]);
        glVertex3f(pt2[0], pt2[1], pt2[2]);
    }
    glEnd();
    
    for (size_t i = 0; i <= pts.size() - 2; i++) {
        glBegin(GL_TRIANGLE_STRIP);
            for (size_t j = 0; j < pts[i].size(); j++) {
                auto pt1 = pts[i][j];
                auto pt2 = pts[i + 1][j];
                
                glNormal3d(pt2[0], 0, pt2[2]);
                glVertex3d(pt2[0], pt2[1], pt2[2]);
                glNormal3d(pt1[0], 0, pt1[2]);
                glVertex3d(pt1[0], pt1[1], pt1[2]);
            }
        
        auto pt1 = pts[i][0];
        auto pt2 = pts[i + 1][0];
        
        glNormal3d(pt2[0], 0, pt2[2]);
        glVertex3d(pt2[0], pt2[1], pt2[2]);
        glNormal3d(pt1[0], 0, pt1[2]);
        glVertex3d(pt1[0], pt1[1], pt1[2]);
        
//        GLfloat n[3];
//        glGetFloatv(GL_CURRENT_NORMAL, n);
        
        glEnd();
    }
    
    // Bottom circle
    glBegin(GL_TRIANGLE_FAN);
    glNormal3d(0.0, -1.0, 0.0);
    glVertex3d(0.0, -0.5, 0.0);
    
    v = pts[0];
    for(auto i = v.size() - 1; i < v.size(); i--) {
        auto pt = v[i];
        glNormal3d(0.0, -1.0, 0.0);
        glVertex3d(pt[0], pt[1], pt[2]);
    }
    
    glVertex3d(pts[0][v.size() - 1][0], pts[0][v.size() - 1][1], pts[0][v.size() - 1][2]);
    glEnd();
};


HitRecord Cone::intersect(Point3 p, Vector3 dir) const {
    HitRecord hr = HitRecord();
    
    // Bottom
    // (p + td - _tip - height * n) * n = 0
    double tbot = ((_tip - _height * _n - p) * _n) / (dir * _n);
    
    // Side
    // v = p + td - tip
    // (v - (v*n)n)^2 - r^2(v*n)^2 = 0
    // => quadratic
    Vector3 alpha = dir - (dir * _n * _n);
    Vector3 beta = p - _tip - (p - _tip) * _n * _n;
    double gamma = dir * _n;
    double delta = (p - _tip) * _n;
    
    double a = alpha * alpha - _radius * _radius * gamma * gamma;
    double b = 2 * alpha * beta - (2 * _radius * _radius * gamma * delta);
    double c = beta * beta - (_radius * _radius * delta * delta);
    
    double ts1 = (-b + sqrt(pow(b, 2) - 4 * a * c)) / (2 * a);
    double ts2 = (-b - sqrt(pow(b, 2) - 4 * a * c)) / (2 * a);
    
    Point3 pbot = p + tbot * dir;
    bool pbotFits = sideConstraint(pbot) < 0;
    
    Point3 ps1 = p + ts1 * dir;
    bool ps1Fits = botConstraint(ps1) > 0 && topConstraint(ps1) < 0;
    
    Point3 ps2 = p + ts2 * dir;
    bool ps2Fits = botConstraint(ps2) > 0 && topConstraint(ps2) < 0;
    
    if (pbotFits) {
        hr.addHit(tbot, 0, 0, pbot, -_n);
    }
    
    if (ps1Fits) {
        hr.addHit(ts1, 0, 0, ps1, ((ps1 - _tip) ^ (_height * _n) ^ (ps1 - _tip)).unit());
    }
    
    if (ps2Fits) {
        hr.addHit(ts2, 0, 0, ps2, ((ps2 - _tip) ^ (_height * _n) ^ (ps2 - _tip)).unit());
    }
    
    return hr;
};

double Cone::topConstraint(Point3 p) const {
    return (p - _tip) * _n;
};

double Cone::botConstraint(Point3 p) const {
    return (p - _tip + _height * _n) * _n;
};

double Cone::sideConstraint(Point3 p) const {
    auto v = p - _tip;
    auto a = v - (v * _n) * _n;
    auto b = v * _n;
    return a * a - _radius * _radius * b * b;
};