## xe architecture

### code modules and their completion status
* shader loader (✔︎)
  * uniform handler (✔︎)
* simple gui layer (✔︎)
* scenegraph (wip)
  * AOI culling (mostly in scenegraph) (✘)
* render system (✘)
  * texturing (✘)
  * mesh rendering (✘)
  * quadtree voxel rendering (✘)
  * materials (✘)
    * lighting & lightmaps (✘)
    * caustics etc (✘)
  * mipmapping (✘)
  * transparency and ordering (✘)
  * (*far in the future*) deferred shading (✘)
* camera (✘)
* model loading (✘)
* input layer (✘)

### the main game loop
* read/trigger input events
* simulate one frame
  * update frame graph
    * compute transforms
    * get transform state of all tree end-point objects
  * update physics
  * update particle simulations
* render the game stuff
* render the gui
