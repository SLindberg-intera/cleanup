/*
 * This file was generated automatically by ExtUtils::ParseXS version 3.28 from the
 * contents of PolygonXS.xs. Do not edit this file, edit PolygonXS.xs instead.
 *
 *    ANY CHANGES MADE HERE WILL BE LOST!
 *
 */

#line 1 "PolygonXS.xs"
#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"

#include "ppport.h"

#include <functions.h>


#line 20 "PolygonXS.c"
#ifndef PERL_UNUSED_VAR
#  define PERL_UNUSED_VAR(var) if (0) var = var
#endif

#ifndef dVAR
#  define dVAR		dNOOP
#endif


/* This stuff is not part of the API! You have been warned. */
#ifndef PERL_VERSION_DECIMAL
#  define PERL_VERSION_DECIMAL(r,v,s) (r*1000000 + v*1000 + s)
#endif
#ifndef PERL_DECIMAL_VERSION
#  define PERL_DECIMAL_VERSION \
	  PERL_VERSION_DECIMAL(PERL_REVISION,PERL_VERSION,PERL_SUBVERSION)
#endif
#ifndef PERL_VERSION_GE
#  define PERL_VERSION_GE(r,v,s) \
	  (PERL_DECIMAL_VERSION >= PERL_VERSION_DECIMAL(r,v,s))
#endif
#ifndef PERL_VERSION_LE
#  define PERL_VERSION_LE(r,v,s) \
	  (PERL_DECIMAL_VERSION <= PERL_VERSION_DECIMAL(r,v,s))
#endif

/* XS_INTERNAL is the explicit static-linkage variant of the default
 * XS macro.
 *
 * XS_EXTERNAL is the same as XS_INTERNAL except it does not include
 * "STATIC", ie. it exports XSUB symbols. You probably don't want that
 * for anything but the BOOT XSUB.
 *
 * See XSUB.h in core!
 */


/* TODO: This might be compatible further back than 5.10.0. */
#if PERL_VERSION_GE(5, 10, 0) && PERL_VERSION_LE(5, 15, 1)
#  undef XS_EXTERNAL
#  undef XS_INTERNAL
#  if defined(__CYGWIN__) && defined(USE_DYNAMIC_LOADING)
#    define XS_EXTERNAL(name) __declspec(dllexport) XSPROTO(name)
#    define XS_INTERNAL(name) STATIC XSPROTO(name)
#  endif
#  if defined(__SYMBIAN32__)
#    define XS_EXTERNAL(name) EXPORT_C XSPROTO(name)
#    define XS_INTERNAL(name) EXPORT_C STATIC XSPROTO(name)
#  endif
#  ifndef XS_EXTERNAL
#    if defined(HASATTRIBUTE_UNUSED) && !defined(__cplusplus)
#      define XS_EXTERNAL(name) void name(pTHX_ CV* cv __attribute__unused__)
#      define XS_INTERNAL(name) STATIC void name(pTHX_ CV* cv __attribute__unused__)
#    else
#      ifdef __cplusplus
#        define XS_EXTERNAL(name) extern "C" XSPROTO(name)
#        define XS_INTERNAL(name) static XSPROTO(name)
#      else
#        define XS_EXTERNAL(name) XSPROTO(name)
#        define XS_INTERNAL(name) STATIC XSPROTO(name)
#      endif
#    endif
#  endif
#endif

/* perl >= 5.10.0 && perl <= 5.15.1 */


/* The XS_EXTERNAL macro is used for functions that must not be static
 * like the boot XSUB of a module. If perl didn't have an XS_EXTERNAL
 * macro defined, the best we can do is assume XS is the same.
 * Dito for XS_INTERNAL.
 */
#ifndef XS_EXTERNAL
#  define XS_EXTERNAL(name) XS(name)
#endif
#ifndef XS_INTERNAL
#  define XS_INTERNAL(name) XS(name)
#endif

/* Now, finally, after all this mess, we want an ExtUtils::ParseXS
 * internal macro that we're free to redefine for varying linkage due
 * to the EXPORT_XSUB_SYMBOLS XS keyword. This is internal, use
 * XS_EXTERNAL(name) or XS_INTERNAL(name) in your code if you need to!
 */

#undef XS_EUPXS
#if defined(PERL_EUPXS_ALWAYS_EXPORT)
#  define XS_EUPXS(name) XS_EXTERNAL(name)
#else
   /* default to internal */
#  define XS_EUPXS(name) XS_INTERNAL(name)
#endif

