/**********************************************************************************
*                     Copyright (c) 2013-2015 Carson Brownlee
*         Texas Advanced Computing Center, University of Texas at Austin
*                       All rights reserved
* 
*       This library is free software; you can redistribute it and/or
* modify it under the terms of the GNU Lesser General Public
* License as published by the Free Software Foundation; either
* version 2.1 of the License, or (at your option) any later version.
* 
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
* Lesser General Public License for more details.
* 
* You should have received a copy of the GNU Lesser General Public
* License along with this library; if not, write to the Free Software
* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
**********************************************************************************/

#ifndef GvtRENDERABLE_H
#define GvtRENDERABLE_H

#include <Interface/MantaInterface.h>
#include <Interface/Scene.h>
#include <Interface/Object.h>
#include <Interface/Context.h>
#include <Core/Geometry/BBox.h>
#include <Core/Exceptions/Exception.h>
#include <Core/Exceptions/InternalError.h>
#include <Model/Instances/Instance.h>
#include <Model/TexCoordMappers/UniformMapper.h>
#include <Model/Groups/Group.h>
#include <Model/Primitives/MeshTriangle.h>
#include <Model/Primitives/PrimitiveCommon.h>

#include "defines.h"
#include "Renderable.h"

#include <cassert>

using namespace Manta;

struct GvtData : public GeometryData
{
};

//instead of sotring the entire display list, keep track of each
//begin end segment as a seperate item
//IMPORTANT:: Need to add as to work queue when mrenderable is finished, but only if it's MESH isn't empty!!!!!!
class GvtRenderable : public Renderable
{
public:
  GvtRenderable(GeometryGenerator* gen) :Renderable(gen) {}
  virtual ~GvtRenderable() {}
  virtual void setGenerator(GeometryGenerator* gen)
  {
    _generator = gen;
    gen->setData(_data);
  }
  GvtData* _data;
};

#endif
