/* CHANGELOG
 * Written by Josh Grooms on 20151215
 */

#pragma once
#include "Math/Vector2.h"
#include "Spatial/Area.h"
#include "Spatial/Transform.h"



namespace Cyclone
{
    namespace { using namespace Utilities; }

    namespace SVG
    {        

        class Entity2D
        {
            public:
        
                /** PROPERTIES **/
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
        


                virtual bool IsVisible()                    const { return _isVisible; }
        
        
                /** DESTRUCTOR **/
                virtual ~Entity2D() { }
               
            protected:
        
                Area        _displayArea;
                bool        _isVisible;
                Transform   _modelTransform;
                Transform   _worldTransform;
        
        
        
                /** CONSTRUCTOR **/
                Entity2D();
        
        
        
        
        
        };
    }
}