// TODO: Eigen opperators like *= /* coeff not working
// __bug

#include <npe.h>
#include <typedefs.h>






#include <igl/biharmonic_coordinates.h>

const char* ds_biharmonic_coordinates = R"igl_Qu8mg5v7(

Compute "discrete biharmonic generalized barycentric coordinates" as
  described in "Linear Subspace Design for Real-Time Shape Deformation"
  [Wang et al. 2015]. Not to be confused with "Bounded Biharmonic Weights
  for Real-Time Deformation" [Jacobson et al. 2011] or "Biharmonic
  Coordinates" (2D complex barycentric coordinates) [Weber et al. 2012].
  These weights minimize a discrete version of the squared Laplacian energy
  subject to positional interpolation constraints at selected vertices
  (point handles) and transformation interpolation constraints at regions
  (region handles).

Parameters
----------
Templates: HType  should be a simple index type e.g. `int`,`size_t`

V  #V by dim list of mesh vertex positions
T  #T by dim+1 list of / triangle indices into V      if dim=2
                       \ tetrahedron indices into V   if dim=3
S  #point-handles+#region-handles list of lists of selected vertices for
  each handle. Point handles should have singleton lists and region
  handles should have lists of size at least dim+1 (and these points
  should be in general position).


Returns
-------
W  #V by #points-handles+(#region-handles * dim+1) matrix of weights so
  that columns correspond to each handles generalized barycentric
  coordinates (for point-handles) or animation space weights (for region
  handles).
returns true only on success


See also
--------


Notes
-----
None

Examples
--------
MatrixXd W;
igl::biharmonic_coordinates(V,F,S,W);
const size_t dim = T.cols()-1;
MatrixXd H(W.cols(),dim);
{
  int c = 0;
  for(int h = 0;h<S.size();h++)
  {
    if(S[h].size()==1)
    {
      H.row(c++) = V.block(S[h][0],0,1,dim);
    }else
    {
      H.block(c,0,dim+1,dim).setIdentity();
      c+=dim+1;
    }
   }
}
assert( (V-(W*H)).array().maxCoeff() < 1e-7 );

)igl_Qu8mg5v7";

npe_function(biharmonic_coordinates)
npe_doc(ds_biharmonic_coordinates)

npe_arg(v, dense_float, dense_double)
npe_arg(t, dense_float, dense_double)
npe_arg(s, std::vector<std::vector<int> > &)


npe_begin_code()

  npe_Matrix_v w;
  igl::biharmonic_coordinates(v, t, s, w);
  return npe::move(w);

npe_end_code()



const char* ds_bitriharmonic_coordinates = R"igl_Qu8mg5v7(

Parameters
----------
k  2-->biharmonic, 3-->triharmonic
The rest are the same as biharmonic_coordinates

Returns
-------


See also
--------


Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";

npe_function(bitriharmonic_coordinates)
npe_doc(ds_bitriharmonic_coordinates)

npe_arg(v, dense_float, dense_double)
npe_arg(t, dense_float, dense_double)
npe_arg(s, std::vector<std::vector<int> > &)
npe_arg(k, int)


npe_begin_code()

  npe_Matrix_v w;
  igl::biharmonic_coordinates(v, t, s, k, w);
  return npe::move(w);

npe_end_code()


