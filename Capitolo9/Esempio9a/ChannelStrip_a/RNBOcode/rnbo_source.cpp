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

class RNBOSubpatcher_13 : public PatcherInterfaceImpl {
    
    friend class rnbomatic;
    
    public:
    
    RNBOSubpatcher_13()
    {
    }
    
    ~RNBOSubpatcher_13()
    {
    }
    
    virtual rnbomatic* getPatcher() const {
        return static_cast<rnbomatic *>(_parentPatcher);
    }
    
    rnbomatic* getTopLevelPatcher() {
        return this->getPatcher()->getTopLevelPatcher();
    }
    
    void cancelClockEvents()
    {
    }
    
    inline number safesqrt(number num) {
        return (num > 0.0 ? rnbo_sqrt(num) : 0.0);
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
        SampleValue * out2 = (numOutputs >= 2 && outputs[1] ? outputs[1] : this->dummyBuffer);
        const SampleValue * in1 = (numInputs >= 1 && inputs[0] ? inputs[0] : this->zeroBuffer);
        this->dspexpr_03_perform(this->dspexpr_03_in1, this->signals[0], n);
        this->dspexpr_02_perform(in1, this->signals[0], this->signals[1], n);
    
        this->average_rms_tilde_01_perform(
            this->signals[1],
            this->average_rms_tilde_01_windowSize,
            this->average_rms_tilde_01_reset,
            this->signals[0],
            n
        );
    
        this->dspexpr_07_perform(this->signals[0], this->signals[2], n);
        this->dspexpr_06_perform(this->signals[2], this->dspexpr_06_in2, this->signals[0], n);
        this->dspexpr_12_perform(this->dspexpr_12_in1, this->signals[2], this->signals[3], n);
        this->mstosamps_tilde_01_perform(this->mstosamps_tilde_01_ms, this->signals[2], n);
        this->mstosamps_tilde_02_perform(this->mstosamps_tilde_02_ms, this->signals[4], n);
        this->dspexpr_13_perform(this->dspexpr_13_in1, this->signals[5], n);
        this->dspexpr_15_perform(this->signals[5], this->dspexpr_15_in2, this->signals[6], n);
        this->dspexpr_14_perform(this->signals[6], this->dspexpr_14_in2, this->signals[5], n);
        this->dspexpr_11_perform(this->signals[3], this->signals[5], this->signals[6], n);
        this->dspexpr_10_perform(this->signals[6], this->signals[5], n);
        this->dspexpr_08_perform(this->signals[5], this->dspexpr_08_in2, this->signals[6], n);
        this->dspexpr_09_perform(this->signals[6], this->dspexpr_09_in2, this->signals[5], n);
        this->dspexpr_05_perform(this->signals[0], this->signals[5], this->signals[6], n);
        this->dspexpr_04_perform(this->signals[6], this->dspexpr_04_in2, this->signals[5], n);
        this->rampsmooth_tilde_01_perform(this->signals[5], this->signals[2], this->signals[4], this->signals[6], n);
        this->dspexpr_01_perform(this->signals[1], this->signals[6], out1, n);
        this->signalforwarder_01_perform(this->signals[6], out2, n);
        this->stackprotect_perform(n);
        this->audioProcessSampleCount += this->vs;
    }
    
    void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
        if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
            Index i;
    
            for (i = 0; i < 7; i++) {
                this->signals[i] = resizeSignal(this->signals[i], this->maxvs, maxBlockSize);
            }
    
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
    
        this->average_rms_tilde_01_dspsetup(forceDSPSetup);
        this->rampsmooth_tilde_01_dspsetup(forceDSPSetup);
    
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
    
    void getPreset(PatcherStateInterface& ) {}
    
