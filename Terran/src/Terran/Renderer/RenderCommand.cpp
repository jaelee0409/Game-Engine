#include "pch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Terran {

    RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();

}