/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#ifndef ak_texture_h
#define ak_texture_h

typedef enum AkWrapMode {
  AK_WRAP_MODE_WRAP        = 0,
  AK_WRAP_MODE_MIRROR      = 1,
  AK_WRAP_MODE_CLAMP       = 2,
  AK_WRAP_MODE_BORDER      = 3,
  AK_WRAP_MODE_MIRROR_ONCE = 4
} AkWrapMode;

typedef enum AkMinFilter {
  AK_MINFILTER_LINEAR       = 0,
  AK_MINFILTER_NEAREST      = 1,
  AK_MINFILTER_ANISOTROPIC  = 2,

  AK_LINEAR_MIPMAP_NEAREST  = 2,
  AK_LINEAR_MIPMAP_LINEAR   = 3,
  AK_NEAREST_MIPMAP_NEAREST = 4,
  AK_NEAREST_MIPMAP_LINEAR  = 5
} AkMinFilter;

typedef enum AkMagFilter {
  AK_MAGFILTER_LINEAR       = 0,
  AK_MAGFILTER_NEAREST      = 1
} AkMagFilter;

typedef enum AkMipFilter {
  AK_MIPFILTER_LINEAR  = 0,
  AK_MIPFILTER_NONE    = 1,
  AK_MIPFILTER_NEAREST = 2
} AkMipFilter;

typedef struct AkSampler {
  const char     *uniformName;
  const char     *coordInputName;
  AkColor        *borderColor;
  const char     *texcoordSemantic;
  AkInstanceBase *instanceImage;
  AkTree         *extra;

  AkWrapMode      wrapS;
  AkWrapMode      wrapT;
  AkWrapMode      wrapP;

  AkMinFilter     minfilter;
  AkMagFilter     magfilter;
  AkMipFilter     mipfilter;

  unsigned long   maxAnisotropy;
  unsigned long   mipMaxLevel;
  unsigned long   mipMinLevel;
  float           mipBias;
} AkSampler;

#endif /* ak_texture_h */
