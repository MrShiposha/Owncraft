#include <iostream>
#include <osgViewer/View>
#include "Player.h"

const float moveSpeed = 0.2;
const float inputTimeInterval = 0.02;

osg::Vec3d tempMov;
double maxTick = inputTimeInterval;

float getXnormalized(const osgGA::GUIEventAdapter &ea, float x) {
    return (x-ea.getXmin())/(ea.getXmax()-ea.getXmin())*2.0f-1.0f;
}
float getYnormalized(const osgGA::GUIEventAdapter &ea, float y) {
    return (y-ea.getYmin())/(ea.getYmax()-ea.getYmin())*2.0f-1.0f;
}

bool Player::Manipulator::performMouseDeltaMovement( const float dx, const float dy )
{
    // world up vector
    osg::CoordinateFrame coordinateFrame = getCoordinateFrame( _eye );
    osg::Vec3d localUp = getUpVector( coordinateFrame );

    rotateYawPitch( _rotation, dx, dy, localUp );
    //std::cout << "dx=" << dx << ", dy=" << dy << std::endl;

    return true;
}

bool Player::Manipulator::handleMouseMove(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &us) {
    float dx = ea.getXnormalized() - getXnormalized(ea, _mouseCenterX);
    float dy = ea.getYnormalized() - getYnormalized(ea, _mouseCenterY);

    if( dx == 0.f && dy == 0.f )
        return false;

    addMouseEvent( ea );
    centerMousePointer( ea, us );

    if( _ga_t0.get() == NULL || _ga_t1.get() == NULL )
        return false;

    return performMouseDeltaMovement( dx, dy );
}

osg::Vec3d getHPRfromQuat(osg::Quat quat){
// From: http://guardian.curtin.edu.au/cga/faq/angles.html
// Except OSG exchanges pitch & roll from what is listed on that
    double qx = quat.x();
    double qy = quat.y();
    double qz = quat.z();
    double qw = quat.w();

    double sqx = qx * qx;
    double sqy = qy * qy;
    double sqz = qz * qz;
    double sqw = qw * qw;

    double term1 = 2*(qx*qy+qw*qz);
    double term2 = sqw+sqx-sqy-sqz;
    double term3 = -2*(qx*qz-qw*qy);
    double term4 = 2*(qw*qx+qy*qz);
    double term5 = sqw - sqx - sqy + sqz;

    double heading = atan2(term1, term2);
    double pitch = atan2(term4, term5);
    double roll = asin(term3);

    return osg::Vec3d( pitch, roll, heading );
}

bool Player::Manipulator::handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa)
{

    // Still use first person manipulator for camera movements (Inherited class function)
    osgGA::FirstPersonManipulator::handle(ea, aa);

    // Set the viewer's "eye" position, which is located at the center of the camera.
    osg::Vec3d eyePos;
    //osg::Matrix matrix = _viewer->getCameraManipulator()->getMatrix();
    osg::Matrix matrix = getMatrix();

    eyePos = matrix.getTrans();

    auto fullCamRotation = getHPRfromQuat(matrix.getRotate());
    osg::Quat camRotation(fullCamRotation.z(), osg::Z_AXIS);

    //Do movement
    eyePos += camRotation * tempMov;
    matrix.setTrans(eyePos);

    // Check [mainTimer.time % (time divisor) == 0]
    if (mainTimer.time_s() >= maxTick)
    {
        //_viewer->getCameraManipulator()->setByMatrix(matrix);
        setByMatrix(matrix);
        maxTick += inputTimeInterval;
    }

    return false;
}

bool Player::Manipulator::handleKeyDown(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &us) {
    // Movement of the camera correlates with W, A, S, D
    switch(ea.getKey())
    {
        case 'w':
            tempMov.y() = moveSpeed;
            break;
        case 'a':
            tempMov.x() = -moveSpeed;
            break;
        case 's':
            tempMov.y() = -moveSpeed;
            break;
        case 'd':
            tempMov.x() = moveSpeed;
            break;

        case osgGA::GUIEventAdapter::KEY_Space:
            tempMov.z() = moveSpeed;
            break;
        case osgGA::GUIEventAdapter::KEY_Shift_L:
            tempMov.z() = -moveSpeed;
            break;

        default:
            return false;
    }
    keyDowns[ea.getKey()] = true;

    return true;
}

bool Player::Manipulator::handleKeyUp(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &us) {
    switch(ea.getKey())
    {
//                tempMov._v;
        case 'w':
            tempMov.y() = keyDowns['s'] ? -moveSpeed : 0;;
            break;
        case 'a':
            tempMov.x() = keyDowns['d'] ? moveSpeed : 0;
            break;
        case 's':
            tempMov.y() = keyDowns['w'] ? moveSpeed : 0;
            break;
        case 'd':
            tempMov.x() = keyDowns['a'] ? -moveSpeed : 0;;
            break;

        case osgGA::GUIEventAdapter::KEY_Space:
            tempMov.z() = keyDowns[osgGA::GUIEventAdapter::KEY_Shift_L] ? -moveSpeed : 0;
            break;
        case osgGA::GUIEventAdapter::KEY_Shift_L:
            tempMov.z() = keyDowns[osgGA::GUIEventAdapter::KEY_Space] ? moveSpeed : 0;
            break;

        default:
            return false;
    }
    keyDowns[ea.getKey()] = false;

    return true;
}

//bool Player::Manipulator::performMovementLeftMouseButton(const double dt, const double dx, const double dy) {
//    std::cout << "dx=" << dx << ", dy=" << dy << std::endl;
//    return FirstPersonManipulator::performMovementLeftMouseButton(dt, dx, dy);
//}
