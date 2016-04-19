/*
 *  Tweenzor.h
 *  openFrameworks
 *
 *  Created by Nick Hardeman on 10/31/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _TWEENZOR_
#define _TWEENZOR_

#include "ofColor.h"
#include "ofVec2f.h"
#include "Tween.h"
#include "TweenEvent.h"
#include "ofParameterTween.h"

typedef struct _tweenParams {
	_tweenParams() {
		bUseSeconds = true;
		duration	= 1.f;
		delay		= 0.f;
	}
	
	// params for a tween using frames //
	_tweenParams( float* a_property, float a_end, int a_delay, int a_duration, int a_easeType=EASE_LINEAR) {
		bUseSeconds = false;
		setup( a_property, *a_property, a_end, a_delay, a_duration, a_easeType );
	}
	_tweenParams( float* a_property, float a_begin, float a_end, int a_delay, int a_duration, int a_easeType=EASE_LINEAR, float a_p=0, float a_a=0) {
		bUseSeconds = false;
		setup( a_property, a_begin, a_end, a_delay, a_duration, a_easeType, a_p, a_a );
	}
	
	
	// params for seconds based tween //
	_tweenParams( float* a_property, float a_end, float a_delay, float a_duration, int a_easeType=EASE_LINEAR ) {
		bUseSeconds = true;
		setup( a_property, *a_property, a_end, a_delay, a_duration, a_easeType );
	}
	_tweenParams( float* a_property, float a_begin, float a_end, float a_delay, float a_duration, int a_easeType=EASE_LINEAR, float a_p=0, float a_a=0 ) {
		bUseSeconds = true;
		setup( a_property, a_begin, a_end, a_delay, a_duration, a_easeType, a_p, a_a );
	}
	// setup in frame //
	void setup( float* a_property, float a_begin, float a_end, int a_delay, int a_duration, int a_easeType=EASE_LINEAR, float a_p=0, float a_a=0 ) {
		property	= a_property;
		begin		= a_begin;
		end			= a_end;
		delay		= a_delay;
		duration	= a_duration;
		easeType	= a_easeType;
		p			= a_p;
		a			= a_a;
		bUseSeconds	= false;
	}
	// setup in seconds //
	void setup( float* a_property, float a_begin, float a_end, float a_delay, float a_duration, int a_easeType=EASE_LINEAR, float a_p=0, float a_a=0 ) {
		property	= a_property;
		begin		= a_begin;
		end			= a_end;
		delay		= a_delay;
		duration	= a_duration;
		easeType	= a_easeType;
		p			= a_p;
		a			= a_a;
		bUseSeconds	= true;
	}
	
	float *property;
	float begin, end;
	float duration;
	float delay;
	int easeType;
	// I don't remember what these are for :/ 
	float a;
	float p;
	
	bool bUseSeconds;
} TweenParams;



class Tweenzor {
public:
	static Tweenzor* Instance();
	
	static void init();
	static void update(int a_millis);
	static void add(float* a_property, float a_begin, float a_end, int a_delay, int a_duration, int a_easeType=EASE_LINEAR, float a_p=0, float a_a=0);
	static void add(float* a_property, float a_begin, float a_end, float a_delay, float a_duration, int a_easeType=EASE_LINEAR, float a_p=0, float a_a=0);
	static void add(vector <float *> a_properties, float a_begin, float a_end, float a_delay, float a_duration, int a_easeType=EASE_LINEAR, float a_p=0, float a_a=0);
    static void add(ofFloatColor* a_color, const ofFloatColor& c_begin, const ofFloatColor& c_end, float a_delay, float a_duration, int a_easeType=EASE_LINEAR, float a_p=0, float a_a=0);
    static void add(ofVec2f* a_vec, const ofVec2f& v_begin, const ofVec2f& v_end, float a_delay, float a_duration, int a_easeType=EASE_LINEAR, float a_p=0, float a_a=0);
    static void add(ofVec3f* a_vec, const ofVec3f& v_begin, const ofVec3f& v_end, float a_delay, float a_duration, int a_easeType=EASE_LINEAR, float a_p=0, float a_a=0);
    static void add(ofVec4f* a_vec, const ofVec4f& v_begin, const ofVec4f& v_end, float a_delay, float a_duration, int a_easeType=EASE_LINEAR, float a_p=0, float a_a=0);
    static void add(ofRectangle* a_rect, const ofRectangle& r_begin, const ofRectangle& r_end, float a_delay, float a_duration, int a_easeType=EASE_LINEAR, float a_p=0, float a_a=0);
	
	

	template <typename T>
	static void add(ofParameter<T> *a_param, T a_begin, T a_end, float a_delay, float a_duration, int a_easeType=EASE_LINEAR, float a_p=0, float a_a=0) {
		removeCompleteListener( a_param );
		removeTween( a_param );
		cout << "add param tween" << endl;
		shared_ptr<ofParameterTween<T> > tweenzlebob = shared_ptr<ofParameterTween<T> >( new ofParameterTween<T>(a_param, __instance->_currMillis, a_begin, a_end, a_delay, a_duration, a_easeType, a_p, a_a ));
		__instance->_tweens.push_back( tweenzlebob );
	};

	template <typename T>
	static void removeCompleteListener( ofParameter<T> *a_param ) {
		removeCompleteListener( getTween(a_param) );
	}
	
	template <typename T>
	static void removeTween( ofParameter<T> *a_param ) {
		if (__instance->_tweens.size() > 0) {
			int i = 0;
			vector<shared_ptr<Tween> >::iterator iter;
			for ( iter=__instance->_tweens.begin(); iter < __instance->_tweens.end(); iter++ )
			{
				shared_ptr<Tween> it = *iter;
				ofParameterTween<T> *tween = dynamic_cast<ofParameterTween<T> *>(it.get());
				if (tween && tween->_param == a_param) {
					//cout << "Tweenzor :: removeTween : property = " <<  it->getProperty() << " = " << a_property << endl;
					it->remove();
					__instance->_tweens.erase( iter );
					cout << "removeTween " << *a_param << endl;
					break;
				}
				i++;
			}
			
		}
	}
	
	template <typename T>
	static Tween* getTween( ofParameter<T> *a_param ) {
		vector<shared_ptr<Tween> >::iterator iter;
		for ( iter=__instance->_tweens.begin(); iter < __instance->_tweens.end(); iter++ ) {
			shared_ptr<Tween> &it = *iter;
			ofParameterTween<T> *tw = dynamic_cast<ofParameterTween<T> *>(it.get());
			if(tw && tw->_param == a_param) {
				cout << "get tween " << *a_param << endl;
				return tw;
			}
		}
		return NULL;
	}
	
	//static void add(vector <TweenObject> a_properties, float a_delay, float a_duration, int a_easeType=EASE_LINEAR, float a_p=0, float a_a=0);
	static void add( TweenParams& a_params );
	static void add( vector<TweenParams>& a_params );
	static void removeAllTweens();
	static void removeTween( float* a_property );
	
	static void destroy();
	
	static void pauseAllTweens();
	static void resumeAllTweens();
	static void resetAllTweens();
	static void toggleAllTweens();
	
	static int getSize();
	
	static Tween* getTween( float * a_property );
    static Tween* getTween( ofFloatColor *color );
    static Tween* getTween( ofVec2f *vec );
    static Tween* getTween( ofVec3f *vec );
    static Tween* getTween( ofVec4f *vec );
    static Tween* getTween( ofRectangle *rect );
    
	static Tween* getRecentTween();
	
	
	typedef TweenEvent<float> TweenEv;
	// EVENTS, since POCO is weird //
	template <class ListenerClass>
	static void addCompleteListener( Tween* a_tween, ListenerClass* a_listener, void (ListenerClass::*a_listenerMethod)(float* args)) {
		removeCompleteListener( a_tween );
		TweenEv completeEvent;
		completeEvent = new TweenEv::T<ListenerClass>(a_listener, a_listenerMethod);
		// associate the IDs //
		// can't use pointers, since when manipulating vector,
		// the pointers change :(
		completeEvent.setID( __instance->_eventIndex );
		a_tween->eventID = __instance->_eventIndex;
		__instance->_events.push_back( completeEvent );
		//cout << "Tweenzor.h :: addCompleteListener : event id = " << __instance->_eventIndex << endl;
		__instance->_eventIndex++;
		// if somehow gets near its max, reset it //
		if(__instance->_eventIndex > 0xffffffff - 2) {
			__instance->_eventIndex = 0;
		}
	}
	
	static void removeCompleteListener( Tween* a_tween );
	static void removeCompleteListener( float* a_property );
	static void removeCompleteListener( int a_eventID );
	static void removeAllListeners();
	

protected:
	Tweenzor() {};
	static int getEventIndexForTween( Tween* a_tween );
	static int getEventIDForTween( Tween* a_tween );
	static int getEventIndexForID( int a_eventID );
	
private:
	static Tweenzor* __instance;
	vector <shared_ptr<Tween> > _tweens;
	vector< TweenEv > _events;
	
	unsigned int _eventIndex;
	int _currMillis;
};

#endif






