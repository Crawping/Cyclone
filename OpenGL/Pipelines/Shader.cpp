#include "Console.h"
#include "EnumerationsGL.h"
#include "OpenGL.h"
#include "Shader.h"
#include "Utilities.h"
#include <regex>
#include <sstream>

using std::string;


namespace Cyclone
{
    namespace OpenGL
    {
        /** CONSTRUCTOR & DESTRUCTOR **/
        Shader::Shader(string fileName, ShaderTypes type) :
            _id(glCreateShader(type)),
            _location(fileName),
            _type(type)
        {
            string src = readfile(_location);
            if (src.size() == 0)
                Console::WriteLine("Unable to open and read the shader program file " + _location);
            else
            {
                src = Preprocess(src);
                Compile(src);
            }
        }
        Shader::~Shader()
        {
            if (_id)
                glDeleteShader(_id);
        }



        /** PRIVATE UTILITIES **/
        /// <summary> Compiles the GLSL source code for this shader into a binary package. </summary>
        /// <remarks> Compiled shader programs can be linked together to form a shader program pipeline. </remarks>
        void Shader::Compile(string src)
        {
            const char* srcstr = src.c_str();
            glShaderSource(ID(), 1, &srcstr, NULL);

            GLint status;
            glCompileShader(ID());
            glGetShaderiv(ID(), GL_COMPILE_STATUS, &status);

            if (status == GL_FALSE)
            {
                Console::WriteLine("Failed to compile the shader program in " + _location);
                Console::WriteLine("GPU Error Information: " + ReportShaderLog());
            }
        }

        /// <summary> Edits the GLSL source code as necessary before passing it on to the shader program compiler. </summary>
        /// <remarks>
        ///     This method provides a customizable preprocessing stage for GLSL source code, allowing for additional feature support
        ///     within those files. Currently, it is being used to provide basic support for #include directives referencing other
        ///     files.
        /// </remarks>
        string Shader::Preprocess(string src)
        {
            const static std::regex incPattern("\\s*#\\s*include\\s+\"(.*)\"");
            const string path(SourcePath().substr(0, SourcePath().find_last_of("/")));

            std::smatch incMatches;
            std::stringstream prepsrc;
            while (std::regex_search(src, incMatches, incPattern))
            {
                prepsrc << incMatches.prefix().str();

                string filestr = readfile(path + "/" + incMatches[1].str());
                if (filestr.size() == 0)
                {
                    Console::WriteLine("Unable to locate the file \"" + incMatches[1].str() + "\" for inclusion in this shader.");
                    return src;
                }

                prepsrc << Preprocess(filestr);
                src = incMatches.suffix().str();
            }

            prepsrc << src;
            return prepsrc.str();
        }

        /// <summary> Retrieves and posts error information that was logged while attempting to compile this shader program. </summary>
        string Shader::ReportShaderLog()
        {
            GLint nchars = 0;
            glGetShaderiv(ID(), GL_INFO_LOG_LENGTH, &nchars);
            if (nchars > 0)
            {
                GLchar msg[1024];
                glGetShaderInfoLog(ID(), nchars, 0, msg);
                return msg;
            }
            return "No errors were detected.";
        }

    }
}
