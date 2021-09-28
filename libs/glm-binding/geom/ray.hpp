/// <summary>
/// See Copyright Notice in setup.hpp
/// </summary>
#ifndef __EXT_GEOM_RAY_HPP__
#define __EXT_GEOM_RAY_HPP__

#include "setup.hpp"
#include "line.hpp"
#include "linesegment.hpp"
#include "triangle.hpp"

namespace glm {
  /// <summary>
  /// A line in 3D spaced defined by an origin pointer and a direction,
  /// extending to infinity in one direction.
  /// </summary>
  template<length_t L, typename T, qualifier Q>
  struct Ray {
    using Point = vec<L, T, Q>;

    Point pos;  // Specifies the origin of this line.
    Point dir;  // The normalized direction vector of this ray.

    Ray() = default;

    Ray(T scalar)
      : pos(scalar), dir(scalar) {
    }

    Ray(const vec<L, T, Q> &position, const vec<L, T, Q> &direction)
      : pos(position), dir(normalize(direction)) {
    }

    Ray(const Line<L, T, Q> &line)
      : pos(line.pos), dir(line.dir) {
    }

    Ray(const Ray<L, T, Q> &ray)
      : pos(ray.pos), dir(ray.dir) {
    }

    Ray<L, T, Q> &operator=(const Ray<L, T, Q> &ray) {
      pos = ray.pos;
      dir = ray.dir;
      return *this;
    }
  };

  template<length_t L, typename T, qualifier Q>
  GLM_GEOM_QUALIFIER Line<L, T, Q> toLine(const Ray<L, T, Q> &ray) {
    return Line<L, T, Q>(ray.pos, ray.dir);
  }

  template<length_t L, typename T, qualifier Q>
  static Ray<L, T, Q> operator-(const Ray<L, T, Q> &ray) {
    return Ray<L, T, Q>(ray.pos, -ray.dir);
  }

  template<length_t L, typename T, qualifier Q>
  static bool operator==(const Ray<L, T, Q> &r1, const Ray<L, T, Q> &r2) {
    return r1.pos == r2.pos && r1.dir == r2.dir;
  }

  template<length_t L, typename T, qualifier Q>
  static Ray<L, T, Q> operator+(const Ray<L, T, Q> &ray, const vec<L, T, Q> &offset) {
    return Ray<L, T, Q>(ray.pos + offset, ray.dir);
  }

  template<length_t L, typename T, qualifier Q>
  static Ray<L, T, Q> operator-(const Ray<L, T, Q> &ray, const vec<L, T, Q> &offset) {
    return Ray<L, T, Q>(ray.pos - offset, ray.dir);
  }

  template<typename T, qualifier Q>
  static Ray<3, T, Q> operator*(const mat<3, 3, T, Q> &m, const Ray<3, T, Q> &ray) {
    GLM_GEOM_ASSUME(isNormalized(ray.dir, epsilon<T>()), ray);
    return Ray<3, T, Q>(m * ray.pos, m * ray.dir);
  }

  template<typename T, qualifier Q>
  static Ray<3, T, Q> operator*(const mat<3, 4, T, Q> &m, const Ray<3, T, Q> &ray) {
    GLM_GEOM_ASSUME(isNormalized(ray.dir, epsilon<T>()), ray);
    return Ray<3, T, Q>(m * ray.pos, m * ray.dir);
  }

  template<typename T, qualifier Q>
  static Ray<3, T, Q> operator*(const mat<4, 3, T, Q> &m, const Ray<3, T, Q> &ray) {
    GLM_GEOM_ASSUME(isNormalized(ray.dir, epsilon<T>()), ray);
    return Ray<3, T, Q>(transformPos(m, ray.pos), transformDir(m, ray.dir));
  }

  template<typename T, qualifier Q>
  static Ray<3, T, Q> operator*(const mat<4, 4, T, Q> &m, const Ray<3, T, Q> &ray) {
    GLM_GEOM_ASSUME(isNormalized(ray.dir, epsilon<T>()), ray);
    return Ray<3, T, Q>(transformPos(m, ray.pos), transformDir(m, ray.dir));
  }

