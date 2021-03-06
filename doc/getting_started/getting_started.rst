.. _chap_getting_started:

Getting Started with MITgcm
***************************

This chapter is divided into two main parts. The first part, which is
covered in sections :numref:`whereToFindInfo` through
:numref:`run_the_model`, contains information about how to download, build and run the  MITgcm.
The second part, covered in :numref:`chap_modelExamples`, contains a set of
step-by-step tutorials for running specific pre-configured atmospheric
and oceanic experiments.

We believe the best way to familiarize yourself with the
model is to run the case study examples provided in the MITgcm repository. 
Information is also provided
here on how to customize the code when you are ready to try implementing 
the configuration you have in mind.  The code and algorithm
are described more fully in :numref:`discret_algorithm` and 
:numref:`sarch`. 

.. _whereToFindInfo:

Where to find information
=========================


There is a web-archived support mailing list for the model that you can
email at MITgcm-support@mitgcm.org.

To sign up for the mailing list (highly recommended), click `here <http://mailman.mitgcm.org/mailman/listinfo/mitgcm-support/>`_ 

To browse through the support archive, click `here <http://mailman.mitgcm.org/pipermail/mitgcm-support/>`_


Obtaining the code
==================

The MITgcm code and documentation are under continuous development and we generally recommend that one downloads the latest version of the code. You will need to decide if you want to work in a “git-aware” environment (`Method 1`_) or with a one-time “stagnant” download (`Method 2`_). We generally recommend method 1, as it is more flexible and allows your version of the code to be regularly updated as MITgcm developers check in bug fixes and new features. However, this typically requires at minimum a rudimentary understanding of git in order to make it worth one’s while. 

Periodically we release an official checkpoint (or “tag”). We recommend one download the latest code, unless there are reasons for obtaining a specific checkpoint (e.g. duplicating older results, collaborating with someone using an older release, etc.) 

Method 1
--------

This section describes how to download git-aware copies of the repository.
In a terminal window, cd to the directory where you want your code to reside. 
Type:

::

    % git clone https://github.com/altMITgcm/MITgcm.git

This will download the latest available code. If you now want to revert this code to a specific checkpoint release,
first ``cd`` into the MITgcm directory you just downloaded, then type ``git checkout checkpointXXX`` where ``XXX`` is the checkpoint version.

Alternatively, if you prefer to use ssh keys (say for example, you have a firewall which won’t allow a https download), type:

::

    % git clone git@github.com:altMITgcm/MITgcm.git

You will need a GitHub account for this, and will have to generate a ssh key though your GitHub account user settings. 

The fully git-aware download is over several hundred MB, which is considerable if one has limited internet download speed. In comparison, the one-time download zip file (`Method 2`_, below) is order 100MB. However, one can obtain a truncated, yet still git-aware copy of the current code by adding the option ``--depth=1`` to the git clone command above; all files will be present, but it will not include the full git history. However, the repository can be updated going forward. 

Method 2
--------

This section describes how to do a one-time download of the MITgcm, NOT git-aware.
In a terminal window, ``cd`` to the directory where you want your code to reside. 
To obtain the current code, type:

::

    % wget https://github.com/altMITgcm/MITgcm/archive/master.zip

For specific checkpoint release ``XXX``, instead type: 

::

    % wget https://github.com/altMITgcm/MITgcm/archive/checkpointXXX.zip

Updating the code
=================

There are several different approaches one can use to obtain updates to the MITgcm; which is best for you depends a bit on how you intend to use the MITgcm and your knowledge of git (and/or willingness to learn). Below we outline three suggested update pathways:

1. **Fresh Download of the MITgcm**

This approach is the most simple, and virtually foolproof. Whether you downloaded the code from a static zip file (`Method 2`_) or used the git clone command (`Method 1`_), create a new directory and repeat this procedure to download a current copy of the MITgcm. Say for example you are starting a new research project, this would be a great time to grab the most recent code repository and keep this new work entirely separate from any past simulations. This approach requires no understanding of git, and you are free to make changes to any files in the MIT repo tree (although we generally recommend that you avoid doing so, instead working in new subdirectories or on separate scratch disks as described in :numref:`build_elsewhere`, for example). 

