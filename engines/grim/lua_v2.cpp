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

#define FORBIDDEN_SYMBOL_EXCEPTION_chdir
#define FORBIDDEN_SYMBOL_EXCEPTION_getcwd
#define FORBIDDEN_SYMBOL_EXCEPTION_unlink
#define FORBIDDEN_SYMBOL_EXCEPTION_getwd
#define FORBIDDEN_SYMBOL_EXCEPTION_mkdir

#include "common/endian.h"

#include "engines/grim/lua.h"
#include "engines/grim/lua/luadebug.h"
#include "engines/grim/lua/lauxlib.h"

#include "engines/grim/grim.h"
#include "engines/grim/actor.h"
#include "engines/grim/lipsync.h"
#include "engines/grim/costume.h"

#include "engines/grim/movie/movie.h"

namespace Grim {

static void L2_UndimAll() {
	warning("L2_UndimAll: stub");
}

static void L2_SetActorLocalAlpha() {
	lua_Object actorObj = lua_getparam(1);

	if (!lua_isuserdata(actorObj) || lua_tag(actorObj) != MKTAG('A','C','T','R'))
		return;

	Actor *actor = getactor(actorObj);
	if (!actor)
		return;

	// FIXME: implement missing code
	warning("L2_SetActorLocalAlpha: stub, actor: %s", actor->getName().c_str());
}

static void L2_UndimRegion() {
	lua_Object regionObj = lua_getparam(1);

	if (lua_isnumber(regionObj)) {
		int region = (int)lua_getnumber(regionObj);
		// FIXME func(region);
		warning("L2_UndimRegion: region: %d", region);
	} else {
		lua_pushnil();
	}
}

static void L2_SleepFor() {
	lua_Object msObj = lua_getparam(1);

	if (lua_isnumber(msObj)) {
		int ms = (int)lua_getnumber(msObj);
		// FIXME func(ms);
		warning("L2_SleepFor: ms: %d", ms);
	}
}

static void L2_DimScreen() {
	lua_Object dimObj = lua_getparam(1);
	float dim = 0.6999f;

	if (lua_isnumber(dimObj))
		dim = lua_getnumber(dimObj);

	// FIXME func(dim);
	warning("L2_DimScreen: dim: %f", dim);
}

static void L2_MakeCurrentSetup() {
	lua_Object setupObj = lua_getparam(1);
	if (lua_isnumber(setupObj)) {
		int num = (int)lua_getnumber(setupObj);
		g_grim->makeCurrentSetup(num);
	} else if (lua_isstring(setupObj)) {
		const char *setupName = lua_getstring(setupObj);
		error("L2_MakeCurrentSetup: Not implemented case: setup: %s", setupName);
	}
}

static void L2_SetActorGlobalAlpha() {
	lua_Object actorObj = lua_getparam(1);
//	lua_Object alphaModeObj = lua_getparam(2);
//	lua_Object valueObj = lua_getparam(3);

	if (!lua_isuserdata(actorObj) || lua_tag(actorObj) != MKTAG('A','C','T','R'))
		return;

	Actor *actor = getactor(actorObj);
	if (!actor)
		return;

	warning("L2_SetActorGlobalAlpha: actor: %s", actor->getName().c_str());

	/* Only when actor has primitives
	if (!actor->primities)
			return;
	if (lua_isnumber(alphaModeObj) {
		int alphaMode = (int)lua_getnumber(alphaModeObj);
		if (!lua_isnil(valueObj) && lua_isstring(valueObj)) {
				// TODO: missing part
		}
		// TODO
	}
	*/
}

static void L2_ImGetMillisecondPosition() {
	lua_Object soundObj = lua_getparam(1);

	if (lua_isnumber(soundObj)) {
		int sound = (int)lua_getnumber(soundObj);
		// FIXME int ms = func(sound);
		// lua_pushnumber(ms);
		// push -1 for now
		warning("L2_ImGetMillisecondPosition: sound: %d", sound);
		lua_pushnumber(-1);
	}
}

static void L2_RemoveActorFromOverworld() {
	lua_Object actorObj = lua_getparam(1);

	if (!lua_isuserdata(actorObj) || lua_tag(actorObj) != MKTAG('A','C','T','R'))
		return;

	Actor *actor = getactor(actorObj);
	if (!actor)
		return;

	warning("L2_RemoveActorFromOverworld: actor: %s", actor->getName().c_str());
	// FIXME actor->func();
}

static void L2_UnloadActor() {
	lua_Object actorObj = lua_getparam(1);

	if (!lua_isuserdata(actorObj) || lua_tag(actorObj) != MKTAG('A','C','T','R'))
		return;

	Actor *actor = getactor(actorObj);
	if (!actor)
		return;

	warning("L2_UnloadActor: actor: %s", actor->getName().c_str());
	// FIXME actor->func();
}

static void L2_SetActorWalkRate() {
	lua_Object actorObj = lua_getparam(1);
	lua_Object rateObj = lua_getparam(2);

	if (!lua_isuserdata(actorObj) || lua_tag(actorObj) != MKTAG('A','C','T','R'))
		return;
	if (!lua_isnumber(rateObj))
		return;

	Actor *actor = getactor(actorObj);
	float rate = lua_getnumber(rateObj);
	// const below only differ from grim
	actor->setWalkRate(rate * 3.279999971389771);
}

void L2_GetActorWalkRate() {
	lua_Object actorObj = lua_getparam(1);
	if (!lua_isuserdata(actorObj) || lua_tag(actorObj) != MKTAG('A','C','T','R'))
		return;

	Actor *actor = getactor(actorObj);
	// const below only differ from grim
	lua_pushnumber(actor->getWalkRate() * 0.3048780560493469);
}

static void L2_SetReverb() {
	lua_Object eaxObj = lua_getparam(1);
	lua_Object decayObj = lua_getparam(2);
	lua_Object mixObj = lua_getparam(3);
	lua_Object predelayObj = lua_getparam(4);
	lua_Object dampingObj = lua_getparam(5);

	if (!lua_isnumber(eaxObj))
		return;

	int eax = (int)lua_getnumber(eaxObj);
	int param = 0;
	float decay = -1;
	float mix = -1;
	float predelay = -1;
	float damping = -1;

	if (eax == 60) {
		param = 26;
	} else if (eax == 70) {
		param = 27;
	} else if (eax >= 0 && eax <= 25) {
		param = eax;
		// there is some table, initialy is like eax
	} else {
		return;
	}

	if (lua_isnumber(decayObj))
		decay = lua_getnumber(decayObj);
	if (lua_isnumber(mixObj))
		mix = lua_getnumber(mixObj);
	if (lua_isnumber(predelayObj))
		predelay = lua_getnumber(predelayObj);
	if (lua_isnumber(dampingObj))
		damping = lua_getnumber(dampingObj);

	warning("L2_SetReverb, eax: %d, decay: %f, mix: %f, predelay: %f, damping: %f", param, decay, mix, predelay, damping);
	// FIXME: func(param, decay, mix, predelay, damping);
}

static void L2_LockBackground() {
	lua_Object filenameObj = lua_getparam(1);

	if (!lua_isstring(filenameObj)) {
		lua_pushnil();
		return;
	}
	const char *filename = lua_getstring(filenameObj);
	warning("L2_LockBackground, filename: %s", filename);
	// FIXME: implement missing rest part of code
}

static void L2_UnLockBackground() {
	lua_Object filenameObj = lua_getparam(1);

	if (!lua_isstring(filenameObj)) {
		lua_pushnil();
		return;
	}

	const char *filename = lua_getstring(filenameObj);
	// FIXME: implement missin code
	warning("L2_UnLockBackground: stub, filename: %s", filename);
}

static void L2_LockChore() {
	lua_Object nameObj = lua_getparam(1);
	lua_Object filenameObj = lua_getparam(2);

	if (!lua_isstring(nameObj) || !lua_isstring(filenameObj)) {
		lua_pushnil();
		return;
	}

	const char *name = lua_getstring(nameObj);
	const char *filename = lua_getstring(filenameObj);
	warning("L2_LockChore, name: %s, filename: %s", name, filename);
	// FIXME: implement missing rest part of code
}

static void L2_IsChoreValid() {
	lua_Object paramObj = lua_getparam(1);

	if (!lua_isnumber(paramObj))
		return;

	int num = (int)lua_getnumber(paramObj);
	warning("L2_IsChoreValid: stub, got %d, returns true", num);
	// FIXME: implement missing rest part of code
	pushbool(true);
}

static void L2_IsChorePlaying() {
	lua_Object paramObj = lua_getparam(1);

	if (!lua_isnumber(paramObj))
		return;

	int num = (int)lua_getnumber(paramObj);
	warning("L2_IsChorePlaying: stub, got %d, returns true", num);
	// FIXME: implement missing rest part of code
	pushbool(true);
}

static void L2_StopChore() {
	lua_Object choreObj = lua_getparam(1);
	lua_Object timeObj = lua_getparam(2);

	if (!lua_isnumber(choreObj) || !lua_isnumber(timeObj))
		return;

	int chore = (int)lua_getnumber(choreObj);
	float time = lua_getnumber(timeObj);
	// FIXME: implement missing rest part of code
	warning("L2_StopChore: stub, chore: %d time: %f", chore, time);
}

static void L2_AdvanceChore() {
	lua_Object choreObj = lua_getparam(1);
	lua_Object timeObj = lua_getparam(2);

	if (!lua_isnumber(choreObj) || !lua_isnumber(timeObj))
		return;

	int chore = (int)lua_getnumber(choreObj);
	float time = lua_getnumber(timeObj);
	// FIXME: implement missong code
	warning("L2_AdvanceChore: stub, chore: %d time: %f", chore, time);
}

static void L2_SetActorSortOrder() {
	lua_Object actorObj = lua_getparam(1);
	lua_Object modeObj = lua_getparam(2);

	if (!lua_isuserdata(actorObj) || lua_tag(actorObj) != MKTAG('A','C','T','R'))
		return;

	if (!lua_isnumber(modeObj))
		return;

	Actor *actor = getactor(actorObj);
	int mode = (int)lua_getnumber(modeObj);
	warning("L2_SetActorSortOrder, actor: %s, mode: %d", actor->getName().c_str(), mode);
	// FIXME: actor->func(mode);
}

static void L2_ActorActivateShadow() {
	lua_Object actorObj = lua_getparam(1);
	lua_Object qualityObj = lua_getparam(2);
	lua_Object planeObj = lua_getparam(3);

	if (!lua_isuserdata(actorObj) || lua_tag(actorObj) != MKTAG('A','C','T','R'))
		return;

	Actor *actor = getactor(actorObj);
	if (!actor)
		return;
	int quality = (int)lua_getnumber(qualityObj);
	const char *plane = "NULL";
	if (lua_isstring(planeObj))
		plane = lua_getstring(planeObj);
	warning("L2_ActorActivateShadow, actor: %s, aquality: %d, plane: %s", actor->getName().c_str(), quality, plane);
	// FIXME: implement missing rest part of code
}

static void L2_ActorStopMoving() {
	lua_Object actorObj = lua_getparam(1);

	if (!lua_isuserdata(actorObj) || lua_tag(actorObj) != MKTAG('A','C','T','R'))
		return;

	Actor *actor = getactor(actorObj);

	warning("L2_ActorStopMoving, actor: %s", actor->getName().c_str());
	// FIXME: implement missing rest part of code
}

static void L2_PutActorInOverworld() {
	lua_Object actorObj = lua_getparam(1);

	if (!lua_isuserdata(actorObj) || lua_tag(actorObj) != MKTAG('A','C','T','R'))
		return;

	Actor *actor = getactor(actorObj);

	warning("L2_PutActorInOverworld, actor: %s", actor->getName().c_str());
	// FIXME: implement missing func
	//actor->func();
}

void L2_GetActorWorldPos() {
	L1_GetActorPos();
	// FIXME: verify
	warning("L2_GetActorWorldPos: Currently just calls L1_GetActorPos, probably wrong");
}

static void L2_MakeScreenTextures() {
	lua_Object indexObj = lua_getparam(1);

	if (!lua_isnil(indexObj) && lua_isnumber(indexObj)) {
		int index = (int)lua_getnumber(indexObj);
		warning("L2_MakeScreenTextures, index: %d", index);
		// FIXME: implement missing function
//		if (func(index)) {
			lua_pushnumber(1.0);
			return;
//		}
	}
	lua_pushnil();
}

static void L2_PutActorInSet() {
	lua_Object actorObj = lua_getparam(1);
	lua_Object setObj = lua_getparam(2);

	if (!lua_isuserdata(actorObj) || lua_tag(actorObj) != MKTAG('A','C','T','R'))
		return;

	Actor *actor = getactor(actorObj);

	if (!lua_isstring(setObj) && !lua_isnil(setObj)) {
		lua_pushnil();
		return;
	}

	const char *set = lua_getstring(setObj);

	// FIXME verify adding actor to set
	if (!set) {
		actor->putInSet("");
	} else if (!actor->isInSet(set)) {
		actor->putInSet(set);
		lua_pushnumber(1.0);
		return;
	}
	lua_pushnil();
}

static void L2_LoadBundle() {
	lua_Object paramObj = lua_getparam(1);
	if (lua_isstring(paramObj) || lua_isnil(paramObj)) {
		const char *name = lua_getstring(paramObj);
		// FIXME: implement missing function
/*		if (!func(name))
			lua_pushnil();
		else*/
			lua_pushnumber(1.0);
		warning("L2_LoadBundle: stub, name: %s", name);
	}
}

static void L2_AreWeInternational() {
	if (g_grim->getGameLanguage() != Common::EN_ANY)
		lua_pushnumber(1.0);
}

static void L2_ImSetState() {
	lua_Object stateObj = lua_getparam(1);
	if (!lua_isnumber(stateObj))
		return;

	int state = (int)lua_getnumber(stateObj);
	warning("L2_ImSetState: stub, state: %d", state);
}

static void L2_EnableVoiceFX() {
	lua_Object stateObj = lua_getparam(1);

	bool state = false;
	if (!lua_isnil(stateObj))
		state = true;

	// FIXME: func(state);
	warning("L2_EnableVoiceFX: implement opcode, state: %d", (int)state);
}

static void L2_SetGroupVolume() {
	lua_Object groupObj = lua_getparam(1);
	lua_Object volumeObj = lua_getparam(2);

	if (!lua_isnumber(groupObj))
		return;
	int group = (int)lua_getnumber(groupObj);

	int volume = 100;
	if (lua_isnumber(volumeObj))
		volume = (int)lua_getnumber(volumeObj);

	// FIXME: func(group, volume);
	warning("L2_SetGroupVolume: implement opcode, group: %d, volume %d", group, volume);
}

static void L2_EnableAudioGroup() {
	lua_Object groupObj = lua_getparam(1);
	lua_Object stateObj = lua_getparam(2);

	if (!lua_isnumber(groupObj))
		return;
	int group = (int)lua_getnumber(groupObj);

	bool state = false;
	if (!lua_isnil(stateObj))
		state = true;

	// FIXME: func(group, state);
	warning("L2_EnableAudioGroup: implement opcode, group: %d, state %d", group, (int)state);
}

static void L2_ImSelectSet() {
	lua_Object qualityObj = lua_getparam(1);

	if (lua_isnumber(qualityObj)) {
		int quality = (int)lua_getnumber(qualityObj);
		// FIXME: func(quality);
		warning("L2_ImSelectSet: implement opcode, quality mode: %d", quality);
	}
}

static void L2_PlayActorChore() {
	lua_Object actorObj = lua_getparam(1);
	lua_Object choreObj = lua_getparam(2);
	lua_Object costumeObj = lua_getparam(3);
	lua_Object modeObj = lua_getparam(4);
	lua_Object paramObj = lua_getparam(5);

	if (!lua_isuserdata(actorObj) || lua_tag(actorObj) != MKTAG('A','C','T','R'))
		return;

	Actor *actor = getactor(actorObj);

	if (!lua_isstring(choreObj) || !lua_isstring(costumeObj))
		lua_pushnil();

	bool mode = false;
	float param = 0.0;

	if (!lua_isnil(modeObj)) {
		if (lua_getnumber(modeObj) != 0.0)
			mode = true;
		if (!lua_isnil(paramObj))
			if (lua_isnumber(paramObj))
				param = lua_getnumber(paramObj);
	}

	const char *choreName = lua_getstring(choreObj);
	const char *costumeName = lua_getstring(costumeObj);

	warning("L2_PlayActorChore: implement opcode actor: %s, chore: %s, costume: %s, mode bool: %d, param: %f",
			actor->getName().c_str(), choreName, costumeName, (int)mode, param);
	// FIXME. code below is a hack, need proper implementation
	actor->setCostume(costumeName);
	Costume *costume = actor->getCurrentCostume();
	costume->playChore(choreName);
	pushbool(true);
}

static void L2_StopActorChores() {
	lua_Object actorObj = lua_getparam(1);
	lua_Object paramObj = lua_getparam(2);

	if (!lua_isuserdata(actorObj) || lua_tag(actorObj) != MKTAG('A','C','T','R'))
		return;

	Actor *actor = getactor(actorObj);
	if (!actor)
		return;

	bool p = lua_isnil(paramObj) != 0;
	// I'm not fully sure about bool logic here
	//actor->func(p);
	warning("L2_StopActorChores: implement opcode... bool param: %d, actor: %s", (int)p, actor->getName().c_str());
}

static void L2_SetActorLighting() {
	lua_Object actorObj = lua_getparam(1);
	lua_Object lightModeObj = lua_getparam(2);

	if (!lua_isuserdata(actorObj) || lua_tag(actorObj) != MKTAG('A','C','T','R'))
		return;

	Actor *actor = getactor(actorObj);
	if (!actor)
		return;

	if (lua_isnil(lightModeObj) || !lua_isnumber(lightModeObj))
		return;

	int lightMode = (int)lua_getnumber(lightModeObj);
	if (lightMode != 0) {
		if (lightMode == 1) {
			//FIXME actor->
			warning("L2_SetActorLighting: case param 1(LIGHT_FASTDYN), actor: %s", actor->getName().c_str());
		} else if (lightMode == 2) {
			//FIXME actor->
			warning("L2_SetActorLighting: case param 2(LIGHT_NORMDYN), actor: %s", actor->getName().c_str());
		} else {
			//FIXME actor->
			warning("L2_SetActorLighting: case param %d(LIGHT_NONE), actor: %s", lightMode, actor->getName().c_str());
		}
	} else {
		//FIXME actor->
		warning("L2_SetActorLighting: case param 0(LIGHT_STATIC), actor: %s", actor->getName().c_str());
	}
}

static void L2_SetActorCollisionMode() {
	lua_Object actorObj = lua_getparam(1);
	lua_Object modeObj = lua_getparam(2);

	if (!lua_isuserdata(actorObj) || lua_tag(actorObj) != MKTAG('A','C','T','R'))
		return;

	Actor *actor = getactor(actorObj);
	assert(actor);
	int mode = (int)lua_getnumber(modeObj);
	// From _actors.lua
	// COLLISION_OFF = 0
	// COLLISION_BOX = 1
	// COLLISION_SPHERE = 2

	// FIXME: set collision mode
	//actor->func(mode);
	warning("L2_SetActorCollisionMode: implement opcode. Mode %d", mode);
}

static void L2_SetActorCollisionScale() {
	lua_Object actorObj = lua_getparam(1);
	lua_Object scaleObj = lua_getparam(2);

	if (!lua_isuserdata(actorObj) || lua_tag(actorObj) != MKTAG('A','C','T','R'))
		return;

	Actor *actor = getactor(actorObj);
	assert(actor);

	float scale = lua_getnumber(scaleObj);
	// FIXME: set collision scale
	//actor->func(scale);
	warning("L2_SetActorCollisionScale: implement opcode. Scale %f", scale);
}

static void L2_GetActorPuckVector() {
	// stub this for now as the regular one crashes.
	warning("L2_GetActorPuckVector: stubbed to L2 for now, L1 crashes");
	lua_pushnil();
}

static void L2_SetActorHeadLimits() {
	lua_Object actorObj = lua_getparam(1);
	lua_Object param2Obj = lua_getparam(2);
	lua_Object param3Obj = lua_getparam(3);
	lua_Object param4Obj = lua_getparam(4);

	if (!lua_isuserdata(actorObj) || lua_tag(actorObj) != MKTAG('A','C','T','R'))
		return;

	Actor *actor = getactor(actorObj);
	if (!actor)
		return;

	if (lua_isnumber(param2Obj) && lua_isnumber(param3Obj) && lua_isnumber(param4Obj)) {
		float param2 = lua_getnumber(param2Obj); // belows needs multiply by some runtime value
		float param3 = lua_getnumber(param3Obj);
		float param4 = lua_getnumber(param4Obj);
		// FIXME: implement missing func
		//actor->func(param2, param3, param4);
		warning("L2_SetActorHeadLimits: implement opcode. actor: %s, params: %f, %f, %f", actor->getName().c_str(), param2, param3, param4);
	}
}

static void L2_SetActorFOV() {
	lua_Object actorObj = lua_getparam(1);
	lua_Object fovObj = lua_getparam(2);

	if (!lua_isuserdata(actorObj) || lua_tag(actorObj) != MKTAG('A','C','T','R'))
		return;

	Actor *actor = getactor(actorObj);
	if (!actor)
		return;

	if (lua_isnumber(fovObj)) {
		float fov = lua_getnumber(fovObj);
		// FIXME: implement missing code
		//actor->func(fov); // cos(fov * some tuntime val * 0.5)
		warning("L2_SetActorFOV: implement opcode. actor: %s, param: %f", actor->getName().c_str(), fov);
	}
}

static void L2_AttachActor() {
	// Missing lua parts
	warning("L2_AttachActor: implement opcode");
}

static void L2_DetachActor() {
	// Missing lua parts
	warning("L2_DetachActor: implement opcode");
}

static void L2_GetCPUSpeed() {
	lua_pushnumber(500); // anything above 333 make best configuration
}

// This should be correct, judging by the Demo
// the only real difference from L1 is the lack of looping
static void L2_StartMovie() {
	lua_Object name = lua_getparam(1);
	if (!lua_isstring(name)) {
		lua_pushnil();
		return;
	}
	L1_CleanBuffer();

	GrimEngine::EngineMode prevEngineMode = g_grim->getMode();
	g_grim->setMode(GrimEngine::SmushMode);
	bool result = g_movie->play(lua_getstring(name), false, 0, 0);
	if (!result)
		g_grim->setMode(prevEngineMode);
	pushbool(result);
	g_grim->setMode(GrimEngine::SmushMode);
}

static void L2_IsMoviePlaying() {
	pushbool(g_movie->isPlaying());
}

static void L2_SetActiveCD() {
	lua_Object cdObj = lua_getparam(1);
	int cd = (int)lua_getnumber(cdObj);

	if (cd == 1 || cd == 2) {
		warning("L2_GetActiveCD: set to CD: %d", cd);
		// FIXME
		lua_pushnumber(1.0);
	}
}

static void L2_GetActiveCD() {
	// FIXME: return current CD number 1 or 2, original can also avoid push any numer
	warning("L2_GetActiveCD: return const CD 1");
	lua_pushnumber(1);
}

static void L2_PurgeText() {
	// FIXME
	warning("L2_PurgeText: implement opcode");
}

static void L2_ImFlushStack() {
	// FIXME
	warning("L2_ImFlushStack: implement opcode");
}

static void L2_LoadSound() {
	lua_Object strObj = lua_getparam(1);

	if (!lua_isstring(strObj))
		return;

	const char *str = lua_getstring(strObj);
	// FIXME: implement code
	warning("L2_LoadSound: stub, wants to load %s", str);
}

static void L2_ImSetMusicVol() {
	warning("L2_ImSetMusicVol: implement opcode");
}

static void L2_ImSetSfxVol() {
	warning("L2_ImSetSfxVol: implement opcode");
}

static void L2_ImSetVoiceVol() {
	warning("L2_ImSetVoiceVol: implement opcode");
}

static void L2_ImSetVoiceEffect() {
	warning("L2_ImSetVoiceEffect: implement opcode");
}

static void L2_ToggleOverworld() {
	warning("L2_ToggleOverworld: implement opcode");
}

static void L2_ScreenshotForSavegame() {
	warning("L2_ScreenshotForSavegame: implement opcode");
}

static void L2_EngineDisplay() {
	// dummy
}

static void L2_SetAmbientLight() {
	// dummy
}

static void L2_Display() {
	// dummy
}

// Stub function for builtin functions not yet implemented
static void stubWarning(const char *funcName) {
	warning("Stub function: %s", funcName);
}

static void stubError(const char *funcName) {
	error("Stub function: %s", funcName);
}

#define STUB_FUNC(name) void name() { stubWarning(#name); }
#define STUB_FUNC2(name) void name() { stubError(#name); }

// Opcodes more or less differ to Grim L1_* opcodes
STUB_FUNC2(L2_SetActorWalkChore)
STUB_FUNC2(L2_SetActorTurnChores)
STUB_FUNC2(L2_SetActorRestChore)
STUB_FUNC2(L2_SetActorMumblechore)
STUB_FUNC2(L2_SetActorTalkChore)
STUB_FUNC2(L2_WalkActorVector)
STUB_FUNC2(L2_SetActorLookRate)
STUB_FUNC2(L2_GetActorLookRate)
STUB_FUNC2(L2_GetVisibleThings)
STUB_FUNC2(L2_GetActorRot)
STUB_FUNC2(L2_LockSet)
STUB_FUNC2(L2_UnLockSet)
STUB_FUNC2(L2_PlaySound)
STUB_FUNC2(L2_IsSoundPlaying)
STUB_FUNC2(L2_MakeSectorActive)
STUB_FUNC2(L2_TurnActorTo)
STUB_FUNC2(L2_GetAngleBetweenActors)
STUB_FUNC2(L2_ImStartSound)
STUB_FUNC2(L2_ImGetSfxVol)
STUB_FUNC2(L2_ImGetVoiceVol)
STUB_FUNC2(L2_ImGetMusicVol)
STUB_FUNC2(L2_ImSetSequence)
STUB_FUNC2(L2_ChangeTextObject)
STUB_FUNC2(L2_GetTextCharPosition)
STUB_FUNC2(L2_SetOffscreenTextPos)
STUB_FUNC2(L2_FadeInChore)
STUB_FUNC2(L2_FadeOutChore)
STUB_FUNC2(L2_SetLightPosition)
STUB_FUNC2(L2_GetAngleBetweenVectors)
STUB_FUNC2(L2_IsPointInSector)

// Opcodes below are stubs in L1_* at that moment
STUB_FUNC2(L2_SetActorInvClipNode)
STUB_FUNC2(L2_NukeResources)
STUB_FUNC2(L2_UnShrinkBoxes)
STUB_FUNC2(L2_ShrinkBoxes)
STUB_FUNC2(L2_ResetTextures)
STUB_FUNC2(L2_AttachToResources)
STUB_FUNC2(L2_DetachFromResources)
STUB_FUNC2(L2_IrisUp)
STUB_FUNC2(L2_IrisDown)
STUB_FUNC2(L2_SetActorClipPlane)
STUB_FUNC2(L2_SetActorClipActive)
STUB_FUNC2(L2_FlushControls)
STUB_FUNC2(L2_ActorToClean)
STUB_FUNC2(L2_TurnLightOn)
STUB_FUNC2(L2_GetCameraLookVector)
STUB_FUNC2(L2_SetCameraRoll)
STUB_FUNC2(L2_SetCameraInterest)
STUB_FUNC2(L2_GetCameraPosition)
STUB_FUNC2(L2_SpewStartup)
STUB_FUNC2(L2_PreRender)
STUB_FUNC2(L2_GetSectorOppositeEdge)
STUB_FUNC2(L2_PreviousSetup)
STUB_FUNC2(L2_NextSetup)
STUB_FUNC2(L2_WorldToScreen)
STUB_FUNC2(L2_SetActorRoll)
STUB_FUNC2(L2_SetActorFrustrumCull)
STUB_FUNC2(L2_DriveActorTo)
STUB_FUNC2(L2_GetActorRect)
STUB_FUNC2(L2_GetTranslationMode)
STUB_FUNC2(L2_SetTranslationMode)
STUB_FUNC2(L2_KillPrimitive)
STUB_FUNC2(L2_WalkActorToAvoiding)
STUB_FUNC(L2_GetActorChores)
STUB_FUNC2(L2_SetCameraPosition)
STUB_FUNC2(L2_GetCameraFOV)
STUB_FUNC2(L2_SetCameraFOV)
STUB_FUNC2(L2_GetCameraRoll)
STUB_FUNC2(L2_ActorPuckOrient)
STUB_FUNC2(L2_GetMemoryUsage)
STUB_FUNC(L2_GetFontDimensions)

// Monkey specific opcodes
STUB_FUNC2(L2_ThumbnailFromFile)
STUB_FUNC2(L2_ClearSpecialtyTexture)
STUB_FUNC2(L2_ClearOverworld)
STUB_FUNC2(L2_EnableActorPuck)
STUB_FUNC2(L2_GetActorSortOrder)
STUB_FUNC2(L2_IsChoreLooping)
STUB_FUNC2(L2_PlayChore)
STUB_FUNC2(L2_PauseChore)
STUB_FUNC2(L2_CompleteChore)
STUB_FUNC2(L2_UnlockChore)
STUB_FUNC2(L2_LockChoreSet)
STUB_FUNC2(L2_UnlockChoreSet)
STUB_FUNC2(L2_EscapeMovie)
STUB_FUNC2(L2_StopAllSounds)
STUB_FUNC2(L2_FreeSound)
STUB_FUNC2(L2_PlayLoadedSound)
STUB_FUNC2(L2_GetSoundVolume)
STUB_FUNC2(L2_SetSoundVolume)
STUB_FUNC2(L2_PlaySoundFrom)
STUB_FUNC2(L2_PlayLoadedSoundFrom)
STUB_FUNC2(L2_UpdateSoundPosition)
STUB_FUNC2(L2_ImStateHasLooped)
STUB_FUNC2(L2_ImStateHasEnded)
STUB_FUNC2(L2_ImPushState)
STUB_FUNC2(L2_ImPopState)
STUB_FUNC2(L2_GetSectorName)
STUB_FUNC2(L2_GetCameraYaw)
STUB_FUNC2(L2_YawCamera)
STUB_FUNC2(L2_GetCameraPitch)
STUB_FUNC2(L2_PitchCamera)
STUB_FUNC2(L2_RollCamera)
STUB_FUNC2(L2_NewLayer)
STUB_FUNC2(L2_FreeLayer)
STUB_FUNC2(L2_SetLayerSortOrder)
STUB_FUNC2(L2_SetLayerFrame)
STUB_FUNC2(L2_AdvanceLayerFrame)
STUB_FUNC2(L2_PushText)
STUB_FUNC2(L2_PopText)
STUB_FUNC2(L2_NukeAllScriptLocks)
STUB_FUNC2(L2_ToggleDebugDraw)
STUB_FUNC2(L2_ToggleDrawCameras)
STUB_FUNC2(L2_ToggleDrawLights)
STUB_FUNC2(L2_ToggleDrawSectors)
STUB_FUNC2(L2_ToggleDrawBBoxes)
STUB_FUNC2(L2_ToggleDrawFPS)
STUB_FUNC2(L2_ToggleDrawPerformance)
STUB_FUNC2(L2_ToggleDrawActorStats)
STUB_FUNC2(L2_SectEditSelect)
STUB_FUNC2(L2_SectEditPlace)
STUB_FUNC2(L2_SectEditDelete)
STUB_FUNC2(L2_SectEditInsert)
STUB_FUNC2(L2_SectEditSortAdd)
STUB_FUNC2(L2_SectEditForgetIt)
STUB_FUNC2(L2_FRUTEY_Begin)
STUB_FUNC2(L2_FRUTEY_End)

struct luaL_reg monkeyMainOpcodes[] = {
	{ "EngineDisplay", L2_EngineDisplay },
	{ "Load", L1_Load },
	{ "Save", L1_Save },
	{ "remove", L1_Remove },
	{ "SetActorTimeScale", L1_SetActorTimeScale },
	{ "SetActorWalkChore", L1_SetActorWalkChore },
	{ "SetActorTurnChores", L1_SetActorTurnChores },
	{ "SetActorRestChore", L1_SetActorRestChore },
	{ "SetActorMumblechore", L1_SetActorMumblechore },
	{ "SetActorTalkChore", L1_SetActorTalkChore },
	{ "SetActorWalkRate", L2_SetActorWalkRate },
	{ "GetActorWalkRate", L2_GetActorWalkRate },
	{ "SetActorTurnRate", L1_SetActorTurnRate },
	{ "SetSelectedActor", L1_SetSelectedActor },
	{ "LoadActor", L1_LoadActor },
	{ "GetActorPos", L1_GetActorPos },
	{ "GetActorPuckVector", L2_GetActorPuckVector },
	{ "GetActorYawToPoint", L1_GetActorYawToPoint },
	{ "SetActorReflection", L1_SetActorReflection },
	{ "PutActorAt", L1_PutActorAt },
	{ "PutActorInSet", L2_PutActorInSet },
	{ "WalkActorVector", L2_WalkActorVector },
	{ "WalkActorForward", L1_WalkActorForward },
	{ "WalkActorTo", L1_WalkActorTo },
	{ "WalkActorToAvoiding", L2_WalkActorToAvoiding },
	{ "ActorLookAt", L1_ActorLookAt },
	{ "SetActorLookRate", L1_SetActorLookRate },
	{ "GetActorLookRate", L2_GetActorLookRate },
	{ "GetVisibleThings", L1_GetVisibleThings },
	{ "SetActorHead", L1_SetActorHead },
	{ "SetActorVisibility", L1_SetActorVisibility },
	{ "SetActorFollowBoxes", L1_SetActorFollowBoxes },
	{ "ShutUpActor", L1_ShutUpActor },
	{ "IsActorInSector", L1_IsActorInSector },
	{ "GetActorSector", L1_GetActorSector },
	{ "TurnActor", L1_TurnActor },
	{ "GetActorRot", L1_GetActorRot },
	{ "SetActorRot", L1_SetActorRot },
	{ "IsActorTurning", L1_IsActorTurning },
	{ "PlayActorChore", L2_PlayActorChore },
	{ "IsActorResting", L1_IsActorResting },
	{ "GetActorChores", L2_GetActorChores },
	{ "WorldToScreen", L2_WorldToScreen },
	{ "exit", L1_Exit },
	{ "FunctionName", L1_FunctionName },
	{ "EnableControl", L1_EnableControl },
	{ "DisableControl", L1_DisableControl },
	{ "GetControlState", L1_GetControlState },
	{ "PrintError", L1_PrintDebug },
	{ "PrintWarning", L1_PrintDebug },
	{ "PrintDebug", L1_PrintDebug },
	{ "MakeCurrentSet", L1_MakeCurrentSet },
	{ "LockSet", L2_LockSet },
	{ "UnLockSet", L2_UnLockSet },
	{ "MakeCurrentSetup", L2_MakeCurrentSetup },
	{ "GetCurrentSetup", L1_GetCurrentSetup },
	{ "NextSetup", L2_NextSetup },
	{ "PreviousSetup", L2_PreviousSetup },
	{ "StartMovie", L2_StartMovie },
	{ "StopMovie", L1_StopMovie },
	{ "PauseMovie", L1_PauseMovie },
	{ "IsMoviePlaying", L2_IsMoviePlaying },
	{ "PlaySound", L2_PlaySound },
	{ "IsSoundPlaying", L2_IsSoundPlaying },
	{ "FileFindFirst", L1_FileFindFirst },
	{ "FileFindNext", L1_FileFindNext },
	{ "FileFindDispose", L1_FileFindDispose },
	{ "InputDialog", L1_InputDialog },
	{ "GetSectorOppositeEdge", L2_GetSectorOppositeEdge },
	{ "MakeSectorActive", L1_MakeSectorActive },
	{ "GetCurrentScript", L1_GetCurrentScript },
	{ "GetCameraPosition", L2_GetCameraPosition },
	{ "SetCameraPosition", L2_SetCameraPosition },
	{ "GetCameraFOV", L2_GetCameraFOV },
	{ "SetCameraFOV", L2_SetCameraFOV },
	{ "GetCameraRoll", L2_GetCameraRoll },
	{ "GetCameraLookVector", L2_GetCameraLookVector },
	{ "TurnActorTo", L2_TurnActorTo },
	{ "PerSecond", L1_PerSecond },
	{ "GetAngleBetweenVectors", L2_GetAngleBetweenVectors },
	{ "GetAngleBetweenActors", L2_GetAngleBetweenActors },
	{ "SetAmbientLight", L2_SetAmbientLight },
	{ "TurnLightOn", L2_TurnLightOn },
	{ "SetLightPosition", L2_SetLightPosition },
	{ "LightMgrStartup", L1_LightMgrStartup },
	{ "ImStartSound", L2_ImStartSound },
	{ "ImGetSfxVol", L2_ImGetSfxVol },
	{ "ImGetVoiceVol", L2_ImGetVoiceVol },
	{ "ImGetMusicVol", L2_ImGetMusicVol },
	{ "ImSetState", L2_ImSetState },
	{ "ImSetSequence", L2_ImSetSequence },
	{ "ImSetMusicVol", L2_ImSetMusicVol },
	{ "ImSetSfxVol", L2_ImSetSfxVol },
	{ "ImSetVoiceVol", L2_ImSetVoiceVol },
	{ "ImSetVoiceEffect", L2_ImSetVoiceEffect },
	{ "LoadBundle", L2_LoadBundle },
	{ "SetGamma", L1_SetGamma },
	{ "SetActorWalkDominate", L1_SetActorWalkDominate },
	{ "RenderModeUser", L1_RenderModeUser },
	{ "DimScreen", L2_DimScreen },
	{ "Display", L2_Display },
	{ "SetSpeechMode", L1_SetSpeechMode },
	{ "GetSpeechMode", L1_GetSpeechMode },
	{ "SetActorCollisionMode", L2_SetActorCollisionMode },
	{ "SetActorCollisionScale", L2_SetActorCollisionScale },
	{ "SubmitSaveGameData", L1_SubmitSaveGameData },
	{ "GetSaveGameData", L1_GetSaveGameData },
	{ "SetTextSpeed", L1_SetTextSpeed },
	{ "GetTextSpeed", L1_GetTextSpeed },
	{ "JustLoaded", L1_JustLoaded },
	{ "UnShrinkBoxes", L2_UnShrinkBoxes },
	{ "GetMemoryUsage", L2_GetMemoryUsage },
	{ "dofile", L1_new_dofile },

