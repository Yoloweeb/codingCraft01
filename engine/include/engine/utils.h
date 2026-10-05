#pragma once
#include "structs.h"
#include <vector>

namespace utils
{

	const float g_Pi{ 3.1415926535f };

#pragma region OpenGLDrawFunctionality

	// Colors: 
	// Color components are between 0.0f and 1.0f. The a (alpha) is optional. Example: SetColor(1.0f, 0.0f, 0.0f); // red
	void SetColor(float r, float g, float b, float a = 1);
	void SetColor(const Color4f& color);

	// Clears the screen using a defautl color.
	void ClearBackground();
	// Clears the screen using the specified RGB color
	void ClearBackground(float r, float g, float b);
	void ClearBackground(const Color4f& color);

	// Lines:
	void DrawLine(float x1, float y1, float x2, float y2, float lineWidth = 1.0f);
	void DrawLine(const Point2f& p1, const Point2f& p2, float lineWidth = 1.0f);

	// Triangles:
	void DrawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, float lineWidth = 1.0f);
	void DrawTriangle(const Point2f& p1, const Point2f& p2, const Point2f& p3, float lineWidth = 1);
	void FillTriangle(float x1, float y1, float x2, float y2, float x3, float y3);
	void FillTriangle(const Point2f& p1, const Point2f& p2, const Point2f& p3);

	// Rectangles:
	void DrawRect(float left, float top, float width, float height, float lineWidth = 1.0f);
	void DrawRect(const Point2f& topLeft, float width, float height, float lineWidth = 1.0f);
	void DrawRect(const Rectf& rect, float lineWidth = 1.0f);
	void FillRect(float left, float top, float width, float height);
	void FillRect(const Point2f& topLeft, float width, float height);
	void FillRect(const Rectf& rect);

	// Ellipses:
	void DrawEllipse(float centerX, float centerY, float radX, float radY, float lineWidth = 1.0f);
	void DrawEllipse(const Point2f& center, float radX, float radY, float lineWidth = 1.0f);
	void DrawEllipse(const Ellipsef& ellipse, float lineWidth = 1.0f);
	void FillEllipse(float centerX, float centerY, float radX, float radY);
	void FillEllipse(const Ellipsef& ellipse);
	void FillEllipse(const Point2f& center, float radX, float radY);

	// Arcs:
	// The angle parameters are in radians, not in degrees.
	void DrawArc(float centerX, float centerY, float radX, float radY, float fromAngle, float tillAngle, float lineWidth = 1.0f);
	// The angle parameters are in radians, not in degrees.
	void DrawArc(const Point2f& center, float radX, float radY, float fromAngle, float tillAngle, float lineWidth = 1.0f);
	// The angle parameters are in radians, not in degrees.
	void FillArc(float centerX, float centerY, float radX, float radY, float fromAngle, float tillAngle);
	// The angle parameters are in radians, not in degrees.
	void FillArc(const Point2f& center, float radX, float radY, float fromAngle, float tillAngle);

	//Polygons:
	// Draws a polygon. When closed is true, the last vertex is connected to the first.
	void DrawPolygon(const std::vector<Point2f>& vertices, bool closed = true, float lineWidth = 1.0f);
	// Draws a polygon. When closed is true, the last vertex is connected to the first.
	void DrawPolygon(const Point2f* pVertices, size_t nrVertices, bool closed = true, float lineWidth = 1.0f);
	void FillPolygon(const std::vector<Point2f>& vertices);
	void FillPolygon(const Point2f* pVertices, size_t nrVertices);

#pragma endregion OpenGLDrawFunctionality

#pragma region TextureFunctionality

	struct Texture
	{
		GLuint id;
		float width;
		float height;
	};


	/// <summary>
	/// Loads an image from Game/resources into a Texture.
	/// Call DeleteTexture when you no longer need it!
	/// </summary>
	/// <param name="path">
	/// Image filename, optionally including subfolders.
	/// Example: "player.png" or "Enemies/boss.png</param>
	/// <param name="texture">Texture that will receive the loaded image.</param>
	/// <returns>True if the texture was loaded successfully.</returns>
	bool TextureFromFile(const std::string& path, Texture& texture);

	/// <summary>
	/// Creates a texture containing the specified text using an existing font.
	/// Call DeleteTexture when you no longer need it!
	/// </summary>
	/// <param name="text">The text to convert into a texture.</param>
	/// <param name="pFont">The font used to render the text.</param>
	/// <param name="textColor">The color of the rendered text.</param>
	/// <param name="texture">The Texture object that will receive the generated text texture.</param>
	/// <returns>True if the texture was created successfully; otherwise false.</returns>
	bool TextureFromString(const std::string& text, TTF_Font* pFont, const Color4f& textColor, Texture& texture);

	/// <summary>
	/// Creates a texture containing the specified text using a font file from the Game/resources folder.
	/// Call DeleteTexture when you no longer need it!
	/// </summary>
	/// <param name="text">The text to convert into a texture.</param>
	/// <param name="fontPath">Font filename, optionally including subfolders.</param>
	/// <param name="ptSize">Font size in points.</param>
	/// <param name="textColor">The color of the rendered text.</param>
	/// <param name="texture">The Texture object that will receive the generated text texture.</param>
	/// <returns>True if the texture was created successfully; otherwise false.</returns>
	bool TextureFromString(const std::string& text, const std::string& fontPath, int ptSize, const Color4f& textColor, Texture& texture);

	/// <summary>
	/// Internal helper used by TextureFromFile and TextureFromString
	/// to convert an SDL_Surface into a Texture.
	/// </summary>
	void TextureFromSurface(const SDL_Surface* pSurface, Texture& textureData);

	/// <summary>
	/// Draws the texture at its original size with the given top-left position.
	/// Optionally, only a portion of the texture can be drawn by specifying a source rectangle.
	/// </summary>
	/// <param name="texture">The texture to draw.</param>
	/// <param name="dstTopLeft">Position (as a Point2f) where the texture will be drawn.</param>
	/// <param name="srcRect">
	/// Optional source rectangle defining which part of the texture to draw.
	/// Leave empty to draw the entire texture.
	/// </param>
	void DrawTexture(const Texture& texture, const Point2f& dstTopLeft, const Rectf& srcRect = {});

	/// <summary>
	/// Draws the texture inside the specified destination rectangle.
	/// The texture is stretched to fit the rectangle.
	/// Optionally, only a portion of the texture can be drawn by specifying a source rectangle.
	/// </summary>
	/// <param name="texture">The texture to draw.</param>
	/// <param name="dstTopLeft">Rectangle in which the texture will be drawn.</param>
	/// <param name="srcRect">
	/// Optional source rectangle defining which part of the texture to draw.
	/// Leave empty to draw the entire texture.
	/// </param>
	void DrawTexture(const Texture& texture, const Rectf& dstRect, const Rectf& srcRect = {});

	/// <summary>
	/// Releases the memory used by a texture.
	/// Call this once for every texture created with TextureFromFile or TextureFromString
	/// when you no longer need it, typically in the End() function.
	/// </summary>
	/// <param name="texture">The texture to delete from memory.</param>
	void DeleteTexture(Texture& texture);
#pragma endregion TextureFunctionality

#pragma region CollisionFunctionality

#pragma endregion CollisionFunctionality

}