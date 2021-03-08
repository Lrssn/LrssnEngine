#include "lepch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace LrssnEngine {

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) 	{
		switch (type) 		{
		case LrssnEngine::ShaderDataType::Float:    return GL_FLOAT;
		case LrssnEngine::ShaderDataType::Float2:   return GL_FLOAT;
		case LrssnEngine::ShaderDataType::Float3:   return GL_FLOAT;
		case LrssnEngine::ShaderDataType::Float4:   return GL_FLOAT;
		case LrssnEngine::ShaderDataType::Mat3:     return GL_FLOAT;
		case LrssnEngine::ShaderDataType::Mat4:     return GL_FLOAT;
		case LrssnEngine::ShaderDataType::Int:      return GL_INT;
		case LrssnEngine::ShaderDataType::Int2:     return GL_INT;
		case LrssnEngine::ShaderDataType::Int3:     return GL_INT;
		case LrssnEngine::ShaderDataType::Int4:     return GL_INT;
		case LrssnEngine::ShaderDataType::Bool:     return GL_BOOL;
		}

		LE_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray() 	{
		glCreateVertexArrays(1, &mRendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray() 	{
		glDeleteVertexArrays(1, &mRendererID);
	}

	void OpenGLVertexArray::Bind() const 	{
		glBindVertexArray(mRendererID);
	}

	void OpenGLVertexArray::Unbind() const 	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) 	{
		LE_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

		glBindVertexArray(mRendererID);
		vertexBuffer->Bind();

		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout) 		{
			glEnableVertexAttribArray(mVertexBufferIndex);
			glVertexAttribPointer(mVertexBufferIndex,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.Offset);
			mVertexBufferIndex++;
		}
		mVertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) 	{
		glBindVertexArray(mRendererID);
		indexBuffer->Bind();

		mIndexBuffer = indexBuffer;
	}

}