#ifndef PERL_ARGS_ASSERT_CROAK_XS_USAGE
#define PERL_ARGS_ASSERT_CROAK_XS_USAGE assert(cv); assert(params)

/* prototype to pass -Wmissing-prototypes */
STATIC void
S_croak_xs_usage(const CV *const cv, const char *const params);

STATIC void
S_croak_xs_usage(const CV *const cv, const char *const params)
{
    const GV *const gv = CvGV(cv);

    PERL_ARGS_ASSERT_CROAK_XS_USAGE;

    if (gv) {
        const char *const gvname = GvNAME(gv);
        const HV *const stash = GvSTASH(gv);
        const char *const hvname = stash ? HvNAME(stash) : NULL;

        if (hvname)
	    Perl_croak_nocontext("Usage: %s::%s(%s)", hvname, gvname, params);
        else
	    Perl_croak_nocontext("Usage: %s(%s)", gvname, params);
    } else {
        /* Pants. I don't think that it should be possible to get here. */
	Perl_croak_nocontext("Usage: CODE(0x%"UVxf")(%s)", PTR2UV(cv), params);
    }
}
#undef  PERL_ARGS_ASSERT_CROAK_XS_USAGE

#define croak_xs_usage        S_croak_xs_usage

#endif

/* NOTE: the prototype of newXSproto() is different in versions of perls,
 * so we define a portable version of newXSproto()
 */
#ifdef newXS_flags
#define newXSproto_portable(name, c_impl, file, proto) newXS_flags(name, c_impl, file, proto, 0)
#else
#define newXSproto_portable(name, c_impl, file, proto) (PL_Sv=(SV*)newXS(name, c_impl, file), sv_setpv(PL_Sv, proto), (CV*)PL_Sv)
#endif /* !defined(newXS_flags) */

#if PERL_VERSION_LE(5, 21, 5)
#  define newXS_deffile(a,b) Perl_newXS(aTHX_ a,b,file)
#else
#  define newXS_deffile(a,b) Perl_newXS_deffile(aTHX_ a,b)
#endif

#line 164 "PolygonXS.c"

XS_EUPXS(XS_Math__Geometry__Planar__GPC__PolygonXS_new); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_Math__Geometry__Planar__GPC__PolygonXS_new)
{
    dVAR; dXSARGS;
    if (items != 1)
       croak_xs_usage(cv,  "class");
    {
	char*	class = (char *)SvPV_nolen(ST(0))
;
	SV *	RETVAL;

	RETVAL = new(class);
	RETVAL = sv_2mortal(RETVAL);
	ST(0) = RETVAL;
    }
    XSRETURN(1);
}


XS_EUPXS(XS_Math__Geometry__Planar__GPC__PolygonXS_add_polygon); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_Math__Geometry__Planar__GPC__PolygonXS_add_polygon)
{
    dVAR; dXSARGS;
    if (items != 3)
       croak_xs_usage(cv,  "obj, pg, hole");
    {
	SV*	obj = ST(0)
;
	SV*	pg = ST(1)
;
	int	hole = (int)SvIV(ST(2))
;

	add_polygon(obj, pg, hole);
    }
    XSRETURN_EMPTY;
}


XS_EUPXS(XS_Math__Geometry__Planar__GPC__PolygonXS_DESTROY); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_Math__Geometry__Planar__GPC__PolygonXS_DESTROY)
{
    dVAR; dXSARGS;
    if (items != 1)
       croak_xs_usage(cv,  "obj");
    {
	SV*	obj = ST(0)
;

	DESTROY(obj);
    }
    XSRETURN_EMPTY;
}


XS_EUPXS(XS_Math__Geometry__Planar__GPC__PolygonXS_from_file); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_Math__Geometry__Planar__GPC__PolygonXS_from_file)
{
    dVAR; dXSARGS;
    if (items != 3)
       croak_xs_usage(cv,  "obj, filename, want_hole");
    {
	SV*	obj = ST(0)
;
	char*	filename = (char *)SvPV_nolen(ST(1))
;
	int	want_hole = (int)SvIV(ST(2))
;
	int	RETVAL;
	dXSTARG;

	RETVAL = from_file(obj, filename, want_hole);
	XSprePUSH; PUSHi((IV)RETVAL);
    }
    XSRETURN(1);
}


XS_EUPXS(XS_Math__Geometry__Planar__GPC__PolygonXS_to_file); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_Math__Geometry__Planar__GPC__PolygonXS_to_file)
{
    dVAR; dXSARGS;
    if (items != 3)
       croak_xs_usage(cv,  "obj, filename, want_hole");
    {
	SV*	obj = ST(0)
;
	char*	filename = (char *)SvPV_nolen(ST(1))
;
	int	want_hole = (int)SvIV(ST(2))
;

	to_file(obj, filename, want_hole);
    }
    XSRETURN_EMPTY;
}


