// TODO: Add licence
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $URL:$
// $Id: $
// 
//
// Author(s)     : Eric Berberich <eric@mpi-inf.mpg.de>
//                 Pavel Emeliyanenko <asm@mpi-sb.mpg.de>
//
// ============================================================================

#ifndef CGAL_CURVED_KERNEL_VIA_ANALYSIS_2_H
#define CGAL_CURVED_KERNEL_VIA_ANALYSIS_2_H

/*! \file Curved_kernel_via_analysis_2.h
 *  \brief defines class \c Curved_kernel_via_analysis_2
 *  
 * Defines points and arcs supported by curves that can be analyzed.
 */

#include <CGAL/basic.h>

#include <boost/mpl/if.hpp>
#include <boost/type_traits.hpp>

#include <CGAL/Arr_enums.h>
#include <CGAL/Arr_tags.h>
#include <CGAL/Curved_kernel_via_analysis_2/Point_2.h>
#include <CGAL/Curved_kernel_via_analysis_2/Arc_2.h>

#include <CGAL/Curved_kernel_via_analysis_2/Curve_interval_arcno_cache.h>
#include <CGAL/Curved_kernel_via_analysis_2/Curved_kernel_via_analysis_2_functors.h>

CGAL_BEGIN_NAMESPACE

namespace CGALi {

// todo mode to another file
/*!\brief
 * Provides basic types for Curved_kernel_via_analysis_2
 */
template < class CurvedKernelViaAnalysis_2, class CurveKernel_2 >
class Curved_kernel_via_analysis_2_base {
public:

    //!\name Global types
    //!@{
    
    //! this instance's template parameter
    typedef CurvedKernelViaAnalysis_2 Curved_kernel_via_analysis_2;

    //! type of curve kernel
    typedef CurveKernel_2 Curve_kernel_2;

    //! self
    typedef 
    Curved_kernel_via_analysis_2_base< 
        Curved_kernel_via_analysis_2, CurveKernel_2 
    > 
    Self;

    //!@}

public:

    //!\name Tags
    //!@{
    
    //! tag specifies that "to the left of" comparisons supported
    typedef CGAL::Tag_true Has_left_category;

    //! tag specifies that merge and split functors supported
    typedef CGAL::Tag_true Has_merge_category; 

    //! tag specifies that unbounded arcs supported
    typedef CGAL::Tag_true Has_boundary_category;

    //! tag specifies which boundary functors are implemented
    typedef CGAL::Arr_unbounded_boundary_tag Boundary_category;

    //!@}

public:
    //!\name Caching
    
    //!@{
    
    //! type of inverval arcno cache
    typedef CGALi::Curve_interval_arcno_cache< Self > 
    Curve_interval_arcno_cache;

    //!@}
    
protected:
    //!\name Internal types
    //!@{

    //! provides analysis of a single curve
    typedef typename Curve_kernel_2::Curve_analysis_2 Curve_analysis_2;
    
    //! provides analysis of a pair of curves
    typedef typename Curve_kernel_2::Curve_pair_analysis_2
            Curve_pair_analysis_2;
    
    //!@}
    
public:
    //! \name Constructors
    //!@{

    //! default constructor
    Curved_kernel_via_analysis_2_base() :
        _m_kernel(Curve_kernel_2()), _m_interval_arcno_cache(this) {
    }

    //! construct using specific Curve_kernel_2 instance \c kernel
    Curved_kernel_via_analysis_2_base(const Curve_kernel_2& kernel) :
        _m_kernel(kernel), _m_interval_arcno_cache(this) {
    }
    
    //!@}

    //!\name underlying curve kernel + caching
    //!@{
    
    /*!\brief
     * access to static Curve_interval_arcno_cache
     */
    const Curve_interval_arcno_cache& interval_arcno_cache() const {
        return this->_m_interval_arcno_cache;
    }
            
    /*!\brief
     * instance of internal Curve_kernel_2 instance
     *
     * \return 
     */
    const Curve_kernel_2& kernel() const {
        return _m_kernel;
    }

    //!@}

protected:
    //!\name private members
    //!@{
    
