/* CHANGELOG 
 * Written by Josh Grooms on 20161007
 */

#pragma once
#include "Collections/List.h"
#include "Geometry/Vertex.h"
#include "Interfaces/IRenderable.h"
#include "Spatial/Volume.h"



namespace Cyclone
{
    namespace OpenGL
    {

        class Space3D
        {
            public:
                virtual const Vector3& Position()   const { return Voxel->Position(); }
                virtual const Vector3& Size()       const { return Voxel->Size(); }


                Space3D() :
                    Root(nullptr),
                    Voxel(nullptr)
                {
                    Root = new SpatialNode();
                    Voxel = Root;
                }

                ~Space3D()
                {
                    if (Root) { delete Root; }
                }



                virtual Space3D& Insert(const IRenderable3D<Vertex::Standard>& entity)
                {

                }



            private:
                struct SpatialNode;

                SpatialNode*    Root;
                SpatialNode*    Voxel;

                

                struct SpatialNode
                {
                    public:
                        using IRenderable = const IRenderable3D<Vertex::Standard>*;    


                        const Vector3& Position()   const { return _bounds.Position(); }
                        const Vector3& Size()       const { return _bounds.Size(); }


                        SpatialNode() : 
                            _parent(nullptr),
                            Nodes(nullptr) 
                        {

                        }
                        ~SpatialNode()
                        {
                            for (uint a = 0; a < Nodes.Count(); a++)
                                if (Nodes(a)) { delete Nodes(a); }                                    
                        }



                        SpatialNode*& Node(uint idx) { return Nodes(idx); }
                        

                        bool Contains(const Vector3& point) const { return _bounds.Contains(point); }
                        bool Contains(const Volume& volume) const { return _bounds.Contains(volume); }

                        SpatialNode* Insert(IRenderable entity)
                        {
                            //if (!Contains(entity->)
                        }


                    private:
                        
                        Volume                      _bounds;
                        SpatialNode*                _parent;

                        List<IRenderable>          Entities;
                        Vector<SpatialNode*, 8>     Nodes;

                };


        };
    }
}
