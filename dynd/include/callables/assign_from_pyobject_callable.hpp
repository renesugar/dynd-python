#pragma once

#include <dynd/callables/base_callable.hpp>
#include "kernels/assign_from_pyobject_kernel.hpp"

namespace pydynd {
namespace nd {

  template <type_id_t ResID>
  class assign_from_pyobject_callable
      : public dynd::nd::default_instantiable_callable<assign_from_pyobject_kernel<ResID>> {
  public:
    assign_from_pyobject_callable()
        : dynd::nd::default_instantiable_callable<assign_from_pyobject_kernel<ResID>>(
              dynd::ndt::callable_type::make(ResID, {dynd::ndt::make_type<pyobject_type>()}))
    {
    }
  };

  template <>
  class assign_from_pyobject_callable<bytes_id> : public dynd::nd::base_callable {
  public:
    assign_from_pyobject_callable()
        : dynd::nd::base_callable(dynd::ndt::callable_type::make(bytes_id, {dynd::ndt::make_type<pyobject_type>()}))
    {
    }

    ndt::type resolve(dynd::nd::base_callable *DYND_UNUSED(caller), char *DYND_UNUSED(data), dynd::nd::call_graph &cg,
                      const dynd::ndt::type &dst_tp, size_t DYND_UNUSED(nsrc),
                      const dynd::ndt::type *DYND_UNUSED(src_tp), size_t DYND_UNUSED(nkwd),
                      const dynd::nd::array *DYND_UNUSED(kwds),
                      const std::map<std::string, dynd::ndt::type> &DYND_UNUSED(tp_vars))
    {
      return dst_tp;
    }

    void instantiate(dynd::nd::call_node *&DYND_UNUSED(node), char *data, dynd::nd::kernel_builder *ckb,
                     const dynd::ndt::type &dst_tp, const char *dst_arrmeta, intptr_t nsrc,
                     const dynd::ndt::type *src_tp, const char *const *src_arrmeta, dynd::kernel_request_t kernreq,
                     intptr_t nkwd, const dynd::nd::array *kwds, const std::map<std::string, dynd::ndt::type> &tp_vars)
    {
      ckb->emplace_back<assign_from_pyobject_kernel<bytes_id>>(kernreq, dst_tp, dst_arrmeta);
    }
  };

  template <>
  class assign_from_pyobject_callable<fixed_bytes_id> : public dynd::nd::base_callable {
  public:
    assign_from_pyobject_callable()
        : dynd::nd::base_callable(
              dynd::ndt::callable_type::make(fixed_bytes_id, {dynd::ndt::make_type<pyobject_type>()}))
    {
    }

    ndt::type resolve(dynd::nd::base_callable *DYND_UNUSED(caller), char *DYND_UNUSED(data), dynd::nd::call_graph &cg,
                      const dynd::ndt::type &dst_tp, size_t DYND_UNUSED(nsrc),
                      const dynd::ndt::type *DYND_UNUSED(src_tp), size_t DYND_UNUSED(nkwd),
                      const dynd::nd::array *DYND_UNUSED(kwds),
                      const std::map<std::string, dynd::ndt::type> &DYND_UNUSED(tp_vars))
    {
      cg.push_back([dst_tp](dynd::nd::call_node *&node, dynd::nd::kernel_builder *ckb, dynd::kernel_request_t kernreq,
                            const char *dst_arrmeta, size_t nsrc, const char *const *src_arrmeta) {
        ckb->emplace_back<assign_from_pyobject_kernel<fixed_bytes_id>>(kernreq, dst_tp, dst_arrmeta);
        node = next(node);
      });

      return dst_tp;
    }
  };

  template <>
  class assign_from_pyobject_callable<string_id> : public dynd::nd::base_callable {
  public:
    assign_from_pyobject_callable()
        : dynd::nd::base_callable(dynd::ndt::callable_type::make(string_id, {dynd::ndt::make_type<pyobject_type>()}))
    {
    }

