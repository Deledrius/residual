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

#ifndef GRIM_PRIMITIVESOBJECT_H
#define GRIM_PRIMITIVESOBJECT_H

#include "common/rect.h"

#include "engines/grim/pool.h"

namespace Grim {

class SaveGame;
class Bitmap;
class PoolColor;

class PrimitiveObject : public PoolObject<PrimitiveObject, MKTAG('P', 'R', 'I', 'M')> {
public:
	PrimitiveObject();
	~PrimitiveObject();

	typedef enum {
		RECTANGLE = 1,
		BITMAP,
		LINE,
		POLYGON
	} PrimType;

	void createRectangle(Common::Point p1, Common::Point p2, PoolColor *color, bool filled);
	void createBitmap(Bitmap *bitmap, Common::Point p, bool transparent);
	void createLine(Common::Point p1, Common::Point p2, PoolColor *color);
	void createPolygon(Common::Point p1, Common::Point p2, Common::Point p3, Common::Point p4, PoolColor *color);
	Common::Point getP1() { return _p1; }
	Common::Point getP2() { return _p2; }
	Common::Point getP3() { return _p3; }
	Common::Point getP4() { return _p4; }
	void setPos(int x, int y);
	void setColor(PoolColor *color) { _color = color; }
	PoolColor *getColor() { return _color; }
	bool isFilled() { return _filled; }
	void draw();
	bool isBitmap() { return _type == BITMAP; }
	Bitmap *getBitmapHandle() { assert(_bitmap); return _bitmap; }
	void saveState(SaveGame *state) const;
    bool restoreState(SaveGame *state);

private:
	Common::Point _p1, _p2, _p3, _p4;
	PoolColor *_color;
	bool _filled;
	int _type;
	Bitmap *_bitmap;

	friend class GrimEngine;
};

} // end of namespace Grim

#endif
