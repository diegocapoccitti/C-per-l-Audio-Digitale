#include "delay.h"

namespace delay {

/****************************************************************************************
Copyright (c) 2023 Cycling '74

The code that Max generates automatically and that end users are capable of
exporting and using, and any associated documentation files (the “Software”)
is a work of authorship for which Cycling '74 is the author and owner for
copyright purposes.

This Software is dual-licensed either under the terms of the Cycling '74
License for Max-Generated Code for Export, or alternatively under the terms
of the General Public License (GPL) Version 3. You may use the Software
according to either of these licenses as it is most appropriate for your
project on a case-by-case basis (proprietary or not).

A) Cycling '74 License for Max-Generated Code for Export

A license is hereby granted, free of charge, to any person obtaining a copy
of the Software (“Licensee”) to use, copy, modify, merge, publish, and
distribute copies of the Software, and to permit persons to whom the Software
is furnished to do so, subject to the following conditions:

The Software is licensed to Licensee for all uses that do not include the sale,
sublicensing, or commercial distribution of software that incorporates this
source code. This means that the Licensee is free to use this software for
educational, research, and prototyping purposes, to create musical or other
creative works with software that incorporates this source code, or any other
use that does not constitute selling software that makes use of this source
code. Commercial distribution also includes the packaging of free software with
other paid software, hardware, or software-provided commercial services.

For entities with UNDER 200k USD in annual revenue or funding, a license is hereby
granted, free of charge, for the sale, sublicensing, or commercial distribution
of software that incorporates this source code, for as long as the entity's
annual revenue remains below 200k USD annual revenue or funding.

For entities with OVER 200k USD in annual revenue or funding interested in the
sale, sublicensing, or commercial distribution of software that incorporates
this source code, please send inquiries to licensing (at) cycling74.com.

The above copyright notice and this license shall be included in all copies or
substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

Please see
https://support.cycling74.com/hc/en-us/articles/360050779193-Gen-Code-Export-Licensing-FAQ
for additional information

B) General Public License Version 3 (GPLv3)
Details of the GPLv3 license can be found at: https://www.gnu.org/licenses/gpl-3.0.html
****************************************************************************************/

// global noise generator
Noise noise;
static const int GENLIB_LOOPCOUNT_BAIL = 100000;


// The State struct contains all the state and procedures for the gendsp kernel
typedef struct State {
	CommonState __commonstate;
	Delay m_delay_3;
	Delay m_delay_4;
	int __exception;
	int vectorsize;
	t_sample m_damp_5;
	t_sample m_R_2;
	t_sample m_L_1;
	t_sample m_delay_6;
	t_sample samplerate;
	t_sample m_wetdry_7;
	// re-initialize all member variables;
	inline void reset(t_param __sr, int __vs) {
		__exception = 0;
		vectorsize = __vs;
		samplerate = __sr;
		m_L_1 = ((int)0);
		m_R_2 = ((int)0);
		m_delay_3.reset("m_delay_3", ((int)44100));
		m_delay_4.reset("m_delay_4", ((int)44100));
		m_damp_5 = ((t_sample)0.25);
		m_delay_6 = ((int)1000);
		m_wetdry_7 = ((t_sample)0.5);
		genlib_reset_complete(this);
		
	};
	// the signal processing routine;
	inline int perform(t_sample ** __ins, t_sample ** __outs, int __n) {
		vectorsize = __n;
		const t_sample * __in1 = __ins[0];
		const t_sample * __in2 = __ins[1];
		t_sample * __out1 = __outs[0];
		t_sample * __out2 = __outs[1];
		if (__exception) {
			return __exception;
			
		} else if (( (__in1 == 0) || (__in2 == 0) || (__out1 == 0) || (__out2 == 0) )) {
			__exception = GENLIB_ERR_NULL_BUFFER;
			return __exception;
			
		};
		t_sample clamp_327 = ((m_damp_5 <= ((int)0)) ? ((int)0) : ((m_damp_5 >= ((int)1)) ? ((int)1) : m_damp_5));
		t_sample clamp_328 = ((m_wetdry_7 <= ((int)0)) ? ((int)0) : ((m_wetdry_7 >= ((int)1)) ? ((int)1) : m_wetdry_7));
		int min_8 = (-1);
		int min_9 = (-1);
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			const t_sample in2 = (*(__in2++));
			t_sample tap_332 = m_delay_4.read_linear(m_delay_6);
			t_sample fold_330 = fold(tap_332, (-1), ((int)1));
			t_sample mix_348 = (fold_330 + (clamp_327 * (m_R_2 - fold_330)));
			t_sample mix_329 = mix_348;
			t_sample tap_340 = m_delay_3.read_linear(m_delay_6);
			t_sample fold_338 = fold(tap_340, (-1), ((int)1));
			t_sample mix_349 = (fold_338 + (clamp_327 * (m_L_1 - fold_338)));
			t_sample mix_333 = mix_349;
			t_sample mix_350 = (in2 + (clamp_328 * (mix_329 - in2)));
			t_sample clamp_336 = ((mix_350 <= min_8) ? min_8 : ((mix_350 >= ((int)1)) ? ((int)1) : mix_350));
			t_sample out2 = clamp_336;
			t_sample mix_351 = (in1 + (clamp_328 * (mix_333 - in1)));
			t_sample clamp_337 = ((mix_351 <= min_9) ? min_9 : ((mix_351 >= ((int)1)) ? ((int)1) : mix_351));
			t_sample out1 = clamp_337;
			t_sample R_next_341 = fixdenorm(mix_329);
			t_sample L_next_342 = fixdenorm(mix_333);
			m_delay_4.write((m_R_2 + in1));
			m_delay_3.write((m_L_1 + in1));
			m_R_2 = R_next_341;
			m_L_1 = L_next_342;
			m_delay_3.step();
			m_delay_4.step();
			// assign results to output buffer;
			(*(__out1++)) = out1;
			(*(__out2++)) = out2;
			
		};
		return __exception;
		
	};
	inline void set_damp(t_param _value) {
		m_damp_5 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_delay(t_param _value) {
		m_delay_6 = (_value < 0 ? 0 : (_value > 10000 ? 10000 : _value));
	};
	inline void set_wetdry(t_param _value) {
		m_wetdry_7 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	
} State;


///
///	Configuration for the genlib API
///

/// Number of signal inputs and outputs

int gen_kernel_numins = 2;
int gen_kernel_numouts = 2;

int num_inputs() { return gen_kernel_numins; }
int num_outputs() { return gen_kernel_numouts; }
int num_params() { return 3; }

/// Assistive lables for the signal inputs and outputs

const char *gen_kernel_innames[] = { "L", "R" };
const char *gen_kernel_outnames[] = { "out1", "out2" };

/// Invoke the signal process of a State object

int perform(CommonState *cself, t_sample **ins, long numins, t_sample **outs, long numouts, long n) {
	State* self = (State *)cself;
	return self->perform(ins, outs, n);
}

/// Reset all parameters and stateful operators of a State object

void reset(CommonState *cself) {
	State* self = (State *)cself;
	self->reset(cself->sr, cself->vs);
}

/// Set a parameter of a State object

void setparameter(CommonState *cself, long index, t_param value, void *ref) {
	State *self = (State *)cself;
	switch (index) {
		case 0: self->set_damp(value); break;
		case 1: self->set_delay(value); break;
		case 2: self->set_wetdry(value); break;
		
		default: break;
	}
}

/// Get the value of a parameter of a State object

void getparameter(CommonState *cself, long index, t_param *value) {
	State *self = (State *)cself;
	switch (index) {
		case 0: *value = self->m_damp_5; break;
		case 1: *value = self->m_delay_6; break;
		case 2: *value = self->m_wetdry_7; break;
		
		default: break;
	}
}

/// Get the name of a parameter of a State object

const char *getparametername(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].name;
	}
	return 0;
}

