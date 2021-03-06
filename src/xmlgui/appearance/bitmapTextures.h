/**     ___           ___           ___                         ___           ___     
 *     /__/\         /  /\         /  /\         _____         /  /\         /__/|    
 *    |  |::\       /  /::\       /  /::|       /  /::\       /  /::\       |  |:|    
 *    |  |:|:\     /  /:/\:\     /  /:/:|      /  /:/\:\     /  /:/\:\      |  |:|    
 *  __|__|:|\:\   /  /:/~/::\   /  /:/|:|__   /  /:/~/::\   /  /:/  \:\   __|__|:|    
 * /__/::::| \:\ /__/:/ /:/\:\ /__/:/ |:| /\ /__/:/ /:/\:| /__/:/ \__\:\ /__/::::\____
 * \  \:\~~\__\/ \  \:\/:/__\/ \__\/  |:|/:/ \  \:\/:/~/:/ \  \:\ /  /:/    ~\~~\::::/
 *  \  \:\        \  \::/          |  |:/:/   \  \::/ /:/   \  \:\  /:/      |~~|:|~~ 
 *   \  \:\        \  \:\          |  |::/     \  \:\/:/     \  \:\/:/       |  |:|   
 *    \  \:\        \  \:\         |  |:/       \  \::/       \  \::/        |  |:|   
 *     \__\/         \__\/         |__|/         \__\/         \__\/         |__|/   
 *
 *  Description: 
 *				 
 *  bitmapTextures.h, created by Marek Bereza on 10/01/2014.
 */





class BitmapTexRect {
public:
	BitmapTexRect() {
		hasBeenSetup = false;
	}
	
    glm::vec3 vec2vec3(const ofVec2f &a) {
        return glm::vec3(a.x, a.y, 0);
    }
	void draw(const ofRectangle &r) {
		if(!hasBeenSetup) {
			setup();
		}
		
		vbo.clear();
		
        vector<glm::vec3> &v = vbo.getVertices();
		vector<glm::vec2> &tc = vbo.getTexCoords();
        
		
		while(v.size()<4) v.push_back(ofVec3f());
		while(tc.size()<4) tc.push_back(ofVec2f());
		
        tc[0] = glm::vec2(r.getTopLeft()*texScale);
		v[0] = vec2vec3(r.getTopLeft());
		
		tc[1] = glm::vec2(r.getTopRight()*texScale);
		v[1] = vec2vec3(r.getTopRight());
		
		tc[3] = glm::vec2(r.getBottomRight()*texScale);
		v[3] = vec2vec3(r.getBottomRight());
		
		tc[2] = glm::vec2(r.getBottomLeft()*texScale);
		v[2] = vec2vec3(r.getBottomLeft());
		
		
		tex.bind();
		vbo.draw();
		tex.unbind();
	}
	virtual unsigned char *getBitmap() = 0;
	
	// must be power-of-2
	virtual int getSize() = 0;
	
	
private:
	bool hasBeenSetup;
	ofTexture tex;
	ofVboMesh vbo;
	float texScale;
	
	void setup() {
		vbo.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
		texScale = 1.f/getSize();
		ofDisableArbTex();
		tex.loadData(getBitmap(), getSize(), getSize(), GL_LUMINANCE);
		tex.setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
		tex.setTextureWrap(GL_REPEAT, GL_REPEAT);
		ofEnableArbTex();
		hasBeenSetup = true;
	}
};





class StripeyRect: public BitmapTexRect {
public:
	
	unsigned char blackLevel;
	unsigned char whiteLevel;
	unsigned char *bitmap;
	int dims;
	StripeyRect(int dims, unsigned char blackLevel, unsigned char whiteLevel) {
		this->dims = dims;
		this->blackLevel = blackLevel;
		this->whiteLevel = whiteLevel;
		bitmap = new unsigned char[dims*dims];
		memset(bitmap, blackLevel, dims*dims);
		for(int i = 0; i < dims; i++) {
			bitmap[i*dims + (dims - i - 1)] = whiteLevel;
		}
	}
	unsigned char *getBitmap() {
		return bitmap;
	}
	int getSize() {
		return dims;
	}
};


class HorizontalLinesRect: public BitmapTexRect {
public:
	unsigned char *getBitmap() {
		static unsigned char pix [16] = {
			0xff, 0xff, 0xff, 0xff,
			0x00, 0x00, 0x00, 0x00,
			0xff, 0xff, 0xff, 0xff,
			0x00, 0x00, 0x00, 0x00
		};
		return pix;
	}
	int getSize() {
		return 4;
	}
};

class VerticalLinesRect: public BitmapTexRect {
public:
	unsigned char blackLevel;
	unsigned char whiteLevel;
	unsigned char *bitmap;

	VerticalLinesRect(unsigned char blackLevel, unsigned char whiteLevel) {
		bitmap = new unsigned char[4];
		bitmap[0] = bitmap[2] = blackLevel;
		bitmap[1] = bitmap[3] = whiteLevel;
		
	}
	
	unsigned char *getBitmap() {
		return bitmap;
	}
	
	int getSize() {
		return 2;
	}
};







