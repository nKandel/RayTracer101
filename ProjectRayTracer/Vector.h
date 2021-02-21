
// 3D vectors, completely inlined


//--------------------------------------------------
//
//  3D vector class for chromeball
//
//--------------------------------------------------

#include <cmath>
#include <iostream>
#ifndef ___VECTOR_H____
#define ___VECTOR_H____



namespace chromeball{


/*!
 *  This is a fully inlined class for vector manipulation in 3D
 */
class Vector
{

  private:

    double m_Data[3];

  public:


    Vector()
    {
       m_Data[0] = 0;
       m_Data[1] = 0;
       m_Data[2] = 0;
    }

    Vector( const double& v1, const double& v2, const double& v3 )
    {
       m_Data[0] = v1;
       m_Data[1] = v2;
       m_Data[2] = v3;
    }

    Vector( const double v[3] )
    {
       m_Data[0] = v[0];
       m_Data[1] = v[1];
       m_Data[2] = v[2];
    }

    // copy constructor
    Vector( const Vector& v )
    {
       m_Data[0] = v.m_Data[0];
       m_Data[1] = v.m_Data[1];
       m_Data[2] = v.m_Data[2];
    }

   ~Vector(){}



    //----------------------------------------------------------------
    //
    // Set and get methods
    //
    //----------------------------------------------------------------

    void set( const double& v1, const double& v2, const double& v3 )
    {
       m_Data[0] = v1;
       m_Data[1] = v2;
       m_Data[2] = v3;
    }


    void get( double& v1, double& v2, double& v3 ) const
    {
       v1 = m_Data[0];
       v2 = m_Data[1];
       v3 = m_Data[2];
    }

    void set ( const int index, const double value ) { m_Data[index] = value; }
    void setX( const double value )                  { m_Data[0] = value; }
    void setY( const double value )                  { m_Data[1] = value; }
    void setZ( const double value )                  { m_Data[2] = value; }


    void get( const int index, double& value ) const { value = m_Data[index]; }
    const double get ( const int index ) const       { return m_Data[index]; }
    const double getX() const                        { return m_Data[0]; }
    const double getY() const                        { return m_Data[1]; }
    const double getZ() const                        { return m_Data[2]; }


    const double operator() ( const int& a ) const   { return m_Data[a]; }
    double&      operator[] ( const int& a )         { return m_Data[a]; }
    const double& operator[] ( const int& a ) const { return m_Data[a]; }



    //------------------------------------------------------------------------
    //
    // operator overloads for linear space math: inner product, cross product
    //
    //------------------------------------------------------------------------

    //! inner (dot) product
    const double operator* ( const Vector& v ) const
    {
        return ( m_Data[0]*v.m_Data[0]
               + m_Data[1]*v.m_Data[1]
               + m_Data[2]*v.m_Data[2] );
    }

    //! cross product  ( NOT outer product )
    const Vector operator^ (const Vector& v ) const
    {
       return Vector(
                      m_Data[1]*v.m_Data[2] - m_Data[2]*v.m_Data[1],
                      m_Data[2]*v.m_Data[0] - m_Data[0]*v.m_Data[2],
                      m_Data[0]*v.m_Data[1] - m_Data[1]*v.m_Data[0]
                    );
    }


    //-------------------------------------------------------------------------
    //
    // operator= and related overloads
    //
    //-------------------------------------------------------------------------

    Vector& operator= ( const Vector& v )
    {
        m_Data[0] = v.m_Data[0];
        m_Data[1] = v.m_Data[1];
        m_Data[2] = v.m_Data[2];
	return *this;
    }

    Vector& operator= ( const double v )
    {
        m_Data[0] = v;
        m_Data[1] = v;
        m_Data[2] = v;
	return *this;
    }

    Vector& operator+= ( const Vector& v )
    {
        m_Data[0] += v.m_Data[0];
        m_Data[1] += v.m_Data[1];
        m_Data[2] += v.m_Data[2];
        return *this;
    }

    Vector& operator+= ( const double v )
    {
        m_Data[0] += v;
        m_Data[1] += v;
        m_Data[2] += v;
        return *this;
    }

    Vector& operator-= ( const Vector& v )
    {
        m_Data[0] -= v.m_Data[0];
        m_Data[1] -= v.m_Data[1];
        m_Data[2] -= v.m_Data[2];
        return *this;
    }

    Vector& operator-= ( const double v )
    {
        m_Data[0] -= v;
        m_Data[1] -= v;
        m_Data[2] -= v;
        return *this;
    }

    Vector& operator*= ( const double& v )
    {
        m_Data[0] *= v;
        m_Data[1] *= v;
        m_Data[2] *= v;
        return *this;
    }

    Vector& operator/= ( const double& v )
    {
        m_Data[0] /= v;
        m_Data[1] /= v;
        m_Data[2] /= v;
        return *this;
    }

    Vector operator* ( const double& v ) const
    {
        return Vector( m_Data[0]*v, m_Data[1]*v, m_Data[2]*v );
    }

    Vector operator/ ( const double& v ) const
    {
        return Vector( m_Data[0]/v, m_Data[1]/v, m_Data[2]/v );
    }

    Vector operator+ ( const Vector& v ) const
    {
        return Vector( m_Data[0] + v.m_Data[0],
                       m_Data[1] + v.m_Data[1],
                       m_Data[2] + v.m_Data[2] );

    }

    Vector operator- ( const Vector& v ) const
    {
        return Vector( m_Data[0] - v.m_Data[0],
                       m_Data[1] - v.m_Data[1],
                       m_Data[2] - v.m_Data[2] );

    }

    friend Vector operator* ( const double v, const Vector& V )
    {
        return V*v;
    }

    friend Vector operator- ( const Vector& V ) { return V*(-1.0); }


    //--------------------------------------------------------------------
    //
    //  Other utilities
    //
    //--------------------------------------------------------------------

    const double magnitude() const { return std::sqrt( m_Data[0]*m_Data[0]
                                                     + m_Data[1]*m_Data[1]
                                                     + m_Data[2]*m_Data[2] ); }

    void normalize()
    {
        const double mag = magnitude();
        m_Data[0] /= mag;
        m_Data[1] /= mag;
        m_Data[2] /= mag;
    }

    const Vector normal() const { return (*this)/magnitude(); }

    const Vector rotate(const Vector& axis, const double angle)
    {
       Vector a = axis.normal();
       double ca = std::cos(angle);
       double sa = std::sin(angle);
       Vector result = (*this)*ca + a*(a*(*this))*(1.0-ca) + (a^(*this))*sa;
       return result;
    }

};


struct Color
{
    double r, g, b;

    void printColor()
    {
        std::cout<<"[R,G,B] = ["<<r<<", "<<g<<", "<<b<<"]"<<std::endl;
    }
};



}

#endif

