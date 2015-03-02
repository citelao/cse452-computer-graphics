#include "../cse452.h"
#include "Camera.h"
#include <cmath>
#include <FL/Fl.H>

void Camera::initialize(std::vector<std::string> changed) {
    if(changed.size() == 0) {
        // Assume all changed
        changed = {
            "_from",
            "_look",
            "_up",
            
            "_fov",
            
            "_width",
            "_height",
            
            "_near",
            "_far"
        };
    }
    
    if (std::find(changed.begin(), changed.end(), "_look") != changed.end()) {
        _n = -_look.unit();
        changed.push_back("_n");
    }
    
    if (std::find(changed.begin(), changed.end(), "_up") != changed.end() ||
        std::find(changed.begin(), changed.end(), "_n") != changed.end()) {
        _v = (_up - (_up * _n) * _n).unit();
        
        _u = (_v ^ _n).unit();
        
        changed.push_back("_v");
        changed.push_back("_u");
    }

    if (std::find(changed.begin(), changed.end(), "_width") != changed.end() ||
        std::find(changed.begin(), changed.end(), "_height") != changed.end()) {
        
        _aspect = (double)_width / (double)_height;
        
        changed.push_back("_aspect");
    }
    
    if (std::find(changed.begin(), changed.end(), "_from") != changed.end()) {
        _t = Matrix4(Vector4(1, 0, 0, -_from[0]),
                     Vector4(0, 1, 0, -_from[1]),
                     Vector4(0, 0, 1, -_from[2]),
                     Vector4(0, 0, 0, 1));
        
        _tinv = Matrix4(Vector4(1, 0, 0, _from[0]),
                        Vector4(0, 1, 0, _from[1]),
                        Vector4(0, 0, 1, _from[2]),
                        Vector4(0, 0, 0, 1));
        
        assert(Matrix4::identity().approxEqual(_t * _tinv));
        
        changed.push_back("_t");
        changed.push_back("_tinv");
    }
    
    if (std::find(changed.begin(), changed.end(), "_u") != changed.end() ||
        std::find(changed.begin(), changed.end(), "_v") != changed.end() ||
        std::find(changed.begin(), changed.end(), "_n") != changed.end()) {
        _r = Matrix4(Vector4(_u[0], _u[1], _u[2], 0),
                     Vector4(_v[0], _v[1], _v[2], 0),
                     Vector4(_n[0], _n[1], _n[2], 0),
                     Vector4(0, 0, 0, 1));
        
        _rinv = Matrix4(Vector4(_u[0], _v[0], _n[0], 0),
                        Vector4(_u[1], _v[1], _n[1], 0),
                        Vector4(_u[2], _v[2], _n[2], 0),
                        Vector4(0, 0, 0, 1));
        
        assert(Matrix4::identity().approxEqual(_r * _rinv));
        
        changed.push_back("_r");
        changed.push_back("_rinv");
    }
    
    if (std::find(changed.begin(), changed.end(), "_fov") != changed.end() ||
        std::find(changed.begin(), changed.end(), "_aspect") != changed.end()) {
        double thetaw = _fov;
        double thetah = _fov / _aspect;
        
        _sxy = Matrix4(Vector4(1 / tan(thetaw / 2), 0, 0, 0),
                       Vector4(0, 1 / tan(thetah / 2), 0, 0),
                       Vector4(0, 0, 1, 0),
                       Vector4(0, 0, 0, 1));
        
        _sxyinv = Matrix4(Vector4(tan(thetaw / 2), 0, 0, 0),
                          Vector4(0, tan(thetah / 2), 0, 0),
                          Vector4(0, 0, 1, 0),
                          Vector4(0, 0, 0, 1));
        
        assert(Matrix4::identity().approxEqual(_sxy * _sxyinv));
        
        changed.push_back("_sxy");
        changed.push_back("_sxyinv");
    }
    
    if (std::find(changed.begin(), changed.end(), "_far") != changed.end()) {
        _sxyz = Matrix4(Vector4(1 / _far, 0, 0, 0),
                        Vector4(0, 1 / _far, 0, 0),
                        Vector4(0, 0, 1 / _far, 0),
                        Vector4(0, 0, 0, 1));
        
        _sxyzinv = Matrix4(Vector4(_far, 0, 0, 0),
                           Vector4(0, _far, 0, 0),
                           Vector4(0, 0, _far, 0),
                           Vector4(0, 0, 0, 1));
        
        assert(Matrix4::identity().approxEqual(_sxyz * _sxyzinv));
        
        changed.push_back("_sxyz");
        changed.push_back("_sxyzinv");
    }
    
    if (std::find(changed.begin(), changed.end(), "_near") != changed.end() ||
        std::find(changed.begin(), changed.end(), "_far") != changed.end()) {
        double k = _near / _far;
        
        _d = Matrix4(Vector4(1, 0, 0, 0),
                     Vector4(0, 1, 0, 0),
                     Vector4(0, 0, 1 / (k - 1), k / (k - 1)),
                     Vector4(0, 0, -1, 0));
        
        _dinv = Matrix4(Vector4(1, 0, 0, 0),
                        Vector4(0, 1, 0, 0),
                        Vector4(0, 0, 0, -1),
                        Vector4(0, 0, (-1 + k) / k, 1 / k));
        
        assert(Matrix4::identity().approxEqual(_d * _dinv));
        
        changed.push_back("_d");
        changed.push_back("_dinv");
    }
    
    if (std::find(changed.begin(), changed.end(), "_sxy") != changed.end() ||
        std::find(changed.begin(), changed.end(), "_r") != changed.end() ||
        std::find(changed.begin(), changed.end(), "_t") != changed.end() ||
        std::find(changed.begin(), changed.end(), "_sxyinv") != changed.end() ||
        std::find(changed.begin(), changed.end(), "_rinv") != changed.end() ||
        std::find(changed.begin(), changed.end(), "_tinv") != changed.end()) {
        
        _wtc = _sxy * _r * _t;
        _ctw = _tinv * _rinv * _sxyinv;
        
        assert(Matrix4::identity().approxEqual(_wtc * _ctw));
        
        changed.push_back("_wtc");
        changed.push_back("_ctw");
    }
    
    if (std::find(changed.begin(), changed.end(), "_sxyz") != changed.end() ||
        std::find(changed.begin(), changed.end(), "_d") != changed.end()) {
        _proj = _d * _sxyz;
        _projinv = _sxyzinv * _dinv;
//
//        _proj = Matrix4(Vector4(1, 0, 0, 0),
//                        Vector4(0, 1, 0, 0),
//                        Vector4(0, 0, - 2 / _far, - (_near + _far) / (_far - _near)),
//                        Vector4(0, 0, 0, 1));
        
        changed.push_back("_proj");
    }
}

