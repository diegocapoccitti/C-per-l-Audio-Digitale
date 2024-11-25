/*******************************************************************************************************************
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

For entities with UNDER $200k in annual revenue or funding, a license is hereby
granted, free of charge, for the sale, sublicensing, or commercial distribution
of software that incorporates this source code, for as long as the entity's
annual revenue remains below $200k annual revenue or funding.

For entities with OVER $200k in annual revenue or funding interested in the
sale, sublicensing, or commercial distribution of software that incorporates
this source code, please send inquiries to licensing@cycling74.com.

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
https://support.cycling74.com/hc/en-us/articles/10730637742483-RNBO-Export-Licensing-FAQ
for additional information

B) General Public License Version 3 (GPLv3)
Details of the GPLv3 license can be found at: https://www.gnu.org/licenses/gpl-3.0.html
*******************************************************************************************************************/

#include "RNBO_Common.h"
#include "RNBO_AudioSignal.h"

namespace RNBO {


#define trunc(x) ((Int)(x))

#if defined(__GNUC__) || defined(__clang__)
    #define RNBO_RESTRICT __restrict__
#elif defined(_MSC_VER)
    #define RNBO_RESTRICT __restrict
#endif

#define FIXEDSIZEARRAYINIT(...) { }

class rnbomatic : public PatcherInterfaceImpl {
public:

rnbomatic()
{
}

~rnbomatic()
{
}

rnbomatic* getTopLevelPatcher() {
    return this;
}

void cancelClockEvents()
{
    getEngine()->flushClockEvents(this, -1494586265, false);
}

template <typename T> void listquicksort(T& arr, T& sortindices, Int l, Int h, bool ascending) {
    if (l < h) {
        Int p = (Int)(this->listpartition(arr, sortindices, l, h, ascending));
        this->listquicksort(arr, sortindices, l, p - 1, ascending);
        this->listquicksort(arr, sortindices, p + 1, h, ascending);
    }
}

template <typename T> Int listpartition(T& arr, T& sortindices, Int l, Int h, bool ascending) {
    number x = arr[(Index)h];
    Int i = (Int)(l - 1);

    for (Int j = (Int)(l); j <= h - 1; j++) {
        bool asc = (bool)((bool)(ascending) && arr[(Index)j] <= x);
        bool desc = (bool)((bool)(!(bool)(ascending)) && arr[(Index)j] >= x);

        if ((bool)(asc) || (bool)(desc)) {
            i++;
            this->listswapelements(arr, i, j);
            this->listswapelements(sortindices, i, j);
        }
    }

    i++;
    this->listswapelements(arr, i, h);
    this->listswapelements(sortindices, i, h);
    return i;
}

template <typename T> void listswapelements(T& arr, Int a, Int b) {
    auto tmp = arr[(Index)a];
    arr[(Index)a] = arr[(Index)b];
    arr[(Index)b] = tmp;
}

inline number linearinterp(number frac, number x, number y) {
    return x + (y - x) * frac;
}

inline number cubicinterp(number a, number w, number x, number y, number z) {
    number a1 = 1. + a;
    number aa = a * a1;
    number b = 1. - a;
    number b1 = 2. - a;
    number bb = b * b1;
    number fw = -.1666667 * bb * a;
    number fx = .5 * bb * a1;
    number fy = .5 * aa * b1;
    number fz = -.1666667 * aa * b;
    return w * fw + x * fx + y * fy + z * fz;
}

inline number fastcubicinterp(number a, number w, number x, number y, number z) {
    number a2 = a * a;
    number f0 = z - y - w + x;
    number f1 = w - x - f0;
    number f2 = y - w;
    number f3 = x;
    return f0 * a * a2 + f1 * a2 + f2 * a + f3;
}

inline number splineinterp(number a, number w, number x, number y, number z) {
    number a2 = a * a;
    number f0 = -0.5 * w + 1.5 * x - 1.5 * y + 0.5 * z;
    number f1 = w - 2.5 * x + 2 * y - 0.5 * z;
    number f2 = -0.5 * w + 0.5 * y;
    return f0 * a * a2 + f1 * a2 + f2 * a + x;
}

inline number spline6interp(number a, number y0, number y1, number y2, number y3, number y4, number y5) {
    number ym2py2 = y0 + y4;
    number ym1py1 = y1 + y3;
    number y2mym2 = y4 - y0;
    number y1mym1 = y3 - y1;
    number sixthym1py1 = (number)1 / (number)6.0 * ym1py1;
    number c0 = (number)1 / (number)120.0 * ym2py2 + (number)13 / (number)60.0 * ym1py1 + (number)11 / (number)20.0 * y2;
    number c1 = (number)1 / (number)24.0 * y2mym2 + (number)5 / (number)12.0 * y1mym1;
    number c2 = (number)1 / (number)12.0 * ym2py2 + sixthym1py1 - (number)1 / (number)2.0 * y2;
    number c3 = (number)1 / (number)12.0 * y2mym2 - (number)1 / (number)6.0 * y1mym1;
    number c4 = (number)1 / (number)24.0 * ym2py2 - sixthym1py1 + (number)1 / (number)4.0 * y2;
    number c5 = (number)1 / (number)120.0 * (y5 - y0) + (number)1 / (number)24.0 * (y1 - y4) + (number)1 / (number)12.0 * (y3 - y2);
    return ((((c5 * a + c4) * a + c3) * a + c2) * a + c1) * a + c0;
}

inline number cosT8(number r) {
    number t84 = 56.0;
    number t83 = 1680.0;
    number t82 = 20160.0;
    number t81 = 2.4801587302e-05;
    number t73 = 42.0;
    number t72 = 840.0;
    number t71 = 1.9841269841e-04;

    if (r < 0.785398163397448309615660845819875721 && r > -0.785398163397448309615660845819875721) {
        number rr = r * r;
        return 1.0 - rr * t81 * (t82 - rr * (t83 - rr * (t84 - rr)));
    } else if (r > 0.0) {
        r -= 1.57079632679489661923132169163975144;
        number rr = r * r;
        return -r * (1.0 - t71 * rr * (t72 - rr * (t73 - rr)));
    } else {
        r += 1.57079632679489661923132169163975144;
        number rr = r * r;
        return r * (1.0 - t71 * rr * (t72 - rr * (t73 - rr)));
    }
}

inline number cosineinterp(number frac, number x, number y) {
    number a2 = (1.0 - this->cosT8(frac * 3.14159265358979323846)) / (number)2.0;
    return x * (1.0 - a2) + y * a2;
}

number mstosamps(MillisecondTime ms) {
    return ms * this->sr * 0.001;
}

number samplerate() const {
    return this->sr;
}

Index vectorsize() const {
    return this->vs;
}

number maximum(number x, number y) {
    return (x < y ? y : x);
}

MillisecondTime sampstoms(number samps) {
    return samps * 1000 / this->sr;
}

Index getNumMidiInputPorts() const {
    return 0;
}

void processMidiEvent(MillisecondTime , int , ConstByteArray , Index ) {}

Index getNumMidiOutputPorts() const {
    return 0;
}

void process(
    const SampleValue * const* inputs,
    Index numInputs,
    SampleValue * const* outputs,
    Index numOutputs,
    Index n
) {
    this->vs = n;
    this->updateTime(this->getEngine()->getCurrentTime());
    SampleValue * out1 = (numOutputs >= 1 && outputs[0] ? outputs[0] : this->dummyBuffer);
    const SampleValue * in1 = (numInputs >= 1 && inputs[0] ? inputs[0] : this->zeroBuffer);
    this->mstosamps_tilde_01_perform(this->mstosamps_tilde_01_ms, this->signals[0], n);
    this->vectorsize_tilde_01_perform(this->signals[1], n);
    this->numbertilde_01_perform(this->signals[1], this->dummyBuffer, n);
    this->feedbackreader_01_perform(this->signals[1], n);
    this->dspexpr_01_perform(this->signals[1], this->dspexpr_01_in2, this->signals[2], n);
    this->signaladder_01_perform(in1, this->signals[2], this->signals[2], n);
    this->delaytilde_01_perform(this->signals[0], this->signals[2], out1, n);
    this->feedbackwriter_01_perform(out1, n);
    this->stackprotect_perform(n);
    this->globaltransport_advance();
    this->audioProcessSampleCount += this->vs;
}

void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
    if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
        Index i;

