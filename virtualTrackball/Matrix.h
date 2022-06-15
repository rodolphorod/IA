#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <math.h>

/**
 * Created by Luan Sala on 07/05/2017.
 */
class Matrix
{
public:
  Matrix();
  virtual ~Matrix();

  /**
   * Defines a projection matrix in terms of a field of view angle, an
   * aspect ratio, and z clip planes.
   *
   * @param m the float array that holds the perspective matrix
   * @param fov field of view in y direction, in degrees
   * @param aspect width to height aspect ratio of the viewport
   * @param zNear
   * @param zFar
   *
   * \ Method copied from android.opengl package. /
   * \ Matrix class                               /
   */
  static void perspective (float mat[],
                           float fov,
                           float aspect,
                           float zNear,
                           float zFar);

  /**
   * Translates matrix m by x, y, and z, putting the result in tm
   *
   * @param tm returns the result
   * @param m source matrix
   * @param x translation factor x
   * @param y translation factor y
   * @param z translation factor z
   *
   * \ Method copied from android.opengl package. /
   * \ Matrix class                               /
   */
  static void translate (float tm[],
                        float m[],
                        float x,
                        float y,
                        float z);

  /**
   *  Faz a multiplicacao de duas matrizes de tamanho 16, pondo o resultado
   *  em result.
   *
   *  @param result O resultado da multiplicacao.
   *  @param leftMatrix Matriz esquerda da multiplicacao.
   *  @param rightMatriz Matriz direita da multiplicacao.
   */
  static void multiply (float result[],
                        float lMat[],
                        float rMat[]);

protected:

private:
};

Matrix::~Matrix ()
{
}

Matrix::Matrix ()
{
}

void
Matrix::perspective (float mat[],
                     float fov,
                     float aspect,
                     float zNear,
                     float zFar)
{
  float _f = 1.0f / tan(fov*(M_PI / 360.0f));
  float _rangeReciprocal = 1.0f / (zNear - zFar);

  mat[0]  = _f / aspect;
  mat[1]  = 0.0f;
  mat[2]  = 0.0f;
  mat[3]  = 0.0f;
  mat[4]  = 0.0f;
  mat[5]  = _f;
  mat[6]  = 0.0f;
  mat[7]  = 0.0f;
  mat[8]  = 0.0f;
  mat[9]  = 0.0f;
  mat[10] = (zFar + zNear) * _rangeReciprocal;
  mat[11] = -1.0f;
  mat[12] = 0.0f;
  mat[13] = 0.0f;
  mat[14] = 2.0f * zFar * zNear * _rangeReciprocal;
  mat[15] = 0.0f;
}

void
Matrix::translate(float tm[],
                  float m[],
                  float x,
                  float y,
                  float z)
{
  for (int i = 0; i < 12; i++)
    tm[i] = m[i];

  for (int i = 0; i < 4; i++)
    {
      int _tmi = i;
      int _mi  = i;
      tm[12+_tmi] = m[_mi] * x +
                    m[4+_mi] * y +
                    m[8+_mi] * z +
                    m[12+_mi];
    }
  //tm[12+_tmi] = m[_mi] * x + m[4+_mi] * y + m[8+_mi] * z + m[12+_mi];
}

void
Matrix::multiply (float result[],
                  float lMat[],
                  float rMat[])
{
  result[0] = lMat[0]*rMat[0]+lMat[4]*rMat[1]+lMat[ 8]*rMat[2]+lMat[12]*rMat[3];
  result[1] = lMat[1]*rMat[0]+lMat[5]*rMat[1]+lMat[ 9]*rMat[2]+lMat[13]*rMat[3];
  result[2] = lMat[2]*rMat[0]+lMat[6]*rMat[1]+lMat[10]*rMat[2]+lMat[14]*rMat[3];
  result[3] = lMat[3]*rMat[0]+lMat[7]*rMat[1]+lMat[11]*rMat[2]+lMat[15]*rMat[3];

  result[4] = lMat[0]*rMat[4]+lMat[4]*rMat[5]+lMat[ 8]*rMat[6]+lMat[12]*rMat[7];
  result[5] = lMat[1]*rMat[4]+lMat[5]*rMat[5]+lMat[ 9]*rMat[6]+lMat[13]*rMat[7];
  result[6] = lMat[2]*rMat[4]+lMat[6]*rMat[5]+lMat[10]*rMat[6]+lMat[14]*rMat[7];
  result[7] = lMat[3]*rMat[4]+lMat[7]*rMat[5]+lMat[11]*rMat[6]+lMat[15]*rMat[7];

  result[8]  = lMat[0]*rMat[8]+lMat[4]*rMat[9]+lMat[ 8]*rMat[10]+lMat[12]*rMat[11];
  result[9]  = lMat[1]*rMat[8]+lMat[5]*rMat[9]+lMat[ 9]*rMat[10]+lMat[13]*rMat[11];
  result[10] = lMat[2]*rMat[8]+lMat[6]*rMat[9]+lMat[10]*rMat[10]+lMat[14]*rMat[11];
  result[11] = lMat[3]*rMat[8]+lMat[7]*rMat[9]+lMat[11]*rMat[10]+lMat[15]*rMat[11];

  result[12] = lMat[0]*rMat[12]+lMat[4]*rMat[13]+lMat[ 8]*rMat[14]+lMat[12]*rMat[15];
  result[13] = lMat[1]*rMat[12]+lMat[5]*rMat[13]+lMat[ 9]*rMat[14]+lMat[13]*rMat[15];
  result[14] = lMat[2]*rMat[12]+lMat[6]*rMat[13]+lMat[10]*rMat[14]+lMat[14]*rMat[15];
  result[15] = lMat[3]*rMat[12]+lMat[7]*rMat[13]+lMat[11]*rMat[14]+lMat[15]*rMat[15];
}

#endif // _MATRIX_H_
