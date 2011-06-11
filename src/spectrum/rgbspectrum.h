/*
 * filename :	rgbspectrum.h
 *
 * programmer :	Cao Jiayin
 */

#ifndef	SORT_RGBSPECTRUM
#define	SORT_RGBSPECTRUM

///////////////////////////////////////////////////////////////////
// defination of rgb spectrum
class	RGBSpectrum
{
// public method
public:
	// default constructor
	RGBSpectrum();
	// constructor from three float
	RGBSpectrum( float r , float g , float b );
	// constructor from three unsigned char
	RGBSpectrum( unsigned char r , unsigned char g , unsigned char b );
	// destructor
	~RGBSpectrum();

	// get the color
	unsigned int GetColor() const;
	// set the color
	void SetColor( unsigned int color );
	// get each component
	float	GetR() const { return m_r; }
	float	GetG() const { return m_g; }
	float	GetB() const { return m_b; }

// private field
private:
	// the rgb color
	float m_r;
	float m_g;
	float m_b;
};

#endif