        for (i = 0; i < 3; i++) {
            this->signals[i] = resizeSignal(this->signals[i], this->maxvs, maxBlockSize);
        }

        this->feedbacktilde_01_feedbackbuffer = resizeSignal(this->feedbacktilde_01_feedbackbuffer, this->maxvs, maxBlockSize);
        this->globaltransport_tempo = resizeSignal(this->globaltransport_tempo, this->maxvs, maxBlockSize);
        this->globaltransport_state = resizeSignal(this->globaltransport_state, this->maxvs, maxBlockSize);
        this->zeroBuffer = resizeSignal(this->zeroBuffer, this->maxvs, maxBlockSize);
        this->dummyBuffer = resizeSignal(this->dummyBuffer, this->maxvs, maxBlockSize);
        this->didAllocateSignals = true;
    }

    const bool sampleRateChanged = sampleRate != this->sr;
    const bool maxvsChanged = maxBlockSize != this->maxvs;
    const bool forceDSPSetup = sampleRateChanged || maxvsChanged || force;

    if (sampleRateChanged || maxvsChanged) {
        this->vs = maxBlockSize;
        this->maxvs = maxBlockSize;
        this->sr = sampleRate;
        this->invsr = 1 / sampleRate;
    }

    this->numbertilde_01_dspsetup(forceDSPSetup);
    this->delaytilde_01_dspsetup(forceDSPSetup);
    this->globaltransport_dspsetup(forceDSPSetup);

    if (sampleRateChanged)
        this->onSampleRateChanged(sampleRate);
}

void setProbingTarget(MessageTag id) {
    switch (id) {
    default:
        {
        this->setProbingIndex(-1);
        break;
        }
    }
}

void setProbingIndex(ProbingIndex ) {}

Index getProbingChannels(MessageTag outletId) const {
    RNBO_UNUSED(outletId);
    return 0;
}

DataRef* getDataRef(DataRefIndex index)  {
    switch (index) {
    case 0:
        {
        return addressOf(this->delaytilde_01_del_bufferobj);
        break;
        }
    default:
        {
        return nullptr;
        }
    }
}

DataRefIndex getNumDataRefs() const {
    return 1;
}

void fillDataRef(DataRefIndex , DataRef& ) {}

void zeroDataRef(DataRef& ref) {
    ref->setZero();
}

void processDataViewUpdate(DataRefIndex index, MillisecondTime time) {
    this->updateTime(time);

    if (index == 0) {
        this->delaytilde_01_del_buffer = new Float64Buffer(this->delaytilde_01_del_bufferobj);
    }
}

void initialize() {
    this->delaytilde_01_del_bufferobj = initDataRef("delaytilde_01_del_bufferobj", true, nullptr, "buffer~");
    this->assign_defaults();
    this->setState();
    this->delaytilde_01_del_bufferobj->setIndex(0);
    this->delaytilde_01_del_buffer = new Float64Buffer(this->delaytilde_01_del_bufferobj);
    this->initializeObjects();
    this->allocateDataRefs();
    this->startup();
}

Index getIsMuted()  {
    return this->isMuted;
}

