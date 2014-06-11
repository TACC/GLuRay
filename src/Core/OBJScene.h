#ifndef OBJSCENE_H
#define OBJSCENE_H

#include <ostream>
#include <vector>
//#include <boost/numeric/ublas/vector.hpp>
//#include <boost/numeric/ublas/io.hpp>

//typedef float3 boost::numeric::ublas::vector<float>;
#include <Interface/MantaInterface.h>
#include <Core/Geometry/BBox.h>
//using namespace Manta;

typedef Manta::Vector float3;

class OBJVertex
{
public:
  OBJVertex(float x_=0.0, float y_=0.0, float z_=0.0, float w_=1.0) : x(x_), y(y_), z(z_), w(w_) {}
  float x,y,z,w;
};

std::ostream& operator<<(std::ostream& lh, const OBJVertex& rh)
{
  lh << "v " << rh.x << " " << rh.y << " " << rh.z << " " << rh.w;
  return lh;
}

class OBJTexCoord
{
public:
  OBJTexCoord(float u_=0.0, float v_=0.0, float w_=0.0) : u(u_), v(v_), w(w_) {}
  float u,v,w;
};
std::ostream& operator<<(std::ostream& lh, const OBJTexCoord& rh)
{
  lh << "vt " << rh.u << " " << rh.v << " " << rh.w ;
  return lh;
}

class OBJNormal
{
public:
  OBJNormal(float x_=0.0, float y_=1.0, float z_=0.0, float w_=1.0) : x(x_), y(y_), z(z_), w(w_) {}
  float x,y,z,w;
};
std::ostream& operator<<(std::ostream& lh, const OBJNormal& rh)
{
  lh << "vn " << rh.x << " " << rh.y << " " << rh.z << " " << rh.w;
  return lh;
}

class OBJFace
{
public:
  std::vector<size_t> vertexIndices;
  std::vector<size_t> textureIndices;
  std::vector<size_t> normalIndices;
};
std::ostream& operator<<(std::ostream& lh, const OBJFace& rh)
{
  lh << "f ";
  for(size_t vi = 0 ; vi < rh.vertexIndices.size(); vi++)
  {
    lh << rh.vertexIndices[vi];
    if (vi < rh.textureIndices.size())
    {
      lh << "/" << rh.textureIndices[vi];
    }
    if (vi < rh.normalIndices.size())
    {
      if (vi >= rh.textureIndices.size())
        lh << "/";
      lh << "/" << rh.normalIndices[vi];
    }
    lh << " ";
  }
  return lh;
}

class OBJMaterial
{
  public:
  OBJMaterial(std::string name_="Untitled", float3 Ka_=float3(1,1,1), float3 Kd_=float3(1,1,1), float3 Ks_=float3(1,1,1), float Ns_=10.0, float Tr_=1.0, unsigned int illum_=2) : name(name_), Ka(Ka_), Kd(Kd_), Ks(Ks_), Ns(Ns_), Tr(Tr_), illum(illum_)
  {};
  std::string name;
  float3 Ka, Kd, Ks;
  float Ns, Tr;
  unsigned int illum;
};
std::ostream& operator<<(std::ostream& lh, const OBJMaterial& rh)
{
  lh << "#Material : \"" << rh.name << "\"" << std::endl
    << "newmtl " << rh.name << std::endl;
  lh << "Ka " << rh.Ka[0] << " " << rh.Ka[1] << " " << rh.Ka[2] << std::endl;
  lh << "Kd " << rh.Kd[0] << " " << rh.Kd[1] << " " << rh.Kd[2] << std::endl;
  lh << "Ks " << rh.Ks[0] << " " << rh.Ks[1] << " " << rh.Ks[2] << std::endl;
  lh << "Ns " << rh.Ns << std::endl;
  lh << "Tr " << rh.Tr << std::endl;
  lh << "illum 2 " << rh.Ns << std::endl;
  return lh;
}

