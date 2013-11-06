#ifndef GLURAYRENDERPARAMETERS_H
#define GLURAYRENDERPARAMETERS_H

#include <Core/Geometry/Vector.h>
#include <Model/Materials/Volume.h>

class GLuRayRenderParameters
{
 public:
  GLuRayRenderParameters()
    : num_samples(1), num_threads(8), num_ao_samples(0), ao_distance(10.0), ao_intensity(0.1f), env_map(""), shadows(false), num_skyDome_lights(0),
    camera("pinhole"), camera_hfov(85.0), camera_vfov(85.0), focalDistance(2.0), aperture(0.01), reflectivity(0.0), write_to_file(""),
    width(512), height(512), material("phong"), bgcolor(0,0,0,0), ri(1.5), ri2(1.0), skyDome_size(1.0), skyDome_intensity(0.0), rotate_speed(0), rotate_offset(0), add_plane(false), use_gl_lights(true), accumulate(false), eta(1.5), thickness(0.1)
      , export_obj(0)
  {
    camera_eye = Manta::Vector(0,0,0);
    camera_up = Manta::Vector(0,1,0);
    camera_dir = Manta::Vector(0,0,-1);
  }
  int num_samples;
  int num_threads;
  int num_ao_samples;
  double ao_distance;
  float ao_intensity;
  std::string env_map;
  bool shadows, add_plane;
  int num_skyDome_lights;
  std::string camera;
  Manta::Vector camera_eye, camera_dir, camera_up;
  double camera_hfov, camera_vfov;
  double focalDistance, aperture;
  double reflectivity;
  std::string write_to_file;
  int width, height;
  std::string material;
  double ri, ri2;
  Manta::RGBAColor bgcolor;
  double skyDome_size, skyDome_intensity;
  float thickness, eta;  //for thindielectric
  float roughness; //orennayar
  double rotate_speed;
  int rotate_offset;
  Manta::Vector plane_normal, plane_center;
  bool use_gl_lights;
  bool accumulate;
  unsigned int export_obj;  //frame number to export scene as obj.  Exports as out.obj if > 0.
};

#endif
