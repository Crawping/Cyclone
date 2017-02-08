#include "Storage/StringLibrary.h"
#include <functional>



namespace Cyclone
{
    namespace VM
    {

        /** INTERNAL UTILITIES **/
        static std::hash<string> Hash;



        /** CONSTRUCTOR **/
        StringLibrary::StringLibrary()
        {
            _ids.Insert("", 0);
            _strings.Insert(0, "");
        }



        /** UTILITIES **/
        void StringLibrary::Clear()
        {
            _ids.Clear();
            _ids.Insert("", 0);
            _strings.Clear();
            _strings.Insert(0, "");
        }
        bool StringLibrary::Contains(uint id)               const { return _strings.Contains(id); }
        bool StringLibrary::Contains(const string& string)  const { return _ids.Contains(string); }
        const string& StringLibrary::Find(uint id)          const
        {
            return _strings[ Contains(id) ? id : 0 ];
        }
        uint StringLibrary::Find(const string& string)      const
        {
            return _ids[ Contains(string) ? string : "" ];
        }
        uint StringLibrary::Insert(const string& string)
        {
            if (string.empty()) { return 0; }
            uint id = Hash(string);
            _ids.Insert(string, id);
            _strings.Insert(id, string);
            return id;
        }
        void StringLibrary::Remove(uint id)
        {
            if (!id || !Contains(id)) { return; }
            string string = _strings[id];
            _ids.Remove(string);
            _strings.Remove(id);
        }
        void StringLibrary::Remove(const string& string)
        {
            if (string.empty() || !Contains(string)) { return; }
            uint id = _ids[string];
            _ids.Remove(string);
            _strings.Remove(id);
        }

    }
}