    void setParameterValue(ParameterIndex , ParameterValue , MillisecondTime ) {}
    
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
        return 0;
    }
    
    ConstCharPointer getParameterName(ParameterIndex index) const {
        switch (index) {
        default:
            {
            return "bogus";
            }
        }
    }
    
    ConstCharPointer getParameterId(ParameterIndex index) const {
        switch (index) {
        default:
            {
            return "bogus";
            }
        }
    }
    
    void getParameterInfo(ParameterIndex , ParameterInfo * ) const {}
    
    void sendParameter(ParameterIndex index, bool ignoreValue) {
        this->getPatcher()->sendParameter(index + this->parameterOffset, ignoreValue);
    }
    
    void setParameterOffset(ParameterIndex offset) {
        this->parameterOffset = offset;
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
        default:
            {
            return value;
            }
        }
    }
    
    ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
        value = (value < 0 ? 0 : (value > 1 ? 1 : value));
    
        switch (index) {
        default:
            {
            return value;
            }
        }
    }
    
    ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
        switch (index) {
        default:
            {
            return value;
            }
        }
    }
    
    void scheduleParamInit(ParameterIndex index, Index order) {
        this->getPatcher()->scheduleParamInit(index + this->parameterOffset, order);
    }
    
    void processClockEvent(MillisecondTime , ClockId , bool , ParameterValue ) {}
    
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
        case TAG("valin"):
            {
            if (TAG("compressor[1]/number_obj-62") == objectId)
                this->numberobj_01_valin_set(payload);
    
            if (TAG("compressor[1]/flonum[2]") == objectId)
                this->numberobj_02_valin_set(payload);
    
            if (TAG("compressor[1]/flonum[3]") == objectId)
                this->numberobj_03_valin_set(payload);
    
            if (TAG("compressor[1]/flonum") == objectId)
                this->numberobj_04_valin_set(payload);
    
            if (TAG("compressor[1]/flonum[1]") == objectId)
                this->numberobj_05_valin_set(payload);
    
            break;
            }
        case TAG("format"):
            {
            if (TAG("compressor[1]/number_obj-62") == objectId)
                this->numberobj_01_format_set(payload);
    
            if (TAG("compressor[1]/flonum[2]") == objectId)
                this->numberobj_02_format_set(payload);
    
            if (TAG("compressor[1]/flonum[3]") == objectId)
                this->numberobj_03_format_set(payload);
    
            if (TAG("compressor[1]/flonum") == objectId)
                this->numberobj_04_format_set(payload);
    
            if (TAG("compressor[1]/flonum[1]") == objectId)
                this->numberobj_05_format_set(payload);
    
            break;
            }
        }
    }
    
    void processListMessage(MessageTag , MessageTag , MillisecondTime , const list& ) {}
    
    void processBangMessage(MessageTag , MessageTag , MillisecondTime ) {}
    
    MessageTagInfo resolveTag(MessageTag tag) const {
        switch (tag) {
        case TAG("valout"):
            {
            return "valout";
            }
        case TAG("compressor[1]/number_obj-62"):
            {
            return "compressor[1]/number_obj-62";
            }
        case TAG("setup"):
            {
            return "setup";
            }
        case TAG("compressor[1]/flonum[2]"):
            {
            return "compressor[1]/flonum[2]";
            }
        case TAG("compressor[1]/flonum[3]"):
            {
            return "compressor[1]/flonum[3]";
            }
        case TAG("compressor[1]/flonum"):
            {
            return "compressor[1]/flonum";
            }
        case TAG("compressor[1]/flonum[1]"):
            {
            return "compressor[1]/flonum[1]";
            }
        case TAG("valin"):
            {
            return "valin";
            }
        case TAG("format"):
            {
            return "format";
            }
        }
    
        return nullptr;
    }
    
    DataRef* getDataRef(DataRefIndex index)  {
        switch (index) {
        case 0:
            {
            return addressOf(this->average_rms_tilde_01_av_bufferobj);
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
            this->average_rms_tilde_01_av_buffer = new Float64Buffer(this->average_rms_tilde_01_av_bufferobj);
        }
    }
    
    void initialize() {
        this->average_rms_tilde_01_av_bufferobj = initDataRef("average_rms_tilde_01_av_bufferobj", true, nullptr, "buffer~");
        this->assign_defaults();
        this->setState();
        this->average_rms_tilde_01_av_bufferobj->setIndex(0);
        this->average_rms_tilde_01_av_buffer = new Float64Buffer(this->average_rms_tilde_01_av_bufferobj);
    }
    
    protected:
    
    void eventinlet_01_out1_bang_bang() {
        this->numberobj_01_value_bang();
    }
    
    void eventinlet_01_out1_list_set(const list& v) {
        {
            number converted = (v->length > 0 ? v[0] : 0);
            this->numberobj_01_value_set(converted);
        }
    }
    
    void numberobj_01_valin_set(number v) {
        this->numberobj_01_value_set(v);
    }
    
    void numberobj_01_format_set(number v) {
        this->numberobj_01_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
    }
    
    void eventinlet_02_out1_bang_bang() {
        this->numberobj_02_value_bang();
    }
    
    void eventinlet_02_out1_list_set(const list& v) {
        {
            number converted = (v->length > 0 ? v[0] : 0);
            this->numberobj_02_value_set(converted);
        }
    }
    
    void numberobj_02_valin_set(number v) {
        this->numberobj_02_value_set(v);
    }
    
    void numberobj_02_format_set(number v) {
        this->numberobj_02_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
    }
    
    void eventinlet_03_out1_bang_bang() {
        this->numberobj_03_value_bang();
    }
    
    void eventinlet_03_out1_list_set(const list& v) {
        {
            number converted = (v->length > 0 ? v[0] : 0);
            this->numberobj_03_value_set(converted);
        }
    }
    
    void numberobj_03_valin_set(number v) {
        this->numberobj_03_value_set(v);
    }
    
    void numberobj_03_format_set(number v) {
        this->numberobj_03_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
    }
    
    void numberobj_04_valin_set(number v) {
        this->numberobj_04_value_set(v);
    }
    
    void numberobj_04_format_set(number v) {
        this->numberobj_04_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
    }
    
    void eventinlet_04_out1_bang_bang() {
        this->numberobj_04_value_bang();
    }
    
    void eventinlet_04_out1_list_set(const list& v) {
        {
            number converted = (v->length > 0 ? v[0] : 0);
            this->numberobj_04_value_set(converted);
        }
    }
    
    void eventinlet_05_out1_bang_bang() {
        this->numberobj_05_value_bang();
    }
    
    void eventinlet_05_out1_list_set(const list& v) {
        {
            number converted = (v->length > 0 ? v[0] : 0);
            this->numberobj_05_value_set(converted);
        }
    }
    
    void numberobj_05_valin_set(number v) {
        this->numberobj_05_value_set(v);
    }
    
    void numberobj_05_format_set(number v) {
        this->numberobj_05_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
    }
    
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
        return 2;
    }
    
    void initializeObjects() {
        this->numberobj_01_init();
        this->average_rms_tilde_01_av_init();
        this->numberobj_02_init();
        this->numberobj_03_init();
        this->numberobj_04_init();
        this->numberobj_05_init();
    }
    
    void sendOutlet(OutletIndex index, ParameterValue value) {
        this->getEngine()->sendOutlet(this, index, value);
    }
    
    void startup() {}
    
    void allocateDataRefs() {
        this->average_rms_tilde_01_av_buffer = this->average_rms_tilde_01_av_buffer->allocateIfNeeded();
    
        if (this->average_rms_tilde_01_av_bufferobj->hasRequestedSize()) {
            if (this->average_rms_tilde_01_av_bufferobj->wantsFill())
                this->zeroDataRef(this->average_rms_tilde_01_av_bufferobj);
    
            this->getEngine()->sendDataRefUpdated(0);
        }
    }
    
    void mstosamps_tilde_02_ms_set(number v) {
        this->mstosamps_tilde_02_ms = v;
    }
    
    void numberobj_03_output_set(number v) {
        this->mstosamps_tilde_02_ms_set(v);
    }
    
    void numberobj_03_value_set(number v) {
        this->numberobj_03_value_setter(v);
        v = this->numberobj_03_value;
        number localvalue = v;
    
        if (this->numberobj_03_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->getEngine()->sendNumMessage(
            TAG("valout"),
            TAG("compressor[1]/flonum[3]"),
            localvalue,
            this->_currentTime
        );
    
        this->numberobj_03_output_set(localvalue);
    }
    
    void eventinlet_03_out1_number_set(number v) {
        this->numberobj_03_value_set(v);
    }
    
    void mstosamps_tilde_01_ms_set(number v) {
        this->mstosamps_tilde_01_ms = v;
    }
    
    void numberobj_02_output_set(number v) {
        this->mstosamps_tilde_01_ms_set(v);
    }
    
    void numberobj_02_value_set(number v) {
        this->numberobj_02_value_setter(v);
        v = this->numberobj_02_value;
        number localvalue = v;
    
        if (this->numberobj_02_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->getEngine()->sendNumMessage(
            TAG("valout"),
            TAG("compressor[1]/flonum[2]"),
            localvalue,
            this->_currentTime
        );
    
        this->numberobj_02_output_set(localvalue);
    }
    
    void eventinlet_02_out1_number_set(number v) {
        this->numberobj_02_value_set(v);
    }
    
    void dspexpr_13_in1_set(number v) {
        this->dspexpr_13_in1 = v;
    }
    
    void numberobj_05_output_set(number v) {
        this->dspexpr_13_in1_set(v);
    }
    
    void numberobj_05_value_set(number v) {
        this->numberobj_05_value_setter(v);
        v = this->numberobj_05_value;
        number localvalue = v;
    
        if ((bool)(true) && localvalue < 1) {
            localvalue = 1;
        }
    
        if (this->numberobj_05_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->getEngine()->sendNumMessage(
            TAG("valout"),
            TAG("compressor[1]/flonum[1]"),
            localvalue,
            this->_currentTime
        );
    
        this->numberobj_05_output_set(localvalue);
    }
    
    void eventinlet_05_out1_number_set(number v) {
        this->numberobj_05_value_set(v);
    }
    
    void dspexpr_12_in1_set(number v) {
        this->dspexpr_12_in1 = v;
    }
    
    void dspexpr_06_in2_set(number v) {
        this->dspexpr_06_in2 = v;
    }
    
    void numberobj_04_output_set(number v) {
        this->dspexpr_12_in1_set(v);
        this->dspexpr_06_in2_set(v);
    }
    
    void numberobj_04_value_set(number v) {
        this->numberobj_04_value_setter(v);
        v = this->numberobj_04_value;
        number localvalue = v;
    
        if ((bool)(true) && localvalue < -96) {
            localvalue = -96;
        }
    
        if ((bool)(true) && localvalue > 0) {
            localvalue = 0;
        }
    
        if (this->numberobj_04_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->getEngine()->sendNumMessage(TAG("valout"), TAG("compressor[1]/flonum"), localvalue, this->_currentTime);
        this->numberobj_04_output_set(localvalue);
    }
    
    void eventinlet_04_out1_number_set(number v) {
        this->numberobj_04_value_set(v);
    }
    
    void dspexpr_03_in1_set(number v) {
        this->dspexpr_03_in1 = v;
    }
    
    void numberobj_01_output_set(number v) {
        this->dspexpr_03_in1_set(v);
    }
    
    void numberobj_01_value_set(number v) {
        this->numberobj_01_value_setter(v);
        v = this->numberobj_01_value;
        number localvalue = v;
    
        if (this->numberobj_01_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->getEngine()->sendNumMessage(
            TAG("valout"),
            TAG("compressor[1]/number_obj-62"),
            localvalue,
            this->_currentTime
        );
    
        this->numberobj_01_output_set(localvalue);
    }
    
    void eventinlet_01_out1_number_set(number v) {
        this->numberobj_01_value_set(v);
    }
    
    void numberobj_01_value_bang() {
        number v = this->numberobj_01_value;
        number localvalue = v;
    
        if (this->numberobj_01_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->getEngine()->sendNumMessage(
            TAG("valout"),
            TAG("compressor[1]/number_obj-62"),
            localvalue,
            this->_currentTime
        );
    
        this->numberobj_01_output_set(localvalue);
    }
    
    void numberobj_02_value_bang() {
        number v = this->numberobj_02_value;
        number localvalue = v;
    
        if (this->numberobj_02_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->getEngine()->sendNumMessage(
            TAG("valout"),
            TAG("compressor[1]/flonum[2]"),
            localvalue,
            this->_currentTime
        );
    
        this->numberobj_02_output_set(localvalue);
    }
    
    void numberobj_03_value_bang() {
        number v = this->numberobj_03_value;
        number localvalue = v;
    
        if (this->numberobj_03_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->getEngine()->sendNumMessage(
            TAG("valout"),
            TAG("compressor[1]/flonum[3]"),
            localvalue,
            this->_currentTime
        );
    
        this->numberobj_03_output_set(localvalue);
    }
    
    void numberobj_04_value_bang() {
        number v = this->numberobj_04_value;
        number localvalue = v;
    
        if ((bool)(true) && localvalue < -96) {
            localvalue = -96;
        }
    
        if ((bool)(true) && localvalue > 0) {
            localvalue = 0;
        }
    
        if (this->numberobj_04_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->getEngine()->sendNumMessage(TAG("valout"), TAG("compressor[1]/flonum"), localvalue, this->_currentTime);
        this->numberobj_04_output_set(localvalue);
    }
    
    void numberobj_05_value_bang() {
        number v = this->numberobj_05_value;
        number localvalue = v;
    
        if ((bool)(true) && localvalue < 1) {
            localvalue = 1;
        }
    
        if (this->numberobj_05_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->getEngine()->sendNumMessage(
            TAG("valout"),
            TAG("compressor[1]/flonum[1]"),
            localvalue,
            this->_currentTime
        );
    
        this->numberobj_05_output_set(localvalue);
    }
    
    void dspexpr_03_perform(number in1, SampleValue * out1, Index n) {
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = rnbo_pow(10, in1 * 0.05);//#map:_###_obj_###_:1
        }
    }
    
    void dspexpr_02_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = in1[(Index)i] * in2[(Index)i];//#map:_###_obj_###_:1
        }
    }
    
    void average_rms_tilde_01_perform(
        const Sample * x,
        number windowSize,
        number reset,
        SampleValue * out1,
        Index n
    ) {
        RNBO_UNUSED(reset);
        RNBO_UNUSED(windowSize);
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = this->safesqrt(this->average_rms_tilde_01_av_next(x[(Index)i] * x[(Index)i], 1000, 0));
        }
    }
    
    void dspexpr_07_perform(const Sample * in1, SampleValue * out1, Index n) {
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = (in1[(Index)i] <= 0 ? -999 : 20 * rnbo_log10((in1[(Index)i] <= 0.0000000001 ? 0.0000000001 : in1[(Index)i])));//#map:_###_obj_###_:1
        }
    }
    
    void dspexpr_06_perform(const Sample * in1, number in2, SampleValue * out1, Index n) {
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = in1[(Index)i] > in2;//#map:_###_obj_###_:1
        }
    }
    
    void dspexpr_12_perform(number in1, const Sample * in2, SampleValue * out1, Index n) {
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = in1 - in2[(Index)i];//#map:_###_obj_###_:1
        }
    }
    
    void mstosamps_tilde_01_perform(number ms, SampleValue * out1, Index n) {
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = ms * this->sr * 0.001;
        }
    }
    
    void mstosamps_tilde_02_perform(number ms, SampleValue * out1, Index n) {
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = ms * this->sr * 0.001;
        }
    }
    
    void dspexpr_13_perform(number in1, SampleValue * out1, Index n) {
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = rnbo_abs(in1);//#map:_###_obj_###_:1
        }
    }
    
    void dspexpr_15_perform(const Sample * in1, number in2, SampleValue * out1, Index n) {
        RNBO_UNUSED(in2);
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = (in1[(Index)i] == 0. ? 0. : 1 / in1[(Index)i]);//#map:_###_obj_###_:1
        }
    }
    
    void dspexpr_14_perform(const Sample * in1, number in2, SampleValue * out1, Index n) {
        RNBO_UNUSED(in2);
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = 1 - in1[(Index)i];//#map:_###_obj_###_:1
        }
    }
    
    void dspexpr_11_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = in1[(Index)i] * in2[(Index)i];//#map:_###_obj_###_:1
        }
    }
    
    void dspexpr_10_perform(const Sample * in1, SampleValue * out1, Index n) {
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = rnbo_pow(10, in1[(Index)i] * 0.05);//#map:_###_obj_###_:1
        }
    }
    
    void dspexpr_08_perform(const Sample * in1, number in2, SampleValue * out1, Index n) {
        RNBO_UNUSED(in2);
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = 1 - in1[(Index)i];//#map:_###_obj_###_:1
        }
    }
    
    void dspexpr_09_perform(const Sample * in1, number in2, SampleValue * out1, Index n) {
        RNBO_UNUSED(in2);
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = in1[(Index)i] * -1;//#map:_###_obj_###_:1
        }
    }
    
    void dspexpr_05_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = in1[(Index)i] * in2[(Index)i];//#map:_###_obj_###_:1
        }
    }
    
    void dspexpr_04_perform(const Sample * in1, number in2, SampleValue * out1, Index n) {
        RNBO_UNUSED(in2);
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = in1[(Index)i] + 1;//#map:_###_obj_###_:1
        }
    }
    
    void rampsmooth_tilde_01_perform(
        const Sample * x,
        const Sample * up,
        const Sample * down,
        SampleValue * out1,
        Index n
    ) {
        auto __rampsmooth_tilde_01_increment = this->rampsmooth_tilde_01_increment;
        auto __rampsmooth_tilde_01_index = this->rampsmooth_tilde_01_index;
        auto __rampsmooth_tilde_01_prev = this->rampsmooth_tilde_01_prev;
        Index i;
    
        for (i = 0; i < n; i++) {
            if (this->rampsmooth_tilde_01_d_next(x[(Index)i]) != 0.) {
                if (x[(Index)i] > __rampsmooth_tilde_01_prev) {
                    number _up = up[(Index)i];
    
                    if (_up < 1)
                        _up = 1;
    
                    __rampsmooth_tilde_01_index = _up;
                    __rampsmooth_tilde_01_increment = (x[(Index)i] - __rampsmooth_tilde_01_prev) / _up;
                } else if (x[(Index)i] < __rampsmooth_tilde_01_prev) {
                    number _down = down[(Index)i];
    
                    if (_down < 1)
                        _down = 1;
    
                    __rampsmooth_tilde_01_index = _down;
                    __rampsmooth_tilde_01_increment = (x[(Index)i] - __rampsmooth_tilde_01_prev) / _down;
                }
            }
    
            if (__rampsmooth_tilde_01_index > 0) {
                __rampsmooth_tilde_01_prev += __rampsmooth_tilde_01_increment;
                __rampsmooth_tilde_01_index -= 1;
            } else {
                __rampsmooth_tilde_01_prev = x[(Index)i];
            }
    
            out1[(Index)i] = __rampsmooth_tilde_01_prev;
        }
    
        this->rampsmooth_tilde_01_prev = __rampsmooth_tilde_01_prev;
        this->rampsmooth_tilde_01_index = __rampsmooth_tilde_01_index;
        this->rampsmooth_tilde_01_increment = __rampsmooth_tilde_01_increment;
    }
    
    void dspexpr_01_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = in1[(Index)i] * in2[(Index)i];//#map:_###_obj_###_:1
        }
    }
    
    void signalforwarder_01_perform(const SampleValue * input, SampleValue * output, Index n) {
        for (Index i = 0; i < n; i++) {
            output[(Index)i] = input[(Index)i];
        }
    }
    
    void stackprotect_perform(Index n) {
        RNBO_UNUSED(n);
        auto __stackprotect_count = this->stackprotect_count;
        __stackprotect_count = 0;
        this->stackprotect_count = __stackprotect_count;
    }
    
    void numberobj_01_value_setter(number v) {
        number localvalue = v;
    
        if (this->numberobj_01_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->numberobj_01_value = localvalue;
    }
    
    void numberobj_02_value_setter(number v) {
        number localvalue = v;
    
        if (this->numberobj_02_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->numberobj_02_value = localvalue;
    }
    
    void numberobj_03_value_setter(number v) {
        number localvalue = v;
    
        if (this->numberobj_03_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->numberobj_03_value = localvalue;
    }
    
    void numberobj_04_value_setter(number v) {
        number localvalue = v;
    
        if ((bool)(true) && localvalue < -96) {
            localvalue = -96;
        }
    
        if ((bool)(true) && localvalue > 0) {
            localvalue = 0;
        }
    
        if (this->numberobj_04_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->numberobj_04_value = localvalue;
    }
    
    void numberobj_05_value_setter(number v) {
        number localvalue = v;
    
        if ((bool)(true) && localvalue < 1) {
            localvalue = 1;
        }
    
        if (this->numberobj_05_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->numberobj_05_value = localvalue;
    }
    
    void numberobj_01_init() {
        this->numberobj_01_currentFormat = 6;
        this->getEngine()->sendNumMessage(TAG("setup"), TAG("compressor[1]/number_obj-62"), 1, this->_currentTime);
    }
    
    void numberobj_01_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->numberobj_01_value;
    }
    
    void numberobj_01_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->numberobj_01_value_set(preset["value"]);
    }
    
    number rampsmooth_tilde_01_d_next(number x) {
        number temp = (number)(x - this->rampsmooth_tilde_01_d_prev);
        this->rampsmooth_tilde_01_d_prev = x;
        return temp;
    }
    
    void rampsmooth_tilde_01_d_dspsetup() {
        this->rampsmooth_tilde_01_d_reset();
    }
    
    void rampsmooth_tilde_01_d_reset() {
        this->rampsmooth_tilde_01_d_prev = 0;
    }
    
    void rampsmooth_tilde_01_dspsetup(bool force) {
        if ((bool)(this->rampsmooth_tilde_01_setupDone) && (bool)(!(bool)(force)))
            return;
    
        this->rampsmooth_tilde_01_setupDone = true;
        this->rampsmooth_tilde_01_d_dspsetup();
    }
    
    number average_rms_tilde_01_av_next(number x, int windowSize, bool reset) {
        if (windowSize > 0)
            this->average_rms_tilde_01_av_setwindowsize(windowSize);
    
        if (reset != 0) {
            if (this->average_rms_tilde_01_av_resetFlag != 1) {
                this->average_rms_tilde_01_av_wantsReset = 1;
                this->average_rms_tilde_01_av_resetFlag = 1;
            }
        } else {
            this->average_rms_tilde_01_av_resetFlag = 0;
        }
    
        if (this->average_rms_tilde_01_av_wantsReset == 1) {
            this->average_rms_tilde_01_av_doReset();
        }
    
        this->average_rms_tilde_01_av_accum += x;
        this->average_rms_tilde_01_av_buffer[(Index)this->average_rms_tilde_01_av_bufferPos] = x;
        number bufferSize = this->average_rms_tilde_01_av_buffer->getSize();
    
        if (this->average_rms_tilde_01_av_effectiveWindowSize < this->average_rms_tilde_01_av_currentWindowSize) {
            this->average_rms_tilde_01_av_effectiveWindowSize++;
        } else {
            number bufferReadPos = this->average_rms_tilde_01_av_bufferPos - this->average_rms_tilde_01_av_effectiveWindowSize;
    
            while (bufferReadPos < 0)
                bufferReadPos += bufferSize;
    
            this->average_rms_tilde_01_av_accum -= this->average_rms_tilde_01_av_buffer[(Index)bufferReadPos];
        }
    
        this->average_rms_tilde_01_av_bufferPos++;
    
        if (this->average_rms_tilde_01_av_bufferPos >= bufferSize) {
            this->average_rms_tilde_01_av_bufferPos -= bufferSize;
        }
    
        return this->average_rms_tilde_01_av_accum / this->average_rms_tilde_01_av_effectiveWindowSize;
    }
    
    void average_rms_tilde_01_av_setwindowsize(int wsize) {
        wsize = trunc(wsize);
    
        if (wsize != this->average_rms_tilde_01_av_currentWindowSize && wsize > 0 && wsize <= this->sr) {
            this->average_rms_tilde_01_av_currentWindowSize = wsize;
            this->average_rms_tilde_01_av_wantsReset = 1;
        }
    }
    
    void average_rms_tilde_01_av_reset() {
        this->average_rms_tilde_01_av_wantsReset = 1;
    }
    
    void average_rms_tilde_01_av_dspsetup() {
        this->average_rms_tilde_01_av_wantsReset = 1;
    
        if (this->sr > this->average_rms_tilde_01_av_buffer->getSize()) {
            this->average_rms_tilde_01_av_buffer->setSize(this->sr + 1);
            updateDataRef(this, this->average_rms_tilde_01_av_buffer);
        }
    }
    
    void average_rms_tilde_01_av_doReset() {
        this->average_rms_tilde_01_av_accum = 0;
        this->average_rms_tilde_01_av_effectiveWindowSize = 0;
        this->average_rms_tilde_01_av_bufferPos = 0;
        this->average_rms_tilde_01_av_wantsReset = 0;
    }
    
    void average_rms_tilde_01_av_init() {
        this->average_rms_tilde_01_av_currentWindowSize = this->sr;
        this->average_rms_tilde_01_av_buffer->requestSize(this->sr + 1, 1);
        this->average_rms_tilde_01_av_doReset();
    }
    
    void average_rms_tilde_01_dspsetup(bool force) {
        if ((bool)(this->average_rms_tilde_01_setupDone) && (bool)(!(bool)(force)))
            return;
    
        this->average_rms_tilde_01_setupDone = true;
        this->average_rms_tilde_01_av_dspsetup();
    }
    
    void numberobj_02_init() {
        this->numberobj_02_currentFormat = 6;
        this->getEngine()->sendNumMessage(TAG("setup"), TAG("compressor[1]/flonum[2]"), 1, this->_currentTime);
    }
    
    void numberobj_02_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->numberobj_02_value;
    }
    
    void numberobj_02_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->numberobj_02_value_set(preset["value"]);
    }
    
    void numberobj_03_init() {
        this->numberobj_03_currentFormat = 6;
        this->getEngine()->sendNumMessage(TAG("setup"), TAG("compressor[1]/flonum[3]"), 1, this->_currentTime);
    }
    
    void numberobj_03_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->numberobj_03_value;
    }
    
    void numberobj_03_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->numberobj_03_value_set(preset["value"]);
    }
    
    void numberobj_04_init() {
        this->numberobj_04_currentFormat = 6;
        this->getEngine()->sendNumMessage(TAG("setup"), TAG("compressor[1]/flonum"), 1, this->_currentTime);
    }
    
    void numberobj_04_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->numberobj_04_value;
    }
    
    void numberobj_04_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->numberobj_04_value_set(preset["value"]);
    }
    
    void numberobj_05_init() {
        this->numberobj_05_currentFormat = 6;
        this->getEngine()->sendNumMessage(TAG("setup"), TAG("compressor[1]/flonum[1]"), 1, this->_currentTime);
    }
    
    void numberobj_05_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->numberobj_05_value;
    }
    
    void numberobj_05_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->numberobj_05_value_set(preset["value"]);
    }
    
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
        dspexpr_01_in1 = 0;
        dspexpr_01_in2 = 1;
        dspexpr_02_in1 = 0;
        dspexpr_02_in2 = 1;
        numberobj_01_value = 0;
        numberobj_01_value_setter(numberobj_01_value);
        dspexpr_03_in1 = 0;
        rampsmooth_tilde_01_x = 0;
        rampsmooth_tilde_01_up = 0;
        rampsmooth_tilde_01_down = 0;
        average_rms_tilde_01_x = 0;
        average_rms_tilde_01_windowSize = 1000;
        average_rms_tilde_01_reset = 0;
        dspexpr_04_in1 = 0;
        dspexpr_04_in2 = 1;
        dspexpr_05_in1 = 0;
        dspexpr_05_in2 = 0;
        dspexpr_06_in1 = 0;
        dspexpr_06_in2 = 0;
        dspexpr_07_in1 = 0;
        mstosamps_tilde_01_ms = 0;
        numberobj_02_value = 0;
        numberobj_02_value_setter(numberobj_02_value);
        mstosamps_tilde_02_ms = 0;
        numberobj_03_value = 0;
        numberobj_03_value_setter(numberobj_03_value);
        dspexpr_08_in1 = 0;
        dspexpr_08_in2 = 1;
        dspexpr_09_in1 = 0;
        dspexpr_09_in2 = -1;
        dspexpr_10_in1 = 0;
        numberobj_04_value = 0;
        numberobj_04_value_setter(numberobj_04_value);
        dspexpr_11_in1 = 0;
        dspexpr_11_in2 = 0;
        dspexpr_12_in1 = 0;
        dspexpr_12_in2 = 0;
        numberobj_05_value = 0;
        numberobj_05_value_setter(numberobj_05_value);
        dspexpr_13_in1 = 0;
        dspexpr_14_in1 = 0;
        dspexpr_14_in2 = 1;
        dspexpr_15_in1 = 0;
        dspexpr_15_in2 = 1;
        _currentTime = 0;
        audioProcessSampleCount = 0;
        sampleOffsetIntoNextAudioBuffer = 0;
        zeroBuffer = nullptr;
        dummyBuffer = nullptr;
        signals[0] = nullptr;
        signals[1] = nullptr;
        signals[2] = nullptr;
        signals[3] = nullptr;
        signals[4] = nullptr;
        signals[5] = nullptr;
        signals[6] = nullptr;
        didAllocateSignals = 0;
        vs = 0;
        maxvs = 0;
        sr = 44100;
        invsr = 0.00002267573696;
        numberobj_01_currentFormat = 6;
        numberobj_01_lastValue = 0;
        rampsmooth_tilde_01_prev = 0;
        rampsmooth_tilde_01_index = 0;
        rampsmooth_tilde_01_increment = 0;
        rampsmooth_tilde_01_d_prev = 0;
        rampsmooth_tilde_01_setupDone = false;
        average_rms_tilde_01_av_currentWindowSize = 44100;
        average_rms_tilde_01_av_accum = 0;
        average_rms_tilde_01_av_effectiveWindowSize = 0;
        average_rms_tilde_01_av_bufferPos = 0;
        average_rms_tilde_01_av_wantsReset = false;
        average_rms_tilde_01_av_resetFlag = false;
        average_rms_tilde_01_setupDone = false;
        numberobj_02_currentFormat = 6;
        numberobj_02_lastValue = 0;
        numberobj_03_currentFormat = 6;
        numberobj_03_lastValue = 0;
        numberobj_04_currentFormat = 6;
        numberobj_04_lastValue = 0;
        numberobj_05_currentFormat = 6;
        numberobj_05_lastValue = 0;
        stackprotect_count = 0;
        _voiceIndex = 0;
        _noteNumber = 0;
        isMuted = 1;
        parameterOffset = 0;
    }
    
    // member variables
    
        number dspexpr_01_in1;
        number dspexpr_01_in2;
        number dspexpr_02_in1;
        number dspexpr_02_in2;
        number numberobj_01_value;
        number dspexpr_03_in1;
        number rampsmooth_tilde_01_x;
        number rampsmooth_tilde_01_up;
        number rampsmooth_tilde_01_down;
        number average_rms_tilde_01_x;
        number average_rms_tilde_01_windowSize;
        number average_rms_tilde_01_reset;
        number dspexpr_04_in1;
        number dspexpr_04_in2;
        number dspexpr_05_in1;
        number dspexpr_05_in2;
        number dspexpr_06_in1;
        number dspexpr_06_in2;
        number dspexpr_07_in1;
        number mstosamps_tilde_01_ms;
        number numberobj_02_value;
        number mstosamps_tilde_02_ms;
        number numberobj_03_value;
        number dspexpr_08_in1;
        number dspexpr_08_in2;
        number dspexpr_09_in1;
        number dspexpr_09_in2;
        number dspexpr_10_in1;
        number numberobj_04_value;
        number dspexpr_11_in1;
        number dspexpr_11_in2;
        number dspexpr_12_in1;
        number dspexpr_12_in2;
        number numberobj_05_value;
        number dspexpr_13_in1;
        number dspexpr_14_in1;
        number dspexpr_14_in2;
        number dspexpr_15_in1;
        number dspexpr_15_in2;
        MillisecondTime _currentTime;
        UInt64 audioProcessSampleCount;
        SampleIndex sampleOffsetIntoNextAudioBuffer;
        signal zeroBuffer;
        signal dummyBuffer;
        SampleValue * signals[7];
        bool didAllocateSignals;
        Index vs;
        Index maxvs;
        number sr;
        number invsr;
        Int numberobj_01_currentFormat;
        number numberobj_01_lastValue;
        number rampsmooth_tilde_01_prev;
        number rampsmooth_tilde_01_index;
        number rampsmooth_tilde_01_increment;
        number rampsmooth_tilde_01_d_prev;
        bool rampsmooth_tilde_01_setupDone;
        int average_rms_tilde_01_av_currentWindowSize;
        number average_rms_tilde_01_av_accum;
        int average_rms_tilde_01_av_effectiveWindowSize;
        int average_rms_tilde_01_av_bufferPos;
        bool average_rms_tilde_01_av_wantsReset;
        bool average_rms_tilde_01_av_resetFlag;
        Float64BufferRef average_rms_tilde_01_av_buffer;
        bool average_rms_tilde_01_setupDone;
        Int numberobj_02_currentFormat;
        number numberobj_02_lastValue;
        Int numberobj_03_currentFormat;
        number numberobj_03_lastValue;
        Int numberobj_04_currentFormat;
        number numberobj_04_lastValue;
        Int numberobj_05_currentFormat;
        number numberobj_05_lastValue;
        number stackprotect_count;
        DataRef average_rms_tilde_01_av_bufferobj;
        Index _voiceIndex;
        Int _noteNumber;
        Index isMuted;
        ParameterIndex parameterOffset;
    
};

