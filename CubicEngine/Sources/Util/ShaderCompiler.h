#pragma once

#include <string>
#include <vector>

namespace CubicEngine {

	struct ShaderPassGLShader {
		std::string type;
		std::string code;
	};
	
	struct ShaderPassResult {
		int passIndex;
		std::vector<ShaderPassGLShader> shaderPassGLShaders;
	};

	struct ShaderCompileResult {
		bool error = false;
		std::vector<std::pair<std::string, std::string>> shaderCommands;
		std::vector<ShaderPassResult> passResults;
	};

	class ShaderCompiler {
	public:
		static ShaderCompileResult Compile_csl(std::string code);

	private:
		static ShaderPassResult CompilePass(std::string passCode);
	};
}