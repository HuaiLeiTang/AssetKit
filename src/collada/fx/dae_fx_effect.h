/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */


#ifndef __libassetkit__dae_fx_effect__h_
#define __libassetkit__dae_fx_effect__h_

#include "../../../include/assetkit.h"
#include "../dae_common.h"

AkResult _assetkit_hide
ak_dae_effect(AkXmlState * __restrict xst,
              void * __restrict memParent,
              void ** __restrict dest);

AkResult _assetkit_hide
ak_dae_fxInstanceEffect(AkXmlState * __restrict xst,
                        void * __restrict memParent,
                        AkInstanceEffect ** __restrict dest);

#endif /* __libassetkit__dae_fx_effect__h_ */