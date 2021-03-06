/* Residual - A 3D game interpreter
 *
 * Residual is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.

 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
 *
 */

#ifndef GRIM_GFX_BASE_H
#define GRIM_GFX_BASE_H

#include "math/vector3d.h"

namespace Graphics {
	struct Surface;
}

namespace Grim {

struct Shadow;
class SaveGame;
class BitmapData;
class Bitmap;
class CMap;
class Color;
class PrimitiveObject;
class Font;
class TextObject;
class Material;
class ModelNode;
class Mesh;
class MeshFace;
struct Sprite;
class Light;
class Texture;

/**
 * The Color-formats used for bitmaps in Grim Fandango/Escape From Monkey Island
 */
enum colorFormat {
	BM_RGB565 = 1,    // Grim Fandango
	BM_RGB1555 = 2,   // EMI-PS2
	BM_RGBA = 3      // EMI-PC
};
class GfxBase {
public:
	GfxBase();
	virtual ~GfxBase() { ; }

	/**
	 * Creates a render-context.
	 *
	 * @param screenW		the width of the context
	 * @param screenH		the height of the context
	 * @param fullscreen	true if fullscreen is desired, false otherwise.
	 */
	virtual byte *setupScreen(int screenW, int screenH, bool fullscreen) = 0;

	/**
	 *	Query whether the current context is hardware-accelerated
	 *
	 * @return true if hw-accelerated, false otherwise
	 */
	virtual bool isHardwareAccelerated() = 0;

	virtual void setupCamera(float fov, float nclip, float fclip, float roll) = 0;
	virtual void positionCamera(Math::Vector3d pos, Math::Vector3d interest) = 0;

	virtual void clearScreen() = 0;

	/**
	 *	Swap the buffers, making the drawn screen visible
	 */
	virtual void flipBuffer() = 0;

	virtual void getBoundingBoxPos(const Mesh *mesh, int *x1, int *y1, int *x2, int *y2) = 0;
	virtual void startActorDraw(Math::Vector3d pos, float scale, const Math::Angle &yaw,
								const Math::Angle &pitch, const Math::Angle &roll) = 0;
	virtual void finishActorDraw() = 0;
	virtual void setShadow(Shadow *shadow) = 0;
	virtual void drawShadowPlanes() = 0;
	virtual void setShadowMode() = 0;
	virtual void clearShadowMode() = 0;
	virtual void setShadowColor(byte r, byte g, byte b) = 0;
	virtual void getShadowColor(byte *r, byte *g, byte *b) = 0;

	virtual void set3DMode() = 0;

	virtual void translateViewpointStart(Math::Vector3d pos, const Math::Angle &pitch,
										 const Math::Angle &yaw, const Math::Angle &roll) = 0;
	virtual void translateViewpointFinish() = 0;

	virtual void drawHierachyNode(const ModelNode *node, int *x1, int *y1, int *x2, int *y2) = 0;
	virtual void drawModelFace(const MeshFace *face, float *vertices, float *vertNormals, float *textureVerts) = 0;
	virtual void drawSprite(const Sprite *sprite) = 0;

	virtual void enableLights() = 0;
	virtual void disableLights() = 0;
	virtual void setupLight(Light *light, int lightId) = 0;

	virtual void createMaterial(Texture *material, const char *data, const CMap *cmap) = 0;
	virtual void selectMaterial(const Texture *material) = 0;
	virtual void destroyMaterial(Texture *material) = 0;

	/**
	 * Prepares a bitmap for drawing
	 * performs any format conversions needed for the renderer,
	 * and might create an internal representation of the bitmap
	 * external changes to the bitmap may not be visible after this
	 * is called. Must be called before drawBitmap can be used.
	 *
	 * the external bitmap might have its data changed by this function,
	 *
	 * @param bitmap	the bitmap to be prepared
	 * @see destroyBitmap
	 * @see drawBitmap
	 */
	virtual void createBitmap(BitmapData *bitmap) = 0;

	/**
	 * Draws a bitmap
	 * before this is safe to use, createBitmap MUST have been called
	 *
	 * @param bitmap	the bitmap to be drawn
	 * @see createBitmap
	 * @see destroyBitmap
	 */
	virtual void drawBitmap(const Bitmap *bitmap) = 0;

	/**
	 * Deletes any internal references and representations of a bitmap
	 * after this is called, it is safe to dispose of or change the external
	 * bitmapdata.
	 *
	 * @param bitmap	the bitmap to be destroyed
	 * @see createBitmap
	 * @see drawBitmap
	 */
	virtual void destroyBitmap(BitmapData *bitmap) = 0;

	virtual void createFont(Font *font) = 0;
	virtual void destroyFont(Font *font) = 0;

	virtual void createTextObject(TextObject *text) = 0;
	virtual void drawTextObject(TextObject *text) = 0;
	virtual void destroyTextObject(TextObject *text) = 0;

	virtual Bitmap *getScreenshot(int w, int h) = 0;
	virtual void storeDisplay() = 0;
	virtual void copyStoredToDisplay() = 0;

	/**
	 * Dims the entire screen
	 * Sets the entire screen to 10% of its current brightness,
	 * and converts it to grayscale.
	 */
	virtual void dimScreen() = 0;
	virtual void dimRegion(int x, int y, int w, int h, float level) = 0;

	/**
	 * Draw a completely opaque Iris around the specified rectangle.
	 * the arguments specify the distance from the screen-edge to the first
	 * non-iris pixel.
	 *
	 * @param x		the width of the Iris
	 * @param y		the height of the Iris
	 */
	virtual void irisAroundRegion(int x1, int y1, int x2, int y2) = 0;

	virtual void drawEmergString(int x, int y, const char *text, const Color &fgColor) = 0;
	virtual void loadEmergFont() = 0;

	virtual void drawRectangle(PrimitiveObject *primitive) = 0;
	virtual void drawLine(PrimitiveObject *primitive) = 0;
	virtual void drawPolygon(PrimitiveObject *primitive) = 0;

	/**
	 * Prepare a movie-frame for drawing
	 * performing any necessary conversion
	 *
	 * @param width			the width of the movie-frame.
	 * @param height		the height of the movie-frame.
	 * @param bitmap		a pointer to the data for the movie-frame.
	 * @see drawMovieFrame
	 * @see releaseMovieFrame
	 */
	virtual void prepareMovieFrame(Graphics::Surface* frame) = 0;
	virtual void drawMovieFrame(int offsetX, int offsetY) = 0;

	/**
	 * Release the currently prepared movie-frame, if one exists.
	 *
	 * @see drawMovieFrame
	 * @see prepareMovieFrame
	 */
	virtual void releaseMovieFrame() = 0;

	virtual const char *getVideoDeviceName() = 0;

	virtual void saveState(SaveGame *state);
	virtual void restoreState(SaveGame *state);

	void renderBitmaps(bool render);
	void renderZBitmaps(bool render);

protected:
	int _screenWidth, _screenHeight, _screenBPP;
	bool _isFullscreen;
	Shadow *_currentShadowArray;
	unsigned char _shadowColorR;
	unsigned char _shadowColorG;
	unsigned char _shadowColorB;
	bool _renderBitmaps;
	bool _renderZBitmaps;
};

// Factory-like functions:

GfxBase *CreateGfxOpenGL();
GfxBase *CreateGfxTinyGL();

extern GfxBase *g_driver;

} // end of namespace Grim

#endif