/// Get the minimum value of a parameter of a State object

t_param getparametermin(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].outputmin;
	}
	return 0;
}

/// Get the maximum value of a parameter of a State object

t_param getparametermax(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].outputmax;
	}
	return 0;
}

/// Get parameter of a State object has a minimum and maximum value

char getparameterhasminmax(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].hasminmax;
	}
	return 0;
}

/// Get the units of a parameter of a State object

const char *getparameterunits(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].units;
	}
	return 0;
}

/// Get the size of the state of all parameters of a State object

size_t getstatesize(CommonState *cself) {
	return genlib_getstatesize(cself, &getparameter);
}

/// Get the state of all parameters of a State object

short getstate(CommonState *cself, char *state) {
	return genlib_getstate(cself, state, &getparameter);
}

/// set the state of all parameters of a State object

short setstate(CommonState *cself, const char *state) {
	return genlib_setstate(cself, state, &setparameter);
}

/// Allocate and configure a new State object and it's internal CommonState:

void *create(t_param sr, long vs) {
	State *self = new State;
	self->reset(sr, vs);
	ParamInfo *pi;
	self->__commonstate.inputnames = gen_kernel_innames;
	self->__commonstate.outputnames = gen_kernel_outnames;
	self->__commonstate.numins = gen_kernel_numins;
	self->__commonstate.numouts = gen_kernel_numouts;
	self->__commonstate.sr = sr;
	self->__commonstate.vs = vs;
	self->__commonstate.params = (ParamInfo *)genlib_sysmem_newptr(3 * sizeof(ParamInfo));
	self->__commonstate.numparams = 3;
	// initialize parameter 0 ("m_damp_5")
	pi = self->__commonstate.params + 0;
	pi->name = "damp";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_damp_5;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_delay_6")
	pi = self->__commonstate.params + 1;
	pi->name = "delay";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_delay_6;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 10000;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 2 ("m_wetdry_7")
	pi = self->__commonstate.params + 2;
	pi->name = "wetdry";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_wetdry_7;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	
	return self;
}

/// Release all resources and memory used by a State object:

void destroy(CommonState *cself) {
	State *self = (State *)cself;
	genlib_sysmem_freeptr(cself->params);
		
	delete self;
}


} // delay::
