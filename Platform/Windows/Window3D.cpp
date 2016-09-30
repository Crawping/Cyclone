#include "Console.h"
#include "Math/Vector2.h"
#include "Utilities.h"
#include "Window3D.h"
#include "Windows/WGL.h"
#include <Windows.h>

using namespace Cyclone::Platform;
using namespace Cyclone::Utilities;



/** INTERNAL FUNCTIONS **/
static KeyboardKeys translateKeys(WPARAM keyCode)
{
    switch (keyCode)
    {
        case VK_CONTROL:    return KeyboardKeys::Control;
        case VK_MENU:       return KeyboardKeys::Alt;
        case VK_SHIFT:      return KeyboardKeys::Shift;
        case VK_SPACE:      return KeyboardKeys::Space;
        case VK_F1:         return KeyboardKeys::F1;
        case VK_F2:         return KeyboardKeys::F2;
        case 0x41:          return KeyboardKeys::A;
        case 0x42:          return KeyboardKeys::B;
        case 0x43:          return KeyboardKeys::C;
        case 0x44:          return KeyboardKeys::D;
        case 0x45:          return KeyboardKeys::E;
        case 0x46:          return KeyboardKeys::F;
        case 0x47:          return KeyboardKeys::G;
        case 0x48:          return KeyboardKeys::H;
        case 0x49:          return KeyboardKeys::I;
        case 0x4A:          return KeyboardKeys::J;
        case 0x4B:          return KeyboardKeys::K;
        case 0x4C:          return KeyboardKeys::L;
        case 0x4D:          return KeyboardKeys::M;
        case 0x4E:          return KeyboardKeys::N;
        case 0x4F:          return KeyboardKeys::O;
        case 0x50:          return KeyboardKeys::P;
        case 0x51:          return KeyboardKeys::Q;
        case 0x52:          return KeyboardKeys::R;
        case 0x53:          return KeyboardKeys::S;
        case 0x54:          return KeyboardKeys::T;
        case 0x55:          return KeyboardKeys::U;
        case 0x56:          return KeyboardKeys::V;
        case 0x57:          return KeyboardKeys::W;
        case 0x58:          return KeyboardKeys::X;
        case 0x59:          return KeyboardKeys::Y;
        case 0x5A:          return KeyboardKeys::Z;
        default:            return KeyboardKeys::Nothing;
    }
}
/// <summary> Handles any events posted to a specific window on the Windows platform. </summary>
/// <param name="win"> The handle of the window to which the event is being posted. </param>
/// <param name="msg"> The type of event that is being posted. </param>
/// <param name="wparam"> An argument of unknown significance. </param>
/// <param name="lparam"> An argument of unknown significance. </param>
/// <returns> An argument of unknown significance. </returns>
static LRESULT CALLBACK WindowMessageLoop(HWND win, UINT msg, WPARAM wparam, LPARAM lparam)
{
    Window3D* win3D = (Window3D*)GetWindowLong(win, GWLP_USERDATA);
    KeyboardKeys key;

    if (win3D)
    {
        switch (msg)
        {
            case WM_CLOSE:
                win3D->Close();
                break;
            case WM_DESTROY:
                break;

            case WM_KEYDOWN:
            case WM_SYSKEYDOWN:
                key = translateKeys(wparam);
                if (key.Count())
                    win3D->ProcessKeyPress(key);
                break;

            case WM_KEYUP:
            case WM_SYSKEYUP:
                key = translateKeys(wparam);
                if (key.Count())
                    win3D->ProcessKeyRelease(key);
                break;

            case WM_LBUTTONDBLCLK:
            case WM_LBUTTONDOWN:
                win3D->ProcessButtonPress(PointerButtons::Button001);
                break;

            case WM_LBUTTONUP:
                win3D->ProcessButtonRelease(PointerButtons::Button001);
                break;

            case WM_MBUTTONDBLCLK:
            case WM_MBUTTONDOWN:
                win3D->ProcessButtonPress(PointerButtons::Button002);
                break;

            case WM_MBUTTONUP:
                win3D->ProcessButtonRelease(PointerButtons::Button002);
                break;

            case WM_RBUTTONDBLCLK:
            case WM_RBUTTONDOWN:
                win3D->ProcessButtonPress(PointerButtons::Button003);
                break;

            case WM_RBUTTONUP:
                win3D->ProcessButtonRelease(PointerButtons::Button003);
                break;

            case WM_XBUTTONDBLCLK:
            case WM_XBUTTONDOWN:
            case WM_XBUTTONUP:
                break;

            case WM_MOUSEMOVE:
                POINTS pts = MAKEPOINTS(lparam);
                win3D->UpdatePointerPosition(pts.x, pts.y);
                break;

            case WM_MOUSEWHEEL:
            case WM_MOUSEHWHEEL:
                break;

            case WM_SIZE:
                win3D->ProcessSizeChange();
                break;

            default:            break;
        }
    }

    return DefWindowProc(win, msg, wparam, lparam);
}
/// <summary> Converts a standard text string into an equivalent wide-character one. </summary>
/// <param name="text"> A standard string of text. </param>
/// <returns> A string that is identical to the inputted one except composed of wide-characters. </returns>
static std::wstring str2wstr(const std::string& text)
{
    int length = MultiByteToWideChar(CP_UTF8, 0, text.c_str(), -1, NULL, 0);
    if (!length)
    {
        PostInfo("Failed to convert the inputted text.");
        return L"";
    }

    WCHAR* wtext = (WCHAR*)calloc(length + 1, sizeof(WCHAR));
    if (!MultiByteToWideChar(CP_UTF8, 0, text.c_str(), -1, wtext, length + 1))
    {
        free(wtext);
        PostInfo("Failed to convert the inputted text.");
        return L"";
    }

    std::wstring wstr = wtext;
    free(wtext);
    return wstr;
}



