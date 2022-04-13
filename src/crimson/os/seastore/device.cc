// -*- mode:C++; tab-width:8; c-basic-offset:2; indent-tabs-mode:nil -*-
// vim: ts=8 sw=2 smarttab

#include "device.h"

#include "segment_manager.h"

namespace crimson::os::seastore {

std::ostream& operator<<(std::ostream& out, const device_spec_t& ds)
{
  return out << "device_spec("
             << "magic=" << ds.magic
             << ", device_type=" << ds.dtype
             << ", device_id=" << device_id_printer_t{ds.id}
             << ")";
}

std::ostream& operator<<(std::ostream& out, const device_config_t& conf)
{
  out << "device_config_t("
      << "major_dev=" << conf.major_dev
      << ", magic=" << conf.magic
      << ", device_type=" << conf.dtype
      << ", device_id=" << device_id_printer_t{conf.device_id}
      << ", meta=" << conf.meta
      << ", secondary(";
  for (const auto& [k, v] : conf.secondary_devices) {
    out << std::to_string(k) << ": " << v;
  }
  return out << "))";
}

seastar::future<DeviceRef>
Device::make_device(const std::string& device)
{
  // TODO: configure device type
  return SegmentManager::get_segment_manager(device
  ).then([](DeviceRef ret) {
    return ret;
  });
}

}