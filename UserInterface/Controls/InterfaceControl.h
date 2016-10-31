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
            Area        BackgroundArea;
            Color4      BackgroundColor;
            Color4      BorderColor;
            Border      BorderRadius;
            Border      BorderWidth;
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
                virtual IInterfaceControl* Parent()                 const override { return _parent; }
                virtual Path2D* Shape()                             const = 0;
                //virtual VertexTopologies Topology()                 const override { return _shape->Topology(); }



                virtual InterfaceControl& BackgroundColor(const Color4& value)      { _style.BackgroundColor = value; return *this; }
                virtual InterfaceControl& BorderColor(const Color4& value)          { _style.BorderColor = value; return *this; }
                virtual InterfaceControl& BorderRadius(const Border& value)         { _style.BorderRadius = value; return *this; }
                virtual InterfaceControl& BorderWidth(const Border& value)          { _style.BorderWidth = value; return *this; }

                virtual InterfaceControl& IsClippingEnabled(bool value)            { _isClippingEnabled = value; return *this; }
                virtual InterfaceControl& IsEnabled(bool value)                    { _isEnabled = value; return *this; }
                //virtual InterfaceControl& Style(const ControlStyle& value)         { _style = value; Restyle(); return *this; }
                //virtual InterfaceControl& Parent(InterfaceControl* value)           { _parent = value; }



                /** DESTRUCTOR **/
                virtual ~InterfaceControl() { }



                /** UTILITIES **/
                virtual void Configure(const ControlStyle& style)
                {
                    _style = style;
                    if (!Shape()) { return; }

                    Shape()->
                         StrokeWidth(style.BorderWidth.Left)
                        .PrimaryColor(style.BackgroundColor)
                        .SecondaryColor(style.BorderColor);
                }

                virtual void Fill()     const override 
                {
                    if (Shape())
                        Shape()->Fill(); 
                }
                virtual void Stroke()   const override 
                {
                    if (Shape())
                        Shape()->Stroke(); 
                }
                virtual void Update()   const override
                {
                    if (Shape())
                        Shape()->Update();
                }

            protected:

                /** DATA**/
                //Path2D*             _shape;
                ControlStyle        _style;


                InterfaceControl() : 
                    _isClippingEnabled(true),
                    _isEnabled(true),
                    _parent(nullptr)
                    //_shape(nullptr)
                {

                }


                //virtual void Restyle() = 0;

            private:
                
                bool                _isClippingEnabled;
                bool                _isEnabled;
                InterfaceControl*   _parent;


        };

    }
}
