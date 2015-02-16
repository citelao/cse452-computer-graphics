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

    
    top.push_back(Vector3(0.0, 1.0, 0.0));
    bot.push_back(Vector3(0.0, -1.0, 0.0));
    
    for (int i = 0; i < topdiv; i++) {
        double radians = (double)i / (double)topdiv * 2 * 3.14159;
  
        auto topv = Vector3(sin(radians), 1.0, cos(radians));
        auto botv = Vector3(sin(radians), -1.0, cos(radians));
        
        top.push_back(topv);
        bot.push_back(botv);
    }
    
    top.push_back(Vector3(sin(0), 1.0, cos(0)));
    bot.push_back(Vector3(sin(0), -1.0, cos(0)));
};

void Cylinder::draw() {
    // Top circle
    glBegin(GL_TRIANGLE_FAN);
        for(auto pt : top) {
            glNormal3d(0, 1, 0);
            glVertex3d(pt[0], pt[1], pt[2]);
        }
    glEnd();
    
    // Bottom circle
    glBegin(GL_TRIANGLE_FAN);
        glVertex3d(bot[0][0], bot[0][1], bot[0][2]);
    
//        for(auto i = bot.size() - 1; i >= 1; i--) {
//            auto pt = bot[i];
        for(auto pt : bot) {
            glNormal3d(0.0, -1.0, 0.0);
            GLfloat n[3];
            glGetFloatv(GL_CURRENT_NORMAL, n);
            glVertex3d(pt[0], pt[1], pt[2]);
        }
    glEnd();
    
    // Walls
    glBegin(GL_QUAD_STRIP);
    double divsize = (double)1 / (double)sidediv;
    for (auto i = 0; i < sidediv; i++) {
        double div = (double)i / (double)sidediv;
        double ty = (1 - div) * top[0][1] + div * bot[0][1];
        double by = (1 - div - divsize) * top[0][1] + (div + divsize) * bot[0][1];;
        
        for (size_t i = 1; i < bot.size(); i++) {
            auto tpt = top[i];
            auto bpt = bot[i];
            
            //            glNormal3d(0.0, pow(-1, i), 0.0);
            glVertex3d(tpt[0], ty, tpt[2]);
            glVertex3d(bpt[0], by, bpt[2]);
        }
    }
    glEnd();
};