class RNBOSubpatcher_14 : public PatcherInterfaceImpl {
    
    friend class rnbomatic;
    
    public:
    
    RNBOSubpatcher_14()
    {
    }
    
    ~RNBOSubpatcher_14()
    {
    }
    
    virtual rnbomatic* getPatcher() const {
        return static_cast<rnbomatic *>(_parentPatcher);
    }
    
    rnbomatic* getTopLevelPatcher() {
        return this->getPatcher()->getTopLevelPatcher();
    }
    
    void cancelClockEvents()
    {
    }
    
    inline number safesqrt(number num) {
        return (num > 0.0 ? rnbo_sqrt(num) : 0.0);
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
        this->dspexpr_18_perform(this->dspexpr_18_in1, this->signals[0], n);
        this->dspexpr_17_perform(in1, this->signals[0], this->signals[1], n);
    
        this->average_rms_tilde_02_perform(
            this->signals[1],
            this->average_rms_tilde_02_windowSize,
            this->average_rms_tilde_02_reset,
            this->signals[0],
            n
        );
    
        this->dspexpr_22_perform(this->signals[0], this->signals[2], n);
        this->dspexpr_21_perform(this->signals[2], this->dspexpr_21_in2, this->signals[0], n);
        this->dspexpr_27_perform(this->dspexpr_27_in1, this->signals[2], this->signals[3], n);
        this->mstosamps_tilde_03_perform(this->mstosamps_tilde_03_ms, this->signals[2], n);
        this->mstosamps_tilde_04_perform(this->mstosamps_tilde_04_ms, this->signals[4], n);
        this->dspexpr_28_perform(this->dspexpr_28_in1, this->signals[5], n);
        this->dspexpr_30_perform(this->signals[5], this->dspexpr_30_in2, this->signals[6], n);
        this->dspexpr_29_perform(this->signals[6], this->dspexpr_29_in2, this->signals[5], n);
        this->dspexpr_26_perform(this->signals[3], this->signals[5], this->signals[6], n);
        this->dspexpr_25_perform(this->signals[6], this->signals[5], n);
        this->dspexpr_23_perform(this->signals[5], this->dspexpr_23_in2, this->signals[6], n);
        this->dspexpr_24_perform(this->signals[6], this->dspexpr_24_in2, this->signals[5], n);
        this->dspexpr_20_perform(this->signals[0], this->signals[5], this->signals[6], n);
        this->dspexpr_19_perform(this->signals[6], this->dspexpr_19_in2, this->signals[5], n);
        this->rampsmooth_tilde_02_perform(this->signals[5], this->signals[2], this->signals[4], this->signals[6], n);
        this->dspexpr_16_perform(this->signals[1], this->signals[6], out1, n);
        this->stackprotect_perform(n);
        this->audioProcessSampleCount += this->vs;
    }
    
