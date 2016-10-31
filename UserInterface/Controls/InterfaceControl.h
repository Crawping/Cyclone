/* CHANGELOG
 * Written by Josh Grooms on 20161023
 */

#pragma once
#include "UIAPI.h"
#include "Geometry/Path2D.h"
#include "Interfaces/IInterfaceControl.h"
#include "Interfaces/IRenderable2D.h"
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

                UIAPI virtual InterfaceControl& BackgroundColor(const Color4& value);
                UIAPI virtual InterfaceControl& BorderColor(const Color4& value);
                UIAPI virtual InterfaceControl& BorderRadius(const Border& value);
                UIAPI virtual InterfaceControl& BorderWidth(const Border& value);

                UIAPI virtual InterfaceControl& IsClippingEnabled(bool value);
                UIAPI virtual InterfaceControl& IsEnabled(bool value);



                /** DESTRUCTOR **/
                virtual ~InterfaceControl() { }



                /** UTILITIES **/
                UIAPI virtual void Configure(const ControlStyle& style) override;



                /** RENDERING UTILITIES **/
                UIAPI virtual void Fill()     const override;
                UIAPI virtual void Stroke()   const override;
                UIAPI virtual void Update()   const override;

            protected:

                /** PROPERTY DATA**/
                ControlStyle        _style;



                /** CONSTRUCTOR **/
                UIAPI InterfaceControl();

            private:
                
                /** PROPERTY DATA**/
                bool                _isClippingEnabled;
                bool                _isEnabled;
                InterfaceControl*   _parent;


        };

    }
}
