#pragma once
#include "../Common.hpp"
#include "Types.hpp"
#include "TextBox.hpp"
#include "UI/submenu/AbstractSubmenu.hpp"

#include "natives.hpp"
#include "nlohmann/json.hpp"

namespace big::UserInterface
{
	struct RGB_COLOR
	{
		int r = 0,
			g = 0,
			b = 0;
	};

	struct RGBA : RGB_COLOR
	{
		int a = 0;
	};

	struct RGBAF : RGBA
	{
		int f = 0;
	};

	enum class Font : std::int32_t
	{
		ChaletLondon = 0,
		HouseScript = 1,
		Monospace = 2,
		Wingdings = 3,
		ChaletComprimeCologne = 4,
		Pricedown = 7
	};

	enum class HeaderType : std::int32_t
	{
		Static = 0
	};
	enum ControllerInputs
	{
		INPUT_NEXT_CAMERA = 0,
		INPUT_LOOK_LR = 1,
		INPUT_LOOK_UD = 2,
		INPUT_LOOK_UP_ONLY = 3,
		INPUT_LOOK_DOWN_ONLY = 4,
		INPUT_LOOK_LEFT_ONLY = 5,
		INPUT_LOOK_RIGHT_ONLY = 6,
		INPUT_CINEMATIC_SLOWMO = 7,
		INPUT_SCRIPTED_FLY_UD = 8,
		INPUT_SCRIPTED_FLY_LR = 9,
		INPUT_SCRIPTED_FLY_ZUP = 10,
		INPUT_SCRIPTED_FLY_ZDOWN = 11,
		INPUT_WEAPON_WHEEL_UD = 12,
		INPUT_WEAPON_WHEEL_LR = 13,
		INPUT_WEAPON_WHEEL_NEXT = 14,
		INPUT_WEAPON_WHEEL_PREV = 15,
		INPUT_SELECT_NEXT_WEAPON = 16,
		INPUT_SELECT_PREV_WEAPON = 17,
		INPUT_SKIP_CUTSCENE = 18,
		INPUT_CHARACTER_WHEEL = 19,
		INPUT_MULTIPLAYER_INFO = 20,
		INPUT_SPRINT = 21,
		INPUT_JUMP = 22,
		INPUT_ENTER = 23,
		INPUT_ATTACK = 24,
		INPUT_AIM = 25,
		INPUT_LOOK_BEHIND = 26,
		INPUT_PHONE = 27,
		INPUT_SPECIAL_ABILITY = 28,
		INPUT_SPECIAL_ABILITY_SECONDARY = 29,
		INPUT_MOVE_LR = 30,
		INPUT_MOVE_UD = 31,
		INPUT_MOVE_UP_ONLY = 32,
		INPUT_MOVE_DOWN_ONLY = 33,
		INPUT_MOVE_LEFT_ONLY = 34,
		INPUT_MOVE_RIGHT_ONLY = 35,
		INPUT_DUCK = 36,
		INPUT_SELECT_WEAPON = 37,
		INPUT_PICKUP = 38,
		INPUT_SNIPER_ZOOM = 39,
		INPUT_SNIPER_ZOOM_IN_ONLY = 40,
		INPUT_SNIPER_ZOOM_OUT_ONLY = 41,
		INPUT_SNIPER_ZOOM_IN_SECONDARY = 42,
		INPUT_SNIPER_ZOOM_OUT_SECONDARY = 43,
		INPUT_COVER = 44,
		INPUT_RELOAD = 45,
		INPUT_TALK = 46,
		INPUT_DETONATE = 47,
		INPUT_HUD_SPECIAL = 48,
		INPUT_ARREST = 49,
		INPUT_ACCURATE_AIM = 50,
		INPUT_CONTEXT = 51,
		INPUT_CONTEXT_SECONDARY = 52,
		INPUT_WEAPON_SPECIAL = 53,
		INPUT_WEAPON_SPECIAL_TWO = 54,
		INPUT_DIVE = 55,
		INPUT_DROP_WEAPON = 56,
		INPUT_DROP_AMMO = 57,
		INPUT_THROW_GRENADE = 58,
		INPUT_VEH_MOVE_LR = 59,
		INPUT_VEH_MOVE_UD = 60,
		INPUT_VEH_MOVE_UP_ONLY = 61,
		INPUT_VEH_MOVE_DOWN_ONLY = 62,
		INPUT_VEH_MOVE_LEFT_ONLY = 63,
		INPUT_VEH_MOVE_RIGHT_ONLY = 64,
		INPUT_VEH_SPECIAL = 65,
		INPUT_VEH_GUN_LR = 66,
		INPUT_VEH_GUN_UD = 67,
		INPUT_VEH_AIM = 68,
		INPUT_VEH_ATTACK = 69,
		INPUT_VEH_ATTACK2 = 70,
		INPUT_VEH_ACCELERATE = 71,
		INPUT_VEH_BRAKE = 72,
		INPUT_VEH_DUCK = 73,
		INPUT_VEH_HEADLIGHT = 74,
		INPUT_VEH_EXIT = 75,
		INPUT_VEH_HANDBRAKE = 76,
		INPUT_VEH_HOTWIRE_LEFT = 77,
		INPUT_VEH_HOTWIRE_RIGHT = 78,
		INPUT_VEH_LOOK_BEHIND = 79,
		INPUT_VEH_CIN_CAM = 80,
		INPUT_VEH_NEXT_RADIO = 81,
		INPUT_VEH_PREV_RADIO = 82,
		INPUT_VEH_NEXT_RADIO_TRACK = 83,
		INPUT_VEH_PREV_RADIO_TRACK = 84,
		INPUT_VEH_RADIO_WHEEL = 85,
		INPUT_VEH_HORN = 86,
		INPUT_VEH_FLY_THROTTLE_UP = 87,
		INPUT_VEH_FLY_THROTTLE_DOWN = 88,
		INPUT_VEH_FLY_YAW_LEFT = 89,
		INPUT_VEH_FLY_YAW_RIGHT = 90,
		INPUT_VEH_PASSENGER_AIM = 91,
		INPUT_VEH_PASSENGER_ATTACK = 92,
		INPUT_VEH_SPECIAL_ABILITY_FRANKLIN = 93,
		INPUT_VEH_STUNT_UD = 94,
		INPUT_VEH_CINEMATIC_UD = 95,
		INPUT_VEH_CINEMATIC_UP_ONLY = 96,
		INPUT_VEH_CINEMATIC_DOWN_ONLY = 97,
		INPUT_VEH_CINEMATIC_LR = 98,
		INPUT_VEH_SELECT_NEXT_WEAPON = 99,
		INPUT_VEH_SELECT_PREV_WEAPON = 100,
		INPUT_VEH_ROOF = 101,
		INPUT_VEH_JUMP = 102,
		INPUT_VEH_GRAPPLING_HOOK = 103,
		INPUT_VEH_SHUFFLE = 104,
		INPUT_VEH_DROP_PROJECTILE = 105,
		INPUT_VEH_MOUSE_CONTROL_OVERRIDE = 106,
		INPUT_VEH_FLY_ROLL_LR = 107,
		INPUT_VEH_FLY_ROLL_LEFT_ONLY = 108,
		INPUT_VEH_FLY_ROLL_RIGHT_ONLY = 109,
		INPUT_VEH_FLY_PITCH_UD = 110,
		INPUT_VEH_FLY_PITCH_UP_ONLY = 111,
		INPUT_VEH_FLY_PITCH_DOWN_ONLY = 112,
		INPUT_VEH_FLY_UNDERCARRIAGE = 113,
		INPUT_VEH_FLY_ATTACK = 114,
		INPUT_VEH_FLY_SELECT_NEXT_WEAPON = 115,
		INPUT_VEH_FLY_SELECT_PREV_WEAPON = 116,
		INPUT_VEH_FLY_SELECT_TARGET_LEFT = 117,
		INPUT_VEH_FLY_SELECT_TARGET_RIGHT = 118,
		INPUT_VEH_FLY_VERTICAL_FLIGHT_MODE = 119,
		INPUT_VEH_FLY_DUCK = 120,
		INPUT_VEH_FLY_ATTACK_CAMERA = 121,
		INPUT_VEH_FLY_MOUSE_CONTROL_OVERRIDE = 122,
		INPUT_VEH_SUB_TURN_LR = 123,
		INPUT_VEH_SUB_TURN_LEFT_ONLY = 124,
		INPUT_VEH_SUB_TURN_RIGHT_ONLY = 125,
		INPUT_VEH_SUB_PITCH_UD = 126,
		INPUT_VEH_SUB_PITCH_UP_ONLY = 127,
		INPUT_VEH_SUB_PITCH_DOWN_ONLY = 128,
		INPUT_VEH_SUB_THROTTLE_UP = 129,
		INPUT_VEH_SUB_THROTTLE_DOWN = 130,
		INPUT_VEH_SUB_ASCEND = 131,
		INPUT_VEH_SUB_DESCEND = 132,
		INPUT_VEH_SUB_TURN_HARD_LEFT = 133,
		INPUT_VEH_SUB_TURN_HARD_RIGHT = 134,
		INPUT_VEH_SUB_MOUSE_CONTROL_OVERRIDE = 135,
		INPUT_VEH_PUSHBIKE_PEDAL = 136,
		INPUT_VEH_PUSHBIKE_SPRINT = 137,
		INPUT_VEH_PUSHBIKE_FRONT_BRAKE = 138,
		INPUT_VEH_PUSHBIKE_REAR_BRAKE = 139,
		INPUT_MELEE_ATTACK_LIGHT = 140,
		INPUT_MELEE_ATTACK_HEAVY = 141,
		INPUT_MELEE_ATTACK_ALTERNATE = 142,
		INPUT_MELEE_BLOCK = 143,
		INPUT_PARACHUTE_DEPLOY = 144,
		INPUT_PARACHUTE_DETACH = 145,
		INPUT_PARACHUTE_TURN_LR = 146,
		INPUT_PARACHUTE_TURN_LEFT_ONLY = 147,
		INPUT_PARACHUTE_TURN_RIGHT_ONLY = 148,
		INPUT_PARACHUTE_PITCH_UD = 149,
		INPUT_PARACHUTE_PITCH_UP_ONLY = 150,
		INPUT_PARACHUTE_PITCH_DOWN_ONLY = 151,
		INPUT_PARACHUTE_BRAKE_LEFT = 152,
		INPUT_PARACHUTE_BRAKE_RIGHT = 153,
		INPUT_PARACHUTE_SMOKE = 154,
		INPUT_PARACHUTE_PRECISION_LANDING = 155,
		INPUT_MAP = 156,
		INPUT_SELECT_WEAPON_UNARMED = 157,
		INPUT_SELECT_WEAPON_MELEE = 158,
		INPUT_SELECT_WEAPON_HANDGUN = 159,
		INPUT_SELECT_WEAPON_SHOTGUN = 160,
		INPUT_SELECT_WEAPON_SMG = 161,
		INPUT_SELECT_WEAPON_AUTO_RIFLE = 162,
		INPUT_SELECT_WEAPON_SNIPER = 163,
		INPUT_SELECT_WEAPON_HEAVY = 164,
		INPUT_SELECT_WEAPON_SPECIAL = 165,
		INPUT_SELECT_CHARACTER_MICHAEL = 166,
		INPUT_SELECT_CHARACTER_FRANKLIN = 167,
		INPUT_SELECT_CHARACTER_TREVOR = 168,
		INPUT_SELECT_CHARACTER_MULTIPLAYER = 169,
		INPUT_SAVE_REPLAY_CLIP = 170,
		INPUT_SPECIAL_ABILITY_PC = 171,
		INPUT_CELLPHONE_UP = 172,
		INPUT_CELLPHONE_DOWN = 173,
		INPUT_CELLPHONE_LEFT = 174,
		INPUT_CELLPHONE_RIGHT = 175,
		INPUT_CELLPHONE_SELECT = 176,
		INPUT_CELLPHONE_CANCEL = 177,
		INPUT_CELLPHONE_OPTION = 178,
		INPUT_CELLPHONE_EXTRA_OPTION = 179,
		INPUT_CELLPHONE_SCROLL_FORWARD = 180,
		INPUT_CELLPHONE_SCROLL_BACKWARD = 181,
		INPUT_CELLPHONE_CAMERA_FOCUS_LOCK = 182,
		INPUT_CELLPHONE_CAMERA_GRID = 183,
		INPUT_CELLPHONE_CAMERA_SELFIE = 184,
		INPUT_CELLPHONE_CAMERA_DOF = 185,
		INPUT_CELLPHONE_CAMERA_EXPRESSION = 186,
		INPUT_FRONTEND_DOWN = 187,
		INPUT_FRONTEND_UP = 188,
		INPUT_FRONTEND_LEFT = 189,
		INPUT_FRONTEND_RIGHT = 190,
		INPUT_FRONTEND_RDOWN = 191,
		INPUT_FRONTEND_RUP = 192,
		INPUT_FRONTEND_RLEFT = 193,
		INPUT_FRONTEND_RRIGHT = 194,
		INPUT_FRONTEND_AXIS_X = 195,
		INPUT_FRONTEND_AXIS_Y = 196,
		INPUT_FRONTEND_RIGHT_AXIS_X = 197,
		INPUT_FRONTEND_RIGHT_AXIS_Y = 198,
		INPUT_FRONTEND_PAUSE = 199,
		INPUT_FRONTEND_PAUSE_ALTERNATE = 200,
		INPUT_FRONTEND_ACCEPT = 201,
		INPUT_FRONTEND_CANCEL = 202,
		INPUT_FRONTEND_X = 203,
		INPUT_FRONTEND_Y = 204,
		INPUT_FRONTEND_LB = 205,
		INPUT_FRONTEND_RB = 206,
		INPUT_FRONTEND_LT = 207,
		INPUT_FRONTEND_RT = 208,
		INPUT_FRONTEND_LS = 209,
		INPUT_FRONTEND_RS = 210,
		INPUT_FRONTEND_LEADERBOARD = 211,
		INPUT_FRONTEND_SOCIAL_CLUB = 212,
		INPUT_FRONTEND_SOCIAL_CLUB_SECONDARY = 213,
		INPUT_FRONTEND_DELETE = 214,
		INPUT_FRONTEND_ENDSCREEN_ACCEPT = 215,
		INPUT_FRONTEND_ENDSCREEN_EXPAND = 216,
		INPUT_FRONTEND_SELECT = 217,
		INPUT_SCRIPT_LEFT_AXIS_X = 218,
		INPUT_SCRIPT_LEFT_AXIS_Y = 219,
		INPUT_SCRIPT_RIGHT_AXIS_X = 220,
		INPUT_SCRIPT_RIGHT_AXIS_Y = 221,
		INPUT_SCRIPT_RUP = 222,
		INPUT_SCRIPT_RDOWN = 223,
		INPUT_SCRIPT_RLEFT = 224,
		INPUT_SCRIPT_RRIGHT = 225,
		INPUT_SCRIPT_LB = 226,
		INPUT_SCRIPT_RB = 227,
		INPUT_SCRIPT_LT = 228,
		INPUT_SCRIPT_RT = 229,
		INPUT_SCRIPT_LS = 230,
		INPUT_SCRIPT_RS = 231,
		INPUT_SCRIPT_PAD_UP = 232,
		INPUT_SCRIPT_PAD_DOWN = 233,
		INPUT_SCRIPT_PAD_LEFT = 234,
		INPUT_SCRIPT_PAD_RIGHT = 235,
		INPUT_SCRIPT_SELECT = 236,
		INPUT_CURSOR_ACCEPT = 237,
		INPUT_CURSOR_CANCEL = 238,
		INPUT_CURSOR_X = 239,
		INPUT_CURSOR_Y = 240,
		INPUT_CURSOR_SCROLL_UP = 241,
		INPUT_CURSOR_SCROLL_DOWN = 242,
		INPUT_ENTER_CHEAT_CODE = 243,
		INPUT_INTERACTION_MENU = 244,
		INPUT_MP_TEXT_CHAT_ALL = 245,
		INPUT_MP_TEXT_CHAT_TEAM = 246,
		INPUT_MP_TEXT_CHAT_FRIENDS = 247,
		INPUT_MP_TEXT_CHAT_CREW = 248,
		INPUT_PUSH_TO_TALK = 249,
		INPUT_CREATOR_LS = 250,
		INPUT_CREATOR_RS = 251,
		INPUT_CREATOR_LT = 252,
		INPUT_CREATOR_RT = 253,
		INPUT_CREATOR_MENU_TOGGLE = 254,
		INPUT_CREATOR_ACCEPT = 255,
		INPUT_CREATOR_DELETE = 256,
		INPUT_ATTACK2 = 257,
		INPUT_RAPPEL_JUMP = 258,
		INPUT_RAPPEL_LONG_JUMP = 259,
		INPUT_RAPPEL_SMASH_WINDOW = 260,
		INPUT_PREV_WEAPON = 261,
		INPUT_NEXT_WEAPON = 262,
		INPUT_MELEE_ATTACK1 = 263,
		INPUT_MELEE_ATTACK2 = 264,
		INPUT_WHISTLE = 265,
		INPUT_MOVE_LEFT = 266,
		INPUT_MOVE_RIGHT = 267,
		INPUT_MOVE_UP = 268,
		INPUT_MOVE_DOWN = 269,
		INPUT_LOOK_LEFT = 270,
		INPUT_LOOK_RIGHT = 271,
		INPUT_LOOK_UP = 272,
		INPUT_LOOK_DOWN = 273,
		INPUT_SNIPER_ZOOM_IN = 274,
		INPUT_SNIPER_ZOOM_OUT = 275,
		INPUT_SNIPER_ZOOM_IN_ALTERNATE = 276,
		INPUT_SNIPER_ZOOM_OUT_ALTERNATE = 277,
		INPUT_VEH_MOVE_LEFT = 278,
		INPUT_VEH_MOVE_RIGHT = 279,
		INPUT_VEH_MOVE_UP = 280,
		INPUT_VEH_MOVE_DOWN = 281,
		INPUT_VEH_GUN_LEFT = 282,
		INPUT_VEH_GUN_RIGHT = 283,
		INPUT_VEH_GUN_UP = 284,
		INPUT_VEH_GUN_DOWN = 285,
		INPUT_VEH_LOOK_LEFT = 286,
		INPUT_VEH_LOOK_RIGHT = 287,
		INPUT_REPLAY_START_STOP_RECORDING = 288,
		INPUT_REPLAY_START_STOP_RECORDING_SECONDARY = 289,
		INPUT_SCALED_LOOK_LR = 290,
		INPUT_SCALED_LOOK_UD = 291,
		INPUT_SCALED_LOOK_UP_ONLY = 292,
		INPUT_SCALED_LOOK_DOWN_ONLY = 293,
		INPUT_SCALED_LOOK_LEFT_ONLY = 294,
		INPUT_SCALED_LOOK_RIGHT_ONLY = 295,
		INPUT_REPLAY_MARKER_DELETE = 296,
		INPUT_REPLAY_CLIP_DELETE = 297,
		INPUT_REPLAY_PAUSE = 298,
		INPUT_REPLAY_REWIND = 299,
		INPUT_REPLAY_FFWD = 300,
		INPUT_REPLAY_NEWMARKER = 301,
		INPUT_REPLAY_RECORD = 302,
		INPUT_REPLAY_SCREENSHOT = 303,
		INPUT_REPLAY_HIDEHUD = 304,
		INPUT_REPLAY_STARTPOINT = 305,
		INPUT_REPLAY_ENDPOINT = 306,
		INPUT_REPLAY_ADVANCE = 307,
		INPUT_REPLAY_BACK = 308,
		INPUT_REPLAY_TOOLS = 309,
		INPUT_REPLAY_RESTART = 310,
		INPUT_REPLAY_SHOWHOTKEY = 311,
		INPUT_REPLAY_CYCLEMARKERLEFT = 312,
		INPUT_REPLAY_CYCLEMARKERRIGHT = 313,
		INPUT_REPLAY_FOVINCREASE = 314,
		INPUT_REPLAY_FOVDECREASE = 315,
		INPUT_REPLAY_CAMERAUP = 316,
		INPUT_REPLAY_CAMERADOWN = 317,
		INPUT_REPLAY_SAVE = 318,
		INPUT_REPLAY_TOGGLETIME = 319,
		INPUT_REPLAY_TOGGLETIPS = 320,
		INPUT_REPLAY_PREVIEW = 321,
		INPUT_REPLAY_TOGGLE_TIMELINE = 322,
		INPUT_REPLAY_TIMELINE_PICKUP_CLIP = 323,
		INPUT_REPLAY_TIMELINE_DUPLICATE_CLIP = 324,
		INPUT_REPLAY_TIMELINE_PLACE_CLIP = 325,
		INPUT_REPLAY_CTRL = 326,
		INPUT_REPLAY_TIMELINE_SAVE = 327,
		INPUT_REPLAY_PREVIEW_AUDIO = 328,
		INPUT_VEH_DRIVE_LOOK = 329,
		INPUT_VEH_DRIVE_LOOK2 = 330,
		INPUT_VEH_FLY_ATTACK2 = 331,
		INPUT_RADIO_WHEEL_UD = 332,
		INPUT_RADIO_WHEEL_LR = 333,
		INPUT_VEH_SLOWMO_UD = 334,
		INPUT_VEH_SLOWMO_UP_ONLY = 335,
		INPUT_VEH_SLOWMO_DOWN_ONLY = 336,
		INPUT_MAP_POI = 337
	};
	enum eControl
	{
		ControlNextCamera = 0,
		ControlLookLeftRight = 1,
		ControlLookUpDown = 2,
		ControlLookUpOnly = 3,
		ControlLookDownOnly = 4,
		ControlLookLeftOnly = 5,
		ControlLookRightOnly = 6,
		ControlCinematicSlowMo = 7,
		ControlFlyUpDown = 8,
		ControlFlyLeftRight = 9,
		ControlScriptedFlyZUp = 10,
		ControlScriptedFlyZDown = 11,
		ControlWeaponWheelUpDown = 12,
		ControlWeaponWheelLeftRight = 13,
		ControlWeaponWheelNext = 14,
		ControlWeaponWheelPrev = 15,
		ControlSelectNextWeapon = 16,
		ControlSelectPrevWeapon = 17,
		ControlSkipCutscene = 18,
		ControlCharacterWheel = 19,
		ControlMultiplayerInfo = 20,
		ControlSprint = 21,
		ControlJump = 22,
		ControlEnter = 23,
		ControlAttack = 24,
		ControlAim = 25,
		ControlLookBehind = 26,
		ControlPhone = 27,
		ControlSpecialAbility = 28,
		ControlSpecialAbilitySecondary = 29,
		ControlMoveLeftRight = 30,
		ControlMoveUpDown = 31,
		ControlMoveUpOnly = 32,
		ControlMoveDownOnly = 33,
		ControlMoveLeftOnly = 34,
		ControlMoveRightOnly = 35,
		ControlDuck = 36,
		ControlSelectWeapon = 37,
		ControlPickup = 38,
		ControlSniperZoom = 39,
		ControlSniperZoomInOnly = 40,
		ControlSniperZoomOutOnly = 41,
		ControlSniperZoomInSecondary = 42,
		ControlSniperZoomOutSecondary = 43,
		ControlCover = 44,
		ControlReload = 45,
		ControlTalk = 46,
		ControlDetonate = 47,
		ControlHUDSpecial = 48,
		ControlArrest = 49,
		ControlAccurateAim = 50,
		ControlContext = 51,
		ControlContextSecondary = 52,
		ControlWeaponSpecial = 53,
		ControlWeaponSpecial2 = 54,
		ControlDive = 55,
		ControlDropWeapon = 56,
		ControlDropAmmo = 57,
		ControlThrowGrenade = 58,
		ControlVehicleMoveLeftRight = 59,
		ControlVehicleMoveUpDown = 60,
		ControlVehicleMoveUpOnly = 61,
		ControlVehicleMoveDownOnly = 62,
		ControlVehicleMoveLeftOnly = 63,
		ControlVehicleMoveRightOnly = 64,
		ControlVehicleSpecial = 65,
		ControlVehicleGunLeftRight = 66,
		ControlVehicleGunUpDown = 67,
		ControlVehicleAim = 68,
		ControlVehicleAttack = 69,
		ControlVehicleAttack2 = 70,
		ControlVehicleAccelerate = 71,
		ControlVehicleBrake = 72,
		ControlVehicleDuck = 73,
		ControlVehicleHeadlight = 74,
		ControlVehicleExit = 75,
		ControlVehicleHandbrake = 76,
		ControlVehicleHotwireLeft = 77,
		ControlVehicleHotwireRight = 78,
		ControlVehicleLookBehind = 79,
		ControlVehicleCinCam = 80,
		ControlVehicleNextRadio = 81,
		ControlVehiclePrevRadio = 82,
		ControlVehicleNextRadioTrack = 83,
		ControlVehiclePrevRadioTrack = 84,
		ControlVehicleRadioWheel = 85,
		ControlVehicleHorn = 86,
		ControlVehicleFlyThrottleUp = 87,
		ControlVehicleFlyThrottleDown = 88,
		ControlVehicleFlyYawLeft = 89,
		ControlVehicleFlyYawRight = 90,
		ControlVehiclePassengerAim = 91,
		ControlVehiclePassengerAttack = 92,
		ControlVehicleSpecialAbilityFranklin = 93,
		ControlVehicleStuntUpDown = 94,
		ControlVehicleCinematicUpDown = 95,
		ControlVehicleCinematicUpOnly = 96,
		ControlVehicleCinematicDownOnly = 97,
		ControlVehicleCinematicLeftRight = 98,
		ControlVehicleSelectNextWeapon = 99,
		ControlVehicleSelectPrevWeapon = 100,
		ControlVehicleRoof = 101,
		ControlVehicleJump = 102,
		ControlVehicleGrapplingHook = 103,
		ControlVehicleShuffle = 104,
		ControlVehicleDropProjectile = 105,
		ControlVehicleMouseControlOverride = 106,
		ControlVehicleFlyRollLeftRight = 107,
		ControlVehicleFlyRollLeftOnly = 108,
		ControlVehicleFlyRollRightOnly = 109,
		ControlVehicleFlyPitchUpDown = 110,
		ControlVehicleFlyPitchUpOnly = 111,
		ControlVehicleFlyPitchDownOnly = 112,
		ControlVehicleFlyUnderCarriage = 113,
		ControlVehicleFlyAttack = 114,
		ControlVehicleFlySelectNextWeapon = 115,
		ControlVehicleFlySelectPrevWeapon = 116,
		ControlVehicleFlySelectTargetLeft = 117,
		ControlVehicleFlySelectTargetRight = 118,
		ControlVehicleFlyVerticalFlightMode = 119,
		ControlVehicleFlyDuck = 120,
		ControlVehicleFlyAttackCamera = 121,
		ControlVehicleFlyMouseControlOverride = 122,
		ControlVehicleSubTurnLeftRight = 123,
		ControlVehicleSubTurnLeftOnly = 124,
		ControlVehicleSubTurnRightOnly = 125,
		ControlVehicleSubPitchUpDown = 126,
		ControlVehicleSubPitchUpOnly = 127,
		ControlVehicleSubPitchDownOnly = 128,
		ControlVehicleSubThrottleUp = 129,
		ControlVehicleSubThrottleDown = 130,
		ControlVehicleSubAscend = 131,
		ControlVehicleSubDescend = 132,
		ControlVehicleSubTurnHardLeft = 133,
		ControlVehicleSubTurnHardRight = 134,
		ControlVehicleSubMouseControlOverride = 135,
		ControlVehiclePushbikePedal = 136,
		ControlVehiclePushbikeSprint = 137,
		ControlVehiclePushbikeFrontBrake = 138,
		ControlVehiclePushbikeRearBrake = 139,
		ControlMeleeAttackLight = 140,
		ControlMeleeAttackHeavy = 141,
		ControlMeleeAttackAlternate = 142,
		ControlMeleeBlock = 143,
		ControlParachuteDeploy = 144,
		ControlParachuteDetach = 145,
		ControlParachuteTurnLeftRight = 146,
		ControlParachuteTurnLeftOnly = 147,
		ControlParachuteTurnRightOnly = 148,
		ControlParachutePitchUpDown = 149,
		ControlParachutePitchUpOnly = 150,
		ControlParachutePitchDownOnly = 151,
		ControlParachuteBrakeLeft = 152,
		ControlParachuteBrakeRight = 153,
		ControlParachuteSmoke = 154,
		ControlParachutePrecisionLanding = 155,
		ControlMap = 156,
		ControlSelectWeaponUnarmed = 157,
		ControlSelectWeaponMelee = 158,
		ControlSelectWeaponHandgun = 159,
		ControlSelectWeaponShotgun = 160,
		ControlSelectWeaponSmg = 161,
		ControlSelectWeaponAutoRifle = 162,
		ControlSelectWeaponSniper = 163,
		ControlSelectWeaponHeavy = 164,
		ControlSelectWeaponSpecial = 165,
		ControlSelectCharacterMichael = 166,
		ControlSelectCharacterFranklin = 167,
		ControlSelectCharacterTrevor = 168,
		ControlSelectCharacterMultiplayer = 169,
		ControlSaveReplayClip = 170,
		ControlSpecialAbilityPC = 171,
		ControlPhoneUp = 172,
		ControlPhoneDown = 173,
		ControlPhoneLeft = 174,
		ControlPhoneRight = 175,
		ControlPhoneSelect = 176,
		ControlPhoneCancel = 177,
		ControlPhoneOption = 178,
		ControlPhoneExtraOption = 179,
		ControlPhoneScrollForward = 180,
		ControlPhoneScrollBackward = 181,
		ControlPhoneCameraFocusLock = 182,
		ControlPhoneCameraGrid = 183,
		ControlPhoneCameraSelfie = 184,
		ControlPhoneCameraDOF = 185,
		ControlPhoneCameraExpression = 186,
		ControlFrontendDown = 187,
		ControlFrontendUp = 188,
		ControlFrontendLeft = 189,
		ControlFrontendRight = 190,
		ControlFrontendRdown = 191,
		ControlFrontendRup = 192,
		ControlFrontendRleft = 193,
		ControlFrontendRright = 194,
		ControlFrontendAxisX = 195,
		ControlFrontendAxisY = 196,
		ControlFrontendRightAxisX = 197,
		ControlFrontendRightAxisY = 198,
		ControlFrontendPause = 199,
		ControlFrontendPauseAlternate = 200,
		ControlFrontendAccept = 201,
		ControlFrontendCancel = 202,
		ControlFrontendX = 203,
		ControlFrontendY = 204,
		ControlFrontendLb = 205,
		ControlFrontendRb = 206,
		ControlFrontendLt = 207,
		ControlFrontendRt = 208,
		ControlFrontendLs = 209,
		ControlFrontendRs = 210,
		ControlFrontendLeaderboard = 211,
		ControlFrontendSocialClub = 212,
		ControlFrontendSocialClubSecondary = 213,
		ControlFrontendDelete = 214,
		ControlFrontendEndscreenAccept = 215,
		ControlFrontendEndscreenExpand = 216,
		ControlFrontendSelect = 217,
		ControlScriptLeftAxisX = 218,
		ControlScriptLeftAxisY = 219,
		ControlScriptRightAxisX = 220,
		ControlScriptRightAxisY = 221,
		ControlScriptRUp = 222,
		ControlScriptRDown = 223,
		ControlScriptRLeft = 224,
		ControlScriptRRight = 225,
		ControlScriptLB = 226,
		ControlScriptRB = 227,
		ControlScriptLT = 228,
		ControlScriptRT = 229,
		ControlScriptLS = 230,
		ControlScriptRS = 231,
		ControlScriptPadUp = 232,
		ControlScriptPadDown = 233,
		ControlScriptPadLeft = 234,
		ControlScriptPadRight = 235,
		ControlScriptSelect = 236,
		ControlCursorAccept = 237,
		ControlCursorCancel = 238,
		ControlCursorX = 239,
		ControlCursorY = 240,
		ControlCursorScrollUp = 241,
		ControlCursorScrollDown = 242,
		ControlEnterCheatCode = 243,
		ControlInteractionMenu = 244,
		ControlMpTextChatAll = 245,
		ControlMpTextChatTeam = 246,
		ControlMpTextChatFriends = 247,
		ControlMpTextChatCrew = 248,
		ControlPushToTalk = 249,
		ControlCreatorLS = 250,
		ControlCreatorRS = 251,
		ControlCreatorLT = 252,
		ControlCreatorRT = 253,
		ControlCreatorMenuToggle = 254,
		ControlCreatorAccept = 255,
		ControlCreatorDelete = 256,
		ControlAttack2 = 257,
		ControlRappelJump = 258,
		ControlRappelLongJump = 259,
		ControlRappelSmashWindow = 260,
		ControlPrevWeapon = 261,
		ControlNextWeapon = 262,
		ControlMeleeAttack1 = 263,
		ControlMeleeAttack2 = 264,
		ControlWhistle = 265,
		ControlMoveLeft = 266,
		ControlMoveRight = 267,
		ControlMoveUp = 268,
		ControlMoveDown = 269,
		ControlLookLeft = 270,
		ControlLookRight = 271,
		ControlLookUp = 272,
		ControlLookDown = 273,
		ControlSniperZoomIn = 274,
		ControlSniperZoomOut = 275,
		ControlSniperZoomInAlternate = 276,
		ControlSniperZoomOutAlternate = 277,
		ControlVehicleMoveLeft = 278,
		ControlVehicleMoveRight = 279,
		ControlVehicleMoveUp = 280,
		ControlVehicleMoveDown = 281,
		ControlVehicleGunLeft = 282,
		ControlVehicleGunRight = 283,
		ControlVehicleGunUp = 284,
		ControlVehicleGunDown = 285,
		ControlVehicleLookLeft = 286,
		ControlVehicleLookRight = 287,
		ControlReplayStartStopRecording = 288,
		ControlReplayStartStopRecordingSecondary = 289,
		ControlScaledLookLeftRight = 290,
		ControlScaledLookUpDown = 291,
		ControlScaledLookUpOnly = 292,
		ControlScaledLookDownOnly = 293,
		ControlScaledLookLeftOnly = 294,
		ControlScaledLookRightOnly = 295,
		ControlReplayMarkerDelete = 296,
		ControlReplayClipDelete = 297,
		ControlReplayPause = 298,
		ControlReplayRewind = 299,
		ControlReplayFfwd = 300,
		ControlReplayNewmarker = 301,
		ControlReplayRecord = 302,
		ControlReplayScreenshot = 303,
		ControlReplayHidehud = 304,
		ControlReplayStartpoint = 305,
		ControlReplayEndpoint = 306,
		ControlReplayAdvance = 307,
		ControlReplayBack = 308,
		ControlReplayTools = 309,
		ControlReplayRestart = 310,
		ControlReplayShowhotkey = 311,
		ControlReplayCycleMarkerLeft = 312,
		ControlReplayCycleMarkerRight = 313,
		ControlReplayFOVIncrease = 314,
		ControlReplayFOVDecrease = 315,
		ControlReplayCameraUp = 316,
		ControlReplayCameraDown = 317,
		ControlReplaySave = 318,
		ControlReplayToggletime = 319,
		ControlReplayToggletips = 320,
		ControlReplayPreview = 321,
		ControlReplayToggleTimeline = 322,
		ControlReplayTimelinePickupClip = 323,
		ControlReplayTimelineDuplicateClip = 324,
		ControlReplayTimelinePlaceClip = 325,
		ControlReplayCtrl = 326,
		ControlReplayTimelineSave = 327,
		ControlReplayPreviewAudio = 328,
		ControlVehicleDriveLook = 329,
		ControlVehicleDriveLook2 = 330,
		ControlVehicleFlyAttack2 = 331,
		ControlRadioWheelUpDown = 332,
		ControlRadioWheelLeftRight = 333,
		ControlVehicleSlowMoUpDown = 334,
		ControlVehicleSlowMoUpOnly = 335,
		ControlVehicleSlowMoDownOnly = 336,
		ControlMapPointOfInterest = 337,
	};
	struct Rectangle
	{
		Vector2 m_Center;
		Vector2 m_Size;

