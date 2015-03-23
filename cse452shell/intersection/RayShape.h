//
//  RayShape.h
//  cse452shellXC
//
//  Created by Ben Stolovitz on 3/22/15.
//  Copyright (c) 2015 bstolovitz. All rights reserved.
//

#ifndef __cse452shellXC__RayShape__
#define __cse452shellXC__RayShape__

#include <stdio.h>
#include "../vecmath/Point3.h"
#include "../vecmath/Vector3.h"
#include "HitRecord.h"

class RayShape {
    public:
        virtual HitRecord intersect(Point3 p, Vector3 dir) const = 0;
};

#endif /* defined(__cse452shellXC__RayShape__) */