    void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
        if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
            Index i;
    
            for (i = 0; i < 7; i++) {
                this->signals[i] = resizeSignal(this->signals[i], this->maxvs, maxBlockSize);
            }
    
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
    
        this->average_rms_tilde_02_dspsetup(forceDSPSetup);
        this->rampsmooth_tilde_02_dspsetup(forceDSPSetup);
    
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
    
    void getPreset(PatcherStateInterface& ) {}
    
    void setParameterValue(ParameterIndex , ParameterValue , MillisecondTime ) {}
    
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
        return 0;
    }
    
    ConstCharPointer getParameterName(ParameterIndex index) const {
        switch (index) {
        default:
            {
            return "bogus";
            }
        }
    }
    
    ConstCharPointer getParameterId(ParameterIndex index) const {
        switch (index) {
        default:
            {
            return "bogus";
            }
        }
    }
    
    void getParameterInfo(ParameterIndex , ParameterInfo * ) const {}
    
    void sendParameter(ParameterIndex index, bool ignoreValue) {
        this->getPatcher()->sendParameter(index + this->parameterOffset, ignoreValue);
    }
    
    void setParameterOffset(ParameterIndex offset) {
        this->parameterOffset = offset;
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
        default:
            {
            return value;
            }
        }
    }
    
    ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
        value = (value < 0 ? 0 : (value > 1 ? 1 : value));
    
        switch (index) {
        default:
            {
            return value;
            }
        }
    }
    
    ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
        switch (index) {
        default:
            {
            return value;
            }
        }
    }
    
    void scheduleParamInit(ParameterIndex index, Index order) {
        this->getPatcher()->scheduleParamInit(index + this->parameterOffset, order);
    }
    
    void processClockEvent(MillisecondTime , ClockId , bool , ParameterValue ) {}
    
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
        case TAG("valin"):
            {
            if (TAG("compressor/number_obj-62") == objectId)
                this->numberobj_06_valin_set(payload);
    
            if (TAG("compressor/flonum[2]") == objectId)
                this->numberobj_07_valin_set(payload);
    
            if (TAG("compressor/flonum[3]") == objectId)
                this->numberobj_08_valin_set(payload);
    
            if (TAG("compressor/flonum") == objectId)
                this->numberobj_09_valin_set(payload);
    
            if (TAG("compressor/flonum[1]") == objectId)
                this->numberobj_10_valin_set(payload);
    
            break;
            }
        case TAG("format"):
            {
            if (TAG("compressor/number_obj-62") == objectId)
                this->numberobj_06_format_set(payload);
    
            if (TAG("compressor/flonum[2]") == objectId)
                this->numberobj_07_format_set(payload);
    
            if (TAG("compressor/flonum[3]") == objectId)
                this->numberobj_08_format_set(payload);
    
            if (TAG("compressor/flonum") == objectId)
                this->numberobj_09_format_set(payload);
    
            if (TAG("compressor/flonum[1]") == objectId)
                this->numberobj_10_format_set(payload);
    
            break;
            }
        }
    }
    
    void processListMessage(MessageTag , MessageTag , MillisecondTime , const list& ) {}
    
    void processBangMessage(MessageTag , MessageTag , MillisecondTime ) {}
    
    MessageTagInfo resolveTag(MessageTag tag) const {
        switch (tag) {
        case TAG("valout"):
            {
            return "valout";
            }
        case TAG("compressor/number_obj-62"):
            {
            return "compressor/number_obj-62";
            }
        case TAG("setup"):
            {
            return "setup";
            }
        case TAG("compressor/flonum[2]"):
            {
            return "compressor/flonum[2]";
            }
        case TAG("compressor/flonum[3]"):
            {
            return "compressor/flonum[3]";
            }
        case TAG("compressor/flonum"):
            {
            return "compressor/flonum";
            }
        case TAG("compressor/flonum[1]"):
            {
            return "compressor/flonum[1]";
            }
        case TAG("valin"):
            {
            return "valin";
            }
        case TAG("format"):
            {
            return "format";
            }
        }
    
        return nullptr;
    }
    
    DataRef* getDataRef(DataRefIndex index)  {
        switch (index) {
        case 0:
            {
            return addressOf(this->average_rms_tilde_02_av_bufferobj);
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
            this->average_rms_tilde_02_av_buffer = new Float64Buffer(this->average_rms_tilde_02_av_bufferobj);
        }
    }
    
    void initialize() {
        this->average_rms_tilde_02_av_bufferobj = initDataRef("average_rms_tilde_02_av_bufferobj", true, nullptr, "buffer~");
        this->assign_defaults();
        this->setState();
        this->average_rms_tilde_02_av_bufferobj->setIndex(0);
        this->average_rms_tilde_02_av_buffer = new Float64Buffer(this->average_rms_tilde_02_av_bufferobj);
    }
    
    protected:
    
    void eventinlet_06_out1_bang_bang() {
        this->numberobj_06_value_bang();
    }
    
    void eventinlet_06_out1_list_set(const list& v) {
        {
            number converted = (v->length > 0 ? v[0] : 0);
            this->numberobj_06_value_set(converted);
        }
    }
    
    void numberobj_06_valin_set(number v) {
        this->numberobj_06_value_set(v);
    }
    
    void numberobj_06_format_set(number v) {
        this->numberobj_06_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
    }
    
    void eventinlet_07_out1_bang_bang() {
        this->numberobj_07_value_bang();
    }
    
    void eventinlet_07_out1_list_set(const list& v) {
        {
            number converted = (v->length > 0 ? v[0] : 0);
            this->numberobj_07_value_set(converted);
        }
    }
    
    void numberobj_07_valin_set(number v) {
        this->numberobj_07_value_set(v);
    }
    
    void numberobj_07_format_set(number v) {
        this->numberobj_07_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
    }
    
    void eventinlet_08_out1_bang_bang() {
        this->numberobj_08_value_bang();
    }
    
    void eventinlet_08_out1_list_set(const list& v) {
        {
            number converted = (v->length > 0 ? v[0] : 0);
            this->numberobj_08_value_set(converted);
        }
    }
    
    void numberobj_08_valin_set(number v) {
        this->numberobj_08_value_set(v);
    }
    
    void numberobj_08_format_set(number v) {
        this->numberobj_08_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
    }
    
    void numberobj_09_valin_set(number v) {
        this->numberobj_09_value_set(v);
    }
    
    void numberobj_09_format_set(number v) {
        this->numberobj_09_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
    }
    
    void eventinlet_09_out1_bang_bang() {
        this->numberobj_09_value_bang();
    }
    
    void eventinlet_09_out1_list_set(const list& v) {
        {
            number converted = (v->length > 0 ? v[0] : 0);
            this->numberobj_09_value_set(converted);
        }
    }
    
    void eventinlet_10_out1_bang_bang() {
        this->numberobj_10_value_bang();
    }
    
    void eventinlet_10_out1_list_set(const list& v) {
        {
            number converted = (v->length > 0 ? v[0] : 0);
            this->numberobj_10_value_set(converted);
        }
    }
    
    void numberobj_10_valin_set(number v) {
        this->numberobj_10_value_set(v);
    }
    
    void numberobj_10_format_set(number v) {
        this->numberobj_10_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
    }
    
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
    
    void initializeObjects() {
        this->numberobj_06_init();
        this->average_rms_tilde_02_av_init();
        this->numberobj_07_init();
        this->numberobj_08_init();
        this->numberobj_09_init();
        this->numberobj_10_init();
    }
    
    void sendOutlet(OutletIndex index, ParameterValue value) {
        this->getEngine()->sendOutlet(this, index, value);
    }
    
    void startup() {}
    
    void allocateDataRefs() {
        this->average_rms_tilde_02_av_buffer = this->average_rms_tilde_02_av_buffer->allocateIfNeeded();
    
        if (this->average_rms_tilde_02_av_bufferobj->hasRequestedSize()) {
            if (this->average_rms_tilde_02_av_bufferobj->wantsFill())
                this->zeroDataRef(this->average_rms_tilde_02_av_bufferobj);
    
            this->getEngine()->sendDataRefUpdated(0);
        }
    }
    
    void mstosamps_tilde_04_ms_set(number v) {
        this->mstosamps_tilde_04_ms = v;
    }
    
    void numberobj_08_output_set(number v) {
        this->mstosamps_tilde_04_ms_set(v);
    }
    
    void numberobj_08_value_set(number v) {
        this->numberobj_08_value_setter(v);
        v = this->numberobj_08_value;
        number localvalue = v;
    
        if (this->numberobj_08_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->getEngine()->sendNumMessage(TAG("valout"), TAG("compressor/flonum[3]"), localvalue, this->_currentTime);
        this->numberobj_08_output_set(localvalue);
    }
    
    void eventinlet_08_out1_number_set(number v) {
        this->numberobj_08_value_set(v);
    }
    
    void mstosamps_tilde_03_ms_set(number v) {
        this->mstosamps_tilde_03_ms = v;
    }
    
    void numberobj_07_output_set(number v) {
        this->mstosamps_tilde_03_ms_set(v);
    }
    
    void numberobj_07_value_set(number v) {
        this->numberobj_07_value_setter(v);
        v = this->numberobj_07_value;
        number localvalue = v;
    
        if (this->numberobj_07_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->getEngine()->sendNumMessage(TAG("valout"), TAG("compressor/flonum[2]"), localvalue, this->_currentTime);
        this->numberobj_07_output_set(localvalue);
    }
    
    void eventinlet_07_out1_number_set(number v) {
        this->numberobj_07_value_set(v);
    }
    
    void dspexpr_28_in1_set(number v) {
        this->dspexpr_28_in1 = v;
    }
    
    void numberobj_10_output_set(number v) {
        this->dspexpr_28_in1_set(v);
    }
    
    void numberobj_10_value_set(number v) {
        this->numberobj_10_value_setter(v);
        v = this->numberobj_10_value;
        number localvalue = v;
    
        if ((bool)(true) && localvalue < 1) {
            localvalue = 1;
        }
    
        if (this->numberobj_10_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->getEngine()->sendNumMessage(TAG("valout"), TAG("compressor/flonum[1]"), localvalue, this->_currentTime);
        this->numberobj_10_output_set(localvalue);
    }
    
    void eventinlet_10_out1_number_set(number v) {
        this->numberobj_10_value_set(v);
    }
    
    void dspexpr_27_in1_set(number v) {
        this->dspexpr_27_in1 = v;
    }
    
    void dspexpr_21_in2_set(number v) {
        this->dspexpr_21_in2 = v;
    }
    
    void numberobj_09_output_set(number v) {
        this->dspexpr_27_in1_set(v);
        this->dspexpr_21_in2_set(v);
    }
    
    void numberobj_09_value_set(number v) {
        this->numberobj_09_value_setter(v);
        v = this->numberobj_09_value;
        number localvalue = v;
    
        if ((bool)(true) && localvalue < -96) {
            localvalue = -96;
        }
    
        if ((bool)(true) && localvalue > 0) {
            localvalue = 0;
        }
    
        if (this->numberobj_09_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->getEngine()->sendNumMessage(TAG("valout"), TAG("compressor/flonum"), localvalue, this->_currentTime);
        this->numberobj_09_output_set(localvalue);
    }
    
    void eventinlet_09_out1_number_set(number v) {
        this->numberobj_09_value_set(v);
    }
    
    void dspexpr_18_in1_set(number v) {
        this->dspexpr_18_in1 = v;
    }
    
    void numberobj_06_output_set(number v) {
        this->dspexpr_18_in1_set(v);
    }
    
    void numberobj_06_value_set(number v) {
        this->numberobj_06_value_setter(v);
        v = this->numberobj_06_value;
        number localvalue = v;
    
        if (this->numberobj_06_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->getEngine()->sendNumMessage(
            TAG("valout"),
            TAG("compressor/number_obj-62"),
            localvalue,
            this->_currentTime
        );
    
        this->numberobj_06_output_set(localvalue);
    }
    
    void eventinlet_06_out1_number_set(number v) {
        this->numberobj_06_value_set(v);
    }
    
    void numberobj_06_value_bang() {
        number v = this->numberobj_06_value;
        number localvalue = v;
    
        if (this->numberobj_06_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->getEngine()->sendNumMessage(
            TAG("valout"),
            TAG("compressor/number_obj-62"),
            localvalue,
            this->_currentTime
        );
    
        this->numberobj_06_output_set(localvalue);
    }
    
    void numberobj_07_value_bang() {
        number v = this->numberobj_07_value;
        number localvalue = v;
    
        if (this->numberobj_07_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->getEngine()->sendNumMessage(TAG("valout"), TAG("compressor/flonum[2]"), localvalue, this->_currentTime);
        this->numberobj_07_output_set(localvalue);
    }
    
    void numberobj_08_value_bang() {
        number v = this->numberobj_08_value;
        number localvalue = v;
    
        if (this->numberobj_08_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->getEngine()->sendNumMessage(TAG("valout"), TAG("compressor/flonum[3]"), localvalue, this->_currentTime);
        this->numberobj_08_output_set(localvalue);
    }
    
    void numberobj_09_value_bang() {
        number v = this->numberobj_09_value;
        number localvalue = v;
    
        if ((bool)(true) && localvalue < -96) {
            localvalue = -96;
        }
    
        if ((bool)(true) && localvalue > 0) {
            localvalue = 0;
        }
    
        if (this->numberobj_09_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->getEngine()->sendNumMessage(TAG("valout"), TAG("compressor/flonum"), localvalue, this->_currentTime);
        this->numberobj_09_output_set(localvalue);
    }
    
    void numberobj_10_value_bang() {
        number v = this->numberobj_10_value;
        number localvalue = v;
    
        if ((bool)(true) && localvalue < 1) {
            localvalue = 1;
        }
    
        if (this->numberobj_10_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->getEngine()->sendNumMessage(TAG("valout"), TAG("compressor/flonum[1]"), localvalue, this->_currentTime);
        this->numberobj_10_output_set(localvalue);
    }
    
    void dspexpr_18_perform(number in1, SampleValue * out1, Index n) {
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = rnbo_pow(10, in1 * 0.05);//#map:_###_obj_###_:1
        }
    }
    
    void dspexpr_17_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = in1[(Index)i] * in2[(Index)i];//#map:_###_obj_###_:1
        }
    }
    
    void average_rms_tilde_02_perform(
        const Sample * x,
        number windowSize,
        number reset,
        SampleValue * out1,
        Index n
    ) {
        RNBO_UNUSED(reset);
        RNBO_UNUSED(windowSize);
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = this->safesqrt(this->average_rms_tilde_02_av_next(x[(Index)i] * x[(Index)i], 1000, 0));
        }
    }
    
    void dspexpr_22_perform(const Sample * in1, SampleValue * out1, Index n) {
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = (in1[(Index)i] <= 0 ? -999 : 20 * rnbo_log10((in1[(Index)i] <= 0.0000000001 ? 0.0000000001 : in1[(Index)i])));//#map:_###_obj_###_:1
        }
    }
    
    void dspexpr_21_perform(const Sample * in1, number in2, SampleValue * out1, Index n) {
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = in1[(Index)i] > in2;//#map:_###_obj_###_:1
        }
    }
    
    void dspexpr_27_perform(number in1, const Sample * in2, SampleValue * out1, Index n) {
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = in1 - in2[(Index)i];//#map:_###_obj_###_:1
        }
    }
    
    void mstosamps_tilde_03_perform(number ms, SampleValue * out1, Index n) {
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = ms * this->sr * 0.001;
        }
    }
    
    void mstosamps_tilde_04_perform(number ms, SampleValue * out1, Index n) {
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = ms * this->sr * 0.001;
        }
    }
    
    void dspexpr_28_perform(number in1, SampleValue * out1, Index n) {
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = rnbo_abs(in1);//#map:_###_obj_###_:1
        }
    }
    
    void dspexpr_30_perform(const Sample * in1, number in2, SampleValue * out1, Index n) {
        RNBO_UNUSED(in2);
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = (in1[(Index)i] == 0. ? 0. : 1 / in1[(Index)i]);//#map:_###_obj_###_:1
        }
    }
    
    void dspexpr_29_perform(const Sample * in1, number in2, SampleValue * out1, Index n) {
        RNBO_UNUSED(in2);
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = 1 - in1[(Index)i];//#map:_###_obj_###_:1
        }
    }
    
    void dspexpr_26_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = in1[(Index)i] * in2[(Index)i];//#map:_###_obj_###_:1
        }
    }
    
    void dspexpr_25_perform(const Sample * in1, SampleValue * out1, Index n) {
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = rnbo_pow(10, in1[(Index)i] * 0.05);//#map:_###_obj_###_:1
        }
    }
    
    void dspexpr_23_perform(const Sample * in1, number in2, SampleValue * out1, Index n) {
        RNBO_UNUSED(in2);
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = 1 - in1[(Index)i];//#map:_###_obj_###_:1
        }
    }
    
    void dspexpr_24_perform(const Sample * in1, number in2, SampleValue * out1, Index n) {
        RNBO_UNUSED(in2);
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = in1[(Index)i] * -1;//#map:_###_obj_###_:1
        }
    }
    
    void dspexpr_20_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = in1[(Index)i] * in2[(Index)i];//#map:_###_obj_###_:1
        }
    }
    
    void dspexpr_19_perform(const Sample * in1, number in2, SampleValue * out1, Index n) {
        RNBO_UNUSED(in2);
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = in1[(Index)i] + 1;//#map:_###_obj_###_:1
        }
    }
    
    void rampsmooth_tilde_02_perform(
        const Sample * x,
        const Sample * up,
        const Sample * down,
        SampleValue * out1,
        Index n
    ) {
        auto __rampsmooth_tilde_02_increment = this->rampsmooth_tilde_02_increment;
        auto __rampsmooth_tilde_02_index = this->rampsmooth_tilde_02_index;
        auto __rampsmooth_tilde_02_prev = this->rampsmooth_tilde_02_prev;
        Index i;
    
        for (i = 0; i < n; i++) {
            if (this->rampsmooth_tilde_02_d_next(x[(Index)i]) != 0.) {
                if (x[(Index)i] > __rampsmooth_tilde_02_prev) {
                    number _up = up[(Index)i];
    
                    if (_up < 1)
                        _up = 1;
    
                    __rampsmooth_tilde_02_index = _up;
                    __rampsmooth_tilde_02_increment = (x[(Index)i] - __rampsmooth_tilde_02_prev) / _up;
                } else if (x[(Index)i] < __rampsmooth_tilde_02_prev) {
                    number _down = down[(Index)i];
    
                    if (_down < 1)
                        _down = 1;
    
                    __rampsmooth_tilde_02_index = _down;
                    __rampsmooth_tilde_02_increment = (x[(Index)i] - __rampsmooth_tilde_02_prev) / _down;
                }
            }
    
            if (__rampsmooth_tilde_02_index > 0) {
                __rampsmooth_tilde_02_prev += __rampsmooth_tilde_02_increment;
                __rampsmooth_tilde_02_index -= 1;
            } else {
                __rampsmooth_tilde_02_prev = x[(Index)i];
            }
    
            out1[(Index)i] = __rampsmooth_tilde_02_prev;
        }
    
        this->rampsmooth_tilde_02_prev = __rampsmooth_tilde_02_prev;
        this->rampsmooth_tilde_02_index = __rampsmooth_tilde_02_index;
        this->rampsmooth_tilde_02_increment = __rampsmooth_tilde_02_increment;
    }
    
    void dspexpr_16_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = in1[(Index)i] * in2[(Index)i];//#map:_###_obj_###_:1
        }
    }
    
    void stackprotect_perform(Index n) {
        RNBO_UNUSED(n);
        auto __stackprotect_count = this->stackprotect_count;
        __stackprotect_count = 0;
        this->stackprotect_count = __stackprotect_count;
    }
    
    void numberobj_06_value_setter(number v) {
        number localvalue = v;
    
        if (this->numberobj_06_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->numberobj_06_value = localvalue;
    }
    
    void numberobj_07_value_setter(number v) {
        number localvalue = v;
    
        if (this->numberobj_07_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->numberobj_07_value = localvalue;
    }
    
    void numberobj_08_value_setter(number v) {
        number localvalue = v;
    
        if (this->numberobj_08_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->numberobj_08_value = localvalue;
    }
    
    void numberobj_09_value_setter(number v) {
        number localvalue = v;
    
        if ((bool)(true) && localvalue < -96) {
            localvalue = -96;
        }
    
        if ((bool)(true) && localvalue > 0) {
            localvalue = 0;
        }
    
        if (this->numberobj_09_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->numberobj_09_value = localvalue;
    }
    
    void numberobj_10_value_setter(number v) {
        number localvalue = v;
    
        if ((bool)(true) && localvalue < 1) {
            localvalue = 1;
        }
    
        if (this->numberobj_10_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->numberobj_10_value = localvalue;
    }
    
    void numberobj_06_init() {
        this->numberobj_06_currentFormat = 6;
        this->getEngine()->sendNumMessage(TAG("setup"), TAG("compressor/number_obj-62"), 1, this->_currentTime);
    }
    
    void numberobj_06_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->numberobj_06_value;
    }
    
    void numberobj_06_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->numberobj_06_value_set(preset["value"]);
    }
    
    number rampsmooth_tilde_02_d_next(number x) {
        number temp = (number)(x - this->rampsmooth_tilde_02_d_prev);
        this->rampsmooth_tilde_02_d_prev = x;
        return temp;
    }
    
    void rampsmooth_tilde_02_d_dspsetup() {
        this->rampsmooth_tilde_02_d_reset();
    }
    
    void rampsmooth_tilde_02_d_reset() {
        this->rampsmooth_tilde_02_d_prev = 0;
    }
    
    void rampsmooth_tilde_02_dspsetup(bool force) {
        if ((bool)(this->rampsmooth_tilde_02_setupDone) && (bool)(!(bool)(force)))
            return;
    
        this->rampsmooth_tilde_02_setupDone = true;
        this->rampsmooth_tilde_02_d_dspsetup();
    }
    
    number average_rms_tilde_02_av_next(number x, int windowSize, bool reset) {
        if (windowSize > 0)
            this->average_rms_tilde_02_av_setwindowsize(windowSize);
    
        if (reset != 0) {
            if (this->average_rms_tilde_02_av_resetFlag != 1) {
                this->average_rms_tilde_02_av_wantsReset = 1;
                this->average_rms_tilde_02_av_resetFlag = 1;
            }
        } else {
            this->average_rms_tilde_02_av_resetFlag = 0;
        }
    
        if (this->average_rms_tilde_02_av_wantsReset == 1) {
            this->average_rms_tilde_02_av_doReset();
        }
    
        this->average_rms_tilde_02_av_accum += x;
        this->average_rms_tilde_02_av_buffer[(Index)this->average_rms_tilde_02_av_bufferPos] = x;
        number bufferSize = this->average_rms_tilde_02_av_buffer->getSize();
    
        if (this->average_rms_tilde_02_av_effectiveWindowSize < this->average_rms_tilde_02_av_currentWindowSize) {
            this->average_rms_tilde_02_av_effectiveWindowSize++;
        } else {
            number bufferReadPos = this->average_rms_tilde_02_av_bufferPos - this->average_rms_tilde_02_av_effectiveWindowSize;
    
            while (bufferReadPos < 0)
                bufferReadPos += bufferSize;
    
            this->average_rms_tilde_02_av_accum -= this->average_rms_tilde_02_av_buffer[(Index)bufferReadPos];
        }
    
        this->average_rms_tilde_02_av_bufferPos++;
    
        if (this->average_rms_tilde_02_av_bufferPos >= bufferSize) {
            this->average_rms_tilde_02_av_bufferPos -= bufferSize;
        }
    
        return this->average_rms_tilde_02_av_accum / this->average_rms_tilde_02_av_effectiveWindowSize;
    }
    
    void average_rms_tilde_02_av_setwindowsize(int wsize) {
        wsize = trunc(wsize);
    
        if (wsize != this->average_rms_tilde_02_av_currentWindowSize && wsize > 0 && wsize <= this->sr) {
            this->average_rms_tilde_02_av_currentWindowSize = wsize;
            this->average_rms_tilde_02_av_wantsReset = 1;
        }
    }
    
    void average_rms_tilde_02_av_reset() {
        this->average_rms_tilde_02_av_wantsReset = 1;
    }
    
    void average_rms_tilde_02_av_dspsetup() {
        this->average_rms_tilde_02_av_wantsReset = 1;
    
        if (this->sr > this->average_rms_tilde_02_av_buffer->getSize()) {
            this->average_rms_tilde_02_av_buffer->setSize(this->sr + 1);
            updateDataRef(this, this->average_rms_tilde_02_av_buffer);
        }
    }
    
    void average_rms_tilde_02_av_doReset() {
        this->average_rms_tilde_02_av_accum = 0;
        this->average_rms_tilde_02_av_effectiveWindowSize = 0;
        this->average_rms_tilde_02_av_bufferPos = 0;
        this->average_rms_tilde_02_av_wantsReset = 0;
    }
    
    void average_rms_tilde_02_av_init() {
        this->average_rms_tilde_02_av_currentWindowSize = this->sr;
        this->average_rms_tilde_02_av_buffer->requestSize(this->sr + 1, 1);
        this->average_rms_tilde_02_av_doReset();
    }
    
    void average_rms_tilde_02_dspsetup(bool force) {
        if ((bool)(this->average_rms_tilde_02_setupDone) && (bool)(!(bool)(force)))
            return;
    
        this->average_rms_tilde_02_setupDone = true;
        this->average_rms_tilde_02_av_dspsetup();
    }
    
    void numberobj_07_init() {
        this->numberobj_07_currentFormat = 6;
        this->getEngine()->sendNumMessage(TAG("setup"), TAG("compressor/flonum[2]"), 1, this->_currentTime);
    }
    
    void numberobj_07_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->numberobj_07_value;
    }
    
    void numberobj_07_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->numberobj_07_value_set(preset["value"]);
    }
    
    void numberobj_08_init() {
        this->numberobj_08_currentFormat = 6;
        this->getEngine()->sendNumMessage(TAG("setup"), TAG("compressor/flonum[3]"), 1, this->_currentTime);
    }
    
    void numberobj_08_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->numberobj_08_value;
    }
    
    void numberobj_08_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->numberobj_08_value_set(preset["value"]);
    }
    
    void numberobj_09_init() {
        this->numberobj_09_currentFormat = 6;
        this->getEngine()->sendNumMessage(TAG("setup"), TAG("compressor/flonum"), 1, this->_currentTime);
    }
    
    void numberobj_09_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->numberobj_09_value;
    }
    
    void numberobj_09_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->numberobj_09_value_set(preset["value"]);
    }
    
    void numberobj_10_init() {
        this->numberobj_10_currentFormat = 6;
        this->getEngine()->sendNumMessage(TAG("setup"), TAG("compressor/flonum[1]"), 1, this->_currentTime);
    }
    
    void numberobj_10_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->numberobj_10_value;
    }
    
    void numberobj_10_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->numberobj_10_value_set(preset["value"]);
    }
    
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
        dspexpr_16_in1 = 0;
        dspexpr_16_in2 = 1;
        dspexpr_17_in1 = 0;
        dspexpr_17_in2 = 1;
        numberobj_06_value = 0;
        numberobj_06_value_setter(numberobj_06_value);
        dspexpr_18_in1 = 0;
        rampsmooth_tilde_02_x = 0;
        rampsmooth_tilde_02_up = 0;
        rampsmooth_tilde_02_down = 0;
        average_rms_tilde_02_x = 0;
        average_rms_tilde_02_windowSize = 1000;
        average_rms_tilde_02_reset = 0;
        dspexpr_19_in1 = 0;
        dspexpr_19_in2 = 1;
        dspexpr_20_in1 = 0;
        dspexpr_20_in2 = 0;
        dspexpr_21_in1 = 0;
        dspexpr_21_in2 = 0;
        dspexpr_22_in1 = 0;
        mstosamps_tilde_03_ms = 0;
        numberobj_07_value = 0;
        numberobj_07_value_setter(numberobj_07_value);
        mstosamps_tilde_04_ms = 0;
        numberobj_08_value = 0;
        numberobj_08_value_setter(numberobj_08_value);
        dspexpr_23_in1 = 0;
        dspexpr_23_in2 = 1;
        dspexpr_24_in1 = 0;
        dspexpr_24_in2 = -1;
        dspexpr_25_in1 = 0;
        numberobj_09_value = 0;
        numberobj_09_value_setter(numberobj_09_value);
        dspexpr_26_in1 = 0;
        dspexpr_26_in2 = 0;
        dspexpr_27_in1 = 0;
        dspexpr_27_in2 = 0;
        numberobj_10_value = 0;
        numberobj_10_value_setter(numberobj_10_value);
        dspexpr_28_in1 = 0;
        dspexpr_29_in1 = 0;
        dspexpr_29_in2 = 1;
        dspexpr_30_in1 = 0;
        dspexpr_30_in2 = 1;
        _currentTime = 0;
        audioProcessSampleCount = 0;
        sampleOffsetIntoNextAudioBuffer = 0;
        zeroBuffer = nullptr;
        dummyBuffer = nullptr;
        signals[0] = nullptr;
        signals[1] = nullptr;
        signals[2] = nullptr;
        signals[3] = nullptr;
        signals[4] = nullptr;
        signals[5] = nullptr;
        signals[6] = nullptr;
        didAllocateSignals = 0;
        vs = 0;
        maxvs = 0;
        sr = 44100;
        invsr = 0.00002267573696;
        numberobj_06_currentFormat = 6;
        numberobj_06_lastValue = 0;
        rampsmooth_tilde_02_prev = 0;
        rampsmooth_tilde_02_index = 0;
        rampsmooth_tilde_02_increment = 0;
        rampsmooth_tilde_02_d_prev = 0;
        rampsmooth_tilde_02_setupDone = false;
        average_rms_tilde_02_av_currentWindowSize = 44100;
        average_rms_tilde_02_av_accum = 0;
        average_rms_tilde_02_av_effectiveWindowSize = 0;
        average_rms_tilde_02_av_bufferPos = 0;
        average_rms_tilde_02_av_wantsReset = false;
        average_rms_tilde_02_av_resetFlag = false;
        average_rms_tilde_02_setupDone = false;
        numberobj_07_currentFormat = 6;
        numberobj_07_lastValue = 0;
        numberobj_08_currentFormat = 6;
        numberobj_08_lastValue = 0;
        numberobj_09_currentFormat = 6;
        numberobj_09_lastValue = 0;
        numberobj_10_currentFormat = 6;
        numberobj_10_lastValue = 0;
        stackprotect_count = 0;
        _voiceIndex = 0;
        _noteNumber = 0;
        isMuted = 1;
        parameterOffset = 0;
    }
    
    // member variables
    
        number dspexpr_16_in1;
        number dspexpr_16_in2;
        number dspexpr_17_in1;
        number dspexpr_17_in2;
        number numberobj_06_value;
        number dspexpr_18_in1;
        number rampsmooth_tilde_02_x;
        number rampsmooth_tilde_02_up;
        number rampsmooth_tilde_02_down;
        number average_rms_tilde_02_x;
        number average_rms_tilde_02_windowSize;
        number average_rms_tilde_02_reset;
        number dspexpr_19_in1;
        number dspexpr_19_in2;
        number dspexpr_20_in1;
        number dspexpr_20_in2;
        number dspexpr_21_in1;
        number dspexpr_21_in2;
        number dspexpr_22_in1;
        number mstosamps_tilde_03_ms;
        number numberobj_07_value;
        number mstosamps_tilde_04_ms;
        number numberobj_08_value;
        number dspexpr_23_in1;
        number dspexpr_23_in2;
        number dspexpr_24_in1;
        number dspexpr_24_in2;
        number dspexpr_25_in1;
        number numberobj_09_value;
        number dspexpr_26_in1;
        number dspexpr_26_in2;
        number dspexpr_27_in1;
        number dspexpr_27_in2;
        number numberobj_10_value;
        number dspexpr_28_in1;
        number dspexpr_29_in1;
        number dspexpr_29_in2;
        number dspexpr_30_in1;
        number dspexpr_30_in2;
        MillisecondTime _currentTime;
        UInt64 audioProcessSampleCount;
        SampleIndex sampleOffsetIntoNextAudioBuffer;
        signal zeroBuffer;
        signal dummyBuffer;
        SampleValue * signals[7];
        bool didAllocateSignals;
        Index vs;
        Index maxvs;
        number sr;
        number invsr;
        Int numberobj_06_currentFormat;
        number numberobj_06_lastValue;
        number rampsmooth_tilde_02_prev;
        number rampsmooth_tilde_02_index;
        number rampsmooth_tilde_02_increment;
        number rampsmooth_tilde_02_d_prev;
        bool rampsmooth_tilde_02_setupDone;
        int average_rms_tilde_02_av_currentWindowSize;
        number average_rms_tilde_02_av_accum;
        int average_rms_tilde_02_av_effectiveWindowSize;
        int average_rms_tilde_02_av_bufferPos;
        bool average_rms_tilde_02_av_wantsReset;
        bool average_rms_tilde_02_av_resetFlag;
        Float64BufferRef average_rms_tilde_02_av_buffer;
        bool average_rms_tilde_02_setupDone;
        Int numberobj_07_currentFormat;
        number numberobj_07_lastValue;
        Int numberobj_08_currentFormat;
        number numberobj_08_lastValue;
        Int numberobj_09_currentFormat;
        number numberobj_09_lastValue;
        Int numberobj_10_currentFormat;
        number numberobj_10_lastValue;
        number stackprotect_count;
        DataRef average_rms_tilde_02_av_bufferobj;
        Index _voiceIndex;
        Int _noteNumber;
        Index isMuted;
        ParameterIndex parameterOffset;
    
};

