#ifndef OWNCRAFT_PLAYER_H
#define OWNCRAFT_PLAYER_H

#include "osgViewer/Viewer"
#include "osgGA/FirstPersonManipulator"
#include "osg/ref_ptr"

class Player {
public:

    class Manipulator : public osgGA::FirstPersonManipulator {
    public:
        Manipulator() {}

    protected:
        //virtual bool performMouseDeltaMovement(const float dx, const float dy);

        //virtual bool handleMouseMove(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &us);

        virtual bool handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa);

        virtual bool performMovement();

    private:
        osg::Timer mainTimer;
    };

	Player() : manipulator(new Manipulator()) {
	}

    osg::ref_ptr<osgGA::CameraManipulator> getManipulator() const {
		return manipulator;
	}

private:
	osg::ref_ptr<osgGA::CameraManipulator> manipulator;
};


#endif // OWNCRAFT_PLAYER_H