#pragma once
#include "Tween.h"
#include "ofParameter.h"

template <typename T>
class ofParameterTween : public Tween
{
	
	float _rat;
	T _begin;
	T _end;
	string _type;
	
	public:
	
		ofParameter<T> _param;
	
		ofParameterTween() {};
	
		ofParameterTween(ofParameter<T> param, T a_begin, T a_end, int a_delay, int a_duration, int a_easeType, float a_p=0, float a_a=0)
		:_param(param), _begin(a_begin), _end(a_end), Tween(&_rat, 0.0f, 1.0f, a_delay, a_duration, a_easeType, a_p, a_a)
		{
			_type = typeid(ofParameter<T>).name();
		}
	
		ofParameterTween(ofParameter<T> param, int a_millis, T a_begin, T a_end, float a_delay, float a_duration, int a_easeType, float a_p=0, float a_a=0)
		:_param(param), _begin(a_begin), _end(a_end), Tween(&_rat, a_millis, 0.0f, 1.0f, a_delay, a_duration, a_easeType, a_p, a_a)
		{
			_type = typeid(ofParameter<T>).name();
		}
	
		virtual void update(int a_millis);
};