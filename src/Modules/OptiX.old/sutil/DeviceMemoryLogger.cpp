
/*
 * Copyright (c) 2008 - 2009 NVIDIA Corporation.  All rights reserved.
 *
 * NVIDIA Corporation and its licensors retain all intellectual property and proprietary
 * rights in and to this software, related documentation and any modifications thereto.
 * Any use, reproduction, disclosure or distribution of this software and related
 * documentation without an express license agreement from NVIDIA Corporation is strictly
 * prohibited.
 *
 * TO THE MAXIMUM EXTENT PERMITTED BY APPLICABLE LAW, THIS SOFTWARE IS PROVIDED *AS IS*
 * AND NVIDIA AND ITS SUPPLIERS DISCLAIM ALL WARRANTIES, EITHER EXPRESS OR IMPLIED,
 * INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE.  IN NO EVENT SHALL NVIDIA OR ITS SUPPLIERS BE LIABLE FOR ANY
 * SPECIAL, INCIDENTAL, INDIRECT, OR CONSEQUENTIAL DAMAGES WHATSOEVER (INCLUDING, WITHOUT
 * LIMITATION, DAMAGES FOR LOSS OF BUSINESS PROFITS, BUSINESS INTERRUPTION, LOSS OF
 * BUSINESS INFORMATION, OR ANY OTHER PECUNIARY LOSS) ARISING OUT OF THE USE OF OR
 * INABILITY TO USE THIS SOFTWARE, EVEN IF NVIDIA HAS BEEN ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGES
 */

#include "DeviceMemoryLogger.h"
#include <string>
#include <vector>
#include <algorithm>


void DeviceMemoryLogger::logDeviceDescription(optix::Context& context, std::ostream& out)
{
  unsigned int numDevices = optix::Context::getDeviceCount();
  std::vector<int> devices = context->getEnabledDevices();
  for( unsigned int i = 0; i < numDevices; ++i)
  {
    int device = i;

    // Device name
    char name[256];
    RTresult result = rtDeviceGetAttribute(device, RT_DEVICE_ATTRIBUTE_NAME, sizeof( name ), name);
    if( result != RT_SUCCESS ) {
      std::cerr << "DeviceMemoryLogger::logDeviceDescription(): rtDeviceGetAttribute(RT_DEVICE_ATTRIBUTE_NAME) failed ("
                << result << ")" << std::endl;
      return;
    }

    // Device compute capability
    int computeCaps[2];
    result = rtDeviceGetAttribute(device, RT_DEVICE_ATTRIBUTE_COMPUTE_CAPABILITY, sizeof(computeCaps), &computeCaps);
    if( result != RT_SUCCESS ) {
      std::cerr << "DeviceMemoryLogger::logDeviceDescription(): rtDeviceGetAttribute(RT_DEVICE_ATTRIBUTE_COMPUTE_CAPABILITY) failed ("
                << result << ")" << std::endl;
      return;
    }
    
    // Total memory available
    RTsize total_mem;
    result = rtDeviceGetAttribute(device, RT_DEVICE_ATTRIBUTE_TOTAL_MEMORY, sizeof(total_mem), &total_mem);
    if( result != RT_SUCCESS ) {
      std::cerr << "DeviceMemoryLogger::logDeviceDescription(): rtDeviceGetAttribute(RT_DEVICE_ATTRIBUTE_TOTAL_MEMORY) failed ("
                << result << ")" << std::endl;
      return;
    }

    bool enabled = std::find(devices.begin(), devices.end(), device) != devices.end();

    out << "Device " << device << " ("<< (enabled? " enabled": "disabled") << "): '" 
        << name << "' (compute " << computeCaps[0] << "." << computeCaps[1]
        << ") mem " << total_mem / ( 1024*1024 ) << "MB" << std::endl;
  }
}


void DeviceMemoryLogger::logCurrentMemoryUsage( optix::Context& context, std::ostream& out,
                                                const std::string& label )
{
  out << label;

  std::vector<int> devices = context->getEnabledDevices();
  for( size_t i = 0; i < devices.size(); ++i)
  {
    int device = devices[i];

    // Query memory usage, total memory first
    RTsize total_mem;
    RTresult result = rtDeviceGetAttribute(device, RT_DEVICE_ATTRIBUTE_TOTAL_MEMORY, sizeof(total_mem), &total_mem);
    if( result != RT_SUCCESS ) {
      std::cerr << "DeviceMemoryLogger::logDeviceDescription(): rtDeviceGetAttribute(RT_DEVICE_ATTRIBUTE_TOTAL_MEMORY) failed ("
                << result << ")" << std::endl;
      return;
    }
    // Now for the free memory
    RTsize free_mem = context->getAvailableDeviceMemory(device);

    free_mem  /= (1024*1024);
    total_mem /= (1024*1024);
    out << "Dev" << device << ": " << total_mem-free_mem << "/" << total_mem << "MB used  ";
  }

  int paged = 0, paging_forced_off = 0;
  rtContextGetAttribute(context->get(), RT_CONTEXT_ATTRIBUTE_GPU_PAGING_ACTIVE, sizeof(paged), &paged);
  rtContextGetAttribute(context->get(), RT_CONTEXT_ATTRIBUTE_GPU_PAGING_FORCED_OFF, sizeof(paging_forced_off), &paging_forced_off);
  if(paged)
    out << "PAGING IS OCCURRING.";
  else if(paging_forced_off)
    out << "PAGING IS FORCED OFF.";
  else
    out << "PAGING IS NOT NEEDED.";
}

