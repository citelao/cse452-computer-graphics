//
//  Cylinder.cpp
//  cse452shellXC
//
//  Created by Ben Stolovitz on 2/15/15.
//  Copyright (c) 2015 bstolovitz. All rights reserved.
//

#include "Cylinder.h"

Cylinder::Cylinder(int topdiv, int sidediv) : sidediv(sidediv) {
    top = std::vector<Vector3>();
    bot = std::vector<Vector3>();

    
    top.push_back(Vector3(0.0, 0.5, 0.0));
    bot.push_back(Vector3(0.0, -0.5, 0.0));
    
    for (int i = 0; i < topdiv; i++) {
        double radians = (double)i / (double)topdiv * 2 * 3.14159;
  
        auto topv = Vector3(0.5 * sin(radians), 0.5, 0.5 * cos(radians));
        auto botv = Vector3(0.5 * sin(radians), -0.5, 0.5 * cos(radians));
        
        top.push_back(topv);
        bot.push_back(botv);
    }
    
    top.push_back(Vector3(0.5 * sin(0), 0.5, 0.5 * cos(0)));
    bot.push_back(Vector3(0.5 * sin(0), -0.5, 0.5 * cos(0)));
};


HitRecord Cylinder::intersect(Point3 p, Vector3 dir) const {
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

double Cylinder::topConstraint(Point3 p) const {
    return (p - _center - _height * _n) * _n;
};

double Cylinder::botConstraint(Point3 p) const {
    return (p - _center + _height * _n) * _n;
};

double Cylinder::sideConstraint(Point3 p) const {
    auto f = p - _center;
    auto g = f - (f * _n) * _n;
    return g * g - _radius * _radius;
};

void Cylinder::draw() const {
    // Top circle
    glBegin(GL_TRIANGLE_FAN);
        for(auto pt : top) {
            glNormal3d(0, 1, 0);
            glVertex3d(pt[0], pt[1], pt[2]);
        }
    glEnd();
    
    // Bottom circle
    glBegin(GL_TRIANGLE_FAN);
        glNormal3d(0.0, -1.0, 0.0);
        glVertex3d(bot[0][0], bot[0][1], bot[0][2]);
    
        for(auto i = bot.size() - 1; i >= 1; i--) {
            auto pt = bot[i];
            glNormal3d(0.0, -1.0, 0.0);
            GLfloat n[3];
            glGetFloatv(GL_CURRENT_NORMAL, n);
            glVertex3d(pt[0], pt[1], pt[2]);
        }
    glEnd();
    
    // Walls
    glBegin(GL_TRIANGLE_STRIP);
    double divsize = (double)1 / (double)sidediv;
    for (auto i = 0; i < sidediv; i++) {
        double div = (double)i / (double)sidediv;
        double ty = (1 - div) * top[0][1] + div * bot[0][1];
        double by = (1 - div - divsize) * top[0][1] + (div + divsize) * bot[0][1];;
        
        for (size_t i = 1; i < bot.size(); i++) {
            auto tpt = top[i];
            auto bpt = bot[i];
            
            glNormal3d(tpt[0], 0.0, tpt[2]);
            glVertex3d(tpt[0], ty, tpt[2]);
            glVertex3d(bpt[0], by, bpt[2]);
        }
    }
    glEnd();
};