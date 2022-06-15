#ifndef _QUATERNION_H_
#define _QUATERNION_H_

#include <math.h>

#include "VectorFloat.h"

/**
 * Created by Luan Sala on 21/07/2015.
 */
class Quaternion
{
public:
  Quaternion (Quaternion &q);
  Quaternion (float scalar, float x, float y, float z);
  Quaternion (float scalar, VectorFloat v);
  virtual ~Quaternion();

  float* getFloatArray ();
  float  getReal ();
  float  getX ();
  float  getY ();
  float  getZ ();

  void set (Quaternion q);
  void set (float scalar, float x, float y, float z);

  Quaternion* add (Quaternion q);
  Quaternion* mult (float a);
  Quaternion* mult (Quaternion q);
  Quaternion* conjugate ();

  void   normalize ();
  float  norm ();
  float  dotProduct (Quaternion q);
  float* getMatrix ();

  static Quaternion* getRotationIdentity ();
  static Quaternion* getRotationQuaternion (float angle,
                                           float x,
                                           float y,
                                           float z);
  static Quaternion* getRotationQuaternion (float angle, VectorFloat axis);

protected:

private:
  float s;
  float x, y, z;
};

Quaternion::~Quaternion ()
{
}

Quaternion::Quaternion (Quaternion &q)
{
  s = q.getReal();
  x = q.getX();
  y = q.getY();
  z = q.getZ();
}

Quaternion::Quaternion (float scalar,
                        float x,
                        float y,
                        float z)
{
  s       = scalar;
  this->x = x;
  this->y = y;
  this->z = z;
}

Quaternion::Quaternion (float scalar,
                        VectorFloat v)
{
  s = scalar;
  x = v.getX();
  y = v.getY();
  z = v.getZ();
}

float*
Quaternion::getFloatArray ()
{
  float *_floatArray = (float*) malloc(sizeof(float)*4);

  _floatArray[0] = s;
  _floatArray[1] = x;
  _floatArray[2] = y;
  _floatArray[3] = z;

  return _floatArray;
}

float
Quaternion::getReal ()
{
  return s;
}

float
Quaternion::getX ()
{
  return x;
}

float
Quaternion::getY ()
{
  return y;
}

float
Quaternion::getZ ()
{
  return z;
}

void
Quaternion::set (Quaternion q)
{
  s = q.s;
  x = q.x;
  y = q.y;
  z = q.z;
}

void
Quaternion::set (float scalar,
                 float x,
                 float y,
                 float z)
{
  s       = scalar;
  this->x = x;
  this->y = y;
  this->z = z;
}

Quaternion*
Quaternion::add (Quaternion q)
{
  return new Quaternion(s+q.getReal(),
                        x+q.getX(),
                        y+q.getY(),
                        z+q.getZ());
}

Quaternion*
Quaternion::mult (float a)
{
  return new Quaternion(a*s, a*x, a*y, a*z);
}

Quaternion*
Quaternion::mult (Quaternion q)
{
  float       _scalar = s*q.getReal() - (x*q.getX()+y*q.getY()+z*q.getZ());
  VectorFloat _vector(s*q.getX()+q.getReal()*x + (y*q.getZ()-z*q.getY()),
                      s*q.getY()+q.getReal()*y + (z*q.getX()-x*q.getZ()),
                      s*q.getZ()+q.getReal()*z + (x*q.getY()-y*q.getX()));
  //float _vector[] = {s*q.getX()+q.getReal()*x + (y*q.getZ()-z*q.getY()),
    //                 s*q.getY()+q.getReal()*y + (z*q.getX()-x*q.getZ()),
      //               s*q.getZ()+q.getReal()*z + (x*q.getY()-y*q.getX())};

  return new Quaternion(_scalar, _vector);
}

Quaternion*
Quaternion::conjugate ()
{
  return new Quaternion(s, -x, -y, -z);
}

void
Quaternion::normalize ()
{
  float _norm = norm();

  if ( _norm > 0.00001f && abs(_norm-1.0f) > 0.00001f )
    {
      _norm = 1.0f/_norm;
      s = s * _norm;
      x = x * _norm;
      y = y * _norm;
      z = z * _norm;
    }
}

float
Quaternion::norm ()
{
  return sqrt(s*s + x*x + y*y + z*z);
}

float
Quaternion::dotProduct (Quaternion q)
{
  return (s*q.getReal() + x*q.getX() + y*q.getY() + z*q.getZ());
}

float*
Quaternion::getMatrix ()
{
  float *_matrix = (float*) malloc(sizeof(float)*16);
  float xx = x*x;  float yy = y*y;  float zz = z*z;
  float xs = x*s;  float xy = x*y;  float xz = x*z;
  float ys = y*s;                   float yz = y*z;
  float zs = z*s;

  _matrix[ 0] = 1-2*(yy+zz); _matrix[ 1] = 2*(xy-zs);   _matrix[ 2] = 2*xz+ys;     _matrix[ 3] = 0.0f;
  _matrix[ 4] = 2*(xy+zs);   _matrix[ 5] = 1-2*(xx+zz); _matrix[ 6] = 2*(yz-xs);   _matrix[ 7] = 0.0f;
  _matrix[ 8] = 2*(xz-ys);   _matrix[ 9] = 2*(yz+xs);   _matrix[10] = 1-2*(xx+yy); _matrix[11] = 0.0f;
  _matrix[12] = 0.0f;        _matrix[13] = 0.0f;        _matrix[14] = 0.0f;        _matrix[15] = 1.0f;

  return _matrix;
}

Quaternion*
Quaternion::getRotationIdentity ()
{
  return new Quaternion(1.0f, 0.0f, 0.0f, 0.0f);
}

Quaternion*
Quaternion::getRotationQuaternion (float angle,
                                   float x,
                                   float y,
                                   float z)
{
  float _scalar = cos(angle*0.5f);
  float _sin    = sin(angle*0.5f);
  float _norm   = sqrt(x*x + y*y + z*z);
  _norm = 1.0f/_norm;

  float aux = _sin*_norm;
  return new Quaternion(_scalar, x*aux, y*aux, z*aux);
}

Quaternion*
Quaternion::getRotationQuaternion (float angle,
                                   VectorFloat axis)
{
  float _scalar = cos(angle*0.5f);
  float _sin    = sin(angle*0.5f);
  float _x    = axis.getX();
  float _y    = axis.getY();
  float _z    = axis.getZ();
  float _norm = sqrt(_x*_x + _y*_y + _z*_z);
  _norm = 1.0f/_norm;

  float _aux = _sin*_norm;
  return new Quaternion(_scalar, _x*_aux, _y*_aux, _z*_aux);
}

#endif // _QUATERNION_H_