		bool IsInBounds(Vector2 point)
		{
			auto left = m_Center.x - (m_Size.x / 2.f);
			auto right = m_Center.x + (m_Size.x / 2.f);
			auto top = m_Center.y + (m_Size.y / 2.f);
			auto bottom = m_Center.y - (m_Size.y / 2.f);

			if (point.x > right || point.x < left)
				return false;
			if (point.y > top || point.y < bottom)
				return false;

			return true;
		}
	};
	inline bool bars = false;
	inline bool show_positions = false;
	inline bool show_max = false;
	inline bool FileExists(const std::string& fileName);
	void GET_YTD(std::string name);
	void GET_YTDFullTheme(std::string name);
	inline std::vector<std::string> m_YTDNames;
	inline std::vector<std::string> m_YTDNamesFull;
	std::vector<std::string> YTDLister();
	std::vector<std::string> YTDListerFullTheme();



	inline std::string m_YTDName{ "Virtual_X_T" };
	inline std::string m_PNGName;

	inline std::string FullHeaderName{ "Virtual_X_T" };

	class UIManager
	{
	public:
		explicit UIManager() = default;
		~UIManager() noexcept = default;
		UIManager(UIManager const&) = delete;
		UIManager(UIManager&&) = delete;
		UIManager& operator=(UIManager const&) = delete;
		UIManager& operator=(UIManager&&) = delete;

