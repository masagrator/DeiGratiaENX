#include "lib.hpp"
#include "ENG.hpp"
#include "xxHash/xxhash.h"
#include "textureHashes.hpp"
#include "nn/fs.hpp"
#include "spng/spng.h"

ptrdiff_t returnInstructionOffset(uintptr_t LR) {
	return LR - exl::util::modules::GetTargetOffset(0);
}

enum XTX_TYPE {
	XTX_BC3_1    = 2,
	XTX_BC3_2    = 3,
	XTX_RGBA4444 = 5,
	XTX_RGBA8    = 8,
	XTX_ASTC_4X4 = 9
};

struct XTX_HEADER {
	const char MAGIC[4];
	uint8_t xtx_type;
	bool LittleEndian;
	char reserved[2];
	uint32_t texture_width;
	uint32_t texture_height;
	uint32_t image_width;
	uint32_t image_height;
	uint32_t anchor_X;
	uint32_t anchor_Y;
};

struct XTX_FILE {
	XTX_HEADER header;
	char texture_start[2];
};

XTX_FILE* ReplaceXTXTexture(XTX_FILE* TexturePointer, const char* index) {

		nn::fs::FileHandle filehandle;
		char filepath[128] = "";
		snprintf(&filepath[0], 128, "rom:/%s.png", index);
		if (R_FAILED(nn::fs::OpenFile(&filehandle, filepath, nn::fs::OpenMode_Read))) {
			return nullptr;
		}
		long in_size = 0;
		nn::fs::GetFileSize(&in_size, filehandle);
		void* in_buffer = malloc(in_size);
		nn::fs::ReadFile(filehandle, 0, in_buffer, in_size);
		nn::fs::CloseFile(filehandle);
		spng_ctx *ctx = spng_ctx_new(0);
		spng_set_png_buffer(ctx, in_buffer, in_size);
		size_t out_size = 0;
		spng_decoded_image_size(ctx, SPNG_FMT_RGBA8, &out_size);
		XTX_FILE* out_buffer = (XTX_FILE*)malloc(out_size+sizeof(XTX_HEADER));
		memcpy((void*)out_buffer, TexturePointer, sizeof(XTX_HEADER));
		spng_decode_image(ctx, out_buffer -> texture_start, out_size, SPNG_FMT_RGBA8, 0);
		spng_ctx_free(ctx);
		free(in_buffer);
		out_buffer -> header.xtx_type = XTX_RGBA8;
		return out_buffer;
}

HOOK_DEFINE_TRAMPOLINE(LoadXTXTexture) {
	static int Callback(void* GLTextures, XTX_FILE* TexturePointer) {
		// Sometimes this function is called to just clean textures, 
		// then TexturePointer leads to empty space
		if (!strncmp(TexturePointer -> header.MAGIC, "xtx", 3)) {
			uint32_t width = TexturePointer -> header.texture_width;
			uint32_t height = TexturePointer -> header.texture_height;
			if (!(TexturePointer -> header.LittleEndian)) {
				width = __builtin_bswap32(width);
				height = __builtin_bswap32(height);
			}
			//case 9, 2 & 3
			uint32_t xtx_size = width * height;
			switch(TexturePointer -> header.xtx_type) {
				case XTX_RGBA8:
					xtx_size *= 4;
					break;
				case XTX_RGBA4444:
					xtx_size *= 2;
			}
			xtx_size += sizeof(XTX_HEADER);
			XXH64_hash_t hash_output = XXH3_64bits((void*)TexturePointer, xtx_size);
			const char* index = compareHashes(hash_output);
			if (index != nullptr) {
				XTX_FILE* TexturePointer_temp = ReplaceXTXTexture(TexturePointer, index);
				if (TexturePointer_temp) {
					int ret = Orig(GLTextures, TexturePointer_temp);
					free(TexturePointer_temp);
					return ret;
				}
			}
		}

		return Orig(GLTextures, TexturePointer);
	}
};

struct nnswkbdKeyboardConfig {
	uint8_t mode;
};

extern "C" {
	int _ZN2nn5swkbd12ShowKeyboardEPNS0_6StringERKNS0_15ShowKeyboardArgE(const char* string, nnswkbdKeyboardConfig* config);
}