  template<typename T, qualifier Q>
  static Ray<3, T, Q> operator*(const qua<T, Q> &q, const Ray<3, T, Q> &ray) {
    return Ray<3, T, Q>(q * ray.pos, q * ray.dir);
  }

  template<length_t L, typename T, qualifier Q>
  GLM_GEOM_QUALIFIER GLM_CONSTEXPR bool equal(Ray<L, T, Q> const &x, Ray<L, T, Q> const &y, T eps = epsilon<T>()) {
    return all_equal(x.pos, y.pos, eps) && all_equal(x.dir, y.dir, eps);
  }

  template<length_t L, typename T, qualifier Q>
  GLM_GEOM_QUALIFIER GLM_CONSTEXPR bool equal(Ray<L, T, Q> const &x, Ray<L, T, Q> const &y, vec<L, T, Q> const &eps) {
    return all_equal(x.pos, y.pos, eps) && all_equal(x.dir, y.dir, eps);
  }

  template<length_t L, typename T, qualifier Q>
  GLM_GEOM_QUALIFIER GLM_CONSTEXPR bool equal(Ray<L, T, Q> const &x, Ray<L, T, Q> const &y, int MaxULPs) {
    return all_equal(x.pos, y.pos, MaxULPs) && all_equal(x.dir, y.dir, MaxULPs);
  }

  template<length_t L, typename T, qualifier Q>
  GLM_GEOM_QUALIFIER GLM_CONSTEXPR bool equal(Ray<L, T, Q> const &x, Ray<L, T, Q> const &y, vec<L, int, Q> const &MaxULPs) {
    return all_equal(x.pos, y.pos, MaxULPs) && all_equal(x.dir, y.dir, MaxULPs);
  }

  template<length_t L, typename T, qualifier Q>
  GLM_GEOM_QUALIFIER GLM_CONSTEXPR bool notEqual(Ray<L, T, Q> const &x, Ray<L, T, Q> const &y, T eps = epsilon<T>()) {
    return any_notequal(x.pos, y.pos, eps) || any_notequal(x.dir, y.dir, eps);
  }

  template<length_t L, typename T, qualifier Q>
  GLM_GEOM_QUALIFIER GLM_CONSTEXPR bool notEqual(Ray<L, T, Q> const &x, Ray<L, T, Q> const &y, vec<L, T, Q> const &eps) {
    return any_notequal(x.pos, y.pos, eps) || any_notequal(x.dir, y.dir, eps);
  }

  template<length_t L, typename T, qualifier Q>
  GLM_GEOM_QUALIFIER GLM_CONSTEXPR bool notEqual(Ray<L, T, Q> const &x, Ray<L, T, Q> const &y, int MaxULPs) {
    return any_notequal(x.pos, y.pos, MaxULPs) || any_notequal(x.dir, y.dir, MaxULPs);
  }

  template<length_t L, typename T, qualifier Q>
  GLM_GEOM_QUALIFIER GLM_CONSTEXPR bool notEqual(Ray<L, T, Q> const &x, Ray<L, T, Q> const &y, vec<L, int, Q> const &MaxULPs) {
    return any_notequal(x.pos, y.pos, MaxULPs) || any_notequal(x.dir, y.dir, MaxULPs);
  }

  /// <summary>
  /// Tests if any component of the ray is infinite.
  /// </summary>
  template<length_t L, typename T, qualifier Q>
  GLM_GEOM_QUALIFIER bool isinf(const Ray<L, T, Q> &line) {
    return any_isinf(line.pos) || any_isinf(line.dir);
  }

  template<length_t L, typename T, qualifier Q>
  GLM_GEOM_QUALIFIER bool isnan(const Ray<L, T, Q> &line) {
    return any_isnan(line.pos) || any_isnan(line.dir);
  }

  template<length_t L, typename T, qualifier Q>
  GLM_GEOM_QUALIFIER bool isfinite(const Ray<L, T, Q> &line) {
    return all(isfinite(line.pos)) && all(isfinite(line.dir));
  }