rnbomatic()
{
}

~rnbomatic()
{
    delete this->p_01;
    delete this->p_02;
}

rnbomatic* getTopLevelPatcher() {
    return this;
}

void cancelClockEvents()
{
    getEngine()->flushClockEvents(this, 1646922831, false);
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

number mstosamps(MillisecondTime ms) {
    return ms * this->sr * 0.001;
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
    SampleValue * out2 = (numOutputs >= 2 && outputs[1] ? outputs[1] : this->dummyBuffer);
    const SampleValue * in1 = (numInputs >= 1 && inputs[0] ? inputs[0] : this->zeroBuffer);
    const SampleValue * in2 = (numInputs >= 2 && inputs[1] ? inputs[1] : this->zeroBuffer);
    this->p_01_perform(in1, this->signals[0], this->signals[1], n);
    this->dspexpr_31_perform(in1, this->signals[0], this->dspexpr_31_in3, out1, n);
    this->snapshot_01_perform(this->signals[1], n);
    this->p_02_perform(in2, this->signals[1], n);
    this->dspexpr_32_perform(in2, this->signals[1], this->dspexpr_32_in3, out2, n);
    this->stackprotect_perform(n);
    this->globaltransport_advance();
    this->audioProcessSampleCount += this->vs;
}

void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
    if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
        Index i;

        for (i = 0; i < 2; i++) {
            this->signals[i] = resizeSignal(this->signals[i], this->maxvs, maxBlockSize);
        }

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

    this->globaltransport_dspsetup(forceDSPSetup);
    this->p_01->prepareToProcess(sampleRate, maxBlockSize, force);
    this->p_02->prepareToProcess(sampleRate, maxBlockSize, force);

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
    default:
        {
        return nullptr;
        }
    }
}