HOOK_DEFINE_TRAMPOLINE(ShowKeyboard) {
	static int Callback(const char* string, nnswkbdKeyboardConfig* config) {
		//Block swkbd to use only ASCII
		config -> mode = 2;
		return Orig(string, config);
	}
};

HOOK_DEFINE_TRAMPOLINE(SubMenuTextRender) {
	static int Callback(void* x0, void* x1, float s0) {
		uintptr_t ret_offset = returnInstructionOffset((uintptr_t)__builtin_return_address(0));
		//Change text aligning in YES/NO prompts while not touching anything else
		switch(ret_offset) {
			case 0x3CD4:
			case 0x42EC:
			case 0x43F0:
			case 0x4490:
				break;
			default:
				s0 = 42.0/32.0;
		}

		return Orig(x0, x1, s0);
	}
};

extern "C" void exl_main(void* x0, void* x1) {
	*(uint64_t*)exl::util::modules::GetTargetOffset(0x133430) = (uint64_t)&ENG::CHAPTER_TITLES;
	*(uint64_t*)exl::util::modules::GetTargetOffset(0x133A20) = (uint64_t)&ENG::NOTIFICATIONS;
	*(uint64_t*)exl::util::modules::GetTargetOffset(0x133418) = (uint64_t)&ENG::PLAYING_LOG_MAIN;
	*(uint64_t*)exl::util::modules::GetTargetOffset(0x133838) = (uint64_t)&ENG::MUSIC;
	*(uint64_t*)exl::util::modules::GetTargetOffset(0x133868) = (uint64_t)&ENG::SETTINGS_DESCRIPTIONS;
	*(uint64_t*)exl::util::modules::GetTargetOffset(0x133438) = (uint64_t)&ENG::ENDINGS;

	exl::hook::Initialize();

	LoadXTXTexture::InstallAtOffset(0xF1B0);
	ShowKeyboard::InstallAtFuncPtr(_ZN2nn5swkbd12ShowKeyboardEPNS0_6StringERKNS0_15ShowKeyboardArgE);
	SubMenuTextRender::InstallAtOffset(0x94D0);

	exl::patch::CodePatcher patcher{0x39544};
	uint64_t save_text_address = (uint64_t)exl::util::modules::GetTargetOffset(0x39544) & ~0xFFF;
	ptrdiff_t save_text0 = (uint64_t)ENG::SAVE_EXIT[0] - save_text_address;
	ptrdiff_t save_text1 = (uint64_t)ENG::SAVE_EXIT[1] - save_text_address;
	ptrdiff_t save_text2 = (uint64_t)ENG::SAVE_EXIT[2] - save_text_address;
	patcher.WriteInst(exl::armv8::inst::Adrp(exl::armv8::reg::X3, save_text0 & ~0xFFF));
	patcher.WriteInst(exl::armv8::inst::Adrp(exl::armv8::reg::X4, save_text1 & ~0xFFF));
	patcher.WriteInst(exl::armv8::inst::Adrp(exl::armv8::reg::X5, save_text2 & ~0xFFF));
	patcher.WriteInst(exl::armv8::inst::AddImmediate(exl::armv8::reg::X3, exl::armv8::reg::X3, save_text0 & 0xFFF));
	patcher.WriteInst(exl::armv8::inst::AddImmediate(exl::armv8::reg::X4, exl::armv8::reg::X4, save_text1 & 0xFFF));
	patcher.WriteInst(exl::armv8::inst::AddImmediate(exl::armv8::reg::X5, exl::armv8::reg::X5, save_text2 & 0xFFF));

	patcher.Seek(0x12E10);
	save_text_address = (uint64_t)exl::util::modules::GetTargetOffset(0x12E10) & ~0xFFF;
	save_text0 = (uint64_t)ENG::YES_NO[0] - save_text_address;
	patcher.WriteInst(exl::armv8::inst::Adrp(exl::armv8::reg::X24, save_text0 & ~0xFFF));
	patcher.WriteInst(exl::armv8::inst::AddImmediate(exl::armv8::reg::X24, exl::armv8::reg::X24, save_text0 & 0xFFF));
	patcher.Seek(0x12F4C);
	patcher.WriteInst(exl::armv8::inst::Adrp(exl::armv8::reg::X23, save_text0 & ~0xFFF));
	patcher.WriteInst(exl::armv8::inst::AddImmediate(exl::armv8::reg::X23, exl::armv8::reg::X23, save_text0 & 0xFFF));

	patcher.Seek(0x13024);
	save_text_address = (uint64_t)exl::util::modules::GetTargetOffset(0x13024) & ~0xFFF;
	save_text0 = (uint64_t)ENG::YES_NO[1] - save_text_address;
	patcher.WriteInst(exl::armv8::inst::Adrp(exl::armv8::reg::X0, save_text0 & ~0xFFF));
	patcher.WriteInst(exl::armv8::inst::AddImmediate(exl::armv8::reg::X0, exl::armv8::reg::X0, save_text0 & 0xFFF));

	patcher.Seek(0x12DA4);
	save_text_address = (uint64_t)exl::util::modules::GetTargetOffset(0x12DA4) & ~0xFFF;
	save_text0 = (uint64_t)ENG::YES_NO[2] - save_text_address;
	patcher.WriteInst(exl::armv8::inst::Adrp(exl::armv8::reg::X0, save_text0 & ~0xFFF));
	patcher.WriteInst(exl::armv8::inst::AddImmediate(exl::armv8::reg::X0, exl::armv8::reg::X0, save_text0 & 0xFFF));
	patcher.Seek(0x12EFC);
	patcher.WriteInst(exl::armv8::inst::Adrp(exl::armv8::reg::X0, save_text0 & ~0xFFF));
	patcher.WriteInst(exl::armv8::inst::AddImmediate(exl::armv8::reg::X0, exl::armv8::reg::X0, save_text0 & 0xFFF));

	patcher.Seek(0x12EB4);
	save_text_address = (uint64_t)exl::util::modules::GetTargetOffset(0x12EB4) & ~0xFFF;
	save_text0 = (uint64_t)ENG::YES_NO[3] - save_text_address;
	patcher.WriteInst(exl::armv8::inst::Adrp(exl::armv8::reg::X0, save_text0 & ~0xFFF));
	patcher.WriteInst(exl::armv8::inst::AddImmediate(exl::armv8::reg::X0, exl::armv8::reg::X0, save_text0 & 0xFFF));
	patcher.Seek(0x1300C);
	save_text_address = (uint64_t)exl::util::modules::GetTargetOffset(0x1300C) & ~0xFFF;
	save_text0 = (uint64_t)ENG::YES_NO[3] - save_text_address;
	patcher.WriteInst(exl::armv8::inst::Adrp(exl::armv8::reg::X0, save_text0 & ~0xFFF));
	patcher.WriteInst(exl::armv8::inst::AddImmediate(exl::armv8::reg::X0, exl::armv8::reg::X0, save_text0 & 0xFFF));

	patcher.Seek(0x37E98);
	save_text_address = (uint64_t)exl::util::modules::GetTargetOffset(0x37E98) & ~0xFFF;
	save_text0 = (uint64_t)ENG::QUICK_SAVE[0] - save_text_address;
	save_text1 = (uint64_t)ENG::QUICK_SAVE[1] - save_text_address;
	patcher.WriteInst(exl::armv8::inst::Adrp(exl::armv8::reg::X3, save_text0 & ~0xFFF));
	patcher.WriteInst(exl::armv8::inst::Adrp(exl::armv8::reg::X4, save_text1 & ~0xFFF));
	patcher.WriteInst(exl::armv8::inst::AddImmediate(exl::armv8::reg::X3, exl::armv8::reg::X3, save_text0 & 0xFFF));
	patcher.WriteInst(exl::armv8::inst::AddImmediate(exl::armv8::reg::X4, exl::armv8::reg::X4, save_text1 & 0xFFF));

	patcher.Seek(0x18084);
	save_text_address = (uint64_t)exl::util::modules::GetTargetOffset(0x18084) & ~0xFFF;
	save_text0 = (uint64_t)&ENG::SAVING[0] - save_text_address;
	patcher.WriteInst(exl::armv8::inst::Adrp(exl::armv8::reg::X20, save_text0 & ~0xFFF));
	patcher.WriteInst(exl::armv8::inst::AddImmediate(exl::armv8::reg::X20, exl::armv8::reg::X20, save_text0 & 0xFFF));

	patcher.Seek(0x1B3B0);
	save_text_address = (uint64_t)exl::util::modules::GetTargetOffset(0x1B3B0) & ~0xFFF;
	save_text0 = (uint64_t)&ENG::SAVING[0] - save_text_address;
	patcher.WriteInst(exl::armv8::inst::Adrp(exl::armv8::reg::X20, save_text0 & ~0xFFF));
	patcher.WriteInst(exl::armv8::inst::AddImmediate(exl::armv8::reg::X20, exl::armv8::reg::X20, save_text0 & 0xFFF));

	patcher.Seek(0x396F0);
	save_text_address = (uint64_t)exl::util::modules::GetTargetOffset(0x396F0) & ~0xFFF;
	save_text0 = (uint64_t)&ENG::CUSTOM_NAME[0] - save_text_address;
	patcher.WriteInst(exl::armv8::inst::Adrp(exl::armv8::reg::X1, save_text0 & ~0xFFF));
	patcher.WriteInst(exl::armv8::inst::AddImmediate(exl::armv8::reg::X1, exl::armv8::reg::X1, save_text0 & 0xFFF));

	patcher.Seek(0x378D8);
	save_text_address = (uint64_t)exl::util::modules::GetTargetOffset(0x378D8) & ~0xFFF;
	save_text0 = (uint64_t)ENG::NAME_PROMPT[0] - save_text_address;
	save_text1 = (uint64_t)ENG::NAME_PROMPT[1] - save_text_address;
	patcher.WriteInst(exl::armv8::inst::Adrp(exl::armv8::reg::X1, save_text0 & ~0xFFF));
	patcher.WriteInst(exl::armv8::inst::AddImmediate(exl::armv8::reg::X1, exl::armv8::reg::X1, save_text0 & 0xFFF));
	patcher.Seek(0x378E8);
	patcher.WriteInst(exl::armv8::inst::Adrp(exl::armv8::reg::X3, save_text1 & ~0xFFF));
	patcher.WriteInst(exl::armv8::inst::AddImmediate(exl::armv8::reg::X3, exl::armv8::reg::X3, save_text1 & 0xFFF));

	patcher.Seek(0x3B680);
	save_text_address = (uint64_t)exl::util::modules::GetTargetOffset(0x3B680) & ~0xFFF;
	save_text0 = (uint64_t)ENG::NAME_PROMPT[0] - save_text_address;
	save_text1 = (uint64_t)ENG::NAME_PROMPT[2] - save_text_address;
	patcher.WriteInst(exl::armv8::inst::Adrp(exl::armv8::reg::X1, save_text0 & ~0xFFF));
	patcher.WriteInst(exl::armv8::inst::AddImmediate(exl::armv8::reg::X1, exl::armv8::reg::X1, save_text0 & 0xFFF));
	patcher.Seek(0x3B690);
	patcher.WriteInst(exl::armv8::inst::Adrp(exl::armv8::reg::X3, save_text1 & ~0xFFF));
	patcher.WriteInst(exl::armv8::inst::AddImmediate(exl::armv8::reg::X3, exl::armv8::reg::X3, save_text1 & 0xFFF));

	patcher.Seek(0x396D0);
	save_text_address = (uint64_t)exl::util::modules::GetTargetOffset(0x396D0) & ~0xFFF;
	save_text0 = (uint64_t)ENG::NAME_ERROR[0] - save_text_address;
	save_text1 = (uint64_t)ENG::NAME_ERROR[1] - save_text_address;
	save_text2 = (uint64_t)ENG::NAME_ERROR[2] - save_text_address;
	patcher.WriteInst(exl::armv8::inst::Adrp(exl::armv8::reg::X4, save_text0 & ~0xFFF));
	patcher.WriteInst(exl::armv8::inst::AddImmediate(exl::armv8::reg::X4, exl::armv8::reg::X4, save_text0 & 0xFFF));
	patcher.Seek(0x3974C);
	patcher.WriteInst(exl::armv8::inst::Adrp(exl::armv8::reg::X4, save_text1 & ~0xFFF));
	patcher.WriteInst(exl::armv8::inst::AddImmediate(exl::armv8::reg::X4, exl::armv8::reg::X4, save_text1 & 0xFFF));
	patcher.Seek(0x39794);
	patcher.WriteInst(exl::armv8::inst::Adrp(exl::armv8::reg::X4, save_text2 & ~0xFFF));
	patcher.WriteInst(exl::armv8::inst::AddImmediate(exl::armv8::reg::X4, exl::armv8::reg::X4, save_text2 & 0xFFF));
	patcher.Seek(0x1B8C8);
	save_text_address = (uint64_t)exl::util::modules::GetTargetOffset(0x1B8C8) & ~0xFFF;
	save_text0 = (uint64_t)ENG::NAME_ERROR[2] - save_text_address;
	patcher.WriteInst(exl::armv8::inst::Adrp(exl::armv8::reg::X1, save_text0 & ~0xFFF));
	patcher.WriteInst(exl::armv8::inst::AddImmediate(exl::armv8::reg::X1, exl::armv8::reg::X1, save_text0 & 0xFFF));
	patcher.WriteInst(exl::armv8::inst::Movz(exl::armv8::reg::W2, strlen(ENG::NAME_ERROR[2])));
	patcher.Seek(0x1B8F4);
	save_text0 = (uint64_t)ENG::NAME_ERROR[3] - save_text_address;
	patcher.WriteInst(exl::armv8::inst::Adrp(exl::armv8::reg::X1, save_text0 & ~0xFFF));
	patcher.WriteInst(exl::armv8::inst::AddImmediate(exl::armv8::reg::X1, exl::armv8::reg::X1, save_text0 & 0xFFF));

	//Replace last name with first name in prompt
	patcher.Seek(0x396E4);
	patcher.WriteInst(0xD00007C3);
	patcher.WriteInst(0xF9459863);
	patcher.WriteInst(0x91006062);

	//Change first and last name limit from 5 to 17 each
	patcher.Seek(0x1BA00);
	patcher.WriteInst(exl::armv8::inst::Movk(exl::armv8::reg::X9, 17));

	//Remove forward slash used for YES/NO
	patcher.Seek(0xE5F97);
	patcher.WriteInst(0x0);

	//Replace in message offset check unused `《` with used `【`
	patcher.Seek(0xE95A3);
	patcher.WriteInst(0x00798100);

	//Block player from using MC's romaji real first or last name in prompt with change from strcmp to strncasecmp (because there is no support for strcasecmp in main)
	//This code is used before finishing first two endings
	*(uint64_t*)exl::util::modules::GetTargetOffset(0x10FF58) = (uint64_t)ENG::MC_NAME[0];
	*(uint64_t*)exl::util::modules::GetTargetOffset(0x10FF70) = (uint64_t)ENG::MC_NAME[1];
	patcher.Seek(0x1B878);
	patcher.WriteInst(exl::armv8::inst::Movz(exl::armv8::reg::X2, strlen(ENG::MC_NAME[0])));
	patcher.WriteInst(exl::armv8::inst::Nop());
	patcher.WriteInst(exl::armv8::inst::Nop());
	patcher.WriteInst(exl::armv8::inst::Nop());
	patcher.WriteInst(0x94029E6E);
	patcher.Seek(0x1B8A8);
	patcher.WriteInst(exl::armv8::inst::Movz(exl::armv8::reg::X2, strlen(ENG::MC_NAME[1])));
	patcher.WriteInst(exl::armv8::inst::Nop());
	patcher.WriteInst(exl::armv8::inst::Nop());
	patcher.WriteInst(exl::armv8::inst::Nop());
	patcher.WriteInst(0x94029E62);

	//Check if player is using MC's real name in romaji, in case of using only one part of name correctly it throws error that this name cannot be used.
	//Changed from strcmp to strncasecmp (because there is no support for strcasecmp in main)
	//This code is used after finishing first two endings
	patcher.Seek(0x3C9E8);
	save_text_address = (uint64_t)exl::util::modules::GetTargetOffset(0x3C9E8) & ~0xFFF;
	save_text0 = (uint64_t)ENG::MC_NAME[0] - save_text_address;
	save_text1 = (uint64_t)ENG::MC_NAME[1] - save_text_address;
	patcher.WriteInst(exl::armv8::inst::Adrp(exl::armv8::reg::X1, save_text0 & ~0xFFF));
	patcher.WriteInst(exl::armv8::inst::AddImmediate(exl::armv8::reg::X1, exl::armv8::reg::X1, save_text0 & 0xFFF));
	patcher.WriteInst(exl::armv8::inst::Movz(exl::armv8::reg::X2, strlen(ENG::MC_NAME[0])));
	patcher.WriteInst(0xAA1303E0);
	patcher.WriteInst(0x94021A0C);
	patcher.Seek(0x3CA30);
	patcher.WriteInst(exl::armv8::inst::Adrp(exl::armv8::reg::X1, save_text1 & ~0xFFF));
	patcher.WriteInst(exl::armv8::inst::AddImmediate(exl::armv8::reg::X1, exl::armv8::reg::X1, save_text1 & 0xFFF));
	patcher.WriteInst(exl::armv8::inst::Movz(exl::armv8::reg::X2, strlen(ENG::MC_NAME[1])));
	patcher.WriteInst(0xAA1403E0);
	patcher.WriteInst(exl::armv8::inst::Nop());
	patcher.WriteInst(exl::armv8::inst::Nop());
	patcher.WriteInst(exl::armv8::inst::Nop());
	patcher.WriteInst(exl::armv8::inst::Nop());
	patcher.WriteInst(0x940219FC);
	patcher.Seek(0x3CA74);
	patcher.WriteInst(exl::armv8::inst::Adrp(exl::armv8::reg::X1, save_text0 & ~0xFFF));
	patcher.WriteInst(exl::armv8::inst::AddImmediate(exl::armv8::reg::X1, exl::armv8::reg::X1, save_text0 & 0xFFF));
	patcher.WriteInst(exl::armv8::inst::Movz(exl::armv8::reg::X2, strlen(ENG::MC_NAME[0])));
	patcher.WriteInst(0xAA1303E0);
	patcher.WriteInst(0x940219EF);
	patcher.Seek(0x3CABC);
	patcher.WriteInst(exl::armv8::inst::Adrp(exl::armv8::reg::X1, save_text1 & ~0xFFF));
	patcher.WriteInst(exl::armv8::inst::AddImmediate(exl::armv8::reg::X1, exl::armv8::reg::X1, save_text1 & 0xFFF));
	patcher.WriteInst(exl::armv8::inst::Movz(exl::armv8::reg::X2, strlen(ENG::MC_NAME[1])));
	patcher.WriteInst(0xAA1403E0);
	patcher.WriteInst(exl::armv8::inst::Nop());
	patcher.WriteInst(exl::armv8::inst::Nop());
	patcher.WriteInst(exl::armv8::inst::Nop());
	patcher.WriteInst(exl::armv8::inst::Nop());	
	patcher.WriteInst(0x940219D9);

	//Check if player is using MC's real name in romaji to branch to new route
	//Changed from strcmp to strncasecmp (because there is no support for strcasecmp in main)
	//This code is used after finishing first two endings
	patcher.Seek(0x1BBF0);
	save_text_address = (uint64_t)exl::util::modules::GetTargetOffset(0x1BBF0) & ~0xFFF;
	save_text0 = (uint64_t)ENG::MC_NAME[0] - save_text_address;
	save_text1 = (uint64_t)ENG::MC_NAME[1] - save_text_address;
	patcher.WriteInst(exl::armv8::inst::Adrp(exl::armv8::reg::X1, save_text0 & ~0xFFF));
	patcher.WriteInst(exl::armv8::inst::AddImmediate(exl::armv8::reg::X1, exl::armv8::reg::X1, save_text0 & 0xFFF));
	patcher.WriteInst(exl::armv8::inst::Movz(exl::armv8::reg::X2, strlen(ENG::MC_NAME[0])+1));
	patcher.WriteInst(0xAA1303E0);
	patcher.WriteInst(0x94029D90);
	patcher.Seek(0x1BC34);
	patcher.WriteInst(exl::armv8::inst::Adrp(exl::armv8::reg::X1, save_text1 & ~0xFFF));
	patcher.WriteInst(exl::armv8::inst::AddImmediate(exl::armv8::reg::X1, exl::armv8::reg::X1, save_text1 & 0xFFF));
	patcher.WriteInst(exl::armv8::inst::Movz(exl::armv8::reg::X2, strlen(ENG::MC_NAME[1])+1));
	patcher.WriteInst(0xAA1403E0);
	patcher.WriteInst(0x94029D7F);
	patcher.Seek(0x1BC54);
	patcher.WriteInst(0xAA1403E0);
}

extern "C" NORETURN void exl_exception_entry() {
	/* TODO: exception handling */
	EXL_ABORT(0x420);
}