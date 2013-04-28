#ifndef _GLFT_FONT_HH_
#define _GLFT_FONT_HH_

#include <unordered_map>

struct FT_LibraryRec_;
struct FT_FaceRec_;
typedef FT_LibraryRec_* FT_Library;
typedef FT_FaceRec_* FT_Face;
namespace glft {
class Atlas;
/**
 * @brief represents a FreeType font
 * @author amro
 * This class handles loading and rendering a FreeType font
 */
class GLFT_EXPORT Font {
public:
	Font() : atlas(nullptr) {}
	Font(const std::string& path, unsigned int size);
	~Font();
	
	struct BitmapInfo {
		unsigned char* data;
		int width;
		int height;
	};
	
	struct CharInfo {
		float width;
		float height;
		float bearingX;
		float bearingY;
		float advance;
		float *vertexData;
	};
	
	BitmapInfo getBitmapData(char qchar);
	
	CharInfo getCharInfo(char qchar);
	
	Atlas* getAtlas() { return atlas; }
	
	unsigned int size() const;
	
	std::unordered_map<char, CharInfo> cache;
private:
	unsigned int faceSize;
	Atlas* atlas;
	
	static FT_Library library;
	
	FT_Face face;
};
}
#endif
