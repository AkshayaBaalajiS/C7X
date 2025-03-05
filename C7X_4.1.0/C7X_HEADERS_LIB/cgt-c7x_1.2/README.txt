                  C7000 C/C++ CODE GENERATION TOOLS
                    1.2.0.STS Pre-Release Notes

===============================================================================
Contents
===============================================================================
0) Introduction to Pre-Release
1) Documentation
2) Defect Reporting
3) Supported and Unsupported Features
4) Support for Vector Data Types
   4.1) Basic Usage
   4.2) Vector Data Types and Operations

-------------------------------------------------------------------------------
0) Introduction to STS Pre-Release
-------------------------------------------------------------------------------

This release is an STS (Short-Term Support) pre-release.  As such, it is not
feature complete with respect to the boundary agreement of the C7x CGT v1.x
project.  Aspects of the support, including names of visible C7x intrinsics,
may change over the course of the releases as feature support improves.

* Definitions
  -----------
- *Active* releases have bug fixes applied pro-actively and patch releases
  occur on a semi-regular schedule (2-3 months)
- *Reactive* releases only have a subset of bug fixes applied and patch
  releases occur only when requested or are deemed necessary.
- *Patch* releases only contain bug fixes (no new features)

* Short term support (STS) release:
  All STS branches will be made reactive upon creation. A patch release for
  this branch will only be created for production stop issues and will only
  contain fixes for the production stop issues.  For all other issues, users
  are advised to wait for the next STS branch, which may also contain new
  features.  An STS release will occur approx. every 3 months after the first
  LTS release.

* Long term support (LTS) release:
  The LTS branch will be active upon creation. The branch will be active for at
  least 2 years.  Production stop bugs will be fixed within 15 days of being
  reported.  Planned patch releases expected every 2-3 months to correct any
  critical bugs within 60 days of being reported. The LTS release is intended
  for customers to lock down on tools.  We will have no more than one LTS per
  year.

  The complier policy is to only maintain two active branches at any given
  time.  When the LTS branch is made, the 2nd to last LTS releases will be made
  reactive.

-------------------------------------------------------------------------------
1) Documentation
-------------------------------------------------------------------------------

The following documents are included to provide information for the C7x:

SPRUIG8A***.PDF : C7000 C/C++Optimizing Compiler Users Guide
SPRUIG4C***.PDF: C7000 Embedded Application Binary Interface (EABI) Reference Guide
SPRUIG5C***.PDF: C6000-to-C7000 Migration User's Guide
SPRUIG3C***.PDF: VCOP Kernel-C to C7000 Migration Tool User's Guide
SPRUIG6C***.PDF: C7000 Host Emulation User's Guide

-------------------------------------------------------------------------------
2) Defect Reporting
-------------------------------------------------------------------------------

1.) File issues in the "Code Generation Tools (CODEGEN)" project (do not
    file issues in the old COMPILE project)

2.) Please set issue type to 'bug' for defects and 'story' for anything else
    (e.g. performance issues, etc).  Please don't use any other issue types.

3.) Adjust the severity of the issue accordingly:
    a. "critical": A production stop issue that must be fixed ASAP.  Be clear
       as to the nature of the issue. These issues will be fixed within a few
       days or weeks.

    b. "major": An issue that should be addressed by the next major STS, LTS,
       or alpha release.

    c. "minor": An issue that should be addressed at some point in v1.x release
       (or even beyond, depending on schedule constraints).

4.) For ADAS reported issues, set the label to "ADAS_BU_REPORTED_ISSUE".  We
    can use this label to keep track of all reported issues.

5.) Set another label: "COMP_C7000". This label is used by CODEGEN to
    distinguish between all compiler teams.

6.) Attach a scaled-down test case with command-line options to allow us to
    reproduce the issue easily.

-------------------------------------------------------------------------------
3) Supported and Unsupported Features
-------------------------------------------------------------------------------

New Features
------------

* C++14 Support