void setIsMuted(Index v)  {
    this->isMuted = v;
}

void onSampleRateChanged(double ) {}

Index getPatcherSerial() const {
    return 0;
}

void getState(PatcherStateInterface& ) {}

void setState() {}

void getPreset(PatcherStateInterface& preset) {
    preset["__presetid"] = "rnbo";
    this->param_01_getPresetValue(getSubState(preset, "delaytime"));
    this->param_02_getPresetValue(getSubState(preset, "feedback"));
}

void setPreset(MillisecondTime time, PatcherStateInterface& preset) {
    this->updateTime(time);
    this->param_01_setPresetValue(getSubState(preset, "delaytime"));
    this->param_02_setPresetValue(getSubState(preset, "feedback"));
}

void setParameterValue(ParameterIndex index, ParameterValue v, MillisecondTime time) {
    this->updateTime(time);

    switch (index) {
    case 0:
        {
        this->param_01_value_set(v);
        break;
        }
    case 1:
        {
        this->param_02_value_set(v);
        break;
        }
    }
}

void processParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
    this->setParameterValue(index, value, time);
}

void processParameterBangEvent(ParameterIndex index, MillisecondTime time) {
    this->setParameterValue(index, this->getParameterValue(index), time);
}

void processNormalizedParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
    this->setParameterValueNormalized(index, value, time);
}

ParameterValue getParameterValue(ParameterIndex index)  {
    switch (index) {
    case 0:
        {
        return this->param_01_value;
        }
    case 1:
        {
        return this->param_02_value;
        }
    default:
        {
        return 0;
        }
    }
}

ParameterIndex getNumSignalInParameters() const {
    return 0;
}

ParameterIndex getNumSignalOutParameters() const {
    return 0;
}

ParameterIndex getNumParameters() const {
    return 2;
}

ConstCharPointer getParameterName(ParameterIndex index) const {
    switch (index) {
    case 0:
        {
        return "delaytime";
        }
    case 1:
        {
        return "feedback";
        }
    default:
        {
        return "bogus";
        }
    }
}

ConstCharPointer getParameterId(ParameterIndex index) const {
    switch (index) {
    case 0:
        {
        return "delaytime";
        }
    case 1:
        {
        return "feedback";
        }
    default:
        {
        return "bogus";
        }
    }
}

void getParameterInfo(ParameterIndex index, ParameterInfo * info) const {
    {
        switch (index) {
        case 0:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 220;
            info->min = 1;
            info->max = 2000;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 1:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0.5;
            info->min = 0;
            info->max = 0.999;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        }
    }
}

void sendParameter(ParameterIndex index, bool ignoreValue) {
    this->getEngine()->notifyParameterValueChanged(index, (ignoreValue ? 0 : this->getParameterValue(index)), ignoreValue);
}

ParameterValue applyStepsToNormalizedParameterValue(ParameterValue normalizedValue, int steps) const {
    if (steps == 1) {
        if (normalizedValue > 0) {
            normalizedValue = 1.;
        }
    } else {
        ParameterValue oneStep = (number)1. / (steps - 1);
        ParameterValue numberOfSteps = rnbo_fround(normalizedValue / oneStep * 1 / (number)1) * (number)1;
        normalizedValue = numberOfSteps * oneStep;
    }

    return normalizedValue;
}

ParameterValue convertToNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
    switch (index) {
    case 1:
        {
        {
            value = (value < 0 ? 0 : (value > 0.999 ? 0.999 : value));
            ParameterValue normalizedValue = (value - 0) / (0.999 - 0);
            return normalizedValue;
        }
        }
    case 0:
        {
        {
            value = (value < 1 ? 1 : (value > 2000 ? 2000 : value));
            ParameterValue normalizedValue = (value - 1) / (2000 - 1);
            return normalizedValue;
        }
        }
    default:
        {
        return value;
        }
    }
}

ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
    value = (value < 0 ? 0 : (value > 1 ? 1 : value));

    switch (index) {
    case 1:
        {
        {
            {
                return 0 + value * (0.999 - 0);
            }
        }
        }
    case 0:
        {
        {
            {
                return 1 + value * (2000 - 1);
            }
        }
        }
    default:
        {
        return value;
        }
    }
}

ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
    switch (index) {
    case 0:
        {
        return this->param_01_value_constrain(value);
        }
    case 1:
        {
        return this->param_02_value_constrain(value);
        }
    default:
        {
        return value;
        }
    }
}

void scheduleParamInit(ParameterIndex index, Index order) {
    this->paramInitIndices->push(index);
    this->paramInitOrder->push(order);
}

void processParamInitEvents() {
    this->listquicksort(
        this->paramInitOrder,
        this->paramInitIndices,
        0,
        (int)(this->paramInitOrder->length - 1),
        true
    );

    for (Index i = 0; i < this->paramInitOrder->length; i++) {
        this->getEngine()->scheduleParameterBang(this->paramInitIndices[i], 0);
    }
}

void processClockEvent(MillisecondTime time, ClockId index, bool hasValue, ParameterValue value) {
    RNBO_UNUSED(hasValue);
    this->updateTime(time);

    switch (index) {
    case -1494586265:
        {
        this->numbertilde_01_value_set(value);
        break;
        }
    }
}

void processOutletAtCurrentTime(EngineLink* , OutletIndex , ParameterValue ) {}

void processOutletEvent(
    EngineLink* sender,
    OutletIndex index,
    ParameterValue value,
    MillisecondTime time
) {
    this->updateTime(time);
    this->processOutletAtCurrentTime(sender, index, value);
}

