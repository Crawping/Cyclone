/* CHANGELOG
 * Written by Josh Grooms on 20160702
 */

#pragma once



class Program
{
    //public:
    //    /** PROPERTIES **/
    //    /* DEBUG - Gets whether or not this program is being executed with debugging functionality enabled.
    //    *
    //    *      This property is controlled via the command-line startup option '--debug'. By default, it takes on a value of
    //    *      'false'.
    //    */
    //    bool Debug() const { return _debug; }
    //    /* HASERRORS - Determines whether or not any errors have been logged throughout the existence of this program. */
    //    bool HasErrors() const { return _hasErrors; }



    //    /** EVENTS **/
    //    //        Action OnExceptionThrown;
    //    //Event<int> OnInputEvent;



    //    /** CONSTRUCTOR & DESTRUCTOR **/
    //    Program(int nargs, char** args);
    //    ~Program();



    //    /** UTILITIES **/
    //    /* EXECUTE - Runs the main event loop for the program. */
    //    void Execute();



    //    /** LOGGING UTILITIES **/
    //    /* POSTERRORMESSAGE - Displays an error message in the application event log.
    //    *
    //    *      This method both displays an error message and forces the running program to terminate. It does this by enabling a flag
    //    *      that causes the application's main event loop to abort at the beginning of its next iteration.
    //    *
    //    *      Therefore, only use this method to log errors that should result in the program (safely) crashing.
    //    */
    //    void PostErrorMessage(const string& msg);
    //    void PostErrorMessage(const string& fileName, int lineNumber, const string& msg);
    //    /* POSTGENERALMESSAGE - Displays a general information message in the application event log.
    //    *
    //    *      Unlike 'PostErrorMessage', this method has no additional side effects. It is intended for use when logging any information
    //    *      of general interest.
    //    */
    //    void PostGeneralMessage(const string& msg);
    //    void PostGeneralMessage(const string& fileName, int lineNumber, const string& msg);
    //    /* POSTWARNINGMESSAGE - Displays a warning message in the application event log.
    //    *
    //    *      Unlike 'PostErrorMessage', this method has no additional side effects. It is intended for use when logging non-
    //    *      catastrophic errors or events.
    //    */
    //    void PostWarningMessage(const string& msg);
    //    void PostWarningMessage(const string& fileName, int lineNumber, const string& msg);


    //private:
    //    bool    _debug;
    //    int     _display;

        ///* CONTROLS - A pointer to the active user input device manager object. */
        //InputManager*   Controls;
        ///* DESKTOP - A pointer to the active desktop window manager. */
        //Desktop3D*      Desktop;
        ///* RENDERER - A pointer to the active OpenGL 3D rendering display. */
        //Display3D*      Renderer;
        ///* SERVER - A pointer to the active X11 display server interface. */
        //DisplayServer*  Server;

        /* ORIGINALFOCUS - The window that possesses the input focus when this application is launched.
        *
        *      This value is used to restore input focus to its original place once this application exits, which is helpful during
        *      development because, at least for now, no other window managers can be running when testing this program.
        */
        //Window          OriginalFocus;
        /* ORIGINALREVERT - The value of the 'revert_to' argument for the original focus window.
        *
        *      This value is needed to properly restore input focus to its original place once the application exists.
        */
        //int             OriginalRevert;

        void InitializeOpenGL();
        void ParseInputArguments(int nargs, char** args);


};



/** GLOBAL VARIABLES **/
/* APPLICATION - A pointer to the running program instance. */
extern Program* Application;

