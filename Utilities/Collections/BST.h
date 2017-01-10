/* CHANGELOG
 * Written by Josh Grooms on 20161126
 */

#pragma once
//#include "Interfaces/ICollection.h"
#include "Collections/List.h"



namespace Cyclone
{
    namespace Utilities
    {
        /// <summary> A class that represents a self-balancing binary search tree (BST) of keys and their corresponding values. </summary>
        /// <typeparam name="T"> The type name of the keys used to index values within the tree. </typeparam>
        /// <typeparam name="U"> The type name of the data element values stored within the tree. </typeparam>
        template<typename T, typename U>
        class BST : public ICollection<U>
        {
            public:
                struct Iterator;
                template<typename T, typename U> struct Node;

                /** PROPERTIES **/
                /// <summary> Gets the total number of nodes found in this tree. </summary>
                virtual uint Count()        const override { return Root ? Root->Count : 0; }
                /// <summary> Gets the height of this tree. </summary>
                /// <remarks>
                ///     The height of the tree is defined here as the distance (i.e. number of nodes) between the root and the most 
                ///     distal leaf node in its subtrees.
                /// </remarks>
                virtual uint Height()       const { return Root ? Root->Height : 0; }
                /// <summary> Gets a list of all of the keys that index values within the tree. </summary>
                virtual List<T> Keys()      const { return Root ? Root->Keys() : List<T>(); }
                /// <summary> Gets a list of all data element values contained in the tree. </summary>
                virtual List<U> Values()    const { return Root ? Root->Values() : List<U>(); }
                


                /** CONSTRUCTOR & DESTRUCTOR **/
                /// <summary> Constructs a new self-balancing binary search tree (BST) that is initially empty. </summary>
                BST() :
                    Root(nullptr)
                {

                }
                /// <summary> Destroys all of the data nodes held by the tree. </summary>
                ~BST()
                {
                    if (Root) { delete Root; }
                }



                /** UTILITIES **/
                /// <summary> Removes all data elements stored within the tree. </summary>
                virtual void Clear()
                {
                    if (Root) { delete Root; }
                    Root = nullptr;
                }
                /// <summary> Determines whether the tree contains a node that corresponds with a specific key. </summary>
                /// <param name="key"> A key value to be tested. </param>
                /// <returns> A Boolean <c>true</c> if the key exists within the tree, or <c>false</c> otherwise. </returns>
                virtual bool Contains(const T& key)         const { return Root ? (Root->Find(key) != nullptr) : false; }
                /// <summary> Finds the numeric index into the tree that corresponds with a specific key value, if it exists. </summary>
                /// <param name="key"> The key for which a corresponding linear index is to be found. </param>
                /// <returns> A linear index that corresponds with <paramref name="key"/>, or the <see cref="Count"/> if no such index exists. </returns>
                virtual uint IndexOf(const T& key)          const { return Root ? Root->IndexOf(key) : 0; }
                /// <summary> Inserts a new node into the BST and automatically rebalances the tree, if necessary. </summary>
                /// <param name="key"> The key for the new node being inserted. </param>
                /// <param name="value"> The value for the new node being inserted. </param>
                /// <remarks>
                ///     This method will either create a new node with the inputted key-value pair (if one does not exist within the 
                ///     BST) or overwrite the value of any node whose key matches the 'key' input argument.
                /// </remarks>
                virtual void Insert(const T& key, const U& value) 
                { 
                    Root = Root ? Root->Insert(key, value) : new Node<T, U>(key, value);
                }
                /// <summary> Removes the specified node from the binary search tree. </summary>
                /// <param name="key"> The key of the node to be removed. </param>
                virtual void Remove(const T& key)
                {
                    Root = Root ? Root->Remove(key) : nullptr;
                }        



