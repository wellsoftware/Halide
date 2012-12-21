#ifndef BOUNDS_H
#define BOUNDS_H

#include "IRVisitor.h"
#include "Scope.h"
#include <utility>
#include <vector>

namespace Halide {
namespace Internal {
    
using std::pair;
using std::vector;    
    
/* Given an expression in some variables, and a map from those
 * variables to their bounds (in the form of (minimum possible value,
 * maximum possible value)), compute two expressions that give the
 * minimum possible value and the maximum possible value of this
 * expression. Max or min may be undefined expressions if the value is
 * not bounded above or below.
 *
 * This is for tasks such as deducing the region of a buffer
 * loaded by a chunk of code.
 */
pair<Expr, Expr> bounds_of_expr_in_scope(Expr expr, const Scope<pair<Expr, Expr> > &scope);    

/* Compute a rectangular domain large enough to cover all the 'Call's
 * to each function that occur within a given statement. This is useful
 * for figuring out what regions of things to evaluate. */
map<string, vector<pair<Expr, Expr> > > regions_required(Stmt s, const Scope<pair<Expr, Expr> > &scope);

/* Compute a rectangular domain large enough to cover all the
 * 'Provide's to a function the occur within a given statement. This
 * is useful for figuring out what region of a function a scattering
 * reduction (e.g. a histogram) might touch. */
map<string, vector<pair<Expr, Expr> > > regions_provided(Stmt s, const Scope<pair<Expr, Expr> > &scope);

/* Compute the union of the above two */
map<string, vector<pair<Expr, Expr> > > regions_touched(Stmt s, const Scope<pair<Expr, Expr> > &scope);

/* Compute the smallest bounding box that contains two regions */
vector<pair<Expr, Expr> > region_union(const vector<pair<Expr, Expr> > &, const vector<pair<Expr, Expr> > &);

void bounds_test();
        
}
}

#endif
