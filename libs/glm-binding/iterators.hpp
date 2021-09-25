/*
** A set of iterator definitions for processing collections of traits without
** needing to allocate additional memory.
**
** An iterator dependent implementations should avoid interoperability issues
** for strictly-C compiled versions of Lua.
*/
#ifndef __BINDING_ITERATORS_HPP__
#define __BINDING_ITERATORS_HPP__

#include <iterator>
#include <functional>
#include <lua.hpp>

#include "bindings.hpp"

/// <summary>
/// Enum of different iterator types. This is more efficient than if this was calculated at runtime, at the cost of needing to update this to add new iterators.
/// <summary>
enum struct glmIteratorType {
  Stack,
  Array
};

/// <summary>
/// Base Iterator Interface
/// </summary>
template<typename Trait>
class glmLuaIterator : public gLuaBase {
protected:
  virtual bool isEqual(const glmLuaIterator<Trait> &obj) const = 0;
  virtual glmIteratorType getId() const = 0; // This is in the vtable so we don't add any more fields.

public:
  glmLuaIterator(lua_State *L_, int idx_ = 1)
    : gLuaBase(L_, idx_) {
    gLuaBase::top();  // Cache lua_gettop
  }

  virtual ~glmLuaIterator() = default;
  glmLuaIterator(const glmLuaIterator &) = default;
  glmLuaIterator(glmLuaIterator &&) = default;
  glmLuaIterator &operator=(const glmLuaIterator &) = default;
  glmLuaIterator &operator=(glmLuaIterator &&) = default;

  template<typename S>
  friend bool operator==(const glmLuaIterator<S> &, const glmLuaIterator<S> &);

  template<typename S>
  friend bool operator!=(const glmLuaIterator<S> &, const glmLuaIterator<S> &);

  // Iterator Traits
  using iterator_category = std::forward_iterator_tag;
  using value_type = typename Trait::type;
  using difference_type = ptrdiff_t;
  using pointer = typename Trait::type *;
  using reference = typename Trait::type &;
};

template<typename Trait>
bool operator==(const glmLuaIterator<Trait> &lhs, const glmLuaIterator<Trait> &rhs) {
  return lhs.getId() == rhs.getId() && lhs.isEqual(rhs);
}

template<typename Trait>
bool operator!=(const glmLuaIterator<Trait> &lhs, const glmLuaIterator<Trait> &rhs) {
  return lhs.getId() != rhs.getId() || !lhs.isEqual(rhs);
}

/// <summary>
/// Trait defined over elements of a Lua stack.
/// </summary>
class glmLuaStack {
  public:
  template<typename Tr>
  class Iterator : public glmLuaIterator<Tr> {
    friend class glmLuaStack;

private:
    /// <summary>
    /// Within stack bounds.
    /// </summary>
    bool valid() const {
      return gLuaBase::idx >= 1 && gLuaBase::idx <= lua_gettop(gLuaBase::L);
    }

public:
    Iterator(lua_State *L_, int idx_ = 1)
      : glmLuaIterator<Tr>(L_, idx_) {
    }

    /// <summary>
    /// Create a glm value starting at the current Lua stack index
    /// </summary>
    typename Tr::type operator*() const {
      typename Tr::type value = Tr::zero();
      if (!gLuaBase::Pull(*this, gLuaBase::idx, value))
        luaL_error(gLuaBase::L, "Invalid %s structure", Tr::Label());

      return value;
    }

    /// <summary>
    /// Iterate to the next glm value on the Lua stack. At one point this could
    /// have possibly corresponded to multiple stack values. However, the
    /// current implementation is one-to-one (i.e., each GLM structure is
    /// equivalent to one Lua stack value).
    /// </summary>
    const Iterator<Tr> &operator++() {
      gLuaBase::idx++;
      return *this;
    }

    /// <summary>
    /// @HACK
    /// </summary>
    const Iterator<Tr> &operator++(int) {
      gLuaBase::idx++;
      return *this;
    }

    /// <summary>
    /// </summary>
    bool isEqual(const glmLuaIterator<Tr> &obj) const override {
      const Iterator<Tr> &other = static_cast<const Iterator<Tr> &>(obj);
      return (gLuaBase::idx == other.idx) || (!valid() && !other.valid());
    }

    /// <summary>
    /// </summary>
    glmIteratorType getId() const override {
      return glmIteratorType::Stack;
    }
  };

  /// <summary>
  /// Begin stack iteration, starting at "idx"
  /// </summary>
  template<typename Type>
  static Iterator<Type> begin(lua_State *L, int idx = 1) {
    return Iterator<Type>(L, idx);
  }

