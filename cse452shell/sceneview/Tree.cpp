//
//  Tree.cpp
//  cse452shellXC
//
//  Created by Ben Stolovitz on 4/1/15.
//  Copyright (c) 2015 bstolovitz. All rights reserved.
//

#include "Tree.h"

void Tree::addNode(Node* node) {
    nodes.push_back(node);
};

void Tree::draw() const {
    for (auto n : nodes) {
        n->draw();
    }
};