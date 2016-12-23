/* CHANGELOG
 * Written by Josh Grooms on 20161223
 */

#pragma once
#include "Interfaces/IRenderStage.h"



namespace Cyclone
{
    namespace OpenGL
    {
        struct GraphicsSettings;
        struct ResourceMapping;

        class IRenderLayer
        {
            public:

                /** PROPERTIES **/
                virtual List<IRenderStage*> Stages()        const = 0;

                /** DESTRUCTOR **/
                virtual ~IRenderLayer() { }

                /** UTILITIES **/
                virtual void Add(const string& name, const GraphicsSettings& stage)             = 0;
                virtual void Associate(const string& stage, const ResourceMapping& indices)     = 0;
                virtual void Dissociate(const string& stage, const ResourceMapping& indices)    = 0;
                virtual void Remove(const string& stage)                                        = 0;
                virtual void Update()                                                           = 0;
        };
    }
}