void processNumMessage(MessageTag tag, MessageTag objectId, MillisecondTime time, number payload) {
    this->updateTime(time);

    switch (tag) {
    case TAG("sig"):
        {
        if (TAG("number~_obj-10") == objectId)
            this->numbertilde_01_sig_number_set(payload);

        break;
        }
    case TAG("mode"):
        {
        if (TAG("number~_obj-10") == objectId)
            this->numbertilde_01_mode_set(payload);

        break;
        }
    }
}

void processListMessage(
    MessageTag tag,
    MessageTag objectId,
    MillisecondTime time,
    const list& payload
) {
    this->updateTime(time);

    switch (tag) {
    case TAG("sig"):
        {
        if (TAG("number~_obj-10") == objectId)
            this->numbertilde_01_sig_list_set(payload);

        break;
        }
    }
}

void processBangMessage(MessageTag , MessageTag , MillisecondTime ) {}

MessageTagInfo resolveTag(MessageTag tag) const {
    switch (tag) {
    case TAG("monitor"):
        {
        return "monitor";
        }
    case TAG("number~_obj-10"):
        {
        return "number~_obj-10";
        }
    case TAG("assign"):
        {
        return "assign";
        }
    case TAG("setup"):
        {
        return "setup";
        }
    case TAG("sig"):
        {
        return "sig";
        }
    case TAG("mode"):
        {
        return "mode";
        }
    }

    return "";
}

MessageIndex getNumMessages() const {
    return 0;
}

const MessageInfo& getMessageInfo(MessageIndex index) const {
    switch (index) {

    }

    return NullMessageInfo;
}

protected:

void param_01_value_set(number v) {
    v = this->param_01_value_constrain(v);
    this->param_01_value = v;
    this->sendParameter(0, false);

    if (this->param_01_value != this->param_01_lastValue) {
        this->getEngine()->presetTouched();
        this->param_01_lastValue = this->param_01_value;
    }

    this->mstosamps_tilde_01_ms_set(v);
}

void param_02_value_set(number v) {
    v = this->param_02_value_constrain(v);
    this->param_02_value = v;
    this->sendParameter(1, false);

    if (this->param_02_value != this->param_02_lastValue) {
        this->getEngine()->presetTouched();
        this->param_02_lastValue = this->param_02_value;
    }

    this->dspexpr_01_in2_set(v);
}

void numbertilde_01_sig_number_set(number v) {
    this->numbertilde_01_outValue = v;
}

void numbertilde_01_sig_list_set(const list& v) {
    this->numbertilde_01_outValue = v[0];
}

void numbertilde_01_mode_set(number v) {
    if (v == 1) {
        this->numbertilde_01_currentMode = 0;
    } else if (v == 2) {
        this->numbertilde_01_currentMode = 1;
    }
}

void numbertilde_01_value_set(number ) {}

number msToSamps(MillisecondTime ms, number sampleRate) {
    return ms * sampleRate * 0.001;
}

MillisecondTime sampsToMs(SampleIndex samps) {
    return samps * (this->invsr * 1000);
}

Index getMaxBlockSize() const {
    return this->maxvs;
}

number getSampleRate() const {
    return this->sr;
}

bool hasFixedVectorSize() const {
    return false;
}

Index getNumInputChannels() const {
    return 1;
}

Index getNumOutputChannels() const {
    return 1;
}

void allocateDataRefs() {
    this->delaytilde_01_del_buffer = this->delaytilde_01_del_buffer->allocateIfNeeded();

    if (this->delaytilde_01_del_bufferobj->hasRequestedSize()) {
        if (this->delaytilde_01_del_bufferobj->wantsFill())
            this->zeroDataRef(this->delaytilde_01_del_bufferobj);

        this->getEngine()->sendDataRefUpdated(0);
    }
}

void initializeObjects() {
    this->delaytilde_01_del_init();
    this->numbertilde_01_init();
}

void sendOutlet(OutletIndex index, ParameterValue value) {
    this->getEngine()->sendOutlet(this, index, value);
}

void startup() {
    this->updateTime(this->getEngine()->getCurrentTime());

    {
        this->scheduleParamInit(0, 0);
    }

    {
        this->scheduleParamInit(1, 0);
    }

    this->processParamInitEvents();
}

number param_01_value_constrain(number v) const {
    v = (v > 2000 ? 2000 : (v < 1 ? 1 : v));
    return v;
}

void mstosamps_tilde_01_ms_set(number v) {
    this->mstosamps_tilde_01_ms = v;
}

number param_02_value_constrain(number v) const {
    v = (v > 0.999 ? 0.999 : (v < 0 ? 0 : v));
    return v;
}

void dspexpr_01_in2_set(number v) {
    this->dspexpr_01_in2 = v;
}

void mstosamps_tilde_01_perform(number ms, SampleValue * out1, Index n) {
    Index i;

    for (i = 0; i < n; i++) {
        out1[(Index)i] = ms * this->sr * 0.001;
    }
}

void vectorsize_tilde_01_perform(SampleValue * out1, Index n) {
    Index i;

    for (i = 0; i < n; i++) {
        out1[(Index)i] = this->vs;
    }
}

