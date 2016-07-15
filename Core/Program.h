/* CHANGELOG
 * Written by Josh Grooms on 20160702
 */

#pragma once



class Program
{
    public:

        /** CONSTRUCTOR & DESTRUCTOR **/
        Program(int nargs, char** args);
        ~Program();



        /** UTILITIES **/
        /// <summary> Runs the main event loop for the program. </summary>
        void Execute();

    private:

        bool    _debug;
        int     _display;
        bool    _showHelp;



        /** UTILITIES **/
        void ParseInputArguments(int nargs, char** args);
};
