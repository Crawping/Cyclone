/* CHANGELOG
 * Written by Josh Grooms on 20161023
 */

#pragma once
#include "UIAPI.h"
#include "Controls/ControlStyle.h"
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
        class InterfaceControl : 
            public virtual IInterfaceControl,
            public virtual IRenderable2D<float>
        {
            public:
                
                /** PROPERTIES **/
                virtual bool IsEnabled()                            const override { return _isEnabled; }
                virtual IInterfaceControl* Parent()                 const override { return _parent; }
                virtual const ControlStyle& Style()                 const override { return _style; }
                virtual const Path2D& Shape()                       const override = 0;

                virtual const Color4& BackgroundColor()             const { return _style.BackgroundColor; }
                virtual const Color4& BorderColor()                 const { return _style.BorderColor; }
                virtual const Border& BorderRadius()                const { return _style.BorderRadius; }
                virtual const Border& BorderWidth()                 const { return _style.BorderWidth; }

                UIAPI virtual InterfaceControl& BackgroundColor(const Color4& value);
                UIAPI virtual InterfaceControl& BorderColor(const Color4& value);
                UIAPI virtual InterfaceControl& BorderRadius(const Border& value);
                UIAPI virtual InterfaceControl& BorderWidth(const Border& value);

                UIAPI virtual InterfaceControl& IsClippingEnabled(bool value);
                UIAPI virtual InterfaceControl& IsEnabled(bool value);

                UIAPI virtual InterfaceControl& Style(const ControlStyle& value);



                /** DESTRUCTOR **/
                virtual ~InterfaceControl() { }



                /** UTILITIES **/



                /** RENDERING UTILITIES **/
                UIAPI virtual void Fill()     const override;
                UIAPI virtual void Stroke()   const override;
                UIAPI virtual void Update()   const override;

            protected:

                /** PROPERTY DATA**/
                ControlStyle        _style;


                /** PROPERTIES **/
                virtual Path2D& Shape() = 0;



                /** CONSTRUCTOR **/
                UIAPI InterfaceControl();


                /** UTILITIES**/
                UIAPI virtual void UpdateStyle();

            private:
                
                /** PROPERTY DATA**/
                bool                _isClippingEnabled;
                bool                _isEnabled;
                InterfaceControl*   _parent;


        };

    }
}