                /** OPERATORS **/
                Iterator begin() const
                {
                    return Iterator(0, Root);
                }
                Iterator end() const
                {
                    return Iterator(Count(), nullptr);
                }
                /// <summary> Gets the value corresponding with an inputted key from the tree. </summary>
                /// <param name="key"> The key that corresponds with a desired value in the tree. </param>
                /// <returns> A reference to the value that corresponds with the inputted key. </returns>
                /// <remarks> Attempting to use a key that is not present in the tree will result in exceptions being thrown. </remarks>
                virtual U& operator [](const T& key)        { return Root->Find(key)->Value; }
                /// <summary> Gets the value corresponding with an inputted key from the tree. </summary>
                /// <param name="key"> The key that corresponds with a desired value in the tree. </param>
                /// <returns> A constant reference to the value that corresponds with the inputted key. </returns>
                /// <remarks> Attempting to use a key that is not present in the tree will result in exceptions being thrown. </remarks>
                virtual const U& operator [](const T& key)  const { return Root->Find(key)->Value; }
                /// <summary> Gets the value corresponding with a numeric index into the list of values stored within the tree. </summary>
                /// <param name="index"> A linear index into the tree, as if it were a flattened list of values sorted by its keys. </param>
                /// <returns> A constant reference to the value that corresponds with the inputted index. </returns>
                /// <remarks> Attempting to use an index that is not present in the tree will result in exceptions being thrown. </remarks>
                virtual const U& operator ()(uint index)    const { return Root->Index(index)->Value; }

            private:

                /** DATA **/
                /// <summary> The root node of the tree. </summary>
                Node<T, U>* Root;



                /** NESTED TYPES **/
                template<typename T, typename U>
                struct Node
                {
                    public:
                        /** DATA **/
                        /// <summary> A pointer to the left child node and subtree of this node. This value can be null. </summary>
                        Node<T, U>* Left;
                        /// <summary> A pointer to the right child node and subtree of this node. This value can be null. </summary>
                        Node<T, U>* Right;

                        /// <summary> Gets the balance of the subtree for which this node is the root. </summary>
                        /// <remarks>
                        ///     The balance of any node is defined here as the difference between the heights of the right and the left 
                        ///     subtrees (i.e. B = LH - RH).
                        /// </remarks>
                        int Balance;
                        /// <summary> Gets the number of nodes in the subtree for which this node is the root. </summary>
                        int Count;
                        /// <summary> Gets the height of this node. </summary>
                        /// <remarks>
                        ///     The height of any node is defined here as the distance (i.e. number of nodes) between it and the most 
                        ///     distal leaf node in its subtree.
                        /// </remarks>
                        int Height;
                        /// <summary> Gets the key used to index this node within the search tree. </summary>
                        T Key;
                        /// <summary> Gets the value held by this node. </summary>
                        U Value;

                        /// <summary> Gets a list containing all of the keys that index this tree. </summary>
                        List<T> Keys() const
                        {
                            List<T> keys;
                            if (Left) { keys.Append(Left->Keys()); }
                            keys.Append(Key);
                            if (Right) { keys.Append(Right->Keys()); }
                            return keys;
                        }
                        /// <summary> Gets the node possessing the maximum key from the subtree rooted in this node. </summary>
                        Node<T, U>* Max()
                        {
                            return Right ? Right->Max() : this;
                        }
                        /// <summary> Gets the node possessing the minimum key from the subtree rooted in this node. </summary>
                        Node<T, U>* Min()
                        { 
                            return Left ? Left->Min() : this;
                        }
                        /// <summary> Gets a list containing all of the values held by the search tree. </summary>
                        List<U> Values() const
                        {
                            List<U> values;
                            if (Left) { values.Append(Left->Values()); }
                            values.Append(Value);
                            if (Right) { values.Append(Right->Values()); }
                            return values;
                        }



                        /** CONSTRUCTOR **/
                        /// <summary> Constructs a new node with a specific key-value pair. </summary>
                        /// <param name="key"> The key that will be used to index the new node within a tree. </param>
                        /// <param name="value"> The value held by the node that is associated with its key. </param>
                        Node(const T& key, const U& value) : 
                            Left(nullptr),
                            Right(nullptr),
                            Balance(0),
                            Count(1),
                            Height(0),
                            Key(key),
                            Value(value)
                        {

                        }
                        /// <summary> Destroys this node and all other nodes within the subtree rooted by it. </summary>
                        ~Node()
                        {
                            if (Left)   { delete Left; }
                            if (Right)  { delete Right; }
                        }



