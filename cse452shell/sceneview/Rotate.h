//
//  Rotate.h
//  cse452shellXC
//
//  Created by Ben Stolovitz on 4/5/15.
//  Copyright (c) 2015 bstolovitz. All rights reserved.
//

#ifndef __cse452shellXC__Rotate__
#define __cse452shellXC__Rotate__

#include <stdio.h>
#ifdef __APPLE__
// because Apple is stupid and I hate everyone
#include <OpenGL/glu.h>
#else
#include <Windows.h>
#include <GL/glu.h>
#endif

#include "../vecmath/Vector3.h"

#include "ITransform.h"

class Rotate : public ITransform {
    public:
        Rotate(double angle, Vector3 axis)
        : _angle(angle), _axis(axis) {};
    
        void apply();
    
    private:
        Vector3 _axis;
        double _angle;
    
    };

#endif /* defined(__cse452shellXC__Rotate__) */