XS_EUPXS(XS_Math__Geometry__Planar__GPC__PolygonXS_clip_to); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_Math__Geometry__Planar__GPC__PolygonXS_clip_to)
{
    dVAR; dXSARGS;
    if (items != 3)
       croak_xs_usage(cv,  "obj, clp, action");
    {
	SV*	obj = ST(0)
;
	SV*	clp = ST(1)
;
	char*	action = (char *)SvPV_nolen(ST(2))
;
	SV *	RETVAL;

	RETVAL = clip_to(obj, clp, action);
	RETVAL = sv_2mortal(RETVAL);
	ST(0) = RETVAL;
    }
    XSRETURN(1);
}


XS_EUPXS(XS_Math__Geometry__Planar__GPC__PolygonXS_get_polygons); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_Math__Geometry__Planar__GPC__PolygonXS_get_polygons)
{
    dVAR; dXSARGS;
    if (items != 1)
       croak_xs_usage(cv,  "obj");
    PERL_UNUSED_VAR(ax); /* -Wall */
    SP -= items;
    {
	SV*	obj = ST(0)
;
#line 44 "PolygonXS.xs"
    int c;
    gpc_polygon* p;

#line 302 "PolygonXS.c"
#line 48 "PolygonXS.xs"
	p = (gpc_polygon*) SvIV(SvRV(obj));
	PUSHMARK(SP);
	if(p->num_contours < 1) {
		PUTBACK;
		return;
	}
	for(c = 0; c < p->num_contours; c++) {
		XPUSHs(newRV_noinc((SV*) vertex_list_to_pts(&(p->contour[c]))));
	}
#line 313 "PolygonXS.c"
	PUTBACK;
	return;
    }
}

#ifdef __cplusplus
extern "C"
#endif
XS_EXTERNAL(boot_Math__Geometry__Planar__GPC__PolygonXS); /* prototype to pass -Wmissing-prototypes */
XS_EXTERNAL(boot_Math__Geometry__Planar__GPC__PolygonXS)
{
#if PERL_VERSION_LE(5, 21, 5)
    dVAR; dXSARGS;
#else
    dVAR; dXSBOOTARGSXSAPIVERCHK;
#endif
#if (PERL_REVISION == 5 && PERL_VERSION < 9)
    char* file = __FILE__;
#else
    const char* file = __FILE__;
#endif

    PERL_UNUSED_VAR(file);

    PERL_UNUSED_VAR(cv); /* -W */
    PERL_UNUSED_VAR(items); /* -W */
#if PERL_VERSION_LE(5, 21, 5)
    XS_VERSION_BOOTCHECK;
#  ifdef XS_APIVERSION_BOOTCHECK
    XS_APIVERSION_BOOTCHECK;
#  endif
#endif

        newXS_deffile("Math::Geometry::Planar::GPC::PolygonXS::new", XS_Math__Geometry__Planar__GPC__PolygonXS_new);
        newXS_deffile("Math::Geometry::Planar::GPC::PolygonXS::add_polygon", XS_Math__Geometry__Planar__GPC__PolygonXS_add_polygon);
        newXS_deffile("Math::Geometry::Planar::GPC::PolygonXS::DESTROY", XS_Math__Geometry__Planar__GPC__PolygonXS_DESTROY);
        newXS_deffile("Math::Geometry::Planar::GPC::PolygonXS::from_file", XS_Math__Geometry__Planar__GPC__PolygonXS_from_file);
        newXS_deffile("Math::Geometry::Planar::GPC::PolygonXS::to_file", XS_Math__Geometry__Planar__GPC__PolygonXS_to_file);
        newXS_deffile("Math::Geometry::Planar::GPC::PolygonXS::clip_to", XS_Math__Geometry__Planar__GPC__PolygonXS_clip_to);
        newXS_deffile("Math::Geometry::Planar::GPC::PolygonXS::get_polygons", XS_Math__Geometry__Planar__GPC__PolygonXS_get_polygons);
#if PERL_VERSION_LE(5, 21, 5)
#  if PERL_VERSION_GE(5, 9, 0)
    if (PL_unitcheckav)
        call_list(PL_scopestack_ix, PL_unitcheckav);
#  endif
    XSRETURN_YES;
#else
    Perl_xs_boot_epilog(aTHX_ ax);
#endif
}