namespace Cyclone
{
    namespace Platform
    {

        /** PROPERTIES **/
        Window3D& Window3D::IsTrackingKeyRepeat(bool value)
        {
            _isTrackingKeyRepeat = value;
            return *this;
        }
        Window3D& Window3D::IsTrackingPointer(bool value)
        {
            _isTrackingPointer = value;
            if (!value) { _pointerPosition = Vector2::Zero; }
            return *this;
        }
        Window3D& Window3D::Title(const string& title)
        {
            _title = title;
            SetWindowText(Internals->ID, str2wstr(title).c_str());
            return *this;
        }



        /** CONSTRUCTOR & DESTRUCTOR **/
        Window3D::Window3D(const Area& displayArea, const string& title, int nsamples) :
            Internals(nullptr),
            _isBordered(true),
            _isTrackingKeyboard(true),
            _isTrackingKeyRepeat(true),
            _isTrackingPointer(true),
            _title(title)
        {
            std::wstring winClass = str2wstr("WindowWGL");
            std::wstring winTitle = str2wstr(title);

            int DefaultPixelAttributes[] =
            {
                WGL_SUPPORT_OPENGL_ARB,             GL_TRUE,
                WGL_PIXEL_TYPE_ARB,                 WGL_TYPE_RGBA_ARB,
                WGL_ACCELERATION_ARB,               WGL_FULL_ACCELERATION_ARB,
                WGL_COLOR_BITS_ARB,                 32,
                WGL_ALPHA_BITS_ARB,                 8,
                WGL_DEPTH_BITS_ARB,                 24,
                WGL_STENCIL_BITS_ARB,               8,
                WGL_DOUBLE_BUFFER_ARB,              GL_TRUE,
                WGL_SAMPLE_BUFFERS_ARB,             GL_TRUE,
                nsamples ? WGL_SAMPLES_ARB : NULL,  nsamples,
                //WGL_SAMPLES_ARB,                0,
                NULL,
            };          

			WindowSettings settings = 
			{
                winClass.c_str(),
				{ (int)displayArea.Left(), (int)displayArea.Bottom(), (int)displayArea.Right(), (int)displayArea.Top() },
				WindowMessageLoop,
				DefaultPixelAttributes,
				winTitle.c_str(),
			};

            Internals = wglCreateWindow(&settings);
            if (Internals)
            {
				SetWindowLong(Internals->ID, GWLP_USERDATA, (long)this);
                ProcessSizeChange();
                ShowWindow(Internals->ID, SW_SHOW);
            }
        }

