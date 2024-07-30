#pragma once

class CWaterTune
{
public:
	DWORD dwWaterColor; //0x0000  Default: 0x1A00191C
	float fRippleScale; //0x0004  Default: 0.040000f
	float fOceanFoamScale; //0x0008  Default: 0.050000f
	float fSpecularFalloff; //0x000C  Default: 1118.000000f
	float fFodPierceIntensity; //0x0010  Default: 1.100000f
	float fRefractionBlend; //0x0014  Default: 0.700000f
	float fRefractionExponent; //0x0018  Default: 0.250000f
	float fWaterCycleDepth; //0x001C  Default: 10.000000f
	float fWaterCycleFade; //0x0020  Default: 50.000000f
	float fWaterLightningDepth; //0x0024  Default: 0.000000f
	float fWaterLightningFade; //0x0028  Default: 10.000000f
	float fDeepWaterModDepth; //0x002C  Default: 90.000000f
	float fDeepWaterModFade; //0x0030  Default: 80.000000f
	float fGodRaysLerpStart; //0x0034  Default: 0.000000f
	float fGodRaysLerpEnd; //0x0038  Default: 200.000000f
	float fDisturbFoamScale; //0x003C  Default: 0.050000f
	void* vec2FogMin; //0x0040  Default: x = -4000.000000 y = -4000.000000
	void* vec2FogMax; //0x0048  Default: x = 4500.000000 y= 8000.000000
};

class CWaterDataItem
{
public:
	__int16 iMinX; //0x0000 X Coord 1
	__int16 iMinY; //0x0002  Y Coord 1
	__int16 iMaxX; //0x0004 X Coord 2
	__int16 iMaxY; //0x0006 Y Coord 2
	__int8 iAlphaSW; //0x0008  (South West, default 26)
	__int8 iAlphaSE; //0x0009  (South East, default 26)
	__int8 iAlphaNW; //0x000A  (North West, default 26)
	__int8 iAlphaNE; //0x000B  (North East, default 26)
	char _0x000C[8]; // (Unknown, appear to be two floats?)
	float fHeight; //0x0014 (Z-Height, default 0.0)
	BYTE bHasLimitedDepth; //0x0018  (Second bit [binary 10] = On, gives the water quad an effective range of 6 z-points)
	char _0x0019[3]; // (Unknown)
};//Size=0x001C

class ListPool {
public:
	std::uint64_t* list; //0x0000
	std::int32_t capacity; //0x0008
	char pad_000C[4]; //0x000C
	std::int32_t free; //0x0010
	char pad_0014[4]; //0x0014
	std::uint64_t item_size; //0x0018
	char pad_0020[16]; //0x0020
	std::uint32_t* data; //0x0030
	char pad_0038[16]; //0x0038
	std::int32_t occupied; //0x0048

	const std::uint64_t get(std::int32_t index) const {
		if ((this->data[index >> 5] >> (index & 0x1F)) & 1)
			return this->list[index];
		return NULL;
	}

}; //Size: 0x004C

class CBuilding
{
public:
	std::uint64_t vmt; //0x0000
	char pad_0008[24]; //0x0008
	std::uint64_t model_info; //0x0020
	char pad_0028[56]; //0x0028
	float s1; //0x0060
	char pad_0064[16]; //0x0064
	float s2; //0x0074
	char pad_0078[4]; //0x0078
	float s3; //0x007C
	char pad_0080[8]; //0x0080
	float s4; //0x0088
	float s5; //0x008C
	float x; //0x0090
	float y; //0x0094
	float z; //0x0098
	char pad_009C[52]; //0x009C
}; //Size: 0x00D0

static CBuilding* g_menu_drawable_manager_current_closest_drawable = nullptr;

namespace big
{
	using Void = std::uint32_t;
	using Any = std::uint32_t;
	using Hash = std::uint32_t;
	using Entity = std::int32_t;
	using Player = std::int32_t;
	using FireId = std::int32_t;
	using Ped = Entity;
	using Vehicle = Entity;
	using Cam = std::int32_t;
	using CarGenerator = std::int32_t;
	using Group = std::int32_t;
	using Train = std::int32_t;
	using Object = Entity;
	using Pickup = Object;
	using Weapon = std::int32_t;
	using Interior = std::int32_t;
	using Blip = std::int32_t;
	using Texture = std::int32_t;
	using TextureDict = std::int32_t;
	using CoverPoint = std::int32_t;
	using Camera = std::int32_t;
	using TaskSequence = std::int32_t;
	using ColourIndex = std::int32_t;
	using Sphere = std::int32_t;
	using ScrHandle = std::int32_t;

#pragma pack(push, 1)
	struct Vector2
	{
		float x{};
		float y{};
	};
#pragma pack(pop)

#pragma pack(push, 1)
	struct NativeVector3
	{
	public:
		NativeVector3() = default;
		NativeVector3(float x, float y, float z) :
			x(x), y(y), z(z)
		{}
	public:
		float x{};
	private:
		char paddingX[4];
	public:
		float y{};
	private:
		char paddingY[4];
	public:
		float z{};
	private:
		char paddingZ[4];
	};
#pragma pack(pop)

#pragma pack(push, 1)
	struct Vector3
	{
		float x{};
		float y{};
		float z{};
	};
#pragma pack(pop)

#pragma pack(push, 1)
	struct Color
	{
		int r{ 255 };
		int g{ 255 };
		int b{ 255 };
		int a{ 255 };
	};
#pragma pack(pop)
}
