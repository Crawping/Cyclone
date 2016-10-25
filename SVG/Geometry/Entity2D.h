/* CHANGELOG
 * Written by Josh Grooms on 20151215
 */

#pragma once
#include "Math/Vector2.h"
#include "Spatial/Area.h"



namespace Cyclone
{
    namespace
    {
        using namespace Utilities;
    }
    namespace SVG
    {        

        class Entity2D
        {
            public:
        
                /** PROPERTIES **/
                virtual const Area& DisplayArea()           const { return _displayArea; }
                virtual bool IsVisible()                    const { return _isVisible; }
                                                    
                virtual float X()                           const { return _displayArea.X; }
                virtual float Y()                           const { return _displayArea.Y; }
                                                    
                virtual void X(float x)                           { _displayArea.X = x; }
                virtual void Y(float y)                           { _displayArea.Y = y; }
                                                    
                virtual float Height()                      const { return _displayArea.Height; }
                virtual float Width()                       const { return _displayArea.Width; }
                                                    
                virtual void Height(float h)                      { _displayArea.Height = h; }
                virtual void Width(float w)                       { _displayArea.Width = w; }
                                            
                                            
                virtual Vector2 Position()                      const { return _displayArea.Position(); }
                virtual Entity2D& Position(const Vector2& p)          { _displayArea.Position(p); return *this; }
                virtual Entity2D& Position(float x, float y)          { _displayArea.Position(x, y); return *this; }
                                            
                virtual Vector2 Scale()                         const { return _displayArea.Scale(); }
                virtual Entity2D& Scale(const Vector2& s)             { _displayArea.Scale(s); return *this; }
                virtual Entity2D& Scale(float w, float h)             { _displayArea.Scale(w, h); return *this; }
        
        
        
                /** DESTRUCTOR **/
                virtual ~Entity2D() { }
               
            protected:
        
                Area _displayArea;
                bool _isVisible;
        
        
        
                /** CONSTRUCTOR **/
                Entity2D();
        
        
        
        
        
        };
    }
}