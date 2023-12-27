#ifndef CARBON_SINK_CALCULATOR_H
#define CARBON_SINK_CALCULATOR_H

struct CarbonSinkForm;
class CarbonSinkCalculator
{
  public:
    CarbonSinkCalculator(CarbonSinkForm const& form);
    ~CarbonSinkCalculator();

    [[nodiscard]] double calculate() const;

  private:
    CarbonSinkForm const& _form;
};

#endif