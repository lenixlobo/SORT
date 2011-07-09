/*
 * filename:	vector.h
 *
 * programmer:	Cao Jiayin
 */

#ifndef SORT_VECTOR
#define	SORT_VECTOR

#include "managers/logmanager.h"

// pre-deleration
class Transform;

/////////////////////////////////////////////////////////////////////////
// definition of vector
class	Vector
{
// public method
public:
	// default constructor, all of the components are set zero
	Vector( bool normal = false );
	// constructor from three float data
	// para 'x':	x component
	// para 'y':	y component
	// para 'z':	z component
	Vector( float x , float y , float z , bool normal = false );
	// copy constructor
	// para 'vector':	vector to copy
	Vector( const Vector& vector );
	// destructor does nothing here
	~Vector();

	// math operations
	// para 'v' : 	vector to add
	// result :	a vector containing the sum of two vectors in each component
	Vector operator+( const Vector& v ) const;
	// para 'v' :	vector to add
	// result :	current vector after adding 'v' in each component
	Vector& operator+=( const Vector& v );
	// para 'v' :	vector to minus
	// result :	a vector containing the difference of two vectors in each component
	Vector operator-( const Vector& v ) const;
	// para 'v' :	vector to minus
	// result :	current vector after minusing 'v' in each component
	Vector& operator-=( const Vector& v );
	// para 'f' :	scaler to the vector
	// result :	a vector scaled by the scaler
	Vector operator*( float f ) const;
	// para 'f' :	scaler to the vector
	// result   :   current vector scaled by the scaler
	Vector& operator*=( float f );
	// para 'f' :	the divider
	// result   :	a vector divided by the divider
	// note	    :	there will be run-time and log LOG_ERROR if 'f' is zero
	Vector operator/( float f ) const;
	// para 'f' :	the divider
	// result   :	current vector after dividing by the divider
	// note	    :	there will be run-time and log LOG_ERROR if 'f' is zero
	Vector&	operator /= ( float f );
	// para 'v' :	vector to copy
	// result   :	copy the vector
	Vector& operator = ( const Vector& v ) ;

	// get the length of the vector
	// result :	the length of the vector
	float	Length() const;
	// get the squared length of the vector
	// result :	the squared length of the vector
	float	SquaredLength() const;
	// normalize the vector
	// result :	the normalized vector
	// note   :	there will be warning if it's a zero vector ( 0 , 0 , 0 )
	Vector&	Normalize();

	// [] operator
	// para 'id' :	an id from 0 to 2
	// result :	a component with the specific id
	float	operator[] ( unsigned id ) const;
	// [] operator
	// para 'id' :	an from 0 to 2
	// result :	a component with the specific id
	float&	operator[] ( unsigned id );

	// - operator , flip the vector
	// result :	a flipped vector
	Vector  operator- () const;

	// == operator
	// para 'v' :	an vector to compare
	// result   :	'true' if the 'v' is the same with current vector, 'false' else
	bool	operator == ( const Vector& v ) const;
	// != operator
	// para 'v' :	an vector to compare
	// result   :	'false' if the 'v' is not the same with current vector, 'false' else
	bool	operator != ( const Vector& v ) const;

	// rotate a vector along the current vector
	// para 'vec'   : the vector to rotate
	// para 'angle' : the angle of rotation
	void	Rotate( Vector& vec , float angle ) const;

// make all of the components public.
public:
	// the x y z data in three dimension
	float x;
	float y;
	float z;

	// whether it's a normal or not
	// by default , it's false
	bool m_bNormal;
};

// * operator
// para 'f'  :	scaler
// para 'v0' :	the vector to scale
// result    :	a scaled vector
inline Vector operator *( float f , const Vector& v0 )
{
	return v0 * f;
}
// para 'v0' : 	a vector
// para 'v1' :	another vector
// result    :	the dot product of the two vectors
inline float Dot( const Vector& v0 , const Vector& v1 )
{
	return v0.x * v1.x + v0.y * v1.y + v0.z * v1.z;
}
// para 'v0' :	a vector
// para 'v1' :	another vector
// result    :	the absolute value of the dot product
inline float AbsDot( const Vector& v0 , const Vector& v1 )
{
	float r = Dot( v0 , v1 );
	return ( r < 0.0f )? -r : r;
}
// para 'v0' :	a vector
// para 'v1' :	another vector
// result    :	the cross product of the two vectors
inline Vector Cross( const Vector& v0 , const Vector& v1 )
{
	Vector v;
	v.x = v0.y * v1.z - v0.z * v1.y;
	v.y = v0.z * v1.x - v0.x * v1.z;
	v.z = v0.x * v1.y - v0.y * v1.x;
	return v;
}
// para 'v0' :	a vector
// para 'v1' :	another vector
// result    :	'true' if the two vector is facing towards the same direction, 'false' else
inline bool FaceForward( const Vector& v0 , const Vector& v1 )
{
	return Dot( v0 , v1 ) >= 0.0f;
}

// normalize a vector
inline Vector Normalize( const Vector& v )
{
	float len = v.Length();

	if( len == 0.0f )
	{
		LOG_WARNING<<"Try to normalize a zero length vector."<<ENDL;
		return Vector();
	}

	return v / len;
}

#endif