		template <typename SubmenuType, typename ...TArgs>
		void AddSubmenu(TArgs&&... args)
		{
			auto sub = std::make_unique<SubmenuType>(std::forward<TArgs>(args)...);
			if (m_SubmenuStack.empty())
			{
				m_SubmenuStack.push(sub.get());
			}

			m_AllSubmenus.push_back(std::move(sub));
		}

		void SwitchToSubmenu(std::uint32_t id)
		{
			for (auto&& sub : m_AllSubmenus)
			{
				if (sub->GetId() == id)
				{
					m_SubmenuStack.push(sub.get());
					return;
				}
			}
		}
		float m_delta = 0.f;
		void OnTick();
	public:
		std::mutex m_Mutex;
		bool m_ImGuiActive = false;
		bool m_Opened = false;
		bool TextKek{ true };
		std::string textkek{ "BigBase" };
		bool m_MouseLocked = false;
		float m_PosX = g_Settings.m_Options["m_PosX"].get<float>();
		float m_PosY = g_Settings.m_Options["m_PosY"].get<float>();
		float m_Width = g_Settings.m_Options["m_Width"].get<float>();
		std::size_t m_OptionsPerPage = 14;
		bool m_Sounds = true;
		bool m_Controllerinput = true;
		bool g_XFThemes = false;