    //! an instance of \c Curve_kernel_2
    Curve_kernel_2 _m_kernel;
    
    //! an instance of \c Curve_interval_arcno_cache
    mutable Curve_interval_arcno_cache _m_interval_arcno_cache;
    
    //!@}

public:
    //!\name Static Member to provide CKvA instance
    //!@{

    /*!\brief
     * a default instance of \c Curved_kernel_via_analysis_2
     *
     * \return static instance of \c Curved_kernel_via_analysis_2
     */
    static Curved_kernel_via_analysis_2& instance() {
        return set_instance(_set_instance());
    }
    
    /*!\brief
     * sets static instance of \c Curved_kernel_via_analysis_2 to \c ckva
     *
     * \param ckva The instance that should be stored
     * \return the stored instance
     */
    static Curved_kernel_via_analysis_2& set_instance(
            const Curved_kernel_via_analysis_2& ckva
    ) {
        static Curved_kernel_via_analysis_2 instance;
        static Curved_kernel_via_analysis_2 binstance;
        
        if (&ckva == &_reset_instance()) {
            instance = binstance;
        } else if (&ckva != &_set_instance()) {
            binstance = instance;
            instance = ckva;
        }
        return instance;
        
    }
    
    /*!\brief
     * resets static instance to original one
     */ 
    static void reset_instance() {
        set_instance(_reset_instance());
    }
    
private:
    /*!\brief 
     * sets instance to default for internal purposes
     */
    static Curved_kernel_via_analysis_2& _set_instance() {
        static Curved_kernel_via_analysis_2 instance;
        return instance;
        
    }
    
    /*!\brief 
     * sets instance to default for internal purposes
     */
    static Curved_kernel_via_analysis_2& _reset_instance() {
        static Curved_kernel_via_analysis_2 instance;
        return instance;
    }
    
    //!@}
};    
    
} // namespace CGALi


/*!\brief 
 * Kernel for unbounded planar curves, and points and arcs of them
 * 
 * It expects a CurveKernel_2 type that fulfills the CurveKernel_2 concept.
 * The other template parameters can be left default. They are used during
 * rebind to exchange certain point and arc type.
 *
 * Is a model of CGAL's ArrangementTraits_2 concept.
 */
template < class CurveKernel_2, 
           class CKvA_ = void, class Point_ = void, class Arc_ = void >
