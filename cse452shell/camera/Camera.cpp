#include "../cse452.h"
#include "Camera.h"
#include <cmath>
#include <FL/Fl.H>

void Camera::initialize() {
    _n = -_look.unit();
    _v = (_up - (_up * _n) * _n).unit();
    _u = (_v ^ _n).unit();
    
    _aspect = (double)_width / (double)_height;
    
    double thetaw = _fov / 180 * 3.1415;
    double thetah = _fov / 180 * 3.1415 / _aspect;
    
    double df = _far;
    
    double k = _near / _far;
    
    _wtc = Matrix4(
        Vector4(_u[0] / tan(thetaw/2) / df,
                _u[1] / tan(thetaw/2) / df,
                _u[2] / tan(thetaw/2) / df,
                - _from[0] * _u[0] / tan(thetaw / 2) / df
                - _from[1] * _u[1] / tan(thetaw / 2) / df
                - _from[2] * _u[2] / tan(thetaw / 2) / df),
        Vector4(_v[0] / tan(thetah/2) / df,
              _v[1] / tan(thetah/2) / df,
              _v[2] / tan(thetah/2) / df,
              - _from[0] * _v[0] / tan(thetah / 2) / df
              - _from[1] * _v[1] / tan(thetah / 2) / df
              - _from[2] * _v[2] / tan(thetah / 2) / df),
        Vector4(_n[0] / df,
                _n[1] / df,
                _n[2] / df,
                - (_n[0] * _from[0]) / df - (_n[1] * _from[1]) / df - (_n[2] * _from[2]) / df),
        Vector4(0, 0, 0, 1)
    );
    
    _ctw = Matrix4::identity();
    
    _proj = Matrix4(
        Vector4(1, 0, 0, 0),
        Vector4(0, 1, 0, 0),
        Vector4(0, 0, 1 / (k - 1), k / (k - 1)),
        Vector4(0, 0, -1, 0)
    );
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
    // return just the rotation matrix

    // Change this
    return Matrix4::identity();
}

Matrix4 Camera::getRotationToXYZ() const
{
    // return just the rotation matrix

    // Change this
    return Matrix4::identity();
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
    // Change this
    return 0;
}

void Camera::setFrom(const Point3& from) {
    // set the current viewpoint (eye point)
    _from = from;
    initialize();
}

void Camera::setAt(const Point3& at) {
    // set the point the camera is looking at
    _look = at - _from;
    initialize();
}

void Camera::setLook(const Vector3& l) {
    // set the direction the camera is looking at
    _look = l;
    initialize();
}

void Camera::setUp(const Vector3& up) {
    // set the upwards direction of the camera
    _up = up;
    initialize();
}

void Camera::setWidthHeight(int w, int h) {
    // set the current width and height of the film plane
    _width = w;
    _height = h;
    initialize();
}

void Camera::setZoom(double z) {
    // set field of view (specified in degrees)
}

void Camera::setNearFar(double n, double f) {
    // set the near and far clipping planes
    _near = n;
    _far = f;
    initialize();
}

void Camera::setSkew( double d )
{
}

void Camera::setAspectRatioScale( double d )
{
}

void Camera::setProjectionCenter( const Point3 &p )
{
}

void Camera::moveForward(double dist) {
    Vector3 move = dist * (_from - Point3(0, 0, 0)).unit();
    
    _from -= move;
    initialize();
}

void Camera::moveSideways(double dist) {
    Vector3 move = dist * (_v);
    
    _from -= move;
}

void Camera::moveVertical(double dist) {
    // move the camera vertically (along the up vector)
    // by the amount dist
    
    Vector3 move = dist * (_u);
    
    _from -= move;
}

void Camera::rotateYaw(double angle) {
    // rotate the camera left/right (around the up vector)
}

void Camera::rotatePitch(double angle) {
    // rotate the camera up/down (pitch angle)
}

void Camera::rotateAroundAtPoint(int axis, double angle, double focusDist) {
    // Rotate the camera around the right (0), up (1), or look (2) vector
    // around the point at eye + look * focusDist
}


void Camera::moveKeyboard( )
{
    // you may change key controls for the interactive
    // camera controls here, make sure you document your changes
    // in your README file

    if (Fl::event_key('w'))
        moveForward(+0.05);
    if (Fl::event_key('s'))
        moveForward(-0.05);
    if (Fl::event_key('a'))
        moveSideways(-0.05);
    if (Fl::event_key('d'))
        moveSideways(+0.05);
    if (Fl::event_key(FL_Up))
        moveVertical(+0.05);
    if (Fl::event_key(FL_Down))
        moveVertical(-0.05);
    if (Fl::event_key(FL_Left))
        rotateYaw(+0.05);
    if (Fl::event_key(FL_Right))
        rotateYaw(-0.05);
    if (Fl::event_key(FL_Page_Up))
        rotatePitch(+0.05);
    if (Fl::event_key(FL_Page_Down))
        rotatePitch(-0.05);
}
