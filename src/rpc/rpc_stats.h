#pragma once
#include <ostream>

namespace smf {

struct rpc_stats {
  size_t active_connections{};
  size_t total_connections{};
  size_t in_bytes{};
  size_t out_bytes{};
  size_t bad_requests{};
  size_t completed_requests{};
  size_t too_large_requests{};
  // you need this so you can invoke
  // on a distributed<type> obj_ a map reduce
  // i.e.:
  // obj_.map_reduce(adder<type>, &outer::rpc_stats);
  void operator+=(const rpc_stats &o) {
    active_connections += o.active_connections;
    total_connections += o.total_connections;
    in_bytes += o.in_bytes;
    out_bytes += o.out_bytes;
    bad_requests += o.bad_requests;
    completed_requests += o.completed_requests;
    too_large_requests += o.too_large_requests;
  }
  rpc_stats self() {
    return *this; // make a copy for map_reduce framework
  }
  std::ostream &operator<<(std::ostream &o) {
    o << "active conn: " << active_connections << ", "
      << "total conn: " << total_connections << ", "
      << "in bytes: " << in_bytes << ", "
      << "out bytes: " << out_bytes << ", "
      << "bad requests: " << bad_requests << ", "
      << "completed requests: " << completed_requests << ", "
      << "too large requests: " << too_large_requests;
    return o;
  }
  future<> stop() { return make_ready_future<>(); }
};
}