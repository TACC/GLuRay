GLuRay
======

An OpenGL interceptor using Ray Tracing backends for photorealistic rendering.

         <h2>prerequisites:</h2>
<p>1.  the latest build of Manta.  Enable the DYNBV_APPROX option in Manta for significantly faster acceleration structure build times.<br />
2.  cmake [ccmake recommended]</p>
<h2>building:</h2>
<p>mkdir build<br />
cd build<br />
ccmake ..</p>
<p>in CMAKE options you will need to set the location of MANTA_SRC and MANTA_BUILD_PREFIX.</p>
<h2>building with Embree suport:</h2>
<p>1.  Currently, Manta is still required and has to be built with USE_SSE disabled in order to build with Embree support.<br />
2.  In build directory, ccmake .<br />
3.  Enable USE_EMBREE and then specify the root folder of the Embree install as well as a build folder.<br />
4.  Configure, Generate, and then run &#8220;make&#8221;</p>
<p>NOTE: Embree is setup to use progressive rendering while most applications are event driven.  Be sure to run the path tracer with sufficient samples per pixel to get a decent image.  </p>
<h2>running:</h2>
<p>./gluray glxgears</p>
<h2>environment variables:</h2>
<p>GLURAY_RENDER_MODE [GLREADPIXELS, GLXSWAPBUFFERS, GLFINISH, GLFLUSH]<br />
GLURAY_CONFIG
<path to config file>
<h2>configuration files:</h2>
<p>config files are in the form: -apply [-spp <number of samples per pixel] [ -threads <int> ] [-skydome <int number>  <float size of dome> <float 0-1 intensity>] [-reflectivity <float 0-1>] [-env <string path to .hdr file>] [-ao <int number> <float cutoff distance> <float intensity>] [-phong] [-shadows] [-no_gl_lights] [-rotate <float speed> <float offset>] [-plane] [-thinLens <float focaldistance> <float aperture>] [-pinhole] [-lambertian] [-thinDielectric] [-metal] [-transparent] [-orenNayar] [-write_to_file <string file or may say generated to generate file names for each frame>]</p>
<p>example configuration files:<br />
 &#8220;-apply -spp 1 -threads 8 -phong -fov 30 -ao 36 10.0 0.8&#8243;<br />
&#8220;-apply -spp 8 -threads 8 -skyDome 32 100 0.8 -reflectivity 0.1 -env /Users/username/data/lightProbes/campus_probe.hdr -ao 36 10.0 0.8 -phong -fov 45 -shadows -no_gl_lights&#8221;</p>
<h2> Example run </h2>
<p>Here is an example of running glxgears with Embree.  </p>
<p>Configuration file:  &#8220;-apply -spp 256 -threads 16 -skyDome 32 100 0.8 -reflectivity 0.1 -env /work/01336/carson/data/lightProbes/rnl_probe.pfm -ao 36 10.0 0.8 -phong -fov 45 -shadows&#8221;</p>
<p>GLURAY_CONFIG=/home1/01336/carson/gluray_scripts/shiny_embree.cfg ./gluray glxgears</p>
<p><a href="http://enja.org/carson/wp-content/uploads/2013/04/Screen-Shot-2013-10-02-at-11.18.00-AM1.png"><img src="http://enja.org/carson/wp-content/uploads/2013/04/Screen-Shot-2013-10-02-at-11.18.00-AM1.png" alt="" title="Screen Shot 2013-10-02 at 11.18.00 AM"  width="256" height="256" class="aligncenter size-full wp-image-199" /></a></p>
<h2>building the GUI</h2>
<p>the GUI is located in glurayGUI folder which can be built with Qt.  Currently this is disabled and hasn&#8217;t been tested with newer versions of GLuRay, you will need to modify defines.h to enable run_client.  The client is run by first running the GUI program using GLuRay and then launching GLuRay instances with other programs which will then attach to the GUI.</p>
<p>GLuRay was written by Carson Brownlee at the University of Utah.  It is based on SpyGlassGL and the Manta ray tracer.</p>
    -->
  </div>