DataRefIndex getNumDataRefs() const {
    return 0;
}

void fillDataRef(DataRefIndex , DataRef& ) {}

void processDataViewUpdate(DataRefIndex index, MillisecondTime time) {
    this->p_01->processDataViewUpdate(index, time);
    this->p_02->processDataViewUpdate(index, time);
}

void initialize() {
    this->assign_defaults();
    this->setState();
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

void setState() {
    this->p_01 = new RNBOSubpatcher_13();
    this->p_01->setEngineAndPatcher(this->getEngine(), this);
    this->p_01->initialize();
    this->p_01->setParameterOffset(this->getParameterOffset(this->p_01));
    this->p_02 = new RNBOSubpatcher_14();
    this->p_02->setEngineAndPatcher(this->getEngine(), this);
    this->p_02->initialize();
    this->p_02->setParameterOffset(this->getParameterOffset(this->p_02));
}

void getPreset(PatcherStateInterface& preset) {
    preset["__presetid"] = "rnbo";
    this->param_01_getPresetValue(getSubState(preset, "release"));
    this->param_02_getPresetValue(getSubState(preset, "attack"));
    this->param_03_getPresetValue(getSubState(preset, "ratio"));
    this->param_04_getPresetValue(getSubState(preset, "threshold"));
    this->param_05_getPresetValue(getSubState(preset, "input_gain"));
    this->param_06_getPresetValue(getSubState(preset, "parallel_mix"));
    this->p_01->getPreset(getSubState(getSubState(preset, "__sps"), "compressor[1]"));
    this->p_02->getPreset(getSubState(getSubState(preset, "__sps"), "compressor"));
}

void setPreset(MillisecondTime time, PatcherStateInterface& preset) {
    this->updateTime(time);
    this->param_01_setPresetValue(getSubState(preset, "release"));
    this->param_02_setPresetValue(getSubState(preset, "attack"));
    this->param_03_setPresetValue(getSubState(preset, "ratio"));
    this->param_04_setPresetValue(getSubState(preset, "threshold"));
    this->param_05_setPresetValue(getSubState(preset, "input_gain"));
    this->param_06_setPresetValue(getSubState(preset, "parallel_mix"));
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
    case 2:
        {
        this->param_03_value_set(v);
        break;
        }
    case 3:
        {
        this->param_04_value_set(v);
        break;
        }
    case 4:
        {
        this->param_05_value_set(v);
        break;
        }
    case 5:
        {
        this->param_06_value_set(v);
        break;
        }
    default:
        {
        index -= 6;

        if (index < this->p_01->getNumParameters())
            this->p_01->setParameterValue(index, v, time);

        index -= this->p_01->getNumParameters();

        if (index < this->p_02->getNumParameters())
            this->p_02->setParameterValue(index, v, time);

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
    case 2:
        {
        return this->param_03_value;
        }
    case 3:
        {
        return this->param_04_value;
        }
    case 4:
        {
        return this->param_05_value;
        }
    case 5:
        {
        return this->param_06_value;
        }
    default:
        {
        index -= 6;

        if (index < this->p_01->getNumParameters())
            return this->p_01->getParameterValue(index);

        index -= this->p_01->getNumParameters();

        if (index < this->p_02->getNumParameters())
            return this->p_02->getParameterValue(index);

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
    return 6 + this->p_01->getNumParameters() + this->p_02->getNumParameters();
}

ConstCharPointer getParameterName(ParameterIndex index) const {
    switch (index) {
    case 0:
        {
        return "release";
        }
    case 1:
        {
        return "attack";
        }
    case 2:
        {
        return "ratio";
        }
    case 3:
        {
        return "threshold";
        }
    case 4:
        {
        return "input_gain";
        }
    case 5:
        {
        return "parallel_mix";
        }
    default:
        {
        index -= 6;

        if (index < this->p_01->getNumParameters())
            return this->p_01->getParameterName(index);

        index -= this->p_01->getNumParameters();

        if (index < this->p_02->getNumParameters())
            return this->p_02->getParameterName(index);

        return "bogus";
        }
    }
}

ConstCharPointer getParameterId(ParameterIndex index) const {
    switch (index) {
    case 0:
        {
        return "release";
        }
    case 1:
        {
        return "attack";
        }
    case 2:
        {
        return "ratio";
        }
    case 3:
        {
        return "threshold";
        }
    case 4:
        {
        return "input_gain";
        }
    case 5:
        {
        return "parallel_mix";
        }
    default:
        {
        index -= 6;

        if (index < this->p_01->getNumParameters())
            return this->p_01->getParameterId(index);

        index -= this->p_01->getNumParameters();

        if (index < this->p_02->getNumParameters())
            return this->p_02->getParameterId(index);

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
            info->initialValue = 50;
            info->min = 0;
            info->max = 1000;
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
            info->initialValue = 5;
            info->min = 0;
            info->max = 1000;
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
        case 2:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 3;
            info->min = 0;
            info->max = 100;
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
        case 3:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = -30;
            info->min = -100;
            info->max = 10;
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
        case 4:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0;
            info->min = 0;
            info->max = 100;
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
        case 5:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 1;
            info->min = 0;
            info->max = 1;
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
        default:
            {
            index -= 6;

            if (index < this->p_01->getNumParameters())
                this->p_01->getParameterInfo(index, info);

            index -= this->p_01->getNumParameters();

            if (index < this->p_02->getNumParameters())
                this->p_02->getParameterInfo(index, info);

            break;
            }
        }
    }
}

void sendParameter(ParameterIndex index, bool ignoreValue) {
    this->getEngine()->notifyParameterValueChanged(index, (ignoreValue ? 0 : this->getParameterValue(index)), ignoreValue);
}

ParameterIndex getParameterOffset(BaseInterface* subpatcher) const {
    if (subpatcher == this->p_01)
        return 6;

    if (subpatcher == this->p_02)
        return 6 + this->p_01->getNumParameters();

    return 0;
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
    case 5:
        {
        {
            value = (value < 0 ? 0 : (value > 1 ? 1 : value));
            ParameterValue normalizedValue = (value - 0) / (1 - 0);
            return normalizedValue;
        }
        }
    case 2:
    case 4:
        {
        {
            value = (value < 0 ? 0 : (value > 100 ? 100 : value));
            ParameterValue normalizedValue = (value - 0) / (100 - 0);
            return normalizedValue;
        }
        }
    case 0:
    case 1:
        {
        {
            value = (value < 0 ? 0 : (value > 1000 ? 1000 : value));
            ParameterValue normalizedValue = (value - 0) / (1000 - 0);
            return normalizedValue;
        }
        }
    case 3:
        {
        {
            value = (value < -100 ? -100 : (value > 10 ? 10 : value));
            ParameterValue normalizedValue = (value - -100) / (10 - -100);
            return normalizedValue;
        }
        }
    default:
        {
        index -= 6;

        if (index < this->p_01->getNumParameters())
            return this->p_01->convertToNormalizedParameterValue(index, value);

        index -= this->p_01->getNumParameters();

        if (index < this->p_02->getNumParameters())
            return this->p_02->convertToNormalizedParameterValue(index, value);

        return value;
        }
    }
}

ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
    value = (value < 0 ? 0 : (value > 1 ? 1 : value));

    switch (index) {
    case 5:
        {
        {
            {
                return 0 + value * (1 - 0);
            }
        }
        }
    case 2:
    case 4:
        {
        {
            {
                return 0 + value * (100 - 0);
            }
        }
        }
    case 0:
    case 1:
        {
        {
            {
                return 0 + value * (1000 - 0);
            }
        }
        }
    case 3:
        {
        {
            {
                return -100 + value * (10 - -100);
            }
        }
        }
    default:
        {
        index -= 6;

        if (index < this->p_01->getNumParameters())
            return this->p_01->convertFromNormalizedParameterValue(index, value);

        index -= this->p_01->getNumParameters();

        if (index < this->p_02->getNumParameters())
            return this->p_02->convertFromNormalizedParameterValue(index, value);

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
    case 2:
        {
        return this->param_03_value_constrain(value);
        }
    case 3:
        {
        return this->param_04_value_constrain(value);
        }
    case 4:
        {
        return this->param_05_value_constrain(value);
        }
    case 5:
        {
        return this->param_06_value_constrain(value);
        }
    default:
        {
        index -= 6;

        if (index < this->p_01->getNumParameters())
            return this->p_01->constrainParameterValue(index, value);

        index -= this->p_01->getNumParameters();

        if (index < this->p_02->getNumParameters())
            return this->p_02->constrainParameterValue(index, value);

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
    case 1646922831:
        {
        this->snapshot_01_out_set(value);
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
    RNBO_UNUSED(objectId);
    this->updateTime(time);
    this->p_01->processNumMessage(tag, objectId, time, payload);
    this->p_02->processNumMessage(tag, objectId, time, payload);
}

void processListMessage(
    MessageTag tag,
    MessageTag objectId,
    MillisecondTime time,
    const list& payload
) {
    RNBO_UNUSED(objectId);
    this->updateTime(time);
    this->p_01->processListMessage(tag, objectId, time, payload);
    this->p_02->processListMessage(tag, objectId, time, payload);
}

void processBangMessage(MessageTag tag, MessageTag objectId, MillisecondTime time) {
    RNBO_UNUSED(objectId);
    this->updateTime(time);
    this->p_01->processBangMessage(tag, objectId, time);
    this->p_02->processBangMessage(tag, objectId, time);
}

MessageTagInfo resolveTag(MessageTag tag) const {
    switch (tag) {
    case TAG("compression"):
        {
        return "compression";
        }
    case TAG(""):
        {
        return "";
        }
    }

    auto subpatchResult_0 = this->p_01->resolveTag(tag);

    if (subpatchResult_0)
        return subpatchResult_0;

    auto subpatchResult_1 = this->p_02->resolveTag(tag);

    if (subpatchResult_1)
        return subpatchResult_1;

    return "";
}

MessageIndex getNumMessages() const {
    return 1;
}

const MessageInfo& getMessageInfo(MessageIndex index) const {
    switch (index) {
    case 0:
        {
        static const MessageInfo r0 = {
            "compression",
            Outport
        };

        return r0;
        }
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

    this->p_02_in6_number_set(v);
    this->p_01_in6_number_set(v);
}

void param_02_value_set(number v) {
    v = this->param_02_value_constrain(v);
    this->param_02_value = v;
    this->sendParameter(1, false);

    if (this->param_02_value != this->param_02_lastValue) {
        this->getEngine()->presetTouched();
        this->param_02_lastValue = this->param_02_value;
    }

    this->p_02_in5_number_set(v);
    this->p_01_in5_number_set(v);
}

void param_03_value_set(number v) {
    v = this->param_03_value_constrain(v);
    this->param_03_value = v;
    this->sendParameter(2, false);

    if (this->param_03_value != this->param_03_lastValue) {
        this->getEngine()->presetTouched();
        this->param_03_lastValue = this->param_03_value;
    }

    this->p_02_in4_number_set(v);
    this->p_01_in4_number_set(v);
}

void param_04_value_set(number v) {
    v = this->param_04_value_constrain(v);
    this->param_04_value = v;
    this->sendParameter(3, false);

    if (this->param_04_value != this->param_04_lastValue) {
        this->getEngine()->presetTouched();
        this->param_04_lastValue = this->param_04_value;
    }

    this->p_02_in3_number_set(v);
    this->p_01_in3_number_set(v);
}

void param_05_value_set(number v) {
    v = this->param_05_value_constrain(v);
    this->param_05_value = v;
    this->sendParameter(4, false);

    if (this->param_05_value != this->param_05_lastValue) {
        this->getEngine()->presetTouched();
        this->param_05_lastValue = this->param_05_value;
    }

    this->p_02_in2_number_set(v);
    this->p_01_in2_number_set(v);
}

void param_06_value_set(number v) {
    v = this->param_06_value_constrain(v);
    this->param_06_value = v;
    this->sendParameter(5, false);

    if (this->param_06_value != this->param_06_lastValue) {
        this->getEngine()->presetTouched();
        this->param_06_lastValue = this->param_06_value;
    }

    this->dspexpr_32_in3_set(v);
    this->dspexpr_31_in3_set(v);
}

void snapshot_01_out_set(number v) {
    this->snapshot_01_out = v;
    this->outport_01_input_number_set(v);
}

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
    return 2;
}

Index getNumOutputChannels() const {
    return 2;
}

void allocateDataRefs() {
    this->p_01->allocateDataRefs();
    this->p_02->allocateDataRefs();
}

void initializeObjects() {
    this->p_01->initializeObjects();
    this->p_02->initializeObjects();
}

void sendOutlet(OutletIndex index, ParameterValue value) {
    this->getEngine()->sendOutlet(this, index, value);
}

void startup() {
    this->updateTime(this->getEngine()->getCurrentTime());
    this->p_01->startup();
    this->p_02->startup();

    {
        this->scheduleParamInit(0, 0);
    }

    {
        this->scheduleParamInit(1, 0);
    }

    {
        this->scheduleParamInit(2, 0);
    }

    {
        this->scheduleParamInit(3, 0);
    }

    {
        this->scheduleParamInit(4, 0);
    }

    {
        this->scheduleParamInit(5, 0);
    }

    this->processParamInitEvents();
}

number param_01_value_constrain(number v) const {
    v = (v > 1000 ? 1000 : (v < 0 ? 0 : v));
    return v;
}

void p_02_in6_number_set(number v) {
    this->p_02->updateTime(this->_currentTime);
    this->p_02->eventinlet_08_out1_number_set(v);
}

void p_01_in6_number_set(number v) {
    this->p_01->updateTime(this->_currentTime);
    this->p_01->eventinlet_03_out1_number_set(v);
}

number param_02_value_constrain(number v) const {
    v = (v > 1000 ? 1000 : (v < 0 ? 0 : v));
    return v;
}

void p_02_in5_number_set(number v) {
    this->p_02->updateTime(this->_currentTime);
    this->p_02->eventinlet_07_out1_number_set(v);
}

void p_01_in5_number_set(number v) {
    this->p_01->updateTime(this->_currentTime);
    this->p_01->eventinlet_02_out1_number_set(v);
}

number param_03_value_constrain(number v) const {
    v = (v > 100 ? 100 : (v < 0 ? 0 : v));
    return v;
}

void p_02_in4_number_set(number v) {
    this->p_02->updateTime(this->_currentTime);
    this->p_02->eventinlet_10_out1_number_set(v);
}

void p_01_in4_number_set(number v) {
    this->p_01->updateTime(this->_currentTime);
    this->p_01->eventinlet_05_out1_number_set(v);
}

number param_04_value_constrain(number v) const {
    v = (v > 10 ? 10 : (v < -100 ? -100 : v));
    return v;
}

void p_02_in3_number_set(number v) {
    this->p_02->updateTime(this->_currentTime);
    this->p_02->eventinlet_09_out1_number_set(v);
}

void p_01_in3_number_set(number v) {
    this->p_01->updateTime(this->_currentTime);
    this->p_01->eventinlet_04_out1_number_set(v);
}

number param_05_value_constrain(number v) const {
    v = (v > 100 ? 100 : (v < 0 ? 0 : v));
    return v;
}

void p_02_in2_number_set(number v) {
    this->p_02->updateTime(this->_currentTime);
    this->p_02->eventinlet_06_out1_number_set(v);
}

void p_01_in2_number_set(number v) {
    this->p_01->updateTime(this->_currentTime);
    this->p_01->eventinlet_01_out1_number_set(v);
}

number param_06_value_constrain(number v) const {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    return v;
}

void dspexpr_32_in3_set(number v) {
    this->dspexpr_32_in3 = v;
}

void dspexpr_31_in3_set(number v) {
    this->dspexpr_31_in3 = v;
}

void outport_01_input_number_set(number v) {
    this->getEngine()->sendNumMessage(TAG("compression"), TAG(""), v, this->_currentTime);
}

void p_01_perform(const SampleValue * in1, SampleValue * out1, SampleValue * out2, Index n) {
    // subpatcher: compressor
    ConstSampleArray<1> ins = {in1};

    SampleArray<2> outs = {out1, out2};
    this->p_01->process(ins, 1, outs, 2, n);
}

void dspexpr_31_perform(
    const Sample * in1,
    const Sample * in2,
    number in3,
    SampleValue * out1,
    Index n
) {
    Index i;

    for (i = 0; i < n; i++) {
        out1[(Index)i] = in1[(Index)i] + in3 * (in2[(Index)i] - in1[(Index)i]);//#map:_###_obj_###_:1
    }
}

void snapshot_01_perform(const SampleValue * input_signal, Index n) {
    auto __snapshot_01_lastValue = this->snapshot_01_lastValue;
    auto __snapshot_01_calc = this->snapshot_01_calc;
    auto __snapshot_01_count = this->snapshot_01_count;
    auto __snapshot_01_nextTime = this->snapshot_01_nextTime;
    auto __snapshot_01_interval = this->snapshot_01_interval;
    number timeInSamples = this->msToSamps(__snapshot_01_interval, this->sr);

    if (__snapshot_01_interval > 0) {
        for (Index i = 0; i < n; i++) {
            if (__snapshot_01_nextTime <= __snapshot_01_count + (SampleIndex)(i)) {
                {
                    __snapshot_01_calc = input_signal[(Index)i];
                }

                this->getEngine()->scheduleClockEventWithValue(
                    this,
                    1646922831,
                    this->sampsToMs((SampleIndex)(this->vs)) + this->_currentTime,
                    __snapshot_01_calc
                );;

                __snapshot_01_calc = 0;
                __snapshot_01_nextTime += timeInSamples;
            }
        }

        __snapshot_01_count += this->vs;
    }

    __snapshot_01_lastValue = input_signal[(Index)(n - 1)];
    this->snapshot_01_nextTime = __snapshot_01_nextTime;
    this->snapshot_01_count = __snapshot_01_count;
    this->snapshot_01_calc = __snapshot_01_calc;
    this->snapshot_01_lastValue = __snapshot_01_lastValue;
}

void p_02_perform(const SampleValue * in1, SampleValue * out1, Index n) {
    // subpatcher: compressor
    ConstSampleArray<1> ins = {in1};

    SampleArray<1> outs = {out1};
    this->p_02->process(ins, 1, outs, 1, n);
}

void dspexpr_32_perform(
    const Sample * in1,
    const Sample * in2,
    number in3,
    SampleValue * out1,
    Index n
) {
    Index i;

    for (i = 0; i < n; i++) {
        out1[(Index)i] = in1[(Index)i] + in3 * (in2[(Index)i] - in1[(Index)i]);//#map:_###_obj_###_:1
    }
}

void stackprotect_perform(Index n) {
    RNBO_UNUSED(n);
    auto __stackprotect_count = this->stackprotect_count;
    __stackprotect_count = 0;
    this->stackprotect_count = __stackprotect_count;
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

void param_03_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_03_value;
}

void param_03_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_03_value_set(preset["value"]);
}

void param_04_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_04_value;
}

void param_04_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_04_value_set(preset["value"]);
}

void param_05_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_05_value;
}

void param_05_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_05_value_set(preset["value"]);
}