  /// <summary>
  /// Get a point along the ray at a given distance (parametric point).
  ///
  /// Passing negative values to this function treats the ray as if it were a
  /// line.
  /// </summary>
  template<length_t L, typename T, qualifier Q>
  GLM_GEOM_QUALIFIER vec<L, T, Q> getPoint(const Ray<L, T, Q> &ray, T d) {
    GLM_GEOM_ASSUME(isNormalized(ray.dir, epsilon<T>()), ray.pos);
    return ray.pos + d * ray.dir;
  }

  // Computes the closest point on this ray to the given object.

  template<length_t L, typename T, qualifier Q>
  GLM_GEOM_QUALIFIER vec<L, T, Q> closestPoint(const Ray<L, T, Q> &ray, const vec<L, T, Q> &targetPoint, T &d) {
    d = max(T(0), dot(targetPoint - ray.pos, ray.dir));
    return getPoint(ray, d);
  }

  template<length_t L, typename T, qualifier Q>
  GLM_GEOM_QUALIFIER_NOINLINE vec<L, T, Q> closestPoint(const Ray<L, T, Q> &ray, const Line<L, T, Q> &other, T &d, T &d2) {
    closestPointLineLine(ray.pos, ray.dir, other.pos, other.dir, d, d2);
    if (d < T(0)) {
      d = T(0);
      closestPoint(other, ray.pos, d2);
      return ray.pos;
    }
    return getPoint(ray, d);
  }

  template<length_t L, typename T, qualifier Q>
  GLM_GEOM_QUALIFIER_NOINLINE vec<L, T, Q> closestPoint(const Ray<L, T, Q> &ray, const Ray<L, T, Q> &other, T &d, T &d2) {
    closestPointLineLine(ray.pos, ray.dir, other.pos, other.dir, d, d2);
    if (d < T(0) && d2 < T(0)) {
      const vec<L, T, Q> pt = closestPoint(ray, other.pos, d);
      const vec<L, T, Q> pt2 = closestPoint(other, ray.pos, d2);
      if (distance2(pt, other.pos) <= distance2(pt2, ray.pos)) {
        d2 = T(0);
        return pt;
      }
      else {
        d = T(0);
        return ray.pos;
      }
    }
    else if (d < T(0)) {
      closestPoint(other, ray.pos, d2);
      d = T(0);
      d2 = max(T(0), d2);
      return ray.pos;
    }
    else if (d2 < T(0)) {
      const vec<L, T, Q> pt = closestPoint(ray, other.pos, d);
      d = max(T(0), d);
      d2 = T(0);
      return pt;
    }
    else {
      return getPoint(ray, d);
    }
  }

  template<length_t L, typename T, qualifier Q>
  GLM_GEOM_QUALIFIER_NOINLINE vec<L, T, Q> closestPoint(const Ray<L, T, Q> &ray, const LineSegment<L, T, Q> &other, T &d, T &d2) {
    closestPointLineLine(ray.pos, ray.dir, other.a, other.dir2(), d, d2);
    if (d < T(0)) {
      d = T(0);
      if (d2 >= T(0) && d2 <= T(1)) {
        closestPoint(other, ray.pos, d2);
        return ray.pos;
      }
      else {
        const T t2 = (d2 < T(0)) ? T(0) : T(1);
        const vec<L, T, Q> p = (d2 < T(0)) ? other.a : other.b;
        const vec<L, T, Q> pt = closestPoint(ray, p, d);
        const vec<L, T, Q> pt2 = closestPoint(other, ray.pos, d2);
        if (distance2(pt, p) <= distance2(pt2, ray.pos)) {
          d2 = t2;
          return pt;
        }
        else {
          d = T(0);
          return ray.pos;
        }
      }
    }
    else if (d2 < T(0)) {
      d2 = T(0);
      return closestPoint(ray, other.a, d);
    }
    else if (d2 > T(1)) {
      d2 = T(1);
      return closestPoint(ray, other.b, d);
    }
    return getPoint(ray, d);
  }

  template<length_t L, typename T, qualifier Q>
  GLM_GEOM_QUALIFIER vec<L, T, Q> closestPoint(const Ray<L, T, Q> &ray, const vec<L, T, Q> &targetPoint) {
    T d(0);
    return closestPoint(ray, targetPoint, d);
  }

