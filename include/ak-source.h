/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#ifndef ak_source_h
#define ak_source_h
#ifdef __cplusplus
extern "C" {
#endif

struct AkDataParam;
struct AkTechnique;
struct AkTechniqueCommon;
struct AkAssetInf;

typedef enum AkSourceArrayType {
  AK_SOURCE_ARRAY_TYPE_BOOL   = 1,
  AK_SOURCE_ARRAY_TYPE_FLOAT  = 2,
  AK_SOURCE_ARRAY_TYPE_INT    = 3,
  AK_SOURCE_ARRAY_TYPE_IDREF  = 4,
  AK_SOURCE_ARRAY_TYPE_NAME   = 5,
  AK_SOURCE_ARRAY_TYPE_SIDREF = 6,
  AK_SOURCE_ARRAY_TYPE_TOKEN  = 7
} AkSourceArrayType;

typedef struct AkAccessor {
  AkURL    source;
  uint32_t count;
  uint32_t offset;
  uint32_t stride;
  struct AkDataParam *param;
} AkAccessor;

typedef struct AkSource {
  /* const char * id; */
  struct AkAssetInf  *inf;
  const char         *name;
  AkObject           *data; /* arrays inside source */
  AkAccessor         *techniqueCommon;
  struct AkTechnique *technique;
  struct AkSource    *next;
} AkSource;

typedef struct AkBoolArrayN {
  /* const char * id; */
  const char * name;
  size_t       count;
  AkBool       items[];
} AkBoolArrayN;

typedef struct AkFloatArrayN {
  /* const char * id; */
  const char * name;
  size_t       count;
  AkUInt       digits;
  AkUInt       magnitude;
  AkFloat      items[];
} AkFloatArrayN;

typedef struct AkIntArrayN {
  /* const char * id; */
  const char * name;
  size_t       count;
  AkInt        minInclusive;
  AkInt        maxInclusive;
  AkInt        items[];
} AkIntArrayN;

typedef struct AkStringArrayN {
  /* const char  * id; */
  const char  * name;
  size_t count;
  AkString items[];
} AkStringArrayN;

#ifdef __cplusplus
}
#endif
#endif /* ak_source_h */
