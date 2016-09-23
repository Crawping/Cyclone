#include "InputControls.h"
#include <sstream>
using std::string;


namespace Cyclone
{
    namespace Platform
    {

        string InputControls::Report() const
        {
            std::stringstream msg;
            msg << "Input Control Flags Set:";
            if (Value & InputControls::Alt)             { msg << "\n\tAlt"; }
            if (Value & InputControls::CapsLock)        { msg << "\n\tCapsLock"; }
            if (Value & InputControls::Ctrl)            { msg << "\n\tCtrl"; }
            if (Value & InputControls::Hyper)           { msg << "\n\tHyper"; }
            if (Value & InputControls::Meta)            { msg << "\n\tMeta"; }
            if (Value & InputControls::NumLock)         { msg << "\n\tNumLock"; }
            if (Value & InputControls::Shift)           { msg << "\n\tShift"; }
            if (Value & InputControls::Super)           { msg << "\n\tSuper"; }
            if (Value & InputControls::Switch)          { msg << "\n\tSwitch"; }
            if (Value & InputControls::Button001)       { msg << "\n\tButton001"; }
            if (Value & InputControls::Button002)       { msg << "\n\tButton002"; }
            if (Value & InputControls::Button003)       { msg << "\n\tButton003"; }
            if (Value & InputControls::Button004)       { msg << "\n\tButton004"; }
            if (Value & InputControls::Button005)       { msg << "\n\tButton005"; }
            if (Value & InputControls::Button006)       { msg << "\n\tButton006"; }
            if (Value & InputControls::Button007)       { msg << "\n\tButton007"; }
            if (Value & InputControls::Button008)       { msg << "\n\tButton008"; }
            if (Value & InputControls::Button009)       { msg << "\n\tButton009"; }
            if (Value & InputControls::Button010)       { msg << "\n\tButton010"; }
            if (Value & InputControls::Button011)       { msg << "\n\tButton011"; }
            if (Value & InputControls::Button012)       { msg << "\n\tButton012"; }
            if (Value & InputControls::Button013)       { msg << "\n\tButton013"; }
            if (Value & InputControls::Button014)       { msg << "\n\tButton014"; }
            if (Value & InputControls::Button015)       { msg << "\n\tButton015"; }
            if (Value & InputControls::Button016)       { msg << "\n\tButton016"; }
            if (Value & InputControls::Button017)       { msg << "\n\tButton017"; }
            if (Value & InputControls::Button018)       { msg << "\n\tButton018"; }
            if (Value & InputControls::Button019)       { msg << "\n\tButton019"; }
            if (Value & InputControls::Button020)       { msg << "\n\tButton020"; }
                                                          
            if (Value == InputControls::Nothing)        { msg << "\n\tNothing."; }
    
            return msg.str();
        }

        string InputControls::ToString() const
        {
            switch (Value)
            {
                case InputControls::Alt:                return "Alt";
                case InputControls::CapsLock:           return "CapsLock";
                case InputControls::Ctrl:               return "Ctrl";
                case InputControls::Hyper:              return "Hyper";
                case InputControls::Meta:               return "Meta";
                case InputControls::NumLock:            return "NumLock";
                case InputControls::Shift:              return "Shift";
                case InputControls::Super:              return "Super";
                case InputControls::Switch:             return "Switch"; 
                case InputControls::Button001:          return "Button001";
                case InputControls::Button002:          return "Button002";
                case InputControls::Button003:          return "Button003";
                case InputControls::Button004:          return "Button004";
                case InputControls::Button005:          return "Button005";
                case InputControls::Button006:          return "Button006";
                case InputControls::Button007:          return "Button007";
                case InputControls::Button008:          return "Button008";
                case InputControls::Button009:          return "Button009";
                case InputControls::Button010:          return "Button010";
                case InputControls::Button011:          return "Button011";
                case InputControls::Button012:          return "Button012";
                case InputControls::Button013:          return "Button013";
                case InputControls::Button014:          return "Button014";
                case InputControls::Button015:          return "Button015";
                case InputControls::Button016:          return "Button016";
                case InputControls::Button017:          return "Button017";
                case InputControls::Button018:          return "Button018";
                case InputControls::Button019:          return "Button019";
                case InputControls::Button020:          return "Button020";
                default:                                return "Unknown";
            }
        }

    }
}