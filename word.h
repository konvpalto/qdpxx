// -*- C++ -*-
// $Id: word.h,v 1.1 2002-09-12 18:22:16 edwards Exp $
//
// QDP data parallel interface
//

// NOT USING THIS CODE AT THE MOMENT

#include <cmath>

QDP_BEGIN_NAMESPACE(QDP);

//-------------------------------------------------------------------------------------
//! Word class - builtin machine word type
/*! 
 * A template class wrapper for the actual machine primitive.
 * NOTE: with inlining code optimization looks good even with a wrapper
 */
template<class T> class Word
{
public:
  Word() {}
  ~Word() {}

  //! dest = float
  explicit Word(const T& rhs) : F(rhs) {}

//private:
  /*! Hide copy constructor to prevent copying */
  Word(const Word& a): F(a.F) {}

public:
  T& elem() {return F;}
  const T& elem() const {return F;}

private:
  T F;
};


//-------------------------------------------------------------------------------------
//! Real32 word class - builtin machine word type over flow
/*! 
 * A template class wrapper for the actual machine primitive.
 * NOTE: with inlining code optimization looks good even with a wrapper
 */
class Real32 : public Word<float>
{
public:
  Real32() {}
  ~Real32() {}

  //! dest = float
  explicit Real32(const float& rhs)
    {
//      fprintf(stderr,"construct Real32(float): %f\n",rhs);
      elem() = rhs;
    }

  //! dest = int
  /*! Fill with an integer constant. Will be promoted to underlying word type */
  inline
  Real32& operator=(int rhs) 
    {
//      fprintf(stderr,"Real32 = int\n");
      elem() = rhs;
      return *this;
    }

};


//! Real64 word class - wrapper over builtin double type
/*! 
 * A template class wrapper for the actual machine primitive.
 * NOTE: with inlining code optimization looks good even with a wrapper
 */
class Real64 : public Word<double>
{
public:
};


//! Integer32 word class - wrapper over builtin integer type
/*! 
 * A template class wrapper for the actual machine primitive.
 * NOTE: with inlining code optimization looks good even with a wrapper
 */
class Integer32 : public Word<int>
{
public:
  //! dest = int
  /*! Fill with an integer constant. Will be promoted to underlying word type */
  inline
  Integer32& operator=(int rhs) 
    {
//      fprintf(stderr,"Integer32 = int\n");
      elem() = rhs;
      return *this;
    }

};


//! Logical class - wrapper over builtin boolean type
/*! 
 * The boolean class is restricted from the Word class.
 * It supports only a few primitive operations
 */
class Logical
{
public:
  bool& elem() {return d;}
  const bool& elem() const {return d;}

private:
  bool d;
};

//! Ascii output
template<class T>  ostream& operator<<(ostream& s, const Word<T>& d)
{
  return s << d.elem();
}

//! Ascii output
inline ostream& operator<<(ostream& s, const Logical& d)
{
  return s << d.elem();
}


//-----------------------------------------------------------------------------
// Traits classes 
//-----------------------------------------------------------------------------

// Underlying word type
struct WordType<Real32> 
{
  typedef float  Type_t;
};

// Underlying word type
struct WordType<Real64> 
{
  typedef double  Type_t;
};

// Underlying word type
struct WordType<Integer32> 
{
  typedef int  Type_t;
};


template<class Op>
struct BinaryReturn<Real32, Real32, Op> {
  typedef Real32  Type_t;
};

#if 1
struct BinaryReturn<Real32, Real32, OpAssign > {
  typedef Real32& Type_t;
};
#endif


//-----------------------------------------------------------------------------
// Operators
//-----------------------------------------------------------------------------

inline UnaryReturn<Real32, OpUnaryMinus>::Type_t
operator-(const Real32 & l)
{
//  fprintf(stderr,"negate a Real32\n");
  Real32 d;
  d.elem() = -l.elem();

//  fprintf(stderr,"return a -Real32\n");
  return d;
}

inline BinaryReturn<Real32, Real32, OpAdd>::Type_t
operator+(const Real32 & l,const Real32 & r)
{
//  fprintf(stderr,"add a Real32 + Real32\n");
  Real32 d;
  d.elem() = l.elem() + r.elem();

//  fprintf(stderr,"return a Real32 + Real32\n");
  return d;
}

inline BinaryReturn<Real32, Real32, OpAdd>::Type_t
operator-(const Real32 & l,const Real32 & r)
{
//  fprintf(stderr,"add a Real32 - Real32\n");
  Real32 d;
  d.elem() = l.elem() - r.elem();

//  fprintf(stderr,"return a Real32 - Real32\n");
  return d;
}

inline BinaryReturn<Real32, Real32, OpMultiply>::Type_t
operator*(const Real32 & l, const Real32 & r)
{
  Real32 d;
  d.elem() = l.elem() * r.elem();
  return d;
}

QDP_END_NAMESPACE();