void numbertilde_01_perform(const SampleValue * input_signal, SampleValue * output, Index n) {
    auto __numbertilde_01_currentIntervalInSamples = this->numbertilde_01_currentIntervalInSamples;
    auto __numbertilde_01_lastValue = this->numbertilde_01_lastValue;
    auto __numbertilde_01_currentInterval = this->numbertilde_01_currentInterval;
    auto __numbertilde_01_rampInSamples = this->numbertilde_01_rampInSamples;
    auto __numbertilde_01_outValue = this->numbertilde_01_outValue;
    auto __numbertilde_01_currentMode = this->numbertilde_01_currentMode;
    number monitorvalue = input_signal[0];

    for (Index i = 0; i < n; i++) {
        if (__numbertilde_01_currentMode == 0) {
            output[(Index)i] = this->numbertilde_01_smooth_next(
                __numbertilde_01_outValue,
                __numbertilde_01_rampInSamples,
                __numbertilde_01_rampInSamples
            );
        } else {
            output[(Index)i] = input_signal[(Index)i];
        }
    }

    __numbertilde_01_currentInterval -= n;

    if (monitorvalue != __numbertilde_01_lastValue && __numbertilde_01_currentInterval <= 0) {
        __numbertilde_01_currentInterval = __numbertilde_01_currentIntervalInSamples;

        this->getEngine()->scheduleClockEventWithValue(
            this,
            -1494586265,
            this->sampsToMs((SampleIndex)(this->vs)) + this->_currentTime,
            monitorvalue
        );;

        __numbertilde_01_lastValue = monitorvalue;
        this->getEngine()->sendListMessage(TAG("monitor"), TAG("number~_obj-10"), {monitorvalue}, this->_currentTime);;
    }

    this->numbertilde_01_currentInterval = __numbertilde_01_currentInterval;
    this->numbertilde_01_lastValue = __numbertilde_01_lastValue;
}

void feedbackreader_01_perform(SampleValue * output, Index n) {
    auto& buffer = this->feedbacktilde_01_feedbackbuffer;

    for (Index i = 0; i < n; i++) {
        output[(Index)i] = buffer[(Index)i];
    }
}

void dspexpr_01_perform(const Sample * in1, number in2, SampleValue * out1, Index n) {
    Index i;

    for (i = 0; i < n; i++) {
        out1[(Index)i] = in1[(Index)i] * in2;//#map:_###_obj_###_:1
    }
}

void signaladder_01_perform(
    const SampleValue * in1,
    const SampleValue * in2,
    SampleValue * out,
    Index n
) {
    Index i;

    for (i = 0; i < n; i++) {
        out[(Index)i] = in1[(Index)i] + in2[(Index)i];
    }
}

void delaytilde_01_perform(
    const Sample * delay,
    const SampleValue * input,
    SampleValue * output,
    Index n
) {
    auto __delaytilde_01_crossfadeDelay = this->delaytilde_01_crossfadeDelay;
    auto __delaytilde_01_rampInSamples = this->delaytilde_01_rampInSamples;
    auto __delaytilde_01_ramp = this->delaytilde_01_ramp;
    auto __delaytilde_01_lastDelay = this->delaytilde_01_lastDelay;

    for (Index i = 0; i < n; i++) {
        if (__delaytilde_01_lastDelay == -1) {
            __delaytilde_01_lastDelay = delay[(Index)i];
        }

        if (__delaytilde_01_ramp > 0) {
            number factor = __delaytilde_01_ramp / __delaytilde_01_rampInSamples;
            output[(Index)i] = this->delaytilde_01_del_read(__delaytilde_01_crossfadeDelay, 0) * factor + this->delaytilde_01_del_read(__delaytilde_01_lastDelay, 0) * (1. - factor);
            __delaytilde_01_ramp--;
        } else {
            number effectiveDelay = delay[(Index)i];

            if (effectiveDelay != __delaytilde_01_lastDelay) {
                __delaytilde_01_ramp = __delaytilde_01_rampInSamples;
                __delaytilde_01_crossfadeDelay = __delaytilde_01_lastDelay;
                __delaytilde_01_lastDelay = effectiveDelay;
                output[(Index)i] = this->delaytilde_01_del_read(__delaytilde_01_crossfadeDelay, 0);
                __delaytilde_01_ramp--;
            } else {
                output[(Index)i] = this->delaytilde_01_del_read(effectiveDelay, 0);
            }
        }

        this->delaytilde_01_del_write(input[(Index)i]);
        this->delaytilde_01_del_step();
    }

    this->delaytilde_01_lastDelay = __delaytilde_01_lastDelay;
    this->delaytilde_01_ramp = __delaytilde_01_ramp;
    this->delaytilde_01_crossfadeDelay = __delaytilde_01_crossfadeDelay;
}

void feedbackwriter_01_perform(const SampleValue * input, Index n) {
    auto& buffer = this->feedbacktilde_01_feedbackbuffer;

    for (Index i = 0; i < n; i++) {
        buffer[(Index)i] = input[(Index)i];
    }
}

void stackprotect_perform(Index n) {
    RNBO_UNUSED(n);
    auto __stackprotect_count = this->stackprotect_count;
    __stackprotect_count = 0;
    this->stackprotect_count = __stackprotect_count;
}

void delaytilde_01_del_step() {
    this->delaytilde_01_del_reader++;

    if (this->delaytilde_01_del_reader >= (int)(this->delaytilde_01_del_buffer->getSize()))
        this->delaytilde_01_del_reader = 0;
}

