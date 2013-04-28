
#include "atlas.hh"

#ifndef UNIX
#include <windows.h>
#endif

#include <cstring>

#include <GL/gl.h>

namespace glft {

Atlas::Atlas(Font* font) : font(font) {
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 2048, 2048, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
}

Atlas::~Atlas() {
	glDeleteTextures(1, &texture);
}

float* Atlas::getVertexData(const std::string& text) {
	float* vdata = new float[text.size()*4*4];
	float xoffset = 0;
	for (unsigned int i = 0; i < text.size(); i++) {
		const Font::CharInfo& info = getCharInfo(text[i]);
		for (int j = 0; j < 4; j++) {
			vdata[(j*4)+(i*16)  ] = xoffset + info.vertexData[(j*4)];
			vdata[(j*4)+(i*16)+1] = info.vertexData[(j*4)+1];
			vdata[(j*4)+(i*16)+2] = info.vertexData[(j*4)+2];
			vdata[(j*4)+(i*16)+3] = info.vertexData[(j*4)+3];
		}
		xoffset += info.advance;
	}
	return vdata;
}

const Font::CharInfo& Atlas::getCharInfo(char chr) {
	InfoMap::const_iterator iterator = infoMap.find(chr);
	if (iterator != infoMap.end()) return iterator->second;
	cacheChar(chr);
	return infoMap[chr];
}

void Atlas::cacheChar(char chr) {
	Font::CharInfo info;
	Font::BitmapInfo bi = font->getBitmapData(chr);
	BinPacker::Node* node = packer.insert(bi.width, bi.height);
	
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexSubImage2D(GL_TEXTURE_2D, 0, node->x, node->y, node->width, node->width, GL_RGBA, GL_UNSIGNED_BYTE, bi.data);
	
	info = font->getCharInfo(chr);
	info.vertexData = new float[4*4];
	
	float data[] = {
		info.bearingX+info.width, info.bearingY               , (node->x+node->width)/2048.0f, node->y/2048.0f,
		info.bearingX           , info.bearingY               , node->x/2048.0f              , node->y/2048.0f,
		info.bearingX           , -(info.height-info.bearingY), node->x/2048.0f              , (node->y+node->height)/2048.0f,
		info.bearingX+info.width, -(info.height-info.bearingY), (node->x+node->width)/2048.0f, (node->y+node->height)/2048.0f
	};
	
	memcpy(info.vertexData, data, sizeof(float)*4*4);
	
	infoMap[chr] = info;
	
	delete[] bi.data;
}

}