                        /** UTILITIES **/
                        /// <summary> Retrieves the node stored at a numeric index into the sorted list of nodes, if it exists. </summary>
                        /// <param name="index"> A linear index into node tree, as if it were a flattened list of sorted values. </param>
                        /// <returns> A pointer to the node referenced by <paramref name="index"/>, or a <c>nullptr</c> if no such node exists. </returns>
                        Node<T, U>* Index(uint index)
                        {
                            if (Left)
                                if (index < Left->Count)
                                    return Left->Index(index);
                                else
                                    index -= Left->Count;
                            
                            if (index == 0)
                                return this;
                            else
                                index--;
                            
                            if (Right && index < Right->Count)
                                return Right->Index(index);
                            
                            return nullptr;
                        }
                        const Node<T, U>* Index(uint index)     const { return Index(index); }
                        /// <summary> Finds the numeric index into the tree that corresponds with a key value, if it exists.  </summary>
                        /// <param name="key"> The key for which a corresponding linear index is to be found. </param>
                        /// <returns> A linear index that corresponds with <paramref name="key"/>, or the <see cref="Count"/> if no such index exists. </returns>
                        uint IndexOf(const T& key)              const
                        {
                            uint index = Count;
                            uint lc = Left ? Left->Count : 0;

                            if (key < Key)
                                return Left ? Left->IndexOf(key) : index;
                            else if (key > Key)
                                return Right ? (Right->IndexOf(key) + lc + 1) : index;
                            else
                                return lc;
                        }
                        /// <summary> Inserts a new node into the subtree rooted by this node. </summary>
                        /// <param name="key"> The key for the new node being inserted. </param>
                        /// <param name="value"> The value for the new node being inserted. </param>
                        /// <returns> The new root node of this subtree. </returns>
                        /// <remarks>
                        ///     If automatic tree rebalancing is applied during an insert operation, then the root node of this subtree is 
                        ///     liable to change. Thus, the node returned by this method is useful for tracking overall tree organization 
                        ///     at levels higher than the node on which this method gets invoked.
                        /// </remarks>
                        Node<T, U>* Insert(const T& key, const U& value)
                        {
                            if (key < Key)
                                Left = Left ? Left->Insert(key, value) : new Node<T, U>(key, value);
                            else if (key > Key)
                                Right = Right ? Right->Insert(key, value) : new Node<T, U>(key, value);
                            else
                            {
                                Value = value;
                                return this;
                            }

                            return Rebalance();
                        }                
                        /// <summary> Finds a node within the subtree whose key is greater than or equal to the inputted key. </summary>
                        /// <param name="key"> The key for which a greater-keyed node is to be found. </param>
                        /// <returns> A node whose key is greater than or equal to the input, or 'null' if one cannot be found. </returns>
                        /// <remarks>
                        ///     This method searches a subtree for the 'next higher' node, which is defined here as the node whose key is 
                        ///     the minimum of all keys that are greater than or equal to the 'key' input argument. If such a node cannot 
                        ///     be found, then this method returns 'null'.
                        /// </remarks>
                        Node<T, U>* Ceiling(const T& key)
                        {
                            if (key < Key)
                                return Left ? (Left->Ceiling(key) ? Left->Ceiling(key) : this) : this;
                            else if (key > Key)
                                return Right ? Right->Ceiling(key) : nullptr;
                            else
                                return this;
                        }
                        const Node<T, U>* Ceiling(const T& key) const { return Ceiling(key); }
                        /// <summary> Finds a node within the subtree whose key is either less than or equal to the inputted key. </summary>
                        /// <param name="key"> The key for which a lesser-keyed node is to be found. </param>
                        /// <returns> A node whose key is less than or equal to the input, or <c>nullptr</c> if no such node exists. </returns>
                        /// <remarks>
                        ///     This method searches a subtree for the 'next lower' node, which is defined here as the node whose key is 
                        ///     the maximum of all keys that are less than or equal to the 'key' input argument. If such a node cannot be 
                        ///     found, then this method returns 'null'.
                        /// </remarks>
                        Node<T, U>* Floor(const T& key)
                        {
                            if (key < Key)
                                return Left ? Left->Floor(key) : nullptr;
                            else if (key > Key)
                                return Right ? (Right->Floor(key) ? Right->Floor(key) : this) : this;
                            else
                                return this;
                        }
                        const Node<T, U>* Floor(const T& key)   const { return Floor(key); }
                        /// <summary> Finds the node within the subtree that corresponds with a specific key, if it exists. </summary>
                        /// <param name="key"> A key for which the corresponding node is to be found. </param>
                        /// <returns> A node whose key matches the input, or <c>nullptr</c> if no such node exists. </returns>
                        Node<T, U>* Find(const T& key)
                        {
                            if (key < Key)
                                return Left ? Left->Find(key) : nullptr;
                            else if (key > Key)
                                return Right ? Right->Find(key) : nullptr;
                            else
                                return this;
                        }
                        const Node<T, U>* Find(const T& key)    const { return Find(key); }
                        /// <summary> Removes the node within the subtree that corresponds with a specific key, if it exists. </summary>
                        /// <param name="key"> A key for which the corresponding node is to be removed. </param>
                        /// <returns> The new root node of the subtree. </returns>
                        Node<T, U>* Remove(const T& key)
                        {
                            if (key < Key)
                                Left = Left ? Left->Remove(key) : Left;
                            else if (key > Key)
                                Right = Right ? Right->Remove(key) : Right;
                            else
                            {
                                Node<T, U>* newRoot;
                                if (!Right)         { newRoot = Left; }
                                else if (!Left)     { newRoot = Right; }
                                else
                                {
                                    newRoot = Right->Min();
                                    newRoot->Right = Right->SeverMin();
                                    newRoot->Left = Left;

                                    Left = nullptr;
                                    Right = nullptr;

                                    delete this;
                                    newRoot = newRoot->Rebalance();
                                }

                                return newRoot;
                            }
    
                            return Rebalance();
                        }
               
