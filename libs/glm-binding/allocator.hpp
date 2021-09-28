/*
** $Id: allocator.hpp $
** An allocator implementation for C++ STL objects.
** See Copyright Notice in lua.h
*/
#ifndef __BINDING_ALLOCATOR_HPP__
#define __BINDING_ALLOCATOR_HPP__

#include <new>
#if defined(LUA_ALLOC_DEBUG)
  #include <iostream>
#endif

#include <lua.hpp>

#if __cplusplus >= 201103L
  #define LUA_ALLOC_NOEXCEPT noexcept
  #define LUA_ALLOC_CONSTEXPR constexpr
#else
  #define LUA_ALLOC_NOEXCEPT
  #define LUA_ALLOC_CONSTEXPR
#endif

/// <summary>
/// A CRuntime allocator that uses lua_Alloc.
/// </summary>
template<class T>
struct LuaCrtAllocator {
  typedef T value_type;
  mutable lua_Alloc l_alloc = nullptr;  // A cache of the memory-allocation function used by Lua states.
  mutable void *l_ud = nullptr;  // An (optional) opaque pointer used by the allocator.

  LuaCrtAllocator() = default;
  LuaCrtAllocator(lua_State *L) {
    l_alloc = lua_getallocf(L, &l_ud);
  }

  template<class U>
  LUA_ALLOC_CONSTEXPR LuaCrtAllocator(const LuaCrtAllocator<U> &o) LUA_ALLOC_NOEXCEPT
    : l_alloc(o.l_alloc), l_ud(o.l_ud) {
  }

  /// <summary>
  /// Update the allocator state and ensure its allocation function and opaque
  /// pointer are still (cache) coherent.
  ///
  /// Caching the lua_Alloc pointer is susceptible to errors: If any external
  /// library, e.g., a memory profiler, replaces the allocator then l_alloc and
  /// l_ud to have the potential to reference invalid data.
  /// </summary>
  LUA_INLINE LuaCrtAllocator &Validate(lua_State *L) const {
    l_alloc = lua_getallocf(L, &l_ud);
    return *const_cast<LuaCrtAllocator *>(this);
  }

  /// <summary>
  /// lua_Alloc: See Lua manual
  /// </summary>
  inline void *realloc(void *block, size_t osize, size_t nsize) {
    if (l_alloc == nullptr)
      throw std::bad_alloc();

    return l_alloc(l_ud, block, osize, nsize);
  }

  T *allocate(std::size_t n) {
    try {
      if (n <= std::numeric_limits<std::size_t>::max() / sizeof(T)) {
        if (auto p = static_cast<T *>(realloc(nullptr, 0, n * sizeof(T)))) {
#if defined(LUA_ALLOC_DEBUG)
          report(p, n);
#endif
          return p;
        }
      }
    }
    catch (...) {
    }

    throw std::bad_alloc();
  }

  void deallocate(T *p, std::size_t n) LUA_ALLOC_NOEXCEPT {
#if defined(LUA_ALLOC_DEBUG)
    report(p, n, 0);
#endif
    realloc(static_cast<void *>(p), n, 0);
  }

private:
#if defined(LUA_ALLOC_DEBUG)
  void report(T *p, std::size_t n, bool alloc = true) const {
    std::cout << (alloc ? "Alloc: " : "Dealloc: ") << sizeof(T) * n
              << " bytes at " << std::hex << std::showbase
              << reinterpret_cast<void *>(p) << std::dec << '\n';
  }
#endif
};

template<class T, class U>
bool operator==(const LuaCrtAllocator<T> &, const LuaCrtAllocator<U> &) {
  return true;
}

template<class T, class U>
bool operator!=(const LuaCrtAllocator<T> &, const LuaCrtAllocator<U> &) {
  return false;
}

#endif
