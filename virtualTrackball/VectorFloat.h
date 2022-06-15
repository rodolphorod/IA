#ifndef _VECTORFLOAT_H_
#define _VECTORFLOAT_H_

#include <stdio.h>
#include <assert.h>
#include <math.h>

using namespace std;

/**
 * Created by Luan Sala on 24/07/2015.
 */
class VectorFloat
{
public:
  VectorFloat ();
  VectorFloat (int size);
  VectorFloat (float d0, float d1);
  VectorFloat (float d0, float d1, float d2);
  VectorFloat (VectorFloat &v);

  virtual ~VectorFloat ();

  char  size () const;
  float getX () const;
  float getY () const;
  float getZ () const;

  void set (float x, float y);
  void set (float x, float y, float z);
  void set (VectorFloat v);
  void setX (float x);
  void setY (float y);
  void setZ (float z);

  VectorFloat* add (VectorFloat v2);
  VectorFloat* sub (VectorFloat v2);

  /**
   * Metodo que retorna o modulo (norma) de um vetor.
   *
   * @return O modulo do vetor.
   */
  float norm ();
  void  normalize();

  float        dotProduct (VectorFloat v2);
  VectorFloat* crossProduct (VectorFloat v2);

  inline VectorFloat& operator= (const VectorFloat &v2);

protected:

private:
  float          *data;
  unsigned char   mSize;
};

VectorFloat::~VectorFloat ()
{
  delete data;
}

VectorFloat::VectorFloat ()
{
  mSize = 3;
  data = (float*) malloc(sizeof(float)*mSize);
}

VectorFloat::VectorFloat (int size)
{
  assert( (size > 1) || (size <= 3) );

  mSize = size;
  data = (float*) malloc(sizeof(float)*size);
}

VectorFloat::VectorFloat (float d0, float d1)
{
  mSize = 2;
  data = (float*) malloc(sizeof(float)*mSize);
  data[0] = d0;
  data[1] = d1;
}

VectorFloat::VectorFloat (float d0, float d1, float d2)
{
  mSize = 3;
  data = (float*) malloc(sizeof(float)*mSize);
  data[0] = d0;
  data[1] = d1;
  data[2] = d2;
}

VectorFloat::VectorFloat (VectorFloat &v)
{
  mSize = v.size();
  data = (float*) malloc(sizeof(float)*mSize);
  data[0] = v.getX();
  data[1] = v.getY();
  if ( mSize == 3 )
    data[2] = v.getZ();
}

char
VectorFloat::size () const
{
  return mSize;
}

float
VectorFloat::getX () const
{
  return data[0];
}

float
VectorFloat::getY () const
{
  if ( mSize > 1 )
    return data[1];
  else
    return 0.0f;
}

float
VectorFloat::getZ () const
{
  if ( mSize > 2 )
    return data[2];
  else
    return 0.0f;
}

void
VectorFloat::set (float x, float y)
{
  data[0] = x;
  data[1] = y;
}

void
VectorFloat::set (float x, float y, float z)
{
  set(x, y);
  if ( mSize == 3 )
    data[2] = z;
}

void
VectorFloat::set (VectorFloat v)
{
  set(v.getX(), v.getY(), v.getZ());
}

void
VectorFloat::setX (float x)
{
  data[0] = x;
}

void
VectorFloat::setY (float y)
{
  data[1] = y;
}

void
VectorFloat::setZ (float z)
{
  if ( mSize > 2 )
    data[2] = z;
}

VectorFloat*
VectorFloat::add (VectorFloat v2)
{
  VectorFloat *result;
  if ( mSize >= v2.size() )
    {
      if ( mSize == 2 )
        result = new VectorFloat(data[0]+v2.getX(), data[1]+v2.getY());
      else
        result = new VectorFloat(data[0]+v2.getX(),
                                 data[1]+v2.getY(),
                                 data[2]+v2.getZ());
    }
  else
    {
      result = new VectorFloat(data[0]+v2.getX(),
                               data[1]+v2.getY(),
                               getZ() +v2.getZ());
    }

  return result;
}


VectorFloat*
VectorFloat::sub (VectorFloat v2)
{
  VectorFloat *result;
  if ( mSize >= v2.size() )
    {
      if ( mSize == 2 )
        result = new VectorFloat(data[0]-v2.getX(), data[1]-v2.getY());
      else
        result = new VectorFloat(data[0]-v2.getX(),
                                 data[1]-v2.getY(),
                                 data[2]-v2.getZ());
    }
  else
    {
      result = new VectorFloat(data[0]-v2.getX(),
                               data[1]-v2.getY(),
                               getZ() -v2.getZ());
    }

  return result;
}

float
VectorFloat::norm ()
{
  float _norm;
  if ( mSize == 2 )
    _norm = (data[0]*data[0]) + (data[1]*data[1]);
  else
    _norm = (data[0]*data[0]) + (data[1]*data[1]) + (data[2]*data[2]);

  return sqrt(_norm);
}

void
VectorFloat::normalize ()
{
  float _norm = norm();

  _norm = 1.0f / _norm;
  data[0] = data[0]*_norm;
  data[1] = data[1]*_norm;
  if ( mSize == 3 )
    data[2] = data[2]*_norm;
}

float
VectorFloat::dotProduct (VectorFloat v2)
{
  return (data[0]*v2.getX() + data[1]*v2.getY() + getZ()*v2.getZ());
}

VectorFloat*
VectorFloat::crossProduct (VectorFloat v2)
{
  float x =  (getY()*v2.getZ() - getZ()*v2.getY());
  float y = -(getX()*v2.getZ() - getZ()*v2.getX());
  float z =  (getX()*v2.getY() - getY()*v2.getX());

  return new VectorFloat(x,y,z);
}

inline
VectorFloat&
VectorFloat::operator= (const VectorFloat &v2)
{
  if ( mSize < v2.size() )
    {
      delete data;
      mSize = v2.size();
      data = (float*) malloc(sizeof(float)*mSize);
    }

  data[0] = v2.getX();
  data[1] = v2.getY();
  data[2] = v2.getZ();

  return *this;
}

#endif // _VECTORFLOAT_H_
