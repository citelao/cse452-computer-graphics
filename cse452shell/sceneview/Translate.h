//
//  Translate.h
//  cse452shellXC
//
//  Created by Ben Stolovitz on 4/5/15.
//  Copyright (c) 2015 bstolovitz. All rights reserved.
//

#ifndef __cse452shellXC__Translate__
#define __cse452shellXC__Translate__

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

class Translate : public ITransform {
    public:
        Translate(Vector3 v) : _v(v) {};
//        ~Translate() {};
    
        void apply();
        Matrix4 matrix();
    
    private:
        Vector3 _v;
};

#endif /* defined(__cse452shellXC__Translate__) */
