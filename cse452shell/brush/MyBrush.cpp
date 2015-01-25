#include "cse452.h"
#include "MyBrush.h"
#include "BrushInterface.h"
#include <cmath>
#include <iostream>

void MyBrush::changedBrush() {
    // this is called anytime the brush type or brush radius changes
    // it should recompute the brush mask appropriately
    const int radius = brushUI->getRadius();
    const BrushType filter = brushUI->getBrushType();
    
    // Create the mask, a 1D array from 0-radius of the different values.
    mask = std::vector<float>(radius);
    switch (filter) {
        case BRUSH_QUADRATIC:
            for (float i = 0; i < radius; i += 1) {
                mask[i] = sqrt(1 - (i * i) / ((float)radius * (float)radius));
            }
            break;
            
        case BRUSH_LINEAR:
            for (float i = 0; i < radius; i += 1) {
                mask[i] = ((float)radius - i) / (float)radius;
            }
            break;
            
        case BRUSH_CONSTANT:
        default:
            for (int i = 0; i < radius; i++) {
                mask[i] = 1.0f;
            }
            break;
    }
}

void MyBrush::drawBrush( ) {
    // apply the current brush mask to image location (x,y)
    // the mouse location is in mouseDrag

    const int radius = brushUI->getRadius();
    const float pixelFlow = brushUI->getFlow();
    const Color colBrush = brushUI->getColor();
    
    for (int i = 0; i < radius; i++) {
        Color origL = getPixel(mouseDrag[0] - i, mouseDrag[1]);
        Color origR = getPixel(mouseDrag[0] + i, mouseDrag[1]);
        
        Color interpL = colBrush * mask[i] + origL * (1.0f - mask[i]);
        Color interpR = colBrush * mask[i] + origR * (1.0f - mask[i]);

        putPixel(mouseDrag[0] - i, mouseDrag[1], interpL);
        putPixel(mouseDrag[0] + i, mouseDrag[1], interpR);
    }
}

void MyBrush::drawLine( ) {
    // draw a thick line from mouseDown to mouseDrag
    // the width of the line is given by the current brush radius
    const int radius = brushUI->getRadius();
    const Color colBrush = brushUI->getColor();
}


void MyBrush::drawCircle() {
    // draw a thick circle at mouseDown with radius r
    // the width of the circle is given by the current brush radius
}


void MyBrush::drawPolygon() {
    // draw a polygon with numVertices whos coordinates are stored in the
    // polygon array: {x0, y0, x1, y1, ...., xn-1, yn-1}
}

void MyBrush::filterRegion( ) {
    // apply the filter indicated by filterType to the square
    // defined by the two corner points mouseDown and mouseDrag
    // these corners are not guarenteed to be in any order
    // The filter width is given by the brush radius
}
