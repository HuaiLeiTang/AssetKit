/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#ifndef __libassetkit__dae_visual_scene_h_
#define __libassetkit__dae_visual_scene_h_

#include "../dae_common.h"

AkResult _assetkit_hide
dae_visualScene(AkXmlState * __restrict xst,
                void * __restrict memParent,
                void ** __restrict dest);

AkResult _assetkit_hide
dae_instanceVisualScene(AkXmlState * __restrict xst,
                        void * __restrict memParent,
                        AkInstanceBase ** __restrict dest);

#endif /* __libassetkit__dae_visual_scene_h_ */
