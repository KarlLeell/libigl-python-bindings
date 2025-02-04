#include <common.h>
#include <npe.h>
#include <igl/cut_mesh_from_singularities.h>

const char* ds_cut_mesh_from_singularities = R"igl_Qu8mg5v7(
Given a mesh (v,f) and the integer mismatch of a cross field per edge
(mismatch), finds and returns the cut_graph connecting the singularities
(seams)

Parameters
----------
v : #v by 3 array of triangle vertices (each row is a vertex)
f : #f by 3 array of triangle indices into v
mismatch : #f by 3 array of per-corner integer mismatches

Returns
-------
seams : #f by 3 array of per corner booleans that denotes if an edge is a
        seam or not

See also
--------
cut_mesh

Notes
-----

Examples
--------

)igl_Qu8mg5v7";

npe_function(cut_mesh_from_singularities)
npe_doc(ds_cut_mesh_from_singularities)
npe_arg(v, dense_double, dense_float)
npe_arg(f, dense_int, dense_long)
npe_arg(mismatch, dense_int)
npe_begin_code()

    // FIXME: LibIGL templates are broken so we need to do copies :'(
    npe_Matrix_v v_copy;
    npe_Matrix_f f_copy;

    Eigen::Matrix<bool, Eigen::Dynamic, Eigen::Dynamic, npe_Matrix_f::Options> seams;

    igl::cut_mesh_from_singularities(v_copy, f_copy, mismatch, seams);

    return npe::move(seams);
npe_end_code()
