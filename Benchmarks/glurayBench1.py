from paraview import servermanager
from time import time
import timeit
import pickle

filename = "test.bench"
file = open(filename, 'w')
if not servermanager.ActiveConnection:
	connection = servermanager.Connect()

coneSource = servermanager.sources.ConeSource()
shrinkFilter = servermanager.filters.ShrinkFilter(Input=coneSource)
view = servermanager.CreateRenderView()
rep = servermanager.CreateRepresentation(shrinkFilter, view)

view.ResetCamera()
total_time  = 0.0
for i in range(0,500):
  t1 = time()
  view.StillRender()
  t2 = time()
  elapsed = t2-t1
  total_time += elapsed
  pickle.dump("elapsed time: " + str(elapsed), file)
  print "total time: " + str(total_time)
  print "avg time: " + str(total_time/500)
