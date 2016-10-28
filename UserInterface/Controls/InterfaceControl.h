/* CHANGELOG
 * Written by Josh Grooms on 20161023
 */

#pragma once
#include "Geometry/Path2D.h"
//#include "Imaging/Color4.h"
#include "Interfaces/IInterfaceControl.h"
#include "Interfaces/IRenderable2D.h"
//#include "Math/Vector4.h"
#include "Spatial/Area.h"
#include "Spatial/Border.h"



namespace Cyclone
{
    namespace 
    { 
        using namespace SVG;
        using namespace Utilities; 
    }

    namespace UI
    {
        struct ControlStyle
        {
            Color4      BackgroundColor;
            Area        BackgroundArea;
            Color4      BorderColor;
            Border      BorderWidth;
            Border      BorderRadius;
            Color4      FontColor;
            string      FontName;
            float       FontSize;
            uint        FontWeight;
            Color4      ForegroundColor;
            Border      Margin;
            Border      Padding;
        };


        class InterfaceControl : 
            public virtual IInterfaceControl,
            public virtual IRenderable2D<float>
        {
            public:
                
                /** PROPERTIES **/
                virtual bool IsEnabled()                            const override { return _isEnabled; }
                virtual IInterfaceControl& Parent()                 const override { return *_parent; }
                virtual VertexTopologies Topology()                 const override { return _shape->Topology(); }

                virtual InterfaceControl& IsEnabled(bool value)     { _isEnabled = value; }



                /** DESTRUCTOR **/
                virtual ~InterfaceControl() { }



                /** UTILITIES **/
                virtual void Fill()     const override { _shape->Fill(); }
                virtual void Stroke()   const override { _shape->Stroke(); }



            protected:

                InterfaceControl() : 
                    _isEnabled(true),
                    _parent(nullptr),
                    _shape(nullptr)
                {

                }



            private:
                
                bool                _isEnabled;
                InterfaceControl*   _parent;
                Path2D*             _shape;


        };

    }
}
