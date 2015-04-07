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