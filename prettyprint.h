#pragma once

#ifdef __GNUC__
#define __PLUGIN_FUNCTION__ __PRETTY_FUNCTION__
#else
#define __PLUGIN_FUNCTION__ __func__
#endif