    ndt::type resolve(dynd::nd::base_callable *DYND_UNUSED(caller), char *DYND_UNUSED(data), dynd::nd::call_graph &cg,
                      const dynd::ndt::type &dst_tp, size_t DYND_UNUSED(nsrc),
                      const dynd::ndt::type *DYND_UNUSED(src_tp), size_t DYND_UNUSED(nkwd),
                      const dynd::nd::array *DYND_UNUSED(kwds),
                      const std::map<std::string, dynd::ndt::type> &DYND_UNUSED(tp_vars))
    {
      cg.push_back([dst_tp](dynd::nd::call_node *&node, dynd::nd::kernel_builder *ckb, dynd::kernel_request_t kernreq,
                            const char *dst_arrmeta, size_t nsrc, const char *const *src_arrmeta) {
        ckb->emplace_back<assign_from_pyobject_kernel<string_id>>(kernreq, dst_tp, dst_arrmeta);
        node = next(node);
      });

      return dst_tp;
    }
  };

  template <>
  class assign_from_pyobject_callable<fixed_string_id> : public dynd::nd::base_callable {
  public:
    assign_from_pyobject_callable()
        : dynd::nd::base_callable(
              dynd::ndt::callable_type::make(fixed_string_id, {dynd::ndt::make_type<pyobject_type>()}))
    {
    }

    ndt::type resolve(dynd::nd::base_callable *DYND_UNUSED(caller), char *DYND_UNUSED(data), dynd::nd::call_graph &cg,
                      const dynd::ndt::type &dst_tp, size_t DYND_UNUSED(nsrc),
                      const dynd::ndt::type *DYND_UNUSED(src_tp), size_t DYND_UNUSED(nkwd),
                      const dynd::nd::array *DYND_UNUSED(kwds),
                      const std::map<std::string, dynd::ndt::type> &DYND_UNUSED(tp_vars))
    {
      std::cout << "assign_from_pyobject_callable<fixed_string_id>::resolve" << std::endl;
      std::cout << "dst_tp = " << dst_tp << std::endl;

      cg.push_back([dst_tp](dynd::nd::call_node *&node, dynd::nd::kernel_builder *ckb, dynd::kernel_request_t kernreq,
                            const char *dst_arrmeta, size_t DYND_UNUSED(nsrc),
                            const char *const *DYND_UNUSED(src_arrmeta)) {
        std::cout << "assign_from_pyobject_callable<fixed_string_id>::instantiate" << std::endl;
        std::cout << "dst_tp = " << dst_tp << std::endl;

        ckb->emplace_back<assign_from_pyobject_kernel<fixed_string_id>>(kernreq, dst_tp, dst_arrmeta);
        node = next(node);
      });

      return dst_tp;
    }
  };

  template <>
  class assign_from_pyobject_callable<option_id> : public dynd::nd::base_callable {
  public:
    assign_from_pyobject_callable()
        : dynd::nd::base_callable(dynd::ndt::callable_type::make(option_id, {dynd::ndt::make_type<pyobject_type>()}))
    {
    }

    ndt::type resolve(dynd::nd::base_callable *DYND_UNUSED(caller), char *DYND_UNUSED(data), dynd::nd::call_graph &cg,
                      const dynd::ndt::type &dst_tp, size_t nsrc, const dynd::ndt::type *src_tp, size_t nkwd,
                      const dynd::nd::array *kwds, const std::map<std::string, dynd::ndt::type> &tp_vars)
    {
      cg.push_back([dst_tp](dynd::nd::call_node *&node, dynd::nd::kernel_builder *ckb, dynd::kernel_request_t kernreq,
                            const char *dst_arrmeta, size_t nsrc, const char *const *src_arrmeta) {
        intptr_t root_ckb_offset = ckb->size();
        ckb->emplace_back<assign_from_pyobject_kernel<option_id>>(kernreq, dst_tp, dst_arrmeta);
        node = next(node);
        intptr_t ckb_offset = ckb->size();
        node->instantiate(node, ckb, dynd::kernel_request_single, dst_arrmeta, nsrc, nullptr);

        ckb_offset = ckb->size();
        ckb->get_at<assign_from_pyobject_kernel<option_id>>(root_ckb_offset)->copy_value_offset =
            ckb_offset - root_ckb_offset;
        node->instantiate(node, ckb, dynd::kernel_request_single, dst_arrmeta, nsrc, src_arrmeta);

        ckb_offset = ckb->size();
      });

      dynd::nd::assign_na->resolve(this, nullptr, cg, dst_tp, nsrc, nullptr, nkwd, kwds, tp_vars);
      dynd::nd::assign->resolve(this, nullptr, cg, dst_tp.extended<dynd::ndt::option_type>()->get_value_type(), nsrc,
                                src_tp, nkwd, kwds, tp_vars);

      return dst_tp;
    }