class OBJGroup
{
public:
  OBJGroup(std::string name_="Untitled", std::string material_="Untitled") : name(name_), material(material_) {}
  std::vector<OBJFace> faces;
  std::string material;
  std::string name;
};
std::ostream& operator<<(std::ostream& lh, const OBJGroup& rh)
{
  lh << "#Group : \"" << rh.name << "\"" << std::endl
    << "usemtl " << rh.material << std::endl;
  lh << "# " << rh.faces.size() << " Faces" << std::endl;
  for (std::vector<OBJFace>::const_iterator itr = rh.faces.begin(); itr != rh.faces.end(); itr++)
  {
    lh << *itr << std::endl;
  }
  return lh;
}

class OBJScene
{
public:
  void SaveOBJToFile(std::string file)
  {
  }
  void SaveTextureToFile(std::string file)
  {
  }

  std::vector<OBJVertex> vertices;
  std::vector<OBJTexCoord> texCoords;
  std::vector<OBJNormal> normals;
  std::vector<OBJGroup> groups;
  std::vector<OBJMaterial> materials;
  std::vector<size_t> material_indices;
};
std::ostream& operator<<(std::ostream& lh, const OBJScene& rh)
{

  lh << "# " << rh.materials.size() << " Materials " << std::endl;
  if (rh.materials.size() > 0)
  {
    for (std::vector<OBJMaterial>::const_iterator itr = rh.materials.begin(); itr != rh.materials.end(); itr++)
    {
      lh << *itr << std::endl;
    }
  }
  //lh << "# Materials" << std::endl;
  //for (std::vector<OBJMaterials>::const_iterator itr = rh.materials.begin(); itr != rh.materials.end(); itr++)
  //{
  //lh << *itr << std::endl;
  //}
  //lh << "mtllib fiu.mtl" << std::endl;
  printf("outputting vertices\n");
  fflush(stdout);
  lh << "# " << rh.vertices.size() << " Vertices (x,y,z,[w])" << std::endl;
  {
    std::stringstream ss;
    int counter =0;
  for (std::vector<OBJVertex>::const_iterator itr = rh.vertices.begin(); itr != rh.vertices.end(); itr++)
  {
      if (++counter >= 999999)
      {
        lh << ss.str();
        ss.str("");
        counter = 0;
      }
    ss << *itr << std::endl;
  }
  lh << ss.str();
  }
  printf("outputting texture coords\n");
  fflush(stdout);
  lh << "# " << rh.texCoords.size() << " Texture coordinates (u,v,[w])" << std::endl;
  {
  std::stringstream ss;
  for (std::vector<OBJTexCoord>::const_iterator itr = rh.texCoords.begin(); itr != rh.texCoords.end(); itr++)
  {
    ss << *itr << std::endl;
  }
  lh << ss.str();
  }
  printf("outputting normals\n");
  fflush(stdout);
  lh << "# " << rh.normals.size() << " Normals (x,y,z).  May not be normalized" << std::endl;
  {
  std::stringstream ss;
  for (std::vector<OBJNormal>::const_iterator itr = rh.normals.begin(); itr != rh.normals.end(); itr++)
  {
    ss << *itr << std::endl;
  }
  lh << ss.str();
  }
  printf("outputting groups\n");
  fflush(stdout);
  lh << "# " << rh.groups.size() << " Groups " << std::endl;
  {
  std::stringstream ss;
  int counter =0;
  //for (std::vector<OBJGroup>::const_iterator itr = rh.groups.begin(); itr != rh.groups.end(); itr++)
  {
    //lh << *itr << std::endl;
  }
  //lh << rh.groups[0];
  for (std::vector<OBJGroup>::const_iterator itr = rh.groups.begin(); itr != rh.groups.end(); itr++)
  {
      if (++counter >= 999999)
      {
        lh << ss.str();
        ss.str("");
        counter = 0;
      }
    ss << *itr << std::endl;
  }
  lh << ss.str();
  }
  for (size_t gi = 0; gi < rh.groups.size(); gi++)
  {
    //lh << rh.groups[gi] << std::endl;
  }
  printf("obj export completed\n");
  fflush(stdout);


  return lh;
}

#endif
