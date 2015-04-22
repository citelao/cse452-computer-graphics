//
//  Scale.h
//  cse452shellXC
//
//  Created by Ben Stolovitz on 4/5/15.
//  Copyright (c) 2015 bstolovitz. All rights reserved.
//

#ifndef __cse452shellXC__Scale__
#define __cse452shellXC__Scale__

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

class Scale : public ITransform {
    public:
        Scale(Vector3 v) : _v(v) {};
    
        void apply();
        Matrix4 matrix();
    
    private:
        Vector3 _v;
};

#endif /* defined(__cse452shellXC__Scale__) */
