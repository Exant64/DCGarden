
#pragma once
#include "stdafx.h"
#include "SA2ModLoader.h"

#include "NeutGarden.h"
#include "HeroGarden.h"
#include "DarkGarden.h"

extern "C"
{

	FunctionPointer(CharObj1 *, sub_5A89C0, (int a1, float a2, float a3), 0x5A89C0);

	DataArray(NJS_VECTOR, SpawnPos, 0x01366260, 16 * 3);

	static const void *const Transporter_LoadPtr = (void*)0x0057E4F0;
	CharObj1* Transporter_Load(NJS_VECTOR *a1, int a2)
	{
		CharObj1* result;
		__asm
		{
			push[a2]
			mov ebx, [a1]
			call Transporter_LoadPtr
			mov result, eax
		}
		return result;
	}

	FunctionPointer(int, sub_57D4C0, (), 0x57D4C0);
	NJS_TEXNAME heroRealName[0x26];
	NJS_TEXLIST heroReal = { arrayptrandlength(heroRealName) };
	NJS_TEXNAME darkRealName[27];
	NJS_TEXLIST darkReal = { arrayptrandlength(darkRealName) };
	NJS_TEXNAME neutralRealName[27];
	NJS_TEXLIST neutralReal = { arrayptrandlength(neutralRealName) };

	void TransporterLoadingDark()
	{
		NJS_VECTOR position;
		position.x = -84;
		position.y = 0;
		position.z = -86;
		Transporter_Load(&position, -8192);
	}
	void TransporterLoadingHero()
	{
		NJS_VECTOR position;
		position.x = 108;
		position.y = 0;
		position.z = 100;
		Transporter_Load(&position, 24940);
	}
	DataArray(NJS_VECTOR, TreePos, 0x01366B30, 30);

	void overwriteHeroGarden()
	{
		sub_57D4C0();
		LoadTexturePack((char*)"al_stg_hero_tex", &heroReal);
	}

	void overwriteNeutGarden()
	{
		sub_57D4C0();
		LoadTexturePack((char*)"al_stg_neut_tex", &neutralReal);
	}

	void overwriteDarkGarden()
	{
		sub_57D4C0();
		LoadTexturePack((char*)"al_stg_dark_tex", &darkReal);
	}

	//pot, 95, 0, -95
	//spout 95, -93
	__declspec(dllexport) void __cdecl Init(const char *path)
	{
		HMODULE v1 = GetModuleHandle(L"Data_DLL_orig");

		//Modelreplacement

		WriteCall((void*)0x0054B914, TransporterLoadingDark);
		WriteCall((void*)0x0054D3F4, TransporterLoadingHero);
		WriteCall((void*)0x0054D390, overwriteHeroGarden);
		WriteCall((void*)0x0054C9AE, overwriteNeutGarden);
		WriteCall((void*)0x0054B8B0, overwriteDarkGarden);

		SpawnPos[21] = { -1,5,63};
		SpawnPos[31] = { -3.5, 14, -118 };
		SpawnPos[38] = {106,0,85};
		SpawnPos[40] = {71,60,53};

		TreePos[20] = { -97.67360687f, 0, 24.8467598f };
		TreePos[21] = { -2.489078522f, 30, 97.21862793f };
		TreePos[22] = { -4.752135754f, 0, -103.2497711f };
		TreePos[23] = { -5.829658031f, 0, -8.904097557f };
		TreePos[24] = { -58.04101181f, 0, 38.79659271f };
		TreePos[25] = { -87.87710571f, 0, 96.62219238f };
		TreePos[26] = { -45.63697052f, 0, -95.78780365f };
		TreePos[10] = { -98.15678406f, 0, 6.223317623f };
		TreePos[11] = { 99.5038147f, 0, 55.1412735f };
		TreePos[12] = { -112.9234543f, 14, -89.29230499f };
		TreePos[13] = { -21.96385574f, 0, -18.78127861f };
		TreePos[14] = { -98.26248169f, 0, 53.00448227f };
		TreePos[15] = { 66.88718414f, 0, 106.6939011f };
		TreePos[16] = { 70.04785156f, 0, 22.01750755f };
		//TreePos[0] = { -98.15678406f, 0f, 6.223317623 };
		//TreePos[1] = { 99.5038147f, 0f, 55.1412735 };
		//TreePos[2] = { -112.9234543f, 14f, -89.29230499 };
		TreePos[3] = { 4.16345787f, 9, 35.49517059f };
		TreePos[4] = { 26.35211372f, 0, -56.29634857f };
		TreePos[5] = { -18.96110916f, 0, -145.6703339f };
		TreePos[6] = { 63.82605362f, 0, -115.38974f };

		if (v1)
		{
			LandTable *table = (LandTable*)GetProcAddress(v1, "objLandTableNeut");
			if (table)
			{
				WriteData((char*)0x0054C80B, (char)0);
				NJS_TEXLIST* test = (NJS_TEXLIST*)GetProcAddress(v1, "texlist_al_stg_neut_tex");
				test->textures = neutralReal.textures;
				*table = landtable_0000CEE8;
			}
		}
		if (v1)
		{
			LandTable *table = (LandTable*)GetProcAddress(v1, "objLandTableHero");
			NJS_OBJECT* spout0 = (NJS_OBJECT*)GetProcAddress(v1, "object_ghero_nc_spout00_spout00");
			NJS_OBJECT* spout1 = (NJS_OBJECT*)GetProcAddress(v1, "object_ghero_nc_spout01_spout01");
			NJS_OBJECT* spout2 = (NJS_OBJECT*)GetProcAddress(v1, "object_ghero_nc_spout02_spout02");
			NJS_OBJECT* spout3 = (NJS_OBJECT*)GetProcAddress(v1, "object_ghero_nc_spout03_spout03");

			NJS_OBJECT* pot = (NJS_OBJECT*)GetProcAddress(v1, "object_ghero_nc_pot_pot");
			NJS_OBJECT* river = (NJS_OBJECT*)GetProcAddress(v1, "object_ghero_nc_river00_river00");

			if (table)
			{
				WriteData((char*)0x0054D243, (char)0);
				*table = landtable_00013C3C;
				NJS_TEXLIST* test = (NJS_TEXLIST*)GetProcAddress(v1, "texlist_al_stg_hero_tex");
				test->textures = heroReal.textures;
				spout0->evalflags = 0x10;
				spout0->pos[0] = 95;
				spout0->pos[2] = -93;
				spout1->evalflags = 0x10;
				spout1->pos[0] = 95;
				spout1->pos[2] = -93;
				spout2->evalflags = 0x10;
				spout2->pos[0] = 95;
				spout2->pos[2] = -93;
				spout3->evalflags = 0x10;
				spout3->pos[0] = 95;
				spout3->pos[2] = -93;
				pot->evalflags = 0x10;
				pot->scl[0] = 0.85;//fountain hero garden scale fix
				pot->scl[2] = 0.85;
				pot->pos[0] = 94.996094;
				pot->pos[2] = -93.329567;
				pot->sa2bmodel->Center.x = -3.016269;
				pot->sa2bmodel->Center.y = 5;
				pot->sa2bmodel->Center.z = -0.000026;
				river->evalflags = 0x10;//water hero garden fix
										//1, 1,2
										//-80, -1.5, 80
										//0, 4294963296(60F0FFFF), 0
				river->scl[0] = 0.9;
				river->scl[2] = 2.1;
				river->pos[0] = -60;
				river->pos[2] = 50;
				river->ang[1] = 60416;
			}
		}
		if (v1)
		{
			LandTable *table = (LandTable*)GetProcAddress(v1, "objLandTableDark");

			if (table)
			{
				WriteData((char*)0x0054B763, (char)0);
				NJS_OBJECT* hotspring = (NJS_OBJECT*)GetProcAddress(v1, "object_gdark_nc_hotspring00_hotspring00");
				NJS_TEXLIST* test = (NJS_TEXLIST*)GetProcAddress(v1, "texlist_al_stg_dark_tex");
				test->textures = darkReal.textures;
				*table = landtable_00012F58;
				hotspring->evalflags = 0x10;
				hotspring->pos[2] = -100;
				hotspring->scl[0] = -1.5;
				hotspring->scl[1] = -1.5;
				hotspring->scl[2] = -1.5;
				//table->COLCount = LengthOfArray<int16_t>(collist_000127B8);
				//table->ChunkModelCount = 36;
				//table->COLList = landtable_00012F58.COLList;
				//table->TextureName = (char*)"AL_STG_DARK_TEX_DC";
			}
		}
		//14


	}

	__declspec(dllexport) ModInfo SA2ModInfo = { ModLoaderVer };
}

