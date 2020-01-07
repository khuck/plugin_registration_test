#pragma once

#if defined(__GNUC__) && defined(__PRETTY_FUNCTION__)
#define __PLUGIN_FUNCTION__ __PRETTY_FUNCTION__
#else
#define __PLUGIN_FUNCTION__ __func__
#endif

