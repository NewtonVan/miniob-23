#include <cmath>
namespace common {

float roundToNDecimalPlaces(float number, int decimalPlaces)
{
  float multiplier = std::pow(10, decimalPlaces);
  return std::round(number * multiplier) / multiplier;
}

}  // namespace common
