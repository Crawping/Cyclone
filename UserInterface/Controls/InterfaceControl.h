/* CHANGELOG
 * Written by Josh Grooms on 20161023
 */

#pragma once
#include "UIAPI.h"
#include "Collections/List.h"
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
            public virtual IInterfaceControl
        {
            public:
                
                /** PROPERTIES **/
                virtual List<IRenderable&> Components()             = 0;

                virtual bool IsEnabled()                            const override { return _isEnabled; }
                virtual bool IsHighlighted()                        const override { return _isHighlighted; }
                virtual bool IsSelected()                           const override { return _isSelected; }

                virtual IInterfaceControl* Parent()                 const override { return _parent; }
                virtual const ControlStyle& Style()                 const override { return _style; }
                virtual const Path2D& Shape()                       const override = 0;



                /** STYLE PROPERTIES **/
                /// <summary> Gets the color of the control's background area. </summary>
                virtual const Color4& BackgroundColor()             const { return _style.BackgroundColor; }
                /// <summary> Gets the color of the control's outer border. </summary>
                virtual const Color4& BorderColor()                 const { return _style.BorderColor; }
                /// <summary> Gets the radius of any joints in the control's outer border in pixels. </summary>
                virtual const Border& BorderRadius()                const { return _style.BorderRadius; }
                /// <summary> Gets the width of the control's outer border stroke in pixels. </summary>
                virtual const Border& BorderWidth()                 const { return _style.BorderWidth; }

                /// <summary> Sets the color of the control's background area. </summary>
                UIAPI virtual InterfaceControl& BackgroundColor(const Color4& value);
                /// <summary> Sets the color of the control's outer border. </summary>
                UIAPI virtual InterfaceControl& BorderColor(const Color4& value);
                /// <summary> Sets the radius of any joints in the control's outer border in pixels. </summary>
                UIAPI virtual InterfaceControl& BorderRadius(const Border& value);
                /// <summary> Sets the width of the control's outer border stroke in pixels. </summary>
                UIAPI virtual InterfaceControl& BorderWidth(const Border& value);

                UIAPI virtual InterfaceControl& IsClippingEnabled(bool value);
                /// <summary> Sets whether the control is enabled for use. </summary>
                UIAPI virtual InterfaceControl& IsEnabled(bool value);
                /// <summary> Sets the (x, y) pixel position of the control in 2D window space. </summary>
                /// <remarks> The z-coordinate is of any input is currently ignored. </remarks>
                UIAPI virtual InterfaceControl& Offset(const Vector3& value);
                /// <summary> Sets the (pitch, yaw, roll) orientation of the control in 3D world space. </summary>
                UIAPI virtual InterfaceControl& Orientation(const Vector3& value);
                /// <summary> Sets the (x, y, z) position of the control in 3D world space. </summary>
                UIAPI virtual InterfaceControl& Position(const Vector3& value);
                /// <summary> Sets the (x, y, z) size of the control in pixels. </summary>
                UIAPI virtual InterfaceControl& Size(const Vector3& value);

                UIAPI virtual InterfaceControl& Style(const ControlStyle& value);



                /** DESTRUCTOR **/
                virtual ~InterfaceControl() { }



                /** UTILITIES **/
                UIAPI virtual void Update()   const;// override;

            protected:

                /** PROPERTY DATA**/
                //List<IRenderable&> _components;



                /** PROPERTIES **/
                virtual Path2D& Shape() = 0;



                /** CONSTRUCTOR **/
                UIAPI InterfaceControl();

            private:
                
                /** PROPERTY DATA**/
                bool                _isClippingEnabled;
                bool                _isEnabled;
                bool                _isHighlighted;
                bool                _isSelected;
                InterfaceControl*   _parent;
                ControlStyle        _style;


        };

    }
}
