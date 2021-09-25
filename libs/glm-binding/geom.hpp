/*
** Geometric Structures
*/
#ifndef __BINDING_GEOM_HPP__
#define __BINDING_GEOM_HPP__
#if defined(LUA_GLM_GEOM_EXTENSIONS)

#include "lapi.h"

#include "lglm.hpp"
#include "lglm_core.h"

#include "allocator.hpp"
#include "iterators.hpp"
#include "bindings.hpp"

#include "geom/setup.hpp"
#include "geom/aabb.hpp"
#include "geom/line.hpp"
#include "geom/linesegment.hpp"
#include "geom/ray.hpp"
#include "geom/sphere.hpp"
#include "geom/plane.hpp"
#include "geom/polygon.hpp"

/* All geometric objects adhere to the glm::equal/glm::notEqual API. */
#define GEOM_EQUALS(LB, F, Tr, ...) \
  _EQUAL(LB, F, Tr, Tr::Point)

/*
** Generic distance definition: returning the distance between a geometric
** object and point-of-interest along with the parametric distances of intersection
*/
#define GEOM_DISTANCE(LB, F, A, B) \
  LUA_MLM_BEGIN                    \
  const A::type a = A::Next(LB);   \
  const B::type b = B::Next(LB);   \
  A::value_type t(0);              \
  TRAITS_PUSH(LB, F(a, b, t), t);  \
  LUA_MLM_END

/*
** Generic intersects definition where the line/ray/segment is the first
** parameter being tested against the structure passed as the second parameter.
** Returning the point of intersection and relative location along each object.
*/
#define GEOM_INTERSECTS(LB, F, A, B)    \
  LUA_MLM_BEGIN                         \
  const A::type a = A::Next(LB);        \
  const B::type b = B::Next(LB);        \
  A::Near::type n = A::Near::Next(LB);  \
  A::Far::type f = A::Far::Next(LB);    \
  TRAITS_PUSH(LB, F(a, b, n, f), n, f); \
  LUA_MLM_END

/*
** The line/ray/segment is the second parameter being tested against the
** structure passed as the first parameter.
*/
#define GEOM_INTERSECTS_RH(LB, F, A, B) \
  LUA_MLM_BEGIN                         \
  const A::type a = A::Next(LB);        \
  const B::type b = B::Next(LB);        \
  B::Near::type n = B::Near::Next(LB);  \
  B::Far::type f = B::Far::Next(LB);    \
  TRAITS_PUSH(LB, F(a, b, n, f), n, f); \
  LUA_MLM_END

/*
** Generic project-to-axis definition; returning the parametric min & max of the
** axis projection.
*/
#define GEOM_PROJECTION(LB, F, A, B)  \
  LUA_MLM_BEGIN                       \
  const A::type a = A::Next(LB);      \
  const B::type b = B::Next(LB);      \
  A::value_type outMin(0), outMax(0); \
  F(a, b, outMin, outMax);            \
  TRAITS_PUSH(LB, outMin, outMax);    \
  LUA_MLM_END

/// <summary>
/// Relative position along a line, segment, ray for casting.
/// </summary>
template<bool isNear, bool isRelative, typename T = glm_Float>
struct gLuaRelative : gLuaTrait<T> {
  static GLM_CONSTEXPR const char *Label() { return "RelativePosition"; }
  LUA_TRAIT_QUALIFIER bool Is(const gLuaBase &LB, int idx) { return lua_isnoneornil(LB.L, idx) || gLuaTrait<T>::Is(LB, idx); }
  LUA_TRAIT_QUALIFIER T Next(gLuaBase &LB) {
    if (lua_isnoneornil(LB.L, LB.idx)) {
      LB.idx++;  // Skip the argument
      GLM_IF_CONSTEXPR(isNear)
        return isRelative ? T(0) : -std::numeric_limits<T>::infinity();
      return isRelative ? T(1) : std::numeric_limits<T>::infinity();
    }

    return gLuaTrait<T>::Next(LB);
  }
};

template<glm::length_t L = 3, typename T = glm_Float>
struct gLuaAABB : gLuaSharedTrait<T, glm::AABB<L, T>> {
  using Point = gLuaTrait<typename glm::AABB<L, T>::Point>;

  static GLM_CONSTEXPR const char *Label() { return "AABB"; }
  LUA_TRAIT_QUALIFIER GLM_CONSTEXPR glm::AABB<L, T> zero() { return glm::AABB<L, T>(T(0)); }
  LUA_TRAIT_QUALIFIER bool Is(gLuaBase &LB, int idx) {
    return Point::Is(LB, idx) && Point::Is(LB, idx + 1);
  }
};

template<glm::length_t L = 3, typename T = glm_Float>
struct gLuaLine : gLuaSharedTrait<T, glm::Line<L, T>> {
  using Point = gLuaTrait<typename glm::Line<L, T>::Point>;
  using Near = gLuaRelative<true, false, T>;
  using Far = gLuaRelative<false, false, T>;

  static GLM_CONSTEXPR const char *Label() { return "Line"; }
  LUA_TRAIT_QUALIFIER GLM_CONSTEXPR glm::Line<L, T> zero() { return glm::Line<L, T>(T(0)); }
  LUA_TRAIT_QUALIFIER bool Is(gLuaBase &LB, int idx) {
    return Point::Is(LB, idx) && Point::Is(LB, idx + 1);
  }
};

template<glm::length_t L = 3, typename T = glm_Float>
struct gLuaSegment : gLuaSharedTrait<T, glm::LineSegment<L, T>> {
  using Point = gLuaTrait<typename glm::LineSegment<L, T>::Point>;
  using Near = gLuaRelative<true, true, T>;
  using Far = gLuaRelative<false, true, T>;

  static GLM_CONSTEXPR const char *Label() { return "Segment"; }
  LUA_TRAIT_QUALIFIER GLM_CONSTEXPR glm::LineSegment<L, T> zero() { return glm::LineSegment<L, T>(T(0)); }
  LUA_TRAIT_QUALIFIER bool Is(gLuaBase &LB, int idx) {
    return Point::Is(LB, idx) && Point::Is(LB, idx + 1);
  }
};

template<glm::length_t L = 3, typename T = glm_Float>
struct gLuaRay : gLuaSharedTrait<T, glm::Ray<L, T>> {
  using Point = gLuaTrait<typename glm::Ray<L, T>::Point>;
  using Near = gLuaRelative<true, true, T>;
  using Far = gLuaRelative<false, false, T>;

  static GLM_CONSTEXPR const char *Label() { return "Ray"; }
  LUA_TRAIT_QUALIFIER GLM_CONSTEXPR glm::Ray<L, T> zero() { return glm::Ray<L, T>(T(0)); }
  LUA_TRAIT_QUALIFIER bool Is(gLuaBase &LB, int idx) {
    return Point::Is(LB, idx) && Point::Is(LB, idx + 1);
  }
};

template<glm::length_t L = 3, typename T = glm_Float>
struct gLuaSphere : gLuaSharedTrait<T, glm::Sphere<L, T>> {
  using Point = gLuaTrait<typename glm::Sphere<L, T>::Point>;

  static GLM_CONSTEXPR const char *Label() { return "Sphere"; }
  LUA_TRAIT_QUALIFIER GLM_CONSTEXPR glm::Sphere<L, T> zero() { return glm::Sphere<L, T>(T(0)); }
  LUA_TRAIT_QUALIFIER bool Is(gLuaBase &LB, int idx) {
    return Point::Is(LB, idx) && gLuaTrait<T>::Is(LB, idx + 1);
  }
};

template<glm::length_t L = 3, typename T = glm_Float>
struct gLuaPlane : gLuaSharedTrait<T, glm::Plane<L, T>> {
  using Point = gLuaTrait<typename glm::Plane<L, T>::Point>;

  static GLM_CONSTEXPR const char *Label() { return "Plane"; }
  LUA_TRAIT_QUALIFIER GLM_CONSTEXPR glm::Plane<L, T> zero() { return glm::Plane<L, T>(T(0)); }
  LUA_TRAIT_QUALIFIER bool Is(gLuaBase &LB, int idx) {
    return Point::Is(LB, idx) && gLuaTrait<T>::Is(LB, idx + 1);
  }
};

/// <summary>
/// An (explicitly three dimensional) polygon trait.
///
/// @TODO More creative casting rules for generalized polygons, e.g., the
///   userdata also storing the dimensionality to each point.
/// </summary>
template<typename T = glm_Float>
struct gLuaPolygon : gLuaSharedTrait<T, glm::Polygon<3, T>> {
  using Point = gLuaTrait<typename glm::Polygon<3, T>::Point>;

  static GLM_CONSTEXPR const char *Label() { return "Polygon"; }
  LUA_TRAIT_QUALIFIER GLM_CONSTEXPR glm::Polygon<3, T> zero() { return glm::Polygon<3, T>(GLM_NULLPTR); }
  LUA_TRAIT_QUALIFIER bool Is(gLuaBase &LB, int idx) {
    return luaL_testudata(LB.L, idx, LUA_GLM_POLYGON_META) != GLM_NULLPTR;
  }
};

/*
** {==================================================================
** AABB
** ===================================================================
*/

/// <summary>
/// Create a new AABB that encloses all coordinates on the Lua stack (or within
/// a table if it is the first argument)
/// </summary>
GLM_BINDING_QUALIFIER(aabb_new) {
  GLM_BINDING_BEGIN
  if (lua_istable(LB.L, LB.idx)) {
    using Iterator = glmLuaArray::Iterator<gLuaVec3<>>;
    return gLuaBase::Push(LB, glm::minimalEnclosingAABB<Iterator, 3, gLuaVec3<>::value_type>(
                              glmLuaArray::begin<gLuaVec3<>>(LB.L, LB.idx),
                              glmLuaArray::end<gLuaVec3<>>(LB.L)));
  }
  else {
    using Iterator = glmLuaStack::Iterator<gLuaVec3<>>;
    return gLuaBase::Push(LB, glm::minimalEnclosingAABB<Iterator, 3, gLuaVec3<>::value_type>(
                              glmLuaStack::begin<gLuaVec3<>>(LB.L, LB.idx),
                              glmLuaStack::end<gLuaVec3<>>(LB.L)));
  }
  GLM_BINDING_END
}

