/* CHANGELOG 
 * Written by Josh Grooms on 20161025
 */

#pragma once
//#include "GraphicsSettings.h"
#include "UIAPI.h"
#include "Interfaces/IInterfaceControl.h"
#include "Interfaces/IRenderable.h"



namespace Cyclone
{
    namespace { using namespace OpenGL; }

    namespace UI
    {
        class InterfaceLayer : public IRenderableScene
        {
            public:

                /** PROPERTIES **/
                UIAPI const List<IRenderStage*>& Stages()       const override;


                        
                /** CONSTRUCTOR **/
                UIAPI InterfaceLayer();



                /** UTILITIES **/
                UIAPI void Add(const IInterfaceControl& control);
                UIAPI void Update() override;






            private:

                //GraphicsSettings _settings;



        };
    }
}
