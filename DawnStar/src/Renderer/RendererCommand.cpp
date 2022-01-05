#include "dspch.h"

#include "RendererCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace DawnStar {
	RendererAPI* RendererCommand::s_rendererAPI = new OpenGLRendererAPI();
}