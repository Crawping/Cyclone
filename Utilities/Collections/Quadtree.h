/* CHANGELOG
 * Written by Josh Grooms on 20161018
 */

#pragma once
#include "Collections/List.h"
#include "Spatial/Area.h"



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

                        template<typename T> struct KVP
                        {
                            Area    Bounds;
                            T       Value;
                        };


                        Node<T>*        NE;
                        Node<T>*        NW;
                        Node<T>*        SE;
                        Node<T>*        SW;

                        Area            Bounds;
                        List<KVP<T>>    Values;

                        void SubtreeInsert(const Area& bounds, T value)
                        {
                            if (!NE) { return false; }

                            if (NE->Insert(point, value)) { return true; }
                            if (NW->Insert(point, value)) { return true; }
                            if (SE->Insert(point, value)) { return true; }
                            if (SW->Insert(point, value)) { return true; }

                            return false;
                        }
                        void SubtreeRemove(const Area& bounds)
                        {
                            if (!NE) { return false; }

                            if (NE->Remove(point)) { return true; }
                            if (NW->Remove(point)) { return true; }
                            if (SE->Remove(point)) { return true; }
                            if (SW->Remove(point)) { return true; }

                            return false;
                        }

                        void Subdivide()
                        {
                            if (NE) { return; }

                            Vector2 center = Bounds.Center();
                            Vector2 size = Bounds.Scale() / 2.0f;

                            NE = new Node<T>( Area(Bounds.Position() + center, size) );
                            NW = new Node<T>( Area(Bounds.Position() + Vector2(0.0f, center.Y), size) );
                            SE = new Node<T>( Area(Bounds.Position(), size) );
                            SW = new Node<T>( Area(Bounds.Position() + Vector2(center.X, 0.0f), size) );

                            List<uint> idsToRemove;
                            for (uint a = 0; a < Values.Count(); a++)
                                if (Insert(Values(a).Bounds, Values(a).Value))
                                    idsToRemove.Append(a);

                            for (uint a = Values.Count() - 1; a >= 0; a--)
                                Values.Remove(idsToRemove(a));                                    
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

                            Values.Clear();
                        }


                        bool Insert(const Area& bounds, T value)
                        {
                            if (!Bounds.Contains(bounds))
                                return false;

                            if (SubtreeInsert(bounds, value))
                                return true;

                            if (Values.Count() < 4)
                            {
                                Values.Append({ bounds, value });
                                return true;
                            }

                            if (NE) { return false; }

                            Subdivide();
                            return SubtreeInsert(bounds, value);       
                        }
                        bool Remove(const Area& bounds)
                        {
                            if (!Bounds.Contains(bounds))
                                return false;

                            if (SubtreeRemove(bounds))
                                return true;

                            for (uint a = 0; a < Values.Count(); a++)
                                if (Values(a).Bounds == bounds)
                                {
                                    Values.Remove(a);
                                    return true;
                                }

                            return false;
                        }

                };
        };


    }
}
