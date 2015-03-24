//
//  RayCube.cpp
//  cse452shellXC
//
//  Created by Ben Stolovitz on 3/22/15.
//  Copyright (c) 2015 bstolovitz. All rights reserved.
//

#include "RayCube.h"

RayCube::RayCube(Point3 corner, Vector3 dimensions) {
    _corner = corner;
    _dimensions = dimensions;
};

HitRecord RayCube::intersect(Point3 p, Vector3 dir) const {
    HitRecord hr = HitRecord();
    
    hr.addHit(1, 0, 0, _corner, _dimensions);
    
    hr.addHit(1, 0, 0, _corner + _dimensions, _dimensions);
    
    return hr;
};