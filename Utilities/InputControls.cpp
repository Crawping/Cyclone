#include "InputControls.h"
#include <sstream>
using std::string;


namespace Cyclone
{
    namespace Utilities
    {

        string PointerButtons::Report() const
        {
            std::stringstream msg;
            msg << "Input Control Chord:";
            if (Value & PointerButtons::Button001)       { msg << "\n\tButton001"; }
            if (Value & PointerButtons::Button002)       { msg << "\n\tButton002"; }
            if (Value & PointerButtons::Button003)       { msg << "\n\tButton003"; }
            if (Value & PointerButtons::Button004)       { msg << "\n\tButton004"; }
            if (Value & PointerButtons::Button005)       { msg << "\n\tButton005"; }
            if (Value & PointerButtons::Button006)       { msg << "\n\tButton006"; }
            if (Value & PointerButtons::Button007)       { msg << "\n\tButton007"; }
            if (Value & PointerButtons::Button008)       { msg << "\n\tButton008"; }
            if (Value & PointerButtons::Button009)       { msg << "\n\tButton009"; }
            if (Value & PointerButtons::Button010)       { msg << "\n\tButton010"; }
            if (Value & PointerButtons::Button011)       { msg << "\n\tButton011"; }
            if (Value & PointerButtons::Button012)       { msg << "\n\tButton012"; }
            if (Value & PointerButtons::Button013)       { msg << "\n\tButton013"; }
            if (Value & PointerButtons::Button014)       { msg << "\n\tButton014"; }
            if (Value & PointerButtons::Button015)       { msg << "\n\tButton015"; }
            if (Value & PointerButtons::Button016)       { msg << "\n\tButton016"; }
            if (Value & PointerButtons::Button017)       { msg << "\n\tButton017"; }
            if (Value & PointerButtons::Button018)       { msg << "\n\tButton018"; }
            if (Value & PointerButtons::Button019)       { msg << "\n\tButton019"; }
            if (Value & PointerButtons::Button020)       { msg << "\n\tButton020"; }

            if (Value == PointerButtons::Nothing)        { msg << "\n\tNothing."; }

            return msg.str();
        }

        string PointerButtons::ToString() const
        {
            switch (Value)
            {
                case PointerButtons::Button001:          return "Button001";
                case PointerButtons::Button002:          return "Button002";
                case PointerButtons::Button003:          return "Button003";
                case PointerButtons::Button004:          return "Button004";
                case PointerButtons::Button005:          return "Button005";
                case PointerButtons::Button006:          return "Button006";
                case PointerButtons::Button007:          return "Button007";
                case PointerButtons::Button008:          return "Button008";
                case PointerButtons::Button009:          return "Button009";
                case PointerButtons::Button010:          return "Button010";
                case PointerButtons::Button011:          return "Button011";
                case PointerButtons::Button012:          return "Button012";
                case PointerButtons::Button013:          return "Button013";
                case PointerButtons::Button014:          return "Button014";
                case PointerButtons::Button015:          return "Button015";
                case PointerButtons::Button016:          return "Button016";
                case PointerButtons::Button017:          return "Button017";
                case PointerButtons::Button018:          return "Button018";
                case PointerButtons::Button019:          return "Button019";
                case PointerButtons::Button020:          return "Button020";
                default:                                 return "Unknown";
            }
        }



        /** KEYBOARD **/
        KeyboardKeys::KeyboardKeys(enum Keys k)
        {
            Press(k);
        }


        /** PUBLIC KEYBOARD UTILITIES **/
        bool KeyboardKeys::IsPressed(enum Keys k) const
        {
            if (k)
                return State[k];
            else
                return Count() == 0;
        }
        bool KeyboardKeys::IsPressed(const KeyboardKeys& k) const
        {
            if (k.Count() > Count()) { return false; }
            return (State & k.State) == k.State;
        }

        KeyboardKeys& KeyboardKeys::Press(enum Keys k)
        {
            if (k) { State[k] = 1; }
            return *this;
        }
        KeyboardKeys& KeyboardKeys::Press(const KeyboardKeys& k)
        {
            if (k.Count())
                State |= k.State;
            return *this;
        }
        KeyboardKeys& KeyboardKeys::Release(enum Keys k)
        {
            if (k) { State[k] = 0; }
            return *this;
        }
        KeyboardKeys& KeyboardKeys::Release(const KeyboardKeys& k)
        {
            if (k.Count())
                State &= ~k.State;
            return *this;
        }

        

