#pragma once
#include "geometry.h"
#include <string>
#include <vector>

bool parseMeshGltf(const std::string& path,
                   std::vector<Vertex>& verts,
                   std::vector<uint32_t>& idxs,
                   std::string& error);

bool parseMeshObj(const std::string& path,
                  std::vector<Vertex>& verts,
                  std::vector<uint32_t>& idxs,
                  std::string& error);