number delaytilde_01_del_read(number size, Int interp) {
    if (interp == 0) {
        number r = (int)(this->delaytilde_01_del_buffer->getSize()) + this->delaytilde_01_del_reader - ((size > this->delaytilde_01_del__maxdelay ? this->delaytilde_01_del__maxdelay : (size < (this->delaytilde_01_del_reader != this->delaytilde_01_del_writer) ? this->delaytilde_01_del_reader != this->delaytilde_01_del_writer : size)));
        long index1 = (long)(rnbo_floor(r));
        number frac = r - index1;
        long index2 = (long)(index1 + 1);

        return this->linearinterp(frac, this->delaytilde_01_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->delaytilde_01_del_wrap))
        ), this->delaytilde_01_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->delaytilde_01_del_wrap))
        ));
    } else if (interp == 1) {
        number r = (int)(this->delaytilde_01_del_buffer->getSize()) + this->delaytilde_01_del_reader - ((size > this->delaytilde_01_del__maxdelay ? this->delaytilde_01_del__maxdelay : (size < (1 + this->delaytilde_01_del_reader != this->delaytilde_01_del_writer) ? 1 + this->delaytilde_01_del_reader != this->delaytilde_01_del_writer : size)));
        long index1 = (long)(rnbo_floor(r));
        number frac = r - index1;
        Index index2 = (Index)(index1 + 1);
        Index index3 = (Index)(index2 + 1);
        Index index4 = (Index)(index3 + 1);

        return this->cubicinterp(frac, this->delaytilde_01_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->delaytilde_01_del_wrap))
        ), this->delaytilde_01_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->delaytilde_01_del_wrap))
        ), this->delaytilde_01_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->delaytilde_01_del_wrap))
        ), this->delaytilde_01_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->delaytilde_01_del_wrap))
        ));
    } else if (interp == 6) {
        number r = (int)(this->delaytilde_01_del_buffer->getSize()) + this->delaytilde_01_del_reader - ((size > this->delaytilde_01_del__maxdelay ? this->delaytilde_01_del__maxdelay : (size < (1 + this->delaytilde_01_del_reader != this->delaytilde_01_del_writer) ? 1 + this->delaytilde_01_del_reader != this->delaytilde_01_del_writer : size)));
        long index1 = (long)(rnbo_floor(r));
        number frac = r - index1;
        Index index2 = (Index)(index1 + 1);
        Index index3 = (Index)(index2 + 1);
        Index index4 = (Index)(index3 + 1);

        return this->fastcubicinterp(frac, this->delaytilde_01_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->delaytilde_01_del_wrap))
        ), this->delaytilde_01_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->delaytilde_01_del_wrap))
        ), this->delaytilde_01_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->delaytilde_01_del_wrap))
        ), this->delaytilde_01_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->delaytilde_01_del_wrap))
        ));
    } else if (interp == 2) {
        number r = (int)(this->delaytilde_01_del_buffer->getSize()) + this->delaytilde_01_del_reader - ((size > this->delaytilde_01_del__maxdelay ? this->delaytilde_01_del__maxdelay : (size < (1 + this->delaytilde_01_del_reader != this->delaytilde_01_del_writer) ? 1 + this->delaytilde_01_del_reader != this->delaytilde_01_del_writer : size)));
        long index1 = (long)(rnbo_floor(r));
        number frac = r - index1;
        Index index2 = (Index)(index1 + 1);
        Index index3 = (Index)(index2 + 1);
        Index index4 = (Index)(index3 + 1);

        return this->splineinterp(frac, this->delaytilde_01_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->delaytilde_01_del_wrap))
        ), this->delaytilde_01_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->delaytilde_01_del_wrap))
        ), this->delaytilde_01_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->delaytilde_01_del_wrap))
        ), this->delaytilde_01_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->delaytilde_01_del_wrap))
        ));
    } else if (interp == 7) {
        number r = (int)(this->delaytilde_01_del_buffer->getSize()) + this->delaytilde_01_del_reader - ((size > this->delaytilde_01_del__maxdelay ? this->delaytilde_01_del__maxdelay : (size < (1 + this->delaytilde_01_del_reader != this->delaytilde_01_del_writer) ? 1 + this->delaytilde_01_del_reader != this->delaytilde_01_del_writer : size)));
        long index1 = (long)(rnbo_floor(r));
        number frac = r - index1;
        Index index2 = (Index)(index1 + 1);
        Index index3 = (Index)(index2 + 1);
        Index index4 = (Index)(index3 + 1);
        Index index5 = (Index)(index4 + 1);
        Index index6 = (Index)(index5 + 1);

        return this->spline6interp(frac, this->delaytilde_01_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->delaytilde_01_del_wrap))
        ), this->delaytilde_01_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->delaytilde_01_del_wrap))
        ), this->delaytilde_01_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index3 & (BinOpInt)this->delaytilde_01_del_wrap))
        ), this->delaytilde_01_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index4 & (BinOpInt)this->delaytilde_01_del_wrap))
        ), this->delaytilde_01_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index5 & (BinOpInt)this->delaytilde_01_del_wrap))
        ), this->delaytilde_01_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index6 & (BinOpInt)this->delaytilde_01_del_wrap))
        ));
    } else if (interp == 3) {
        number r = (int)(this->delaytilde_01_del_buffer->getSize()) + this->delaytilde_01_del_reader - ((size > this->delaytilde_01_del__maxdelay ? this->delaytilde_01_del__maxdelay : (size < (this->delaytilde_01_del_reader != this->delaytilde_01_del_writer) ? this->delaytilde_01_del_reader != this->delaytilde_01_del_writer : size)));
        long index1 = (long)(rnbo_floor(r));
        number frac = r - index1;
        Index index2 = (Index)(index1 + 1);

        return this->cosineinterp(frac, this->delaytilde_01_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->delaytilde_01_del_wrap))
        ), this->delaytilde_01_del_buffer->getSample(
            0,
            (Index)((BinOpInt)((BinOpInt)index2 & (BinOpInt)this->delaytilde_01_del_wrap))
        ));
    }

    number r = (int)(this->delaytilde_01_del_buffer->getSize()) + this->delaytilde_01_del_reader - ((size > this->delaytilde_01_del__maxdelay ? this->delaytilde_01_del__maxdelay : (size < (this->delaytilde_01_del_reader != this->delaytilde_01_del_writer) ? this->delaytilde_01_del_reader != this->delaytilde_01_del_writer : size)));
    long index1 = (long)(rnbo_floor(r));

    return this->delaytilde_01_del_buffer->getSample(
        0,
        (Index)((BinOpInt)((BinOpInt)index1 & (BinOpInt)this->delaytilde_01_del_wrap))
    );
}