		// Input
		std::int32_t m_OpenDelay = g_Settings.m_Options["m_OpenDelay"].get<std::int32_t>();
		std::int32_t m_BackDelay = g_Settings.m_Options["m_BackDelay"].get<std::int32_t>();
		std::int32_t m_EnterDelay = g_Settings.m_Options["m_EnterDelay"].get<std::int32_t>();
		std::int32_t m_VerticalDelay = g_Settings.m_Options["m_VerticalDelay"].get<std::int32_t>();
		std::int32_t m_HorizontalDelay = g_Settings.m_Options["m_HorizontalDelay"].get<std::int32_t>();

		// Header
		float m_HeaderHeight = 0.120f;
		bool m_HeaderText = true;
		float m_HeaderTextSize = 1.40f;
		Font m_HeaderFont = Font::HouseScript;
		Color m_HeaderBackgroundColor{ 61,234,102, 255 };
		Color m_HeaderTextColor{ 255, 255, 255, 255 };
		HeaderType m_HeaderType = HeaderType::Static;

		bool m_Smoothscroll{ g_Settings.m_Options["m_Smoothscroll"].get<bool>() };

		bool m_HeaderGradientTransparent = g_Settings.m_Options["m_HeaderGradientTransparent"].get<bool>();
		bool m_HeaderGradientFlip = g_Settings.m_Options["m_HeaderGradientFlip"].get<bool>();
		float m_HeaderGradientStretch = g_Settings.m_Options["m_HeaderGradientStretch"].get<float>();
		float m_HeaderGradientFiller = g_Settings.m_Options["m_HeaderGradientFiller"].get<float>();
		Color m_HeaderGradientColorRight{ g_Settings.m_Options["m_HeaderGradientColorRight.r"].get<int>(), g_Settings.m_Options["m_HeaderGradientColorRight.g"].get<int>(), g_Settings.m_Options["m_HeaderGradientColorRight.b"].get<int>(), g_Settings.m_Options["m_HeaderGradientColorRight.a"].get<int>() };
		Color m_HeaderGradientColorLeft{ g_Settings.m_Options["m_HeaderGradientColorLeft.r"].get<int>(), g_Settings.m_Options["m_HeaderGradientColorLeft.g"].get<int>(), g_Settings.m_Options["m_HeaderGradientColorLeft.b"].get<int>(), g_Settings.m_Options["m_HeaderGradientColorLeft.a"].get<int>() };

