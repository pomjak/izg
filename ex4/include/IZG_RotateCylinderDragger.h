/* -*-c++-*- OpenSceneGraph - Copyright (C) 1998-2006 Robert Osfield
 *
 * This library is open source and may be redistributed and/or modified under
 * the terms of the OpenSceneGraph Public License (OSGPL) version 0.0 or
 * (at your option) any later version.  The full license is in LICENSE file
 * included with this distribution, and on the openscenegraph.org website.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * OpenSceneGraph Public License for more details.
*/
//osgManipulator - Copyright (C) 2007 Fugro-Jason B.V.

#pragma once

#include <osgManipulator/Dragger>
#include <osgManipulator/Projector>

namespace osgManipulator {

/**
 * Dragger for performing 3D rotation on a cylinder.
 */
class IZG_RotateCylinderDragger : public Dragger
{
    public:

        IZG_RotateCylinderDragger();

        META_OSGMANIPULATOR_Object(osgManipulator,IZG_RotateCylinderDragger)

        /**
         * Handle pick events on dragger and generate TranslateInLine commands.
         */
        virtual bool handle(const PointerInfo& pi, const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& us);

        /** Setup default geometry for dragger. */
        void setupDefaultGeometry();

        /** Set/Get color for dragger. */
        inline void setColor(const osg::Vec4& color) { _color = color; setMaterialColor(_color,*this); }
        inline const osg::Vec4& getColor() const { return _color; }

        /**
         * Set/Get pick color for dragger. Pick color is color of the dragger
         * when picked. It gives a visual feedback to show that the dragger has
         * been picked.
         */
        inline void setPickColor(const osg::Vec4& color) { _pickColor = color; }
        inline const osg::Vec4& getPickColor() const { return _pickColor; }



    protected:

        virtual ~IZG_RotateCylinderDragger();
    
        osg::Geometry* createCircleGeometry(float radius, unsigned int numSegments);

    protected:
        osg::ref_ptr<osgManipulator::PlaneProjector> _projector;

        osg::Vec3d  _startProjectedPoint;

        osg::Vec4 _color;
        osg::Vec4 _pickColor;
};


}
