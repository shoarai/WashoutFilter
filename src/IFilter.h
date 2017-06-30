// Copyright (c) 2017 shoarai

#pragma once

class IFilter
{
public:
  virtual double doFilter(const double &input) = 0;
};