  template<length_t L, typename T, qualifier Q>
  GLM_GEOM_QUALIFIER vec<L, T, Q> closestPoint(const Ray<L, T, Q> &ray, const Line<L, T, Q> &other) {
    T d(0), d2(0);
    return closestPoint(ray, other, d, d2);
  }

  template<length_t L, typename T, qualifier Q>
  GLM_GEOM_QUALIFIER vec<L, T, Q> closestPoint(const Ray<L, T, Q> &ray, const LineSegment<L, T, Q> &segment) {
    T d(0), d2(0);
    return closestPoint(ray, segment, d, d2);
  }

  template<length_t L, typename T, qualifier Q>
  GLM_GEOM_QUALIFIER vec<L, T, Q> closestPoint(const Ray<L, T, Q> &ray, const Ray<L, T, Q> &other) {
    T d(0), d2(0);
    return closestPoint(ray, other, d, d2);
  }

  // Tests if the given object is fully contained on the ray.

  template<length_t L, typename T, qualifier Q>
  GLM_GEOM_QUALIFIER bool contains(const Ray<L, T, Q> &ray, const vec<L, T, Q> &point, T distanceThreshold) {
    T ignore(0);
    return distance2(closestPoint(ray, point, ignore), point) <= distanceThreshold;
  }

  template<length_t L, typename T, qualifier Q>
  GLM_GEOM_QUALIFIER bool contains(const Ray<L, T, Q> &ray, const LineSegment<L, T, Q> &lineSegment, T distanceThreshold) {
    return contains(ray, lineSegment.a, distanceThreshold) && contains(ray, lineSegment.b, distanceThreshold);
  }

  // Computes the distance between the ray and the given object.

  template<length_t L, typename T, qualifier Q>
  GLM_GEOM_QUALIFIER T distance(const Ray<L, T, Q> &ray, const vec<L, T, Q> &point, T &d) {
    return distance(closestPoint(ray, point, d), point);
  }

  template<length_t L, typename T, qualifier Q>
  GLM_GEOM_QUALIFIER T distance(const Ray<L, T, Q> &ray, const Ray<L, T, Q> &other, T &d, T &d2) {
    vec<L, T, Q> c = closestPoint(ray, other, d, d2);
    return distance(c, getPoint(other, d2));
  }

  template<length_t L, typename T, qualifier Q>
  GLM_GEOM_QUALIFIER T distance(const Ray<L, T, Q> &ray, const Line<L, T, Q> &line, T &d, T &d2) {
    vec<L, T, Q> c = closestPoint(ray, line, d, d2);
    return distance(c, getPoint(line, d2));
  }

  template<length_t L, typename T, qualifier Q>
  GLM_GEOM_QUALIFIER T distance(const Ray<L, T, Q> &ray, const LineSegment<L, T, Q> &line, T &d, T &d2) {
    vec<L, T, Q> c = closestPoint(ray, line, d, d2);
    return distance(c, getPoint(line, d2));
  }

  template<length_t L, typename T, qualifier Q>
  GLM_GEOM_QUALIFIER T distance(const Ray<L, T, Q> &ray, const Sphere<L, T, Q> &sphere) {
    return max(T(0), distance(ray, sphere.pos) - sphere.r);
  }

  template<length_t L, typename T, qualifier Q>
  GLM_GEOM_QUALIFIER T distance(const Ray<L, T, Q> &ray, const vec<L, T, Q> &point) {
    T d(0);
    return distance(ray, point, d);
  }

  template<length_t L, typename T, qualifier Q>
  GLM_GEOM_QUALIFIER T distance(const Ray<L, T, Q> &ray, const Ray<L, T, Q> &other) {
    T d(0), d2(0);
    return distance(ray, other, d);
  }

  template<length_t L, typename T, qualifier Q>
  GLM_GEOM_QUALIFIER T distance(const Ray<L, T, Q> &ray, const Line<L, T, Q> &line) {
    T d(0), d2(0);
    return distance(ray, line, d);
  }

  template<length_t L, typename T, qualifier Q>
  GLM_GEOM_QUALIFIER T distance(const Ray<L, T, Q> &ray, const LineSegment<L, T, Q> &line) {
    T d(0), d2(0);
    return distance(ray, line, d);
  }

