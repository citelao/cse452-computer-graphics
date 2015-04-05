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
    _child = child;
    _valid = true;
    
    return this;
};

Node* Node::addTransform(ITransform* t) {
    _transforms.push_back(t);
    
    return this;
};

//
//Node* Node::setTranslate(double x, double y, double z) {
//    _translate = true;
//    
//    _translatev = Vector3(x, y, z);
//    
//    return this;
//}
//
//Node* Node::setRotate(double angle, double x, double y, double z) {
//    _rotate = true;
//    
//    _rotateaxis = Vector3(x, y, z);
//    _rotateangle = angle * 180 / 3.14159;
//    
//    return this;
//}
//
//Node* Node::setScale(double x, double y, double z) {
//    _scale = true;
//    
//    _scalev = Vector3(x, y, z);
//}

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
    
//    if (_translate) {
//        glTranslated(_translatev[0], _translatev[1], _translatev[2]);
//    }
//    
//    if(_rotate) {
//        glRotated(_rotateangle, _rotateaxis[0], _rotateaxis[1], _rotateaxis[2]);
//    }
//    
//    if(_scale) {
//        glScaled(_scalev[0], _scalev[1], _scalev[2]);
//    }
    
    _child->draw();
    
    glPopMatrix();
}