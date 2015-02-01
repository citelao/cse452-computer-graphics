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
    
    // Gaussian const
    // TODO move
    const double scale = 5;
    const double sd = 20;
    const double pi = 3.14159265358979323846;
    const double a =  1 / (sd * sqrt(2 * pi));
    const double b = 0;
    const double c = sd;
    
    // Create the mask, a 1D array from 0-radius of the different values.
    mask = std::vector<double>(radius);
    switch (filter) {
        case BRUSH_GAUSSIAN:
            for (double i = 0; i < radius; i += 1) {
                mask[i] = scale * a * exp(- ((i-b) * (i-b))/(2 * c * c));
            }
            break;
            
        case BRUSH_QUADRATIC:
            for (double i = 0; i < radius; i += 1) {
                mask[i] = sqrt(1 - (i * i) / ((double)radius * (double)radius));
            }
            break;
            
        case BRUSH_LINEAR:
            for (double i = 0; i < radius; i += 1) {
                mask[i] = ((double)radius - i) / (double)radius;
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
    const double pixelFlow = brushUI->getFlow();
    const Color colBrush = brushUI->getColor();
    
    for (double i = -radius; i <= radius; i++) {
        for (double j = -radius; j <= radius; j++) {
            double curR = sqrt((i*i) + (j*j));
            double bw = curR - (int)curR;
            if(curR > radius) {
                continue;
            }
            
            Color orig = getPixel(mouseDrag[0] + i, mouseDrag[1] + j);
            
            double curMask = mask[curR] * (1 - bw) + mask[curR + 1] * bw;
            Color interp = colBrush * curMask + orig * (1.0f - curMask);
            
            putPixel(mouseDrag[0] + i, mouseDrag[1] + j, interp);

        }
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
    const int thickradius = brushUI->getRadius();
//    const double pixelFlow = brushUI->getFlow();
    const Color colBrush = brushUI->getColor();
    
    const int radius = sqrt(pow(mouseDown[0] - mouseDrag[0], 2) + pow(mouseDown[1] - mouseDrag[1], 2));
    
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
        putPixel(mouseDown[0] + x, mouseDown[1] + y, colBrush);
        putPixel(mouseDown[0] + x, mouseDown[1] - y, colBrush);
        putPixel(mouseDown[0] - x, mouseDown[1] + y, colBrush);
        putPixel(mouseDown[0] - x, mouseDown[1] - y, colBrush);
        
        putPixel(mouseDown[0] + y, mouseDown[1] + x, colBrush);
        putPixel(mouseDown[0] + y, mouseDown[1] - x, colBrush);
        putPixel(mouseDown[0] - y, mouseDown[1] + x, colBrush);
        putPixel(mouseDown[0] - y, mouseDown[1] - x, colBrush);
        
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
