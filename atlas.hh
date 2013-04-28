#ifndef _GLFT_ATLAS_HH_
#define _GLFT_ATLAS_HH_

#include <string>
#include <map>

#include "font.hh"
#include "binpacker.hh"

namespace glft {
///font atlas used to cache font textures
class GLFT_EXPORT Atlas {
public:
	Atlas(Font* font);
	~Atlas();
	
	float* getVertexData(const std::string& text);
	
	unsigned int getTexture() { return texture; };
	
	const Font::CharInfo& getCharInfo(char chr);
private:
	BinPacker packer;
	unsigned int texture;
	Font* font;
	
	typedef std::map<char, Font::CharInfo> InfoMap;
	InfoMap infoMap;
	
	void cacheChar(char chr);
};
}

#endif
