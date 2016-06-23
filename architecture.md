## xe architecture

### code modules and their completion status
* shader loader (✔︎)
  * uniform handler (✔︎)
* simple GUI layer (✔︎)
* scenegraph (wip)
  * base system (✔︎)
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
* render the GUI

### GameObjects and stuff
GameObjects store stuff (basically state) for a thing.
GameObjects hold a SceneNode which stores transform data for an instance.
There exists one GameObject per instance of an object.
Different types of objects subclass directly from GameObject and add their state parameters.
#### Rendering gameobjects
Renderables (yeah I know, bad name) are classes that provide batched renderers for a specific type << GameObject.
A single Renderable[T] instance is used for every instance of a T << GameObject. GameObjects never, ever, ever do any rendering.


### Shaders
#### File tree and extensions
Vertex shaders have a `.vert` extension and go in `shaders/vertex`, fragment shaders have a `.frag` extension and go in `shaders/fragment`.

In the `shaders/` directory, put `.yml` or `.yaml` files describing a shader linkage and the io manifest for the linkage.

#### Shader structure and metadata
Each shader code file should begin with `#version 330 core` to direct the glsl compiler to use glsl v3.30.

Each shader manifest file should look something like this:
```yaml
display_name: "Cool Shader"
shaders:
  vertex: shaders/vertex/foo.vert
  fragment: shaders/fragment/baz.frag
inputs:
  - name: position
    type: vec3
    location: 0
  - name: normal
    type: vec3
    location: 1
uniforms:
  - name: model
    tupe: mat4
```
