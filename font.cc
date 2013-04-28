#include "atlas.hh"

#include <sstream>
#include <ft2build.h>
#include <freetype/freetype.h>
#include <freetype/ftimage.h>
#include "exceptions.hh"
#include "font.hh"

namespace glft {

FT_Library Font::library = 0;

Font::Font(const std::string& path, unsigned int size) : faceSize(size) {
	atlas = new Atlas(this);

	if (!library) FT_Init_FreeType(&library);

	int error = FT_New_Face(library, path.c_str(), 0, &face);
	if (error) throw FileNotFound(path);

	error = FT_Set_Char_Size(face, 0, size*16, 300, 300);

	if (error) throw InvalidArgument("FT_Set_Char_Size failed");
}

Font::~Font() {
	if (atlas) delete atlas;
}

unsigned int Font::size() const {
	return faceSize;
}

Font::CharInfo Font::getCharInfo(char qchar) {
	auto iter = cache.find(qchar);
	if (iter != cache.end()) return iter->second;
	Font::CharInfo info;

	int glyph_index = FT_Get_Char_Index(face, qchar);
	int error = FT_Load_Glyph(face, glyph_index, FT_LOAD_DEFAULT);
	if (error) throw InvalidArgument("FT_Load_Glyph failed");

	info.width = face->glyph->metrics.width/64;
	info.height = face->glyph->metrics.height/64;
	info.bearingX = face->glyph->metrics.horiBearingX/64;
	info.bearingY = face->glyph->metrics.horiBearingY/64;
	info.advance = face->glyph->metrics.horiAdvance/64;

	cache[qchar] = info;

	return info;
}

Font::BitmapInfo Font::getBitmapData(char qchar) {
	int error;
	int glyph_index = FT_Get_Char_Index(face, qchar);
	error = FT_Load_Glyph(face, glyph_index, FT_LOAD_DEFAULT);
	if (error) throw InvalidArgument("FT_Load_Glyph failed");

	error = FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL);
	if (error) throw InvalidArgument("FT_Render_Glyph");

	FT_Bitmap bmp = face->glyph->bitmap;

	int width = bmp.width;
	int height = bmp.rows;

	unsigned char* data = new unsigned char[width*height*4];
	memset(data, 0, width*height*4);
	for(int j = 0; j < height;j++) {
		for(int i = 0; i < width; i++){
			data[4*(i+j*width)  ] = data[4*(i+j*width)+1] =
			data[4*(i+j*width)+2] = data[4*(i+j*width)+3] = bmp.buffer[i + width*j];
		}
	}

	BitmapInfo bi;
	bi.data = data;
	bi.width = width;
	bi.height = height;
	return bi;
}

}
