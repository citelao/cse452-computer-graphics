#include "../cse452.h"
#include "../sceneview/MyScene.h"
#include "RenderingInterface.h"
#include <FL/gl.h>
#include <cfloat>

void MyScene::render(int type, int width, int height, unsigned char* pixels) {
    if (!isLoaded) {
        return;
    }

    // Add your rendering code here.
    // Keep track of your progress as a value between 0 and 1
    // so the progress bar can update as the rendering progresses
    switch (type) {
        case RenderingUI::RENDER_SCANLINE:  break;
        case RenderingUI::RENDER_RAY_TRACING:  break;
        case RenderingUI::RENDER_PATH_TRACING:  break;
        default: break;
    }
    
    progress = 0;
    
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            auto rendered = (row * width + col);
            auto index = 3 * rendered;
            progress = (double)rendered / (double)width * (double)height;
            
            auto eye = camera.getEye();
            auto pt = Point3(2.0 * ((double)col / (double)width) - 1.0, 1.0 - 2.0 * ((double)row / (double)height), 0.0);
            
            auto offsetpt = camera.getCameraToWorld() * camera.getDInv() * pt;
            
            if (pt[0] < -0.9 && pt[1] < -0.9) {
//                pixels[index    ] = 255.0f * c[0];
//                pixels[index + 1] = 255.0f;
                pixels[index + 2] = 255.0f;
            } else {
            
                Color c = cast(offsetpt, (offsetpt - eye).unit());
    //            Color c = cast(offsetpt, Vector3(0,0,1));
                pixels[index    ] = 255.0f * c[0];
                pixels[index + 1] = 255.0f * c[1];
                pixels[index + 2] = 255.0f * c[2];
            }
        }
        
        if(stopRequested) {
            return;
        }
    }
}

// Ah, the actual raycasting function!
Color MyScene::cast(Point3 pt, Vector3 dir) {
    // find the closest intersection
    double a, b, c;
    Vector3 e;
    Point3 d;
    if(root->intersect(pt, dir).getFirstHit(a, b, c, d, e)) {
        return Color(1, 0, 0);
    }
    
    // render the colors right!
    // - diffuse
    // - reflection
    // - refraction
    
    return Color(0, 1, 1);
}

void MyScene::stopRender()
{
    // Because this is threaded code, this function
    // can be called in the middle of your rendering code.
    // You should then stop at the next scanline
    stopRequested = true;
    progress = 1;
}

double MyScene::getRenderProgress() {
    // return the current progress as a value between 0 and 1
    return progress;
}

// add extra methods here

