#pragma once

#include <GL\glew.h>
#include <glm/glm.hpp>
#include <vector>

struct Position {
	float x;
	float y;
};
struct ColorRGBA8 {
	ColorRGBA8() : r(0), g(0), b(0), a(0) { }
	ColorRGBA8(GLubyte R, GLubyte G, GLubyte B, GLubyte A) :
		r(R), g(G), b(B), a(A) { }
	GLubyte r;
	GLubyte g;
	GLubyte b;
	GLubyte a;
};

struct UV {
	float u;
	float v;
};

//The vertex definition
struct Vertex {
	//This is the position struct. When you store a struct or class
	//inside of another struct or class, it is called composition. This is
	//layed out exactly the same in memory as if we had a float position[2],
	//but doing it this way makes more sense.
	Position position;

	//4 bytes for r g b a color.
	ColorRGBA8 color;

	//UV texture coordinates.
	UV uv;

	void setPosition(float x, float y) {
		position.x = x;
		position.y = y;
	}

	void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a) {
		color.r = r;
		color.g = g;
		color.b = b;
		color.a = a;
	}

	void setUV(float u, float v) {
		uv.u = u;
		uv.v = v;
	}
};

enum class GlyphSortType {
	NONE,
	FRONT_TO_BACK,
	BACK_TO_FRONT,
	TEXTURE
};

// A glyph is a single quad. These are added via SpriteBatch::draw
class Glyph {
public:
	Glyph() {};
	Glyph(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint Texture, float Depth, const ColorRGBA8& color);
	Glyph(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint Texture, float Depth, const ColorRGBA8& color, float angle);

	GLuint texture;
	float depth;

	Vertex topLeft;
	Vertex bottomLeft;
	Vertex topRight;
	Vertex bottomRight;
private:
	// Rotates a point about (0,0) by angle
	glm::vec2 rotatePoint(const glm::vec2& pos, float angle);
};

// Each render batch is used for a single draw call
class RenderBatch {
public:
	RenderBatch(GLuint Offset, GLuint NumVertices, GLuint Texture) : offset(Offset),
		numVertices(NumVertices), texture(Texture) {
	}
	GLuint offset;
	GLuint numVertices;
	GLuint texture;
};

class SpriteBatch
{
public:
	SpriteBatch();
	~SpriteBatch();

	// Initializes the spritebatch
	void init(GLuint vao, GLuint vbo);
	void dispose();

	// Begins the spritebatch
	void begin(GlyphSortType sortType = GlyphSortType::TEXTURE);

	// Ends the spritebatch
	void end();

	// Adds a glyph to the spritebatch
	void draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const ColorRGBA8& color);
	// Adds a glyph to the spritebatch with rotation
	void draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const ColorRGBA8& color, float angle);
	// Adds a glyph to the spritebatch with rotation
	void draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const ColorRGBA8& color, const glm::vec2& dir);

	// Renders the entire SpriteBatch to the screen
	void renderBatch();

private:
	// Creates all the needed RenderBatches
	void createRenderBatches();

	// Generates our VAO and VBO
	void createVertexArray(GLuint vao, GLuint vbo);

	// Sorts glyphs according to _sortType
	void sortGlyphs();

	// Comparators used by sortGlyphs()
	static bool compareFrontToBack(Glyph* a, Glyph* b);
	static bool compareBackToFront(Glyph* a, Glyph* b);
	static bool compareTexture(Glyph* a, Glyph* b);

	GLuint _vbo;
	GLuint _vao;

	GlyphSortType _sortType;

	std::vector<Glyph*> _glyphPointers; ///< This is for sorting
	std::vector<Glyph> _glyphs; ///< These are the actual glyphs
	std::vector<RenderBatch> _renderBatches;
};