                    private:

                        /** UTILITIES **/
                        /// <summary> Severs the node whose key is the minimum of all keys in this subtree. </summary>
                        /// <returns> The new root of this subtree, rebalanced after severing the node. </returns>
                        /// <remarks> Note that any node severed via this method is not deleted here. </remarks>
                        Node<T, U>* SeverMin()
                        {
                            if (!Left) { return Right; }
                            Left = Left->SeverMin();
                            return Rebalance();
                        }
                        /// <summary> Rotates the subtree about this particular node.  </summary>
                        /// <param name="clockwise"> If true, then the rotation will occur in a clockwise fashion. </param>
                        Node<T, U>* Rotate(bool isClockwise)
                        {
                            Node<T, U>* newRoot;
                            if (isClockwise)
                            {
                                if (!Left) { return this; }
                                newRoot = Left;
                                Left = newRoot->Right;
                                newRoot->Right = this;
                            }
                            else
                            {
                                if (!Right) { return this; }
                                newRoot = Right;
                                Right = newRoot->Left;
                                newRoot->Left = this;
                            }

                            if (newRoot != this) { Update(); } 
                            newRoot->Update();
                            return newRoot;
                        }
                        /// <summary> Balances the tree for which this node is the root. </summary>
                        Node<T, U>* Rebalance()
                        {
                            Update();
                            if (Balance >= -1 && Balance <= 1) { return this; }

                            bool cwFlag = (Balance > 1);
                            if (cwFlag && Left && Left->Balance < 0)
                                Left = Left->Rotate(false);
                            else if (!cwFlag && Right && Right->Balance > 0)
                                Right = Right->Rotate(true);
                    
                            return Rotate(cwFlag);
                        }
                        /// <summary> Updates all child-dependent data for this node (i.e. balance, height, and count). </summary>
                        void Update()
                        {
                            int lh = 0, lc = 0;
                            int rh = 0, rc = 0;
                            if (Left)
                            {
                                lh = Left->Height + 1;
                                lc = Left->Count;
                            }

                            if (Right)
                            {
                                rh = Right->Height + 1;
                                rc = Right->Count;
                            }

                            Balance = lh - rh;
                            Height = (lh >= rh) ? lh : rh;
                            Count = lc + rc + 1;
                        }

                };



                struct Iterator // : public ICollectionIterator<U>
                {
                    public:


                        Iterator(uint idx, Node<T, U>* root) : 
                            Index(idx),
                            Root(root)
                        {

                        }



                        /** OPERATORS **/
                        bool operator ==(const Iterator& other) const
                        {
                            return Index == other.Index;
                        }
                        bool operator !=(const Iterator& other) const { return !(operator ==(other)); }

                        Node<T, U>& operator *()                const { return *(Root->Index(Index)); }
                        Iterator& operator ++()                 { Index++; return *this; }
                        Iterator& operator ++(int)              { Index++; return *this; }
                        
                    private:

                        uint        Index;
                        Node<T, U>* Root;
                };
        };
    }
}