        Window3D::~Window3D()
        {
            if (Internals) { wglDestroyWindow(Internals); }
        }


        
        /** PUBLIC UTILITIES **/
        void Window3D::Close()
        {
            PostQuitMessage(0);
            OnClose();
        }
        void Window3D::Fill(const Area& displayArea)
        {
            SetWindowPos(Internals->ID, 0, displayArea.X, displayArea.Y, displayArea.Width, displayArea.Height, SWP_NOZORDER);
        }
        bool Window3D::ProcessEvent()
        {
            MSG msg;
            if (PeekMessage(&msg, Internals->ID, 0, 0, PM_REMOVE))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);

                if (msg.message == WM_QUIT)
                    return false;
            }

            return true;
        }        



        /** INTERNAL UTILITIES **/
        void Window3D::ProcessButtonPress(PointerButtons button)
        {
            if (!IsTrackingPointer()) { return; }

            _pointerButtonState |= button;
            PointerClickEvent evt =
            {
                button,
                PointerButtonState(),
            };
            OnButtonPress(evt);
        }
        void Window3D::ProcessButtonRelease(PointerButtons button)
        {
            if (!IsTrackingPointer()) { return; }

            _pointerButtonState &= ~button;
            PointerClickEvent evt =
            {
                button,
                PointerButtonState(),
            };
            OnButtonRelease(evt);
        }
        void Window3D::ProcessKeyPress(KeyboardKeys key)
        {
            if ( !IsTrackingKeyboard() || (!IsTrackingKeyRepeat() && _keyboardState.IsPressed(key)) )
                return;
            
            KeyboardEvent evt =
            {
                key,
                _keyboardState.Press(key),
            };
            OnKeyPress(evt);
        }
        void Window3D::ProcessKeyRelease(KeyboardKeys key)
        {
            if (!IsTrackingKeyboard()) { return; }

            KeyboardEvent evt =
            {
                key,
                _keyboardState.Release(key),
            };
            OnKeyRelease(evt);
        }
        void Window3D::ProcessSizeChange()
        {
            RECT displayRect;
            GetWindowRect(Internals->ID, &displayRect);

            Area displayArea = Area
            (
                displayRect.left, displayRect.top,
                displayRect.right - displayRect.left,
                displayRect.bottom - displayRect.top
            );

            if (_displayArea == displayArea) { return; }
            
            RECT renderRect;
            GetClientRect(Internals->ID, &renderRect);

            _displayArea = displayArea;
            _clientArea = Area
            (
                renderRect.left, renderRect.top,
                renderRect.right - renderRect.left,
                renderRect.bottom - renderRect.top
            );

            OnResize();
        }
        void Window3D::UpdatePointerPosition(int x, int y)
        {
            if (!IsTrackingPointer())                                   { return; }
            if (x == PointerPosition().X && y == PointerPosition().Y)   { return; }
            
            Vector2 oldPosition = PointerPosition();
            _pointerPosition = Vector2(x, y);

            PointerMotionEvent evt =
            {
                PointerPosition() - oldPosition,
                PointerPosition(),
            };
            OnPointerMotion(evt);
        }



        /** INTERNAL RENDERING UTILITIES **/
        void Window3D::Bind()               const { wglMakeCurrent(Internals->DeviceContext, Internals->RenderContext); }
        void Window3D::Present()            const { SwapBuffers(Internals->DeviceContext); }
        void Window3D::Unbind()             const { wglMakeCurrent(Internals->DeviceContext, NULL); }
    }
}