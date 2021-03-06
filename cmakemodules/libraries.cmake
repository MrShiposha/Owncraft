LINK_DIRECTORIES(lib/osg)
LINK_DIRECTORIES(lib/boost)

IF(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
	SET(BOOST_CRT_TYPE -gd)
	SET(CRT_TYPE d)
ELSE()
	SET(BOOST_CRT_TYPE )
	SET(CRT_TYPE )
ENDIF()


MACRO(LIB LIB_NAME)
	SET(LIBRARIES ${LIBRARIES} ${LIB_NAME}${CRT_TYPE}.lib)
ENDMACRO()

MACRO(BOOST_LIB LIB_NAME)
	SET(LIBRARIES ${LIBRARIES} libboost_${LIB_NAME}-vc141-mt${BOOST_CRT_TYPE}-x64-1_66.lib)
ENDMACRO()

LIB(OpenThreads)
LIB(osg)
LIB(osgAnimation)
LIB(osgFX)
LIB(osgGA)
LIB(osgManipulator)
LIB(osgParticle)
LIB(osgPresentation)
LIB(osgShadow)
LIB(osgSim)
LIB(osgTerrain)
LIB(osgText)
LIB(osgUI)
LIB(osgVolume)
LIB(osgWidget)
LIB(osgUtil)
LIB(osgDB)
LIB(osgViewer)

BOOST_LIB(filesystem)
BOOST_LIB(system)