#include "ShaderCompiler.h"
#include <regex>

using namespace CubicEngine;

ShaderCompileResult ShaderCompiler::Compile_csl(std::string code) {
	ShaderCompileResult compileResult;

	// (\$[a-zA-Z_][a-zA-Z0-9_]*)(?=\s)|(\S+)(?=\s|\n)|(\$[a-zA-Z_][a-zA-Z0-9_]*)(?=\n|\Z)
	std::regex shaderRegex(R"((\$[a-zA-Z_][a-zA-Z0-9_]*)(?=\s)|(\S+)(?=\s|\n)|(\$[a-zA-Z_][a-zA-Z0-9_]*)(?=\n|\Z))");

	std::smatch match;

	const int RECEIVING_COMMAND = 1;
	const int RECEIVING_PASS = 2;
	const int RECEIVED_PASS = 3;

	int receivingState = 0;
	int passIndex = 0;

	std::string temp;

	while (std::regex_search(code, match, shaderRegex)) {
		if (match.str() == "$pass") {
			receivingState = RECEIVING_PASS;
			continue;
		}

		if (match.str() == "$end") {
			if (receivingState == RECEIVED_PASS) {
				receivingState = 0;
				continue;
			}

			compileResult.error = true;
			return compileResult;
		}

		if (receivingState == RECEIVING_COMMAND) {
			compileResult.shaderCommands.push_back(std::make_pair(temp, match.str()));
			temp = "";
			receivingState = 0;
		}
		else if (receivingState == RECEIVING_PASS) {
			ShaderPassResult passResult = CompilePass(match.str());
			passResult.passIndex = passIndex;
			passIndex++;
			compileResult.passResults.push_back(passResult);
			receivingState = RECEIVED_PASS;
		}
		else {
			temp = match.str();
			receivingState = RECEIVING_COMMAND;
		}

		code = match.suffix().str();
	}

	return compileResult;
}

ShaderPassResult ShaderCompiler::CompilePass(std::string passCode) {
	ShaderPassResult passResult;

	std::regex shaderPassRegex(R"(@(?:fragment|vertex|geometry|compute)\n((?:.|\n)*?)(?=\n@|$))");

	std::smatch match;

	if (std::regex_match(passCode, match, shaderPassRegex)) {
		ShaderPassGLShader SPGLS;
		SPGLS.type = match[1].str();
		SPGLS.code = match[2].str();
		passResult.shaderPassGLShaders.push_back(SPGLS);
	}
	else {
		// TODO: throw error
		// "Error: Input does not match the expected shader pass format.\n";
	}

	return passResult;
}