/* CHANGELOG
 * Written by Josh Grooms on 20161017
 */

#pragma once
#include "Collections/List.h"
#include "Collections/Vector.h"
#include "Math/Vector3.h"
#include "Spatial/Volume.h"



namespace Cyclone
{
    namespace Utilities
    {
        
        template<typename T>
        class VolumeHierarchy
        {
            public:

                bool Contains(const Vector3& point) const { return _bounds.Contains(point); }
                bool Contains(const Volume& volume) const { return _bounds.Contains(volume); }


            private:

                Volume _bounds;


        };
        



        template<typename T>
        struct Voxel
        {
            public:

                const Voxel<T>* Parent()    const { return _parent; }
                const Vector3& Position()   const { return _bounds.Position(); }
                const Vector3& Size()       const { return _bounds.Size(); }
                
                

                bool Contains(const Vector3& point) const { return _bounds.Contains(point); }
                bool Contains(const Volume& volume) const { return _bounds.Contains(volume); }

                //bool Intersects(const Vector3& point) const
                //{
                //    



                //    for (uint a = 0; a < Nodes.Count(); a++)
                //        if (Nodes(a) && Nodes(a)->Intersects(point))
                //            return true;

                //    return false;
                //}


                bool Insert(const Volume& bounds, T value)
                {
                    if (!Contains(bounds)) { return false; }

                    if (bounds.Width > hWidth || bounds.Height > hHeight || bounds.Depth > hDepth)
                        Nodes.Append()

                    if (Nodes.Count() == 8)
                        return false;

                    float hWidth = Size().X / 2.0f;
                    float hHeight = Size().Y / 2.0f;
                    float hDepth = Size().Z / 2.0f;
                }

            private:
                Volume          _bounds;
                Voxel<T>*       _parent;



                //Vector<Voxel<T>*, 8> Nodes;
                List<Voxel<T>*> Nodes;
                T               Value;
        };




        template<typename T>
        class Octree
        {
            public:

                




            private:

                Voxel* Current;
                Voxel* Root;

        };
    }
}
