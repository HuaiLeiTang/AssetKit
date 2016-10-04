/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#ifndef __libassetkit__ak_collada_annotate__h_
#define __libassetkit__ak_collada_annotate__h_

#include "../ak_collada_common.h"

AkResult _assetkit_hide
ak_dae_annotate(AkHeap * __restrict heap,
                void * __restrict memParent,
                xmlTextReaderPtr reader,
                AkAnnotate ** __restrict dest);

#endif /* __libassetkit__ak_collada_annotate__h_ */