        /** OPERATORS **/
        bool KeyboardKeys::operator ==(const KeyboardKeys& other) const
        {
            if (Count() != other.Count()) { return false; }
            return State == other.State;
        }


        /** REPORTING UTILITIES **/
        string KeyboardKeys::Report() const
        {
            std::stringstream msg;
            msg << "Keyboard Control Chord:";

            if (Count() == 0) { msg << " Nothing"; return msg.str(); }

            if (State[KeyboardKeys::Nothing])           { msg << "\n\tNothing"; }
            if (State[KeyboardKeys::Escape])            { msg << "\n\tEscape"; }
            if (State[KeyboardKeys::F1])                { msg << "\n\tF1"; }
            if (State[KeyboardKeys::F2])                { msg << "\n\tF2"; }
            if (State[KeyboardKeys::F3])                { msg << "\n\tF3"; }
            if (State[KeyboardKeys::F4])                { msg << "\n\tF4"; }
            if (State[KeyboardKeys::F5])                { msg << "\n\tF5"; }
            if (State[KeyboardKeys::F6])                { msg << "\n\tF6"; }
            if (State[KeyboardKeys::F7])                { msg << "\n\tF7"; }
            if (State[KeyboardKeys::F8])                { msg << "\n\tF8"; }
            if (State[KeyboardKeys::F9])                { msg << "\n\tF9"; }
            if (State[KeyboardKeys::F10])               { msg << "\n\tF10"; }
            if (State[KeyboardKeys::F11])               { msg << "\n\tF11"; }
            if (State[KeyboardKeys::F12])               { msg << "\n\tF12"; }
            if (State[KeyboardKeys::Zero])              { msg << "\n\tZero"; }
            if (State[KeyboardKeys::One])               { msg << "\n\tOne"; }
            if (State[KeyboardKeys::Two])               { msg << "\n\tTwo"; }
            if (State[KeyboardKeys::Three])             { msg << "\n\tThree"; }
            if (State[KeyboardKeys::Four])              { msg << "\n\tFour"; }
            if (State[KeyboardKeys::Five])              { msg << "\n\tFive"; }
            if (State[KeyboardKeys::Six])               { msg << "\n\tSix"; }
            if (State[KeyboardKeys::Seven])             { msg << "\n\tSeven"; }
            if (State[KeyboardKeys::Eight])             { msg << "\n\tEight"; }
            if (State[KeyboardKeys::Nine])              { msg << "\n\tNine"; }
            if (State[KeyboardKeys::A])                 { msg << "\n\tA"; }
            if (State[KeyboardKeys::B])                 { msg << "\n\tB"; }
            if (State[KeyboardKeys::C])                 { msg << "\n\tC"; }
            if (State[KeyboardKeys::D])                 { msg << "\n\tD"; }
            if (State[KeyboardKeys::E])                 { msg << "\n\tE"; }
            if (State[KeyboardKeys::F])                 { msg << "\n\tF"; }
            if (State[KeyboardKeys::G])                 { msg << "\n\tG"; }
            if (State[KeyboardKeys::H])                 { msg << "\n\tH"; }
            if (State[KeyboardKeys::I])                 { msg << "\n\tI"; }
            if (State[KeyboardKeys::J])                 { msg << "\n\tJ"; }
            if (State[KeyboardKeys::K])                 { msg << "\n\tK"; }
            if (State[KeyboardKeys::L])                 { msg << "\n\tL"; }
            if (State[KeyboardKeys::M])                 { msg << "\n\tM"; }
            if (State[KeyboardKeys::N])                 { msg << "\n\tN"; }
            if (State[KeyboardKeys::O])                 { msg << "\n\tO"; }
            if (State[KeyboardKeys::P])                 { msg << "\n\tP"; }
            if (State[KeyboardKeys::Q])                 { msg << "\n\tQ"; }
            if (State[KeyboardKeys::R])                 { msg << "\n\tR"; }
            if (State[KeyboardKeys::S])                 { msg << "\n\tS"; }
            if (State[KeyboardKeys::T])                 { msg << "\n\tT"; }
            if (State[KeyboardKeys::U])                 { msg << "\n\tU"; }
            if (State[KeyboardKeys::V])                 { msg << "\n\tV"; }
            if (State[KeyboardKeys::W])                 { msg << "\n\tW"; }
            if (State[KeyboardKeys::X])                 { msg << "\n\tX"; }
            if (State[KeyboardKeys::Y])                 { msg << "\n\tY"; }
            if (State[KeyboardKeys::Z])                 { msg << "\n\tZ"; }
            if (State[KeyboardKeys::Apostrophe])        { msg << "\n\tApostrophe"; }
            if (State[KeyboardKeys::BackTick])          { msg << "\n\tBackTick"; }
            if (State[KeyboardKeys::BracketOpen])       { msg << "\n\tBracketOpen"; }
            if (State[KeyboardKeys::BracketClose])      { msg << "\n\tBracketClose"; }
            if (State[KeyboardKeys::BackSlash])         { msg << "\n\tBackSlash"; }
            if (State[KeyboardKeys::Comma])             { msg << "\n\tComma"; }
            if (State[KeyboardKeys::Dash])              { msg << "\n\tDash"; }
            if (State[KeyboardKeys::Equals])            { msg << "\n\tEquals"; }
            if (State[KeyboardKeys::ForwardSlash])      { msg << "\n\tForwardSlash"; }
            if (State[KeyboardKeys::Period])            { msg << "\n\tPeriod"; }
            if (State[KeyboardKeys::Semicolon])         { msg << "\n\tSemicolon"; }
            if (State[KeyboardKeys::Backspace])         { msg << "\n\tBackspace"; }
            if (State[KeyboardKeys::Enter])             { msg << "\n\tEnter"; }
            if (State[KeyboardKeys::Space])             { msg << "\n\tSpace"; }
            if (State[KeyboardKeys::Tab])               { msg << "\n\tTab"; }
            if (State[KeyboardKeys::Alt])               { msg << "\n\tAlt"; }
            if (State[KeyboardKeys::CapsLock])          { msg << "\n\tCapsLock"; }
            if (State[KeyboardKeys::Control])           { msg << "\n\tControl"; }
            if (State[KeyboardKeys::Shift])             { msg << "\n\tShift"; }
            if (State[KeyboardKeys::Super])             { msg << "\n\tSuper"; }
            if (State[KeyboardKeys::Delete])            { msg << "\n\tDelete"; }
            if (State[KeyboardKeys::Down])              { msg << "\n\tDown"; }
            if (State[KeyboardKeys::End])               { msg << "\n\tEnd"; }
            if (State[KeyboardKeys::Home])              { msg << "\n\tHome"; }
            if (State[KeyboardKeys::Insert])            { msg << "\n\tInsert"; }
            if (State[KeyboardKeys::Left])              { msg << "\n\tLeft"; }
            if (State[KeyboardKeys::Menu])              { msg << "\n\tMenu"; }
            if (State[KeyboardKeys::PageDown])          { msg << "\n\tPageDown"; }
            if (State[KeyboardKeys::PageUp])            { msg << "\n\tPageUp"; }
            if (State[KeyboardKeys::Pause])             { msg << "\n\tPause"; }
            if (State[KeyboardKeys::PrintScreen])       { msg << "\n\tPrintScreen"; }
            if (State[KeyboardKeys::Right])             { msg << "\n\tRight"; }
            if (State[KeyboardKeys::ScrollLock])        { msg << "\n\tScrollLock"; }
            if (State[KeyboardKeys::Up])                { msg << "\n\tUp"; }
            if (State[KeyboardKeys::AsteriskKP])        { msg << "\n\tAsteriskKP"; }
            if (State[KeyboardKeys::DashKP])            { msg << "\n\tDashKP"; }
            if (State[KeyboardKeys::EnterKP])           { msg << "\n\tEnterKP"; }
            if (State[KeyboardKeys::ForwardSlashKP])    { msg << "\n\tForwardSlashKP"; }
            if (State[KeyboardKeys::NumLock])           { msg << "\n\tNumLock"; }
            if (State[KeyboardKeys::PeriodKP])          { msg << "\n\tPeriodKP"; }
            if (State[KeyboardKeys::PlusKP])            { msg << "\n\tPlusKP"; }
            if (State[KeyboardKeys::KP0])               { msg << "\n\tKP0"; }
            if (State[KeyboardKeys::KP1])               { msg << "\n\tKP1"; }
            if (State[KeyboardKeys::KP2])               { msg << "\n\tKP2"; }
            if (State[KeyboardKeys::KP3])               { msg << "\n\tKP3"; }
            if (State[KeyboardKeys::KP4])               { msg << "\n\tKP4"; }
            if (State[KeyboardKeys::KP5])               { msg << "\n\tKP5"; }
            if (State[KeyboardKeys::KP6])               { msg << "\n\tKP6"; }
            if (State[KeyboardKeys::KP7])               { msg << "\n\tKP7"; }
            if (State[KeyboardKeys::KP8])               { msg << "\n\tKP8"; }
            if (State[KeyboardKeys::KP9])               { msg << "\n\tKP9"; }

            return msg.str();
        }
        string KeyboardKeys::ToString() const
        {
            std::stringstream msg;
            if (Count() == 0) { return "Nothing"; }

            if (State[KeyboardKeys::Nothing])           { msg << " Nothing"; }
            if (State[KeyboardKeys::Escape])            { msg << " Escape"; }
            if (State[KeyboardKeys::F1])                { msg << " F1"; }
            if (State[KeyboardKeys::F2])                { msg << " F2"; }
            if (State[KeyboardKeys::F3])                { msg << " F3"; }
            if (State[KeyboardKeys::F4])                { msg << " F4"; }
            if (State[KeyboardKeys::F5])                { msg << " F5"; }
            if (State[KeyboardKeys::F6])                { msg << " F6"; }
            if (State[KeyboardKeys::F7])                { msg << " F7"; }
            if (State[KeyboardKeys::F8])                { msg << " F8"; }
            if (State[KeyboardKeys::F9])                { msg << " F9"; }
            if (State[KeyboardKeys::F10])               { msg << " F10"; }
            if (State[KeyboardKeys::F11])               { msg << " F11"; }
            if (State[KeyboardKeys::F12])               { msg << " F12"; }
            if (State[KeyboardKeys::Zero])              { msg << " Zero"; }
            if (State[KeyboardKeys::One])               { msg << " One"; }
            if (State[KeyboardKeys::Two])               { msg << " Two"; }
            if (State[KeyboardKeys::Three])             { msg << " Three"; }
            if (State[KeyboardKeys::Four])              { msg << " Four"; }
            if (State[KeyboardKeys::Five])              { msg << " Five"; }
            if (State[KeyboardKeys::Six])               { msg << " Six"; }
            if (State[KeyboardKeys::Seven])             { msg << " Seven"; }
            if (State[KeyboardKeys::Eight])             { msg << " Eight"; }
            if (State[KeyboardKeys::Nine])              { msg << " Nine"; }
            if (State[KeyboardKeys::A])                 { msg << " A"; }
            if (State[KeyboardKeys::B])                 { msg << " B"; }
            if (State[KeyboardKeys::C])                 { msg << " C"; }
            if (State[KeyboardKeys::D])                 { msg << " D"; }
            if (State[KeyboardKeys::E])                 { msg << " E"; }
            if (State[KeyboardKeys::F])                 { msg << " F"; }
            if (State[KeyboardKeys::G])                 { msg << " G"; }
            if (State[KeyboardKeys::H])                 { msg << " H"; }
            if (State[KeyboardKeys::I])                 { msg << " I"; }
            if (State[KeyboardKeys::J])                 { msg << " J"; }
            if (State[KeyboardKeys::K])                 { msg << " K"; }
            if (State[KeyboardKeys::L])                 { msg << " L"; }
            if (State[KeyboardKeys::M])                 { msg << " M"; }
            if (State[KeyboardKeys::N])                 { msg << " N"; }
            if (State[KeyboardKeys::O])                 { msg << " O"; }
            if (State[KeyboardKeys::P])                 { msg << " P"; }
            if (State[KeyboardKeys::Q])                 { msg << " Q"; }
            if (State[KeyboardKeys::R])                 { msg << " R"; }
            if (State[KeyboardKeys::S])                 { msg << " S"; }
            if (State[KeyboardKeys::T])                 { msg << " T"; }
            if (State[KeyboardKeys::U])                 { msg << " U"; }
            if (State[KeyboardKeys::V])                 { msg << " V"; }
            if (State[KeyboardKeys::W])                 { msg << " W"; }
            if (State[KeyboardKeys::X])                 { msg << " X"; }
            if (State[KeyboardKeys::Y])                 { msg << " Y"; }
            if (State[KeyboardKeys::Z])                 { msg << " Z"; }
            if (State[KeyboardKeys::Apostrophe])        { msg << " Apostrophe"; }
            if (State[KeyboardKeys::BackTick])          { msg << " BackTick"; }
            if (State[KeyboardKeys::BracketOpen])       { msg << " BracketOpen"; }
            if (State[KeyboardKeys::BracketClose])      { msg << " BracketClose"; }
            if (State[KeyboardKeys::BackSlash])         { msg << " BackSlash"; }
            if (State[KeyboardKeys::Comma])             { msg << " Comma"; }
            if (State[KeyboardKeys::Dash])              { msg << " Dash"; }
            if (State[KeyboardKeys::Equals])            { msg << " Equals"; }
            if (State[KeyboardKeys::ForwardSlash])      { msg << " ForwardSlash"; }
            if (State[KeyboardKeys::Period])            { msg << " Period"; }
            if (State[KeyboardKeys::Semicolon])         { msg << " Semicolon"; }
            if (State[KeyboardKeys::Backspace])         { msg << " Backspace"; }
            if (State[KeyboardKeys::Enter])             { msg << " Enter"; }
            if (State[KeyboardKeys::Space])             { msg << " Space"; }
            if (State[KeyboardKeys::Tab])               { msg << " Tab"; }
            if (State[KeyboardKeys::Alt])               { msg << " Alt"; }
            if (State[KeyboardKeys::CapsLock])          { msg << " CapsLock"; }
            if (State[KeyboardKeys::Control])           { msg << " Control"; }
            if (State[KeyboardKeys::Shift])             { msg << " Shift"; }
            if (State[KeyboardKeys::Super])             { msg << " Super"; }
            if (State[KeyboardKeys::Delete])            { msg << " Delete"; }
            if (State[KeyboardKeys::Down])              { msg << " Down"; }
            if (State[KeyboardKeys::End])               { msg << " End"; }
            if (State[KeyboardKeys::Home])              { msg << " Home"; }
            if (State[KeyboardKeys::Insert])            { msg << " Insert"; }
            if (State[KeyboardKeys::Left])              { msg << " Left"; }
            if (State[KeyboardKeys::Menu])              { msg << " Menu"; }
            if (State[KeyboardKeys::PageDown])          { msg << " PageDown"; }
            if (State[KeyboardKeys::PageUp])            { msg << " PageUp"; }
            if (State[KeyboardKeys::Pause])             { msg << " Pause"; }
            if (State[KeyboardKeys::PrintScreen])       { msg << " PrintScreen"; }
            if (State[KeyboardKeys::Right])             { msg << " Right"; }
            if (State[KeyboardKeys::ScrollLock])        { msg << " ScrollLock"; }
            if (State[KeyboardKeys::Up])                { msg << " Up"; }
            if (State[KeyboardKeys::AsteriskKP])        { msg << " AsteriskKP"; }
            if (State[KeyboardKeys::DashKP])            { msg << " DashKP"; }
            if (State[KeyboardKeys::EnterKP])           { msg << " EnterKP"; }
            if (State[KeyboardKeys::ForwardSlashKP])    { msg << " ForwardSlashKP"; }
            if (State[KeyboardKeys::NumLock])           { msg << " NumLock"; }
            if (State[KeyboardKeys::PeriodKP])          { msg << " PeriodKP"; }
            if (State[KeyboardKeys::PlusKP])            { msg << " PlusKP"; }
            if (State[KeyboardKeys::KP0])               { msg << " KP0"; }
            if (State[KeyboardKeys::KP1])               { msg << " KP1"; }
            if (State[KeyboardKeys::KP2])               { msg << " KP2"; }
            if (State[KeyboardKeys::KP3])               { msg << " KP3"; }
            if (State[KeyboardKeys::KP4])               { msg << " KP4"; }
            if (State[KeyboardKeys::KP5])               { msg << " KP5"; }
            if (State[KeyboardKeys::KP6])               { msg << " KP6"; }
            if (State[KeyboardKeys::KP7])               { msg << " KP7"; }
            if (State[KeyboardKeys::KP8])               { msg << " KP8"; }
            if (State[KeyboardKeys::KP9])               { msg << " KP9"; }

            return msg.str();
        }



    }
}