    void instantiate(dynd::nd::call_node *&node, char *data, dynd::nd::kernel_builder *ckb,
                     const dynd::ndt::type &dst_tp, const char *dst_arrmeta, intptr_t nsrc,
                     const dynd::ndt::type *src_tp, const char *const *src_arrmeta, dynd::kernel_request_t kernreq,
                     intptr_t nkwd, const dynd::nd::array *kwds, const std::map<std::string, dynd::ndt::type> &tp_vars)
    {
      intptr_t root_ckb_offset = ckb->size();
      ckb->emplace_back<assign_from_pyobject_kernel<option_id>>(kernreq, dst_tp, dst_arrmeta);
      intptr_t ckb_offset = ckb->size();
      dynd::nd::assign_na->instantiate(node, NULL, ckb, dst_tp, dst_arrmeta, nsrc, NULL, NULL,
                                       dynd::kernel_request_single, nkwd, kwds, tp_vars);
      ckb_offset = ckb->size();
      ckb->get_at<assign_from_pyobject_kernel<option_id>>(root_ckb_offset)->copy_value_offset =
          ckb_offset - root_ckb_offset;
      dynd::nd::assign->instantiate(node, NULL, ckb, dst_tp.extended<dynd::ndt::option_type>()->get_value_type(),
                                    dst_arrmeta, nsrc, src_tp, src_arrmeta, dynd::kernel_request_single, nkwd, kwds,
                                    tp_vars);
      ckb_offset = ckb->size();
    }
  };

  template <>
  class assign_from_pyobject_callable<tuple_id> : public dynd::nd::base_callable {
  public:
    assign_from_pyobject_callable()
        : dynd::nd::base_callable(dynd::ndt::callable_type::make(tuple_id, {dynd::ndt::make_type<pyobject_type>()}))
    {
    }

    ndt::type resolve(dynd::nd::base_callable *DYND_UNUSED(caller), char *DYND_UNUSED(data), dynd::nd::call_graph &cg,
                      const dynd::ndt::type &dst_tp, size_t DYND_UNUSED(nsrc),
                      const dynd::ndt::type *DYND_UNUSED(src_tp), size_t DYND_UNUSED(nkwd),
                      const dynd::nd::array *DYND_UNUSED(kwds),
                      const std::map<std::string, dynd::ndt::type> &DYND_UNUSED(tp_vars))
    {
      std::cout << " assign_from_pyobject_callable<tuple_id>::resolve" << std::endl;

      return dst_tp;
    }

