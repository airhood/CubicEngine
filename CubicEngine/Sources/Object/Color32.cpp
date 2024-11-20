#include "Color32.h"

using namespace CubicEngine;

const Color32 Color32::Red(1.0f, 0.0f, 0.0f);
const Color32 Color32::Green(0.0f, 1.0f, 0.0f);
const Color32 Color32::Blue(0.0f, 0.0f, 1.0f);
const Color32 Color32::Black(0.0f, 0.0f, 0.0f);
const Color32 Color32::White(1.0f, 1.0f, 1.0f);
const Color32 Color32::Transparent(0.0f, 0.0f, 0.0f, 0.0f);

std::string Color32::toString() const {
	return std::string();
}