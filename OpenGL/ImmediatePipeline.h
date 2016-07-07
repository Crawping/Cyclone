/* CHANGELOG
 * Written by Josh Grooms on 20160705
 */

#pragma once
#include "GraphicsPipeline.h"

struct Area;
struct Color4;



class ImmediatePipeline : public GraphicsPipeline
{
	public:
		/** CONSTRUCTOR & DESTRUCTOR **/
		/* SHADERPIPELINE - Constructs an OpenGL rendering pipeline consisting only vertex and fragment shading stages. */
		OpenGLAPI ImmediatePipeline();
		OpenGLAPI ~ImmediatePipeline();



		/** UTILITIES **/
		int GetAttributeID(const string& name);
		/* GETUNIFORM - Retrieves the current value of a specific transformation matrix from this shader pipeline. */
		void GetUniform(const string& name, Transform* value);
		/* GETUNIFORMID - Returns the integer handle to a uniform variable within this shader pipeline.
		*
		*      SYNTAX:
		*          id = S.GetUniformID(name)
		*
		*      OUTPUT:
		*          id:     GLint
		*                  A single unique integer handle identifying the uniform variable 'name' on the GPU. This handle
		*                  can then be used to modify the value of the uniform shader variable before rendering is
		*                  performed. If no variable called 'name' can be found within any of the shader programs, then this
		*                  argument will take a value of -1.
		*
		*      INPUTS:
		*          S:      ShaderPipeline
		*                  A single valid rendering pipeline object containing compiled and linked GPU shader programs.
		*
		*          name:   STRING
		*                  A string containing the name of a uniform variable exactly as it is defined within one of the
		*                  shader programs attached to this pipeline. Letter casing is significant here.
		*/
		int GetUniformID(const string& name);
		
		/* SETUNIFORM - Copies an area description into a uniform shader variable (a four-element vector) on the GPU. */
		void SetUniform(GLint id, const Area& value);
		/* SETUNIFORM - Copies a 32-bit RGBA color into a uniform shader variable (a four-element vector) on the GPU. */
		void SetUniform(GLint id, const Color4& value);
		/* SETUNIFORM - Copies a 32-bit integer value into an equivalent uniform shader variable on the GPU. */
		void SetUniform(GLint id, int value);
		/* SETUNIFORM - Copies a 4x4 transformation matrix into an equivalent uniform shader variable on the GPU. */
		void SetUniform(GLint id, const Transform& value);

		/* SETUNIFORM - Copies an area description into a uniform shader variable (a four-element vector) on the GPU. */
		void SetUniform(string name, const Area& value);
		/* SETUNIFORM - Copies a 32-bit RGBA color into a uniform shader variable (a four-element vector) on the GPU. */
		void SetUniform(string name, const Color4& value);
		/* SETUNIFORM - Copies a 4x4 transformation matrix into an equivalent uniform shader variable on the GPU. */
		void SetUniform(string name, const Transform& value);
		/* SETUNIFORM - Copies a two-element vector into an equivalent uniform shader variable on the GPU. */
		void SetUniform(string name, const Vector2& value);
		/* SETUNIFORM - Copies a three-element vector into an equivalent uniform shader varibale on the GPU. */
		void SetUniform(string name, const Vector3& value);



		/** BINDING UTILITIES **/


		/** RENDERING METHODS **/
		void Execute()							override;
		void Input(const IRenderable& entity)	override;
		void Input(const PerFrame& frameData)	override;
		void Reset()							override;




};