/* Create an AABB from a coordinate & radius. */
TRAITS_LAYOUT_DEFN(aabb_fromCenterAndSize, glm::aabbFromCenterAndSize, LAYOUT_BINARY_OPTIONAL, gLuaVec3<>)
TRAITS_DEFN(aabb_fromSphere, glm::aabbFromSphere, gLuaSphere<>)
TRAITS_DEFN(aabb_operator_negate, operator-, gLuaAABB<>)
TRAITS_DEFN(aabb_operator_equals, operator==, gLuaAABB<>, gLuaAABB<>)
TRAITS_DEFN(aabb_operator_add, operator+, gLuaAABB<>, gLuaVec3<>)
TRAITS_DEFN(aabb_operator_sub, operator-, gLuaAABB<>, gLuaVec3<>)
ROTATION_MATRIX_DEFN(aabb_operator_mul, operator*, LAYOUT_UNARY, gLuaAABB<>)
TRAITS_LAYOUT_DEFN(aabb_equal, glm::equal, GEOM_EQUALS, gLuaAABB<>)
TRAITS_LAYOUT_DEFN(aabb_notEqual, glm::notEqual, GEOM_EQUALS, gLuaAABB<>)
TRAITS_DEFN(aabb_isinf, glm::isinf, gLuaAABB<>)
TRAITS_DEFN(aabb_isnan, glm::isnan, gLuaAABB<>)
TRAITS_DEFN(aabb_isfinite, glm::isfinite, gLuaAABB<>)
TRAITS_DEFN(aabb_isDegenerate, glm::isDegenerate, gLuaAABB<>)
TRAITS_DEFN(aabb_centerPoint, glm::centerPoint, gLuaAABB<>)
TRAITS_DEFN(aabb_pointInside, glm::pointInside, gLuaAABB<>, gLuaVec3<>)
TRAITS_DEFN(aabb_minimalEnclosingSphere, glm::minimalEnclosingSphere, gLuaAABB<>)
TRAITS_DEFN(aabb_maximalContainedSphere, glm::maximalContainedSphere, gLuaAABB<>)
TRAITS_DEFN(aabb_edge, glm::edge, gLuaAABB<>, gLuaTrait<int>)
TRAITS_DEFN(aabb_cornerPoint, glm::cornerPoint, gLuaAABB<>, gLuaTrait<int>)
TRAITS_DEFN(aabb_extremePoint, glm::extremePoint, gLuaAABB<>, gLuaVec3<>)
TRAITS_DEFN(aabb_pointOnEdge, glm::pointOnEdge, gLuaAABB<>, gLuaTrait<int>, gLuaFloat)
TRAITS_DEFN(aabb_faceCenterPoint, glm::faceCenterPoint, gLuaAABB<>, gLuaTrait<int>)
TRAITS_DEFN(aabb_facePoint, glm::facePoint, gLuaAABB<>, gLuaTrait<int>, gLuaFloat, gLuaFloat)
TRAITS_DEFN(aabb_faceNormal, glm::faceNormalAABB<gLuaFloat::value_type>, gLuaTrait<int>)
TRAITS_DEFN(aabb_facePlane, glm::facePlane, gLuaAABB<>, gLuaTrait<int>)
TRAITS_DEFN(aabb_size, glm::size, gLuaAABB<>)
TRAITS_DEFN(aabb_halfSize, glm::halfSize, gLuaAABB<>)
TRAITS_DEFN(aabb_volume, glm::volume, gLuaAABB<>)
TRAITS_DEFN(aabb_surfaceArea, glm::surfaceArea, gLuaAABB<>)
TRAITS_DEFN(aabb_scale, glm::scale, gLuaAABB<>, gLuaVec3<>, gLuaFloat)
TRAITS_DEFN(aabb_closestPoint, glm::closestPoint, gLuaAABB<>, gLuaVec3<>)
TRAITS_DEFN(aabb_distance, glm::distance, gLuaAABB<>, gLuaVec3<>)
TRAITS_DEFN(aabb_distanceSphere, glm::distance, gLuaAABB<>, gLuaSphere<>)
TRAITS_DEFN(aabb_contains, glm::contains, gLuaAABB<>, gLuaVec3<>)
TRAITS_DEFN(aabb_containsAABB, glm::contains, gLuaAABB<>, gLuaAABB<>)
TRAITS_DEFN(aabb_containsSegment, glm::contains, gLuaAABB<>, gLuaSegment<>)
TRAITS_DEFN(aabb_containsSphere, glm::contains, gLuaAABB<>, gLuaSphere<>)
TRAITS_DEFN(aabb_containsPolygon, glm::contains, gLuaAABB<>, gLuaPolygon<>)
TRAITS_DEFN(aabb_grow, glm::grow, gLuaAABB<>, gLuaFloat)
TRAITS_DEFN(aabb_enclose, glm::enclose, gLuaAABB<>, gLuaVec3<>)
TRAITS_DEFN(aabb_encloseSegment, glm::enclose, gLuaAABB<>, gLuaSegment<>)
TRAITS_DEFN(aabb_encloseSphere, glm::enclose, gLuaAABB<>, gLuaSphere<>)
TRAITS_DEFN(aabb_encloseAABB, glm::enclose, gLuaAABB<>, gLuaAABB<>)
TRAITS_DEFN(aabb_enclosePolygon, glm::enclose, gLuaAABB<>, gLuaPolygon<>)
TRAITS_DEFN(aabb_intersectAABB, glm::intersects, gLuaAABB<>, gLuaAABB<>)
TRAITS_DEFN(aabb_intersectSphere, glm::intersects, gLuaAABB<>, gLuaSphere<>)
TRAITS_DEFN(aabb_intersectPlane, glm::intersects, gLuaAABB<>, gLuaPlane<>)
TRAITS_LAYOUT_DEFN(aabb_intersectLine, glm::intersects, GEOM_INTERSECTS_RH, gLuaAABB<>, gLuaLine<>)
TRAITS_LAYOUT_DEFN(aabb_intersectSegment, glm::intersects, GEOM_INTERSECTS_RH, gLuaAABB<>, gLuaSegment<>)
TRAITS_LAYOUT_DEFN(aabb_intersectRay, glm::intersects, GEOM_INTERSECTS_RH, gLuaAABB<>, gLuaRay<>)
TRAITS_DEFN(aabb_intersection, glm::intersection, gLuaAABB<>, gLuaAABB<>)
TRAITS_DEFN(aabb_slabs, glm::slabs, gLuaAABB<>, gLuaRay<>)
TRAITS_LAYOUT_DEFN(aabb_projectToAxis, glm::projectToAxis, GEOM_PROJECTION, gLuaAABB<>, gLuaVec3<>)

static const luaL_Reg luaglm_aabblib[] = {
  { "new", glm_aabb_new },
  { "fromCenterAndSize", glm_aabb_fromCenterAndSize },
  { "aabbFromSphere", glm_aabb_fromSphere },
  { "operator_negate", glm_aabb_operator_negate },
  { "operator_equals", glm_aabb_operator_equals },
  { "operator_add", glm_aabb_operator_add },
  { "operator_sub", glm_aabb_operator_sub },
  { "operator_mul", glm_aabb_operator_mul },
  { "equal", glm_aabb_equal },
  { "notEqual", glm_aabb_notEqual },
  { "isinf", glm_aabb_isinf },
  { "isnan", glm_aabb_isnan },
  { "isfinite", glm_aabb_isfinite },
  { "isDegenerate", glm_aabb_isDegenerate },
  { "centerPoint", glm_aabb_centerPoint },
  { "centroid", glm_aabb_centerPoint },
  { "pointInside", glm_aabb_pointInside },
  { "minimalEnclosingSphere", glm_aabb_minimalEnclosingSphere },
  { "maximalContainedSphere", glm_aabb_maximalContainedSphere },
  { "edge", glm_aabb_edge },
  { "cornerPoint", glm_aabb_cornerPoint },
  { "extremePoint", glm_aabb_extremePoint },
  { "pointOnEdge", glm_aabb_pointOnEdge },
  { "faceCenterPoint", glm_aabb_faceCenterPoint },
  { "facePoint", glm_aabb_facePoint },
  { "faceNormal", glm_aabb_faceNormal },
  { "facePlane", glm_aabb_facePlane },
  { "size", glm_aabb_size },
  { "halfSize", glm_aabb_halfSize },
  { "diagonal", glm_aabb_size },
  { "halfDiagonal", glm_aabb_halfSize },
  { "volume", glm_aabb_volume },
  { "surfaceArea", glm_aabb_surfaceArea },
  { "scale", glm_aabb_scale },
  { "closestPoint", glm_aabb_closestPoint },
  { "distance", glm_aabb_distance },
  { "distanceSphere", glm_aabb_distanceSphere },
  { "contains", glm_aabb_contains },
  { "containsAABB", glm_aabb_containsAABB },
  { "containsSegment", glm_aabb_containsSegment },
  { "containsSphere", glm_aabb_containsSphere },
  { "containsPolygon", glm_aabb_containsPolygon },
  { "grow", glm_aabb_grow },
  { "enclose", glm_aabb_enclose },
  { "encloseSegment", glm_aabb_encloseSegment },
  { "encloseSphere", glm_aabb_encloseSphere },
  { "encloseAABB", glm_aabb_encloseAABB },
  { "enclosePolygon", glm_aabb_enclosePolygon },
  { "intersectAABB", glm_aabb_intersectAABB },
  { "intersectSphere", glm_aabb_intersectSphere },
  { "intersectPlane", glm_aabb_intersectPlane },
  { "intersectLine", glm_aabb_intersectLine },
  { "intersectSegment", glm_aabb_intersectSegment },
  { "intersectRay", glm_aabb_intersectRay },
  { "intersection", glm_aabb_intersection },
  { "slabs", glm_aabb_slabs },
  { "projectToAxis", glm_aabb_projectToAxis },
  { GLM_NULLPTR, GLM_NULLPTR }
};

/* }================================================================== */

/*
** {==================================================================
** AABB2D
** ===================================================================
*/

GLM_BINDING_QUALIFIER(aabb2d_new) {
  GLM_BINDING_BEGIN
  if (lua_istable(LB.L, LB.idx)) {
    using Iterator = glmLuaArray::Iterator<gLuaVec2<>>;
    return gLuaBase::Push(LB, glm::minimalEnclosingAABB<Iterator, 2, gLuaVec2<>::value_type>(
                              glmLuaArray::begin<gLuaVec2<>>(LB.L, LB.idx),
                              glmLuaArray::end<gLuaVec2<>>(LB.L)));
  }
  else {
    using Iterator = glmLuaStack::Iterator<gLuaVec2<>>;
    return gLuaBase::Push(LB, glm::minimalEnclosingAABB<Iterator, 2, gLuaVec2<>::value_type>(
                              glmLuaStack::begin<gLuaVec2<>>(LB.L, LB.idx),
                              glmLuaStack::end<gLuaVec2<>>(LB.L)));
  }
  GLM_BINDING_END
}

/* Create an AABB from a coordinate & radius. */
TRAITS_LAYOUT_DEFN(aabb2d_fromCenterAndSize, glm::aabbFromCenterAndSize, LAYOUT_BINARY_OPTIONAL, gLuaVec2<>)
TRAITS_DEFN(aabb2d_fromSphere, glm::aabbFromSphere, gLuaSphere<2>)
TRAITS_DEFN(aabb2d_operator_negate, operator-, gLuaAABB<2>)
TRAITS_DEFN(aabb2d_operator_equals, operator==, gLuaAABB<2>, gLuaAABB<2>)
TRAITS_DEFN(aabb2d_operator_add, operator+, gLuaAABB<2>, gLuaVec2<>)
TRAITS_DEFN(aabb2d_operator_sub, operator-, gLuaAABB<2>, gLuaVec2<>)
ROTATION_MATRIX_DEFN(aabb2d_operator_mul, operator*, LAYOUT_UNARY, gLuaAABB<2>)
TRAITS_LAYOUT_DEFN(aabb2d_equal, glm::equal, GEOM_EQUALS, gLuaAABB<2>)
TRAITS_LAYOUT_DEFN(aabb2d_notEqual, glm::notEqual, GEOM_EQUALS, gLuaAABB<2>)
TRAITS_DEFN(aabb2d_isinf, glm::isinf, gLuaAABB<2>)
TRAITS_DEFN(aabb2d_isnan, glm::isnan, gLuaAABB<2>)
TRAITS_DEFN(aabb2d_isfinite, glm::isfinite, gLuaAABB<2>)
TRAITS_DEFN(aabb2d_isDegenerate, glm::isDegenerate, gLuaAABB<2>)
TRAITS_DEFN(aabb2d_centerPoint, glm::centerPoint, gLuaAABB<2>)
TRAITS_DEFN(aabb2d_pointInside, glm::pointInside, gLuaAABB<2>, gLuaVec2<>)
TRAITS_DEFN(aabb2d_edge, glm::edge, gLuaAABB<2>, gLuaTrait<int>)
TRAITS_DEFN(aabb2d_cornerPoint, glm::cornerPoint, gLuaAABB<2>, gLuaTrait<int>)
TRAITS_DEFN(aabb2d_extremePoint, glm::extremePoint, gLuaAABB<2>, gLuaVec2<>)
TRAITS_DEFN(aabb2d_size, glm::size, gLuaAABB<2>)
TRAITS_DEFN(aabb2d_halfSize, glm::halfSize, gLuaAABB<2>)
TRAITS_DEFN(aabb2d_volume, glm::volume, gLuaAABB<2>)
TRAITS_DEFN(aabb2d_scale, glm::scale, gLuaAABB<2>, gLuaVec2<>, gLuaFloat)
TRAITS_DEFN(aabb2d_closestPoint, glm::closestPoint, gLuaAABB<2>, gLuaVec2<>)
TRAITS_DEFN(aabb2d_distance, glm::distance, gLuaAABB<2>, gLuaVec2<>)
TRAITS_DEFN(aabb2d_distanceSphere, glm::distance, gLuaAABB<2>, gLuaSphere<2>)
TRAITS_DEFN(aabb2d_contains, glm::contains, gLuaAABB<2>, gLuaVec2<>)
TRAITS_DEFN(aabb2d_containsAABB, glm::contains, gLuaAABB<2>, gLuaAABB<2>)
TRAITS_DEFN(aabb2d_containsSegment, glm::contains, gLuaAABB<2>, gLuaSegment<2>)
TRAITS_DEFN(aabb2d_containsSphere, glm::contains, gLuaAABB<2>, gLuaSphere<2>)
TRAITS_DEFN(aabb2d_grow, glm::grow, gLuaAABB<2>, gLuaFloat)
TRAITS_DEFN(aabb2d_enclose, glm::enclose, gLuaAABB<2>, gLuaVec2<>)
TRAITS_DEFN(aabb2d_encloseSegment, glm::enclose, gLuaAABB<2>, gLuaSegment<2>)
TRAITS_DEFN(aabb2d_encloseSphere, glm::enclose, gLuaAABB<2>, gLuaSphere<2>)
TRAITS_DEFN(aabb2d_encloseAABB, glm::enclose, gLuaAABB<2>, gLuaAABB<2>)
TRAITS_DEFN(aabb2d_intersectAABB, glm::intersects, gLuaAABB<2>, gLuaAABB<2>)
TRAITS_DEFN(aabb2d_intersection, glm::intersection, gLuaAABB<2>, gLuaAABB<2>)
TRAITS_LAYOUT_DEFN(aabb2d_intersectLine, glm::intersects, GEOM_INTERSECTS_RH, gLuaAABB<2>, gLuaLine<2>)
TRAITS_LAYOUT_DEFN(aabb2d_intersectSegment, glm::intersects, GEOM_INTERSECTS_RH, gLuaAABB<2>, gLuaSegment<2>)
TRAITS_LAYOUT_DEFN(aabb2d_intersectRay, glm::intersects, GEOM_INTERSECTS_RH, gLuaAABB<2>, gLuaRay<2>)
TRAITS_LAYOUT_DEFN(aabb2d_projectToAxis, glm::projectToAxis, GEOM_PROJECTION, gLuaAABB<2>, gLuaVec2<>)