		// Submenu bar
		float m_SubmenuBarHeight = 0.030f;
		float m_SubmenuBarTextSize = 0.30f;
		Font m_SubmenuBarFont = Font::ChaletLondon;
		float m_SubmenuBarPadding = 2.1f;
		Color m_SubmenuBarBackgroundColor{ 0, 0, 0, 255 };
		Color m_SubmenuBarTextColor{ 255, 255, 255, 255 };
		bool m_ShowSubmenubar = true;
		bool m_ShowScrollbar = false;
		bool m_lineactivate = false;
		bool m_ShowScrollbar2 = true;
		bool m_description1 = true;
		bool footerload = false;
		bool loadscroller = false;
		bool submenubarload = false;
		bool g_FullThemeLoading{ false };
		bool loadtoggle = { true };
		bool ath = true;
		Color m_separatorcolor{ 61,234,102,255 };
		// Options
		float m_OptionHeight = g_Settings.m_Options["m_OptionHeight"].get<float>();
		float m_OptionTextSize = g_Settings.m_Options["m_OptionTextSize"].get<float>();
		Font m_OptionFont = Font::ChaletLondon;
		float m_OptionPadding = g_Settings.m_Options["m_OptionPadding"].get<float>();
		Color m_OptionSelectedTextColor{ 0, 0, 0, 255 };
		Color m_OptionUnselectedTextColor{ g_Settings.m_Options["m_OptionUnselectedTextColor.r"].get<int>(), g_Settings.m_Options["m_OptionUnselectedTextColor.g"].get<int>(), g_Settings.m_Options["m_OptionUnselectedTextColor.b"].get<int>(), g_Settings.m_Options["m_OptionUnselectedTextColor.a"].get<int>() };
		Color m_OptionSelectedBackgroundColor{ 61,234,102,255 };
		Color m_OptionUnselectedBackgroundColor{ 0, 0, 0, 170 };

		float m_ToggleScale{ g_Settings.m_Options["m_ToggleScale"].get<float>() };
		Color m_SelectedToggle{ g_Settings.m_Options["m_SelectedToggle.r"].get<int>(), g_Settings.m_Options["m_SelectedToggle.g"].get<int>(), g_Settings.m_Options["m_SelectedToggle.b"].get<int>(), g_Settings.m_Options["m_SelectedToggle.a"].get<int>() };
		Color m_UnselectedToggle{ g_Settings.m_Options["m_UnselectedToggle.r"].get<int>(), g_Settings.m_Options["m_UnselectedToggle.g"].get<int>(), g_Settings.m_Options["m_UnselectedToggle.b"].get<int>(), g_Settings.m_Options["m_UnselectedToggle.a"].get<int>() };

