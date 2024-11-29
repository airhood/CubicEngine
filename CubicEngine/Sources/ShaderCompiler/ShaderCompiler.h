#pragma once

#include <string>
#include <vector>

namespace CubicEngine {
	
	struct ShaderPassResult {
		std::string type;
		std::string code;
	};

	struct ShaderCompileResult {
		bool error = false;
		std::vector<std::pair<std::string, std::string>> shaderCommands;
		std::vector<ShaderPassResult> passResults;
	};

	class ShaderCompiler {
	public:
		ShaderCompileResult Compile_csl(std::string code);

	private:
		ShaderPassResult CompilePass(std::string passCode);
	};
}