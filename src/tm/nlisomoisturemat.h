/*
 *
 *                 #####    #####   ######  ######  ###   ###
 *               ##   ##  ##   ##  ##      ##      ## ### ##
 *              ##   ##  ##   ##  ####    ####    ##  #  ##
 *             ##   ##  ##   ##  ##      ##      ##     ##
 *            ##   ##  ##   ##  ##      ##      ##     ##
 *            #####    #####   ##      ######  ##     ##
 *
 *
 *             OOFEM : Object Oriented Finite Element Code
 *
 *               Copyright (C) 1993 - 2012   Borek Patzak
 *
 *
 *
 *       Czech Technical University, Faculty of Civil Engineering,
 *   Department of Structural Mechanics, 166 29 Prague, Czech Republic
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#ifndef nlisomoisturemat_h
#define nlisomoisturemat_h

#include "isomoisturemat.h"
#include "flotarry.h"


namespace oofem {
/**
 * This class implements various functions for concrete moisture permeability and moisture capacity
 */
class NlIsoMoistureMaterial : public IsotropicMoistureTransferMaterial
{

protected:
  enum isothermType {linear, multilinear, Ricken, Kuenzel, Hansen, BSB} Isotherm;

  /// density of the dry solid phase
  double rhodry;

  /// values of the linear isotherm
  double moistureCapacity;

  /// values of the multilinear isotherm
  FloatArray iso_h;
  FloatArray iso_wh;

  /// parameters of the Ricken isotherm
  double dd; 

 /// parameters of the Kuenzel isotherm
  double wf, b; 

  /// parameters of the isotherm proposed by P. Freiesleben Hansen (Coupled moisture/heat transport in cross sections of structures, Beton og Konstruktionsinstituttet, 1985)
  double uh, A, nn;  

  /// parameters of the BSB isotherm
  double c, k, Vm;


  enum permeabilityType {multilin, Bazant, Xi} Permeability;

  /// values of the multilinear permeability
  FloatArray perm_h;
  FloatArray perm_ch;

  /// "permeability" according to Bazant
  double C1, n, alpha0, hC;

  /// permeability parameters according to Xi, Bazant & Jennings
  double alphah, betah, gammah;


public:
    NlIsoMoistureMaterial(int n, Domain *d) : IsotropicMoistureTransferMaterial(n, d) { }
    virtual ~NlIsoMoistureMaterial() { }

    /// evaluates slope of the sorption isotherm
    virtual double giveMoistureCapacity(GaussPoint *gp, TimeStep *atTime);
    virtual double givePermeability(GaussPoint *gp, TimeStep *atTime);

    virtual const char *giveClassName() const { return "NlIsoMoistureMaterial"; }
    virtual classType giveClassID() const { return NlIsoMoistureMaterialClass; }

    double giveHumidity(GaussPoint *gp);

    virtual IRResultType initializeFrom(InputRecord *ir);

};
} // end namespace oofem
#endif // nlisomoisturemat_h
