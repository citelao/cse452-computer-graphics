//
//  Scale.cpp
//  cse452shellXC
//
//  Created by Ben Stolovitz on 4/5/15.
//  Copyright (c) 2015 bstolovitz. All rights reserved.
//

#include "Scale.h"

void Scale::apply() {
    glScaled(_v[0], _v[1], _v[2]);
}

Matrix4 Scale::matrix() {
    return Matrix4::scaling(_v[0], _v[1], _v[2]);
}