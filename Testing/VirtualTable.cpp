/* CHANGELOG
 * Written by Josh Grooms on 20170122
 */

#include "TypeDefinitions.h"
#include "Storage/VirtualTable.h"
#include <gtest/gtest.h>

using namespace Cyclone::VM;
using namespace Cyclone::Utilities;



class _virtualTable : public testing::Test
{
    protected:

        VirtualTable VT;

        _virtualTable() { }
        ~_virtualTable()
        {
            VT.Delete(0);
        }

};



TEST_F(_virtualTable, DefaultConstruction)
{
    //string
    //VT.Insert(VirtualClass())
}



TEST_F(_virtualTable, StringHashing)
{
    uint id = 0;
    string t = "Testing";

    id = VT.Insert(t);
    ASSERT_NE(id, 0);
    ASSERT_EQ(VT.FindName(id), t);
    ASSERT_EQ(VT.FindID(t), id);

    uint id1 = 0;
    string t1 = "Texting";

    id1 = VT.Insert(t1);
    ASSERT_NE(id1, 0);
    ASSERT_NE(id1, id);
    ASSERT_EQ(VT.FindName(id1), t1);
    ASSERT_EQ(VT.FindID(t1), id1);
}

TEST_F(_virtualTable, VariableInsertion)
{
    //string name = "Testing";
    //uint id = VT.Insert(name);

    //Literal v1 = 10;
    //VT.Set(id, v1);

    //ASSERT_EQ(VT.Get(id), v1);
}

TEST_F(_virtualTable, ClassInsertion)
{
    string typeName = "TestClass";
    string propName = "TestProperty";
    string varName = "TestVariable";
    string instName = "ClassInstance";

    uint idt = VT.Insert(typeName);
    uint idp = VT.Insert(propName);
    uint idv = VT.Insert(varName);
    uint idi = VT.Insert(instName);

    VirtualClass type(idt);
    VirtualProperty prop(idp);

    type.Insert(prop);
    VT.Insert(type);
    VT.Set(idt, idi, idp, 10);

    ASSERT_TRUE(VT.Get(idi).IsNull());
    
    ASSERT_EQ(VT.Get(idt, idi, idp).Value, 10);

}