2. **Using** ``git pull`` **to update the (unmodified) MITgcm repo tree**

If you have downloaded the code through a git clone command (`Method 1`_ above), you can incorporate any changes to the source code (including any changes to any files in the MITgcm repository, new packages or analysis routines, etc.) that may have occurred since your original download. There is a simple command to bring all code in the repository to a ‘current release’ state. From the MITgcm top directory or any of its subdirectories, type:

::

    % git pull

and all files will be updated to match the current state of the code repository, as it exists at `GitHub <https://github.com/altMITgcm/MITgcm.git>`_. (*Note:* if you plan to contribute to the MITgcm and followed the steps to download the code as described in 
:numref:`chap_contributing`, you will need to type ``git pull upstream`` instead.)

This update pathway is ideal if you are in the midst of a project and you want to incorporate new MITgcm features into your executable(s), or take advantage of recently added analysis utilties, etc. After the git pull, any changes in model source code and include files will be updated, so you can repeat the build procedure (:numref:`building_code`) and you will include all these new features in your new executable.

Be forewarned, this will only work if you have not modified ANY of the files in the MITgcm repository (adding new files is ok; also, all verification run subdirectories ``build`` and ``run`` are also ignored by git). If you have modified files and the ``git pull`` fails with errors, there is no easy fix other than to learn something about git (continue reading...)

3. **Fully embracing the power of git!**

Git offers many tools to help organize and track changes in your work.  For example, one might keep separate projects on different branches, and update the code separately (using ``git pull``) on these separate branches. You can even make changes to code in the MIT repo tree; when git then tries to update code from upstream (see :numref:`git_setup`), it will notify you about possible conflicts and even merge the code changes together if it can. You can also use ``git commit`` to help you track what you are modifying in your simulations over time. If you're planning to submit a pull request to include your changes, you should read the contributing guide in :numref:`chap_contributing`, and you may find it easier to work on a separate, fresh copy of the code. See here (...) for more information and how to use git effectively to manage your workflow.

(we should be more specific above, need to agree how so however)

Model and directory structure
=============================

The “numerical” model is contained within a execution environment
support wrapper. This wrapper is designed to provide a general framework
for grid-point models; MITgcm is a specific numerical model that makes use of
this framework (see chapWrapper for additional detail). Under this structure,
the model is split into execution
environment support code and conventional numerical model code. The
execution environment support code is held under the ``eesupp``
directory. The grid point model code is held under the ``model``
directory. Code execution actually starts in the ``eesupp`` routines and
not in the ``model`` routines. For this reason the top-level ``MAIN.F``
is in the ``eesupp/src`` directory. In general, end-users should not
need to worry about the wrapper support code. The top-level routine for the numerical
part of the code is in ``model/src/THE_MODEL_MAIN.F``. Here is a brief
description of the directory structure of the model under the root tree.

-  ``model``: this directory contains the main source code. Also
   subdivided into two subdirectories ``inc`` (includes files) and ``src`` (source code).

-  ``eesupp``: contains the execution environment source code. Also
   subdivided into two subdirectories ``inc`` and ``src``.

-  ``pkg``: contains the source code for the packages. Each package
   corresponds to a subdirectory. For example, ``gmredi`` contains the
   code related to the Gent-McWilliams/Redi scheme, ``aim`` the code
   relative to the atmospheric intermediate physics. The packages are
   described in detail in :numref:`packagesI`].

-  ``doc``: contains the MITgcm documentation in reStructured Text (rst) format.

-  ``tools``: this directory contains various useful tools. For example,
   ``genmake2`` is a script written in bash that should be used
   to generate your makefile. The directory ``adjoint`` contains the
   makefile specific to the Tangent linear and Adjoint Compiler (TAMC)
   that generates the adjoint code. The latter is described in detail in
   part [chap.ecco]. This directory also contains the subdirectory
   build\_options, which contains the ‘optfiles’ with the compiler
   options for the different compilers and machines that can run MITgcm (see :numref:`genmake2_optfiles`).

