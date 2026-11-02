#include "Font.h"

#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"

#include <iostream>
#include <fstream>
#include <vector>

Font::Font(IRender2d* r, std::string fileName)
{
	std::string path("F:\\Users\\asdf\\Desktop\\fonts\\ttf\\");
	path.append(fileName);

	std::ifstream font_file(path, std::ios::binary | std::ios::ate);

	if (!font_file.is_open()) {
		std::cerr << "Nem sikerült megnyitni a fájlt!" << std::endl;
		
	}

	std::streamsize size = font_file.tellg();
	std::vector<unsigned char> font_buffer(size);

	
	font_file.seekg(0, std::ios::beg);
	if (!font_file.read(reinterpret_cast<char*>(font_buffer.data()), size)) {
		std::cerr << "Hiba történt a beolvasás során!" << std::endl;
	}
	font_file.close();


	stbtt_fontinfo font;
	if (!stbtt_InitFont(&font, font_buffer.data(), stbtt_GetFontOffsetForIndex(font_buffer.data(), 0))) {
		std::cerr << "Nem sikerült inicializálni a betûtípust!" << std::endl;
		
	}

	const int atlas_width = 512;
	const int atlas_height = 512;
	const float font_size = 32.0f;

	std::vector<unsigned char> atlas_pixels(atlas_width * atlas_height, 0);
	

	if (!stbtt_PackBegin(&ctx, atlas_pixels.data(), atlas_width, atlas_height, 0, 1, nullptr)) {
		std::cerr << "Nem sikerült elindítani a packert!" << std::endl;
		
	}
	stbtt_PackSetOversampling(&ctx, 2, 2);

	if (!stbtt_PackFontRange(&ctx, font_buffer.data(), 0, font_size, 32, 95, packedChars)) {
		std::cerr << "Nem fértek el a betûk az atlaszban! Növeld meg a textúra méretét." << std::endl;
		stbtt_PackEnd(&ctx);
		
	}

	stbtt_PackEnd(&ctx);
	std::vector<unsigned char> atlas(512 * 512 * 4);

	int pointer = 0;
	for (unsigned char c : atlas_pixels)
	{
		atlas[pointer++] = 255;
		atlas[pointer++] = 255;
		atlas[pointer++] = 255;
		atlas[pointer++] = c;
	}

	m_atlas = r->loadImage(atlas.data(), atlas_width, atlas_height, 4);

	for (int i = 0; i < charsToIncludeInFontAtlas; i++)
	{
		float unusedX, unusedY;

		stbtt_GetPackedQuad(
			packedChars,              // Array of stbtt_packedchar
			512,                      // Width of the font atlas texture
			512,                     // Height of the font atlas texture
			i,                                   // Index of the glyph
			&unusedX, &unusedY,                  // current position of the glyph in screen pixel coordinates, (not required as we have a different corrdinate system)
			&alignedQuads[i],                    // stbtt_alligned_quad struct. (this struct mainly consists of the texture coordinates)
			0                                    // Allign X and Y position to a integer (doesn't matter because we are not using 'unusedX' and 'unusedY')
		);
	}
}

void Font::getVerticesOfChar(char ch, float size, float* posX, float posY, glm::vec2* vPos, glm::vec2* texCoords)
{
	float pixelScale = 1;
	

	stbtt_packedchar* packedChar = &packedChars[ch - codePointOfFirstChar];
	stbtt_aligned_quad* alignedQuad = &alignedQuads[ch - codePointOfFirstChar];

	

	glm::vec2 glyphSize =
	{
		(packedChar->x1 - packedChar->x0) * pixelScale * size,
		(packedChar->y1 - packedChar->y0) * pixelScale * size 
	};

	glm::vec2 glyphBoundingBoxBottomLeft(*posX + (packedChar->xoff * pixelScale * size),
		posY + (packedChar->yoff) * pixelScale * size);
	

	// The order of vertices of a quad goes top-right, top-left, bottom-left, bottom-right
	glm::vec2 glyphVertices[4] =
	{
		{ glyphBoundingBoxBottomLeft.x + glyphSize.x, glyphBoundingBoxBottomLeft.y + glyphSize.y },
		{ glyphBoundingBoxBottomLeft.x, glyphBoundingBoxBottomLeft.y + glyphSize.y },
		{ glyphBoundingBoxBottomLeft.x, glyphBoundingBoxBottomLeft.y },
		{ glyphBoundingBoxBottomLeft.x + glyphSize.x, glyphBoundingBoxBottomLeft.y },
	};

	glm::vec2 glyphTextureCoords[4] =
	{
		{ alignedQuad->s1, alignedQuad->t1 },
		{ alignedQuad->s0, alignedQuad->t1 },
		{ alignedQuad->s0, alignedQuad->t0 },
		{ alignedQuad->s1, alignedQuad->t0 },
	};

	memcpy(vPos, glyphVertices, sizeof(glm::vec2) * 4);
	memcpy(texCoords, glyphTextureCoords, sizeof(glm::vec2) * 4);

	*posX += packedChar->xadvance * pixelScale * size + 12 ;
	
}
