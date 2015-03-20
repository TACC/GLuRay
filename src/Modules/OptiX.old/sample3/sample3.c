
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

/*
 *  sample3.c -- Demonstration of the device query functions
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <optix.h>
#include <sutil.h>

int main(int argc, char *argv[])
{
  unsigned int num_devices;
  unsigned int version;
  unsigned int i;
  unsigned int context_device_count;
  unsigned int max_textures;
  RTcontext context;
  int* context_devices;

  RT_CHECK_ERROR_NO_CONTEXT(rtDeviceGetDeviceCount(&num_devices));
  RT_CHECK_ERROR_NO_CONTEXT(rtGetVersion(&version));

  printf("OptiX %d.%d.%d\n", version/1000, (version%1000)/10, version%10);

  printf("Number of Devices = %d\n\n", num_devices);

  for(i = 0; i < num_devices; ++i) {
    char name[256];
    int computeCaps[2];
    RTsize total_mem;
    int clock_rate;
    int threads_per_block;
    int sm_count;
    int execution_timeout_enabled;
    int texture_count;
    int tcc_driver;
    int cuda_device_ordinal;

    RT_CHECK_ERROR_NO_CONTEXT(rtDeviceGetAttribute(i, RT_DEVICE_ATTRIBUTE_NAME, sizeof(name), name));
    printf("Device %d: %s\n", i, name);

    RT_CHECK_ERROR_NO_CONTEXT(rtDeviceGetAttribute(i, RT_DEVICE_ATTRIBUTE_COMPUTE_CAPABILITY, sizeof(computeCaps), &computeCaps));
    printf("  Compute Support: %d %d\n", computeCaps[0], computeCaps[1]);

    RT_CHECK_ERROR_NO_CONTEXT(rtDeviceGetAttribute(i, RT_DEVICE_ATTRIBUTE_TOTAL_MEMORY, sizeof(total_mem), &total_mem));
    printf("  Total Memory: %llu bytes\n", (unsigned long long)total_mem);

    RT_CHECK_ERROR_NO_CONTEXT(rtDeviceGetAttribute(i, RT_DEVICE_ATTRIBUTE_CLOCK_RATE, sizeof(clock_rate), &clock_rate));
    printf("  Clock Rate: %u kilohertz\n", clock_rate);

    RT_CHECK_ERROR_NO_CONTEXT(rtDeviceGetAttribute(i, RT_DEVICE_ATTRIBUTE_MAX_THREADS_PER_BLOCK, sizeof(threads_per_block), &threads_per_block));
    printf("  Max. Threads per Block: %u\n", threads_per_block);

    RT_CHECK_ERROR_NO_CONTEXT(rtDeviceGetAttribute(i, RT_DEVICE_ATTRIBUTE_MULTIPROCESSOR_COUNT, sizeof(sm_count), &sm_count));
    printf("  SM Count: %u\n", sm_count);

    RT_CHECK_ERROR_NO_CONTEXT(rtDeviceGetAttribute(i, RT_DEVICE_ATTRIBUTE_EXECUTION_TIMEOUT_ENABLED, sizeof(execution_timeout_enabled), &execution_timeout_enabled));
    printf("  Execution Timeout Enabled: %d\n", execution_timeout_enabled);

    RT_CHECK_ERROR_NO_CONTEXT(rtDeviceGetAttribute(i, RT_DEVICE_ATTRIBUTE_MAX_HARDWARE_TEXTURE_COUNT, sizeof(texture_count), &texture_count));
    printf("  Max. HW Texture Count: %u\n", texture_count);
 
    RT_CHECK_ERROR_NO_CONTEXT(rtDeviceGetAttribute(i, RT_DEVICE_ATTRIBUTE_TCC_DRIVER, sizeof(tcc_driver), &tcc_driver));
    printf("  TCC driver enabled: %u\n", tcc_driver);
 
    RT_CHECK_ERROR_NO_CONTEXT(rtDeviceGetAttribute(i, RT_DEVICE_ATTRIBUTE_CUDA_DEVICE_ORDINAL, sizeof(cuda_device_ordinal), &cuda_device_ordinal));
    printf("  CUDA Device Ordinal: %d\n", cuda_device_ordinal);
 
    printf("\n");
  }

  printf("Constructing a context...\n");
  RT_CHECK_ERROR(rtContextCreate(&context));
  
  RT_CHECK_ERROR(rtContextGetDeviceCount(context, &context_device_count));
  printf("  Created with %u device(s)\n", context_device_count);

  RT_CHECK_ERROR(rtContextGetAttribute(context, RT_CONTEXT_ATTRIBUTE_MAX_TEXTURE_COUNT, sizeof(max_textures), &max_textures));
  printf("  Supports %u simultaneous textures\n", max_textures);

  context_devices = (int*)malloc(sizeof(int)*context_device_count);
  RT_CHECK_ERROR(rtContextGetDevices(context, context_devices));

  printf("  Free memory:\n");
  for(i = 0; i < context_device_count; ++i) {
    int ordinal = context_devices[i];
    RTsize bytes;
    RT_CHECK_ERROR(rtContextGetAttribute(context, RT_CONTEXT_ATTRIBUTE_AVAILABLE_DEVICE_MEMORY+ordinal, sizeof(bytes), &bytes));
    printf("    Device %d: %llu bytes\n", ordinal, (unsigned long long)bytes);
  }
  free(context_devices);

  printf("\n");

  return 0;
}
    