void delaytilde_01_del_write(number v) {
    this->delaytilde_01_del_writer = this->delaytilde_01_del_reader;
    this->delaytilde_01_del_buffer[(Index)this->delaytilde_01_del_writer] = v;
}

number delaytilde_01_del_next(number v, int size) {
    number effectiveSize = (size == -1 ? this->delaytilde_01_del__maxdelay : size);
    number val = this->delaytilde_01_del_read(effectiveSize, 0);
    this->delaytilde_01_del_write(v);
    this->delaytilde_01_del_step();
    return val;
}

array<Index, 2> delaytilde_01_del_calcSizeInSamples() {
    number sizeInSamples = 0;
    Index allocatedSizeInSamples = 0;

    {
        sizeInSamples = this->delaytilde_01_del_evaluateSizeExpr(this->samplerate(), this->vectorsize());
        this->delaytilde_01_del_sizemode = 0;
    }

    sizeInSamples = rnbo_floor(sizeInSamples);
    sizeInSamples = this->maximum(sizeInSamples, 2);
    allocatedSizeInSamples = (Index)(sizeInSamples);
    allocatedSizeInSamples = nextpoweroftwo(allocatedSizeInSamples);
    return {sizeInSamples, allocatedSizeInSamples};
}

void delaytilde_01_del_init() {
    auto result = this->delaytilde_01_del_calcSizeInSamples();
    this->delaytilde_01_del__maxdelay = result[0];
    Index requestedSizeInSamples = (Index)(result[1]);
    this->delaytilde_01_del_buffer->requestSize(requestedSizeInSamples, 1);
    this->delaytilde_01_del_wrap = requestedSizeInSamples - 1;
}

void delaytilde_01_del_clear() {
    this->delaytilde_01_del_buffer->setZero();
}

void delaytilde_01_del_reset() {
    auto result = this->delaytilde_01_del_calcSizeInSamples();
    this->delaytilde_01_del__maxdelay = result[0];
    Index allocatedSizeInSamples = (Index)(result[1]);
    this->delaytilde_01_del_buffer->setSize(allocatedSizeInSamples);
    updateDataRef(this, this->delaytilde_01_del_buffer);
    this->delaytilde_01_del_wrap = this->delaytilde_01_del_buffer->getSize() - 1;
    this->delaytilde_01_del_clear();

    if (this->delaytilde_01_del_reader >= this->delaytilde_01_del__maxdelay || this->delaytilde_01_del_writer >= this->delaytilde_01_del__maxdelay) {
        this->delaytilde_01_del_reader = 0;
        this->delaytilde_01_del_writer = 0;
    }
}

void delaytilde_01_del_dspsetup() {
    this->delaytilde_01_del_reset();
}

number delaytilde_01_del_evaluateSizeExpr(number samplerate, number vectorsize) {
    RNBO_UNUSED(vectorsize);
    return samplerate * 2;
}

number delaytilde_01_del_size() {
    return this->delaytilde_01_del__maxdelay;
}

void delaytilde_01_dspsetup(bool force) {
    if ((bool)(this->delaytilde_01_setupDone) && (bool)(!(bool)(force)))
        return;

    this->delaytilde_01_rampInSamples = (long)(this->mstosamps(50));
    this->delaytilde_01_lastDelay = -1;
    this->delaytilde_01_setupDone = true;
    this->delaytilde_01_del_dspsetup();
}

void param_01_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_01_value;
}

void param_01_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_01_value_set(preset["value"]);
}

void param_02_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_02_value;
}

void param_02_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_02_value_set(preset["value"]);
}

number numbertilde_01_smooth_d_next(number x) {
    number temp = (number)(x - this->numbertilde_01_smooth_d_prev);
    this->numbertilde_01_smooth_d_prev = x;
    return temp;
}

void numbertilde_01_smooth_d_dspsetup() {
    this->numbertilde_01_smooth_d_reset();
}

void numbertilde_01_smooth_d_reset() {
    this->numbertilde_01_smooth_d_prev = 0;
}

number numbertilde_01_smooth_next(number x, number up, number down) {
    if (this->numbertilde_01_smooth_d_next(x) != 0.) {
        if (x > this->numbertilde_01_smooth_prev) {
            number _up = up;

            if (_up < 1)
                _up = 1;

            this->numbertilde_01_smooth_index = _up;
            this->numbertilde_01_smooth_increment = (x - this->numbertilde_01_smooth_prev) / _up;
        } else if (x < this->numbertilde_01_smooth_prev) {
            number _down = down;

            if (_down < 1)
                _down = 1;

            this->numbertilde_01_smooth_index = _down;
            this->numbertilde_01_smooth_increment = (x - this->numbertilde_01_smooth_prev) / _down;
        }
    }

    if (this->numbertilde_01_smooth_index > 0) {
        this->numbertilde_01_smooth_prev += this->numbertilde_01_smooth_increment;
        this->numbertilde_01_smooth_index -= 1;
    } else {
        this->numbertilde_01_smooth_prev = x;
    }

    return this->numbertilde_01_smooth_prev;
}

void numbertilde_01_smooth_reset() {
    this->numbertilde_01_smooth_prev = 0;
    this->numbertilde_01_smooth_index = 0;
    this->numbertilde_01_smooth_increment = 0;
    this->numbertilde_01_smooth_d_reset();
}

void numbertilde_01_init() {
    this->numbertilde_01_currentMode = 1;
    this->getEngine()->sendNumMessage(TAG("setup"), TAG("number~_obj-10"), 1, this->_currentTime);
}

void numbertilde_01_dspsetup(bool force) {
    if ((bool)(this->numbertilde_01_setupDone) && (bool)(!(bool)(force)))
        return;

    this->numbertilde_01_currentIntervalInSamples = this->mstosamps(100);
    this->numbertilde_01_currentInterval = this->numbertilde_01_currentIntervalInSamples;
    this->numbertilde_01_rampInSamples = this->mstosamps(this->numbertilde_01_ramp);
    this->numbertilde_01_setupDone = true;
    this->numbertilde_01_smooth_d_dspsetup();
}