Camera::~Camera() {
}

// The following three should be unit length and orthogonal to each other
// u vector
Vector3 Camera::getRight() const
{
    return _u;
}

// v vector
Vector3 Camera::getUp() const
{
    return _v;
}

// - n vector
Vector3 Camera::getLook() const
{
    // l = -n
    return -_n;
}

double Camera::getSkew() const
{
    // Change this to implement the extra credit
    return 0.0;
}

double Camera::getAspectRatioScale() const
{
    return _aspect;
}

Point3 Camera::getProjectionCenter() const
{
    // Change this to implement the extra credit
    return Point3( 0.0, 0.0, 0.0 );
}

Matrix4 Camera::getProjection() const {
    // return the current projection and scale matrix
    return _proj;
}

Matrix4 Camera::getWorldToCamera() const {
    // return the current world to camera matrix
    // Rotation and translation
    return _wtc;
}

Matrix4 Camera::getRotationFromXYZ() const
{
    return _r;
}

Matrix4 Camera::getRotationToXYZ() const
{
    // return just the rotation matrix
    return _rinv;
}

Matrix4 Camera::getCameraToWorld() const {
    // return the current camera to world matrix
    // This is the inverse of the rotation, translation, and scale
    return _ctw;
}

int Camera::getWidth()  const{
    // return the current image width
    return _width;
}

int Camera::getHeight()  const{
    // return the current image height
    return _height;
}

Point3 Camera::getEye()  const{
    // return the current eye location
    return _from;
}

double Camera::getZoom() const
{
    return _width / 2 / tan(_fov / 2);
}

