#include <GL/glx.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <unistd.h>
static int attributeListSgl[] = { GLX_RGBA, GLX_RED_SIZE, 1,
  /*get the deepest buffer with 1 red bit*/
  GLX_GREEN_SIZE, 1, GLX_BLUE_SIZE, 1, None };
static int attributeListDbl[] = { GLX_RGBA, GLX_DOUBLEBUFFER, /*In case single buffering is not supported*/ GLX_RED_SIZE, 1, GLX_GREEN_SIZE, 1, GLX_BLUE_SIZE, 1, None };
static Bool WaitForNotify(Display *d, XEvent *e, char *arg) { return (e->type == MapNotify) && (e->xmap.window == (Window)arg); }


int main(int argc, char **argv) {
  Display *dpy; XVisualInfo *vi;
  Colormap cmap; XSetWindowAttributes swa; Window win; GLXContext cx; XEvent event; int swap_flag = 1; /* get a connection */ dpy = XOpenDisplay(0); /* get an appropriate visual */
  vi = glXChooseVisual(dpy, DefaultScreen(dpy), attributeListSgl);
  if (vi == NULL) {
    vi = glXChooseVisual(dpy, DefaultScreen(dpy), attributeListDbl);
    swap_flag = 1;
  }
  /* create a GLX context */ cx = glXCreateContext(dpy, vi, 0, GL_TRUE);
  /* create a color map */ cmap = XCreateColormap(dpy, RootWindow(dpy, vi->screen), vi->visual, AllocNone);
  /* create a window */
  swa.colormap = cmap; swa.border_pixel = 0;
  swa.event_mask = StructureNotifyMask; win = XCreateWindow(dpy, RootWindow(dpy, vi->screen), 0, 0, 512, 512, 0, vi->depth, InputOutput, vi->visual, CWBorderPixel|CWColormap|CWEventMask, &swa);
  XMapWindow(dpy, win);
  XIfEvent(dpy, &event, WaitForNotify, (char*)win);
  /* connect the context to the window */
  glXMakeCurrent(dpy, win, cx);
  glViewport(0,0,512,512);
  glMatrixMode   ( GL_PROJECTION );  // Select The Projection Matrix
  glLoadIdentity ( );                // Reset The Projection Matrix
  gluPerspective ( 80, 1, 1.0, 5000.0 );

  glMatrixMode   ( GL_MODELVIEW );  // Select The Model View Matrix
  glLoadIdentity ( );    // Reset The Model View Matrix
  /* clear the buffer */
  glClearColor(1,1,0,1);
  GLuint list = glGenLists(1);
  glNewList(list, GL_COMPILE);


  glBegin(GL_TRIANGLES);
  glColor3f(1.0f,0.0f,0.0f);			// Red
  glVertex3f( 0.0f, 1.0f, 0.0f);			// Top Of Triangle (Front)
  glColor3f(0.0f,1.0f,0.0f);			// Green
  glVertex3f(-1.0f,-1.0f, 1.0f);			// Left Of Triangle (Front)
  glColor3f(0.0f,0.0f,1.0f);			// Blue
  glVertex3f( 1.0f,-1.0f, 1.0f);			// Right Of Triangle (Front)

  glColor3f(1.0f,0.0f,0.0f);			// Red
  glVertex3f( 0.0f, 1.0f, 0.0f);			// Top Of Triangle (Right)
  glColor3f(0.0f,0.0f,1.0f);			// Blue
  glVertex3f( 1.0f,-1.0f, 1.0f);			// Left Of Triangle (Right)
  glColor3f(0.0f,1.0f,0.0f);			// Green
  glVertex3f( 1.0f,-1.0f, -1.0f);			// Right Of Triangle (Right)

  glColor3f(1.0f,0.0f,0.0f);			// Red
  glVertex3f( 0.0f, 1.0f, 0.0f);			// Top Of Triangle (Back)
  glColor3f(0.0f,1.0f,0.0f);			// Green
  glVertex3f( 1.0f,-1.0f, -1.0f);			// Left Of Triangle (Back)
  glColor3f(0.0f,0.0f,1.0f);			// Blue
  glVertex3f(-1.0f,-1.0f, -1.0f);			// Right Of Triangle (Back)

  glColor3f(1.0f,0.0f,0.0f);			// Red
  glVertex3f( 0.0f, 1.0f, 0.0f);			// Top Of Triangle (Left)
  glColor3f(0.0f,0.0f,1.0f);			// Blue
  glVertex3f(-1.0f,-1.0f,-1.0f);			// Left Of Triangle (Left)
  glColor3f(0.0f,1.0f,0.0f);			// Green
  glVertex3f(-1.0f,-1.0f, 1.0f);			// Right Of Triangle (Left)
  glEnd();						// Done Drawing The Pyramid
  glEndList();
  GLuint list2 = glGenLists(1);
  glNewList(list2, GL_COMPILE);
  glCallList(list);
  glEndList();
  int i;
  for(i = 0; i < 5; i++)
  {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);     // Clear The Screen And The Depth Buffer
    glLoadIdentity();                                       // Reset The View
    glTranslatef(-1.5f,0.0f,-16.0f);                         // Move Left And Into The Screen

    glRotatef(0.5,0.0f,1.0f,0.0f);                          // Rotate The Pyramid On It's Y Axis
    glCallList(list);
    if (swap_flag) glXSwapBuffers(dpy,win);
    else glFinish();
  }
  /* wait a while */ sleep(5);
  return 0;
}
