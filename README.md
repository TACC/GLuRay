<h1>GLuRay - <a href="http://tacc.github.io/GLuRay/">http://tacc.github.io/GLuRay/</a></h1>
======

<h2>An OpenGL inter ceptor using Ray Tracing backends for photorealistic rendering</h2>

<h3>prerequisites:</h3>
<p>
<ol>
<li>the latest build of Manta.  Enable the DYNBV_APPROX option in Manta for significantly faster acceleration structure build times.</li>
<li>cmake [ccmake recommended]</li>
</ol>

<h3>building:</h3>
<p>
<ol>
<li>mkdir build</li>
<li>cd build</li>
<li>ccmake ..</li>
</ol>
</p>
<p>in CMAKE options you will need to set the location of MANTA_SRC and MANTA_BUILD_PREFIX.</p>


<h3>building with Embree support:</h3>
<p>
<ol>
<li>Currently, Manta is still required and has to be built with USE_SSE disabled in order to build with Embree support.</li>
<li>In build directory, ccmake .</li>
<li>Enable USE_EMBREE and then specify the root folder of the Embree install as well as a build folder.</li>
<li>Configure, Generate, and then run &#8220;make&#8221;</li>
</ol>
</p>
<p>NOTE: Embree is setup to use progressive rendering while most applications are event driven.  Be sure to run the path tracer with sufficient samples per pixel to get a decent image.  </p>


<h3>building with OptiX support:</h3>
<p>
Please check out the 'optix' branch of GLuRay and build using CMake.
</p>

<h3>running:</h3>
<p>./gluray glxgears</p>


<h3>environment variables:</h3>
<p>
<ul>
<li>GLURAY_RENDER_MODE [GLREADPIXELS, GLXSWAPBUFFERS, GLFINISH, GLFLUSH]</li>
<li>GLURAY_CONFIG &lt;path to config file&gt;</li>
</ul>
</p>

<h3>configuration files:</h3>
<p>
config files contain '-apply' followed by any of the following options:
<ul>
<li>-spp &lt;number of samples per pixel&gt;</li>
<li>-threads &lt;int&gt;</li>
<li>-skydome &lt;int number&gt;  &lt;float size of dome&gt; &lt;float 0-1 intensity&gt;</li> 
<li>-reflectivity &lt;float 0-1&gt;</li>
<li>-env &lt;string path to .hdr file&gt;</li> 
<li>-ao &lt;int number&gt; &lt;float cutoff distance&gt; &lt;float intensity&gt;</li>
<li>-phong</li>
<li>-shadows</li>
<li>-no_gl_lights</li>
<li>-rotate &lt;float speed&gt; &lt;float offset&gt;</li>
<li>-plane</li> 
<li>-thinLens &lt;float focaldistance&gt; &lt;float aperture&gt;</li>
<li>-pinhole</li> 
<li>-lambertian</li> 
<li>-thinDielectric</li> 
<li>-metal</li> 
<li>-transparent</li> 
<li>-orenNayar</li> 
<li>-write_to_file &lt;string file or may say generated to generate file names for each frame&gt;</li>
</ul>
</p>

<p>example configuration files:
<ul>
<li>-apply -spp 1 -threads 8 -phong -fov 30 -ao 36 10.0 0.8</li>
<li>-apply -spp 8 -threads 8 -skyDome 32 100 0.8 -reflectivity 0.1 -env /Users/username/data/lightProbes/campus_probe.hdr -ao 36 10.0 0.8 -phong -fov 45 -shadows -no_gl_lights</li>
</ul>
</p>

<h3> Example Run </h3>
<p>Here is an example of running glxgears with Embree.  </p>
<p>Configuration file:  <i>-apply -spp 256 -threads 16 -skyDome 32 100 0.8 -reflectivity 0.1 -env /work/01336/carson/data/lightProbes/rnl_probe.pfm -ao 36 10.0 0.8 -phong -fov 45 -shadows</i></p>
<p>GLURAY_CONFIG=/home1/01336/carson/gluray_scripts/shiny_embree.cfg ./gluray glxgears</p>
<p><a href="http://enja.org/carson/wp-content/uploads/2013/04/Screen-Shot-2013-10-02-at-11.18.00-AM1.png"><img src="http://enja.org/carson/wp-content/uploads/2013/04/Screen-Shot-2013-10-02-at-11.18.00-AM1.png" alt="" title="Screen Shot 2013-10-02 at 11.18.00 AM"  width="256" height="256" class="aligncenter size-full wp-image-199" /></a></p>

<h3>building the GUI</h3>
<p>the GUI is located in glurayGUI folder which can be built with Qt.  Currently this is disabled and has not been tested with newer versions of GLuRay, you will need to modify defines.h to enable run_client.  The client is run by first running the GUI program using GLuRay and then launching GLuRay instances with other programs which will then attach to the GUI.</p>
<p>GLuRay was written by Carson Brownlee, originally at the University of Utah with continuted development at the Texas Advanced Computing Center at the University of Texas at Austin.  It is based on SpyGlassGL and the Manta ray tracer.</p>
