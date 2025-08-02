#include "ShaderCompiler.h"
#include <regex>

using namespace CubicEngine;

std::string removeNulls(const std::string& input) {
	std::string result;
	result.reserve(input.size());

	for (char c : input) {
		if (c != '\0') {
			result.push_back(c);
		}
	}

	return result;
}

ShaderCompileResult ShaderCompiler::Compile_csl(std::string code) {
	ShaderCompileResult compileResult;

	// (\$[a-zA-Z_][a-zA-Z0-9_]*)(?=\s)|(\S+)(?=\s|\n)|(\$[a-zA-Z_][a-zA-Z0-9_]*)(?=\n|\Z)
	std::regex shaderRegex(R"((\$[a-zA-Z_][a-zA-Z0-9_]*)(?=\s|$)|(\S+)(?=\s|$))");


	std::smatch match;

	const int RECEIVING_COMMAND = 1;
	const int RECEIVING_PASS = 2;
	const int RECEIVED_PASS = 3;

	int receivingState = 0;
	int passIndex = 0;

	std::string temp;

	while (std::regex_search(code, match, shaderRegex)) {
		if (removeNulls(match.str()) == "$pass") {
			receivingState = RECEIVING_PASS;
			temp = match.suffix().str();
			code = match.suffix().str();
			continue;
		}

		if (removeNulls(match.str()) == "$end") {
			if (receivingState == RECEIVING_PASS) {
				std::regex re(R"(([\s\S]*?)(?=\$end))");
				std::smatch re_match;

				if (std::regex_search(temp, re_match, re)) {
					ShaderPassResult passResult = CompilePass(re_match[1].str());
					passResult.passIndex = passIndex;
					passIndex++;
					compileResult.passResults.push_back(passResult);
					temp = "";
					receivingState = 0;
					code = match.suffix().str();
					continue;
				}
				else {
					// TODO: Log error
				}
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

	while (!passCode.empty() && (passCode.front() == '\n' || passCode.front() == '\r')) {
		passCode.erase(passCode.begin());
	}

	std::regex shaderPassRegex(
		R"(@(vertex|fragment|geometry|compute)\r?\n([^@]*))",
		std::regex_constants::icase
	);

	auto begin = std::sregex_iterator(passCode.begin(), passCode.end(), shaderPassRegex);
	auto end = std::sregex_iterator();

	for (auto it = begin; it != end; ++it) {
		std::smatch match = *it;

		ShaderPassGLShader SPGLS;
		SPGLS.type = match[1].str();
		SPGLS.code = match[2].str();
		passResult.shaderPassGLShaders.push_back(SPGLS);
	}

	return passResult;
}