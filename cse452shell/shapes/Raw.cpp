//
//  Raw.cpp
//  cse452shellXC
//
//  Created by Ben Stolovitz on 3/24/15.
//  Copyright (c) 2015 bstolovitz. All rights reserved.
//

#include "Raw.h"

Raw::Raw(std::string filename) {
    pts = std::vector<Vector3*>();
    normals = std::vector<Vector3*>();
    
    // http://stackoverflow.com/questions/19885876/c-read-from-file-to-double
    std::ifstream ifs(filename, std::ifstream::in);
    
    while (ifs.good()) {
        double x;
        double y;
        double z;
        
        ifs >> x;
        ifs >> y;
        ifs >> z;
        
        pts.push_back(new Vector3(x, y, z));
    }
    
    for (auto i = 0; i < pts.size() / 3; i++) {
        auto norm = (-(*pts[3*i] - *pts[3*i+2]) ^ (*pts[3*i] - *pts[3*i + 1])).unit();
        
        normals.push_back(new Vector3(norm[0], norm[1], norm[2]));
    }
    
    ifs.close();
};

Raw::~Raw() {
    for(auto pt : pts) {
        delete(pt);
    }
    
    for(auto pt : normals) {
        delete(pt);
    }
};

void Raw::draw() const {
    glBegin(GL_TRIANGLES);
        for(size_t i = 0; i < pts.size(); i++) {
            auto pt = *pts[i];
            auto norm = *normals[(i / 3) - 1];
            glNormal3d(norm[0], norm[1], norm[2]);
            glVertex3d(pt[0], pt[1], pt[2]);
        }
    glEnd();
};

HitRecord Raw::intersect(Point3 p, Vector3 dir) const {
    auto hr = HitRecord();
    return hr;
}