/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#include "gltf.h"
#include "../id.h"
#include "../../include/ak/path.h"
#include "core/gltf_asset.h"
#include "core/gltf_buffer.h"
#include "core/gltf_mesh.h"
#include "core/gltf_node.h"
#include "core/gltf_scene.h"
#include "gltf_postscript.h"
#include "core/gltf_camera.h"
#include "core/gltf_image.h"
#include "core/gltf_profile.h"
#include "core/gltf_sampler.h"
#include "core/gltf_texture.h"
#include "core/gltf_material.h"
#include "core/gltf_anim.h"
#include "core/gltf_skin.h"

AkResult _assetkit_hide
gltf_doc(AkDoc     ** __restrict dest,
         const char * __restrict filepath) {
  AkHeap        *heap;
  AkDoc         *doc;
  AkAssetInf    *ainf;
  json_t        *jscene;
  AkVisualScene *scene;
  AkGLTFState    gstVal, *gst;
  json_error_t   error;
  AkResult       ret;

  heap = ak_heap_new(NULL, NULL, NULL);
  doc  = ak_heap_calloc(heap, NULL, sizeof(*doc));

  doc->inf        = ak_heap_calloc(heap, doc, sizeof(*doc->inf));
  doc->inf->name  = filepath;
  doc->inf->dir   = ak_path_dir(heap, doc, filepath);
  doc->inf->ftype = AK_FILE_TYPE_GLTF;

  if (doc->inf->dir)
    doc->inf->dirlen = strlen(doc->inf->dir);

  ak_heap_setdata(heap, doc);
  ak_id_newheap(heap);

  memset(&gstVal, 0, sizeof(gstVal));

  gst         = &gstVal;
  gstVal.doc  = doc;
  gstVal.heap = heap;
  gstVal.root = json_load_file(filepath, 0, &error);

  ainf = NULL;
  ret  = gltf_asset(gst, doc, ainf);

  /* probably unsupportted version or verion is missing */
  if (ret == AK_EBADF) {
    ak_free(doc);
    return ret;
  }

  gst->bufferViews = rb_newtree(ds_allocator(), ds_cmp_i32p, NULL);

  gltf_buffers(gst);
  gltf_images(gst);
  gltf_materials(gst);
  gltf_meshes(gst);
  gltf_cameras(gst);
  gltf_nodes(gst);
  gltf_scenes(gst);
  gltf_animations(gst);
  gltf_skin(gst);

  /* TODO: release resources in GLTFState */

  /* set first scene as default scene if not specified  */
  scene = doc->lib.visualScenes->chld;

  /* set default scene */
  if ((jscene = json_object_get(gst->root, _s_gltf_scene))) {
    int32_t sceneIndex;
    sceneIndex = (int32_t)json_integer_value(jscene);
    while (sceneIndex > 0 && scene) {
      scene = scene->next;
      sceneIndex--;
    }
  }

  if (scene) {
    AkInstanceBase *instScene;
    instScene = ak_heap_calloc(heap, doc, sizeof(*instScene));

    instScene->url.ptr = scene;
    doc->scene.visualScene = instScene;
  }

  *dest = doc;

  /* post-parse operations */
  gltf_postscript(gst);

  return AK_OK;
}
