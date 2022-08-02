#pragma once

#include "Terran/Renderer/Shader.h"
#include <glm/glm.hpp>

// TODO
typedef unsigned int GLenum;

namespace Terran {

	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& filePath);
		OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
		~OpenGLShader();

		virtual void Bind() const;
		virtual void Unbind() const;

		virtual void SetFloat3(const std::string& name, const glm::vec3& value) override;
		virtual void SetFloat4(const std::string& name, const glm::vec4& value) override;
		virtual void SetMat4(const std::string& name, const glm::mat4& value) override;
		virtual void SetInt(const std::string& name, int value) override;

		virtual const std::string& GetName() const override { return m_Name; }

		void UploadUniformFloat(const std::string& name, float value);
		void UploadUniformFloat2(const std::string& name, const glm::vec2& value);
		void UploadUniformFloat3(const std::string& name, const glm::vec3& value);
		void UploadUniformFloat4(const std::string& name, const glm::vec4& value);
		void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
		void UploadUniformInt(const std::string& name, int value);
		void UploadUniformInt2(const std::string& name, const glm::vec4& value);
		void UploadUniformInt3(const std::string& name, const glm::vec4& value);
		void UploadUniformInt4(const std::string& name, const glm::vec4& value);
	private:
		std::string ReadFile(const std::string& filePath);
		std::unordered_map<GLenum, std::string> Preprocess(const std::string& source);
		void Compile(std::unordered_map<GLenum, std::string>& shaderSources);
	private:
		uint32_t m_RendererID;
		std::string m_Name;
	};

}