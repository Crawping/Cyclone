#include "GraphicsPipeline.h"



/** CONSTRUCTORS & DESTRUCTOR **/
GraphicsPipeline::GraphicsPipeline() :
	_id(glCreateProgram())
{

}
GraphicsPipeline::~GraphicsPipeline()
{
	if (_id)
		glDeleteProgram(_id);
}



/** BINDING UTILITIES **/
void GraphicsPipeline::Bind(int slot)		const
{
	BindEntity();
	BindResources();
}
void GraphicsPipeline::BindEntity(int slot) const
{
	glUseProgram(ID());
}

void GraphicsPipeline::Unbind()				const
{
	UnbindResources();
	UnbindEntity();
}
void GraphicsPipeline::UnbindEntity()		const
{
	glUseProgram(0);
}