    void instantiate(dynd::nd::call_node *&node, char *data, dynd::nd::kernel_builder *ckb,
                     const dynd::ndt::type &dst_tp, const char *dst_arrmeta, intptr_t nsrc,
                     const dynd::ndt::type *src_tp, const char *const *src_arrmeta, dynd::kernel_request_t kernreq,
                     intptr_t nkwd, const dynd::nd::array *kwds, const std::map<std::string, dynd::ndt::type> &tp_vars)
    {
      bool dim_broadcast = false;

      intptr_t ckb_offset = ckb->size();
      intptr_t root_ckb_offset = ckb_offset;
      ckb->emplace_back<assign_from_pyobject_kernel<tuple_id>>(kernreq);
      assign_from_pyobject_kernel<tuple_id> *self = ckb->get_at<assign_from_pyobject_kernel<tuple_id>>(root_ckb_offset);
      ckb_offset = ckb->size();
      self->m_dst_tp = dst_tp;
      self->m_dst_arrmeta = dst_arrmeta;
      intptr_t field_count = dst_tp.extended<dynd::ndt::tuple_type>()->get_field_count();
      const dynd::ndt::type *field_types = dst_tp.extended<dynd::ndt::tuple_type>()->get_field_types_raw();
      const uintptr_t *arrmeta_offsets = dst_tp.extended<dynd::ndt::tuple_type>()->get_arrmeta_offsets_raw();
      self->m_dim_broadcast = dim_broadcast;
      self->m_copy_el_offsets.resize(field_count);
      for (intptr_t i = 0; i < field_count; ++i) {
        ckb->reserve(ckb_offset);
        self = ckb->get_at<assign_from_pyobject_kernel<tuple_id>>(root_ckb_offset);
        self->m_copy_el_offsets[i] = ckb_offset - root_ckb_offset;
        const char *field_arrmeta = dst_arrmeta + arrmeta_offsets[i];
        dynd::nd::assign->instantiate(node, NULL, ckb, field_types[i], field_arrmeta, nsrc, src_tp, src_arrmeta,
                                      dynd::kernel_request_single, nkwd, kwds, tp_vars);
        ckb_offset = ckb->size();
      }
    }
  };

  template <>
  class assign_from_pyobject_callable<struct_id> : public dynd::nd::base_callable {
  public:
    assign_from_pyobject_callable()
        : dynd::nd::base_callable(dynd::ndt::callable_type::make(struct_id, {dynd::ndt::make_type<pyobject_type>()}))
    {
    }

    ndt::type resolve(dynd::nd::base_callable *DYND_UNUSED(caller), char *DYND_UNUSED(data), dynd::nd::call_graph &cg,
                      const dynd::ndt::type &dst_tp, size_t nsrc, const dynd::ndt::type *src_tp, size_t nkwd,
                      const dynd::nd::array *kwds, const std::map<std::string, dynd::ndt::type> &tp_vars)
    {
      std::cout << " assign_from_pyobject_callable<struct_id>::resolve" << std::endl;
      std::cout << "dst_tp = " << dst_tp << std::endl;

      bool dim_broadcast = false;
      intptr_t field_count = dst_tp.extended<dynd::ndt::struct_type>()->get_field_count();
      const dynd::ndt::type *field_types = dst_tp.extended<dynd::ndt::struct_type>()->get_field_types_raw();
      const std::vector<uintptr_t> &arrmeta_offsets = dst_tp.extended<dynd::ndt::struct_type>()->get_arrmeta_offsets();

      cg.push_back([arrmeta_offsets, dim_broadcast, field_count,
                    dst_tp](dynd::nd::call_node *&node, dynd::nd::kernel_builder *ckb, dynd::kernel_request_t kernreq,
                            const char *dst_arrmeta, size_t nsrc, const char *const *src_arrmeta) {
        std::cout << " assign_from_pyobject_callable<struct_id>::instantiate" << std::endl;

        intptr_t ckb_offset = ckb->size();
        intptr_t root_ckb_offset = ckb_offset;

        ckb->emplace_back<assign_from_pyobject_kernel<struct_id>>(kernreq);
        node = next(node);

        assign_from_pyobject_kernel<struct_id> *self =
            ckb->get_at<assign_from_pyobject_kernel<struct_id>>(root_ckb_offset);
        ckb_offset = ckb->size();

        self->m_dst_tp = dst_tp;
        self->m_dst_arrmeta = dst_arrmeta;
        self->m_dim_broadcast = dim_broadcast;
        self->m_copy_el_offsets.resize(field_count);

        for (intptr_t i = 0; i < field_count; ++i) {
          ckb->reserve(ckb_offset);
          self = ckb->get_at<assign_from_pyobject_kernel<struct_id>>(root_ckb_offset);
          self->m_copy_el_offsets[i] = ckb_offset - root_ckb_offset;
          const char *field_arrmeta = dst_arrmeta + arrmeta_offsets[i];
          node->instantiate(node, ckb, dynd::kernel_request_single, field_arrmeta, nsrc, src_arrmeta);
          ckb_offset = ckb->size();
        }
      });

      for (intptr_t i = 0; i < field_count; ++i) {
        dynd::nd::assign->resolve(this, nullptr, cg, field_types[i], nsrc, src_tp, nkwd, kwds, tp_vars);
      }

      return dst_tp;
    }

