
/*
  For more information, please see: http://software.sci.utah.edu

  The MIT License

  Copyright (c) 2005-2006
  Scientific Computing and Imaging Institute, University of Utah

  License for the specific language governing rights and limitations under
  Permission is hereby granted, free of charge, to any person obtaining a
  copy of this software and associated documentation files (the "Software"),
  to deal in the Software without restriction, including without limitation
  the rights to use, copy, modify, merge, publish, distribute, sublicense,
  and/or sell copies of the Software, and to permit persons to whom the
  Software is furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included
  in all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
  OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
  DEALINGS IN THE SOFTWARE.
*/

#include <Interface/MantaInterface.h>

#include <Engine/Factory/Factory.h>

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
#include <Model/Materials/Flat.h>
#include <Model/Groups/Group.h>
#include <Model/Primitives/Parallelogram.h>
#include <Model/Primitives/Sphere.h>
#include <Model/TexCoordMappers/UniformMapper.h>
#include <Core/Thread/Thread.h>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;
// using namespace Manta;

#if HAVE_IEEEFP_H
#include <ieeefp.h>
#endif

static void
printList(ostream& out, const Manta::Factory::listType& list, int spaces=0)
{
  for(int i=0;i<spaces;i++)
    out << ' ';
  for(Manta::Factory::listType::const_iterator iter = list.begin();
      iter != list.end(); ++iter){
    if(iter != list.begin())
      out << ", ";
    out << *iter;
  }
  out << "\n";
}

static void usage(Manta::Factory* rtrt)
{

  cerr << "Manta Interactive Ray Tracer" << "\n\n";

  cerr << Manta::getLicenseString() << "\n";

  cerr << "Revision information:\n";

  cerr << Manta::getAboutString() << "\n\n";

  cerr << "Usage: manta [options]\n";
  cerr << "Valid options are:\n";
  cerr << " -[-]h[elp]      - Print this message and exit\n";
  cerr << " -bench [N [M]]  - Time N frames after an M frame warmup period and print out the framerate,\n";
  cerr << "                   default N=100, M=10\n";
  cerr << " -np N           - Use N processors\n";
  cerr << " -res NxM        - Use N by M pixels for rendering (needs the x).\n";
  cerr << " -imagedisplay S - Use image display mode named S, valid modes are:\n";
  printList(cerr, rtrt->listImageDisplays(), 4);
  cerr << " -imagetype S    - Use image display mode named S, valid modes are:\n";
  printList(cerr, rtrt->listImageTypes(), 4);
  cerr << " -ui S           - Use the user interface S, valid options are:\n";
  printList(cerr, rtrt->listUserInterfaces(), 4);
  cerr << " -shadows S      - Use S mode for rendering shadows, valid modes are:\n";
  printList(cerr, rtrt->listShadowAlgorithms(), 4);
  cerr << " -imagetraverser S - Use S method for image traversing, valid modes are:\n";
  printList(cerr, rtrt->listImageTraversers(), 4);
  cerr << " -pixelsampler S - Use S method for pixel sampling, valid modes are:\n";
  printList(cerr, rtrt->listPixelSamplers(), 4);
  cerr << " -camera S       - User camera model S, valid cameras are:\n";
  printList(cerr, rtrt->listCameras(), 4);
  cerr << " -bbcamera       - Positions the lookat in the center of the\n";
  cerr << "                   scene, and the eye point far enough away to\n";
  cerr << "                   see the entire scene.\n";
  cerr << " -renderer S     - Use renderer S, valid renderers are:\n";
  printList(cerr, rtrt->listRenderers(), 2);
  cerr << " -scene S        - Render Scene S\n";
  cerr << " -t, --timeview[=\"args\"] - Display a scaled view of the time it took to render some pixels.\n";
  cerr << " --bgcolor [option] - Change the color the background.  Options are:\n"
       << "           o [colorName]      (such as black or white)\n"
       << "           o [RGB8     r g b] (where components range [0,255])\n"
       << "           o [RGBfloat r g b] (where components range [0,1])\n";
  cerr << " --maxdepth [val] - The maximum ray depth\n";
  Manta::Thread::exitAll(1);
}

class BenchHelper {
public:
  BenchHelper(Manta::MantaInterface* rtrt, long num_frames, int output_format);
  void start(int, int);
  void stop(int, int);

  enum {
    fps_only,
    dart_format,
    default_format // leave me last
  };
private:
  Manta::MantaInterface* rtrt;
  double start_time;
  long num_frames;
  int output_format;
};

BenchHelper::BenchHelper(Manta::MantaInterface* rtrt, long num_frames, int output_format)
  : rtrt(rtrt), num_frames(num_frames), output_format(output_format)
{
}

void BenchHelper::start(int, int)
{
  start_time = Manta::Time::currentSeconds();
}

void BenchHelper::stop(int, int)
{
  double dt = Manta::Time::currentSeconds()-start_time;
  double fps = num_frames/dt;
  switch(output_format) {
  case fps_only:
    std::cout << "fps: " << fps << std::endl;
    break;
  case dart_format:
    std::cout << "<DartMeasurement name=\"frames_per_second\" type=\"numeric/double\">"<<fps<<"</DartMeasurement>\n";
    std::cout << "<DartMeasurement name=\"total_time\" type=\"numeric/double\">"<<dt<<"</DartMeasurement>\n";
    break;
  case default_format:
  default:
    cout << "Benchmark completed in " << dt
         << " seconds (" << num_frames << " frames, "
         << fps << " frames per second)" << std::endl;
  }
  rtrt->finish();
  delete this;
}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

// Default Scene.

