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
    glPushAttrib(GL_CURRENT_BIT);

    glMaterialfv(GL_FRONT, GL_AMBIENT, &ambient[0]);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, &diffuse[0]);
    glMaterialfv(GL_FRONT, GL_SPECULAR, &specular[0]);
    glMaterialfv(GL_FRONT, GL_EMISSION, &emission[0]);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);
    
//    glColor3f(_color[0], _color[1], _color[2]);
    _shape->draw();
    glPopAttrib();
};