-  ``utils``: this directory contains various utilities. The
   subdirectory ``knudsen2`` contains code and a makefile that compute
   coefficients of the polynomial approximation to the knudsen formula
   for an ocean nonlinear equation of state. The ``matlab`` subdirectory
   contains matlab scripts for reading model output directly into
   matlab. The subdirectory ``python`` contains similar routines for python.
   ``scripts`` contains C-shell post-processing scripts for
   joining processor-based and tiled-based model output. 
   The subdirectory ``exch2`` contains the code needed for the exch2 package to
   work with different combinations of domain decompositions.

-  ``verification``: this directory contains the model examples. See
   numref:`chap_modelExamples`.

-  ``jobs``: contains sample job scripts for running MITgcm.

-  ``lsopt``: Line search code used for optimization.

-  ``optim``: Interface between MITgcm and line search code.

.. _building_code:

Building the code
=================

To compile the code, we use the ``make`` program. This uses a file
(``Makefile``) that allows us to pre-process source files, specify
compiler and optimization options and also figures out any file
dependencies. We supply a script (``genmake2``), described in section
:numref:`genmake2_desc`, that automatically creates the ``Makefile`` for you. You
then need to build the dependencies and compile the code.

As an example, assume that you want to build and run experiment
``verification/exp2``. Let’s build the code in ``verification/exp2/build``:

::

    % cd verification/exp2/build

First, build the ``Makefile``:

::

    % ../../../tools/genmake2 -mods ../code

The ``-mods`` command line option tells ``genmake2`` to override model source code
with any files in the directory ``../code/``. This and additional ``genmake2`` command line options are described
more fully in :numref:`genmake_commandline`.

On many systems, the ``genmake2`` program will be able to automatically
recognize the hardware, find compilers and other tools within the user’s
path (“``echo $PATH``”), and then choose an appropriate set of options
from the files (“optfiles”) contained in the ``tools/build_options``
directory. Under some circumstances, a user may have to create a new
optfile in order to specify the exact combination of compiler,
compiler flags, libraries, and other options necessary to build a
particular configuration of MITgcm. In such cases, it is generally
helpful to peruse the existing optfiles and mimic their syntax.
See :numref:`genmake2_optfiles`.

The MITgcm developers are willing to
provide help writing or modifing optfiles. And we encourage users to
ask for assistance or post new optfiles (particularly ones for new machines or
architectures) through the `GitHub issue tracker <https://github.com/altMITgcm/MITgcm/issues>`_
or email the MITgcm-support@mitgcm.org list.

To specify an optfile to ``genmake2``, the command line syntax is:

::

    % ../../../tools/genmake2 -mods ../code -of /path/to/optfile

Once a ``Makefile`` has been generated, we create the dependencies with
the command:

::

    % make depend

This modifies the ``Makefile`` by attaching a (usually, long) list of
files upon which other files depend. The purpose of this is to reduce
re-compilation if and when you start to modify the code. The ``make depend``
command also creates links from the model source to this directory, except for links to those files 
in the specified ``-mods`` directory. **IMPORTANT NOTE:** Editing the source code files in the build directory
will not edit a local copy (since these are just links) but will edit the original files in ``model/src`` (or ``model/inc``)
or in the specified ``-mods`` directory. While the latter might be what you intend, editing the copy in ``model/src``
is usually not intended and may cause grief somewhere down the road. Rather, if you need to add 
to the list of modified source code files, make a copy of
the file(s) to edit in the ``-mods`` directory, make the edits, 
and then re-build the makefile (the latter step critical or the makefile will not 
link to to this newly edited file).

It is important to note that the make depend stage will occasionally
produce warnings or errors if the dependency parsing tool is unable
to find all of the necessary header files (e.g., ``netcdf.inc``). In some cases you
may need to obtain help from your system administrator to locate these files.

Next, one can compile the code using:

::

    % make

The ``make`` command creates an executable called ``mitgcmuv``. Additional
make “targets” are defined within the makefile to aid in the production
of adjoint and other versions of MITgcm. On computers with multiple processor cores
or shared multi-processor (a.k.a. SMP) systems, the build process can often be sped
up appreciably using the command:

::

    % make -j 2

where the “2” can be replaced with a number that corresponds to the
number of cores (or discrete CPUs) available.

Now you are ready to run the model. General instructions for doing so
are given in section :numref:`run_the_model`. 

.. _build_elsewhere:

Building/compiling the code elsewhere
-------------------------------------

In the example above (:numref:`building_code`) we built the
executable in the ``build`` directory of the experiment.
Model object files and output data can use up large amounts of disk
space so it is often preferable to operate on a large
scratch disk. Here, we show how to configure and compile the code on a scratch disk,
without having to copy the entire source
tree. The only requirement to do so is you have ``genmake2`` in your path, or
you know the absolute path to ``genmake2``.
-
Assuming the model source is in ``~/MITgcm``, then the
following commands will build the model in ``/scratch/exp2-run1``:

::

    % cd /scratch/exp2-run1
    % ~/MITgcm/tools/genmake2 -rootdir ~/MITgcm \
      -mods ~/MITgcm/verification/exp2/code
    % make depend
    % make

Note the use of the command line option ``-rootdir`` to tell genamke2 where to find the MITgcm directory tree.

In general, one can compile the code in any given directory following this procedure.

.. _genmake2_desc:

Using ``genmake2``
------------------

This section describes further details and capabilities of ``genmake2`` (located in the
``tools`` directory), the MITgcm tool used to generate a Makefile. ``genmake2`` is a shell
script written to work with all “sh”–compatible shells including bash
v1, bash v2, and Bourne. ``genmake2`` parses information from the
following sources:

-
    a ``genmake_local`` file if one is found in the current directory

-
    command-line options

-
    an “options file” as specified by the command-line option
    ``–of /path/to/filename``

-
    a ``packages.conf`` file (if one is found) with the specific list of
    packages to compile. The search path for file ``packages.conf`` is
    first the current directory, and then each of the ``-mods`` directories
    in the given order (see below).

.. _genmake2_optfiles:

Optfiles in ``tools/build_options`` directory:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The purpose of the optfiles is to provide all the compilation options
for particular “platforms” (where “platform” roughly means the
combination of the hardware and the compiler) and code configurations.
Given the combinations of possible compilers and library dependencies
(e.g., MPI and NetCDF) there may be numerous optfiles available for a
single machine. The naming scheme for the majority of the optfiles
shipped with the code is **OS_HARDWARE_COMPILER** where

**OS**
    is the name of the operating system (generally the lower-case output
    of a linux terminal ``uname`` command)

**HARDWARE**
    is a string that describes the CPU type and corresponds to output
    from a ``uname -m`` command. Some common CPU types:

    amd64
        is for x86\_64 systems (most common, including AMD and Intel 64-bit CPUs)

    ia64
        is for Intel IA64 systems (eg. Itanium, Itanium2)

    ppc
        is for (old) Mac PowerPC systems

**COMPILER**
    is the compiler name (generally, the name of the FORTRAN executable)

In many cases, the default optfiles are sufficient and will result in
usable Makefiles. However, for some machines or code configurations, new
optfiles must be written. To create a new optfile, it is generally
best to start with one of the defaults and modify it to suit your needs.
Like ``genmake2``, the optfiles are all written using a simple
sh–compatible syntax. While nearly all variables used within
``genmake2`` may be specified in the optfiles, the critical ones that
should be defined are:

``FC``
    the FORTRAN compiler (executable) to use

``DEFINES``
    the command-line DEFINE options passed to the compiler

``CPP``
    the C pre-processor to use

``NOOPTFLAGS``
    options flags for special files that should not be optimized

For example, the optfile for a typical Red Hat Linux machine (amd64
architecture) using the GCC (g77) compiler is

::

    FC=g77
    DEFINES='-D_BYTESWAPIO -DWORDLENGTH=4'
    CPP='cpp  -traditional -P'
    NOOPTFLAGS='-O0'
    #  For IEEE, use the "-ffloat-store" option
    if test "x$IEEE" = x ; then
        FFLAGS='-Wimplicit -Wunused -Wuninitialized'
        FOPTIM='-O3 -malign-double -funroll-loops'
    else
        FFLAGS='-Wimplicit -Wunused -ffloat-store'
        FOPTIM='-O0 -malign-double'
    fi

