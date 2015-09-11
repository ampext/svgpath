#pragma once

#ifdef _MSC_VER
	#ifdef SVGPATH_USINGDLL
		#define SVGPATH_EXPORT __declspec(dllexport)
		#define SVGPATH_IMPORT __declspec(dllimport)
	#else
		#define SVGPATH_EXPORT
		#define SVGPATH_IMPORT
	#endif
#else
	#define SVGPATH_EXPORT
	#define SVGPATH_IMPORT
#endif

#ifdef SVGPATH_BUILDINGDLL
	#define SVGPATHAPI SVGPATH_EXPORT
#else
	#define SVGPATHAPI SVGPATH_IMPORT
#endif