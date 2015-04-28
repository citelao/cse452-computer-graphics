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

std::tuple<const Object*, HitRecord> Tree::intersect(Point3 pt, Vector3 dir) const {
    HitRecord nearestHr = HitRecord();
    const Object* nearestShape = nullptr;
    double nearestT = std::numeric_limits<double>::infinity();
    for (auto n : nodes) {
        auto tuple = n->intersect(pt, dir);
        auto currentShape = std::get<0>(tuple);
        auto currentHr = std::get<1>(tuple);
        currentHr.sortHits();
        double t, u, v;
        Point3 p;
        Vector3 norm;
        
        auto hit = currentHr.getFirstHit(t, u, v, p, norm);
        
        while(hit && t < 0.000000001) {
            currentHr.removeFirstHit();
            hit = currentHr.getFirstHit(t, u, v, p, norm);
        }
        
        if (!hit) {
            continue;
        }
        
        if (t < nearestT) {
            nearestT = t;
            nearestHr = currentHr;
            nearestShape = currentShape;
        }
    }
    
    return std::make_tuple(nearestShape, nearestHr);
};