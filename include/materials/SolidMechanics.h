#ifndef SOLIDMECHANICS_H
#define SOLIDMECHANICS_H

#include "PorousMedia.h"
#include "ColumnMajorMatrix.h"

//libMesh includes
#include "tensor_value.h"
#include "vector_value.h"


//Forward Declarations
class SolidMechanics;

template<>
InputParameters validParams<SolidMechanics>();

/**
 * Simple material with SolidMechanics properties.
 */
class SolidMechanics : virtual public PorousMedia
{
public:
  SolidMechanics(const std::string & name,
                 InputParameters parameters);
  
protected:
  static Real randn_trig(Real mu=0.0,Real sigma=1.0)
  {
    static bool deviateAvailable=false;
    static Real storedDeviate;
    Real dist, angle, PI=3.14159265;
    if(!deviateAvailable)
    {
      dist=std::sqrt(-2.0 * std::log(double(rand()) / double(RAND_MAX)) );
      angle=2.0 * PI * (double(rand()) / double(RAND_MAX));
      storedDeviate=dist*std::cos(angle);
      deviateAvailable=true;
      return dist * std::sin(angle) * sigma + mu;
    }
    else
    {
      deviateAvailable=false;
      return storedDeviate * sigma + mu;
    }
  }

  static void rotateSymmetricTensor( const ColumnMajorMatrix & , const RealTensorValue & ,
                                     RealTensorValue & );

  void computeDamage(const int qp); //damage mechanics
  void computeAnisoDamage(const int qp);//anisotropic damage

  void computeCrack_tension(const int qp); //tensile induce cracking
  void computeCrack_Mohr_Coulomb_v1(const int qp); //Mohr_Coulomb criteria
  void computeCrack_Mohr_Coulomb_v2(const int qp); //Mohr_Coulomb criteria
   virtual void computeProperties();

  bool _has_temp;
  VariableGradient & _grad_temp;
  VariableValue  & _temperature;
   
  bool _has_x_disp;
  VariableGradient & _grad_x_disp;
  bool _has_y_disp;
  VariableGradient & _grad_y_disp;
  bool _has_z_disp;
  VariableGradient & _grad_z_disp;

  Real _input_thermal_expansion;
  Real _input_youngs_modulus;
  Real _input_poissons_ratio;

  Real _input_biot_coeff;
  Real _input_t_ref;
  
  bool _has_damage;
  Real _input_damage_coeff;             //initial damage between [0,1]
  Real _input_strain_initialize_damage; //critical strain to lnitialize damage
  Real _input_strain_broken;            //critical strain for complete failure
  Real _damage_a1;                      //parameters for youngs modulus and damage factor
  Real _damage_a2;

  std::string _has_damage_method;
  Real _input_damage_c;
  Real _input_damage_n;
  Real _input_strain_init;
  Real _input_strain_strength;

  bool _has_crack;
  std::string _has_crack_method; // true <==> tensile_induced_crack  false<==>Mohr_Coulomb
  Real _critical_crack_strain;
  Real _cohesion;
  Real _friction_angle;

  bool _has_damage_couple_permeability;
  Real _damage_couple_permeability_coeff1;//not used temperally
  Real _damage_couple_permeability_coeff2;

  ColumnMajorMatrix _total_strain;
  TensorValue<Real> _total_stress;
  ColumnMajorMatrix _total_stress1;
  
  MaterialProperty<Real> & _thermal_strain;
  MaterialProperty<Real> & _alpha;
  MaterialProperty<Real> & _youngs_modulus;
  MaterialProperty<Real> & _poissons_ratio;
  MaterialProperty<Real> & _biot_coeff;
  MaterialProperty<Real> & _damage_coeff;
  MaterialProperty<Real> & _strain_history;

  MaterialProperty<Real> & _damage_coeff_old;//newly added
  MaterialProperty<Real> & _strain_history_old;//newly added
  

  MaterialProperty<RealVectorValue> & _stress_normal_vector;
  MaterialProperty<RealVectorValue> & _stress_shear_vector;
  MaterialProperty<RealVectorValue> & _strain_normal_vector;
  MaterialProperty<RealVectorValue> & _strain_shear_vector;

  MaterialProperty<bool> * _init_status;
  MaterialProperty<Real> & _bond_nstiff;
  MaterialProperty<Real> & _bond_sstiff;

  MaterialProperty<Real> & _bond_damage_factor00;
  MaterialProperty<Real> & _bond_damage_factor00_old;

  MaterialProperty<Real> & _bond_damage_factor01;
  MaterialProperty<Real> & _bond_damage_factor01_old;

  MaterialProperty<Real> & _bond_damage_factor02;
  MaterialProperty<Real> & _bond_damage_factor02_old;

  MaterialProperty<Real> & _bond_damage_factor03;
  MaterialProperty<Real> & _bond_damage_factor03_old;

  MaterialProperty<Real> & _bond_damage_factor04;
  MaterialProperty<Real> & _bond_damage_factor04_old;

  MaterialProperty<Real> & _bond_damage_factor05;
  MaterialProperty<Real> & _bond_damage_factor05_old;

  MaterialProperty<Real> & _bond_damage_factor06;
  MaterialProperty<Real> & _bond_damage_factor06_old;

  MaterialProperty<Real> & _bond_damage_factor07;
  MaterialProperty<Real> & _bond_damage_factor07_old;

  MaterialProperty<Real> & _bond_damage_factor08;
  MaterialProperty<Real> & _bond_damage_factor08_old;

  MaterialProperty<Real> & _bond_damage_factor09;
  MaterialProperty<Real> & _bond_damage_factor09_old;

  MaterialProperty<Real> & _bond_damage_factor10;
  MaterialProperty<Real> & _bond_damage_factor10_old;

  MaterialProperty<Real> & _bond_damage_factor11;
  MaterialProperty<Real> & _bond_damage_factor11_old;

  MaterialProperty<Real> & _bond_damage_factor12;
  MaterialProperty<Real> & _bond_damage_factor12_old;

  MaterialProperty<RealVectorValue> * _crack_flags;
  MaterialProperty<RealVectorValue> * _crack_flags_old;
  
  Real _E;
  Real _nu;
  Real _c1;
  Real _c2;
  Real _c3;
};

#endif //SOLIDMECHANICS_H
