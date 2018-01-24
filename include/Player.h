#ifndef OWNCRAFT_PLAYER_H
#define OWNCRAFT_PLAYER_H

#include <3rd-party/osg/ShapeDrawable>
#include "osgViewer/Viewer"
#include "osgGA/FirstPersonManipulator"
#include "osg/ref_ptr"

class Player {
public:

    class Manipulator : public osgGA::FirstPersonManipulator {
    public:
        Manipulator() {}

    protected:
        virtual bool performMouseDeltaMovement(const float dx, const float dy);

        virtual bool handleMouseMove(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &us);

        virtual bool handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa);

		virtual bool handleKeyDown(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &us);

		virtual bool handleKeyUp(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &us);

		//virtual bool performMovementLeftMouseButton( const double /*eventTimeDelta*/, const double dx, const double dy );
    private:
        osg::Timer mainTimer;
		std::map<int, bool> keyDowns;
    };

	Player() : manipulator(new Manipulator()) {
		osg::Box* box = new osg::Box(osg::Vec3(0.0f, 0.0f, 0.0f), 1.0f, 1.0f, 2.0f);
		collider = new osg::ShapeDrawable(box);
	}

    osg::ref_ptr<osgGA::CameraManipulator> getManipulator() const {
		return manipulator;
	}

private:
	osg::ref_ptr<osgGA::CameraManipulator> manipulator;
	osg::ref_ptr<osg::Node> collider;
};


#endif // OWNCRAFT_PLAYER_H