void Camera::setFrom(const Point3& from) {
    // set the current viewpoint (eye point)
    _from = from;
    initialize({"_from"});
}

void Camera::setAt(const Point3& at) {
    // set the point the camera is looking at
    _look = at - _from;
    initialize({"_look"});
}

void Camera::setLook(const Vector3& l) {
    // set the direction the camera is looking at
    _look = l;
    initialize({"_look"});
}

void Camera::setUp(const Vector3& up) {
    // set the upwards direction of the camera
    _up = up;
    initialize({"_up"});
}

void Camera::setWidthHeight(int w, int h) {
    // set the current width and height of the film plane
    _width = w;
    _height = h;
    initialize({"_width", "_height"});
}

void Camera::setZoom(double z) {
    // set field of view (specified in degrees)
    _fov = atan(_width / 2 / z);
    initialize({"_fov"});
}

void Camera::setNearFar(double n, double f) {
    // set the near and far clipping planes
    _near = n;
    _far = f;
    initialize({"_near", "_far"});
}

void Camera::setSkew( double d )
{
}

void Camera::setAspectRatioScale( double d )
{
    _height = (double)_width / d;
    initialize({"_height"});
}

void Camera::setProjectionCenter( const Point3 &p )
{
}

void Camera::moveForward(double dist) {
    Vector3 move = dist * (_from - Point3(0, 0, 0)).unit();
    
    _from -= move;
    initialize({"_from"});
}

void Camera::moveSideways(double dist) {
    Vector3 move = dist * (_u);
    
    _from += move;
    
    initialize({"_from"});
}

void Camera::moveVertical(double dist) {
    // move the camera vertically (along the up vector)
    // by the amount dist
    Vector3 move = dist * (_v);
    
    _from += move;
    initialize({"_from"});
}

void Camera::rotateYaw(double angle) {
    // rotate the camera left/right (around the up vector)
    // change look vector
    Matrix4 yaw = Matrix4::rotation(_v, angle);
    _look = yaw * _look;
    
    initialize({"_look"});
}

void Camera::rotatePitch(double angle) {
    // rotate the camera up/down (pitch angle)
    // change look vector
    Matrix4 pitch = Matrix4::rotation(_u, angle);
    _look = pitch * _look;
    
    initialize({"_look"});
}

void Camera::rotateAroundAtPoint(int axis, double angle, double focusDist) {
    // Rotate the camera around the right (0), up (1), or look (2) vector
    // around the point at eye + look * focusDist
    Matrix4 rot = Matrix4::identity();
    switch (axis) {
        case 0: // right
            rot = Matrix4::rotation(_u, angle);
            break;
            
        case 1: // up
            rot = Matrix4::rotation(_v, angle);
            break;
            
        case 2: //look
            /// ???
            break;
            
        default:
            break;
    }
    
    _look = rot * _look;
    initialize({"_look"});
}


void Camera::moveKeyboard( )
{
    // you may change key controls for the interactive
    // camera controls here, make sure you document your changes
    // in your README file

    std::cout << Fl::event_key() << std::endl;
    
    if (Fl::event_key('w') || Fl::event_key() == 'w')
        moveForward(+0.05);
    if (Fl::event_key('s') || Fl::event_key() == 's')
        moveForward(-0.05);
    if (Fl::event_key('a') || Fl::event_key() == 'a')
        moveSideways(-0.05);
    if (Fl::event_key('d') || Fl::event_key() == 'd')
        moveSideways(+0.05);
    if (Fl::event_key(FL_Up) || Fl::event_key() == 'i')
        moveVertical(+0.05);
    if (Fl::event_key(FL_Down) || Fl::event_key() == 'k')
        moveVertical(-0.05);
    if (Fl::event_key(FL_Left) || Fl::event_key() == 'j')
        rotateYaw(+0.05);
    if (Fl::event_key(FL_Right) || Fl::event_key() == 'l')
        rotateYaw(-0.05);
    if (Fl::event_key(FL_Page_Up) || Fl::event_key() == ',')
        rotatePitch(+0.05);
    if (Fl::event_key(FL_Page_Down) || Fl::event_key() == '.')
        rotatePitch(-0.05);
}