If you write an optfile for an unrepresented machine or compiler, you
are strongly encouraged to submit the optfile to the MITgcm project for
inclusion. Please submit the file through the `GitHub issue tracker <https://github.com/altMITgcm/MITgcm/issues>`_
or email the MITgcm-support@mitgcm.org list.

.. _genmake_commandline:

Command-line options:
~~~~~~~~~~~~~~~~~~~~~

In addition to the optfiles, ``genmake2`` supports a number of helpful
command-line options. A complete list of these options can be obtained by:

::

    % genmake2 -h

The most important command-line options are:

``–optfile /path/to/file``
    specifies the optfile that should be used for a particular build.

    If no optfile is specified (either through the command line or the
    ``MITGCM_OPTFILE`` environment variable), ``genmake2`` will try to make a
    reasonable guess from the list provided in ``tools/build_options``.
    The method used for making this guess is to first determine the
    combination of operating system and hardware (eg. “linux\_amd64”) and
    then find a working FORTRAN compiler within the user’s path. When
    these three items have been identified, genmake2 will try to find an
    optfile that has a matching name.

``–mods ’dir1 dir2 dir3 ...’``
    specifies a list of directories containing “modifications”. These
    directories contain files with names that may (or may not) exist in
    the main MITgcm source tree but will be overridden by any
    identically-named sources within the ``-mods`` directories.

    The order of precedence for this “name-hiding” is as follows:

    -  “mods” directories (in the order given)

    -  Packages either explicitly specified or provided by default (in
       the order given)

    -  Packages included due to package dependencies (in the order that
       that package dependencies are parsed)

    -  The “standard dirs” (which may have been specified by the
       “-standarddirs” option)

``-oad``
    generates a makefile for a OpenAD build

``–adof /path/to/file``
    specifies the “adjoint” or automatic differentiation options file to
    be used. The file is analogous to the optfile defined above but it
    specifies information for the AD build process.

    The default file is located in
    ``tools/adjoint_options/adjoint_default`` and it defines the “TAF”
    and “TAMC” compilers. An alternate version is also available at
    ``tools/adjoint_options/adjoint_staf`` that selects the newer “STAF”
    compiler. As with any compilers, it is helpful to have their
    directories listed in your $PATH environment variable.

