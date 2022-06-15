#ifndef _VIRTUALTRACKBALL_H_
#define _VIRTUALTRACKBALL_H_

#include <math.h>

#include "VectorFloat.h"
#include "Quaternion.h"
#include "Matrix.h"

class VirtualTrackball {
public:
  VirtualTrackball ();
  //VirtualTrackball (float floatArray[]);
  virtual ~VirtualTrackball ();

  void updateWindowSize (int width,
                         int height);

  Quaternion* getRotationCopy ();

  /**
   *  Retorna o equivalente em matriz. A matriz do modelo de visao, modelView.
   *  --Lembrar de deletar a memoria alocada para esse retorno.--
   */
  float* getMatrix ();

  void setCenter (VectorFloat *center,
                  float zoom);

  void pointerUp ();
  void pointerDown (float x,
                    float y);
  void pointerMove (float x,
                    float y);

  void move (float dx,
             float dy);

  void zoom (float dz);


private:
  // Função que simula a trackball virtual baseado na implementação de Holroyd.
  // Este site https://www.opengl.org/wiki/Object_Mouse_Trackball foi utilizado
  // como referência.
  void trackball (float x,
                  float y);

  void mapsOntoSurface (VectorFloat *p);

  void applyZoom ();

  void loadMatrixIdentity ();

protected:

private:
  static const unsigned short UPDATE_NORMALIZE_ROTATION = 65535;
  const float TRACKBALL_RADIUS = 1.0f;

  unsigned char mCountUpdateRotation;

  float mZoom;
  float mCenter[3];
  float mDisplacement[3];
  float mMatrix[16];

  bool  mTouchPressed;
  float mWidth;
  float mHeight;

  Quaternion  *mRotation;
  VectorFloat *mOldPointer;
};

VirtualTrackball::~VirtualTrackball ()
{
  delete mRotation;
  delete mOldPointer;
}

VirtualTrackball::VirtualTrackball ()
{
  mCountUpdateRotation = 0;
  mTouchPressed = false;

  mOldPointer = new VectorFloat(2);
  mRotation   = Quaternion::getRotationIdentity();
  loadMatrixIdentity();
}

void
VirtualTrackball::updateWindowSize(int width,
                                   int height)
{
  mWidth  = width;
  mHeight = height;
}

Quaternion*
VirtualTrackball::getRotationCopy ()
{
  return new Quaternion(*mRotation);
}

float*
VirtualTrackball::getMatrix ()
{
  float *_matrix = (float*) malloc(sizeof(float)*16);

  Matrix::translate(_matrix,
                    mMatrix,
                    mCenter[0]+mDisplacement[0],
                    mCenter[1]+mDisplacement[1],
                    mCenter[2]+mDisplacement[2]);

  return _matrix;
}

void
VirtualTrackball::setCenter (VectorFloat *center,
                             float zoom)
{
  if ( center != NULL )
    {
      mCenter[0] = -center->getX();
      mCenter[1] = -center->getY();
      mCenter[2] = -center->getZ();
      mDisplacement[0] = mDisplacement[1] = mDisplacement[2] = 0.0f;
      mZoom = zoom;
      applyZoom();
    }
}

void
VirtualTrackball::pointerUp ()
{
  mTouchPressed = false;
}

void
VirtualTrackball::pointerDown(float x,
                              float y)
{
  mOldPointer->setX( (2.0f*x - mWidth) / mWidth );  //Colocando os valores de X
  mOldPointer->setY( (mHeight - 2.0f*y) / mHeight );// e Y no intervalo de
                                                    // [-1, 1].

  mTouchPressed = true;
}

void
VirtualTrackball::pointerMove(float x,
                              float y)
{
  if ( mTouchPressed )
    {
      x = (2.0f*x - mWidth) / mWidth;
      y = (mHeight - 2.0f*y) / mHeight;

      trackball(x, y);

      mOldPointer->set(x, y);
      applyZoom();
    }
  //else
    //pointerDown(x, y);
}

void
VirtualTrackball::move (float dx,
                        float dy)
{
  Quaternion *_q = new Quaternion(0.0f, dx, -dy, 0.0f);
  Quaternion *_conjugate = mRotation->conjugate();
  Quaternion *_mult1 = mRotation->mult(*_q);
  Quaternion *_mult2 = _mult1->mult(*_conjugate);

  float *_disp = _mult2->getFloatArray();

  mDisplacement[0] += _disp[1];
  mDisplacement[1] += _disp[2];
  mDisplacement[2] += _disp[3];

  delete _q;
  delete _conjugate;
  delete _mult1;
  delete _mult2;
  delete _disp;
}

void
VirtualTrackball::zoom (float dz)
{
  mZoom -= dz;
  applyZoom();
}

void
VirtualTrackball::trackball (float x,
                             float y)
{
  if ( (mOldPointer->getX() == x) && (mOldPointer->getY() == y) )
    return;

  VectorFloat *_pOld = new VectorFloat(mOldPointer->getX(),
                                       mOldPointer->getY(),
                                       0.0f);
  VectorFloat *_pNew = new VectorFloat(x, y, 0.0f);

  mapsOntoSurface(_pOld);
  mapsOntoSurface(_pNew);

  _pOld->normalize();
  _pNew->normalize();

  VectorFloat *_axis = _pNew->crossProduct(*_pOld);

  float _arg = _pOld->dotProduct(*_pNew);
  _arg = ((_arg >= -1.0f) && (_arg <= 1.0f)) ?
         _arg :
         (_arg/abs(_arg) > 0.0f ? 1.0f : -1.0f);

  float _theta = acos(_arg);

  Quaternion *_rotQuat = Quaternion::getRotationQuaternion(_theta, *_axis);
  Quaternion *_multQuat = mRotation->mult(*_rotQuat);

  mRotation->set(*_multQuat);

  if ( mCountUpdateRotation == UPDATE_NORMALIZE_ROTATION )
    {
      mCountUpdateRotation = 0;
      mRotation->normalize();
    }
  else
    mCountUpdateRotation++;

  float *_matAux = mRotation->getMatrix();
  for (int i = 0; i < 16; i++)
    mMatrix[i] = _matAux[i];

  delete _pOld;
  delete _pNew;
  delete _axis;
  delete _rotQuat;
  delete _multQuat;
  delete _matAux;
}

void
VirtualTrackball::mapsOntoSurface (VectorFloat *p)
{
  float _overSqrt2 = 0.70710678118654752440f;
  float _length = p->norm();
  float _r = TRACKBALL_RADIUS;

  if ( _length <= (_r*_overSqrt2) ) // r/sqrt(2)
    p->setZ(sqrt( (_r*_r) - (_length*_length)) );
  else
    p->setZ((_r*_r)/(2.0f*_length));
}

void
VirtualTrackball::applyZoom ()
{
  mMatrix[14] = mZoom;
  mMatrix[15] = 1.0f;
}

void
VirtualTrackball::loadMatrixIdentity ()
{
  mMatrix[0]=1.0f; mMatrix[4]=0.0f; mMatrix[ 8]=0.0f; mMatrix[12]=0.0f;
  mMatrix[1]=0.0f; mMatrix[5]=1.0f; mMatrix[ 9]=0.0f; mMatrix[13]=0.0f;
  mMatrix[2]=0.0f; mMatrix[6]=0.0f; mMatrix[10]=1.0f; mMatrix[14]=0.0f;
  mMatrix[3]=0.0f; mMatrix[7]=0.0f; mMatrix[11]=0.0f; mMatrix[15]=1.0f;
}


#endif // _VIRTUALTRACKBALL_H_