  /// Tests whether the ray and the given object intersect.

  template<length_t L, typename T, qualifier Q>
  GLM_GEOM_QUALIFIER int intersects(const Ray<L, T, Q> &ray, const Sphere<L, T, Q> &sphere, T &d, T &d2) {
    return intersects(sphere, ray, d, d2);
  }

  template<length_t L, typename T, qualifier Q>
  GLM_GEOM_QUALIFIER bool intersects(const Ray<L, T, Q> &ray, const AABB<L, T, Q> &aabb, T &d, T &d2) {
    return intersects(aabb, ray, d, d2);
  }

  template<length_t L, typename T, qualifier Q>
  GLM_GEOM_QUALIFIER bool intersects(const Ray<L, T, Q> &ray, const Plane<L, T, Q> &plane, T &d) {
    return intersects(plane, ray, d);
  }

  template<length_t L, typename T, qualifier Q>
  GLM_GEOM_QUALIFIER bool intersects(const Ray<L, T, Q> &ray, const Triangle<L, T, Q> &triangle, T &d, T &u, T &v) {
    d = intersectTriangleLine(triangle, toLine(ray), u, v);
    return d >= T(0) && d != std::numeric_limits<T>::infinity();
  }

  template<length_t L, typename T, qualifier Q>
  GLM_GEOM_QUALIFIER bool intersects(const Ray<L, T, Q> &ray, const Sphere<L, T, Q> &sphere) {
    T d(0), d2(0);
    return intersects(ray, sphere, d, d2) > 0;
  }

  template<length_t L, typename T, qualifier Q>
  GLM_GEOM_QUALIFIER bool intersects(const Ray<L, T, Q> &ray, const AABB<L, T, Q> &aabb) {
    T d(0), d2(0);
    return intersects(ray, aabb, d, d2) > 0;
  }

  template<length_t L, typename T, qualifier Q>
  GLM_GEOM_QUALIFIER bool intersects(const Ray<L, T, Q> &ray, const Plane<L, T, Q> &plane) {
    T d(0);
    return intersects(ray, plane, d);
  }

  template<length_t L, typename T, qualifier Q>
  GLM_GEOM_QUALIFIER bool intersects(const Ray<L, T, Q> &ray, const Triangle<L, T, Q> &triangle) {
    T u, v, d(0);
    return intersects(ray, triangle, d, u, v);
  }

  /// <summary>
  /// Convert the ray to a LineSegment.
  /// </summary>
  template<length_t L, typename T, qualifier Q>
  GLM_GEOM_QUALIFIER LineSegment<L, T, Q> toLineSegment(const Ray<L, T, Q> &ray, T d) {
    return LineSegment<L, T, Q>(ray.pos, getPoint(ray, d));
  }

  template<length_t L, typename T, qualifier Q>
  GLM_GEOM_QUALIFIER LineSegment<L, T, Q> toLineSegment(const Ray<L, T, Q> &ray, T dStart, T dEnd) {
    return LineSegment<L, T, Q>(getPoint(ray, dStart), getPoint(ray, dEnd));
  }

  /// <summary>
  /// Project the ray onto the given axis (direction), i.e., collapse the ray
  /// onto an axis.
  /// </summary>
  template<length_t L, typename T, qualifier Q>
  GLM_GEOM_QUALIFIER void projectToAxis(const Ray<L, T, Q> &ray, const vec<L, T, Q> &direction, T &outMin, T &outMax) {
    T d = dot(direction, ray.dir);

    outMin = outMax = dot(direction, ray.pos);
    if (d > epsilon<T>())
      outMax = std::numeric_limits<T>::infinity();
    else if (d < -epsilon<T>())
      outMin = -std::numeric_limits<T>::infinity();
  }

  namespace detail {
    template<glm::length_t L, typename T, qualifier Q>
    struct compute_to_string<Ray<L, T, Q>> {
      GLM_GEOM_QUALIFIER std::string call(const Ray<L, T, Q> &ray) {
        return detail::format("ray(%s, %s)",
          glm::to_string(ray.pos).c_str(),
          glm::to_string(ray.dir).c_str()
        );
      }
    };
  }
}

#endif