    void instantiate(dynd::nd::call_node *node, char *data, dynd::nd::kernel_builder *ckb,
                     const dynd::ndt::type &dst_tp, const char *dst_arrmeta, intptr_t nsrc,
                     const dynd::ndt::type *src_tp, const char *const *src_arrmeta, dynd::kernel_request_t kernreq,
                     intptr_t nkwd, const dynd::nd::array *kwds, const std::map<std::string, dynd::ndt::type> &tp_vars)
    {
      bool dim_broadcast = false;

      intptr_t ckb_offset = ckb->size();
      intptr_t root_ckb_offset = ckb_offset;
      ckb->emplace_back<assign_from_pyobject_kernel<struct_id>>(kernreq);
      assign_from_pyobject_kernel<struct_id> *self =
          ckb->get_at<assign_from_pyobject_kernel<struct_id>>(root_ckb_offset);
      ckb_offset = ckb->size();
      self->m_dst_tp = dst_tp;
      self->m_dst_arrmeta = dst_arrmeta;
      intptr_t field_count = dst_tp.extended<dynd::ndt::struct_type>()->get_field_count();
      const dynd::ndt::type *field_types = dst_tp.extended<dynd::ndt::struct_type>()->get_field_types_raw();
      const uintptr_t *arrmeta_offsets = dst_tp.extended<dynd::ndt::struct_type>()->get_arrmeta_offsets_raw();
      self->m_dim_broadcast = dim_broadcast;
      self->m_copy_el_offsets.resize(field_count);
      for (intptr_t i = 0; i < field_count; ++i) {
        ckb->reserve(ckb_offset);
        self = ckb->get_at<assign_from_pyobject_kernel<struct_id>>(root_ckb_offset);
        self->m_copy_el_offsets[i] = ckb_offset - root_ckb_offset;
        const char *field_arrmeta = dst_arrmeta + arrmeta_offsets[i];
        dynd::nd::assign->instantiate(node, NULL, ckb, field_types[i], field_arrmeta, nsrc, src_tp, src_arrmeta,
                                      dynd::kernel_request_single, nkwd, kwds, tp_vars);
        ckb_offset = ckb->size();
      }
    }
  };

  template <>
  class assign_from_pyobject_callable<fixed_dim_id> : public dynd::nd::base_callable {
  public:
    assign_from_pyobject_callable()
        : dynd::nd::base_callable(dynd::ndt::callable_type::make(fixed_dim_id, {dynd::ndt::make_type<pyobject_type>()}))
    {
    }

