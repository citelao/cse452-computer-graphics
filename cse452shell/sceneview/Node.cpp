//
//  Node.cpp
//  cse452shellXC
//
//  Created by Ben Stolovitz on 4/1/15.
//  Copyright (c) 2015 bstolovitz. All rights reserved.
//

#include "Node.h"

Node::~Node() {
    if (_valid) {
        delete _child;
    }
    
    for (auto t : _transforms) {
        delete t;
    }
}

Node* Node::setChild(IDrawable* child) {
    if(!child->isValid()) {
        return this;
    }
    
    _child = child;
    _valid = true;
    
    return this;
};

Node* Node::addTransform(ITransform* t) {
    _transforms.push_back(t);
    
    _matrix *= t->matrix();
    _inv = _matrix.inverse();
    _invtranspose = _inv.transpose();
    
    return this;
};

bool Node::isValid() const {
    return _valid;
}

void Node::draw() const {
    // Store transform matrix
    glPushMatrix();
    
    // Create new matrices
    for (auto t : _transforms) {
        t->apply();
    }
    
    _child->draw();
    
    glPopMatrix();
}

std::tuple<const Object*, HitRecord>  Node::intersect(Point3 pt, Vector3 dir) const {
    auto transformedpt = _inv * pt;
    auto transformeddir = _inv * dir;
    
    auto tuple = _child->intersect(transformedpt, transformeddir);
    
    auto shape = std::get<0>(tuple);
    auto hr = std::get<1>(tuple);
    
    auto newhr = HitRecord();
    
    double t, u, v;
    Vector3 n;
    Point3 p;
    auto hit = hr.getFirstHit(t, u, v, p, n);
    while (hit) {
        Point3 transp = _matrix * p;
        double transt = (transp - pt) * dir;
        Vector3 transn = (_invtranspose * n).unit();
        
        newhr.addHit(transt, u, v, transp, transn);
        hr.removeFirstHit();
        hit = hr.getFirstHit(t, u, v, p, n);
    }
    
    newhr.sortHits();

    return std::make_tuple(shape, newhr);
}