		// Footer
		float m_FooterHeight = 0.030f;
		float m_FooterSpriteSize = 0.025f;
		Color m_FooterBackgroundColor{ 0, 0, 0, 255 };
		Color m_FooterSpriteColor{ 255, 255, 255, 255 };
		Color m_linecolor{ 61,234,102,255 };
		Color m_scrollbarcolor{ 0,255,255,255 };
		// Description
		float m_DescriptionHeightPadding = 0.01f;
		float m_DescriptionHeight = 0.033f;
		float m_DescriptionTextSize = 0.28f;
		Font m_DescriptionFont = Font::ChaletLondon;
		Color m_DescriptionBackgroundColor{ 0, 0, 0, 170 };
		Color m_DescriptionTextColor{ 255, 255, 255, 255 };
		float m_DescriptionSpriteSize = 0.025f;
		float m_DescriptionPadding = 1.9f;
		Color m_DescriptionSpriteColor{ 255, 255, 255, 255 };

		float right_text_offset = 0.0;


		// Smooth Scroll
		int minusOpacity = 0;
		float m_ScrollSpeed = g_Settings.m_Options["m_ScrollSpeed"].get<float>();

		inline float get_normalized_font_scale(int font, float scale);
		inline float calculate_string_width(std::string string, int font, float scale);

		const char* ToggleList[3]
		{
			"Checkmarks",
			"Circle",
			"Text"
		};
		std::size_t ToggleIterator = g_Settings.m_Options["ToggleIterator"].get<std::size_t>();

		const char* IndicatorList[4]
		{
			"Arrows HUD",
			"Arrows",
			"Lines",
			"None"
		};
		std::size_t IndicatorIterator = g_Settings.m_Options["IndicatorIterator"].get<std::size_t>();

		void LoadTheme(const char* str)
		{
			std::string path = g_Settings.appdatapath + "\\Themes\\" + static_cast<std::string>(str) + ".json";
			std::ifstream file(path);
			if (!std::filesystem::exists(path))
			{
				LOG(INFO) << "Failed to load " << str;
				LOG(INFO) << "Loading default settings...";
				g_Settings.Initialize();
			}
			LOG(INFO) << "Loading " << str;
			file >> g_Settings.m_Options;

			for (auto& e : g_Settings.m_Options.items())
			{
				if (g_Settings.m_Options.count(e.key()) == 0)
				{
					path = true;
					g_Settings.m_Options[e.key()] = e.value();
				}
			}

			// Input
			m_OpenDelay = g_Settings.m_Options["m_OpenDelay"].get<std::int32_t>();
			m_BackDelay = g_Settings.m_Options["m_BackDelay"].get<std::int32_t>();
			m_EnterDelay = g_Settings.m_Options["m_EnterDelay"].get<std::int32_t>();
			m_VerticalDelay = g_Settings.m_Options["m_VerticalDelay"].get<std::int32_t>();
			m_HorizontalDelay = g_Settings.m_Options["m_HorizontalDelay"].get<std::int32_t>();

			// Header
			m_HeaderHeight = g_Settings.m_Options["m_HeaderHeight"].get<float>();
			m_HeaderText = g_Settings.m_Options["m_HeaderText"].get<bool>();
			m_HeaderTextSize = g_Settings.m_Options["m_HeaderTextSize"].get<float>();
			m_HeaderFont = Font::HouseScript;
			m_HeaderBackgroundColor = { g_Settings.m_Options["m_HeaderBackgroundColor.r"].get<int>(), g_Settings.m_Options["m_HeaderBackgroundColor.g"].get<int>(), g_Settings.m_Options["m_HeaderBackgroundColor.b"].get<int>(), g_Settings.m_Options["m_HeaderBackgroundColor.a"].get<int>() };
			m_HeaderTextColor = { g_Settings.m_Options["m_HeaderTextColor.r"].get<int>(), g_Settings.m_Options["m_HeaderTextColor.g"].get<int>(), g_Settings.m_Options["m_HeaderTextColor.b"].get<int>(), g_Settings.m_Options["m_HeaderTextColor.a"].get<int>() };


			m_HeaderGradientTransparent = g_Settings.m_Options["m_HeaderGradientTransparent"].get<float>();
			m_HeaderGradientFlip = g_Settings.m_Options["m_HeaderGradientFlip"].get<float>();
			m_HeaderGradientStretch = g_Settings.m_Options["m_HeaderGradientStretch"].get<float>();
			m_HeaderGradientFiller = g_Settings.m_Options["m_HeaderGradientFiller"].get<float>();
			m_HeaderGradientColorRight = { g_Settings.m_Options["m_HeaderGradientColorRight.r"].get<int>(), g_Settings.m_Options["m_HeaderGradientColorRight.g"].get<int>(), g_Settings.m_Options["m_HeaderGradientColorRight.b"].get<int>(), g_Settings.m_Options["m_HeaderGradientColorRight.a"].get<int>() };
			m_HeaderGradientColorLeft = { g_Settings.m_Options["m_HeaderGradientColorLeft.r"].get<int>(), g_Settings.m_Options["m_HeaderGradientColorLeft.g"].get<int>(), g_Settings.m_Options["m_HeaderGradientColorLeft.b"].get<int>(), g_Settings.m_Options["m_HeaderGradientColorLeft.a"].get<int>() };

			// Submenu bar
			m_SubmenuBarHeight = g_Settings.m_Options["m_SubmenuBarHeight"].get<float>();
			m_SubmenuBarTextSize = g_Settings.m_Options["m_SubmenuBarTextSize"].get<float>();
			m_SubmenuBarFont = Font::ChaletLondon;
			m_SubmenuBarPadding = g_Settings.m_Options["m_SubmenuBarPadding"].get<float>();
			m_SubmenuBarBackgroundColor = { g_Settings.m_Options["m_SubmenuBarBackgroundColor.r"].get<int>(), g_Settings.m_Options["m_SubmenuBarBackgroundColor.g"].get<int>(), g_Settings.m_Options["m_SubmenuBarBackgroundColor.b"].get<int>(), g_Settings.m_Options["m_SubmenuBarBackgroundColor.a"].get<int>() };
			m_SubmenuBarTextColor = { g_Settings.m_Options["m_SubmenuBarTextColor.r"].get<int>(), g_Settings.m_Options["m_SubmenuBarTextColor.g"].get<int>(), g_Settings.m_Options["m_SubmenuBarTextColor.b"].get<int>(), g_Settings.m_Options["m_SubmenuBarTextColor.a"].get<int>() };
			m_ShowSubmenubar = g_Settings.m_Options["m_ShowSubmenubar"].get<bool>();

			// Options
			m_OptionHeight = g_Settings.m_Options["m_OptionHeight"].get<float>();
			m_OptionTextSize = g_Settings.m_Options["m_OptionTextSize"].get<float>();
			m_OptionFont = Font::ChaletLondon;
			m_OptionPadding = g_Settings.m_Options["m_OptionPadding"].get<float>();
			m_OptionSelectedTextColor = { g_Settings.m_Options["m_OptionUnselectedTextColor.r"].get<int>(), g_Settings.m_Options["m_OptionUnselectedTextColor.g"].get<int>(), g_Settings.m_Options["m_OptionUnselectedTextColor.b"].get<int>(), g_Settings.m_Options["m_OptionUnselectedTextColor.a"].get<int>() };
			m_OptionUnselectedTextColor = { g_Settings.m_Options["m_OptionUnselectedTextColor.r"].get<int>(), g_Settings.m_Options["m_OptionUnselectedTextColor.g"].get<int>(), g_Settings.m_Options["m_OptionUnselectedTextColor.b"].get<int>(), g_Settings.m_Options["m_OptionUnselectedTextColor.a"].get<int>() };
			m_OptionSelectedBackgroundColor = { 0, 128, 128, 255 };
			m_OptionUnselectedBackgroundColor = { 0, 128, 128, 170 };

			m_ToggleScale = { g_Settings.m_Options["m_ToggleScale"].get<float>() };
			m_SelectedToggle = { g_Settings.m_Options["m_SelectedToggle.r"].get<int>(), g_Settings.m_Options["m_SelectedToggle.g"].get<int>(), g_Settings.m_Options["m_SelectedToggle.b"].get<int>(), g_Settings.m_Options["m_SelectedToggle.a"].get<int>() };
			m_UnselectedToggle = { g_Settings.m_Options["m_UnselectedToggle.r"].get<int>(), g_Settings.m_Options["m_UnselectedToggle.g"].get<int>(), g_Settings.m_Options["m_UnselectedToggle.b"].get<int>(), g_Settings.m_Options["m_UnselectedToggle.a"].get<int>() };
			//Line
			m_linecolor = { g_Settings.m_Options["m_linecolor.r"].get<int>(), g_Settings.m_Options["m_linecolor.g"].get<int>(), g_Settings.m_Options["m_linecolor.b"].get<int>(), g_Settings.m_Options["m_linecolor.a"].get<int>() };
			m_ShowScrollbar = g_Settings.m_Options["m_ShowScrollbar"].get<bool>();
			m_ShowScrollbar2 = g_Settings.m_Options["m_ShowScrollbar2"].get<bool>();
			m_lineactivate = g_Settings.m_Options["m_lineactivate"].get<bool>();

			bool m_lineactivate = true;

			// Footer
			m_FooterHeight = g_Settings.m_Options["m_FooterSpriteSize"].get<float>();
			m_FooterSpriteSize = g_Settings.m_Options["m_FooterSpriteSize"].get<float>();
			m_FooterBackgroundColor = { g_Settings.m_Options["m_FooterBackgroundColor.r"].get<int>(), g_Settings.m_Options["m_FooterBackgroundColor.g"].get<int>(), g_Settings.m_Options["m_FooterBackgroundColor.b"].get<int>(), g_Settings.m_Options["m_FooterBackgroundColor.a"].get<int>() };
			m_FooterSpriteColor = { g_Settings.m_Options["m_FooterSpriteColor.r"].get<int>(), g_Settings.m_Options["m_FooterSpriteColor.g"].get<int>(), g_Settings.m_Options["m_FooterSpriteColor.b"].get<int>(), g_Settings.m_Options["m_FooterSpriteColor.a"].get<int>() };

			// Description
			m_DescriptionHeightPadding = g_Settings.m_Options["m_DescriptionHeightPadding"].get<float>();
			m_DescriptionHeight = g_Settings.m_Options["m_DescriptionHeight"].get<float>();
			m_DescriptionTextSize = g_Settings.m_Options["m_DescriptionTextSize"].get<float>();
			m_DescriptionFont = Font::ChaletLondon;
			m_DescriptionBackgroundColor = { g_Settings.m_Options["m_FooterSpriteColor.r"].get<int>(), g_Settings.m_Options["m_FooterSpriteColor.g"].get<int>(), g_Settings.m_Options["m_FooterSpriteColor.b"].get<int>(), g_Settings.m_Options["m_FooterSpriteColor.a"].get<int>() };
			m_DescriptionTextColor = { g_Settings.m_Options["m_FooterSpriteColor.r"].get<int>(), g_Settings.m_Options["m_FooterSpriteColor.g"].get<int>(), g_Settings.m_Options["m_FooterSpriteColor.b"].get<int>(), g_Settings.m_Options["m_FooterSpriteColor.a"].get<int>() };
			m_DescriptionSpriteSize = g_Settings.m_Options["m_DescriptionSpriteSize"].get<float>();
			m_DescriptionPadding = g_Settings.m_Options["m_DescriptionPadding"].get<float>();
			m_DescriptionSpriteColor = { g_Settings.m_Options["m_DescriptionSpriteColor.r"].get<int>(), g_Settings.m_Options["m_DescriptionSpriteColor.g"].get<int>(), g_Settings.m_Options["m_DescriptionSpriteColor.b"].get<int>(), g_Settings.m_Options["m_DescriptionSpriteColor.a"].get<int>() };

			ToggleIterator = g_Settings.m_Options["ToggleIterator"].get<std::size_t>();
			IndicatorIterator = g_Settings.m_Options["IndicatorIterator"].get<std::size_t>();

			m_Width = g_Settings.m_Options["m_Width"].get<float>();
			m_PosX = g_Settings.m_Options["m_PosX"].get<float>();
			m_PosY = g_Settings.m_Options["m_PosY"].get<float>();

			m_Smoothscroll = g_Settings.m_Options["m_Smoothscroll"].get<bool>();

			m_ScrollSpeed = g_Settings.m_Options["m_ScrollSpeed"].get<float>();
			//g_CustomText->AddText(CONSTEXPR_JOAAT("HUD_MAINTIT"), g_UiManager->textkek.c_str());
			LOG(INFO) << "Successfully loaded " << str;
		}

