//
//  Tree.cpp
//  cse452shellXC
//
//  Created by Ben Stolovitz on 4/1/15.
//  Copyright (c) 2015 bstolovitz. All rights reserved.
//

#include "Tree.h"

void Tree::addNode(Node* node) {
    if(!node->isValid()) {
        return;
    }
    
    nodes.push_back(node);
};

void Tree::draw() const {
    for (auto n : nodes) {
        n->draw();
    }
};

HitRecord Tree::intersect(Point3 pt, Vector3 dir) const {
    HitRecord nearestHr = HitRecord();
    double nearestT = std::numeric_limits<double>::infinity();
    for (auto n : nodes) {
        auto currentHr = n->intersect(pt, dir);
        currentHr.sortHits();
        double t, u, v;
        Point3 p;
        Vector3 norm;
        
        if (!currentHr.getFirstHit(t, u, v, p, norm)) {
            continue;
        }
        
        if (t < nearestT) {
            nearestT = t;
            nearestHr = currentHr;
        }
    }
    
    return nearestHr;
};