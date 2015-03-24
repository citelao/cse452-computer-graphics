//
//  RayCube.h
//  cse452shellXC
//
//  Created by Ben Stolovitz on 3/22/15.
//  Copyright (c) 2015 bstolovitz. All rights reserved.
//

#ifndef __cse452shellXC__RayCube__
#define __cse452shellXC__RayCube__

#include <stdio.h>

#include "RayShape.h"

class RayCube : public RayShape {
public:
    RayCube(Point3 corner = Point3(-0.5,-0.5,-0.5),
            Vector3 dimensions = Vector3(1,1,1));
    
    HitRecord intersect(Point3 p, Vector3 dir) const;
    
private:
    Point3 _corner;
    Vector3 _dimensions;
    
    Point3 gTop;
    Point3 gBot;
    Point3 gLeft;
    Point3 gRight;
    Point3 gFront;
    Point3 gBack;
    
    Vector3 nTop;
    Vector3 nBot;
    Vector3 nLeft;
    Vector3 nRight;
    Vector3 nFront;
    Vector3 nBack;
    
    double topConstraint(Point3 p) const;
    double botConstraint(Point3 p) const;
    double rightConstraint(Point3 p) const;
    double leftConstraint(Point3 p) const;
    double frontConstraint(Point3 p) const;
    double backConstraint(Point3 p) const;
};

#endif /* defined(__cse452shellXC__RayCube__) */
