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
    
    // x^2 + y^2 - R^2 > 0 => pt outside of circle
    // (x+1)^2 + (y+.5)^2 - R^2 > 0 => next pt outside of circle
    // = x^2+2x+1 + y^2+.5y+.25 - R^2
    // =in sign= 4x^2+8x+8 + 4y^2+2y+1 - 4R^2
    // if > 0:
    //      move up, too
    // else:
    //      just move over
    //
    // h(x,y) = f(x+1, y+.5)
    //      = 4(x+1)^2+8(x+1)+8 + 4(y+1)^2+2(y+1)+1 - 4R^2
    //      = 4x^2+8x+4 + 8x+8 + 4y^2+8y+4 + 2y+2 + 1
    //      = 4x^2+16x+12 + 4y^2+10y+6+1
    //      = 4x^2+16x+4y^2+10y+19
    // how does x change?
    // h(x+1,y) - E move
    //      4(x+1)^2+8(x+1)+8 + 4y^2+2y+1 - 4R^2
    //      = h(x,y) + 8x + 4 + 8
    //      => h(x+1,y) = h(x,y) + 8x + 12
    // h(x+1,y+1) - NE move
    //      4(x+1)^2+8(x+1)+8 + 4(y+1)^2+2(y+1)+1 - 4R^2
    //      === 4(x^2+2x+1)+8+16 + 4(y^2+2y+1)+2y+2+1 - 4R^2
    //      = h(x,y) + 8x+4+8 + 8y+4+2
    //      = h(x,y) + 8x+12+8y+6
    //      = h(x,y) + 8x+8y+18
    
    int x = 0;
    int y = - radius;
    int h = 5 - 4 * radius * radius + (4 * y * y) + 2 * y;
    int de = 12;
    int dne = 8 * y + 18;
    while (x <= -y) {
        putPixel(mouseDrag[0] + x, mouseDrag[1] + y, colBrush);
        putPixel(mouseDrag[0] + x, mouseDrag[1] - y, colBrush);
        putPixel(mouseDrag[0] - x, mouseDrag[1] + y, colBrush);
        putPixel(mouseDrag[0] - x, mouseDrag[1] - y, colBrush);
        
        putPixel(mouseDrag[0] + y, mouseDrag[1] + x, colBrush);
        putPixel(mouseDrag[0] + y, mouseDrag[1] - x, colBrush);
        putPixel(mouseDrag[0] - y, mouseDrag[1] + x, colBrush);
        putPixel(mouseDrag[0] - y, mouseDrag[1] - x, colBrush);

        // If we want to move NE, do so
        // Otherwise, E
        if(h > 0) {
            x++;
            y++;
            
            h += dne;
            de += 8;
            dne += 16;
        } else {
            x++;
            
            h += de;
            de += 8;
            dne += 8;
        }
    }
    
//    for (int i = 0; i < radius; i++) {
//        Color origL = getPixel(mouseDrag[0] - i, mouseDrag[1]);
//        Color origR = getPixel(mouseDrag[0] + i, mouseDrag[1]);
//        
//        Color interpL = colBrush * mask[i] + origL * (1.0f - mask[i]);
//        Color interpR = colBrush * mask[i] + origR * (1.0f - mask[i]);
//
//        putPixel(mouseDrag[0] - i, mouseDrag[1], interpL);
//        putPixel(mouseDrag[0] + i, mouseDrag[1], interpR);
//    }
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
