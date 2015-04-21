//
//  Shape.h
//  cse452shellXC
//
//  Created by Ben Stolovitz on 2/15/15.
//  Copyright (c) 2015 bstolovitz. All rights reserved.
//

#ifndef __cse452shellXC__Shape__
#define __cse452shellXC__Shape__

#include <stdio.h>
#include "../intersection/HitRecord.h"

class Shape {
    public:
        virtual void draw() const = 0;
        virtual HitRecord intersect(Point3 p, Vector3 dir) const = 0;
};

#endif /* defined(__cse452shellXC__Shape__) */
