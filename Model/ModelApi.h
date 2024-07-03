#pragma once

#ifdef _MSC_VER
#define MODEL_API __declspec(dllexport)
#else
#define MODEL_API
#endif