* Host Emulation Additions
  - The following updates have NOT yet been added to the C7000 Host Emulation
    Users Guide (SPRUIG6C***.PDF)

  - Nested subvector accesses (via .lo, .hi, .even, .odd) is limited to depth
    of 2.  This means that you cannot nest subvector accesses more than 2-deep:
    "vect.lo.lo".  This was necessary to limit the amount of memory space
    required to support a vector type in C++.  As a workaround, if you need to
    access a subvector deeper than 2, you should use a temporary vector:
    "uchar8 tmp = vect.lo.lo; dst = tmp.lo"
    - Complex vectors require a bit more memory because they have more
      accessors at each nested depth. "cchar32.lo.r, cchar32.r.lo.lo", etc

    Please see the following table to guage how much memory (in bytes) is
    consumed by each vector type.

	sizeof(char64)  == 8528		sizeof(cchar32)  == 31576
	sizeof(char32)  == 4912 	sizeof(cchar16)  == 19608
	sizeof(char16)  == 3040 	sizeof(cchar8)   == 15560
	sizeof(char8)   == 2344 	sizeof(cchar4)   == 2792
	sizeof(char4)   == 544 		sizeof(cchar2)   == 456
	sizeof(char2)   == 112

	sizeof(short32) == 4944 	sizeof(cshort16) == 19608
	sizeof(short16) == 3056 	sizeof(cshort8)  == 15560
	sizeof(short8)  == 2352 	sizeof(cshort4)  == 2792
	sizeof(short4)  == 552 		sizeof(cshort2)  == 456
	sizeof(short2)  == 112

	sizeof(int16)   == 3088 	sizeof(cint8)    == 15624
	sizeof(int8)    == 2368 	sizeof(cint4)    == 2824
	sizeof(int4)    == 560 		sizeof(cint2)    == 472
	sizeof(int2)    == 120

	sizeof(float16) == 3088 	sizeof(cfloat8)  == 15624
	sizeof(float8)  == 2368 	sizeof(cfloat4)  == 2824
	sizeof(float4)  == 560 		sizeof(cfloat2)  == 472
	sizeof(float2)  == 120

	sizeof(long8)   == 2400 	sizeof(clong4)   == 2856
	sizeof(long4)   == 576 		sizeof(clong2)   == 488
	sizeof(long2)   == 128

	sizeof(double8) == 2400 	sizeof(cdouble4) == 2856
	sizeof(double4) == 576 		sizeof(cdouble2) == 488
	sizeof(double2) == 128

* All C7x loads now have 6-cycle latency in the compiler; this is particularly
  important in unprotected mode (pipelined loops) where UNPROT is issued with
  argument "1".

* Syntax change on Streaming Address Access
  - From now on, a direct access of the SA simply returns a pointer.
    "uint16 *ptr = __SA0(uint16, base);" In order to load from the pointer, it
    is now necessary to dereference the SA pointer just as you would for any
    other pointer type: "uint16 vector = *__SA0(uint16, base);"

  - It is no longer necessary to use the address-of operator (&) to extract a
    pointer to SA data.

* Added preliminary automatic vector-predication support into optimization to
  eliminate loop peeling

* Early support for user-level boolean vector types
  - Note: This support is NOT complete and is not presently optimizable.
    Continue to use "__vpred" type; intrinsics are documented in c7x_vpred.h

* Ensure that speculated scalar loads use the correct mnemonic (e.g. SLDB,
  SLDH, SLDW, SLDD)

* Fix copy-table support

* Renamed __convert_booln() intrinsics to __reduce_booln() and
  __expand_booln().  See c7x.h for details.

* Added constant-range checking on all intrinsics that rely on constants
  - This means that constants supported as arguments on intrinsics must fall
    within the expected constant range, otherwise a compiler error will be
    generated.

Supported Intrinsics
--------------------

The included top-level header files c7x.h and c6x_migration.h list the
supported intrinsics for both C7x and C6x, respectively. Note that you must
include these header files with your source in order to leverage many of the
C7x intrinsics and all of the legacy C6x intrinsics. c7x.h includes other
useful header files that document/describe supported intrinsics:

- c7x_vpred.h: List of intrinsics supporting low-level "__vpred" vector
  predicate type.
- c7x_direct.h: List of intrinsics that map directly to instructions.
- c7x_strm.h: List of intrinsics and flags for C7x Streaming Engine and Stream
  Address Generator.
- c7x_mma.h: List of intrinsics and associated structures and enumerations for
  the C7x MMA.
- c7x_luthist.h: List of intrinsics and flags for C7x Lookup Table / Histogram
  support.

