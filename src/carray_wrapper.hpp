#pragma once


namespace sk
{
  template <typename T, typename U>
  class carray_wrapper {
  public:

    carray_wrapper() = default;
    carray_wrapper(T* firstWin, U n);
    carray_wrapper(carray_wrapper &&);
    carray_wrapper &operator=(carray_wrapper &&);

    ~carray_wrapper() = default;
    
    T& operator[](U idx);
    const T& operator[](U idx) const;

    T* begin() { return const_cast<T*>(const_cast<const carray_wrapper<T,U>*>(this)->begin()); }
    T* end() { return const_cast<T*>(const_cast<const carray_wrapper<T,U>*>(this)->end()); }

    const T* begin() const { return m_data; }
    const T* end() const { return m_data + m_length; }

    [[nodiscard]] T* data() { return m_data; }
    [[nodiscard]] const T* data() const { return const_cast<T*>(const_cast<const carray_wrapper<T,U>*>(this)->begin()); }
    [[nodiscard]] U length() const{ return m_length; }

  private:

    T* m_data {};
    U m_length {};
  };


  template <typename T, typename U>
  carray_wrapper<T,U>::carray_wrapper(T* ptr, U n)
    :m_data   { ptr }
    ,m_length { n }
  {}


}
