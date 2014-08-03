/**
 * This file is part of the "FnordMetric" project
 *   Copyright (c) 2011-2014 Paul Asmuth, Google Inc.
 *
 * FnordMetric is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License v3.0. You should have received a
 * copy of the GNU General Public License along with this program. If not, see
 * <http://www.gnu.org/licenses/>.
 */
#include <fnordmetric/web/assets.h>
#include <fnordmetric/web/queryendpoint.h>
#include <fnordmetric/query/queryservice.h>

namespace fnordmetric {
namespace web {

std::unique_ptr<http::HTTPHandler> QueryEndpoint::getHandler() {
  return std::unique_ptr<http::HTTPHandler>(new QueryEndpoint());
}

bool QueryEndpoint::handleHTTPRequest(
    http::HTTPRequest* request,
    http::HTTPResponse* response) {
  auto url = request->getUrl();

  if (url.substr(0, 6) == "/query") {
    response->setStatus(200);
    response->addHeader("Content-Type", "application/json; charset=utf-8");

    auto input_stream = request->getBodyInputStream();
    auto output_stream = response->getBodyOutputStream();

    query::QueryService query_service;
    query_service.executeQuery(
        input_stream.get(),
        query::QueryService::FORMAT_SVG,
        output_stream.get());

    response->addHeader(
        "Content-Length",
        std::to_string(response->getBody().size()));

    return true;
  }

  return false;
}

}
}