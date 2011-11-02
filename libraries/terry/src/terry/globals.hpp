#ifndef _TERRY_GLOBALS_HPP_
#define _TERRY_GLOBALS_HPP_

//#include <tuttle/common/math/minmax.hpp>

//#include <ofxCore.h>

#include <boost/gil/gil_config.hpp>
#include <boost/gil/typedefs.hpp>
#include <boost/gil/image.hpp>
#include <boost/gil/image_view.hpp>
#include <boost/gil/image_view_factory.hpp>
#include <boost/type_traits.hpp>

#include <ostream>

namespace terry {

/*
template<class View>
View getFullView( View tileView, const OfxRectI& bounds, const OfxRectI& rod )
{
	using namespace boost::gil;
	typedef typename View::value_type Pixel;

	// if the tile is equals to the full image
	// directly return the tile
	if( bounds.x1 == rod.x1 && bounds.y1 == rod.y1 &&
	    bounds.x2 == rod.x2 && bounds.y2 == rod.y2 )
		return tileView;

	// view the tile as a full image
	return subimage_view( tileView, rod.x1 - bounds.x1, rod.y1 - bounds.y1, rod.x2 - rod.x1, rod.y2 - rod.y1 );
}
*/

template <class View, typename Alloc=std::allocator<unsigned char> >
struct image_from_view
{
	typedef typename View::value_type value_type; // pixel_t
	typedef typename boost::gil::image<value_type, boost::gil::is_planar<View>::value, Alloc> type;
};
// typedef typename view_type_from_pixel<OutPixelType, boost::gil::is_planar<View>::value >::type OutView;

template<class View>
struct layout_type
{
    typedef boost::gil::layout<
	 typename boost::gil::color_space_type<View>::type,
	 typename boost::gil::channel_mapping_type<View>::type
	 > type;
};

/**
 * @return the current type T if it's a floating point type,
 *         else return F
 */
template<typename T, typename F = boost::gil::bits32f>
struct floating_channel_type_t
{
	typedef typename boost::mpl::if_< boost::is_floating_point<T>,
					  T,
					  F >::type type;
};

template<class View>
struct floating_pixel_from_view
{
	typedef typename boost::gil::channel_mapping_type<View>::type Channel;
	typedef typename floating_channel_type_t<Channel>::type ChannelFloat;

	typedef boost::gil::pixel<ChannelFloat, typename layout_type<View>::type > type;
};


template <class View>
inline float max_value()
{
	using namespace boost::gil;
	return channel_traits< typename channel_type< View >::type >::max_value();
}

template <class View>
inline float domain_max_value()
{
	using namespace boost::gil;
	return channel_traits< typename channel_type< View >::type >::max_value() + 1.0f;
}

}


/// \ingroup PointModel
template <typename T>
GIL_FORCEINLINE
boost::gil::point2<T> operator*( const boost::gil::point2<T>& p, const double t ) { return boost::gil::point2<T >( p.x * t, p.y * t ); }
/// \ingroup PointModel
template <typename T>
GIL_FORCEINLINE
boost::gil::point2<T>& operator*=( boost::gil::point2<T>& p, const double t ) { p.x *= t; p.y *= t; return p; }
/// \ingroup PointModel
template <typename T>
GIL_FORCEINLINE
boost::gil::point2<T> operator*( const boost::gil::point2<T>& a, const boost::gil::point2<T>& b ) { return boost::gil::point2<T>( a.x * b.x, a.y * b.y ); }
/// \ingroup PointModel
template <typename T>
GIL_FORCEINLINE
boost::gil::point2<T>& operator*=( boost::gil::point2<T>& a, const boost::gil::point2<T>& b ) { a.x *= b.x; a.y *= b.y; return a; }
/// \ingroup PointModel
template <typename T>
GIL_FORCEINLINE
boost::gil::point2<T> operator/( const boost::gil::point2<T>& a, const boost::gil::point2<T>& b ) { return boost::gil::point2<T>( a.x / b.x, a.y / b.y ); }
/// \ingroup PointModel
template <typename T>
GIL_FORCEINLINE
boost::gil::point2<double> operator/( const double t, const boost::gil::point2<T>& p )
{
	boost::gil::point2<double> res( 0, 0 );
	if( p.x != 0 )
		res.x = t / p.x;
	if( p.y != 0 )
		res.y = t / p.y;
	return res;
}

template <typename T>
std::ostream& operator<<( std::ostream& out, const boost::gil::point2<T>& p )
{
	return out << "x:" << p.x << " y:" << p.y;
}


#endif
