#pragma once

#include  "IRender2d.h"
#include <stb_truetype.h>
#include <glm/glm.hpp>

#define codePointOfFirstChar  32   // ASCII of ' '(Space)
#define charsToIncludeInFontAtlas  95 // Include 95 charecters

class Font
{

public:

	

	unsigned int m_atlas;

	stbtt_pack_context ctx;
	stbtt_packedchar packedChars[charsToIncludeInFontAtlas];
	stbtt_aligned_quad alignedQuads[charsToIncludeInFontAtlas];

	Font(IRender2d* r, std::string fileName);

	void getVerticesOfChar(char ch, float size, float* posX, float posy, glm::vec2* vPos, glm::vec2* texCoords);

};