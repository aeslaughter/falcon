#ifndef CONSTANT_H
#define CONSTANT_H

#include "Material.h"


//Forward Declarations
class Constant;

template<>
InputParameters validParams<Constant>();

/**
 * Simple material with constant properties.
 */
class Constant : public Material
{
public:
  Constant(std::string name,
           MooseSystem & moose_system,
           InputParameters parameters);
  
protected:
  virtual void computeProperties();
  
private:

  bool _has_temp;
  std::vector<Real> & _temp;

  Real _my_thermal_conductivity;
  Real _my_thermal_expansion;
  Real _my_biot_coeff;  
  Real _my_specific_heat;
  Real _my_density;
  Real _my_youngs_modulus;
  Real _my_poissons_ratio;
  Real _my_t_ref;

  std::vector<Real> & _thermal_conductivity;
  std::vector<Real> & _thermal_strain;
  std::vector<Real> & _alpha;
  std::vector<Real> & _biot_coeff;
  std::vector<Real> & _specific_heat;
  std::vector<Real> & _density;
  std::vector<Real> & _rho_r;
  std::vector<Real> & _youngs_modulus;
  std::vector<Real> & _poissons_ratio;
};

#endif //CONSTANT_H
