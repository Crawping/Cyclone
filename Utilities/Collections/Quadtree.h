/* CHANGELOG
 * Written by Josh Grooms on 20161018
 */

#pragma once
#include "Utilities.h"
#include "Collections/List.h"
#include "Collections/Vector.h"
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
                    
                    Area rootBounds(bounds);
                    rootBounds.Union(Bounds());
                    float size = nextpow2((uint)Math::Max(rootBounds.Width, rootBounds.Height, 1.0f));
                    rootBounds.Scale(size);

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

                        Area                _bounds;

                        Vector<Node<T>*, 4> Subtrees;
                        List<KVP<T>>        Values;



                        void Subdivide()
                        {
                            if (Subtrees(0)) { return; }
                                                        
                            Vector2 center = Bounds().Center();
                            Vector2 size = Bounds().Scale() / 2.0f;

                            Subtrees(0) = new Node<T>(Area(Bounds().Position() + center, size));
                            Subtrees(1) = new Node<T>(Area(Bounds().Position() + Vector2(0.0f, center.Y), size));
                            Subtrees(2) = new Node<T>(Area(Bounds().Position(), size));
                            Subtrees(3) = new Node<T>(Area(Bounds().Position() + Vector2(center.X, 0.0f), size));

                            List<uint> idsToRemove;
                            
                            if (Values.IsEmpty()) { return; }
                            for (uint a = Values.Count() - 1; a >= 0; a--)
                                if (Insert(Values(a).Bounds, Values(a).Value))
                                    Values.Remove(a);
                        }
                        List<KVP<T>> SubtreeIndex(const Area& bounds) const
                        {
                            if (!Subtrees(0)) { return List<KVP<T>>(); }

                            for (uint a = 0; a < Subtrees.Count(); a++)
                                if (Subtrees(a)->Bounds() == bounds)
                                    return Subtrees(a)->Contents();

                            return List<KVP<T>>();
                        }
                        bool SubtreeInsert(Node<T>* node)
                        {
                            if (!Subtrees(0)) { return false; }

                            for (uint a = 0; a < Subtrees.Count(); a++)
                                if (Subtrees(a)->Insert(node))
                                    return true;

                            return false;
                        }
                        bool SubtreeInsert(const Area& bounds, T value)
                        {
                            if (!Subtrees(0)) { return false; }

                            for (uint a = 0; a < Subtrees.Count(); a++)
                                if (Subtrees(a)->Insert(bounds, value))
                                    return true;

                            return false;
                        }
                        bool SubtreeRemove(const Area& bounds)
                        {
                            if (!Subtrees(0)) { return false; }

                            for (uint a = 0; a < Subtrees.Count(); a++)
                                if (Subtrees(a)->remove(bounds))
                                    return true;

                            return false;
                        }

                    public:

                        const Area& Bounds()        const { return _bounds; }
                        List<KVP<T>> Contents()     const
                        {
                            if (!Subtrees(0)) { return Values; }

                            List<KVP<T>> contents = Values;
                            for (uint a = 0; a < Subtrees.Count(); a++)
                                contents.Append(Subtrees(a)->Contents());

                            return contents;
                        }



                        Node(const Area& bounds) :
                            _bounds(bounds),
                            Subtrees({ nullptr, nullptr, nullptr, nullptr })
                        {

                        }
                        ~Node()
                        {
                            for (uint a = 0; a < Subtrees.Count(); a++)
                                if (Subtrees(a))
                                    delete Subtrees(a);
                        }




                        bool Contains(const Area& bounds) const { return Bounds().Contains(bounds); }

                        List<KVP<T>> Index(const Area& bounds) const
                        {
                            if (!Contains(bounds)) { return List<KVP<T>>(); }
                            if (Bounds() == bounds) { return Contents(); }

                            List<KVP<T>> intersections;
                            for (uint a = 0; a < Values.Count(); a++)
                                if (bounds.Contains(Values(a).Bounds))
                                    intersections.Append(Values(a));

                            intersections.Append(SubtreeIndex(bounds));
                            return intersections;
                        }
                        bool Insert(Node<T>* node)
                        {
                            if (!node)                              { return true; }
                            if (!Bounds().Contains(node->Bounds())) { return false; }
                            if (SubtreeInsert(node))                { return true; }

                            if (Subtrees(0)) { return false; }
                            Subdivide();

                            Node<T>** toReplace = nullptr;

                            for (uint a = 0; a < Subtrees.Count(); a++)
                                if (Subtrees(a)->Contains(node->Bounds()))
                                {
                                    toReplace = &Subtrees(a);
                                    break;
                                }

                            if (toReplace)
                            {
                                delete *toReplace;
                                *toReplace = node;
                            }
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

                            if (Subtrees(0)) { return false; }

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