static const luaL_Reg luaglm_aabb2dlib[] = {
  { "new", glm_aabb2d_new },
  { "fromCenterAndSize", glm_aabb2d_fromCenterAndSize },
  { "aabbFromSphere", glm_aabb2d_fromSphere },
  { "operator_negate", glm_aabb2d_operator_negate },
  { "operator_equals", glm_aabb2d_operator_equals },
  { "operator_add", glm_aabb2d_operator_add },
  { "operator_sub", glm_aabb2d_operator_sub },
  { "operator_mul", glm_aabb2d_operator_mul },
  { "equal", glm_aabb2d_equal },
  { "notEqual", glm_aabb2d_notEqual },
  { "isinf", glm_aabb2d_isinf },
  { "isnan", glm_aabb2d_isnan },
  { "isfinite", glm_aabb2d_isfinite },
  { "isDegenerate", glm_aabb2d_isDegenerate },
  { "centerPoint", glm_aabb2d_centerPoint },
  { "centroid", glm_aabb2d_centerPoint },
  { "pointInside", glm_aabb2d_pointInside },
  { "edge", glm_aabb2d_edge },
  { "cornerPoint", glm_aabb2d_cornerPoint },
  { "extremePoint", glm_aabb2d_extremePoint },
  { "size", glm_aabb2d_size },
  { "halfSize", glm_aabb2d_halfSize },
  { "diagonal", glm_aabb2d_size },
  { "halfDiagonal", glm_aabb2d_halfSize },
  { "volume", glm_aabb2d_volume },
  { "scale", glm_aabb2d_scale },
  { "closestPoint", glm_aabb2d_closestPoint },
  { "distance", glm_aabb2d_distance },
  { "distanceSphere", glm_aabb2d_distanceSphere },
  { "contains", glm_aabb2d_contains },
  { "containsAABB", glm_aabb2d_containsAABB },
  { "containsSegment", glm_aabb2d_containsSegment },
  { "containsSphere", glm_aabb2d_containsSphere },
  { "grow", glm_aabb2d_grow },
  { "enclose", glm_aabb2d_enclose },
  { "encloseSegment", glm_aabb2d_encloseSegment },
  { "encloseSphere", glm_aabb2d_encloseSphere },
  { "encloseAABB", glm_aabb2d_encloseAABB },
  { "intersectAABB", glm_aabb2d_intersectAABB },
  { "intersectLine", glm_aabb2d_intersectLine },
  { "intersectSegment", glm_aabb2d_intersectSegment },
  { "intersectRay", glm_aabb2d_intersectRay },
  { "intersection", glm_aabb2d_intersection },
  { "projectToAxis", glm_aabb2d_projectToAxis },
  { GLM_NULLPTR, GLM_NULLPTR }
};

/* }================================================================== */

/*
** {==================================================================
** Line
** ===================================================================
*/

TRAITS_DEFN(line_operator_negate, operator-, gLuaLine<>)
TRAITS_DEFN(line_operator_equals, operator==, gLuaLine<>, gLuaLine<>)
TRAITS_DEFN(line_operator_add, operator+, gLuaLine<>, gLuaVec3<>)
TRAITS_DEFN(line_operator_sub, operator-, gLuaLine<>, gLuaVec3<>)
ROTATION_MATRIX_DEFN(line_operator_mul, operator*, LAYOUT_UNARY, gLuaLine<>)
TRAITS_LAYOUT_DEFN(line_equal, glm::equal, GEOM_EQUALS, gLuaLine<>)
TRAITS_LAYOUT_DEFN(line_notEqual, glm::notEqual, GEOM_EQUALS, gLuaLine<>)
TRAITS_DEFN(line_to_segment, glm::toLineSegment, gLuaLine<>, gLuaFloat)
TRAITS_DEFN(line_isinf, glm::isinf, gLuaLine<>)
TRAITS_DEFN(line_isnan, glm::isnan, gLuaLine<>)
TRAITS_DEFN(line_isfinite, glm::isfinite, gLuaLine<>)
TRAITS_DEFN(line_getpoint, glm::getPoint, gLuaLine<>, gLuaFloat)
TRAITS_LAYOUT_DEFN(line_closest, glm::closestPoint, GEOM_DISTANCE, gLuaLine<>, gLuaVec3<>)
TRAITS_LAYOUT_DEFN(line_closestRay, glm::closestPoint, GEOM_INTERSECTS, gLuaLine<>, gLuaRay<>)
TRAITS_LAYOUT_DEFN(line_closestLine, glm::closestPoint, GEOM_INTERSECTS, gLuaLine<>, gLuaLine<>)
TRAITS_LAYOUT_DEFN(line_closestSegment, glm::closestPoint, GEOM_INTERSECTS, gLuaLine<>, gLuaSegment<>)
TRAITS_DEFN(line_contains, glm::contains, gLuaLine<>, gLuaVec3<>, gLuaEps<>)
TRAITS_DEFN(line_containsRay, glm::contains, gLuaLine<>, gLuaRay<>, gLuaEps<>)
TRAITS_DEFN(line_containsSegment, glm::contains, gLuaLine<>, gLuaSegment<>, gLuaEps<>)
TRAITS_LAYOUT_DEFN(line_distance, glm::distance, GEOM_DISTANCE, gLuaLine<>, gLuaVec3<>)
TRAITS_LAYOUT_DEFN(line_distanceRay, glm::distance, GEOM_INTERSECTS, gLuaLine<>, gLuaRay<>)
TRAITS_LAYOUT_DEFN(line_distanceLine, glm::distance, GEOM_INTERSECTS, gLuaLine<>, gLuaLine<>)
TRAITS_LAYOUT_DEFN(line_distanceSegment, glm::distance, GEOM_INTERSECTS, gLuaLine<>, gLuaSegment<>)
TRAITS_DEFN(line_distanceSphere, glm::distance, gLuaLine<>, gLuaSphere<>)
TRAITS_LAYOUT_DEFN(line_intersectAABB, glm::intersects, GEOM_INTERSECTS, gLuaLine<>, gLuaAABB<>)
TRAITS_LAYOUT_DEFN(line_intersectSphere, glm::intersects, GEOM_INTERSECTS, gLuaLine<>, gLuaSphere<>)
TRAITS_LAYOUT_DEFN(line_intersectPlane, glm::intersects, GEOM_DISTANCE, gLuaLine<>, gLuaPlane<>)
TRAITS_LAYOUT_DEFN(line_projectToAxis, glm::projectToAxis, GEOM_PROJECTION, gLuaLine<>, gLuaVec3<>)

static const luaL_Reg luaglm_linelib[] = {
  { "operator_negate", glm_line_operator_negate },
  { "operator_equals", glm_line_operator_equals },
  { "operator_add", glm_line_operator_add },
  { "operator_sub", glm_line_operator_sub },
  { "operator_mul", glm_line_operator_mul },
  { "equal", glm_line_equal },
  { "notEqual", glm_line_notEqual },
  { "to_segment", glm_line_to_segment },
  { "isinf", glm_line_isinf },
  { "isnan", glm_line_isnan },
  { "isfinite", glm_line_isfinite },
  { "getPoint", glm_line_getpoint },
  { "closest", glm_line_closest },
  { "closestRay", glm_line_closestRay },
  { "closestLine", glm_line_closestLine },
  { "closestSegment", glm_line_closestSegment },
  { "contains", glm_line_contains },
  { "containsRay", glm_line_containsRay },
  { "containsSegment", glm_line_containsSegment },
  { "distance", glm_line_distance },
  { "distanceRay", glm_line_distanceRay },
  { "distanceLine", glm_line_distanceLine },
  { "distanceSegment", glm_line_distanceSegment },
  { "distanceSphere", glm_line_distanceSphere },
  { "intersectAABB", glm_line_intersectAABB },
  { "intersectSphere", glm_line_intersectSphere },
  { "intersectPlane", glm_line_intersectPlane },
  { "projectToAxis", glm_line_projectToAxis },
  { GLM_NULLPTR, GLM_NULLPTR }
};

/* }================================================================== */

/*
** {==================================================================
** Ray
** ===================================================================
*/

