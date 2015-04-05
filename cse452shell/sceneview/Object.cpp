//
//  Object.cpp
//  cse452shellXC
//
//  Created by Ben Stolovitz on 4/1/15.
//  Copyright (c) 2015 bstolovitz. All rights reserved.
//

#include "Object.h"

Object::~Object() {
    if (_valid) {
        delete _shape;
    }
}

bool Object::isValid() const {
    return _valid;
}

Object* Object::setShape(Shape* shape) {
    _shape = shape;
    _valid = true;
    return this;
}

void Object::draw() const {
    _shape->draw();
};