void globaltransport_advance() {}

void globaltransport_dspsetup(bool ) {}

bool stackprotect_check() {
    this->stackprotect_count++;

    if (this->stackprotect_count > 128) {
        console->log("STACK OVERFLOW DETECTED - stopped processing branch !");
        return true;
    }

    return false;
}

void updateTime(MillisecondTime time) {
    this->_currentTime = time;
    this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(rnbo_fround(this->msToSamps(time - this->getEngine()->getCurrentTime(), this->sr)));

    if (this->sampleOffsetIntoNextAudioBuffer >= (SampleIndex)(this->vs))
        this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(this->vs) - 1;

    if (this->sampleOffsetIntoNextAudioBuffer < 0)
        this->sampleOffsetIntoNextAudioBuffer = 0;
}

void assign_defaults()
{
    delaytilde_01_delay = 0;
    param_01_value = 220;
    dspexpr_01_in1 = 0;
    dspexpr_01_in2 = 0;
    param_02_value = 0.5;
    mstosamps_tilde_01_ms = 0;
    numbertilde_01_input_number = 0;
    numbertilde_01_ramp = 0;
    _currentTime = 0;
    audioProcessSampleCount = 0;
    sampleOffsetIntoNextAudioBuffer = 0;
    zeroBuffer = nullptr;
    dummyBuffer = nullptr;
    signals[0] = nullptr;
    signals[1] = nullptr;
    signals[2] = nullptr;
    didAllocateSignals = 0;
    vs = 0;
    maxvs = 0;
    sr = 44100;
    invsr = 0.00002267573696;
    delaytilde_01_lastDelay = -1;
    delaytilde_01_crossfadeDelay = 0;
    delaytilde_01_ramp = 0;
    delaytilde_01_rampInSamples = 0;
    delaytilde_01_del__maxdelay = 0;
    delaytilde_01_del_sizemode = 0;
    delaytilde_01_del_wrap = 0;
    delaytilde_01_del_reader = 0;
    delaytilde_01_del_writer = 0;
    delaytilde_01_setupDone = false;
    param_01_lastValue = 0;
    feedbacktilde_01_feedbackbuffer = nullptr;
    param_02_lastValue = 0;
    numbertilde_01_currentInterval = 0;
    numbertilde_01_currentIntervalInSamples = 0;
    numbertilde_01_lastValue = 0;
    numbertilde_01_outValue = 0;
    numbertilde_01_rampInSamples = 0;
    numbertilde_01_currentMode = 0;
    numbertilde_01_smooth_d_prev = 0;
    numbertilde_01_smooth_prev = 0;
    numbertilde_01_smooth_index = 0;
    numbertilde_01_smooth_increment = 0;
    numbertilde_01_setupDone = false;
    globaltransport_tempo = nullptr;
    globaltransport_state = nullptr;
    stackprotect_count = 0;
    _voiceIndex = 0;
    _noteNumber = 0;
    isMuted = 1;
}

// member variables

    number delaytilde_01_delay;
    number param_01_value;
    number dspexpr_01_in1;
    number dspexpr_01_in2;
    number param_02_value;
    number mstosamps_tilde_01_ms;
    number numbertilde_01_input_number;
    number numbertilde_01_ramp;
    MillisecondTime _currentTime;
    UInt64 audioProcessSampleCount;
    SampleIndex sampleOffsetIntoNextAudioBuffer;
    signal zeroBuffer;
    signal dummyBuffer;
    SampleValue * signals[3];
    bool didAllocateSignals;
    Index vs;
    Index maxvs;
    number sr;
    number invsr;
    number delaytilde_01_lastDelay;
    number delaytilde_01_crossfadeDelay;
    number delaytilde_01_ramp;
    long delaytilde_01_rampInSamples;
    Float64BufferRef delaytilde_01_del_buffer;
    Index delaytilde_01_del__maxdelay;
    Int delaytilde_01_del_sizemode;
    Index delaytilde_01_del_wrap;
    Int delaytilde_01_del_reader;
    Int delaytilde_01_del_writer;
    bool delaytilde_01_setupDone;
    number param_01_lastValue;
    signal feedbacktilde_01_feedbackbuffer;
    number param_02_lastValue;
    SampleIndex numbertilde_01_currentInterval;
    SampleIndex numbertilde_01_currentIntervalInSamples;
    number numbertilde_01_lastValue;
    number numbertilde_01_outValue;
    number numbertilde_01_rampInSamples;
    Int numbertilde_01_currentMode;
    number numbertilde_01_smooth_d_prev;
    number numbertilde_01_smooth_prev;
    number numbertilde_01_smooth_index;
    number numbertilde_01_smooth_increment;
    bool numbertilde_01_setupDone;
    signal globaltransport_tempo;
    signal globaltransport_state;
    number stackprotect_count;
    DataRef delaytilde_01_del_bufferobj;
    Index _voiceIndex;
    Int _noteNumber;
    Index isMuted;
    indexlist paramInitIndices;
    indexlist paramInitOrder;

};

PatcherInterface* creaternbomatic()
{
    return new rnbomatic();
}

#ifndef RNBO_NO_PATCHERFACTORY

extern "C" PatcherFactoryFunctionPtr GetPatcherFactoryFunction(PlatformInterface* platformInterface)
#else

extern "C" PatcherFactoryFunctionPtr rnbomaticFactoryFunction(PlatformInterface* platformInterface)
#endif

{
    Platform::set(platformInterface);
    return creaternbomatic;
}

} // end RNBO namespace