    ndt::type resolve(dynd::nd::base_callable *DYND_UNUSED(caller), char *DYND_UNUSED(data), dynd::nd::call_graph &cg,
                      const dynd::ndt::type &dst_tp, size_t nsrc, const dynd::ndt::type *src_tp, size_t nkwd,
                      const dynd::nd::array *kwds, const std::map<std::string, dynd::ndt::type> &tp_vars)
    {
      std::cout << " assign_from_pyobject_callable<fixed_dim_id>::resolve" << std::endl;
      std::cout << "dst_tp = " << dst_tp << std::endl;

      dynd::ndt::type el_tp = dst_tp.extended<ndt::fixed_dim_type>()->get_element_type();

      cg.push_back([dst_tp](call_node *&node, dynd::nd::kernel_builder *ckb, dynd::kernel_request_t kernreq,
                            const char *dst_arrmeta, size_t nsrc, const char *const *src_arrmeta) {
        std::cout << " assign_from_pyobject_callable<fixed_dim_id>::instantiate" << std::endl;

        const char *el_arrmeta = dst_arrmeta + sizeof(size_stride_t);
        intptr_t dim_size = reinterpret_cast<const size_stride_t *>(dst_arrmeta)->dim_size;
        intptr_t stride = reinterpret_cast<const size_stride_t *>(dst_arrmeta)->stride;

        intptr_t ckb_offset = ckb->size();
        intptr_t root_ckb_offset = ckb_offset;
        ckb->emplace_back<assign_from_pyobject_kernel<fixed_dim_id>>(kernreq);
        node = next(node);

        assign_from_pyobject_kernel<fixed_dim_id> *self =
            ckb->get_at<assign_from_pyobject_kernel<fixed_dim_id>>(root_ckb_offset);
        ckb_offset = ckb->size();
        self->m_dim_size = dim_size;
        self->m_stride = stride;
        self->m_dst_tp = dst_tp;
        self->m_dst_arrmeta = dst_arrmeta;
        // from pyobject ckernel
        node->instantiate(node, ckb, dynd::kernel_request_strided, el_arrmeta, nsrc, src_arrmeta);

        ckb_offset = ckb->size();
        self = ckb->get_at<assign_from_pyobject_kernel<fixed_dim_id>>(root_ckb_offset);
        self->m_copy_dst_offset = ckb_offset - root_ckb_offset;
        // dst to dst ckernel, for broadcasting case
        dynd::nd::array error_mode = assign_error_fractional;
        node->instantiate(node, ckb, dynd::kernel_request_strided, el_arrmeta, 1, &el_arrmeta);
      });

      // from pyobject ckernel
      dynd::nd::assign->resolve(this, nullptr, cg, el_tp, nsrc, src_tp, nkwd, kwds, tp_vars);
      // dst to dst ckernel, for broadcasting case
      dynd::nd::array error_mode = assign_error_fractional;
      dynd::nd::assign->resolve(this, nullptr, cg, el_tp, 1, &el_tp, 1, &error_mode,
                                std::map<std::string, ndt::type>());

      return dst_tp;
    }
  };

  template <>
  class assign_from_pyobject_callable<var_dim_id> : public dynd::nd::base_callable {
  public:
    assign_from_pyobject_callable()
        : dynd::nd::base_callable(dynd::ndt::callable_type::make(var_dim_id, {dynd::ndt::make_type<pyobject_type>()}))
    {
    }