TRAITS_DEFN(ray_operator_negate, operator-, gLuaRay<>)
TRAITS_DEFN(ray_operator_equals, operator==, gLuaRay<>, gLuaRay<>)
TRAITS_DEFN(ray_operator_add, operator+, gLuaRay<>, gLuaVec3<>)
TRAITS_DEFN(ray_operator_sub, operator-, gLuaRay<>, gLuaVec3<>)
ROTATION_MATRIX_DEFN(ray_operator_mul, operator*, LAYOUT_UNARY, gLuaRay<>)
TRAITS_LAYOUT_DEFN(ray_equal, glm::equal, GEOM_EQUALS, gLuaRay<>)
TRAITS_LAYOUT_DEFN(ray_notEqual, glm::notEqual, GEOM_EQUALS, gLuaRay<>)
TRAITS_DEFN(ray_isinf, glm::isinf, gLuaRay<>)
TRAITS_DEFN(ray_isnan, glm::isnan, gLuaRay<>)
TRAITS_DEFN(ray_isfinite, glm::isfinite, gLuaRay<>)
TRAITS_DEFN(ray_getPoint, glm::getPoint, gLuaRay<>, gLuaFloat)
TRAITS_LAYOUT_DEFN(ray_closest, glm::closestPoint, GEOM_DISTANCE, gLuaRay<>, gLuaVec3<>)
TRAITS_LAYOUT_DEFN(ray_closestRay, glm::closestPoint, GEOM_INTERSECTS, gLuaRay<>, gLuaRay<>)
TRAITS_LAYOUT_DEFN(ray_closestLine, glm::closestPoint, GEOM_INTERSECTS, gLuaRay<>, gLuaLine<>)
TRAITS_LAYOUT_DEFN(ray_closestSegment, glm::closestPoint, GEOM_INTERSECTS, gLuaRay<>, gLuaSegment<>)
TRAITS_DEFN(ray_contains, glm::contains, gLuaRay<>, gLuaVec3<>, gLuaEps<>)
TRAITS_DEFN(ray_containsSegment, glm::contains, gLuaRay<>, gLuaSegment<>, gLuaEps<>)
TRAITS_LAYOUT_DEFN(ray_distance, glm::distance, GEOM_DISTANCE, gLuaRay<>, gLuaVec3<>)
TRAITS_LAYOUT_DEFN(ray_distanceRay, glm::distance, GEOM_INTERSECTS, gLuaRay<>, gLuaRay<>)
TRAITS_LAYOUT_DEFN(ray_distanceLine, glm::distance, GEOM_INTERSECTS, gLuaRay<>, gLuaLine<>)
TRAITS_LAYOUT_DEFN(ray_distanceSegment, glm::distance, GEOM_INTERSECTS, gLuaRay<>, gLuaSegment<>)
TRAITS_DEFN(ray_distanceSphere, glm::distance, gLuaRay<>, gLuaSphere<>)
TRAITS_LAYOUT_DEFN(ray_intersectSphere, glm::intersects, GEOM_INTERSECTS, gLuaRay<>, gLuaSphere<>)
TRAITS_LAYOUT_DEFN(ray_intersectAABB, glm::intersects, GEOM_INTERSECTS, gLuaRay<>, gLuaAABB<>)
TRAITS_LAYOUT_DEFN(ray_intersectPlane, glm::intersects, GEOM_DISTANCE, gLuaRay<>, gLuaPlane<>)
TRAITS_LAYOUT_DEFN(ray_projectToAxis, glm::projectToAxis, GEOM_PROJECTION, gLuaRay<>, gLuaVec3<>)

static const luaL_Reg luaglm_raylib[] = {
  { "operator_negate", glm_ray_operator_negate },
  { "operator_equals", glm_ray_operator_equals },
  { "operator_add", glm_ray_operator_add },
  { "operator_sub", glm_ray_operator_sub },
  { "operator_mul", glm_ray_operator_mul },
  { "equal", glm_ray_equal },
  { "notEqual", glm_ray_notEqual },
  { "isinf", glm_ray_isinf },
  { "isnan", glm_ray_isnan },
  { "isfinite", glm_ray_isfinite },
  { "getPoint", glm_ray_getPoint },
  { "closest", glm_ray_closest },
  { "closestRay", glm_ray_closestRay },
  { "closestLine", glm_ray_closestLine },
  { "closestSegment", glm_ray_closestSegment },
  { "contains", glm_ray_contains },
  { "containsSegment", glm_ray_containsSegment },
  { "distance", glm_ray_distance },
  { "distanceRay", glm_ray_distanceRay },
  { "distanceLine", glm_ray_distanceLine },
  { "distanceSegment", glm_ray_distanceSegment },
  { "distanceSphere", glm_ray_distanceSphere },
  { "intersectSphere", glm_ray_intersectSphere },
  { "intersectAABB", glm_ray_intersectAABB },
  { "intersectPlane", glm_ray_intersectPlane },
  { "projectToAxis", glm_ray_projectToAxis },
  { GLM_NULLPTR, GLM_NULLPTR }
};

/* }================================================================== */

/*
** {==================================================================
** LineSegment
** ===================================================================
*/

TRAITS_DEFN(segment_operator_negate, operator-, gLuaSegment<>)
TRAITS_DEFN(segment_operator_equals, operator==, gLuaSegment<>, gLuaSegment<>)
TRAITS_DEFN(segment_operator_add, operator+, gLuaSegment<>, gLuaVec3<>)
TRAITS_DEFN(segment_operator_sub, operator-, gLuaSegment<>, gLuaVec3<>)
ROTATION_MATRIX_DEFN(segment_operator_mul, operator*, LAYOUT_UNARY, gLuaSegment<>)
TRAITS_LAYOUT_DEFN(segment_equal, glm::equal, GEOM_EQUALS, gLuaSegment<>)
TRAITS_LAYOUT_DEFN(segment_notEqual, glm::notEqual, GEOM_EQUALS, gLuaSegment<>)
TRAITS_DEFN(segment_length, glm::length, gLuaSegment<>)
TRAITS_DEFN(segment_length2, glm::length2, gLuaSegment<>)
TRAITS_DEFN(segment_isfinite, glm::isfinite, gLuaSegment<>)
TRAITS_DEFN(segment_getPoint, glm::getPoint, gLuaSegment<>, gLuaFloat)
TRAITS_DEFN(segment_centerPoint, glm::centerPoint, gLuaSegment<>)
TRAITS_DEFN(segment_reverse, glm::reverse, gLuaSegment<>)
TRAITS_DEFN(segment_dir, glm::dir, gLuaSegment<>)
TRAITS_DEFN(segment_extremePoint, glm::extremePoint, gLuaSegment<>, gLuaVec3<>)
TRAITS_LAYOUT_DEFN(segment_closestPoint, glm::closestPoint, GEOM_DISTANCE, gLuaSegment<>, gLuaVec3<>)
TRAITS_LAYOUT_DEFN(segment_closestRay, glm::closestPoint, GEOM_INTERSECTS, gLuaSegment<>, gLuaRay<>)
TRAITS_LAYOUT_DEFN(segment_closestLine, glm::closestPoint, GEOM_INTERSECTS, gLuaSegment<>, gLuaLine<>)
TRAITS_LAYOUT_DEFN(segment_closestSegment, glm::closestPoint, GEOM_INTERSECTS, gLuaSegment<>, gLuaSegment<>)
TRAITS_DEFN(segment_containsPoint, glm::contains, gLuaSegment<>, gLuaVec3<>, gLuaEps<>)
TRAITS_DEFN(segment_containsSegment, glm::contains, gLuaSegment<>, gLuaSegment<>, gLuaEps<>)
TRAITS_LAYOUT_DEFN(segment_distance2, glm::distance2, GEOM_DISTANCE, gLuaSegment<>, gLuaVec3<>)
TRAITS_LAYOUT_DEFN(segment_distanceSegment2, glm::distance2, GEOM_INTERSECTS, gLuaSegment<>, gLuaSegment<>)
TRAITS_LAYOUT_DEFN(segment_distance, glm::distance, GEOM_DISTANCE, gLuaSegment<>, gLuaVec3<>)
TRAITS_LAYOUT_DEFN(segment_distanceRay, glm::distance, GEOM_INTERSECTS, gLuaSegment<>, gLuaRay<>)
TRAITS_LAYOUT_DEFN(segment_distanceLine, glm::distance, GEOM_INTERSECTS, gLuaSegment<>, gLuaLine<>)
TRAITS_LAYOUT_DEFN(segment_distanceSegment, glm::distance, GEOM_INTERSECTS, gLuaSegment<>, gLuaSegment<>)
TRAITS_DEFN(segment_distancePlane, glm::distance, gLuaSegment<>, gLuaPlane<>)
TRAITS_LAYOUT_DEFN(segment_intersectsSphere, glm::intersects, GEOM_INTERSECTS, gLuaSegment<>, gLuaSphere<>)
TRAITS_LAYOUT_DEFN(segment_intersectsAABB, glm::intersects, GEOM_INTERSECTS, gLuaSegment<>, gLuaAABB<>)
TRAITS_DEFN(segment_intersectsPlane, glm::intersects, gLuaSegment<>, gLuaPlane<>)
TRAITS_LAYOUT_DEFN(segment_intersectsSegment, glm::intersects, GEOM_INTERSECTS, gLuaSegment<>, gLuaSegment<>)

static const luaL_Reg luaglm_segmentlib[] = {
  { "operator_negate", glm_segment_operator_negate },
  { "operator_equals", glm_segment_operator_equals },
  { "operator_add", glm_segment_operator_add },
  { "operator_sub", glm_segment_operator_sub },
  { "operator_mul", glm_segment_operator_mul },
  { "equal", glm_segment_equal },
  { "notEqual", glm_segment_notEqual },
  { "length", glm_segment_length },
  { "length2", glm_segment_length2 },
  { "isfinite", glm_segment_isfinite },
  { "getPoint", glm_segment_getPoint },
  { "centerPoint", glm_segment_centerPoint },
  { "centroid", glm_segment_centerPoint },
  { "reverse", glm_segment_reverse },
  { "dir", glm_segment_dir },
  { "extremePoint", glm_segment_extremePoint },
  { "closestPoint", glm_segment_closestPoint },
  { "closestRay", glm_segment_closestRay },
  { "closestLine", glm_segment_closestLine },
  { "closestSegment", glm_segment_closestSegment },
  { "containsPoint", glm_segment_containsPoint },
  { "containsSegment", glm_segment_containsSegment },
  { "distance2", glm_segment_distance2 },
  { "distanceSegment2", glm_segment_distanceSegment2 },
  { "distance", glm_segment_distance },
  { "distanceRay", glm_segment_distanceRay },
  { "distanceLine", glm_segment_distanceLine },
  { "distanceSegment", glm_segment_distanceSegment },
  { "distancePlane", glm_segment_distancePlane },
  { "intersectsSphere", glm_segment_intersectsSphere },
  { "intersectsAABB", glm_segment_intersectsAABB },
  { "intersectsPlane", glm_segment_intersectsPlane },
  { "intersectsSegment", glm_segment_intersectsSegment },
  { GLM_NULLPTR, GLM_NULLPTR }
};

/* }================================================================== */

/*
** {==================================================================
** LineSegment2D
** ===================================================================
*/

TRAITS_DEFN(segment2d_operator_negate, operator-, gLuaSegment<2>)
TRAITS_DEFN(segment2d_operator_equals, operator==, gLuaSegment<2>, gLuaSegment<2>)
TRAITS_DEFN(segment2d_operator_add, operator+, gLuaSegment<2>, gLuaVec2<>)
TRAITS_DEFN(segment2d_operator_sub, operator-, gLuaSegment<2>, gLuaVec2<>)
TRAITS_LAYOUT_DEFN(segment2d_equal, glm::equal, GEOM_EQUALS, gLuaSegment<2>)
TRAITS_LAYOUT_DEFN(segment2d_notEqual, glm::notEqual, GEOM_EQUALS, gLuaSegment<2>)
TRAITS_DEFN(segment2d_length, glm::length, gLuaSegment<2>)
TRAITS_DEFN(segment2d_length2, glm::length2, gLuaSegment<2>)
TRAITS_DEFN(segment2d_isfinite, glm::isfinite, gLuaSegment<2>)
TRAITS_DEFN(segment2d_getPoint, glm::getPoint, gLuaSegment<2>, gLuaFloat)
TRAITS_DEFN(segment2d_centerPoint, glm::centerPoint, gLuaSegment<2>)
TRAITS_DEFN(segment2d_reverse, glm::reverse, gLuaSegment<2>)
TRAITS_DEFN(segment2d_dir, glm::dir, gLuaSegment<2>)
TRAITS_DEFN(segment2d_extremePoint, glm::extremePoint, gLuaSegment<2>, gLuaVec2<>)
TRAITS_LAYOUT_DEFN(segment2d_closestPoint, glm::closestPoint, GEOM_DISTANCE, gLuaSegment<2>, gLuaVec2<>)
TRAITS_LAYOUT_DEFN(segment2d_closestRay, glm::closestPoint, GEOM_INTERSECTS, gLuaSegment<2>, gLuaRay<2>)
TRAITS_LAYOUT_DEFN(segment2d_closestLine, glm::closestPoint, GEOM_INTERSECTS, gLuaSegment<2>, gLuaLine<2>)
TRAITS_LAYOUT_DEFN(segment2d_closestSegment, glm::closestPoint, GEOM_INTERSECTS, gLuaSegment<2>, gLuaSegment<2>)
TRAITS_DEFN(segment2d_containsPoint, glm::contains, gLuaSegment<2>, gLuaVec2<>, gLuaEps<>)
TRAITS_DEFN(segment2d_containsSegment, glm::contains, gLuaSegment<2>, gLuaSegment<2>, gLuaEps<>)
TRAITS_LAYOUT_DEFN(segment2d_distance2, glm::distance2, GEOM_DISTANCE, gLuaSegment<2>, gLuaVec2<>)
TRAITS_LAYOUT_DEFN(segment2d_distanceSegment2, glm::distance2, GEOM_INTERSECTS, gLuaSegment<2>, gLuaSegment<2>)
TRAITS_LAYOUT_DEFN(segment2d_distance, glm::distance, GEOM_DISTANCE, gLuaSegment<2>, gLuaVec2<>)
TRAITS_LAYOUT_DEFN(segment2d_distanceRay, glm::distance, GEOM_INTERSECTS, gLuaSegment<2>, gLuaRay<2>)
TRAITS_LAYOUT_DEFN(segment2d_distanceLine, glm::distance, GEOM_INTERSECTS, gLuaSegment<2>, gLuaLine<2>)
TRAITS_LAYOUT_DEFN(segment2d_distanceSegment, glm::distance, GEOM_INTERSECTS, gLuaSegment<2>, gLuaSegment<2>)
TRAITS_DEFN(segment2d_distancePlane, glm::distance, gLuaSegment<2>, gLuaPlane<2>)
TRAITS_LAYOUT_DEFN(segment2d_intersectsAABB, glm::intersects, GEOM_INTERSECTS, gLuaSegment<2>, gLuaAABB<2>)
TRAITS_LAYOUT_DEFN(segment2d_intersectsSegment, glm::intersects, GEOM_INTERSECTS, gLuaSegment<2>, gLuaSegment<2>)