Unsupported Features
--------------------

* Other performance and codesize optimizations
* Automatic leveraging of Streaming Engine and Stream Address Generator
* OpenCL-C & LLVM

-------------------------------------------------------------------------------
4) Support for Vector Data Types
-------------------------------------------------------------------------------

The C7000 v1.0.0 STS C/C++ compiler supports the use of OpenCL-like vector
data types in C/C++ source files by default.

-------------------------------------------------------------------------------
4.1) Basic Usage
-------------------------------------------------------------------------------

  Support for vector data types is available on the C7100 architecure.

  Support for vector data types is enabled by default.  When the
  "--vectypes=off" option is specified on the compiler command line, vector
  types will be interpreted as identifiers rather than types.

  Support for vector data types requires the use of the optimizer. That is,
  the "--vectypes" option must be specified in combination with "-o0", "-o1",
  "-o2", or "-o3" on the compiler command line.

  All of the vector data types and related built-in functions that are
  supported in the C7x programming model are specified in the "c7x.h"
  header file that you can find in the "include" sub-directory where your
  C7000 CGT was installed.

  Any C/C++ source file that utilizes vector data types or any of the built-in
  functions must "#include <c7x.h>" in that source file.


-------------------------------------------------------------------------------
4.2) Vector Data Types and Operations
-------------------------------------------------------------------------------

  Vector Data Types
  -----------------

  A vector type name is a concatenation of element type name with a number
  representing vector length. A vector with such type consists of vector length
  number of vector elements.

  The C7x programming model implementation of vector data types and operations
  follows the OpenCL C language specification very closely. For a more detailed
  description of OpenCL vector data types and operations, please see "The
  OpenCL Specification" version 1.2 which is available from the Khronos OpenCL
  Working Group:

    http://www.khronos.org/opencl/

  Chapter 6, section 6.1.2 of "The OpenCL Specification" version 1.2 provides
  a detailed description of the built-in vector data types supported in the
  OpenCL C programming language.

  The C7x programming model provides the following built-in vector data
  types:

  o Element type names and sizes

    char	char, 8 bits
    uchar	unsigned char, 8 bits
    short	short, 16 bits
    ushort	unsigned short, 16 bits
    int		int, 32 bits
    uint	unsigned int, 32 bits
    longlong	long long, 64 bits
    ulonglong	unsigned long long, 64 bits
    float	IEEE single precision floating-point, 32 bits
    double	IEEE double precision floating-point, 64 bits

  o Valid vector lengths: 2, 3, 4, 8, 16

    For example, a "uchar8" is a vector of 8 unsigned chars. Its length is 8
    and its size is 64 bits.

  The C7x programming model also provides an extension to the OpenCL C
  programming language for representing vectors of complex type. A prefix of
  'c' is used to indicate a complex type name. Each complex type vector element
  contains a real part and an imaginary part with the real part occupying the
  lower address in memory.

  o Complex element type names and sizes:

    cchar	complex char type, 16 bits
    cshort	complex short type, 32 bits
    cint	complex int type, 64 bits
    clonglong	complex long long type, 128 bits
    cfloat	complex float type, 64 bits
    cdouble	complex double type, 128 bits

  o Valid lengths for complex type vectors: 1, 2, 4, 8

    For example, a "cfloat2" is a vector of 2 complex floats. Its length is 2
    and its size is 128 bits. Each "cfloat2" vector element contains a real
    float and an imaginary float.


  Vector Operations: component access
  -----------------------------------

  A component access can occur on the left-hand-side (lhs) or right-hand-side
  (rhs) of an assignment operator. If specified on the lhs of an assignment,
  each component must be uniquely identifiable.

  The C7x programming model implementation supports OpenCL C like swizzle
  operators:

  o A suffix of ".x", ".y", ".z", or ".w" can be used to access an element
    of a vector whose length is <= 4.

      char4 my_c4 = (char4)(1, 2, 3, 4);
      char    tmp = my_c4.y * my_c4.w;  /* ".y" accesses 2nd element
                                        *  ".w" accesses 4th element
					*  tmp = 2 * 4 = 8;
					*/

  o A suffix of ".s0", ".s1", ..., ".s9", ".sa", ..., ".sf" can be used
    to access one of up to 16 elements in a vector.

      uchar16 ucvec16 = (uchar16)(1, 2, 3, 4, 5, 6, 7,
                                  8, 9, 10, 11, 12, 13, 14, 15, 16 );
      uchar8  ucvec8  = (uchar8)(2, 4, 6, 8, 10, 12, 14, 16);

      int tmp = ucvec16.sa * ucvec8.s7; /* ".sa" is 11th element of ucvec16
                                        *  ".s7" is 8th element of ucvec8
					*  tmp = 10 * 16 = 160;
					*/

  o A suffix of ".even" or ".odd" can be used to access the even or odd
    elements of a vector.

      ushort4 usvec4 = (ushort4)(1, 2, 3, 4);
      ushort2 usvecodd  = usvec4.odd;  /* usvecodd  = (ushort2)(2, 4); */
      ushort2 usveceven = usvec4.even; /* usveceven = (ushort2)(1, 3); */

  o A suffix of ".hi" or ".lo" can be used to access the elements in the
    upper half of a vector (for ".hi") or the elements in the lower half
    of a vector (for ".lo").

      ushort8 usvec8 = (ushort8)(1, 2, 3, 4, 5, 6, 7, 8);
      ushort4 usvechi = usvec8.hi; /* usvechi = (ushort4)(5, 6, 7, 8); */
      ushort4 usveclo = usvec8.lo; /* usveclo = (ushort4)(1, 2, 3, 4); */

  The C7x programming model also supports an extension to the OpenCL C
  programming language for accessing elements of a complex type vector:

  o A suffix of ".r" can be used to access the real parts of each of
    the elements in a complex type vector.

      cfloat2 cfa = (cfloat2)(1.0, -2.0, 3.0, -4.0);
      float2  rfa = cfa.r; /* ".r" accesses real parts of cfa elements
                           *  rfa = (float2)(1.0, 3.0);
			   */

  o A suffix of ".i" can be used to access the imaginary parts of each of
    the elements in a complex type vector.

      cfloat2 cfa = (cfloat2)(1.0, -2.0, 3.0, -4.0);
      float2  ifa = cfa.i; /* ".i" accesses imaginary parts of cfa elements
                           *  ifa = (float2)(-2.0, -4.0);
			   */

  Swizzle operators can also be combined if the result of the combination
  is well-defined:

      ushort4 usvec4 = (ushort4)(1, 2, 3, 4);
      ...
      usvec4.hi.even = 5;  /* After this assignment,
                           *  usvec4 contains (1, 2, 5, 4)
			   */


  Vector Operations: concatenation
  --------------------------------

  Scalar entities or shorter vectors can be concatenated together to form
  longer vectors. When all of the components involved are constants, the
  result is a vector literal. Otherwise, the vector's value is determined at
  run-time.

  o Vector literals

    (short4)(1, 2, 3, 4);
    (float2)(3.2, -2.3);

  o Vector concatenation

    void foo(int a, int b)
    {
       int2 myvec = (int2)(a, b);
       ...
    }


  Vector Operations: conversion and re-interpretation
  ---------------------------------------------------

  The C7x programming model includes functions that can convert or re-interpret
  the elements of one vector type as another vector type.

  o convert_<destination type>(<source type object>) can be used to perform
    an element by element conversion of one vector type object into another
    vector type object. The source vector type and the destination vector
    type must be the same length.

      void foo(int a, int b)
      {
	 /* initialize a short2 vector from a converted int2 vector */
         short2 svec2 = convert_short2((int2)(a, b));
	 ...
      }

  o as_<destination type>(<source type object>) can be used to
    re-interpret the original vector type of an object as another
    vector type. The source type and destination type must be the
    same size.

    extern longlong lla;
    float2   fltvec2 = as_float2(lla);

  Neither the convert_<destination type>(<source type object>) nor the
  as_<destination type>(<source type object>) is available for use with
  complex types.


  Vector Operations: infix operators
  ----------------------------------

  When infix operators are applied to vector type objects, the operator
  is applied element by element. That is, each element in the result vector
  is the result of applying the infix operator to the corresponding elements
  in the source vector(s).

  o Unary:

    Negate: -
    Bitwise complement: ~
    Logical not (integer vectors only): !

      int4 pos_i4 = (int4)(1, 2, 3, 4);
      int4 neg_i4 = -pos_i4; /* Use of negate operator initializes
                             *  neg_i4 to (-1, -2, -3, -4)
			     */

  o Binary

    Assignment operators: =, op= (+=, for example)
    Arithmetic operators: +, - , *, /
    Modulo operator (integer vectors only): %
    Bitwise operators:, &, |, ^, <<, >>
    Relational operators: >, >=, ==, !=, <=, <
    Increment / decrement (integer vectors only): ++(), ()++, --(), ()--
    Logical operators (integer vectors only): &&, ||

      /* Assume iv4 argument contains (1, 2, 3, 4) coming in */
      void foo(int4 iv4)
      {
         int4 local_iva = iv4++; /* local_iva = (1, 2, 3, 4) */
         int4 local_ivb = iv4++; /* local_ivb = (2, 3, 4, 5) */

	 /* local_ivc = (1, 2, 3, 4) + (2, 3, 4, 5) = (3, 5, 7, 9) */
         int4 local_ivc = local_iva + local_ivb;
      }
      /* iv4 contains (3, 4, 5, 6) on exit from foo() */

  o Operators available with complex vector types

    Arithmetic operators: +, - , *, /
    Increment / decrement (by 1+0i): ++(), ()++, --(), ()--

      /* On C7100, the compiler will generate a special instruction to       */
      /* carry out the complex multiply operation and call a built-in (RTS)  */
      /* function to carry out the divide operation.                         */
      void foo()
      {
         cfloat2 va = (cfloat2) (1.0, -2.0, 3.0, -4.0);
         cfloat2 va = (cfloat2) (4.0, -2.0, -4.0, 2.0);

         /* For details about the rules for complex multiplication and */
	 /* division, please see Annex G of the C99 C language         */
	 /* specification.                                             */

	 /* vc = < (0.0, -10.0), (-4.0, 22.0)> */
         cfloat2 vc = va * vb;

	 /* vd = < (0.4, -0.3), (-1.0, 0.5)> */
         cfloat2 vd = va / vb;
	 ...
      }


  Vector Operations: built-in functions
  -------------------------------------

  Prototypes for all of the vector built-in functions supported in the
  C7x programming model are listed in the "c7x.h" header file that
  you can find in the "include" sub-directory where your C7000 CGT
  package was installed. Please refer to the contents of "c7x.h"
  for a complete list of the vector built-in functions.

  Here is an example which uses vector built-in functions:

  [vbif_ex.c]

    #include <stdio.h>
    #include <c7x.h>

    void print_short4(char *s, short4 v)
    {
       printf("%s", s);
       printf(" <%d, %d, %d, %d>\n", v.x, v.y, v.z, v.w);
    }

    int main()
    {
       short4 va = (short4) (1, 2, 3, -32766);
       short4 vb = (short4) (5, 32767, -13, 17);
       short4 vc = va + vb;
       short4 vd = va - vb;
       short4 ve = __add_sat(va, vb);
       short4 vf = __sub_sat(va, vb);
       print_short4("va=", va);
       print_short4("vb=", vb);
       print_short4("vc=(va+vb)=", vc);
       print_short4("vd=(va-vb)=", vd);
       print_short4("ve=__add_sat(va,vb)=", ve);
       print_short4("vf=__sub_sat(va,vb)=", vf);
       return 0;
    }

  Compile:

    %> cl7x -mv7100 -o1 -k vbif_ex.c -z -o vbif_ex.out -llnk.cmd

    Note:
       - lnk.cmd contains a reference to rts7100.lib
       - rts7100.lib contains c7x_veclib.obj which defines the built-in
	 functions, __add_sat() and __sub_sat()

  Run:

    Load and run vbif_ex.out from the C7000 simulator to get the following
    result:

    va= <1, 2, 3, -32766>
    vb= <5, 32767, -13, 17>
    vc=(va+vb)= <6, -32767, -10, -32749>
    vd=(va-vb)= <-4, -32765, 16, 32753>
    ve=__add_sat(va,vb)= <6, 32767, -10, -32749>
    vf=__sub_sat(va,vb)= <-4, -32765, 16, -32768>


-- End Of File --