    ndt::type resolve(dynd::nd::base_callable *DYND_UNUSED(caller), char *DYND_UNUSED(data), dynd::nd::call_graph &cg,
                      const dynd::ndt::type &dst_tp, size_t nsrc, const dynd::ndt::type *src_tp, size_t nkwd,
                      const dynd::nd::array *kwds, const std::map<std::string, dynd::ndt::type> &tp_vars)
    {
      std::cout << " assign_from_pyobject_callable<var_dim_id>::resolve" << std::endl;

      bool dim_broadcast = false;

      dynd::ndt::type el_tp = dst_tp.extended<dynd::ndt::var_dim_type>()->get_element_type();

      cg.push_back([dst_tp, el_tp](dynd::nd::call_node *&node, dynd::nd::kernel_builder *ckb,
                                   dynd::kernel_request_t kernreq, const char *dst_arrmeta, size_t nsrc,
                                   const char *const *src_arrmeta) {
        intptr_t ckb_offset = ckb->size();

        intptr_t root_ckb_offset = ckb_offset;
        ckb->emplace_back<assign_from_pyobject_kernel<var_dim_id>>(kernreq);
        assign_from_pyobject_kernel<var_dim_id> *self =
            ckb->get_at<assign_from_pyobject_kernel<var_dim_id>>(root_ckb_offset);
        node = next(node);
        ckb_offset = ckb->size();
        self->m_offset = reinterpret_cast<const dynd::ndt::var_dim_type::metadata_type *>(dst_arrmeta)->offset;
        self->m_stride = reinterpret_cast<const dynd::ndt::var_dim_type::metadata_type *>(dst_arrmeta)->stride;
        self->m_dst_tp = dst_tp;
        self->m_dst_arrmeta = dst_arrmeta;
        const char *el_arrmeta = dst_arrmeta + sizeof(dynd::ndt::var_dim_type::metadata_type);
        node->instantiate(node, ckb, dynd::kernel_request_strided, el_arrmeta, nsrc, src_arrmeta);
        ckb_offset = ckb->size();
        self = ckb->get_at<assign_from_pyobject_kernel<var_dim_id>>(root_ckb_offset);
        self->m_copy_dst_offset = ckb_offset - root_ckb_offset;
        // dst to dst ckernel, for broadcasting case
        dynd::nd::array error_mode = assign_error_fractional;
        node->instantiate(node, ckb, dynd::kernel_request_strided, el_arrmeta, 1, &el_arrmeta);
      });

      dynd::nd::assign->resolve(this, nullptr, cg, el_tp, nsrc, src_tp, nkwd, kwds, tp_vars);

      dynd::nd::array error_mode = assign_error_fractional;
      dynd::nd::assign->resolve(this, nullptr, cg, el_tp, 1, &el_tp, 1, &error_mode, tp_vars);

      return dst_tp;
    }

    void instantiate(dynd::nd::call_node *&node, char *data, dynd::nd::kernel_builder *ckb,
                     const dynd::ndt::type &dst_tp, const char *dst_arrmeta, intptr_t nsrc,
                     const dynd::ndt::type *src_tp, const char *const *src_arrmeta, dynd::kernel_request_t kernreq,
                     intptr_t nkwd, const dynd::nd::array *kwds, const std::map<std::string, dynd::ndt::type> &tp_vars)
    {
      intptr_t ckb_offset = ckb->size();
      bool dim_broadcast = false;

      intptr_t root_ckb_offset = ckb_offset;
      ckb->emplace_back<assign_from_pyobject_kernel<var_dim_id>>(kernreq);
      assign_from_pyobject_kernel<var_dim_id> *self =
          ckb->get_at<assign_from_pyobject_kernel<var_dim_id>>(root_ckb_offset);
      ckb_offset = ckb->size();
      self->m_offset = reinterpret_cast<const dynd::ndt::var_dim_type::metadata_type *>(dst_arrmeta)->offset;
      self->m_stride = reinterpret_cast<const dynd::ndt::var_dim_type::metadata_type *>(dst_arrmeta)->stride;
      self->m_dst_tp = dst_tp;
      self->m_dst_arrmeta = dst_arrmeta;
      dynd::ndt::type el_tp = dst_tp.extended<dynd::ndt::var_dim_type>()->get_element_type();
      const char *el_arrmeta = dst_arrmeta + sizeof(dynd::ndt::var_dim_type::metadata_type);
      dynd::nd::assign->instantiate(node, NULL, ckb, el_tp, el_arrmeta, nsrc, src_tp, src_arrmeta,
                                    dynd::kernel_request_strided, nkwd, kwds, tp_vars);
      ckb_offset = ckb->size();
      self = ckb->get_at<assign_from_pyobject_kernel<var_dim_id>>(root_ckb_offset);
      self->m_copy_dst_offset = ckb_offset - root_ckb_offset;
      // dst to dst ckernel, for broadcasting case
      dynd::nd::array error_mode = assign_error_fractional;
      dynd::nd::assign->instantiate(node, NULL, ckb, el_tp, el_arrmeta, 1, &el_tp, &el_arrmeta,
                                    dynd::kernel_request_strided, 1, &error_mode, std::map<std::string, ndt::type>());
    }
  };

} // namespace pydynd::nd
} // namespace pydynd