static const luaL_Reg luaglm_segment2dlib[] = {
  { "operator_negate", glm_segment2d_operator_negate },
  { "operator_equals", glm_segment2d_operator_equals },
  { "operator_add", glm_segment2d_operator_add },
  { "operator_sub", glm_segment2d_operator_sub },
  { "equal", glm_segment2d_equal },
  { "notEqual", glm_segment2d_notEqual },
  { "length", glm_segment2d_length },
  { "length2", glm_segment2d_length2 },
  { "isfinite", glm_segment2d_isfinite },
  { "getPoint", glm_segment2d_getPoint },
  { "centerPoint", glm_segment2d_centerPoint },
  { "centroid", glm_segment2d_centerPoint },
  { "reverse", glm_segment2d_reverse },
  { "dir", glm_segment2d_dir },
  { "extremePoint", glm_segment2d_extremePoint },
  { "closestPoint", glm_segment2d_closestPoint },
  { "closestRay", glm_segment2d_closestRay },
  { "closestLine", glm_segment2d_closestLine },
  { "closestSegment", glm_segment2d_closestSegment },
  { "containsPoint", glm_segment2d_containsPoint },
  { "containsSegment", glm_segment2d_containsSegment },
  { "distance2", glm_segment2d_distance2 },
  { "distanceSegment2", glm_segment2d_distanceSegment2 },
  { "distance", glm_segment2d_distance },
  { "distanceRay", glm_segment2d_distanceRay },
  { "distanceLine", glm_segment2d_distanceLine },
  { "distanceSegment", glm_segment2d_distanceSegment },
  { "distancePlane", glm_segment2d_distancePlane },
  { "intersectsAABB", glm_segment2d_intersectsAABB },
  { "intersectsSegment", glm_segment2d_intersectsSegment },
  { GLM_NULLPTR, GLM_NULLPTR }
};

/* }================================================================== */

/*
** {==================================================================
** Sphere
** ===================================================================
*/

GLM_BINDING_QUALIFIER(sphere_fitThroughPoints) {
  GLM_BINDING_BEGIN
  switch (LB.top()) {
    case 2: TRAITS_FUNC(LB, glm::fitThroughPoints, gLuaVec3<>, gLuaVec3<>); break;
    case 3: TRAITS_FUNC(LB, glm::fitThroughPoints, gLuaVec3<>, gLuaVec3<>, gLuaVec3<>); break;
    default: TRAITS_FUNC(LB, glm::fitThroughPoints, gLuaVec3<>, gLuaVec3<>, gLuaVec3<>, gLuaVec3<>); break;
  }
  GLM_BINDING_END
}

GLM_BINDING_QUALIFIER(sphere_optimalEnclosingSphere) {
  GLM_BINDING_BEGIN
  switch (LB.top()) {
    case 2: TRAITS_FUNC(LB, glm::optimalEnclosingSphere, gLuaVec3<>, gLuaVec3<>); break;
    case 3: TRAITS_FUNC(LB, glm::optimalEnclosingSphere, gLuaVec3<>, gLuaVec3<>, gLuaVec3<>); break;
    case 4: TRAITS_FUNC(LB, glm::optimalEnclosingSphere, gLuaVec3<>, gLuaVec3<>, gLuaVec3<>, gLuaVec3<>); break;
    default: {
      using List = glm::List<gLuaVec3<>::type>;

      // @TODO: This implementation is UNSAFE. Create a glm::List userdata that
      // is temporarily anchored onto the stack for the duration of the function
      List pts;
      auto push_back = [&pts](const gLuaVec3<>::type &v) { pts.push_back(v); };

      if (lua_istable(LB.L, LB.idx))
        glmLuaArray::forEach<gLuaVec3<>>(LB.L, LB.idx, push_back);
      else
        glmLuaStack::forEach<gLuaVec3<>>(LB.L, LB.idx, push_back);
      return gLuaBase::Push(LB, glm::optimalEnclosingSphere<glm_Float, glm::defaultp, List>(pts));
    }
  }
  GLM_BINDING_END
}

TRAITS_DEFN(sphere_operator_negate, operator-, gLuaSphere<>)
TRAITS_DEFN(sphere_operator_equals, operator==, gLuaSphere<>, gLuaSphere<>)
TRAITS_DEFN(sphere_operator_add, operator+, gLuaSphere<>, gLuaVec3<>)
TRAITS_DEFN(sphere_operator_sub, operator-, gLuaSphere<>, gLuaVec3<>)
ROTATION_MATRIX_DEFN(sphere_operator_mul, operator*, LAYOUT_UNARY, gLuaSphere<>)
TRAITS_LAYOUT_DEFN(sphere_equal, glm::equal, GEOM_EQUALS, gLuaSphere<>)
TRAITS_LAYOUT_DEFN(sphere_notEqual, glm::notEqual, GEOM_EQUALS, gLuaSphere<>)
TRAITS_DEFN(sphere_volume, glm::volume, gLuaSphere<>)
TRAITS_DEFN(sphere_surfaceArea, glm::surfaceArea, gLuaSphere<>)
TRAITS_DEFN(sphere_isinf, glm::isinf, gLuaSphere<>)
TRAITS_DEFN(sphere_isnan, glm::isnan, gLuaSphere<>)
TRAITS_DEFN(sphere_isfinite, glm::isfinite, gLuaSphere<>)
TRAITS_DEFN(sphere_isDegenerate, glm::isDegenerate, gLuaSphere<>)
TRAITS_DEFN(sphere_extremePoint, glm::extremePoint, gLuaSphere<>, gLuaVec3<>)
TRAITS_DEFN(sphere_contains, glm::contains, gLuaSphere<>, gLuaVec3<>, gLuaEps<>)
TRAITS_DEFN(sphere_containsSegment, glm::contains, gLuaSphere<>, gLuaSegment<>)
TRAITS_DEFN(sphere_containsSphere, glm::contains, gLuaSphere<>, gLuaSphere<>, gLuaEps<>)
TRAITS_DEFN(sphere_containsAABB, glm::contains, gLuaSphere<>, gLuaAABB<>)
TRAITS_DEFN(sphere_distance, glm::distance, gLuaSphere<>, gLuaVec3<>)
TRAITS_DEFN(sphere_distanceSphere, glm::distance, gLuaSphere<>, gLuaSphere<>)
TRAITS_DEFN(sphere_distanceAABB, glm::distance, gLuaSphere<>, gLuaAABB<>)
TRAITS_DEFN(sphere_distanceRay, glm::distance, gLuaSphere<>, gLuaRay<>)
TRAITS_DEFN(sphere_distanceSegment, glm::distance, gLuaSphere<>, gLuaSegment<>)
TRAITS_DEFN(sphere_distanceLine, glm::distance, gLuaSphere<>, gLuaLine<>)
TRAITS_DEFN(sphere_closestPoint, glm::closestPoint, gLuaSphere<>, gLuaVec3<>)
TRAITS_DEFN(sphere_intersectSphere, glm::intersects, gLuaSphere<>, gLuaSphere<>)
TRAITS_DEFN(sphere_intersectAABB, glm::intersects, gLuaSphere<>, gLuaAABB<>)
TRAITS_DEFN(sphere_intersectPlane, glm::intersects, gLuaSphere<>, gLuaPlane<>)
TRAITS_LAYOUT_DEFN(sphere_intersectLine, glm::intersects, GEOM_INTERSECTS_RH, gLuaSphere<>, gLuaLine<>)
TRAITS_LAYOUT_DEFN(sphere_intersectSegment, glm::intersects, GEOM_INTERSECTS_RH, gLuaSphere<>, gLuaSegment<>)
TRAITS_LAYOUT_DEFN(sphere_intersectRay, glm::intersects, GEOM_INTERSECTS_RH, gLuaSphere<>, gLuaRay<>)
TRAITS_DEFN(sphere_enclose, glm::enclose, gLuaSphere<>, gLuaVec3<>)
TRAITS_DEFN(sphere_encloseSegment, glm::enclose, gLuaSphere<>, gLuaSegment<>)
TRAITS_DEFN(sphere_encloseSphere, glm::enclose, gLuaSphere<>, gLuaSphere<>)
TRAITS_DEFN(sphere_encloseAABB, glm::enclose, gLuaSphere<>, gLuaAABB<>)
TRAITS_DEFN(sphere_extendRadiusToContain, glm::extendRadiusToContain, gLuaSphere<>, gLuaVec3<>, gLuaEps<>)
TRAITS_DEFN(sphere_extendRadiusToContainSphere, glm::extendRadiusToContain, gLuaSphere<>, gLuaSphere<>, gLuaEps<>)
TRAITS_DEFN(sphere_maximalContainedAABB, glm::maximalContainedAABB, gLuaSphere<>)
TRAITS_LAYOUT_DEFN(sphere_projectToAxis, glm::projectToAxis, GEOM_PROJECTION, gLuaSphere<>, gLuaVec3<>)

static const luaL_Reg luaglm_spherelib[] = {
  { "operator_negate", glm_sphere_operator_negate },
  { "operator_equals", glm_sphere_operator_equals },
  { "operator_add", glm_sphere_operator_add },
  { "operator_sub", glm_sphere_operator_sub },
  { "operator_mul", glm_sphere_operator_mul },
  { "equal", glm_sphere_equal },
  { "notEqual", glm_sphere_notEqual },
  { "volume", glm_sphere_volume },
  { "surfaceArea", glm_sphere_surfaceArea },
  { "isinf", glm_sphere_isinf },
  { "isnan", glm_sphere_isnan },
  { "isfinite", glm_sphere_isfinite },
  { "isDegenerate", glm_sphere_isDegenerate },
  { "extremePoint", glm_sphere_extremePoint },
  { "contains", glm_sphere_contains },
  { "containsSegment", glm_sphere_containsSegment },
  { "containsSphere", glm_sphere_containsSphere },
  { "containsAABB", glm_sphere_containsAABB },
  { "distance", glm_sphere_distance },
  { "distanceSphere", glm_sphere_distanceSphere },
  { "distanceAABB", glm_sphere_distanceAABB },
  { "distanceRay", glm_sphere_distanceRay },
  { "distanceSegment", glm_sphere_distanceSegment },
  { "distanceLine", glm_sphere_distanceLine },
  { "closestPoint", glm_sphere_closestPoint },
  { "intersectSphere", glm_sphere_intersectSphere },
  { "intersectAABB", glm_sphere_intersectAABB },
  { "intersectLine", glm_sphere_intersectLine },
  { "intersectSegment", glm_sphere_intersectSegment },
  { "intersectRay", glm_sphere_intersectRay },
  { "intersectPlane", glm_sphere_intersectPlane },
  { "enclose", glm_sphere_enclose },
  { "encloseSegment", glm_sphere_encloseSegment },
  { "encloseSphere", glm_sphere_encloseSphere },
  { "encloseAABB", glm_sphere_encloseAABB },
  { "extendRadiusToContain", glm_sphere_extendRadiusToContain },
  { "extendRadiusToContainSphere", glm_sphere_extendRadiusToContainSphere },
  { "maximalContainedAABB", glm_sphere_maximalContainedAABB },
  { "fitThroughPoints", glm_sphere_fitThroughPoints },
  { "optimalEnclosingSphere", glm_sphere_optimalEnclosingSphere },
  { "projectToAxis", glm_sphere_projectToAxis },
  { GLM_NULLPTR, GLM_NULLPTR }
};