		void WriteNewConfig(std::string str)
		{
			nlohmann::json CurrentTheme
			{
				{ "m_OptionUnselectedTextColor.r", m_OptionUnselectedTextColor.r },
				{ "m_OptionUnselectedTextColor.g", m_OptionUnselectedTextColor.g },
				{ "m_OptionUnselectedTextColor.b", m_OptionUnselectedTextColor.b },
				{ "m_OptionUnselectedTextColor.a", m_OptionUnselectedTextColor.a },

				{ "m_linecolor.r" , m_linecolor.r },
				{ "m_linecolor.g" , m_linecolor.g },
				{ "m_linecolor.b" , m_linecolor.b },
				{ "m_linecolor.a" , m_linecolor.a },
				{ "m_ShowScrollbar" , m_ShowScrollbar },
				{ "m_ShowScrollbar2" , m_ShowScrollbar2 },
				{ "m_lineactivate" , m_lineactivate },

				{ "m_OptionSelectedTextColor.r", m_OptionSelectedTextColor.r },
				{ "m_OptionSelectedTextColor.g", m_OptionSelectedTextColor.g },
				{ "m_OptionSelectedTextColor.b", m_OptionSelectedTextColor.b },
				{ "m_OptionSelectedTextColor.a", m_OptionSelectedTextColor.a },

				{ "m_OptionUnselectedBackgroundColor.r", m_OptionUnselectedBackgroundColor.r },
				{ "m_OptionUnselectedBackgroundColor.g", m_OptionUnselectedBackgroundColor.g },
				{ "m_OptionUnselectedBackgroundColor.b", m_OptionUnselectedBackgroundColor.b },
				{ "m_OptionUnselectedBackgroundColor.a", m_OptionUnselectedBackgroundColor.a },

				{ "m_SubmenuBarTextColor.r", m_SubmenuBarTextColor.r },
				{ "m_SubmenuBarTextColor.g", m_SubmenuBarTextColor.g },
				{ "m_SubmenuBarTextColor.b", m_SubmenuBarTextColor.b },
				{ "m_SubmenuBarTextColor.a", m_SubmenuBarTextColor.a },

				{ "m_SubmenuBarBackgroundColor.r", m_SubmenuBarBackgroundColor.r },
				{ "m_SubmenuBarBackgroundColor.g", m_SubmenuBarBackgroundColor.g },
				{ "m_SubmenuBarBackgroundColor.b", m_SubmenuBarBackgroundColor.b },
				{ "m_SubmenuBarBackgroundColor.a", m_SubmenuBarBackgroundColor.a },

				{ "m_SelectedToggle.r", m_SelectedToggle.r },
				{ "m_SelectedToggle.g", m_SelectedToggle.g },
				{ "m_SelectedToggle.b", m_SelectedToggle.b },
				{ "m_SelectedToggle.a", m_SelectedToggle.a },

				{ "m_UnselectedToggle.r", m_UnselectedToggle.r },
				{ "m_UnselectedToggle.g", m_UnselectedToggle.g },
				{ "m_UnselectedToggle.b", m_UnselectedToggle.b },
				{ "m_UnselectedToggle.a", m_UnselectedToggle.a },

				{ "m_HeaderGradientColorLeft.r", m_HeaderGradientColorLeft.r },
				{ "m_HeaderGradientColorLeft.g", m_HeaderGradientColorLeft.g },
				{ "m_HeaderGradientColorLeft.b", m_HeaderGradientColorLeft.b },
				{ "m_HeaderGradientColorLeft.a", m_HeaderGradientColorLeft.a },

				{ "m_HeaderGradientColorRight.r", m_HeaderGradientColorRight.r },
				{ "m_HeaderGradientColorRight.g", m_HeaderGradientColorRight.g },
				{ "m_HeaderGradientColorRight.b", m_HeaderGradientColorRight.b },
				{ "m_HeaderGradientColorRight.a", m_HeaderGradientColorRight.a },

				{ "m_HeaderTextColor.r", m_HeaderTextColor.a },
				{ "m_HeaderTextColor.g", m_HeaderTextColor.g },
				{ "m_HeaderTextColor.b", m_HeaderTextColor.b },
				{ "m_HeaderTextColor.a", m_HeaderTextColor.a },

				{ "m_FooterSpriteColor.r", m_FooterSpriteColor.r },
				{ "m_FooterSpriteColor.g", m_FooterSpriteColor.g },
				{ "m_FooterSpriteColor.b", m_FooterSpriteColor.b },
				{ "m_FooterSpriteColor.a", m_FooterSpriteColor.a },

				{ "m_FooterBackgroundColor.r", m_FooterBackgroundColor.r },
				{ "m_FooterBackgroundColor.g", m_FooterBackgroundColor.g },
				{ "m_FooterBackgroundColor.b", m_FooterBackgroundColor.b },
				{ "m_FooterBackgroundColor.a", m_FooterBackgroundColor.a },

				{ "m_HeaderBackgroundColor.r", m_HeaderBackgroundColor.r },
				{ "m_HeaderBackgroundColor.g", m_HeaderBackgroundColor.g },
				{ "m_HeaderBackgroundColor.b", m_HeaderBackgroundColor.b },
				{ "m_HeaderBackgroundColor.a", m_HeaderBackgroundColor.a },

				{ "m_HeaderHeight", m_HeaderHeight },
				{ "m_SubmenuBarHeight", m_SubmenuBarHeight },
				{ "m_SubmenuBarTextSize", m_SubmenuBarTextSize },
				{ "m_SubmenuBarPadding", m_SubmenuBarPadding },

				{ "m_FooterSpriteSize", m_FooterSpriteSize },
				{ "m_FooterHeight", m_FooterHeight },
				{ "m_ToggleScale", m_ToggleScale },
				{ "m_HeaderGradientStretch", m_HeaderGradientStretch },
				{ "m_HeaderGradientFiller", m_HeaderGradientFiller },
				{ "m_OptionPadding", m_OptionPadding },
				{ "m_OptionTextSize", m_OptionTextSize },
				{ "m_OptionHeight", m_OptionHeight },
				{ "m_HeaderTextSize", m_HeaderTextSize },
				{ "m_HeaderText", m_HeaderText },
				{ "m_HeaderGradientTransparent", m_HeaderGradientTransparent },
				{ "m_HeaderGradientFlip", m_HeaderGradientFlip },
				{ "m_HeaderHeight", m_HeaderHeight },

				{ "m_OpenDelay", m_OpenDelay },
				{ "m_BackDelay", m_BackDelay },
				{ "m_EnterDelay", m_EnterDelay },
				{ "m_VerticalDelay", m_VerticalDelay },
				{ "m_HorizontalDelay", m_HorizontalDelay },
				{ "m_DescriptionHeightPadding", m_DescriptionHeightPadding },
				{ "m_DescriptionHeight", m_DescriptionHeight },
				{ "m_DescriptionTextSize", m_DescriptionTextSize },
				{ "m_DescriptionSpriteSize", m_DescriptionSpriteSize },
				{ "m_DescriptionPadding", m_DescriptionPadding },

				{ "m_DescriptionBackgroundColor.r", m_DescriptionBackgroundColor.r },
				{ "m_DescriptionBackgroundColor.g", m_DescriptionBackgroundColor.g },
				{ "m_DescriptionBackgroundColor.b", m_DescriptionBackgroundColor.b },
				{ "m_DescriptionBackgroundColor.a", m_DescriptionBackgroundColor.a },

				{ "m_DescriptionTextColor.r", m_DescriptionTextColor.r },
				{ "m_DescriptionTextColor.g", m_DescriptionTextColor.g },
				{ "m_DescriptionTextColor.b", m_DescriptionTextColor.b },
				{ "m_DescriptionTextColor.a", m_DescriptionTextColor.a },

				{ "m_DescriptionSpriteColor.r", m_DescriptionSpriteColor.r },
				{ "m_DescriptionSpriteColor.g", m_DescriptionSpriteColor.g },
				{ "m_DescriptionSpriteColor.b", m_DescriptionSpriteColor.b },
				{ "m_DescriptionSpriteColor.a", m_DescriptionSpriteColor.a },

				{ "m_PosX", m_PosX },
				{ "m_PosY", m_PosY },
				{ "m_Width", m_Width },

				{ "m_ShowSubmenubar", m_ShowSubmenubar },
				{ "ToggleIterator", ToggleIterator },
				{ "IndicatorIterator", IndicatorIterator },

				{ "m_Width", m_Width },
				{ "m_PosX", m_PosX },
				{ "m_PosY", m_PosY },

				{ "m_HeaderType", m_HeaderType },
				{ "m_Smoothscroll", m_Smoothscroll },
				{ "m_ScrollSpeed", m_ScrollSpeed }
			};

			std::string path = g_Settings.appdatapath + "\\Themes\\" + str + ".json";
			std::ofstream file(path, std::ios::out);

			file << CurrentTheme.dump(4);
			file.close();
			g_Settings.m_Options.clear();
			g_Settings.m_Options = CurrentTheme;
		}

