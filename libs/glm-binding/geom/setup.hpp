/*
** Geometric setup
*/
#ifndef __EXT_GEOM_SETUP_HPP__
#define __EXT_GEOM_SETUP_HPP__

#include <vector>

#include <glm/glm.hpp>
#include <glm/common.hpp>
#include <glm/gtx/compatibility.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/vector_query.hpp>
#include <glm/ext/scalar_relational.hpp>
#include <glm/ext/vector_relational.hpp>
#if GLM_CONFIG_ALIGNED_GENTYPES == GLM_ENABLE
  #include <glm/simd/platform.h>
#endif

#include "ext/vector_extensions.hpp"
#include "ext/quat_extensions.hpp"
#include "ext/matrix_extensions.hpp"

#define GLM_GEOM_QUALIFIER static GLM_INLINE

/*
** For MSVC, GLM_NEVER_INLINE cannot be applied as most binding functions
** have no declarations and __declspec(noinline) cannot be used.
*/
#define GLM_GEOM_QUALIFIER_NOINLINE static

/* Check runtime preconditions on geom structures (often related to ensuring normalized vectors) */
#if defined(LUA_GLM_SAFE)
  #define GLM_GEOM_ASSUME(x, onError) \
    do {                              \
      if (!(x))                       \
        return (onError);             \
    } while (0)
#else
  #define GLM_GEOM_ASSUME(x, onError)
#endif

#if GLM_CONFIG_ALIGNED_GENTYPES == GLM_ENABLE && (GLM_ARCH & GLM_ARCH_SSE41_BIT)
  /*
  ** True if the x,y,z components of the component vector are all zero. Note "v"
  ** should be the result to some binary operation, e.g., _mm_xor_ps, _mm_or_ps,
  ** _mm_and_ps, etc.
  */
  #define _mm_vec3_allzero(v) _mm_testz_si128(_mm_castps_si128(v), _mm_set_epi32(0, 0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU))
#endif

/* Forward declare all structures. */
namespace glm {
  template<length_t L, typename T, qualifier Q = defaultp> struct AABB;
  template<length_t L, typename T, qualifier Q = defaultp> struct Line;
  template<length_t L, typename T, qualifier Q = defaultp> struct Ray;
  template<length_t L, typename T, qualifier Q = defaultp> struct LineSegment;
  template<length_t L, typename T, qualifier Q = defaultp> struct Triangle;
  template<length_t L, typename T, qualifier Q = defaultp> struct Sphere;
  template<length_t L, typename T, qualifier Q = defaultp> struct Plane;
  template<length_t L, typename T, qualifier Q = defaultp> struct Polygon;
};

/******************************************************************************
* GLM Binding:
* See Copyright Notice in lua.h
\******************************************************************************
* MathGeoLib
* Copyright Jukka Jylänki
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
******************************************************************************/

#endif