void param_06_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_06_value;
}

void param_06_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_06_value_set(preset["value"]);
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
    dspexpr_31_in1 = 0;
    dspexpr_31_in2 = 0;
    dspexpr_31_in3 = 0;
    p_01_target = 0;
    dspexpr_32_in1 = 0;
    dspexpr_32_in2 = 0;
    dspexpr_32_in3 = 0;
    p_02_target = 0;
    snapshot_01_interval = 5;
    snapshot_01_out = 0;
    param_01_value = 50;
    param_02_value = 5;
    param_03_value = 3;
    param_04_value = -30;
    param_05_value = 0;
    param_06_value = 1;
    _currentTime = 0;
    audioProcessSampleCount = 0;
    sampleOffsetIntoNextAudioBuffer = 0;
    zeroBuffer = nullptr;
    dummyBuffer = nullptr;
    signals[0] = nullptr;
    signals[1] = nullptr;
    didAllocateSignals = 0;
    vs = 0;
    maxvs = 0;
    sr = 44100;
    invsr = 0.00002267573696;
    snapshot_01_calc = 0;
    snapshot_01_nextTime = 0;
    snapshot_01_count = 0;
    snapshot_01_lastValue = 0;
    param_01_lastValue = 0;
    param_02_lastValue = 0;
    param_03_lastValue = 0;
    param_04_lastValue = 0;
    param_05_lastValue = 0;
    param_06_lastValue = 0;
    globaltransport_tempo = nullptr;
    globaltransport_state = nullptr;
    stackprotect_count = 0;
    _voiceIndex = 0;
    _noteNumber = 0;
    isMuted = 1;
}