		float m_DrawBaseY{};
		void Spriter(std::string Streamedtexture, std::string textureName, float x, float y, float width, float height, float rotation, int r, int g, int b, int a);
		float GetTextHeight(Font font, float size);
		std::stack<AbstractSubmenu*, std::vector<AbstractSubmenu*>> m_SubmenuStack;

		enum TextPosition
		{
			Left = 0,
			Right = 1,
			Center = 2,
		};
		void Text(TextPosition position, const char* text, float x, float y, float size, Font font, Color color, bool outline, bool shadow, bool wrap = false)
		{
			switch (position)
			{
			case TextPosition::Left:
			{
				HUD::SET_TEXT_SCALE(size, size);
				HUD::SET_TEXT_FONT(static_cast<int>(font));
				HUD::SET_TEXT_COLOUR(color.r, color.g, color.b, 255);
				if (outline)
					HUD::SET_TEXT_OUTLINE();
				if (shadow)
					HUD::SET_TEXT_DROP_SHADOW();
				if (wrap)
				{
				}
				HUD::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
				HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text);
				HUD::END_TEXT_COMMAND_DISPLAY_TEXT(x, y, 0);
				break;
			}
			case TextPosition::Right:
			{

				HUD::SET_TEXT_WRAP(0.f, x);
				HUD::SET_TEXT_RIGHT_JUSTIFY(true);
				HUD::SET_TEXT_SCALE(size, size);
				HUD::SET_TEXT_FONT(static_cast<int>(font));
				HUD::SET_TEXT_COLOUR(color.r, color.g, color.b, 255);
				if (outline)
					HUD::SET_TEXT_OUTLINE();
				if (shadow)
					HUD::SET_TEXT_DROP_SHADOW();
				if (wrap)
				{
				}
				HUD::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
				HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text);
				HUD::END_TEXT_COMMAND_DISPLAY_TEXT(x, y, 0);
				break;
			}
			case TextPosition::Center:
			{
				HUD::SET_TEXT_CENTRE(true);
				HUD::SET_TEXT_SCALE(size, size);
				HUD::SET_TEXT_FONT(static_cast<int>(font));
				HUD::SET_TEXT_COLOUR(color.r, color.g, color.b, 255);
				if (outline)
					HUD::SET_TEXT_OUTLINE();
				if (shadow)
					HUD::SET_TEXT_DROP_SHADOW();
				if (wrap)
				{
				}
				HUD::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
				HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text);
				HUD::END_TEXT_COMMAND_DISPLAY_TEXT(x, y, 0);
				break;
			}
			}
		}
	private:
		bool m_OpenKeyPressed = false;
		bool m_BackKeyPressed = false;
		bool m_EnterKeyPressed = false;
		bool m_UpKeyPressed = false;
		bool m_DownKeyPressed = false;
		bool m_LeftKeyPressed = false;
		bool m_RightKeyPressed = false;
		void CheckForInput();
		void HandleInput();
		void ResetInput();

		void DrawHeader(AbstractSubmenu* sub);
		void DrawSubmenuBar(AbstractSubmenu* sub);
		void DrawOption(AbstractOption* opt, AbstractSubmenu* sub, bool selected);
		void DrawFooter();
		void DrawDescription();

		void DrawRect(float x, float y, float width, float height, Color color);
		void DrawSprite(const char* dict, const char* texture, float x, float y, float width, float height, Color color, float rotation);
		void DrawLeftText(const char* text, float x, float y, float size, Font font, Color color, bool outline, bool shadow);
		void DrawCenteredText(const char* text, float x, float y, float size, Font font, Color color, bool outline, bool shadow);
		void DrawRightText(const char* text, float x, float y, float size, Font font, Color color, bool outline, bool shadow);
		Vector2 GetSpriteScale(float size);
		bool IsMouseLocked();
		Rectangle GetMenuRect();
		Vector2 GetMousePos();
		std::vector<std::unique_ptr<AbstractSubmenu>> m_AllSubmenus;
	};
}

namespace big
{
	inline std::unique_ptr<UserInterface::UIManager> g_UiManager;
}
class Ini
{
private:
	std::string inifile;
public:
	Ini(std::string file)
	{
		this->inifile = file;
	}

	void WriteString(std::string string, std::string app, std::string key)
	{
		WritePrivateProfileStringA(app.c_str(), key.c_str(), string.c_str(), this->inifile.c_str());
	}
	std::string GetString(std::string app, std::string key)
	{
		char buf[100];
		GetPrivateProfileStringA(app.c_str(), key.c_str(), "NULL", buf, 100, this->inifile.c_str());
		return (std::string)buf;
	}

	void WriteInt(int value, std::string app, std::string key)
	{
		WriteString(std::to_string(value), app, key);
	}
	int GetInt(std::string app, std::string key)
	{
		return std::stoi(GetString(app, key));
	}

	void WriteFloat(float value, std::string app, std::string key)
	{
		WriteString(std::to_string(value), app, key);
	}
	float GetFloat(std::string app, std::string key)
	{
		return std::stof(GetString(app, key));
	}

	void WriteBool(bool value, std::string app, std::string key)
	{
		WriteString(std::to_string(value), app, key);
	}
	float GetBool(std::string app, std::string key)
	{
		std::string Fetched = GetString(app, key);
		bool returned = (Fetched == "1");
		return returned;
	}

};