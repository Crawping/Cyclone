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
        class QuadTree
        {
            public:


                
                bool Intersects(const Vector2& point) const
                {

                }
                

                void Insert(const Vector2& point, T value)
                {
                    if (!_bounds.Contains(point))
                        return;


                }



            private:
                template<typename T> struct Node;

                Area _bounds;


                Node<T>* Origin;



                template<typename T>
                struct Node
                {
                    private:
                        Node<T>*    NE;
                        Node<T>*    NW;
                        Node<T>*    SE;
                        Node<T>*    SW;

                        Area        Bounds;
                        T           Value;

                            void Subdivide()
                            {
                                if (NE) { return; }

                                Vector2 center = Bounds.Center();
                                Vector2 size = Bounds.Scale() / 2.0f;

                                NE = new Node<T>( Area(Bounds.Position() + center, size) );
                                NW = new Node<T>( Area(Bounds.Position() + Vector2(0.0f, center.Y), size) );
                                SE = new Node<T>( Area(Bounds.Position(), size) );
                                SW = new Node<T>( Area(Bounds.Position() + Vector2(center.X, 0.0f), size) );
                            }


                    public:
                        Node(const Area& bounds) :
                            Bounds(bounds)
                            NE(nullptr), NW(nullptr),
                            SW(nullptr), SW(nullptr)
                        {

                        }
                        ~Node()
                        {
                            if (NE) { delete NE; }
                            if (NW) { delete NW; }
                            if (SE) { delete SE; }
                            if (SW) { delete SW; }
                        }


                        bool Insert(const Vector2& point, T value)
                        {
                            if (!Bounds.Contains(point))
                                return false;

                            if (!Value)
                            {
                                Value = value;
                                return true;
                            }

                            Subdivide();
                            Vector2 center = Bounds.Center();

                            if (NE->Insert(point, value)) { return true; }
                            if (NW->Insert(point, value)) { return true; }
                            if (SE->Insert(point, value)) { return true; }
                            if (SW->Insert(point, value)) { return true; }
                        
                            return false;                            
                        }

                };
        };












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
