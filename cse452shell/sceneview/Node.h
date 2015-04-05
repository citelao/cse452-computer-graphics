//
//  Node.h
//  cse452shellXC
//
//  Created by Ben Stolovitz on 4/1/15.
//  Copyright (c) 2015 bstolovitz. All rights reserved.
//

#ifndef __cse452shellXC__Node__
#define __cse452shellXC__Node__

#include <stdio.h>
#ifdef __APPLE__
// because Apple is stupid and I hate everyone
#include <OpenGL/glu.h>
#else
#include <Windows.h>
#include <GL/glu.h>
#endif
#include <vector>

#include "../vecmath/Vector3.h"

#include "IDrawable.h"
#include "ITransform.h"

class Node : public IDrawable {
    public:
        Node() : _valid(false) {};
        Node(IDrawable* child)
        : _child(child), _valid(true) {};
    
        ~Node();
    
        Node* setChild(IDrawable* child);
        Node* addTransform(ITransform* t);
        bool isValid() const;
    
        void draw() const;
    
    private:
        bool _valid = false;
        IDrawable* _child = nullptr;
    
        std::vector<ITransform*> _transforms;
};

#endif /* defined(__cse452shellXC__Node__) */
