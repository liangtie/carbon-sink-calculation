#include "carbon_sink_form.h"
#include "carbon_sink_calculator.h"

double CarbonSinkForm::getCarbonSink() const
{
    return CarbonSinkCalculator(*this).calculate();
}
