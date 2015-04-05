//
//  Rotate.cpp
//  cse452shellXC
//
//  Created by Ben Stolovitz on 4/5/15.
//  Copyright (c) 2015 bstolovitz. All rights reserved.
//

#include "Rotate.h"

void Rotate::apply() {
    glRotated(_angle, _axis[0], _axis[1], _axis[2]);
}