/* CHANGELOG
 * Written by Josh Grooms on 20161219
 */

#pragma once
#include "Interfaces/IScene.h"



namespace Cyclone
{
    namespace OpenGL
    {
        class SceneComponent3D : public virtual ISceneComponent
        {
            public:
                
                const string& Name() const override { return _name; }





            private:

                string _name;


        };
    }
}
