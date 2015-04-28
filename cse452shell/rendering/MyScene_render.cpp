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
            auto pt = Point3(1.0 - 2.0 * ((double)col / (double)width), 2.0 * ((double)row / (double)height) - 1.0, 0.0);
            
            auto offsetpt = camera.getCameraToWorld() * camera.getDInv() * pt;
            
            Color c = cast(offsetpt, (offsetpt - eye).unit());
            pixels[index    ] = (c[0] > 1.0) ? 255 : 255.0f * c[0];
            pixels[index + 1] = (c[1] > 1.0) ? 255 : 255.0f * c[1];
            pixels[index + 2] = (c[2] > 1.0) ? 255 : 255.0f * c[2];
        }
        
        if(stopRequested) {
            return;
        }
    }
}

// Ah, the actual raycasting function!
Color MyScene::cast(Point3 pt, Vector3 dir, int iterations) {
    // find the closest intersection
    double a, b, c;
    Vector3 normal;
    Point3 castpt;
    auto intersect = root->intersect(pt, dir);
    auto shape = std::get<0>(intersect);
    auto hr = std::get<1>(intersect);
    
    Color returnColor = Color(0,0,0);
    
    if(hr.getFirstHit(a, b, c, castpt, normal)) {
        // Diffuse color
        Color diffuseColor = Color(0,0,0);
        // Color diffuseColor = shape->ambient;
        for (auto l : lights) {
            auto intersect = root->intersect(castpt, (l.getPos() - castpt).unit());
            auto hr = std::get<1>(intersect);
            auto hitshape = std::get<0>(intersect);
            
            double t, b, c;
            Vector3 e;
            Point3 hitpt;
            
            hr.sortHits();
            auto hit = hr.getFirstHit(t, b, c, hitpt, e);
            while (hit && t < 0.000000001) {
                hr.removeFirstHit();
                hit = hr.getFirstHit(t, b, c, hitpt, e);
            }
            
            if(!hit || (hitpt - castpt).lengthSquared() > (l.getPos() - castpt).lengthSquared()) {
                auto mult = ((l.getPos() - castpt).unit() * (normal));
                
                if(mult < 0) {
                    std::cout << "neg mult " << t << " " << mult << std::endl;
                    mult = 0;
                }
                
                diffuseColor += mult * l.getColor() * shape->diffuse;
            }
        }
        
        // Reflection color
        auto reflectedDir = (dir - 2 * (dir * normal.unit()) * normal.unit()).unit();
        Color reflectColor = diffuseColor;
        if (iterations < MAX_BOUNCES && shape->reflect.getMax() > 0.0000001) {
            reflectColor = cast(castpt, reflectedDir, iterations + 1);
        }
        
        // Refraction
        
        Color difPart = (Color(1,1,1) - shape->reflect) * diffuseColor;
        Color refPart = (shape->reflect) * reflectColor;
        Color returnColor = difPart + refPart;
        
        return returnColor;
    }
    
    // Otherwise return black.
    return Color(0, 0, 0);
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