class Curved_kernel_via_analysis_2 :
     public CGALi::Curved_kernel_via_analysis_2_base < 
            typename boost::mpl::if_< 
              boost::mpl::bool_< boost::is_void< CKvA_ >::value >, 
              Curved_kernel_via_analysis_2< CurveKernel_2 >,
              CKvA_
            >::type, 
            CurveKernel_2 
     >,
     public CGALi::Curved_kernel_via_analysis_2_functors < 
            typename boost::mpl::if_< 
              boost::mpl::bool_< boost::is_void< CKvA_ >::value >, 
              Curved_kernel_via_analysis_2< CurveKernel_2 >,
              CKvA_
            >::type, 
            typename CurveKernel_2::Curve_analysis_2,
            typename boost::mpl::if_< 
              boost::mpl::bool_< boost::is_void< Point_ >::value >, 
              CGALi::Point_2 < 
                typename boost::mpl::if_< 
                  boost::mpl::bool_< boost::is_void< CKvA_ >::value >, 
                  Curved_kernel_via_analysis_2< CurveKernel_2 >,
                  CKvA_
                >::type
              >,  
              Point_
            >::type,
            typename boost::mpl::if_< 
              boost::mpl::bool_< boost::is_void< Arc_ >::value >, 
              CGALi::Arc_2 < 
                typename boost::mpl::if_< 
                  boost::mpl::bool_< boost::is_void< CKvA_ >::value >, 
                  Curved_kernel_via_analysis_2< CurveKernel_2 >,
                  CKvA_
                >::type
              >,
              Arc_
            >::type
       > 
{
public:
    //!\name Public types
    //!@{
    
    //! this instance's template argument
    typedef CurveKernel_2 Curve_kernel_2;

    //!@}

protected:
    //!\name Protected types for internal use
    //!@{ 
    
    //! this instance's second template parameter
    typedef CKvA_ CKvA;
    
    //! this instance's third template parameter
    typedef Point_ Point;

    //! this instance's fourth template parameter
    typedef Arc_ Arc;

    //! myself
    typedef Curved_kernel_via_analysis_2< Curve_kernel_2, CKvA, Point, Arc > 
    Self;
    
    //! type of CKvA_2 used internally
    typedef typename boost::mpl::if_< 
              boost::mpl::bool_< boost::is_void< CKvA >::value >, 
              Curved_kernel_via_analysis_2< CurveKernel_2 >,
              CKvA
            >::type
    CKvA_2;

    //!@}

public:
    //!\name Rebind 
    //!@{

    //! allows to rebind CKvA_2 wrt to NewCKvA, NewPoint_2 and NewArc_2
    template < class NewCKvA_2, class NewPoint_2, class NewArc_2 >
    struct rebind {
        
        //! the rebound type
        typedef Curved_kernel_via_analysis_2< 
            Curve_kernel_2, NewCKvA_2, NewPoint_2, NewArc_2 
        >
        Other;

    };
    
    //!@}
    
public:
    //!\name Embedded types to fulfill \c ArrangementTraits_2 concept
    //!@{

    //! type of curve_2
    typedef typename Curve_kernel_2::Curve_analysis_2 Curve_2;
        
    //! type of a point on a curve that can be analyzed
    typedef typename boost::mpl::if_< 
              typename boost::mpl::bool_< boost::is_void< Point >::value >,
              CGALi::Point_2< CKvA_2 >,
              Point >::type
    Point_2;
    
    //! type of an arc on a curve that can be analyzed
    typedef typename boost::mpl::if_< 
              typename boost::mpl::bool_< boost::is_void< Arc >::value >,
              CGALi::Arc_2< CKvA_2 >,
              Arc >::type
    Arc_2;

    //! type of weakly x-monotone arc for \c ArrangementTraits_2
    typedef Arc_2 X_monotone_curve_2;

    //!@}

protected:
    //!\name Protected base types
    //!@{
    
    //! class collecting basic types
    typedef CGALi::Curved_kernel_via_analysis_2_base < CKvA_2, CurveKernel_2 >
    Base_kernel;

    //! class collecting basic functors
    typedef CGALi::Curved_kernel_via_analysis_2_functors < 
            CKvA_2, Curve_2, Point_2, Arc_2
    >  
    Base_functors;
    
    //!@}

public:
    //! \name Constructors
    //!@{

    /*!\brief
     * default constructor
     */
    Curved_kernel_via_analysis_2() :
        Base_kernel() {
    }
    
    /*!\brief
     * construct from \c kernel
     *
     * \param kernel Kernel to use internally
     */
    Curved_kernel_via_analysis_2(const Curve_kernel_2& kernel) :
        Base_kernel(kernel) {
    }
    
    //!@}

    //!\name Additinonal functors
    //!{

// declares curved kernel functors, for each functor defines a member function
// returning an instance of this functor
#define CGAL_CKvA_2_functor_pred(Y, Z) \
    typedef CGALi::Curved_kernel_via_analysis_2_Functors::Y< CKvA_2 > Y; \
    Y Z() const { return Y(&CKvA_2::instance()); }

#define CGAL_CKvA_2_functor_cons(Y, Z) CGAL_CKvA_2_functor_pred(Y, Z)
    
public:

    CGAL_CKvA_2_functor_cons(Construct_point_2, 
                             construct_point_2_object);

    CGAL_CKvA_2_functor_cons(Construct_point_on_arc_2, 
                             construct_point_on_arc_2_object);
    
    CGAL_CKvA_2_functor_cons(Construct_arc_2, 
                             construct_arc_2_object);

#undef CGAL_CKvA_2_functor_pred
#undef CGAL_CKvA_2_functor_cons
    
    //!@}

}; // class Curved_kernel_via_analysis_2

CGAL_END_NAMESPACE

#endif // CGAL_CURVED_KERNEL_VIA_ANALYSIS_2_H
// EOF