/* }================================================================== */

/*
** {==================================================================
** Circle
** ===================================================================
*/

TRAITS_DEFN(circle_operator_negate, operator-, gLuaSphere<2>)
TRAITS_DEFN(circle_operator_equals, operator==, gLuaSphere<2>, gLuaSphere<2>)
TRAITS_DEFN(circle_operator_add, operator+, gLuaSphere<2>, gLuaVec2<>)
TRAITS_DEFN(circle_operator_sub, operator-, gLuaSphere<2>, gLuaVec2<>)
TRAITS_LAYOUT_DEFN(circle_equal, glm::equal, GEOM_EQUALS, gLuaSphere<2>)
TRAITS_LAYOUT_DEFN(circle_notEqual, glm::notEqual, GEOM_EQUALS, gLuaSphere<2>)
TRAITS_DEFN(circle_area, glm::area, gLuaSphere<2>)
TRAITS_DEFN(circle_isinf, glm::isinf, gLuaSphere<2>)
TRAITS_DEFN(circle_isnan, glm::isnan, gLuaSphere<2>)
TRAITS_DEFN(circle_isfinite, glm::isfinite, gLuaSphere<2>)
TRAITS_DEFN(circle_isDegenerate, glm::isDegenerate, gLuaSphere<2>)
TRAITS_DEFN(circle_extremePoint, glm::extremePoint, gLuaSphere<2>, gLuaVec2<>)
TRAITS_DEFN(circle_contains, glm::contains, gLuaSphere<2>, gLuaVec2<>, gLuaEps<>)
TRAITS_DEFN(circle_containsSegment, glm::contains, gLuaSphere<2>, gLuaSegment<2>)
TRAITS_DEFN(circle_containsCircle, glm::contains, gLuaSphere<2>, gLuaSphere<2>, gLuaEps<>)
TRAITS_DEFN(circle_containsAABB, glm::contains, gLuaSphere<2>, gLuaAABB<2>)
TRAITS_DEFN(circle_distance, glm::distance, gLuaSphere<2>, gLuaVec2<>)
TRAITS_DEFN(circle_distanceSphere, glm::distance, gLuaSphere<2>, gLuaSphere<2>)
TRAITS_DEFN(circle_distanceAABB, glm::distance, gLuaSphere<2>, gLuaAABB<2>)
TRAITS_DEFN(circle_distanceRay, glm::distance, gLuaSphere<2>, gLuaRay<2>)
TRAITS_DEFN(circle_distanceSegment, glm::distance, gLuaSphere<2>, gLuaSegment<2>)
TRAITS_DEFN(circle_distanceLine, glm::distance, gLuaSphere<2>, gLuaLine<2>)
TRAITS_DEFN(circle_closestPoint, glm::closestPoint, gLuaSphere<2>, gLuaVec2<>)
TRAITS_DEFN(circle_intersectCircle, glm::intersects, gLuaSphere<2>, gLuaSphere<2>)
TRAITS_DEFN(circle_intersectAABB, glm::intersects, gLuaSphere<2>, gLuaAABB<2>)
TRAITS_DEFN(circle_intersectPlane, glm::intersects, gLuaSphere<2>, gLuaPlane<2>)
TRAITS_LAYOUT_DEFN(circle_intersectLine, glm::intersects, GEOM_INTERSECTS_RH, gLuaSphere<2>, gLuaLine<2>)
TRAITS_LAYOUT_DEFN(circle_intersectSegment, glm::intersects, GEOM_INTERSECTS_RH, gLuaSphere<2>, gLuaSegment<2>)
TRAITS_LAYOUT_DEFN(circle_intersectRay, glm::intersects, GEOM_INTERSECTS_RH, gLuaSphere<2>, gLuaRay<2>)
TRAITS_DEFN(circle_enclose, glm::enclose, gLuaSphere<2>, gLuaVec2<>)
TRAITS_DEFN(circle_encloseSegment, glm::enclose, gLuaSphere<2>, gLuaSegment<2>)
TRAITS_DEFN(circle_encloseSphere, glm::enclose, gLuaSphere<2>, gLuaSphere<2>)
TRAITS_DEFN(circle_encloseAABB, glm::enclose, gLuaSphere<2>, gLuaAABB<2>)
TRAITS_DEFN(circle_extendRadiusToContain, glm::extendRadiusToContain, gLuaSphere<2>, gLuaVec2<>, gLuaEps<>)
TRAITS_DEFN(circle_extendRadiusToContainCircle, glm::extendRadiusToContain, gLuaSphere<2>, gLuaSphere<2>, gLuaEps<>)
TRAITS_DEFN(circle_maximalContainedAABB, glm::maximalContainedAABB, gLuaSphere<2>)
TRAITS_LAYOUT_DEFN(circle_projectToAxis, glm::projectToAxis, GEOM_PROJECTION, gLuaSphere<2>, gLuaVec2<>)

static const luaL_Reg luaglm_circlelib[] = {
  { "operator_negate", glm_circle_operator_negate },
  { "operator_equals", glm_circle_operator_equals },
  { "operator_add", glm_circle_operator_add },
  { "operator_sub", glm_circle_operator_sub },
  { "equal", glm_circle_equal },
  { "notEqual", glm_circle_notEqual },
  { "area", glm_circle_area },
  { "isinf", glm_circle_isinf },
  { "isnan", glm_circle_isnan },
  { "isfinite", glm_circle_isfinite },
  { "isDegenerate", glm_circle_isDegenerate },
  { "extremePoint", glm_circle_extremePoint },
  { "contains", glm_circle_contains },
  { "containsSegment", glm_circle_containsSegment },
  { "containsCircle", glm_circle_containsCircle },
  { "containsAABB", glm_circle_containsAABB },
  { "distance", glm_circle_distance },
  { "distanceSphere", glm_circle_distanceSphere },
  { "distanceAABB", glm_circle_distanceAABB },
  { "distanceRay", glm_circle_distanceRay },
  { "distanceSegment", glm_circle_distanceSegment },
  { "distanceLine", glm_circle_distanceLine },
  { "closestPoint", glm_circle_closestPoint },
  { "intersectCircle", glm_circle_intersectCircle },
  { "intersectAABB", glm_circle_intersectAABB },
  { "intersectLine", glm_circle_intersectLine },
  { "intersectSegment", glm_circle_intersectSegment },
  { "intersectRay", glm_circle_intersectRay },
  { "intersectPlane", glm_circle_intersectPlane },
  { "enclose", glm_circle_enclose },
  { "encloseSegment", glm_circle_encloseSegment },
  { "encloseSphere", glm_circle_encloseSphere },
  { "encloseAABB", glm_circle_encloseAABB },
  { "extendRadiusToContain", glm_circle_extendRadiusToContain },
  { "extendRadiusToContainCircle", glm_circle_extendRadiusToContainCircle },
  { "maximalContainedAABB", glm_circle_maximalContainedAABB },
  { "projectToAxis", glm_circle_projectToAxis },
  { GLM_NULLPTR, GLM_NULLPTR }
};

/* }================================================================== */

/*
** {==================================================================
** Plane
** ===================================================================
*/

TRAITS_DEFN(plane_operator_negate, operator-, gLuaPlane<>)
TRAITS_DEFN(plane_operator_equals, operator==, gLuaPlane<>, gLuaPlane<>)
TRAITS_DEFN(plane_operator_add, operator+, gLuaPlane<>, gLuaVec3<>)
TRAITS_DEFN(plane_operator_sub, operator-, gLuaPlane<>, gLuaVec3<>)
ROTATION_MATRIX_DEFN(plane_operator_mul, operator*, LAYOUT_UNARY, gLuaPlane<>)
TRAITS_LAYOUT_DEFN(plane_equal, glm::equal, GEOM_EQUALS, gLuaPlane<>)
TRAITS_LAYOUT_DEFN(plane_notEqual, glm::notEqual, GEOM_EQUALS, gLuaPlane<>)
TRAITS_DEFN(plane_fromRay, glm::planeFrom, gLuaRay<>, gLuaVec3<>)
TRAITS_DEFN(plane_fromLine, glm::planeFrom, gLuaLine<>, gLuaVec3<>)
TRAITS_DEFN(plane_fromLineSegment, glm::planeFrom, gLuaSegment<>, gLuaVec3<>)
TRAITS_DEFN(plane_fromPointNormal, glm::planeFrom, gLuaVec3<>, gLuaVec3<>)
TRAITS_DEFN(plane_fromPoints, glm::planeFrom, gLuaVec3<>, gLuaVec3<>, gLuaVec3<>)
TRAITS_DEFN(plane_isDegenerate, glm::isDegenerate, gLuaPlane<>)
TRAITS_DEFN(plane_isParallel, glm::isParallel, gLuaPlane<>, gLuaPlane<>, gLuaEps<>)
TRAITS_DEFN(plane_areOnSameSide, glm::areOnSameSide, gLuaPlane<>, gLuaVec3<>, gLuaVec3<>)
TRAITS_DEFN(plane_isInPositiveDirection, glm::isInPositiveDirection, gLuaPlane<>, gLuaVec3<>)
TRAITS_DEFN(plane_isOnPositiveSide, glm::isOnPositiveSide, gLuaPlane<>, gLuaVec3<>)
TRAITS_DEFN(plane_passesThroughOrigin, glm::passesThroughOrigin, gLuaPlane<>, gLuaEps<>)
TRAITS_DEFN(plane_angle, glm::angle, gLuaPlane<>, gLuaPlane<>)
TRAITS_DEFN(plane_reverseNormal, glm::reverseNormal, gLuaPlane<>)
TRAITS_DEFN(plane_pointOnPlane, glm::pointOnPlane, gLuaPlane<>)
TRAITS_DEFN(plane_refract, glm::refract, gLuaPlane<>, gLuaVec3<>, gLuaFloat, gLuaFloat)
TRAITS_DEFN(plane_project, glm::project, gLuaPlane<>, gLuaVec3<>)
TRAITS_DEFN(plane_projectLine, glm::project, gLuaPlane<>, gLuaLine<>)
TRAITS_DEFN(plane_projectSegment, glm::project, gLuaPlane<>, gLuaSegment<>)
TRAITS_DEFN(plane_projectRay, glm::project, gLuaPlane<>, gLuaRay<>)
TRAITS_DEFN(plane_projectToNegativeHalf, glm::projectToNegativeHalf, gLuaPlane<>, gLuaVec3<>)
TRAITS_DEFN(plane_projectToPositiveHalf, glm::projectToPositiveHalf, gLuaPlane<>, gLuaVec3<>)
TRAITS_DEFN(plane_distance, glm::distance, gLuaPlane<>, gLuaVec3<>)
TRAITS_DEFN(plane_distanceSegment, glm::distance, gLuaPlane<>, gLuaSegment<>)
TRAITS_DEFN(plane_distanceSphere, glm::distance, gLuaPlane<>, gLuaSphere<>)
TRAITS_DEFN(plane_signedDistance, glm::signedDistance, gLuaPlane<>, gLuaVec3<>)
TRAITS_DEFN(plane_signedDistanceLine, glm::signedDistance, gLuaPlane<>, gLuaLine<>)
TRAITS_DEFN(plane_signedDistanceSegment, glm::signedDistance, gLuaPlane<>, gLuaSegment<>)
TRAITS_DEFN(plane_signedDistanceRay, glm::signedDistance, gLuaPlane<>, gLuaRay<>)
TRAITS_DEFN(plane_signedDistanceAABB, glm::signedDistance, gLuaPlane<>, gLuaAABB<>)
TRAITS_DEFN(plane_signedDistanceSphere, glm::signedDistance, gLuaPlane<>, gLuaSphere<>)
TRAITS_DEFN(plane_orthoProjection, glm::orthoProjection, gLuaPlane<>)
TRAITS_DEFN(plane_mirrorMatrix, glm::mirrorMatrix, gLuaPlane<>)
TRAITS_DEFN(plane_mirror, glm::mirror, gLuaPlane<>, gLuaVec3<>)
TRAITS_DEFN(plane_closestPointRay, glm::closestPoint, gLuaPlane<>, gLuaRay<>)
TRAITS_DEFN(plane_closestPointSegment, glm::closestPoint, gLuaPlane<>, gLuaSegment<>)
TRAITS_DEFN(plane_contains, glm::contains, gLuaPlane<>, gLuaVec3<>, gLuaEps<>)
TRAITS_DEFN(plane_containsLine, glm::contains, gLuaPlane<>, gLuaLine<>, gLuaEps<>)
TRAITS_DEFN(plane_containsRay, glm::contains, gLuaPlane<>, gLuaRay<>, gLuaEps<>)
TRAITS_DEFN(plane_containsSegment, glm::contains, gLuaPlane<>, gLuaSegment<>, gLuaEps<>)
TRAITS_LAYOUT_DEFN(plane_intersectsRay, glm::intersects, GEOM_DISTANCE, gLuaPlane<>, gLuaRay<>)
TRAITS_LAYOUT_DEFN(plane_intersectsLine, glm::intersects, GEOM_DISTANCE, gLuaPlane<>, gLuaLine<>)
TRAITS_LAYOUT_DEFN(plane_intersectsSegment, glm::intersects, GEOM_DISTANCE, gLuaPlane<>, gLuaSegment<>)
TRAITS_DEFN(plane_intersectsSphere, glm::intersects, gLuaPlane<>, gLuaSphere<>)
TRAITS_DEFN(plane_intersectsAABB, glm::intersects, gLuaPlane<>, gLuaAABB<>)
TRAITS_DEFN(plane_clipSegment, glm::clip, gLuaPlane<>, gLuaSegment<>)

