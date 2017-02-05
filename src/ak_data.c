/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#include "ak_data.h"
#include <assert.h>

AkDataContext*
ak_data_new(void   *memparent,
            size_t  nodeitems,
            size_t  itemsize,
            AkCmpFn cmp) {
  AkHeap        *heap;
  AkDataContext *ctx;

  heap = ak_heap_getheap(memparent);
  ctx  = ak_heap_calloc(heap, memparent, sizeof(*ctx));

  ctx->nodesize = nodeitems * itemsize;
  ctx->itemsize = itemsize;
  ctx->heap     = heap;
  ctx->cmp      = cmp;

  return ctx;
}

void
ak_data_append(AkDataContext *dctx, void *data) {
  AkDataChunk *chunk;
  void        *mem;
  size_t       size;

  size = dctx->itemsize;
  assert(dctx->nodesize > size);

  if (dctx->usedsize + size > dctx->size) {
    chunk = ak_heap_alloc(dctx->heap,
                          dctx,
                          sizeof(*chunk) + dctx->nodesize);
    chunk->usedsize = 0;
    chunk->next     = NULL;

    chunk->next = dctx->last;
    dctx->last  = chunk;
    dctx->size += dctx->nodesize;

    if (!dctx->data)
      dctx->data = chunk;
  } else {
    chunk = dctx->last;
  }

  mem = chunk->data + chunk->usedsize;
  memcpy(mem, data, size);

  chunk->usedsize += size;
  dctx->usedsize  += size;
  dctx->itemcount++;
}

bool
ak_data_append_unq(AkDataContext *dctx, void *item) {
  if (ak_data_exists(dctx, item))
    return false;

  ak_data_append(dctx, item);
  return true;
}

void
ak_data_walk(AkDataContext *dctx) {
  AkDataChunk *chunk;
  void  *data;
  size_t isz, csz, i;

  if (!dctx->data)
    return;

  isz   = dctx->itemsize;
  chunk = dctx->data;

  while (chunk) {
    csz = dctx->nodesize - chunk->usedsize;
    for (i = isz; i < csz; i += isz) {
      data = chunk->data;
      dctx->walkFn(dctx, data);
    }
    chunk = chunk->next;
  }
}

bool
ak_data_exists(AkDataContext *dctx, void *item) {
  AkDataChunk *chunk;
  void  *data;
  char  *pmem;
  size_t isz, csz, i;

  if (!dctx->data)
    return false;

  isz   = dctx->itemsize;
  chunk = dctx->data;

  while (chunk) {
    csz  = dctx->nodesize - chunk->usedsize;
    data = chunk->data;
    pmem = data;

    for (i = isz; i < csz; i += isz) {
      if (dctx->cmp(pmem, item) == 0)
        return true;

      pmem += isz;
    }
    chunk = chunk->next;
  }

  return false;
}

size_t
ak_data_join(AkDataContext *dctx,
             void          *buff) {
  AkDataChunk *chunk;
  void  *data;
  char  *pmem;
  size_t isz, csz, i, count;

  count = 0;

  if (!dctx->data)
    return count;

  isz   = dctx->itemsize;
  chunk = dctx->data;

  pmem = buff;
  while (chunk) {
    csz = dctx->nodesize - chunk->usedsize;
    for (i = isz; i < csz; i += isz) {
      data = chunk->data;
      memcpy(pmem, data, isz);
      pmem += isz;
      count++;
    }
    chunk = chunk->next;
  }

  return count;
}
