#include "color.h"

const Color Color::red = Color(1.0f, 0.0f, 0.0f);
const Color Color::green = Color(0.0f, 1.0f, 0.0f);
const Color Color::blue = Color(0.0f, 0.0f, 1.0f);
const Color Color::white = Color(1.0f, 1.0f, 1.0f);
const Color Color::orange = Color(1.0f, 0.5f, 0.0f);
const Color Color::yellow = Color(1.0f, 1.0f, 0.0f);
const Color Color::magenta = Color(1.0f, 0.0f, 1.0f);
const Color Color::cyan = Color(0.0f, 1.0f, 1.0f);
const Color Color::black = Color(0.0f, 0.0f, 0.0f);

//std::istream & operator>>(std::istream & stream, Color & color)
//{
//	std::string line;
//	std::getline(stream, line);
//
//	if (line.find("{") != std::string::npos)
//	{
//		std::string _r = line.substr(line.find("{") + 1, (line.find(",") - line.find("{")) - 1);
//		color.r = stof(_r);
//		line = line.substr(line.find(",") + 1, (line.find("}") - line.find(",")) - 1);
//		std::string _g = line.substr(0, line.find(",") - 1);
//		color.g = stof(_g);
//		std::string _b = line.substr(line.find(",") + 1, (line.find("}") - line.find(",")) - 1);
//		color.b = stof(_b);
//	}
//
//	return stream;
//}

Color::operator SDL_Color() const
{
	SDL_Color color;
	color.r = ConvertU8(0);
	color.g = ConvertU8(0);
	color.b = ConvertU8(0);
	color.a = 255;
	return color;
}
