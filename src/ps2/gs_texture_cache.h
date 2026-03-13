#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <gsKit.h>

#include "../data_win.h"

// ===[ GsTextureCache ]===
#define GS_VRAM_SIZE (4 * 1024 * 1024)

// On-demand BTX texture loader for PS2 GS VRAM.
// Loads pre-extracted BTX files from host filesystem,
// uploads them to VRAM, and flushes all textures when VRAM is full.
// Uses a bump allocator starting after framebuffers + FONTM.
//
// BTX files are named by sprite/background index:
//   Sprites:     TEXTURES/{spriteIndex}_{frameIndex}.BTX
//   Backgrounds: TEXTURES/bg_{bgIndex}.BTX
//
// The cache builds a tpagIndex -> file path mapping from DataWin at init time.

// Maps a tpagIndex to the BTX file that contains it
typedef struct {
    bool isBackground; // false = sprite, true = background
    int32_t index;     // sprite index or background index
    int32_t frame;     // frame index (only for sprites, ignored for backgrounds)
} TpagFileMapping;

typedef struct {
    int32_t tpagIndex;       // -1 if slot is free
    GSTEXTURE gsTexture;     // gsKit texture handle (Mem/Clut freed after upload)
    uint32_t vramSize;       // total VRAM bytes (texture + clut)
    bool loaded;             // true if currently in VRAM
    int32_t width;           // padded texture width
    int32_t height;          // padded texture height
} GsCachedTexture;

typedef struct {
    GSGLOBAL* gsGlobal;
    GsCachedTexture* entries;                      // stb_ds dynamic array
    struct { int key; int value; }* indexMap;       // stb_ds intmap: tpagIndex -> entries[] index
    struct { int key; TpagFileMapping value; }* fileMap; // stb_ds intmap: tpagIndex -> file mapping
    uint32_t vramBase;       // VRAM offset after framebuffers/FONTM
    uint32_t currentFrame;
} GsTextureCache;

// Create a texture cache. vramBase is gsGlobal->CurrentPointer after FONTM upload.
// Builds the tpagIndex -> file mapping from the DataWin sprite/background tables.
GsTextureCache* GsTextureCache_create(GSGLOBAL* gsGlobal, uint32_t vramBase, DataWin* dataWin);

// Free the texture cache.
void GsTextureCache_free(GsTextureCache* cache);

// Call at the start of each frame.
void GsTextureCache_beginFrame(GsTextureCache* cache);

// Get a cached texture for the given TPAG index. Loads BTX from disk if not cached.
// Returns nullptr if the texture could not be loaded.
GSTEXTURE* GsTextureCache_get(GsTextureCache* cache, int32_t tpagIndex);