GLM_BINDING_QUALIFIER(plane_point) {
  GLM_BINDING_BEGIN
  if (LB.top() > 3)
    TRAITS_FUNC(LB, glm::point, gLuaPlane<>, gLuaFloat, gLuaFloat, gLuaVec3<>);
  TRAITS_FUNC(LB, glm::point, gLuaPlane<>, gLuaFloat, gLuaFloat);
  GLM_BINDING_END
}

GLM_BINDING_QUALIFIER(plane_clipLine) {
  GLM_BINDING_BEGIN
  gLuaRay<>::type result;
  const gLuaPlane<>::type plane = gLuaPlane<>::Next(LB);
  const gLuaLine<>::type line = gLuaLine<>::Next(LB);
  const int clip_type = glm::clip(plane, line, result);
  TRAITS_PUSH(LB, clip_type, result);
  GLM_BINDING_END
}

GLM_BINDING_QUALIFIER(plane_intersectsPlane) {
  GLM_BINDING_BEGIN
  gLuaPlane<>::Point::type result;
  const gLuaPlane<>::type a = gLuaPlane<>::Next(LB);
  const gLuaPlane<>::type b = gLuaPlane<>::Next(LB);
  const gLuaPlane<>::type c = gLuaPlane<>::Next(LB);
  if (glm::intersects(a, b, c, result))
    TRAITS_PUSH(LB, true, result);
  else
    TRAITS_PUSH(LB, false);
  GLM_BINDING_END
}

static const luaL_Reg luaglm_planelib[] = {
  { "operator_negate", glm_plane_operator_negate },
  { "operator_equals", glm_plane_operator_equals },
  { "operator_add", glm_plane_operator_add },
  { "operator_sub", glm_plane_operator_sub },
  { "operator_mul", glm_plane_operator_mul },
  { "equal", glm_plane_equal },
  { "notEqual", glm_plane_notEqual },
  { "fromRay", glm_plane_fromRay },
  { "fromLine", glm_plane_fromLine },
  { "fromLineSegment", glm_plane_fromLineSegment },
  { "fromPointNormal", glm_plane_fromPointNormal },
  { "fromPoints", glm_plane_fromPoints },
  { "isDegenerate", glm_plane_isDegenerate },
  { "isParallel", glm_plane_isParallel },
  { "areOnSameSide", glm_plane_areOnSameSide },
  { "isInPositiveDirection", glm_plane_isInPositiveDirection },
  { "isOnPositiveSide", glm_plane_isOnPositiveSide },
  { "passesThroughOrigin", glm_plane_passesThroughOrigin },
  { "angle", glm_plane_angle },
  { "reverseNormal", glm_plane_reverseNormal },
  { "pointOnPlane", glm_plane_pointOnPlane },
  { "point", glm_plane_point },
  { "refract", glm_plane_refract },
  { "project", glm_plane_project },
  { "projectLine", glm_plane_projectLine },
  { "projectSegment", glm_plane_projectSegment },
  { "projectRay", glm_plane_projectRay },
  { "projectToNegativeHalf", glm_plane_projectToNegativeHalf },
  { "projectToPositiveHalf", glm_plane_projectToPositiveHalf },
  { "distance", glm_plane_distance },
  { "distanceSegment", glm_plane_distanceSegment },
  { "distanceSphere", glm_plane_distanceSphere },
  { "signedDistance", glm_plane_signedDistance },
  { "signedDistanceLine", glm_plane_signedDistanceLine },
  { "signedDistanceSegment", glm_plane_signedDistanceSegment },
  { "signedDistanceRay", glm_plane_signedDistanceRay },
  { "signedDistanceAABB", glm_plane_signedDistanceAABB },
  { "signedDistanceSphere", glm_plane_signedDistanceSphere },
  { "orthoProjection", glm_plane_orthoProjection },
  { "mirrorMatrix", glm_plane_mirrorMatrix },
  { "mirror", glm_plane_mirror },
  { "closestPointRay", glm_plane_closestPointRay },
  { "closestPointSegment", glm_plane_closestPointSegment },
  { "contains", glm_plane_contains },
  { "containsLine", glm_plane_containsLine },
  { "containsRay", glm_plane_containsRay },
  { "containsSegment", glm_plane_containsSegment },
  { "intersectsRay", glm_plane_intersectsRay },
  { "intersectsLine", glm_plane_intersectsLine },
  { "intersectsSegment", glm_plane_intersectsSegment },
  { "intersectsSphere", glm_plane_intersectsSphere },
  { "intersectsAABB", glm_plane_intersectsAABB },
  { "intersectsPlane", glm_plane_intersectsPlane },
  { "clipSegment", glm_plane_clipSegment },
  { "clipLine", glm_plane_clipLine },
  { GLM_NULLPTR, GLM_NULLPTR },
};

/* }================================================================== */

/*
** {==================================================================
** Polygon
** ===================================================================
*/

TRAITS_DEFN(polygon_operator_negate, operator-, gLuaPolygon<>)
TRAITS_DEFN(polygon_operator_equals, operator==, gLuaPolygon<>, gLuaPolygon<>)
TRAITS_DEFN(polygon_operator_add, operator+, gLuaPolygon<>, gLuaVec3<>)
TRAITS_DEFN(polygon_operator_sub, operator-, gLuaPolygon<>, gLuaVec3<>)
ROTATION_MATRIX_DEFN(polygon_operator_mul, operator*, LAYOUT_UNARY, gLuaPolygon<>)
TRAITS_DEFN(polygon_edge, glm::edge, gLuaPolygon<>, gLuaTrait<size_t>)
TRAITS_DEFN(polygon_edge2d, glm::edge2d, gLuaPolygon<>, gLuaTrait<size_t>)
TRAITS_DEFN(polygon_diagonal, glm::diagonal, gLuaPolygon<>, gLuaTrait<size_t>, gLuaTrait<size_t>)
TRAITS_DEFN(polygon_diagonalExists, glm::diagonalExists, gLuaPolygon<>, gLuaTrait<size_t>, gLuaTrait<size_t>)
TRAITS_DEFN(polygon_basisU, glm::basisU, gLuaPolygon<>)
TRAITS_DEFN(polygon_basisV, glm::basisV, gLuaPolygon<>)
TRAITS_DEFN(polygon_mapFrom2D, glm::mapFrom2D, gLuaPolygon<>, gLuaVec2<>)
TRAITS_DEFN(polygon_area, glm::area, gLuaPolygon<>)
TRAITS_DEFN(polygon_perimeter, glm::perimeter, gLuaPolygon<>)
TRAITS_DEFN(polygon_centroid, glm::centroid, gLuaPolygon<>)
TRAITS_DEFN(polygon_isPlanar, glm::isPlanar, gLuaPolygon<>, gLuaEps<>)
TRAITS_DEFN(polygon_isSimple, glm::isSimple, gLuaPolygon<>)
TRAITS_DEFN(polygon_isNull, glm::isNull, gLuaPolygon<>)
TRAITS_DEFN(polygon_isfinite, glm::isfinite, gLuaPolygon<>)
TRAITS_DEFN(polygon_isDegenerate, glm::isDegenerate, gLuaPolygon<>, gLuaEps<>)
TRAITS_DEFN(polygon_isConvex, glm::isConvex, gLuaPolygon<>)
TRAITS_DEFN(polygon_planeCCW, glm::planeCCW, gLuaPolygon<>)
TRAITS_DEFN(polygon_normalCCW, glm::normalCCW, gLuaPolygon<>)
TRAITS_DEFN(polygon_planeCW, glm::planeCW, gLuaPolygon<>)
TRAITS_DEFN(polygon_normalCW, glm::normalCW, gLuaPolygon<>)
TRAITS_DEFN(polygon_pointOnEdge, glm::pointOnEdge, gLuaPolygon<>, gLuaFloat)
TRAITS_DEFN(polygon_edgeNormal, glm::edgeNormal, gLuaPolygon<>, gLuaTrait<size_t>)
TRAITS_DEFN(polygon_edgePlane, glm::edgePlane, gLuaPolygon<>, gLuaTrait<size_t>)
TRAITS_DEFN(polygon_containsSegment2D, glm::contains2D, gLuaPolygon<>, gLuaSegment<>)
TRAITS_DEFN(polygon_contains, glm::contains, gLuaPolygon<>, gLuaVec3<>, gLuaEps<>)
TRAITS_DEFN(polygon_containsAbove, glm::containsAbove, gLuaPolygon<>, gLuaVec3<>, gLuaEps<>)
TRAITS_DEFN(polygon_containsBelow, glm::containsBelow, gLuaPolygon<>, gLuaVec3<>, gLuaEps<>)
TRAITS_DEFN(polygon_containsPolygon, glm::contains, gLuaPolygon<>, gLuaPolygon<>, gLuaEps<>)
TRAITS_DEFN(polygon_containsSegment, glm::contains, gLuaPolygon<>, gLuaSegment<>, gLuaEps<>)
TRAITS_DEFN(polygon_minimalEnclosingAABB, glm::minimalEnclosingAABB, gLuaPolygon<>)
TRAITS_DEFN(polygon_intersectsSegment2D, glm::intersects2D, gLuaPolygon<>, gLuaSegment<>)
TRAITS_DEFN(polygon_intersectsLine, glm::intersects, gLuaPolygon<>, gLuaLine<>)
TRAITS_DEFN(polygon_intersectsRay, glm::intersects, gLuaPolygon<>, gLuaRay<>)
TRAITS_DEFN(polygon_intersectsSegment, glm::intersects, gLuaPolygon<>, gLuaSegment<>)
TRAITS_DEFN(polygon_intersectsPlane, glm::intersects, gLuaPolygon<>, gLuaPlane<>)
TRAITS_LAYOUT_DEFN(polygon_projectToAxis, glm::projectToAxis, GEOM_PROJECTION, gLuaPolygon<>, gLuaVec3<>)

