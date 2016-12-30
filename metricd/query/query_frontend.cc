/**
 * This file is part of the "FnordMetric" project
 *   Copyright (c) 2016 Paul Asmuth, FnordCorp B.V. <paul@asmuth.com>
 *
 * FnordMetric is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License v3.0. You should have received a
 * copy of the GNU General Public License along with this program. If not, see
 * <http://www.gnu.org/licenses/>.
 */
#include "metricd/query/query_frontend.h"

namespace fnordmetric {

QueryFrontend::QueryFrontend(
    MetricService* metric_service) :
    metric_service_(metric_service) {}

ReturnCode QueryFrontend::fetchTimeseriesJSON(
    const QueryOptions* query,
    json::JSONOutputStream* out) {

  auto metric_id = query->getProperty("metric_id");
  if (!metric_id) {
    return ReturnCode::error("EARG", "missing argument: metric_id");
  }

  MetricCursorOptions cursor_opts;

  FetchTimeseriesOperation fetch_op(
      metric_service_,
      *metric_id,
      std::move(cursor_opts));

  return ReturnCode::success();
}

} // namespace fnordmetric