  /// <summary>
  /// End stack iteration, often defaulting to 1 + lua_gettop(L), i.e., the
  /// first index out of bounds.
  /// </summary>
  template<typename Trait>
  static Iterator<Trait> end(lua_State *L, int idx) {
    return Iterator<Trait>(L, idx);
  }

  template<typename Trait>
  static Iterator<Trait> end(lua_State *L) {
    return glmLuaStack::end<Trait>(L, 1 + lua_gettop(L));
  }

  /// <summary>
  /// Sugar forEach helper.
  /// </summary>
  template<typename Trait>
  static void forEach(lua_State *L, int idx, std::function<void(const typename Trait::type &)> func) {
    auto e = glmLuaStack::end<Trait>(L);
    for (auto b = glmLuaStack::begin<Trait>(L, idx); b != e; ++b)
      func(*b);
  }
};

/// <summary>
/// Traits defined over elements of a Lua table.
/// </summary>
class glmLuaArray {
  public:
  template<typename Tr>
  class Iterator : public glmLuaIterator<Tr> {
    friend class glmLuaArray;

private:
    size_t arrayIdx;  // Current array index.
    size_t arraySize;  // (Precomputed) array size.

    /// <summary>
    /// Within array bounds & is a valid trait.
    /// </summary>
    GLM_INLINE bool valid() const {
      return arrayIdx >= 1 && arrayIdx <= arraySize;
    }

public:
    Iterator(lua_State *L_, int idx_, size_t arrayIdx_, size_t arraySize_)
      : glmLuaIterator<Tr>(L_, idx_), arrayIdx(arrayIdx_), arraySize(arraySize_) {
    }

    Iterator(lua_State *L_, int idx_, size_t _arraySize = 1)
      : glmLuaIterator<Tr>(L_, idx_), arrayIdx(_arraySize) {
      arraySize = lua_istable(L_, idx_) ? static_cast<size_t>(lua_rawlen(L_, idx_)) : 0;
    }

    /// <summary>
    /// Goto the next element in the array.
    /// </summary>
    const Iterator<Tr> &operator++() {
      arrayIdx++;
      return *this;
    }

    /// <summary>
    /// @HACK
    /// </summary>
    const Iterator<Tr> &operator++(int) {
      arrayIdx++;
      return *this;
    }

    bool isEqual(const glmLuaIterator<Tr> &obj) const override {
      const Iterator<Tr> &other = static_cast<const Iterator<Tr> &>(obj);
      return (arrayIdx == other.arrayIdx) || (!valid() && !other.valid());
    }

    /// <summary>
    /// </summary>
    glmIteratorType getId() const override {
      return glmIteratorType::Array;
    }

    typename Tr::type operator*() const {
      typename Tr::type value = Tr::zero();

      // Fetch the object within the array that *should* correspond to the trait.
      lua_rawgeti(gLuaBase::L, gLuaBase::idx, i_luaint(arrayIdx));
      const int top = lua_gettop(gLuaBase::L);  // gLuaBase uses absolute values.

      // Parse the trait given the relative stack (starting) index.
      gLuaBase LB(gLuaBase::L, gLuaBase::idx);
      if (!Tr::Is(LB, top) || !gLuaBase::Pull(LB, top, value)) { /* noret */
        lua_pop(gLuaBase::L, 1);
        luaL_error(gLuaBase::L, "Invalid table index: %d for %s", static_cast<int>(arrayIdx), Tr::Label());

        return typename Tr::type(0);  // quash compiler warnings, luaL_error is noret.
      }

      lua_pop(gLuaBase::L, 1);
      return value;
    }
  };

  /// <summary>
  /// Create an iterator, referencing an array at "t_idx", starting at the
  /// specified array index "a_idx".
  /// </summary>
  template<typename Trait>
  static Iterator<Trait> begin(lua_State *L, int t_idx = 1, size_t a_idx = 1) {
    return Iterator<Trait>(L, t_idx, a_idx);
  }

  template<typename Trait>
  static Iterator<Trait> end(lua_State *L, int t_idx = 1, size_t a_endidx = 0) {
    size_t _tablesize = static_cast<size_t>(lua_rawlen(L, t_idx));
    a_endidx = (a_endidx == 0) ? _tablesize + 1 : a_endidx;
    return Iterator<Trait>(L, t_idx, a_endidx, _tablesize);
  }

  /// <summary>
  /// Sugar forEach helper.
  /// </summary>
  template<typename Trait>
  static void forEach(lua_State *L, int t_idx, std::function<void(const typename Trait::type &)> func) {
    auto e = glmLuaArray::end<Trait>(L, t_idx);
    for (auto b = glmLuaArray::begin<Trait>(L, t_idx); b != e; ++b)
      func(*b);
  }
};

#endif