``–mpi``
    enables certain MPI features (using CPP ``#define``)
    within the code and is necessary for MPI builds (see :numref:`build_mpi`).

``–omp``
    enables OPENMP code and compiler flag OMPFLAG 

``–ieee``
    use IEEE numerics (requires support in optfile) 

``–make /path/to/gmake``
    due to the poor handling of soft-links and other bugs common with
    the ``make`` versions provided by commercial Unix vendors, GNU
    ``make`` (sometimes called ``gmake``) may be preferred. This
    option provides a means for specifying the make executable to be
    used.

.. _build_mpi:

Building  with MPI
------------------

Building MITgcm to use MPI libraries can be complicated due to the
variety of different MPI implementations available, their dependencies
or interactions with different compilers, and their often ad-hoc
locations within file systems. For these reasons, its generally a good
idea to start by finding and reading the documentation for your
machine(s) and, if necessary, seeking help from your local systems
administrator.

The steps for building MITgcm with MPI support are:

#. Determine the locations of your MPI-enabled compiler and/or MPI
   libraries and put them into an options file as described in :numref:`genmake2_optfiles`. 
   One can start with one of the examples in
   `tools/build_options <https://github.com/altMITgcm/MITgcm66/tree/master/tools/build_options>`_
   such as ``linux_amd64_gfortran`` or ``linux_amd64_ifort+impi`` and
   then edit it to suit the machine at hand. You may need help from your
   user guide or local systems administrator to determine the exact
   location of the MPI libraries. If libraries are not installed, MPI
   implementations and related tools are available including:

   -  `Open MPI <https://www.open-mpi.org/>`_ 

   -  `MVAPICH2 <http:mvapich.cse.ohio-state.edu/>`_

   -  `MPICH <https://www.mpich.org/>`_

   -  `Intel MPI <https://software.intel.com/en-us/intel-mpi-library/>`_

  
#. Build the code with the ``genmake2`` ``-mpi`` option (see :numref:`genmake_commandline`)
   using commands such as:

   ::

         %  ../../../tools/genmake2 -mods=../code -mpi -of=YOUR_OPTFILE
         %  make depend
         %  make


.. _run_the_model:

Running the model 
=================

If compilation finished successfully (:numref:`building_code`) then an
executable called ``mitgcmuv`` will now exist in the local (``build``) directory.

To run the model as a single process (i.e., not in parallel) simply
type (assuming you are still in the ``build`` directory):

::

    % cd ../run
    % ln -s ../input/* .
    % cp ../build/mitgcmuv .
    % ./mitgcmuv

Here, we are making a link to all the support data files needed by the MITgcm
for this experiment, and then copying the executable from the the build directory.
The ``./`` in the last step is a safe-guard to make sure you use the local executable in
case you have others that might exist in your $PATH.
The above command will spew out many lines of text output to your
screen. This output contains details such as parameter values as well as
diagnostics such as mean kinetic energy, largest CFL number, etc. It is
worth keeping this text output with the binary output so we normally
re-direct the ``stdout`` stream as follows:

::

    % ./mitgcmuv > output.txt

In the event that the model encounters an error and stops, it is very
helpful to include the last few line of this ``output.txt`` file along
with the (``stderr``) error message within any bug reports.

For the example experiments in ``verification``, an example of the
output is kept in ``results/output.txt`` for comparison. You can compare
your ``output.txt`` with the corresponding one for that experiment to
check that your set-up indeed works. Congratulations!


.. _running_mpi:

Running with MPI
----------------

Run the code with the appropriate MPI “run” or “exec” program
provided with your particular implementation of MPI. Typical MPI
packages such as `Open MPI <https://www.open-mpi.org/>`_ will use something like:

   ::

         %  mpirun -np 4 ./mitgcmuv

Sightly more complicated scripts may be needed for many machines
since execution of the code may be controlled by both the MPI library
and a job scheduling and queueing system such as SLURM, PBS, LoadLeveler,
or any of a number of similar tools. See your local cluster documentation 
or system administrator for the specific syntax required to run on your computing facility.


Output files
------------

The model produces various output files and, when using ``mnc`` (i.e., NetCDF),
sometimes even directories. Depending upon the I/O package(s) selected
at compile time (either ``mdsio`` or ``mnc`` or both as determined by
``code/packages.conf``) and the run-time flags set (in
``input/data.pkg``), the following output may appear. More complete information describing output files
and model diagnostics is described in chap_diagnosticsio.

MDSIO output files
~~~~~~~~~~~~~~~~~~

The “traditional” output files are generated by the ``mdsio`` package 
(link to section_mdsio).The ``mdsio`` model data are written according to a
“meta/data” file format. Each variable is associated with two files with
suffix names ``.data`` and ``.meta``. The ``.data`` file contains the
data written in binary form (big endian by default). The ``.meta`` file
is a “header” file that contains information about the size and the
structure of the ``.data`` file. This way of organizing the output is
particularly useful when running multi-processors calculations. 


At a minimum, the instantaneous “state” of the model is written out,
which is made of the following files:

-  ``U.00000nIter`` - zonal component of velocity field (m/s and
   positive eastward).

-  ``V.00000nIter`` - meridional component of velocity field (m/s and
   positive northward).

-  ``W.00000nIter`` - vertical component of velocity field (ocean: m/s
   and positive upward, atmosphere: Pa/s and positive towards increasing
   pressure i.e., downward).

-  ``T.00000nIter`` - potential temperature (ocean:
   :math:`^{\circ}\mathrm{C}`, atmosphere: :math:`^{\circ}\mathrm{K}`).

-  ``S.00000nIter`` - ocean: salinity (psu), atmosphere: water vapor
   (g/kg).

-  ``Eta.00000nIter`` - ocean: surface elevation (m), atmosphere:
   surface pressure anomaly (Pa).

The chain ``00000nIter`` consists of ten figures that specify the
iteration number at which the output is written out. For example,
``U.0000000300`` is the zonal velocity at iteration 300.

In addition, a “pickup” or “checkpoint” file called:

-  ``pickup.00000nIter``

is written out. This file represents the state of the model in a
condensed form and is used for restarting the integration (at the specific iteration number).
Some additional packages and parameterizations also produce separate pickup files, e.g.,

-  ``pickup_cd.00000nIter`` if the C-D scheme is used (see link to description)

-  ``pickup_seaice.00000nIter`` if the seaice package is turned on (see link to description)

-  ``pickup_ptracers.00000nIter`` if passive tracers are included in the simulation (see link to description)


Rolling checkpoint files are
the same as the pickup files but are named differently. Their name
contain the chain ``ckptA`` or ``ckptB`` instead of ``00000nIter``. They
can be used to restart the model but are overwritten every other time
they are output to save disk space during long integrations.

MNC output files
~~~~~~~~~~~~~~~~

The MNC package (link to section_mnc) is a set of routines written to read, write, and
append `NetCDF files <http://www.unidata.ucar.edu/software/netcdf/>`_. Unlike the ``mdsio`` output, the ``mnc``–generated output is usually
placed within a subdirectory with a name such as ``mnc_output_`` (by default, NetCDF tries to append, rather than overwrite, existing files,
so a unique output directory is helpful for each separate run).


The MNC output files are all in the “self-describing” NetCDF format and
can thus be browsed and/or plotted using tools such as:

-  `ncdump <https://www.unidata.ucar.edu/software/netcdf/netcdf-4/newdocs/netcdf/ncdump.html>`_ is a utility which is typically included with every NetCDF
   install, and converts the NetCDF binaries into formatted ASCII text files.

-  `ncview <http://meteora.ucsd.edu/~pierce/ncview_home_page.html>`_ is a very convenient and quick way to plot NetCDF
   data and it runs on most platforms. `Panoply <https://www.giss.nasa.gov/tools/panoply/>`_ is a similar alternative.

-  Matlab, GrADS, IDL and other common post-processing environments provide
   built-in NetCDF interfaces.


Looking at the output
---------------------

MATLAB
~~~~~~

MDSIO output
############

The repository includes a few Matlab utilities to read output
files written in the ``mdsio`` format. The Matlab scripts are located in the
directory ``utils/matlab`` under the root tree. The script ``rdmds.m``
reads the data. Look at the comments inside the script to see how to use
it.

Some examples of reading and visualizing some output in Matlab:

::

    % matlab
    >> H=rdmds('Depth');
    >> contourf(H');colorbar;
    >> title('Depth of fluid as used by model');

    >> eta=rdmds('Eta',10);
    >> imagesc(eta');axis ij;colorbar;
    >> title('Surface height at iter=10');

    >> eta=rdmds('Eta',[0:10:100]);
    >> for n=1:11; imagesc(eta(:,:,n)');axis ij;colorbar;pause(.5);end


NetCDF
######

Similar scripts for netCDF output (``rdmnc.m``) are available and they
are described in Section [sec:pkg:mnc].


Python
~~~~~~

MDSIO output
############

The repository includes Python scripts for reading the ``mdsio`` format under ``utils/python``. The following example shows how to load in some data:

::
  
    # python
    import mds

    Eta = mds.rdmds('Eta', itrs=10)

The docstring for ``mds.rdmds`` contains much more detail about using this function and the options that it takes.

NetCDF output
#############

The NetCDF output is currently produced with one file per processor. This means the individual tiles need to be stitched together to create a single NetCDF file that spans the model domain. The script ``gluemncbig.py`` in the ``utils/python`` folder can do this efficiently from the command line. 

The following example shows how to use the `xarray package <http://xarray.pydata.org/>`_ to read the resulting NetCDF file into python:

::
  
  # python
  import xarray as xr

  Eta = xr.open_dataset('Eta.nc')



