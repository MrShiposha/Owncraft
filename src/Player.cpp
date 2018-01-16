#include <iostream>
#include <osgViewer/View>
#include "Player.h"

const float moveSpeed = 100;
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

bool Player::Manipulator::handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa)
{

    // Still use first person manipulator for camera movements (Inherited class function)
    osgGA::FirstPersonManipulator::handle(ea, aa);

    // Set the viewer's "eye" position, which is located at the center of the camera.
    osg::Vec3d eyePos;
    //osg::Matrix matrix = _viewer->getCameraManipulator()->getMatrix();
    osg::Matrix matrix = getMatrix();

    eyePos = matrix.getTrans();

    osg::Quat camRotation = matrix.getRotate();

    switch(ea.getEventType())
    {
        case(osgGA::GUIEventAdapter::KEYDOWN):
        {
            // Movement of the camera correlates with W, A, S, D
            switch(ea.getKey())
            {
                case 'w':
                    tempMov.z() = -moveSpeed;

                    break;
                case 'a':
                    tempMov.x() = -moveSpeed;

                    break;
                case 's':
                    tempMov.z() = moveSpeed;

                    break;
                case 'd':
                    tempMov.x() = moveSpeed;

                    break;
                default:
                    break;
            }

            default:
                break;
        }

        case(osgGA::GUIEventAdapter::KEYUP):
        {
            switch(ea.getKey())
            {
                case 'w':
                    tempMov.set(0, 0, 0);
                    break;
                case 'a':
                    tempMov.set(0, 0, 0);
                    break;
                case 's':
                    tempMov.set(0, 0, 0);
                    break;
                case 'd':
                    tempMov.set(0, 0, 0);
                    break;
                default:
                    break;
            }

            //default:
            break;
        }

    }
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

//bool Player::Manipulator::performMovementLeftMouseButton(const double dt, const double dx, const double dy) {
//    std::cout << "dx=" << dx << ", dy=" << dy << std::endl;
//    return FirstPersonManipulator::performMovementLeftMouseButton(dt, dx, dy);
//}
