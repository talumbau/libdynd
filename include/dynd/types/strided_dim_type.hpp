//
// Copyright (C) 2011-14 Mark Wiebe, DyND Developers
// BSD 2-Clause License, see LICENSE.txt
//

#ifndef _DYND__STRIDED_ARRAY_TYPE_HPP_
#define _DYND__STRIDED_ARRAY_TYPE_HPP_

#include <dynd/type.hpp>
#include <dynd/types/base_uniform_dim_type.hpp>
#include <dynd/typed_data_assign.hpp>
#include <dynd/types/view_type.hpp>

namespace dynd {

struct strided_dim_type_metadata {
    intptr_t size;
    intptr_t stride;
};

struct strided_dim_type_iterdata {
    iterdata_common common;
    char *data;
    intptr_t stride;
};

class strided_dim_type : public base_uniform_dim_type {
    std::vector<std::pair<std::string, gfunc::callable> > m_array_properties, m_array_functions;
public:
    strided_dim_type(const ndt::type& element_tp);

    virtual ~strided_dim_type();

    size_t get_default_data_size(intptr_t ndim, const intptr_t *shape) const;

    void print_data(std::ostream& o, const char *metadata, const char *data) const;

    void print_type(std::ostream& o) const;

    bool is_expression() const;
    bool is_unique_data_owner(const char *metadata) const;
    void transform_child_types(type_transform_fn_t transform_fn, void *extra,
                    ndt::type& out_transformed_tp, bool& out_was_transformed) const;
    ndt::type get_canonical_type() const;
    bool is_strided() const;
    void process_strided(const char *metadata, const char *data,
                    ndt::type& out_dt, const char *&out_origin,
                    intptr_t& out_stride, intptr_t& out_dim_size) const;

    ndt::type apply_linear_index(intptr_t nindices, const irange *indices,
                size_t current_i, const ndt::type& root_tp, bool leading_dimension) const;
    intptr_t apply_linear_index(intptr_t nindices, const irange *indices, const char *metadata,
                    const ndt::type& result_tp, char *out_metadata,
                    memory_block_data *embedded_reference,
                    size_t current_i, const ndt::type& root_tp,
                    bool leading_dimension, char **inout_data,
                    memory_block_data **inout_dataref) const;
    ndt::type at_single(intptr_t i0, const char **inout_metadata, const char **inout_data) const;

    ndt::type get_type_at_dimension(char **inout_metadata, intptr_t i, intptr_t total_ndim = 0) const;

    intptr_t get_dim_size(const char *metadata, const char *data) const;
        void get_shape(intptr_t ndim, intptr_t i, intptr_t *out_shape, const char *metadata, const char *data) const;
    void get_strides(size_t i, intptr_t *out_strides, const char *metadata) const;

    axis_order_classification_t classify_axis_order(const char *metadata) const;

    bool is_lossless_assignment(const ndt::type& dst_tp, const ndt::type& src_tp) const;

    bool operator==(const base_type& rhs) const;

    void metadata_default_construct(char *metadata, intptr_t ndim, const intptr_t* shape) const;
    void metadata_copy_construct(char *dst_metadata, const char *src_metadata, memory_block_data *embedded_reference) const;
    void metadata_reset_buffers(char *metadata) const;
    void metadata_finalize_buffers(char *metadata) const;
    void metadata_destruct(char *metadata) const;
    void metadata_debug_print(const char *metadata, std::ostream& o, const std::string& indent) const;
    size_t metadata_copy_construct_onedim(char *dst_metadata, const char *src_metadata,
                    memory_block_data *embedded_reference) const;

    size_t get_iterdata_size(intptr_t ndim) const;
    size_t iterdata_construct(iterdata_common *iterdata, const char **inout_metadata, intptr_t ndim, const intptr_t* shape, ndt::type& out_uniform_tp) const;
    size_t iterdata_destruct(iterdata_common *iterdata, intptr_t ndim) const;

    void data_destruct(const char *metadata, char *data) const;
    void data_destruct_strided(const char *metadata, char *data,
                    intptr_t stride, size_t count) const;

    size_t make_assignment_kernel(
                    ckernel_builder *out, size_t offset_out,
                    const ndt::type& dst_tp, const char *dst_metadata,
                    const ndt::type& src_tp, const char *src_metadata,
                    kernel_request_t kernreq, assign_error_mode errmode,
                    const eval::eval_context *ectx) const;

    void foreach_leading(char *data, const char *metadata, foreach_fn_t callback, void *callback_data) const;
    
    /**
     * Modifies metadata allocated using the metadata_default_construct function, to be used
     * immediately after nd::array construction. Given an input type/metadata, edits the output
     * metadata in place to match.
     *
     * \param dst_metadata  The metadata created by metadata_default_construct, which is modified in place
     * \param src_tp  The type of the input nd::array whose stride ordering is to be matched.
     * \param src_metadata  The metadata of the input nd::array whose stride ordering is to be matched.
     */
    void reorder_default_constructed_strides(
                    char *dst_metadata,
                    const ndt::type& src_tp, const char *src_metadata) const;

    void get_dynamic_type_properties(
                    const std::pair<std::string, gfunc::callable> **out_properties,
                    size_t *out_count) const;
    void get_dynamic_array_properties(
                    const std::pair<std::string, gfunc::callable> **out_properties,
                    size_t *out_count) const;
    void get_dynamic_array_functions(
                    const std::pair<std::string, gfunc::callable> **out_functions,
                    size_t *out_count) const;
};

namespace ndt {
    inline ndt::type make_strided_dim(const ndt::type& element_tp) {
        return ndt::type(new strided_dim_type(element_tp), false);
    }

    inline ndt::type make_strided_dim(const ndt::type& uniform_tp, intptr_t ndim) {
        ndt::type result = uniform_tp;
        for (intptr_t i = 0; i < ndim; ++i) {
            result = make_strided_dim(result);
        }
        return result;
    }
} // namespace ndt

} // namespace dynd

#endif // _DYND__STRIDED_ARRAY_TYPE_HPP_