GLM_BINDING_QUALIFIER(polygon_mapTo2D) {
  GLM_BINDING_BEGIN
  if (gLuaTrait<size_t>::Is(LB, LB.idx + 1))
    TRAITS_FUNC(LB, glm::mapTo2D, gLuaPolygon<>, gLuaTrait<size_t>);
  TRAITS_FUNC(LB, glm::mapTo2D, gLuaPolygon<>, gLuaVec3<>);
  GLM_BINDING_END
}

GLM_BINDING_QUALIFIER(polygon_extremePoint) {
  GLM_BINDING_BEGIN
  gLuaVec3<>::value_type distance(0);
  const gLuaPolygon<>::type polygon = gLuaPolygon<>::Next(LB);
  const gLuaVec3<>::type direction = gLuaVec3<>::Next(LB);
  const gLuaVec3<>::type point = glm::extremePoint(polygon, direction, distance);
  TRAITS_PUSH(LB, point, distance);
  GLM_BINDING_END
}

/* Polygon Metamethods */

/// <summary>
/// Create a new polygon from an array of points.
/// </summary>
GLM_BINDING_QUALIFIER(polygon_new) {
  GLM_BINDING_BEGIN
  const int top = LB.top();
  if (!lua_isnoneornil(LB.L, LB.idx) && !lua_istable(LB.L, LB.idx))
    return luaL_argerror(LB.L, LB.idx, lua_typename(LB.L, LUA_TTABLE));

  // Create a new polygon userdata.
  void *ptr = lua_newuserdatauv(LB.L, sizeof(gLuaPolygon<>::type), 0);  // [..., poly]
  gLuaPolygon<>::type *polygon = reinterpret_cast<gLuaPolygon<>::type *>(ptr);
  polygon->stack_idx = -1;
  polygon->p = GLM_NULLPTR;

  // Setup metatable.
  if (luaL_getmetatable(LB.L, LUA_GLM_POLYGON_META) == LUA_TTABLE) { // [..., poly, meta]
    lua_setmetatable(LB.L, -2);  // [..., poly]
    LuaCrtAllocator<gLuaPolygon<>::Point::type> allocator(LB.L);

    // Create a std::vector backed by the Lua allocator.
    using PolyList = glm::List<gLuaPolygon<>::Point::type>;
    PolyList *list = static_cast<PolyList*>(allocator.realloc(GLM_NULLPTR, 0, sizeof(PolyList)));

    // Populate the polygon with an array of coordinates, if one exists.
    try {
      polygon->p = ::new(list) PolyList();

      if (top >= 1 && lua_istable(LB.L, LB.idx)) {
        const auto e = glmLuaArray::end<gLuaVec3<>>(LB.L, LB.idx);
        for (auto b = glmLuaArray::begin<gLuaVec3<>>(LB.L, LB.idx); b != e; ++b) {
          polygon->p->push_back(*b);
        }
      }
    }
    catch (...) {
      lua_pop(L, 1);
      return luaL_error(L, "unknown polygon error");
    }
    return 1;
  }

  lua_pop(L, 2);
  return luaL_error(L, "invalid polygon metatable");
  GLM_BINDING_END
}

GLM_BINDING_QUALIFIER(polygon_to_string) {
  gLuaPolygon<>::type *ud = reinterpret_cast<gLuaPolygon<>::type *>(luaL_checkudata(L, 1, LUA_GLM_POLYGON_META));
  if (ud->p != GLM_NULLPTR) {
    lua_pushfstring(L, "Polygon<%I>", ud->p->size());
    return 1;
  }

  return luaL_argerror(L, 1, "Polygon");
}

/// <summary>
/// Garbage collect an allocated polygon userdata.
/// </summary>
GLM_BINDING_QUALIFIER(polygon__gc) {
  gLuaPolygon<>::type *ud = reinterpret_cast<gLuaPolygon<>::type *>(luaL_checkudata(L, 1, LUA_GLM_POLYGON_META));
  if (ud->p != GLM_NULLPTR) {
    LuaCrtAllocator<void> allocator(L);
    ud->p->~vector();  // Invoke destructor.
    allocator.realloc(ud->p, sizeof(glm::List<gLuaPolygon<>::Point::type>), 0);  // Free allocation
    ud->p = GLM_NULLPTR;
  }
  return 0;
}

/// <summary>
/// The number of points within a polygon.
/// </summary>
TRAITS_DEFN(polygon__len, glm::length, gLuaPolygon<>)

/// <summary>
/// Create an array of points.
/// </summary>
GLM_BINDING_QUALIFIER(polygon__call) {
  GLM_BINDING_BEGIN
  const gLuaPolygon<>::type poly = gLuaPolygon<>::Next(LB);
  lua_createtable(LB.L, static_cast<int>(poly.size()), 0);
  for (size_t i = 0; i < poly.size(); ++i) {
    if (gLuaBase::Push(LB, poly[i]) != 1)
      return luaL_error(LB.L, GLM_INVALID_VECTOR_STRUCTURE);
    lua_rawseti(LB.L, -2, i_luaint(i) + 1);
  }
  return 1;
  GLM_BINDING_END
}

GLM_BINDING_QUALIFIER(polygon__index) {
  GLM_BINDING_BEGIN
  const gLuaPolygon<>::type poly = gLuaPolygon<>::Next(LB);
  if (gLuaTrait<size_t>::Is(LB, LB.idx)) {
    const gLuaTrait<size_t>::type index = gLuaTrait<size_t>::Next(LB);
    if (1 <= index && index <= poly.size())
      return gLuaBase::Push(LB, poly[index - 1]);
    return gLuaBase::Push(LB);  // nil
  }
  // Attempt to fetch the contents from the polygon library.
  else if (luaL_getmetatable(LB.L, LUA_GLM_POLYGON_META) == LUA_TTABLE) {
    lua_pushvalue(LB.L, LB.idx);
    lua_rawget(LB.L, -2);
    return 1;  // Have Lua remove the polygon metatable from the stack.
  }

  lua_pop(LB.L, 1);  // Polygon metatable.
  return 0;
  GLM_BINDING_END
}

GLM_BINDING_QUALIFIER(polygon__newindex) {
  GLM_BINDING_BEGIN
  gLuaPolygon<>::type poly = gLuaPolygon<>::Next(LB);
  if (poly.p != GLM_NULLPTR) {
    const size_t index = gLuaTrait<size_t>::Next(LB);
    const gLuaVec3<>::type value = gLuaVec3<>::Next(LB);
    if (index >= 1 && index <= poly.size())
      poly[index - 1] = value;
    else if (index == poly.size() + 1)
      poly.p->push_back(value);
    else
      return luaL_error(LB.L, "Invalid %s index", gLuaPolygon<>::Label());
  }
  return 0;
  GLM_BINDING_END
}

extern "C" {
  /// <summary>
  /// Iterator function for polygon verticies.
  /// </summary>
  static int polygon__iterator(lua_State *L) {
    GLM_BINDING_BEGIN
    if (!gLuaPolygon<>::Is(LB, LB.idx))
      return luaL_argerror(LB.L, LB.idx, gLuaPolygon<>::Label());
    lua_settop(LB.L, LB.idx + 1);  // create a 2nd argument if there isn't one

    const gLuaPolygon<>::type poly = gLuaPolygon<>::Next(LB);  // Polygon
    if (gLuaTrait<size_t>::Is(LB, LB.idx)) {  // Index
      const gLuaTrait<size_t>::type key = gLuaTrait<size_t>::Next(LB);
      if (key >= 1 && key < poly.size())
        TRAITS_PUSH(LB, key + 1, poly[key]);
      return gLuaBase::Push(LB);
    }
    else if (lua_isnoneornil(LB.L, LB.idx) && poly.size() > 0)  // First index
      TRAITS_PUSH(LB, size_t(1), poly[0]);
    else
      return gLuaBase::Push(LB);  // Nothing to iterate.
    GLM_BINDING_END
  };
}

GLM_BINDING_QUALIFIER(polygon__pairs) {
  lua_pushcfunction(L, polygon__iterator);  // will return generator,
  lua_pushvalue(L, 1);  // state,
  lua_pushnil(L);  // and initial value
  return 3;
}

static const luaL_Reg luaglm_polylib[] = {
  { "__gc", glm_polygon__gc },
  { "__index", glm_polygon__index },  // Array access
  { "__newindex", glm_polygon__newindex },  // Only allow append
  { "__len", glm_polygon__len },  // # of Points
  { "__call", glm_polygon__call },  // Generate a table.
  { "__pairs", glm_polygon__pairs },
  { "__unm", glm_polygon_operator_negate },  // Negate all points.
  { "__eq", glm_polygon_operator_equals },
  { "__add", glm_polygon_operator_add },
  { "__sub", glm_polygon_operator_sub },
  { "__mul", glm_polygon_operator_mul },
  { "__tostring", glm_polygon_to_string },
  { "new", glm_polygon_new },
  { "operator_negate", glm_polygon_operator_negate },
  { "operator_equals", glm_polygon_operator_equals },
  { "operator_add", glm_polygon_operator_add },
  { "operator_sub", glm_polygon_operator_sub },
  { "operator_mul", glm_polygon_operator_mul },
  { "edge", glm_polygon_edge },
  { "edge2d", glm_polygon_edge2d },
  { "diagonal", glm_polygon_diagonal },
  { "diagonalExists", glm_polygon_diagonalExists },
  { "basisU", glm_polygon_basisU },
  { "basisV", glm_polygon_basisV },
  { "mapTo2D", glm_polygon_mapTo2D },
  { "mapFrom2D", glm_polygon_mapFrom2D },
  { "area", glm_polygon_area },
  { "perimeter", glm_polygon_perimeter },
  { "centroid", glm_polygon_centroid },
  { "isPlanar", glm_polygon_isPlanar },
  { "isSimple", glm_polygon_isSimple },
  { "isNull", glm_polygon_isNull },
  { "isfinite", glm_polygon_isfinite },
  { "isDegenerate", glm_polygon_isDegenerate },
  { "isConvex", glm_polygon_isConvex },
  { "extremePoint", glm_polygon_extremePoint },
  { "projectToAxis", glm_polygon_projectToAxis },
  { "planeCCW", glm_polygon_planeCCW },
  { "normalCCW", glm_polygon_normalCCW },
  { "planeCW", glm_polygon_planeCW },
  { "normalCW", glm_polygon_normalCW },
  { "pointOnEdge", glm_polygon_pointOnEdge },
  { "edgeNormal", glm_polygon_edgeNormal },
  { "edgePlane", glm_polygon_edgePlane },
  { "containsSegment2D", glm_polygon_containsSegment2D },
  { "contains", glm_polygon_contains },
  { "containsAbove", glm_polygon_containsAbove },
  { "containsBelow", glm_polygon_containsBelow },
  { "containsPolygon", glm_polygon_containsPolygon },
  { "containsSegment", glm_polygon_containsSegment },
  { "minimalEnclosingAABB", glm_polygon_minimalEnclosingAABB },
  { "intersectsSegment2D", glm_polygon_intersectsSegment2D },
  { "intersectsLine", glm_polygon_intersectsLine },
  { "intersectsRay", glm_polygon_intersectsRay },
  { "intersectsSegment", glm_polygon_intersectsSegment },
  { "intersectsPlane", glm_polygon_intersectsPlane },
  { GLM_NULLPTR, GLM_NULLPTR },
};

/* }================================================================== */

#endif
#endif
