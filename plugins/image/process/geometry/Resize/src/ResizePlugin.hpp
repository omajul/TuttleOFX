#ifndef _TUTTLE_PLUGIN_RESIZE_PLUGIN_HPP_
#define _TUTTLE_PLUGIN_RESIZE_PLUGIN_HPP_

#include "ResizeDefinitions.hpp"

#include <tuttle/plugin/ImageEffectGilPlugin.hpp>

namespace tuttle {
namespace plugin {
namespace resize {

template<typename Scalar>
struct ResizeProcessParams
{
	boost::gil::point2<Scalar> _size;
};

/**
 * @brief Resize plugin
 */
class ResizePlugin : public ImageEffectGilPlugin
{
public:
	typedef float Scalar;
	typedef boost::gil::point2<double> Point2;

public:
	ResizePlugin( OfxImageEffectHandle handle );

public:
	ResizeProcessParams<Scalar> getProcessParams( const OfxPointD& renderScale = OFX::kNoRenderScale ) const;

	void changedParam( const OFX::InstanceChangedArgs &args, const std::string &paramName );

	bool getRegionOfDefinition( const OFX::RegionOfDefinitionArguments& args, OfxRectD& rod );
//	void getRegionsOfInterest( const OFX::RegionsOfInterestArguments& args, OFX::RegionOfInterestSetter& rois );
	bool isIdentity( const OFX::RenderArguments& args, OFX::Clip*& identityClip, double& identityTime );

	void render( const OFX::RenderArguments &args );
	
	const EParamFilter getFilter() const { return static_cast<EParamFilter>( _paramFilter->getValue() ); }
public:
//	OFX::Clip* _clipSrcMatte; ///< Matte source image clip

	OFX::ChoiceParam*	_paramType;
	OFX::Double2DParam*	_paramOutputFormat;
	OFX::ChoiceParam*	_paramFilter;
	OFX::DoubleParam*	_paramScale;
};

}
}
}

#endif
