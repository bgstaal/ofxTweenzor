#include "ofParameterTween.h"


template<>
void ofParameterTween<float>::update(int a_millis)
{
	Tween::update(a_millis);
	_param = ofMap(_rat, 0.0f, 1.0f, _begin, _end);
}

template<>
void ofParameterTween<ofFloatColor>::update(int a_millis)
{
	Tween::update(a_millis);
	_param = _begin.lerp(_end, _rat);
}

template<>
void ofParameterTween<ofVec2f>::update(int a_millis)
{
	Tween::update(a_millis);
	_param = _begin.getInterpolated(_end, _rat);
}

template<>
void ofParameterTween<ofVec3f>::update(int a_millis)
{
	Tween::update(a_millis);
	_param = _begin.getInterpolated(_end, _rat);
}

template<>
void ofParameterTween<ofVec4f>::update(int a_millis)
{
	Tween::update(a_millis);
	_param = _begin.getInterpolated(_end, _rat);
}

template<>
void ofParameterTween<ofRectangle>::update(int a_millis)
{
	Tween::update(a_millis);
	ofRectangle r(ofMap(_rat, 0.0f, 1.0f, _begin.getX(), _end.getX()),
							ofMap(_rat, 0.0f, 1.0f, _begin.getX(), _end.getX()),
							ofMap(_rat, 0.0f, 1.0f, _begin.getX(), _end.getX()),
							ofMap(_rat, 0.0f, 1.0f, _begin.getX(), _end.getX()));
	_param = r;
}