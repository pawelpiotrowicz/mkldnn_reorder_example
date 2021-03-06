#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include "dnnl.hpp"
// #include "example_utils.hpp"
using namespace dnnl;
using tag = memory::format_tag;
using dt = memory::data_type;


enum class LayoutType {
     NCHW,
     NHWC     
};


struct Tensor
{
         
         void reorder(LayoutType _layout /* ??? */)
         {
                
                                 
         }

};


void show(std::vector<int8_t>& v) 
{
      int cnt=0;
      for(auto item : v)
      {
         if(cnt++ == 32)
         {
            std::cout << std::endl;
            cnt=0;
         }
         std::cout << std::setw(3) << std::setfill(' ') << (int)item << " " ;
      }
      std::cout << std::endl;
}

void reorder_example(dnnl::engine::kind engine_kind=dnnl::engine::kind::cpu) {
    // Create execution dnnl::engine.
    dnnl::engine engine(engine_kind, 0);
    // Create dnnl::stream.
    dnnl::stream engine_stream(engine);
    // Tensor dimensions.
    const memory::dim N = 2, // batch size
            IC = 3, // channels
            IH = 4, // tensor height
            IW = 5; // tensor width
    // Source (src) and destination (dst) tensors dimensions.
    memory::dims src_dims = {N, IC, IH, IW};
    // Allocate buffers.
    std::vector<int8_t> src_data(N*IC*IH*IW);
    std::vector<int8_t> dst_data(N*IC*IH*IW);
    // Initialize src tensor.
    std::generate(src_data.begin(), src_data.end(), []() {
        static int i = 0;
        return i++;
    });

    show(src_data);
    // Create memory descriptors and memory objects for src and dst.
    auto src_md = memory::desc(src_dims, dt::s8, tag::nchw);
    auto dst_md = memory::desc(src_dims, dt::s8, tag::nhwc);
    auto src_mem = memory(src_md, engine);
    auto dst_mem = memory(dst_md, engine);
    // Write data to memory object's handle.
   // write_to_dnnl_memory(src_data.data(), src_mem);
    // // Per-channel scales.
    // std::vector<float> scales(IC);
    // std::generate(scales.begin(), scales.end(), []() {
    //     static int i = 0;
    //     return 64 + 5 * i++;
    // });
    // // Dimension of the dst tensor where the output scales will be applied
    // const int ic_dim = 1;
    // // Create primitive post-ops (per-channel output scales)
  
    primitive_attr reorder_attr;
   // reorder_attr.set_output_scales(0 | (1 << ic_dim), scales);
  
  
    // Create primitive descriptor.
    auto reorder_pd = reorder::primitive_desc(engine, src_md, engine, dst_md);
    // Create the primitive.
    auto reorder_prim = reorder(reorder_pd);
    // Primitive arguments.
    std::unordered_map<int, memory> reorder_args;
    reorder_args.insert({DNNL_ARG_SRC, src_mem});
    reorder_args.insert({DNNL_ARG_DST, dst_mem});
    // Primitive execution: reorder with scaled sum.
    reorder_prim.execute(engine_stream, reorder_args);
    // Wait for the computation to finalize.
    engine_stream.wait();
    // Read data from memory object's handle.
    std::cout << "---Reorder Output---" << std::endl; 
    show(dst_data);
  
  //  read_from_dnnl_memory(dst_data.data(), dst_mem);
}
int main(int argc, char **argv) {

  // auto k =  parse_engine_kind(argc, argv);
   reorder_example();
   return 9;
}