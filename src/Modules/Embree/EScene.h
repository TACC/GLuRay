#ifndef ESCENE_H
#define ESCENE_H

#include <Core/GLTypes.h>

#include <Model/Groups/DynBVH.h>

#include <Interface/MantaInterface.h>

#include <Engine/Factory/Factory.h>
#include <Engine/Factory/Create.h>

#include <Core/Util/Args.h>
#include <Core/Util/Callback.h>
#include <Interface/Scene.h>
#include <Interface/Object.h>
#include <Interface/Camera.h>
#include <Interface/UserInterface.h>
#include <Interface/Context.h>
#include <Core/Geometry/BBox.h>
#include <Core/Exceptions/Exception.h>
#include <Core/Exceptions/InternalError.h>
#include <Core/Exceptions/IllegalArgument.h>
#include <Core/Exceptions/UnknownComponent.h>
#include <Core/Exceptions/UnknownColor.h>
#include <Core/Thread/Time.h>
#include <Core/Util/About.h>
#include <Engine/PixelSamplers/TimeViewSampler.h>
#include <Model/Cameras/PinholeCamera.h>
#include <Model/Cameras/ThinLensCamera.h>

// Default scene includes.
#include <Core/Color/ColorDB.h>
#include <Interface/LightSet.h>
#include <Model/AmbientLights/ConstantAmbient.h>
#include <Model/Backgrounds/ConstantBackground.h>
#include <Model/Backgrounds/TextureBackground.h>
#include <Model/Lights/PointLight.h>
#include <Model/Textures/Constant.h>
#include <Model/Textures/CheckerTexture.h>
#include <Model/Textures/MarbleTexture.h>
#include <Model/Materials/Phong.h>
#include <Model/Materials/Lambertian.h>
#include <Model/Materials/Flat.h>
#include <Model/Groups/Group.h>
#include <Model/Primitives/Parallelogram.h>
#include <Model/Primitives/Sphere.h>
#include <Model/Primitives/WaldTriangle.h>
#include <Model/Primitives/MeshTriangle.h>
#include <Model/Primitives/Cylinder.h>
#include <Model/TexCoordMappers/UniformMapper.h>
#include <Core/Thread/Thread.h>
#include <Model/Instances/Instance.h>
//#include <Model/Materials/AmbientOcclusion.h>
//#include <Engine/Display/OpenGLDisplay.h>
#include <Core/Thread/Runnable.h>
#include <Core/Thread/ThreadGroup.h>
#include <Engine/Display/SyncDisplay.h>
#include <Engine/Display/NullDisplay.h>
#include <Image/SimpleImage.h>
#include <Model/TexCoordMappers/LinearMapper.h>
#include <Model/Materials/CopyTextureMaterial.h>
#include <Model/Backgrounds/EnvMapBackground.h>
#include <Model/Textures/ImageTexture.h>
#include <Model/Materials/MetalMaterial.h>
#include <Core/Geometry/AffineTransform.h>

#include <vector>



//class ERenderable;
class Renderable;

// a manta scene consisting of a scene->acceleration structure->world
// objects should be added to world
// all objects should be added to queues for deletion
class EScene
{
  public:
    EScene();
    ~EScene();

    void build();
//    void setBGColor(const Manta::Color& color);

    Manta::Vector camera_eye;
    Manta::Vector camera_dir;
    Manta::Vector camera_up;
    float camera_hfov, camera_vfov;
    float focal_distance, aperture;
    std::string camera_type;
    Manta::Color bgcolor;
    std::string env_filename;
    int icounter;


    //list of renderables to be deleted upon next scene creation
    std::vector<Renderable*> renderables;
    std::vector<GRInstance> instances;
};


#endif