	// Monkey specific opcodes:
	{ "ScreenshotForSavegame", L2_ScreenshotForSavegame },
	{ "GetActorWorldPos", L2_GetActorWorldPos },
	{ "SetActiveCD", L2_SetActiveCD },
	{ "GetActiveCD", L2_GetActiveCD },
	{ "AreWeInternational", L2_AreWeInternational },
	{ "MakeScreenTextures", L2_MakeScreenTextures },
	{ "ThumbnailFromFile", L2_ThumbnailFromFile },
	{ "ClearSpecialtyTexture", L2_ClearSpecialtyTexture },
	{ "UnloadActor", L2_UnloadActor },
	{ "PutActorInOverworld", L2_PutActorInOverworld },
	{ "RemoveActorFromOverworld", L2_RemoveActorFromOverworld },
	{ "ClearOverworld", L2_ClearOverworld },
	{ "ToggleOverworld", L2_ToggleOverworld },
	{ "ActorStopMoving", L2_ActorStopMoving },
	{ "SetActorFOV", L2_SetActorFOV },
	{ "SetActorLighting", L2_SetActorLighting },
	{ "SetActorHeadLimits", L2_SetActorHeadLimits },
	{ "ActorActivateShadow", L2_ActorActivateShadow },
	{ "EnableActorPuck", L2_EnableActorPuck },
	{ "SetActorGlobalAlpha", L2_SetActorGlobalAlpha },
	{ "SetActorLocalAlpha", L2_SetActorLocalAlpha },
	{ "SetActorSortOrder", L2_SetActorSortOrder },
	{ "GetActorSortOrder", L2_GetActorSortOrder },
	{ "AttachActor", L2_AttachActor },
	{ "DetachActor", L2_DetachActor },
	{ "IsChoreValid", L2_IsChoreValid },
	{ "IsChorePlaying", L2_IsChorePlaying },
	{ "IsChoreLooping", L2_IsChoreLooping },
	{ "StopActorChores", L2_StopActorChores },
	{ "PlayChore", L2_PlayChore },
	{ "StopChore", L2_StopChore },
	{ "PauseChore", L2_PauseChore },
	{ "AdvanceChore", L2_AdvanceChore },
	{ "CompleteChore", L2_CompleteChore },
	{ "LockChore", L2_LockChore },
	{ "UnlockChore", L2_UnlockChore },
	{ "LockChoreSet", L2_LockChoreSet },
	{ "UnlockChoreSet", L2_UnlockChoreSet },
	{ "LockBackground", L2_LockBackground },
	{ "UnLockBackground", L2_UnLockBackground },
	{ "EscapeMovie", L2_EscapeMovie },
	{ "StopAllSounds", L2_StopAllSounds },
	{ "LoadSound", L2_LoadSound },
	{ "FreeSound", L2_FreeSound },
	{ "PlayLoadedSound", L2_PlayLoadedSound },
	{ "SetGroupVolume", L2_SetGroupVolume },
	{ "GetSoundVolume", L2_GetSoundVolume },
	{ "SetSoundVolume", L2_SetSoundVolume },
	{ "EnableAudioGroup", L2_EnableAudioGroup },
	{ "EnableVoiceFX", L2_EnableVoiceFX },
	{ "PlaySoundFrom", L2_PlaySoundFrom },
	{ "PlayLoadedSoundFrom", L2_PlayLoadedSoundFrom },
	{ "SetReverb", L2_SetReverb },
	{ "UpdateSoundPosition", L2_UpdateSoundPosition },
	{ "ImSelectSet", L2_ImSelectSet },
	{ "ImStateHasLooped", L2_ImStateHasLooped },
	{ "ImStateHasEnded", L2_ImStateHasEnded },
	{ "ImPushState", L2_ImPushState },
	{ "ImPopState", L2_ImPopState },
	{ "ImFlushStack", L2_ImFlushStack },
	{ "ImGetMillisecondPosition", L2_ImGetMillisecondPosition },
	{ "GetSectorName", L2_GetSectorName },
	{ "GetCameraYaw", L2_GetCameraYaw },
	{ "YawCamera", L2_YawCamera },
	{ "GetCameraPitch", L2_GetCameraPitch },
	{ "PitchCamera", L2_PitchCamera },
	{ "RollCamera", L2_RollCamera },
	{ "UndimAll", L2_UndimAll },
	{ "UndimRegion", L2_UndimRegion },
	{ "GetCPUSpeed", L2_GetCPUSpeed },
	{ "NewLayer", L2_NewLayer },
	{ "FreeLayer", L2_FreeLayer },
	{ "SetLayerSortOrder", L2_SetLayerSortOrder },
	{ "SetLayerFrame", L2_SetLayerFrame },
	{ "AdvanceLayerFrame", L2_AdvanceLayerFrame },
	{ "PushText", L2_PushText },
	{ "PopText", L2_PopText },
	{ "NukeAllScriptLocks", L2_NukeAllScriptLocks },
	{ "ToggleDebugDraw", L2_ToggleDebugDraw },
	{ "ToggleDrawCameras", L2_ToggleDrawCameras },
	{ "ToggleDrawLights", L2_ToggleDrawLights },
	{ "ToggleDrawSectors", L2_ToggleDrawSectors },
	{ "ToggleDrawBBoxes", L2_ToggleDrawBBoxes },
	{ "ToggleDrawFPS", L2_ToggleDrawFPS },
	{ "ToggleDrawPerformance", L2_ToggleDrawPerformance },
	{ "ToggleDrawActorStats", L2_ToggleDrawActorStats },
	{ "SectEditSelect", L2_SectEditSelect },
	{ "SectEditPlace", L2_SectEditPlace },
	{ "SectEditDelete", L2_SectEditDelete },
	{ "SectEditInsert", L2_SectEditInsert },
	{ "SectEditSortAdd", L2_SectEditSortAdd },
	{ "SectEditForgetIt", L2_SectEditForgetIt },
	{ "FRUTEY_Begin", L2_FRUTEY_Begin },
	{ "FRUTEY_End", L2_FRUTEY_End },
	{ "sleep_for", L2_SleepFor }
};

struct luaL_reg monkeyTextOpcodes[] = {
	{ "IsMessageGoing", L1_IsMessageGoing },
	{ "SetSayLineDefaults", L1_SetSayLineDefaults },
	{ "SetActorTalkColor", L1_SetActorTalkColor },
	{ "SayLine", L1_SayLine },
	{ "MakeTextObject", L1_MakeTextObject },
	{ "GetTextObjectDimensions", L1_GetTextObjectDimensions },
	{ "GetFontDimensions", L2_GetFontDimensions },
	{ "ChangeTextObject", L2_ChangeTextObject },
	{ "KillTextObject", L1_KillTextObject },
	{ "ExpireText", L1_ExpireText },
	{ "PurgeText", L2_PurgeText },
	{ "MakeColor", L1_MakeColor },
	{ "GetColorComponents", L1_GetColorComponents },
	{ "GetTextCharPosition", L2_GetTextCharPosition },
	{ "LocalizeString", L1_LocalizeString },
	{ "SetOffscreenTextPos", L2_SetOffscreenTextPos }
};

struct luaL_reg monkeyPrimitivesOpcodes[] = {
	{ "DrawLine", L1_DrawLine },
	{ "ChangePrimitive", L1_ChangePrimitive },
	{ "KillPrimitive", L2_KillPrimitive },
	{ "PurgePrimitiveQueue", L1_PurgePrimitiveQueue }
};

struct luaL_reg monkeyMiscOpcodes[] = {
	{ "  concatfallback", L1_concatFallback },
	{ "  typeoverride", L1_typeOverride },
	{ "  dfltcamera", dummyHandler },
	{ "  dfltcontrol", dummyHandler },
};

void registerMonkeyOpcodes() {
	// Register main opcodes functions
	luaL_openlib(monkeyMainOpcodes, ARRAYSIZE(monkeyMainOpcodes));

	// Register text opcodes functions
	luaL_openlib(monkeyTextOpcodes, ARRAYSIZE(monkeyTextOpcodes));

	// Register primitives opcodes functions
	luaL_openlib(monkeyPrimitivesOpcodes, ARRAYSIZE(monkeyPrimitivesOpcodes));

	// Register miscOpcodes opcodes functions
	luaL_openlib(monkeyMiscOpcodes, ARRAYSIZE(monkeyMiscOpcodes));
}

} // end of namespace Grim
