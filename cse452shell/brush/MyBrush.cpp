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
    mask = std::vector<double>(radius + 1);
    switch (filter) {
        case BRUSH_SPECIAL:
            for (double i = 0; i <= radius; i += 1) {
                mask[i] = (cos(pi * (i / (double) radius))/2) + 0.5;
            }
            break;
            
        case BRUSH_GAUSSIAN:
            for (double i = 0; i <= radius; i += 1) {
                mask[i] = scale * a * exp(- pow(i-b, 2)/(2 * pow(c, 2)));
            }
            break;
            
        case BRUSH_QUADRATIC:
            for (double i = 0; i <= radius; i += 1) {
                mask[i] = sqrt(1 - pow(i, 2) / pow((double)radius, 2));
            }
            break;
            
        case BRUSH_LINEAR:
            for (double i = 0; i <= radius; i += 1) {
                mask[i] = 1 - i / (double)radius;
            }
            break;
            
        case BRUSH_CONSTANT:
        default:
            for (int i = 0; i <= radius; i++) {
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
    
    for (double i = max(-radius, -mouseDrag[0]); i <= min(imageWidth - mouseDrag[0], radius); i++) {
        for (double j = max(-radius, -mouseDrag[1]); j <= min(imageHeight - mouseDrag[1], radius); j++) {
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
    
    // mx + b - y < 0 => point above line
    //      m = (y1 - y0)/(x1 - x0)
    //      b = y intercept
    //
    //      m(x1) + b - y1 = 0
    //      b = y1 - m(x1)
    //      b = y1 - (y1 - y0)x1/(x1 - x0)
    //
    // == ax - by + c
    //      a = y1 - y0
    //      b = x1 - x0
    //      c = y1(x1 - x0) - (y1 - y0)x1
    //        = y1x1 - y1x0 - y1x1 + y0x1
    //        = y0 * x1 - y1 * x0
    //
    // let f(x, y) be posn of point
    //
    // for e or ne decn, check f(x+1, y + .5)
    //  = h(x, y) = a(x+1) - b(y+.5) + c
    //  = ax + a - by - .5b + c
    //  =insign= 2ax + 2a - 2by - b + 2c
    //
    //  h(x+1, y) = h(x + y) + 2a
    //  h(x+1, y+1) = h(x+y) + 2a - 2b
    //
    // for ne or n decn, check f(x + .5, y + 1)
    //  = h(x,y) = ax + .5a - by - b + c
    //  =insign= 2ax + a - 2by - 2b + 2c
    //
    //  h(x, y+1) = h(x+y) - 2b;
    //  h(x+1, y+1) = h(x+y) - 2b + 2a;
    //
    // so let
    //      A = 2a = 2 * (y1 - y0)
    //      B = -2b = 2 * (x0 - x1)
    //      C = 2c = 2 * (y0 * x1 - y1 * x0)
    //      H = h(0,0) = A + B/2 + C = 2A + B + 2C
    
    // auto-flip points so we always draw L -> R
    int x1 = (mouseDown[0] < mouseDrag[0]) ? mouseDrag[0] : mouseDown[0];
    int y1 = (mouseDown[0] < mouseDrag[0]) ? mouseDrag[1] : mouseDown[1];
    
    int x0 = (mouseDown[0] < mouseDrag[0]) ? mouseDown[0] : mouseDrag[0];
    int y0 = (mouseDown[0] < mouseDrag[0]) ? mouseDown[1] : mouseDrag[1];
    
    // vague bounds checking
    double slope = ((double)y1 - (double)y0) / ((double)x1 - (double)x0);
    int yint = y1 - slope * x1;
    if (x1 > imageWidth) {
        // y = mx + b
        x1 = imageWidth + radius / 2;
        y1 = slope * x1 + yint;
    }
    
    if (x0 < 0) {
        x0 = - radius / 2;
        y0 = slope * x0 + yint;
    }
    
    int a = abs(2 * (y1 - y0));
    int b = 2 * (x0 - x1);
    
    // debug code
    //std::cout << "0: (" << x0 << ", " << y0 << ") 1: (" << x1 << ", " << y1 << ")" << std::endl;
    //std::cout << "a: " << a << " b: " << b << std::endl;
    
    if(abs(a) > abs(b)) {
        // traverse by y
        int h = a + 2 * b;
        int x = 0;
        for (int y = 0; y < abs(y1 - y0); y++) {
            for (int i = - radius / 2; i < radius; i++) {
                if (x0 + x + i > imageWidth) {
                    break;
                }
                
                if (x0 + x + i < 0) {
                    continue;
                }
                
                if (y1 < y0) {
                    putPixel(x0 + x + i, y0 - y, colBrush);
                } else {
                    putPixel(x0 + x + i, y0 + y, colBrush);
                }
            }
            
            if(h > 0) {
                // go n
                h += b;
            } else  {
                // go ne
                x++;
                h += a + b;
            }
        }
    } else {
        // traverse by x
        int h = 2 * a + b;
        int y = 0;
        for (int x = max(0, - x0); x < min(x1 - x0, imageWidth - x0); x++) {
            for (int i = - radius / 2; i < radius; i++) {
                if (y1 < y0) {
                    putPixel(x0 + x, y0 - y + i, colBrush);
                } else {
                    putPixel(x0 + x, y0 + y + i, colBrush);
                }
            }
            
            if(h < 0) {
                // go e
                h += a;
            } else  {
                // go ne
                y++;
                h += a + b;
            }
        }
    }
}


void MyBrush::drawCircle() {
    // draw a thick circle at mouseDown with radius r
    // the width of the circle is given by the current brush radius
    const int thickradius = brushUI->getRadius();
    const Color colBrush = brushUI->getColor();
    
    const int radius = sqrt(pow(mouseDown[0] - mouseDrag[0], 2) + pow(mouseDown[1] - mouseDrag[1], 2)) + (thickradius / 2);
    
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
    
    int ox = 0;
    int oy = - radius;
    int oh = 5 + 2 * oy;
    int ode = 12;
    int odne = 8 * oy + 18;
    
    int ix = 0;
    int iy = - radius + thickradius;
    int ih = 5 + 2 * iy;
    int ide = 12;
    int idne = 8 * iy + 18;
    
    while (ox <= -oy) {
        for (int i = oy; i <= iy; i++) {
            putPixel(mouseDown[0] + ox, mouseDown[1] + i, colBrush);
            putPixel(mouseDown[0] + ox, mouseDown[1] - i, colBrush);
            putPixel(mouseDown[0] - ox, mouseDown[1] + i, colBrush);
            putPixel(mouseDown[0] - ox, mouseDown[1] - i, colBrush);
            putPixel(mouseDown[0] + i, mouseDown[1] + ox, colBrush);
            putPixel(mouseDown[0] + i, mouseDown[1] - ox, colBrush);
            putPixel(mouseDown[0] - i, mouseDown[1] + ox, colBrush);
            putPixel(mouseDown[0] - i, mouseDown[1] - ox, colBrush);
        }
        
        // If we want to move NE, do so
        // Otherwise, E
        if(oh > 0) {
            ox++;
            oy++;
            
            oh += odne;
            ode += 8;
            odne += 16;
        } else {
            ox++;
            
            oh += ode;
            ode += 8;
            odne += 8;
        }
        
        if(ih > 0) {
            ix++;
            iy++;
            
            ih += idne;
            ide += 8;
            idne += 16;
        } else {
            ix++;
            
            ih += ide;
            ide += 8;
            idne += 8;
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
