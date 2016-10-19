/* CHANGELOG
 * Written by Josh Grooms on 20161018
 */

#pragma once
#include "Utilities.h"
#include "Collections/List.h"
#include "Spatial/Area.h"



namespace Cyclone
{
    namespace Utilities
    {

        template<typename T>
        class Quadtree
        {
            public:
               

                /** PROPERTIES **/
                const Area& Bounds()    const 
                { 
                    if (Root)   { return Root->Bounds(); }
                    else        { return Area::Empty; }
                }
                const uint Count()      const { return _count; }
                bool IsEmpty()          const { return Bounds().IsEmpty(); }



                /** CONSTRUCTOR **/
                Quadtree() :
                    _count(0),
                    Root(nullptr)
                {

                }
                ~Quadtree()
                { 
                    if (Root) { delete Root; } 
                }


                /** UTILITIES **/
                List<T> Index(const Area& bounds) const
                {
                    List<T> contents;
                    List<KVP<T>> nodeContents = Root->Index(bounds);
                    
                    for (uint a = 0; a < nodeContents.Count(); a++)
                        contents.Append(nodeContents(a).Value);

                    return contents;
                }
                void Insert(const Area& bounds, T value)
                {
                    if (Root && Root->Insert(bounds, value)) { _count++; return; }

                    float size = nextpow2((uint)Math::Max(bounds.Width, bounds.Height, 1.0f));
                    Area rootBounds(bounds.Position(), Vector2(size));

                    Node<T>* newRoot = new Node<T>(rootBounds);

                    newRoot->Insert(Root);
                    if (newRoot->Insert(bounds, value))
                        _count++;

                    Root = newRoot;
                }



            private:
                template<typename T> struct Node;

                uint        _count;
                Node<T>*    Root;




                /** NESTED STRUCTURES **/
                template<typename T> struct KVP
                {
                    Area    Bounds;
                    T       Value;
                };

                template<typename T> struct Node
                {
                    private:

                        Area            _bounds;

                        Node<T>*        NE;
                        Node<T>*        NW;
                        Node<T>*        SE;
                        Node<T>*        SW;
                        List<KVP<T>>    Values;

                        void Subdivide()
                        {
                            if (NE) { return; }

                            Vector2 center = Bounds().Center();
                            Vector2 size = Bounds().Scale() / 2.0f;

                            NE = new Node<T>(Area(Bounds().Position() + center, size));
                            NW = new Node<T>(Area(Bounds().Position() + Vector2(0.0f, center.Y), size));
                            SE = new Node<T>(Area(Bounds().Position(), size));
                            SW = new Node<T>(Area(Bounds().Position() + Vector2(center.X, 0.0f), size));

                            List<uint> idsToRemove;
                            for (uint a = 0; a < Values.Count(); a++)
                                if (Insert(Values(a).Bounds, Values(a).Value))
                                    idsToRemove.Append(a);

                            for (uint a = Values.Count() - 1; a >= 0; a--)
                                Values.Remove(idsToRemove(a));
                        }
                        List<KVP<T>> SubtreeIndex(const Area& bounds) const
                        {
                            if (NE)
                            {
                                if (NE->Bounds() == bounds) { return NE->Contents(); }
                                if (NE->Bounds() == bounds) { return NE->Contents(); }
                                if (NE->Bounds() == bounds) { return NE->Contents(); }
                                if (NE->Bounds() == bounds) { return NE->Contents(); }
                            }

                            return List<KVP<T>>();
                        }
                        bool SubtreeInsert(Node<T>* node)
                        {
                            if (!NE) { return false; }

                            if (NE->Insert(node)) { return true; }
                            if (NW->Insert(node)) { return true; }
                            if (SE->Insert(node)) { return true; }
                            if (SW->Insert(node)) { return true; }

                            return false;
                        }
                        bool SubtreeInsert(const Area& bounds, T value)
                        {
                            if (!NE) { return false; }

                            if (NE->Insert(bounds, value)) { return true; }
                            if (NW->Insert(bounds, value)) { return true; }
                            if (SE->Insert(bounds, value)) { return true; }
                            if (SW->Insert(bounds, value)) { return true; }

                            return false;
                        }
                        bool SubtreeRemove(const Area& bounds)
                        {
                            if (!NE) { return false; }

                            if (NE->Remove(point)) { return true; }
                            if (NW->Remove(point)) { return true; }
                            if (SE->Remove(point)) { return true; }
                            if (SW->Remove(point)) { return true; }

                            return false;
                        }

                    public:

                        const Area& Bounds()        const { return _bounds; }
                        List<KVP<T>> Contents()     const
                        {
                            List<KVP<T>> contents = Values;
                            if (NE)
                            {
                                contents.Append(NE->Contents());
                                contents.Append(NW->Contents());
                                contents.Append(SE->Contents());
                                contents.Append(SW->Contents());
                            }

                            return contents;
                        }


                        Node(const Area& bounds) :
                            _bounds(bounds),
                            NE(nullptr), NW(nullptr),
                            SE(nullptr), SW(nullptr)
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




                        bool Contains(const Area& bounds) const { return Bounds().Contains(bounds); }

                        List<KVP<T>> Index(const Area& bounds) const
                        {
                            if (!Contains(bounds)) { return List<KVP<T>>(); }
                            if (Bounds() == bounds) { return Contents(); }

                            return SubtreeIndex(bounds);
                        }
                        bool Insert(Node<T>* node)
                        {
                            if (!node)                              { return true; }
                            if (!Bounds().Contains(node->Bounds())) { return false; }
                            if (SubtreeInsert(node))                { return true; }

                            if (NE) { return false; }
                            Subdivide();

                            Node<T>** toReplace = nullptr;
                            if      (NE->Bounds().Contains(node->Bounds())) { toReplace = &NE; }
                            else if (NW->Bounds().Contains(node->Bounds())) { toReplace = &NW; }
                            else if (SE->Bounds().Contains(node->Bounds())) { toReplace = &SE; }
                            else if (SW->Bounds().Contains(node->Bounds())) { toReplace = &SW; }
                            else    { return false; }
                                
                            delete *toReplace;
                            *toReplace = node;
                        }
                        bool Insert(const Area& bounds, T value)
                        {
                            if (!Bounds().Contains(bounds))     { return false; }
                            if (SubtreeInsert(bounds, value))   { return true; }

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
                            if (!Bounds().Contains(bounds)) { return false; }
                            if (SubtreeRemove(bounds))      { return true; }

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
