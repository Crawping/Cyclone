/* CHANGELOG
 * Written by Josh Grooms on 20160705
 */

#pragma once
#include "OpenGLAPI.h"

struct	Color4;
class	FrameBuffer;
struct	Transform;



struct OpenGLAPI PipelineConfiguration
{
	// Blend settings
	const Color4*		ClearColor;
	FrameBuffer*		RenderTarget;
};

struct OpenGLAPI FrameConfiguration
{
	const Transform*	ViewProjection;
	unsigned int		Timestamp;
};