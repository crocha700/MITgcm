C $Header: /u/gcmpack/MITgcm/verification/offline_exf_seaice/code_ad/SEAICE_OPTIONS.h,v 1.8 2012/02/07 18:53:14 gforget Exp $
C $Name:  $

C     *==========================================================*
C     | SEAICE_OPTIONS.h
C     | o CPP options file for sea ice package.
C     *==========================================================*
C     | Use this file for selecting options within the sea ice
C     | package.
C     *==========================================================*

#ifndef SEAICE_OPTIONS_H
#define SEAICE_OPTIONS_H
#include "PACKAGES_CONFIG.h"
#include "CPP_OPTIONS.h"

#ifdef ALLOW_SEAICE
C     Package-specific Options & Macros go here

C--   Write "text-plots" of certain fields in STDOUT for debugging.
#undef SEAICE_DEBUG

C--   Allow sea-ice dynamic code.
C     This option is provided to allow use of TAMC
C     on the thermodynamics component of the code only.
C     Sea-ice dynamics can also be turned off at runtime
C     using variable SEAICEuseDYNAMICS.
#undef SEAICE_ALLOW_DYNAMICS

C--   By default, the sea-ice package uses its own integrated bulk
C     formulae to compute fluxes (fu, fv, EmPmR, Qnet, and Qsw) over
C     open-ocean.  When this flag is set, these variables are computed
C     in a separate external package, for example, pkg/exf, and then
C     modified for sea-ice effects by pkg/seaice.
#define SEAICE_EXTERNAL_FLUXES

C--   By default, the sea-ice package uses 2-category thermodynamics.
C     When this flag is set, an 8-category calculation of ice
C     thermodynamics is carried out in groatb.F
C     Note the pickup_seaice.* generated by this option differ
C     from those generated with the default 2-category model.
C     Therefore it is not possible to switch between the two
C     in the middle of an integration.
#undef SEAICE_MULTICATEGORY

C--   Use the Old version of seaice_growth (close to cvs version 1.70)
C     otherwise, use the merged version (with some of Ian Fenty s code)
#define SEAICE_GROWTH_LEGACY

C--   options only available in the merged version (from Ian Fenty s code)
#ifndef SEAICE_GROWTH_LEGACY
C-    to ensure heat conservation in the coupled ocean-seaice system
# undef SEAICE_HEAT_CONSERV_FIX
C-    to switch on/off open-water freezing contribution to thickness tendency:
# define SEAICE_DO_OPEN_WATER_GROWTH
C-    ifdef SEAICE_DO_OPEN_WATER_GROWTH then define SEAICE_DO_OPEN_WATER_MELT
C     to also allow open-water air-sea heat fluxes melt ice
# undef SEAICE_DO_OPEN_WATER_MELT
C-    to switch on/off ocean heat contribution to seaice cover reduction:
# define SEAICE_OCN_MELT_ACT_ON_AREA
C-    to preclude infinitesimal ice concentrations:
# undef ALLOW_PRECLUDE_INFINITESIMAL_AREA
#endif

C--   Use the Old version of seaice_solve4temp (formerly seaice_budget_ice)
C     otherwise, use Ian Fenty s version
#define SEAICE_SOLVE4TEMP_LEGACY

C--   By default the freezing point of water is set to the value of
C     the parameter SEAICE_freeze (=-1.96 by default). To use a
C     simple linear dependence of the freezing point on salinity,
C     set the following flag (pressure is assumed to have no effect,
C     which is a good assumption for the top 20 meters). With this
C     option defined the parameter SEAICE_freeze has no effect.
#undef SEAICE_VARIABLE_FREEZING_POINT

C--   Allow SEAICEuseFlooding, which converts snow to ice if submerged.
#undef ALLOW_SEAICE_FLOODING

C--   By default sea ice is fresh.  Set following flag for salty ice.
#undef SEAICE_VARIABLE_SALINITY

C--   Tracers of ice and/or ice cover.
#undef ALLOW_SITRACER
#ifdef ALLOW_SITRACER
C--   To try avoid 'spontaneous generation' of tracer maxima by advdiff.
# define ALLOW_SITRACER_ADVCAP
#endif

C--   By default the seaice model is discretized on a B-Grid (for
C     historical reasons). Define the following flag to use a new
C     (not thoroughly) test version on a C-grid
#undef SEAICE_CGRID

C--   Only for the C-grid version it is possible to
#ifdef SEAICE_CGRID
C     enable EVP code by defining the following flag
# define SEAICE_ALLOW_EVP
# ifdef SEAICE_ALLOW_EVP
C--   When set use SEAICE_zetaMin and SEAICE_evpDampC to limit
C--   viscosities from below and above in seaice_evp
C--   not necessary, and not recommended
#  undef SEAICE_ALLOW_CLIPZETA
# endif /* SEAICE_ALLOW_EVP */
C     allow the truncated ellipse rheology (runtime flag SEAICEuseTEM)
# undef SEAICE_ALLOW_TEM
#else /* not SEAICE_CGRID, but old B-grid */
C--   By default for B-grid dynamics solver wind stress under sea-ice is
C     set to the same value as it would be if there was no sea-ice.
C     Define following CPP flag for B-grid ice-ocean stress coupling.
# undef SEAICE_BICE_STRESS

C--   By default for B-grid dynamics solver surface tilt is obtained
C     indirectly via geostrophic velocities. Define following CPP
C     in order to use ETAN instead.
# undef EXPLICIT_SSH_SLOPE
C--   Defining this flag turns on a FV-discretization of the B-grid LSOR
C     solver. It is smoother and includes all metric terms, similar to the
C     C-grid solver. It is here for completeness, but its usefulness is
C     unclear.
# undef SEAICE_LSRBNEW
#endif /* SEAICE_CGRID */

C--   When set use MAX_HEFF to cap sea ice thickness in seaice_growth
#undef SEAICE_CAP_HEFF
C--   When set limit the Ice-Loading to mass of 1/5 of Surface ocean grid-box
#undef SEAICE_CAP_ICELOAD
C--   When set use SEAICE_clipVelocties = .true., to clip U/VICE at 40cm/s,
C--   not recommended
#undef SEAICE_ALLOW_CLIPVELS

C     enable free drift code
#undef SEAICE_ALLOW_FREEDRIFT

#endif /* ALLOW_SEAICE */
#endif /* SEAICE_OPTIONS_H */

CEH3 ;;; Local Variables: ***
CEH3 ;;; mode:fortran ***
CEH3 ;;; End: ***