// member variables

    number dspexpr_31_in1;
    number dspexpr_31_in2;
    number dspexpr_31_in3;
    number p_01_target;
    number dspexpr_32_in1;
    number dspexpr_32_in2;
    number dspexpr_32_in3;
    number p_02_target;
    number snapshot_01_interval;
    number snapshot_01_out;
    number param_01_value;
    number param_02_value;
    number param_03_value;
    number param_04_value;
    number param_05_value;
    number param_06_value;
    MillisecondTime _currentTime;
    UInt64 audioProcessSampleCount;
    SampleIndex sampleOffsetIntoNextAudioBuffer;
    signal zeroBuffer;
    signal dummyBuffer;
    SampleValue * signals[2];
    bool didAllocateSignals;
    Index vs;
    Index maxvs;
    number sr;
    number invsr;
    number snapshot_01_calc;
    number snapshot_01_nextTime;
    SampleIndex snapshot_01_count;
    number snapshot_01_lastValue;
    number param_01_lastValue;
    number param_02_lastValue;
    number param_03_lastValue;
    number param_04_lastValue;
    number param_05_lastValue;
    number param_06_lastValue;
    signal globaltransport_tempo;
    signal globaltransport_state;
    number stackprotect_count;
    Index _voiceIndex;
    Int _noteNumber;
    Index isMuted;
    indexlist paramInitIndices;
    indexlist paramInitOrder;
    RNBOSubpatcher_13* p_01;
    RNBOSubpatcher_14* p_02;

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

