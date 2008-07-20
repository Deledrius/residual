/* Residual - Virtual machine to run LucasArts' 3D adventure games
 *
 * Residual is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the AUTHORS
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * $URL$
 * $Id$
 *
 */

#if !defined(BACKEND_SAVES_DEFAULT_H) && !defined(DISABLE_DEFAULT_SAVEFILEMANAGER)
#define BACKEND_SAVES_DEFAULT_H

#include "common/savefile.h"
#include "common/str.h"

/**
 * Provides a default savefile manager implementation for common platforms.
 */
class DefaultSaveFileManager : public Common::SaveFileManager {
public:
	virtual Common::StringList listSavefiles(const char *pattern);
	virtual Common::InSaveFile *openForLoading(const char *filename);
	virtual Common::OutSaveFile *openForSaving(const char *filename);
	virtual bool removeSavefile(const char *filename);

protected:
	/**
	 * Get the path to the savegame directory.
	 * Should only be used internally since some platforms
	 * might implement savefiles in a completely different way.
	 */
	virtual Common::String getSavePath() const;

	/**
	 * Checks the given path for read access, existence, etc.
	 * Sets the internal error and error message accordingly.
	 */
	void checkPath(const Common::String &path);
};

#endif