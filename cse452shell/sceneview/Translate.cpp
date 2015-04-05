//
//  Translate.cpp
//  cse452shellXC
//
//  Created by Ben Stolovitz on 4/5/15.
//  Copyright (c) 2015 bstolovitz. All rights reserved.
//

#include "Translate.h"

void Translate::apply() {
    glTranslated(_v[0], _v[1], _v[2]);
}